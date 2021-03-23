#ifndef __NET_IIC_H_
#define __NET_IIC_H_
#include "stm32f10x_it.h" 

typedef enum  {
		Ack_OK=0,
		Ack_NG=1	
}Flag_Ack_TypeDef;

typedef enum  {
		Pass=0,
		Fail=1	
}Test_Resut_TypeDef;

//	//PF5 SDA  PF4 SCL
#define Net_SDA_IN()  {GPIOG->CRH&=0XFFFFFF0F;GPIOG->CRH|=0x00000080;}
#define Net_SDA_OUT() {GPIOG->CRH&=0XFFFFFF0F;GPIOG->CRH|=0x00000030;}      //外部有上拉配置为开漏输出

#define Net_IIC_SCL    PDout(6) 
#define Net_IIC_SDA    PGout(9)
#define Net_READ_SDA   PGin(9)  

//#define Net_SCL_IN()   {GPIOB->CRL&=0XF0FFFFFF;GPIOB->CRL|=0x04000000;}
void Net_IIC_Init(void);                	 
void Net_IIC_Start(void);				
void Net_IIC_Stop(void);	  			
void Net_IIC_Send_Byte(u8 txd);			
u8 	 Net_IIC_Read_Byte(unsigned char ack);
u8 	 Net_IIC_Wait_Ack(void); 				
void Net_IIC_Ack(void);					
void Net_IIC_NAck(void);				

void  IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 		IIC_Read_One_Byte(u8 daddr,u8 addr);
u8 		Read_IR_Sensor_data(u8 ack);
void  Write_IR_Sensor_data(u8  dat);
u8 		ReadOneByte_IR_Sensor_Reg(u8 Slave_Addr ,u8  Reg_Addr);
void  WriteOneByte_IR_Sensor_Reg(u8 Slave_Addr, u8 Reg_Addr,u8 DataToWrite);

void Idle_IIC_BUS(void);


u8 Write_OneByteToDevice(u8 Slave_Addr, u8 Reg_Addr, u8 Data);
u8 Read_OneByteFromDevice(u8 Slave_Addr ,u8  Reg_Addr,u8 *ReadData );
u8 Read_NByteFromDevice(u8 Slave_Addr ,u8  Reg_Addr,u8 *ReadData,u8  Length );
u8 Write_NByteDataToDevice(u8 Slave_Addr, u8 Reg_Addr, u8 *Data_Addr,u8 Length);

#endif
















