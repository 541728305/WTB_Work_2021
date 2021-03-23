#include "NET_iic.h"
#include "delay.h"

#include "myiic.h"
#define Net_Write    0
#define Net_Read     1

/****************************************************
	* File Name     : Net_IIC_Init
	* Description   : initalize iic gpio,congiratin pull Up or drain output 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void Net_IIC_Init(void)
{					     
	//PG9 SDA  PD6 SCL
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_6); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_9); 	
}
/****************************************************
	* File Name     : Idle_IIC_BUS
	* Description   : initalize iic gpio,congiratin float input 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void Idle_IIC_BUS(){
	//PB5 SDA  PB4 SCL
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
}
/****************************************************
	* File Name     : Net_IIC_Start
	* Description   : set iic start condition 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void Net_IIC_Start(void)
{
	Net_SDA_OUT();    
	Net_IIC_SDA=1;	  	  
	Net_IIC_SCL=1;
	delay_us(IIC_DELAY_TIME);
 	Net_IIC_SDA=0;
	delay_us(IIC_DELAY_TIME);
	Net_IIC_SCL=0;
}
/****************************************************
	* File Name     : Net_IIC_Stop
	* Description   : set iic stop condition 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void Net_IIC_Stop(void)
{
	Net_SDA_OUT();
	Net_IIC_SCL=0;
	Net_IIC_SDA=0;
 	delay_us(IIC_DELAY_TIME);
	Net_IIC_SCL=1; 
	Net_IIC_SDA=1;
	delay_us(IIC_DELAY_TIME);							   	
}
/****************************************************
	* File Name     : Net_IIC_Wait_Ack
	* Description   : Wait slave device acknowledge
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
u8 Net_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	Net_SDA_IN();     
	Net_IIC_SDA=1;delay_us(IIC_DELAY_TIME);	   
	Net_IIC_SCL=1;delay_us(IIC_DELAY_TIME);	 
	while(Net_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			Net_IIC_Stop();
// 			cyc4or3run();
// 			lcd_printf ("Device NO ACK   ");
			return 1;
		}
	}
	Net_IIC_SCL=0;
	delay_us(IIC_DELAY_TIME);	 
	return 0;  
} 
/****************************************************
	* File Name     : Net_IIC_Ack
	* Description   : Master Send acknowledge signal to slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*****************************************************/
