#ifndef _AD5933_H_
#define _AD5933_H
#include "sys.h"
//#define LCR_debug 

#define I2C0_SCL_IN()      {GPIOG->CRL&=0XFFFFFFF0;GPIOG->CRL|=0x00000008;}
#define I2C0_SCL_OUT   		 {GPIOG->CRL&=0XFFFFFFF0;GPIOG->CRL|=0x00000003;}

#define I2C0_SDA_IN()  		 {GPIOG->CRL&=0XFFFFFF0F;GPIOG->CRL|=0x00000080;}
#define I2C0_SDA_OUT() 		 {GPIOG->CRL&=0XFFFFFF0F;GPIOG->CRL|=0x00000030;}

#define I2C0_SCL           PGout(0) //SCL
#define ad5933_READ_SCL    PGin(0)  //输入SCL
#define I2C0_SDA           PGout(1) //SDA	 
#define I2C0_READ_SDA      PGin(1)  //输入SDA 


#define AD5933_Slave_Addr       0x0D
#define AD5933_MCLK             16776000 // 16.776MHz
//comtrol regsitor ox80 commad
#define AD5933_Init_Start_Fre   0x10
#define AD5993_Start_Fre_Scan   0x20
#define AD5933_Fre_Increment    0x30
#define AD5933_Repeat_Fre       0x40
#define AD5933_Temp_Measure     0x90
#define AD5933_Sleep_Mode       0xA0
#define AD5933_Standby_Mode     0xB0


#define AD5933_Vpp_200mV        0x02
#define AD5933_Vpp_400mV        0x04
#define AD5933_Vpp_1000mV       0x06
#define AD5933_Vpp_2000mV       0x00

#define AD599_PGA_Gain_5X       0x00
#define AD599_PGA_Gain_1X       0x01

#define AD5933_Reset            0x10
#define AD5933_Internal_Clock   0x00
#define AD5933_Exteral_Clock    0x80
#define AD5933_Temperature      0x90
#define AD5933_Status_REG       0x8F
//*********AD5933特殊指令*****************************
#define AD5933_Block_Write_Cmd     0xA0
#define AD5933_Block_Read_Cmd      0xA1
#define AD5933_Block_Addr_Pointer  0xB0

typedef enum {
	__Inductor = 0,
	__Capacitor,
	__Resistor
}Network_type_def;
#define Range_Num        1 


void AD5933_Initalize(void);
double LCR_Test(uint8_t Network_type,uint8_t range,uint8_t Test_Num);

#endif

