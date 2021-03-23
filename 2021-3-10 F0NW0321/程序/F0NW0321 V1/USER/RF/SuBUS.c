#include "subus.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd3033.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "other.h"
#include "test.h"

//#define  Debug_Mode

#define CPLF_RST  PFout(13)



#define  SuBus_WRITE   0x04 //3位写命令
#define  SuBus_READ    0x02

#define SWITCH_PAC_STATE     0x00
#define VVAR                 0x02
#define PM_TRIG              0x1C
#define PRODUCT_ID           0x1D
#define MANUFACTURER_ID_Addr 0x1E
#define MAN_USID             0x1F
#define SuBUS_Calibration1   0x13



uint8_t   USID = 0x6 ;





void suBUS_reset_CPLD()
{
    CPLF_RST = 1;
		delay_ms(1);
    CPLF_RST = 0;
		delay_ms(1);
}
// 8 bit dat  FCS 4 bit
u8 SuBus8_proce(u8 da)
{
	u8 i,qz=3,fz=qz,crc=0;
	u8 array[8];
	
	for(array[0]=fz,i=1;i<8;i++)
	{
		fz<<=1;
		if(fz>15)	
			fz=(fz&0x0f)^qz;		
		array[i]=fz;
	}
	
	for(i=0;i<8;i++)
	{
		if((da&(1<<i))>0) crc^=array[i];
	}
	return (crc);
}

// 12 bit dat  FCS 5 bit

u8 SuBus12_proce( u8 Sladd,u8 command, u8 RegAdd  )
{
	u8 qz=5,i,fz=qz,crc=0;
	u8 array[12];
	u16 da;	
	
	for(array[0]=fz,i=1;i<12;i++)
	{
		fz<<=1;
		if(fz>31)	fz=(fz&0x1f)^qz;		
		array[i]=fz;
	}
	
	da=((Sladd&15)<<8);
	da|=((command&7)<<5);
	da|=(RegAdd&31);
	
	for(i=0;i<12;i++)
	{
		if((da&(0x0001<<i))>0) crc^=(u16)(array[i]);
	}
	return (crc);
}

/*
名称： suBus_Read_Data_Generate
功能:  根据入口参数，生成CPLD接口数据
参数1: 器件地址4位
参数2: 寄存器地址5位
参数3: 校验值5位
参数4: 生成的数据存放地址 至少4字节数据
*/
void suBus_Read_Data_Generate(u8 Sub_ID,u8 Reg_Add,u8 *da)
{

	u8  FCS5= SuBus12_proce(Sub_ID,SuBus_READ,Reg_Add);//前面的5位检验值
	
	da[0]=0x00;da[1]=0x00;da[2]=0x00;da[3]=0x00;
	
	da[0]=((Sub_ID&0x0f)<<4)|((SuBus_READ&7) <<1)|((Reg_Add&0x1f)>>4)  ;
	da[1]=((Reg_Add&0x0f)<<4)|((FCS5&0x1f)>>1); 
	da[2]=((FCS5&0x01)<<7); 

#if defined Debug_Mode
		Uart_printf(USART1,"Read_Add: 0x%02X    \r\n",Reg_Add);
		Uart_printf(USART1,"FCS5: 0x%02X    \r\n",FCS5);
		Uart_printf(USART1,"Send:-%02X-%02X-%02X-%02X\r\n",da[0],da[1], da[2],da[3]);	
#endif		
}


