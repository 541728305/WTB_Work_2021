#include "ad7176.h"
#include "lcd3033.h"
#include "global.h"
#include "delay.h"
#include "Sup_Fun.h"
#include "stdio.h"
#include "other.h"

uint8_t AD7176_Rate_Set = 1;
/*********************************************************************************************
	* File Name     : AD_Sample_Rate_Set
	* Description   : Set ADC Sample rate 
  * Input         :  i Sample rate 
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void AD_Sample_Rate_Set(uint8_t i){
	
	 AD7176_Rate_Set = i;
}

/*********************************************************************************************
	* File Name     : AD7176_Write_Data
	* Description   : SPI interface Write regsitor 
  * Input         : reg regsitor Address data   byteCon Number 
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
static void AD7176_Write_Data(u8 reg, u16 data,u8 byteCon){		 //向寄存器写配置值
		u8 i;
		u8 command= AD717X_COMM_REG_WR | AD717X_COMM_REG_RA(reg);	
		u8 bitCon=byteCon<<3;
		AD7176_Sclk=1;
		AD7176_CS=0;
		for(i=0;i<8;i++)	   //发送命令
		{
			AD7176_Sclk=0;
			if(command &0x80)
				AD7176_Din=1;
			else 
				AD7176_Din=0;
		 
			AD7176_Sclk=1;
			
			command<<=1;
		}
	  
		for(i=0;i<bitCon;i++)
		{
			AD7176_Sclk=0;
			if(data &0x8000)
				AD7176_Din=1;
			else 
				AD7176_Din=0;		
			
			AD7176_Sclk=1;
//		  delay_us(AD7176_SCLK_Delay);	
			data<<=1;
		}
	
		AD7176_CS=1;
}
/*********************************************************************************************
	* File Name     : AD7176_Read_Data
	* Description   : SPI interface read regsitor 
  * Input         : reg regsitor Address  byteCon Number 
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
static  uint32_t AD7176_Read_Data(u8 reg,u8 byteCon)			  
{
	u8 i;
	uint32_t ReadData=0;		
	u8 command= AD717X_COMM_REG_RD | AD717X_COMM_REG_RA(reg);	
  u8 bitCon=byteCon<<3;
	AD7176_Sclk=1;
	AD7176_CS=0;
	for(i=0;i<8;i++)//发送读命令
	{
		AD7176_Sclk=0;
		if(command &0x80)
			AD7176_Din=1;
		else 
			AD7176_Din=0;
	
		AD7176_Sclk=1;
		
		command<<=1;
	}	
//   delay_us(AD7176_SCLK_Delay);		
	for(i=0;i<bitCon;i++)//读bitCon位数据 MSB
	{
		ReadData<<=1; 	
		AD7176_Sclk=0;		 
//    delay_us(AD7176_SCLK_Delay);		
		if(AD7176_Dout==1)
			ReadData|=1;	 
		AD7176_Sclk=1;
 //   delay_us(AD7176_SCLK_Delay);		
	}
//  delay_us(AD7176_SCLK_Delay);	
  AD7176_CS=1;	
	return (ReadData);
}

// 0x0003-50K快速 0x000A-1K 中速 0x0A0A-20SPS 慢速
/*********************************************************************************************
	* File Name     : AD7176_Configure
	* Description   : Sample Volts and calc  Average
  * Input         : AinP anolog postive  timer AinN *readmV
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
static  void AD7176_Configure(uint32_t AinP,uint32_t AinN)
{	
	 u16 reg_dat=AD717X_CHMAP_REG_CH_EN |AD717X_CHMAP_REG_SETUP_SEL(0)|AD717X_CHMAP_REG_AINPOS(AinP)|AD717X_CHMAP_REG_AINNEG(AinN);
 	 AD7176_Write_Data(AD717X_CHMAP0_REG, reg_dat ,2); 	
	 AD7176_Write_Data(0x20,0x0000,2);//SETUP CONFIGURATION REGISTER 0	：单极性输出，外部5V基准参考	  Setup0
 	 if(AD7176_Rate_Set == 3){
				AD7176_Write_Data(0x28, 0x000A, 2);
	 }else  if(AD7176_Rate_Set == 2)
				AD7176_Write_Data(0x28,0x0007,2);//，ADC数据传出为中等速度	Setup0
	 else if(AD7176_Rate_Set == 1)
		 		AD7176_Write_Data(0x28,0x0003,2);//  ADC数据传出为中等速度	Setup0
	 else
				AD7176_Write_Data(0x28,0x0000,2);//  ADC数据传出为中等速度	Setup0
	 AD7176_Write_Data(0x01,0x8210,2);//ADC MODE REGISTER				
}                       
u8 Read_AD7176_Voltage(uint32_t AinP,uint32_t AinN, double * readmV){
		uint32_t times=3000000L;
		double mV;
		uint32_t DataReg=0;
		AD7176_Configure(AinP ,AinN );		
		AD7176_CS=0;
		while((--times)&&(AD7176_Dout));
		if(times==0) 
		 return (1);
		DataReg=AD7176_Read_Data ( AD717X_DATA_REG, 3);
		mV= (DataReg*5000.0)/16777215.0;
		*readmV=mV;	  
		return (0);
}
u8 Read_AD7176_Voltage_mV(uint32_t AinP,uint32_t AinN, double * readmV)
{	
		Read_AD7176_Voltage(AinP,AinN,readmV);
		return 0;
}
/*********************************************************************************************
	* File Name     : Read_AD7176_Average_Voltage_mV
	* Description   : Sample Volts and calc  Average
  * Input         : AinP anolog postive  timer AinN *readmV
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
u8 Read_AD7176_Average_Voltage_mV(uint32_t AinP,uint32_t AinN,uint32_t timer, double * readmV){
		uint8_t  i,j;
		double  readdata[100],temp ;

		for(i=0;i<timer;i++){
			if(Read_AD7176_Voltage(AinP,AinN,readmV)!= True )
				return 1;
			readdata[i] = *readmV;
		}
		for ( i = 0 ; i < (timer-1) ; i++){
			 for ( j = i + 1 ; j < timer ; j++) {
					if (readdata[j] < readdata[i])
					{
						temp = readdata[i] ;
						readdata[i] = readdata[j] ;
						readdata[j] = temp ;
					}
			 }
		}
		*readmV=0;
		// 0 1 2 3 4 
		for(i=2;i<timer-2;i++){
			*readmV += readdata[i];
		}
		*readmV = *readmV/(timer -4);
		return 0;
}
/*********************************************************************************************
	* File Name     : Read_AD7176_Voltage_mV_Auto
	* Description   : AD7176 Sample once Volts
  * Input         : AinP anolog postive  AinN *readmV
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
u8 Read_AD7176_Voltage_mV_Auto(uint32_t AinP,uint32_t AinN, double * readmV){
	 uint32_t times=3000000L;
	 double mV;
	 uint32_t DataReg=0;
	 AD7176_Configure(AinP ,AinN );		
	 AD7176_CS=0;
	 while((--times)&&(AD7176_Dout));
	 if(times==0) 
		 return (1);
	 DataReg=AD7176_Read_Data ( AD717X_DATA_REG, 3);
	 mV= (DataReg*5000.0)/16777215.0;
	 if(mV>=5000.0) {
		 times=3000000L;
		 AD7176_Configure(AIN0 ,VREFP );
		 AD7176_CS=0;		 
		 while((--times)&&(AD7176_Dout));
		 if(times==0) 
			 return (2);
		 DataReg=AD7176_Read_Data ( AD717X_DATA_REG, 3);
		 mV= (DataReg*5000.0)/16777215.0+3300;		 
	 }
	 *readmV = mV;
 	 return (0);
}
//u8 Read_AD7176_Voltage_uV(uint32_t AinP,uint32_t AinN,uint32_t Gain, double * readmV)
//{
//	 uint32_t times=3000000L;
//	 double mV;
//	 uint32_t DataReg=0;
//	 AD7176_Configure(AinP, AinN);
//	 while((--times)&&(AD7176_Dout));
//	 if(times==0) 
//		 return (1);
//	 DataReg=AD7176_Read_Data ( AD717X_DATA_REG, 3);//	
//	 mV = (DataReg*5000.0)/1677215.0 ;
//	 *readmV=mV;	 
//	 if(mV>5000.0) 
//		 return (3); 
//	 return (0);
//}

/*********************************************************************************************
	* File Name     : Initialize_AD7176
	* Description   : Initialize AD7176 configration  
  * Input         : 、
  * return        : 、
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void Initialize_AD7176(){
		uint8_t  i; uint16_t  AD7176_ID_Data = 0x0000;
		AD7176_CS=0;
		AD7176_Sclk  = 1;
		delay_ms (1);
		AD7176_Din  = 1;  
		for(i=0;i<70;i++){
			AD7176_Sclk=0;
			AD7176_Sclk=1;
		}
		delay_ms (1);
		AD7176_ID_Data = AD7176_Read_Data (AD717X_ID_REG,2);
		//if((AD7176_ID_Data&0xfff0)!=0x0C90)
		if((AD7176_ID_Data&0xfff0)>0xfff0 && (AD7176_ID_Data&0xfff0) <0x0F)
		{
			 lcdreset ();
			 lcdpos (0,0); lcd_printf  ("     Warning     ");
			 lcdpos (1,0); lcd_printf  ("ADC ID:%04X   OK",AD7176_ID_Data);
			 while(1){beep (1,200);}		

		}	
		cyc4or3run (); lcd_printf  ("ADC ID:%04X   OK",AD7176_ID_Data);
}
 /*********************************************************************************************
	* File Name     : STM32_Software_Hander
	* Description   : STM32 Software reset
  * Input         : /
  * return        : /
	* Author        : Morton
	* Date          : 2019/1/9
*********************************************************************************************/
void STM32_Software_Reset_Hander(void){
		Relay_Drive (0,SET);
		__set_FAULTMASK(1);
		NVIC_SystemReset();
}
/*******************************************************************************************************
	* File Name     :  Receive_MCUISP_Command
	* Description   :  Receive_MCUISP_Command
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/7/11
*******************************************************************************************************/
void MCUISP_Hander(void) {	
	AD7176_Write_Data( 0x06,0x000f, 2);//向寄存器写配置值 
	delay_ms (300);
 	STM32_Software_Reset_Hander();	
}