void Net_IIC_Ack(void)
{
	Net_IIC_SCL=0;
	Net_SDA_OUT();
	Net_IIC_SDA=0;
	delay_us(IIC_DELAY_TIME);
	Net_IIC_SCL=1;
	delay_us(IIC_DELAY_TIME);
	Net_IIC_SCL=0;
}
/****************************************************
	* File Name     : Net_IIC_Ack
	* Description   : Master Send NO acknowledge signal to slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/		    
void Net_IIC_NAck(void)
{
	Net_IIC_SCL=0;
	Net_SDA_OUT();
	Net_IIC_SDA=1;
	delay_us(IIC_DELAY_TIME);
	Net_IIC_SCL=1;
	delay_us(IIC_DELAY_TIME);
	Net_IIC_SCL=0;
}					 				     
/****************************************************
	* File Name     : Net_IIC_Send_Byte
	* Description   : Master Send one byte to slave
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/				  
void Net_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		Net_SDA_OUT(); 	    
    Net_IIC_SCL=0;
    for(t=0;t<8;t++) {              
		if((txd&0x80)>>7)
			Net_IIC_SDA=1;
		else
			Net_IIC_SDA=0;
		txd<<=1; 	  
		delay_us(IIC_DELAY_TIME);  
		Net_IIC_SCL=1;
		delay_us(IIC_DELAY_TIME); 
		Net_IIC_SCL=0;	
		delay_us(IIC_DELAY_TIME);
    }	 

}
/****************************************************
	* File Name     : Net_IIC_Read_Byte
	* Description   : Master read one byte from slave
  * Input         : ack true Send ack false Send NACK
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/
u8 Net_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	Net_SDA_IN();
  for(i=0;i<8;i++ )
	{
    Net_IIC_SCL=0; 
    delay_us(IIC_DELAY_TIME);
		Net_IIC_SCL=1;
    receive<<=1;
    if(Net_READ_SDA)
			receive++;   
		delay_us(IIC_DELAY_TIME); 
   }					 
   if (!ack)
     Net_IIC_NAck();//发送nACK
   else
     Net_IIC_Ack(); //发送ACK   
   return receive;
}

/****************************************************
	* File Name     : Read_One_Byte_Data
	* Description   : Master read one byte from slave
  * Input         : Slave_Addr, Reg_Addr,data data buffer
	* return        : OK return 0 
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/
u8 Read_One_Byte_Data(u8 Slave_Addr ,u8  Reg_Addr,u8 *data){	  	    																 
	Net_IIC_Start();  
	Net_IIC_Send_Byte((Slave_Addr<<1)|Net_Write);	 
	if(Net_IIC_Wait_Ack())
		return 1 ;
	Net_IIC_Send_Byte(Reg_Addr); 
	if(Net_IIC_Wait_Ack())
		return 1 ;    
	Net_IIC_Start();  	 	   
	Net_IIC_Send_Byte((Slave_Addr<<1)|Net_Read);        		   
	if(Net_IIC_Wait_Ack())
		return 1 ; 
	*data = Net_IIC_Read_Byte(0);		   
	Net_IIC_Stop(); 
	return 0 ;
}
/****************************************************
	* File Name     : Read_NByte_Data
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr, Reg_Addr,data data buffer
	* return        : OK return 0 
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/
u8 Read_NByte_Data(u8 Slave_Addr ,u8  Reg_Addr,u8 Nbyte , u8 *data){	
  u8 i;	
	Net_IIC_Start();  
	Net_IIC_Send_Byte((Slave_Addr<<1)|Net_Write);	 
	if(Net_IIC_Wait_Ack())
		return 1 ;
	Net_IIC_Send_Byte(Reg_Addr); 
	if(Net_IIC_Wait_Ack())
		return 1 ;    
	Net_IIC_Start();  	 	   
	Net_IIC_Send_Byte((Slave_Addr<<1)|Net_Read);        		   
	if(Net_IIC_Wait_Ack())
		return 1 ; 
	for(i = 0; i<Nbyte ; i++){
		if(i != Nbyte-1 )
			*data = Net_IIC_Read_Byte(1);		
		else 
			*data = Net_IIC_Read_Byte(0);	
		data ++;
	}		
	Net_IIC_Stop(); 
	return 0 ;
}

/****************************************************
	* File Name     : Write_OneByteToDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器地址 Data，待写入数据
	* return        : OK return 0 
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/
//u8 Write_OneByteToDevice(u8 Slave_Addr, u8 Reg_Addr, u8 Data){
//	  Net_IIC_Start();  
//		Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	   
//			if( Net_IIC_Wait_Ack())
//		return 1;
//		Net_IIC_Send_Byte(Reg_Addr);  
//			if( Net_IIC_Wait_Ack())
//		return 1;	  										  		   
//		Net_IIC_Send_Byte(Data);   
//			if( Net_IIC_Wait_Ack())
//		return 1;	   
//		Net_IIC_Stop();
//		delay_ms(10);	
//		return 0 ;
//}
/******************************************************************************************************************
	* File Name     : Write_NByteDataToDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器地址 *Data，待写入数据指针，Length数据长度
	* return        : 写入结果，OK ，返回0  NG 返回 1.
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
******************************************************************************************************************/
//u8 Write_NByteDataToDevice(u8 Slave_Addr, u8 Reg_Addr, u8 *Data_Addr,u8 Length){
//		u8 i;
//	  Net_IIC_Start();  
//		Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	   
//		if( Net_IIC_Wait_Ack())
//			return 1;
//		Net_IIC_Send_Byte(Reg_Addr);  
//		if( Net_IIC_Wait_Ack())
//			return 1;
//		for(i=0;i<Length;i++){
//			Net_IIC_Send_Byte(Data_Addr[i]);   
//			if( Net_IIC_Wait_Ack())
//				return 1;
//		}			
//		Net_IIC_Stop();
//		delay_ms(10);	
//		return 0 ;
//}
/******************************************************************************************************************
	* File Name     : Read_OneByteFromDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器地址 *Data，读取数据存放地址
	* return        : 读取结果，OK ，返回0  NG 返回 1.
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
******************************************************************************************************************/
//u8 Read_OneByteFromDevice(u8 Slave_Addr ,u8  Reg_Addr,u8 *ReadData ){				  	    																 
//	Net_IIC_Start();  
//	Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	 
//	if( Net_IIC_Wait_Ack())
//		return 1;
//	Net_IIC_Send_Byte(Reg_Addr); 
//	if( Net_IIC_Wait_Ack())
//		return 1;
//	Net_IIC_Start();  	 	   
//	Net_IIC_Send_Byte((Slave_Addr<<1)|Read );        		   
//	if( Net_IIC_Wait_Ack())
//		return 1;	
//	ReadData[0]=Net_IIC_Read_Byte(0);		//读单个字节，发送非应答信号   
//	Net_IIC_Stop();   
//	return 0 ; 
//}
/******************************************************************************************************************
	* File Name     : Read_NByteFromDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器起始地址 *Data，读取数据存放地址 ，Length 数据长度
	* return        : 读取结果，OK ，返回0  NG 返回 1.
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
******************************************************************************************************************/
//u8 Read_NByteFromDevice(u8 Slave_Addr ,u8  Reg_Addr,u8 *ReadData,u8  Length ){				  
//	u8 i;		  	    																 
//	Net_IIC_Start();  
//	Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	 
//	if( Net_IIC_Wait_Ack())
//		return 1;	
//	Net_IIC_Send_Byte(Reg_Addr); 
//	if( Net_IIC_Wait_Ack())
//		return 1;	   
//	Net_IIC_Start();  	 	   
//	Net_IIC_Send_Byte((Slave_Addr<<1)|Read);        		   
//	if( Net_IIC_Wait_Ack())
//		return 1;	 
//	for(i=0;i<Length ;i++){
//		if(i!=Length -1)
//			ReadData[i]=Net_IIC_Read_Byte(1);	
//		else 
//			ReadData[i]=Net_IIC_Read_Byte(0);	
//	}		
//	Net_IIC_Stop();   
//	return 0 ; 
//}



