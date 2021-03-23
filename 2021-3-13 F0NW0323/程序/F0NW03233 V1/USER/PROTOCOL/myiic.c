#include "myiic.h"
#include "global.h"
#include "delay.h"
#include "lcd3033.h"
/****************************************************
	* File Name     : IIC_Start
	* Description   : set iic start condition 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void IIC_Start(void){
	SDA_OUT();     
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(IIC_DELAY_TIME);
 	IIC_SDA=0; 
	delay_us(IIC_DELAY_TIME);
	IIC_SCL=0;
}	
/****************************************************
	* File Name     : IIC_Stop
	* Description   : set iic stop condition 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void IIC_Stop(void){
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(IIC_DELAY_TIME);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(IIC_DELAY_TIME);							   	
}
/****************************************************
	* File Name     : IIC_Wait_Ack
	* Description   : Wait slave device acknowledge
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
u8 IIC_Wait_Ack(void){
	u8 ucErrTime=0;
	SDA_IN();      
	IIC_SDA=1;delay_us(IIC_DELAY_TIME);	   
	IIC_SCL=1;delay_us(IIC_DELAY_TIME);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			lcd_printf ("Device NO ACK   ");
			return 1;
		}
	}
	IIC_SCL=0;
	delay_us(IIC_DELAY_TIME);	 
	return 0;  
} 
/****************************************************
	* File Name     : IIC_Ack
	* Description   : Master Send acknowledge signal to slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void IIC_Ack(void){
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL=1;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL=0;
}
/****************************************************
	* File Name     : IIC_NAck
	* Description   : Master Send NO acknowledge signal to slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/		    
void IIC_NAck(void){
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL=1;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL=0;
}					 				     
/****************************************************
	* File Name     : IIC_Send_Byte
	* Description   : Master Send one byte to slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/			  
void IIC_Send_Byte(u8 txd){                        
    u8 t;   
		SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(IIC_DELAY_TIME);   
		IIC_SCL=1;
		delay_us(IIC_DELAY_TIME); 
		IIC_SCL=0;	
		delay_us(IIC_DELAY_TIME);
    }	 
} 	      
/****************************************************
	* File Name     : IIC_Read_Byte
	* Description   : Master read one byte from slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
u8 IIC_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	SDA_IN();
  for(i=0;i<8;i++ )
	{
    IIC_SCL=0; 
    delay_us(IIC_DELAY_TIME);
		IIC_SCL=1;
    receive<<=1;
    if(READ_SDA)
			receive++;   
		delay_us(IIC_DELAY_TIME); 
   }					 
   if (!ack)
     IIC_NAck();
   else
     IIC_Ack(); 
   return receive;
}














