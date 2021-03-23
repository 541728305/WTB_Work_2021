#include "24cxx.h" 
#include "lcd3033.h"
#include "myiic.h"
#include "delay.h"
#include "menu.h"
#include "other.h"
#include "stdio.h"
/*********************************************************************************************
	* File Name     : AT24CXX_ReadOneByte
	* Description   : Read one byte to EEPROM  
  * Input         : ReadAddr EEPROM   Address 
  * return        : data 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
u8 AT24CXX_ReadOneByte(u16 ReadAddr){				  
	u8 temp=0;		  	    																 
	IIC_Start();  
	IIC_Send_Byte(0XA0);	 
	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr>>8);
	IIC_Wait_Ack();		 
	IIC_Send_Byte(ReadAddr%256);   
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);            
	IIC_Wait_Ack();	 
	temp=IIC_Read_Byte(0);		   
	IIC_Stop();  
	return temp;
}
/*********************************************************************************************
	* File Name     : AT24CXX_WriteOneByte
	* Description   : Write one byte to EEPROM  
  * Input         : ReadAddr EEPROM   Address  DataToWrite
  * return        : 、 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite){				   	  	    																 
  IIC_Start();  
	IIC_Send_Byte(0XA0);	    
	IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr>>8);
	IIC_Wait_Ack();	 
  IIC_Send_Byte(WriteAddr%256);  
	IIC_Wait_Ack();					  		   
	IIC_Send_Byte(DataToWrite);    
	IIC_Wait_Ack();
  IIC_Stop();
	delay_ms(10);	 
}
/*********************************************************************************************
	* File Name     : AT24CXX_WriteLenByte
	* Description   : Write N byte to EEPROM  
  * Input         : ReadAddr EEPROM   Address  DataToWrite Len
  * return        : 、 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len){  	
	u8 t;
	for(t=0;t<Len;t++){
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
/*********************************************************************************************
	* File Name     : AT24CXX_ReadLenByte
	* Description   : Read N byte to EEPROM  
  * Input         : ReadAddr EEPROM   Address  DataToWrite Len
  * return        : 、 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len){  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++){
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

u8 AT24CXX_Check(void){
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);		   
	if(temp==0X55)return 0;		   
	else{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}
/*********************************************************************************************
	* File Name     : AT24CXX_Read
	* Description   : Read N byte to EEPROM  
  * Input         : ReadAddr EEPROM   Address  DataToWrite Len
  * return        : 、 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead){
	while(NumToRead){
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} 
/*********************************************************************************************
	* File Name     : AT24CXX_Write
	* Description   : Write N byte to EEPROM  
  * Input         : ReadAddr EEPROM   Address  DataToWrite Len
  * return        : 、 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite){
	while(NumToWrite--){
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}


typedef  union {
	uint8_t buf[8];
	double  Value;
}double_Type;
double_Type double_data;
#include <math.h>

/**********************************************************************************
	* File Name     : Write_double_data
	* Description   : 向eepROM内写入double类型数据
  * Input         : Addr 存储位置 dat 待写入数据
  * return        : 
	* Author        : Morton
	* Date          : 2018/11/18
***********************************************************************************/
void Write_double_data( uint16_t Addr ,double dat ){
	uint8_t CNT = 0;
	double_data.Value = dat;
	for( CNT = 0; CNT < 8 ; CNT ++)
		AT24CXX_WriteOneByte(Addr+CNT,double_data.buf[CNT ] );

}
/**********************************************************************************
	* File Name     : read_double_data
	* Description   : 从eepROM内读取double类型数据
  * Input         : Addr 存储位置
  * return        : 返回double数据
	* Author        : Morton
	* Date          : 2018/11/18
***********************************************************************************/
double read_double_data( uint16_t Addr ){
	uint8_t CNT = 0;
	for( CNT = 0; CNT < 8 ; CNT ++)
		double_data.buf[CNT] = AT24CXX_ReadOneByte(Addr+CNT);
	if(isnan(double_data.Value)){
		double_data.Value = 0.0;
		Write_double_data(Addr,8);
	}
		
	return  double_data.Value ;
}

