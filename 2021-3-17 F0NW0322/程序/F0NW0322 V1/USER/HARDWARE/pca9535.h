#ifndef _PCA9535_H_
#define _PCA9535_H_
#include"stm32f10x_it.h" 

#define  Slave_Addr_PCA9535_U79   0x20|0x02  //U79  A2 A1 A0 010
#define  Slave_Addr_PCA9535_U80   0x20|0x04  //U80  A2 A1 A0 100
#define  Slave_Addr_PCA9535_U81   0x20|0x06  //U81  A2 A1 A0 110

#define  PCA9535_Config_Reg_H          0x07
#define  PCA9535_Config_Reg_L          0x06

#define  PCA9535_Polarity_Inversion_H  0x05
#define  PCA9535_Polarity_Inversion_L  0x04

#define  PCA9535_Output_Port_Reg_H     0x03
#define  PCA9535_Output_Port_Reg_L     0x02

#define  PCA9535_Input_Port_Reg_H      0x01
#define  PCA9535_Input_Port_Reg_L      0x00


#define K89_COMD_TO_GND          (uint16_t)(0x0001)
#define K13_COMA_TO_Rref_L       (uint16_t)(0x0002)
#define K13_COMC_TO_Rref_L       (uint16_t)(0x0004)

#define K13_COMB_TO_GND          (uint16_t)(0x0040) //1<<6
#define K13_COMB_TO_IN2          (uint16_t)(0x0080) //1<<7

#define K89_COMD_TO_IN2          (uint16_t)(0x0100) //1<<8
#define K89_Rref_H_TO_IN0        (uint16_t)(0x0200) //1<<9
#define K89_Rref_L_TO_IN1        (uint16_t)(0x0400)
#define K35_COMD_Double_TO_GND   (uint16_t)(0x0800)

#define K35_COMB_TO_SCL          (uint16_t)(0x1000)
#define K8_Power_TO_Sound        (uint16_t)(0x2000)
#define K8_ARMIO_TO_INT1         (uint16_t)(0x4000)
#define K35_COMA_TO_SDA          (uint16_t)(0x8000)

#define ALL_U81_Pin              (uint16_t)(0xFFFF)           
void Initalize_PCA9535(void );
void Close_All_Analog_Relay(void );
void Analog_Relay( uint16_t  Num ,u8 Status);
#endif