/****************************************************
	* File Name     : Write_OneByteToDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器地址 Data，待写入数据
	* return        : OK return 0 
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
****************************************************/
u8 Write_OneByteToDevice(u8 Slave_Addr, u8 Reg_Addr, u8 Data){
	  Net_IIC_Start();  
		Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	   
			if( Net_IIC_Wait_Ack())
		return 1;
		Net_IIC_Send_Byte(Reg_Addr);  
			if( Net_IIC_Wait_Ack())
		return 1;	  										  		   
		Net_IIC_Send_Byte(Data);   
			if( Net_IIC_Wait_Ack())
		return 1;	   
		Net_IIC_Stop();
		delay_ms(10);	
		return 0 ;
}
/******************************************************************************************************************
	* File Name     : Write_NByteDataToDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器地址 *Data，待写入数据指针，Length数据长度
	* return        : 写入结果，OK ，返回0  NG 返回 1.
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
******************************************************************************************************************/
u8 Write_NByteDataToDevice(u8 Slave_Addr, u8 Reg_Addr, u8 *Data_Addr,u8 Length){
		u8 i;
	  Net_IIC_Start();  
		Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	   
		if( Net_IIC_Wait_Ack())
			return 1;
		Net_IIC_Send_Byte(Reg_Addr);  
		if( Net_IIC_Wait_Ack())
			return 1;
		for(i=0;i<Length;i++){
			Net_IIC_Send_Byte(Data_Addr[i]);   
			if( Net_IIC_Wait_Ack())
				return 1;
		}			
		Net_IIC_Stop();
		delay_ms(10);	
		return 0 ;
}
/******************************************************************************************************************
	* File Name     : Read_OneByteFromDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器地址 *Data，读取数据存放地址
	* return        : 读取结果，OK ，返回0  NG 返回 1.
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
******************************************************************************************************************/
u8 Read_OneByteFromDevice(u8 Slave_Addr ,u8  Reg_Addr,u8 *ReadData ){				  	    																 
		Net_IIC_Start();  
		Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	 
		if( Net_IIC_Wait_Ack())
			return 1;
		Net_IIC_Send_Byte(Reg_Addr); 
		if( Net_IIC_Wait_Ack())
			return 1;
		Net_IIC_Start();  	 	   
		Net_IIC_Send_Byte((Slave_Addr<<1)|Read );        		   
		if( Net_IIC_Wait_Ack())
			return 1;	
		ReadData[0]=Net_IIC_Read_Byte(0);		//读单个字节，发送非应答信号   
		Net_IIC_Stop();   
		return 0 ; 
}
/******************************************************************************************************************
	* File Name     : Read_NByteFromDevice
	* Description   : Master read N byte from slave
  * Input         : Slave_Addr，从机7bit地址，Reg_Addr，8bit 寄存器起始地址 *Data，读取数据存放地址 ，Length 数据长度
	* return        : 读取结果，OK ，返回0  NG 返回 1.
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
******************************************************************************************************************/
u8 Read_NByteFromDevice(u8 Slave_Addr ,u8  Reg_Addr,u8 *ReadData,u8  Length ){				  
		u8 i;		  	    																 
		Net_IIC_Start();  
		Net_IIC_Send_Byte((Slave_Addr<<1)|Write);	 
		if( Net_IIC_Wait_Ack())
			return 1;	
		Net_IIC_Send_Byte(Reg_Addr); 
		if( Net_IIC_Wait_Ack())
			return 1;	   
		Net_IIC_Start();  	 	   
		Net_IIC_Send_Byte((Slave_Addr<<1)|Read);        		   
		if( Net_IIC_Wait_Ack())
			return 1;	 
		for(i=0;i<Length ;i++){
			if(i!=Length -1)
				ReadData[i]=Net_IIC_Read_Byte(1);	
			else 
				ReadData[i]=Net_IIC_Read_Byte(0);	
		}		
		Net_IIC_Stop();   
		return 0 ; 
}