/*
名称： suBus_Read_Data_Generate
功能:  根据入口参数，生成CPLD接口数据
参数1: 器件地址4位
参数2: 寄存器地址5位
参数3: 校验值5位
参数4: 待写入的寄存器值8位
参数5: 校验值4位
参数6: 生成的数据存放地址 至少4字节数据
*/
void suBus_Write_Data_Generate(u8 Sub_ID,u8 Reg_Add, u8 Write_data, u8 *da)
{

	u8  FCS5 = SuBus12_proce(Sub_ID ,SuBus_WRITE,Reg_Add);
	u8  FCS4 = SuBus8_proce(Write_data);	
	
	da[0]=0x00;da[1]=0x00;da[2]=0x00;da[3]=0x00;
	
	da[0]=((Sub_ID&0x0f)<<4)|((SuBus_WRITE&7) <<1)|((Reg_Add&0x1F)>>4)  ;
	da[1]=((Reg_Add&0x0f)<<4) | ((FCS5&0x1f)>>1); 
	da[2]=((FCS5&0x01)<<7) | ((Write_data&0xfe)>>1) ; 	
	da[3]=((Write_data&0x01)<<7) | ((FCS4&0x0f)<<3);
	
	
#if defined Debug_Mode
		Uart_printf(USART1,"Write_Add: 0x%02X    \r\n",Reg_Add);
		Uart_printf(USART1,"Data: 0x%02X    \r\n",Write_data);		
		Uart_printf(USART1,"FCS5: 0x%02X    \r\n",FCS5);	
		Uart_printf(USART1,"FCS4: 0x%02X    \r\n",FCS4);	
		Uart_printf(USART1,"Send:-%02X-%02X-%02X-%02X\r\n",da[0],da[1], da[2],da[3]);	
#endif		
}
/*
名称： suBus_Read_Reg_Val
功能:  读suBus寄存器值
参数1: 数据串 4Byte 
返回： 
*/
u8 suBus_Read_Reg_Val(u8 *da,u8 *ReadData)
{
	char  buf[10];
  suBUS_reset_CPLD();
	RESET_UART(USART3);
	_Uart_printf(USART3 ,da,4);
	if(_Get_USART_buffer(USART3,buf, 100)== 2){	
		*ReadData=buf[0];
		return  0;
	}else{
		return 1;
	}
}

/*
名称： suBus_Write_Reg_Val
功能:  读suBus寄存器值
参数1: 数据串 4Byte 
返回： 
*/

u8 suBus_Write_Reg_Val(u8 *da)
{

	char buf[128];
  suBUS_reset_CPLD();
	RESET_UART(USART3);
	_Uart_printf(USART3 ,da,4);
	if(_Get_USART_buffer(USART3,buf, 100)== 2){	
		return  0;
	}else{
		return 1;
	}
}


uint8_t ReadRegValue( uint8_t Reg_Add ,uint8_t *RegValue){
	
		uint8_t da[10];
		suBus_Read_Data_Generate( USID, Reg_Add,da);	
		return suBus_Read_Reg_Val(da,RegValue);
}
	
uint8_t WriteRegValue( uint8_t Reg_Addr ,uint8_t RegValue){
	uint8_t da[10];
	suBus_Write_Data_Generate( USID,Reg_Addr,RegValue,da);
	return suBus_Write_Reg_Val(da);
}



void SbudCondition( uint8_t Status){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14; //RESET
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_13);
	
	if(Status == SET ){
		GPIO_SetBits(GPIOF,GPIO_Pin_14);
		uart3_init(115200);	
	}else{
		GPIO_ResetBits(GPIOF,GPIO_Pin_14);
	}	
	delay_ms (80);
}



uint8_t ChangeRFSwitch( uint8_t RF_Status)
{
	uint8_t RegValue=0x00;
	if(WriteRegValue(SWITCH_PAC_STATE,RF_Status)==True){
			if(ReadRegValue(SWITCH_PAC_STATE,&RegValue) ==True && RegValue == RF_Status){
				return True ;	
		}
	}
	return False ;
}

/***********************************************************************************************************************
	* File Name     : SetRFSwitchStatus
	* Description   : SetRFSwitchStatus
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-April-2020
************************************************************************************************************************/
uint8_t  SetRFSwitchStatus(  uint8_t RF_Status, uint8_t Timer){
	
	uint8_t i = 0,RegValue=0x00;
	for( i = 0 ; i < Timer ; i ++)
	{
		WriteRegValue(PM_TRIG,0x38); 
		ReadRegValue (PM_TRIG,&RegValue);
		if(RegValue!= 0x38)
			continue ;
		
		WriteRegValue(VVAR,0x00);
		ReadRegValue (VVAR,&RegValue);
		if(RegValue!= 0x00)
			continue ;
		
		WriteRegValue(SuBUS_Calibration1,0x06);
		ReadRegValue (SuBUS_Calibration1,&RegValue);
		if(RegValue!= 0x06)
			continue ;		
		
		WriteRegValue(SWITCH_PAC_STATE,RF_Status);
		ReadRegValue (SWITCH_PAC_STATE,&RegValue);
		if(RegValue!= RF_Status)
			continue ;	
		return True;
	}
	return False ;
}

