#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#define   SMALL_CAP_TEST_GATE_BIT_0           PFout(5)  //档位选择bit0  JP18 --10
#define   SMALL_CAP_TEST_GATE_BIT_1           PFout(6)  //档位选择bit1  JP18 --9
#define   SMALL_CAP_TEST_GATE_BIT_2           PFout(7)  //档位选择bit2  JP18 --8


#define   SMALL_CAP_TEST_TYPE_SELECT_BIT_0    PFout(9) //元件类型选择bit0  JP18 --6
#define   SMALL_CAP_TEST_TYPE_SELECT_BIT_1    PFout(8) //元件类型选择bit1  JP18 --7

//***********************MAX CAP***********************
#define CAP_S0   PCout(8)
#define CAP_S1   PCout(7)
#define CAP_S2   PCout(6)
//***********************Beep***********************
#define Beep PAout(15)
//*********************  LCD**************************
#define lcdcs    PEout(7)
#define lcdsid   PEout(8)
#define lcdsclk  PEout(9)
//**************************************IIC**********************************************************
//PA14 SCL PA15 SDA
#define SDA_IN()  {GPIOE->CRL&=0XFFFF0FFF;GPIOE->CRL|=0x000008000;}
#define SDA_OUT() {GPIOE->CRL&=0XFFFF0FFF;GPIOE->CRL|=0x000003000;}
#define IIC_SCL    PEout(2) //SCL
#define IIC_SDA    PEout(3) //SDA	 
#define READ_SDA   PEin(3)  //输入SDA 
//PG15 SCL PB3 SDA
#define SDA_IN1()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=0x00008000;}
#define SDA_OUT1() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=0x00003000;}
#define IIC_SCL1    PGout(15) //SCL
#define IIC_SDA1    PBout(3) //SDA	 
#define READ_SDA1   PBin(3)  //输入SDA 

//********************************Driver Cylinder and Relay***************************************************
#define  Valve_Relay_EN  PGout(1)

#define  Valve_Sck    PAout(12)
#define  Valve_Data   PAout(15)
#define  Valve_ST1    PDout(3)
#define  Valve_ST2    PAout(8)
#define  Valve_ST3    PDout(0)

//#define  Relay_Sck    PCout(7)
//#define  Relay_Data   PCout(8)
//#define  Relay_ST1    PCout(9)
//#define  Relay_ST2    PGout(8)

//***********************************AD7176*********************************
#define AD7176_Din   		 PBout(5)  
#define AD7176_Sclk  		 PBout(9) 
#define AD7176_CS    		 PEout(1)  
#define AD7176_SYNC  		 PEout(0)
#define AD7176_Dout  		 PBin(8) 
//*************************************Sensor GPIO  define *****************..
//#define SENSOR1          PGin(6)
//#define SENSOR2          PGin(7)

#define SENSOR1          PBin(0)
#define SENSOR2          PBin(1)
#define SENSOR3          PFin(11)
#define SENSOR4          PFin(12)

#define SENSOR5          PCin(5)
#define SENSOR6          PCin(4)

#define SENSOR7          PAin(7)
#define SENSOR8          PAin(6)
#define SENSOR9          PAin(5)

#define SENSOR10         PAin(1)
#define SENSOR11         PAin(0)

#define SENSOR12         PGin(6)
#define SENSOR13         PGin(7)
//*************************************Start_GPIO_define ***************
#define 	left_start_key    SENSOR1 //SENSOR12 //左键输入
#define 	right_start_key   SENSOR2 //SENSOR13 //右键输入
//********************************DDS*****************************************************
//PB0 FSYNC PC5 CLK  PC4 SDA
#define DDS_SPI_Nss  PBout(0)
#define DDS_SPI_Sck  PCout(5)
#define DDS_SPI_Mosi PCout(4)
//******************************motor*************************************************************
#define  PUL           PFout(9)
#define  DIR           PFout(10)

//***********************ARC班模拟开关控制信号*******************************************

#define ARC_A0   PGout(7)
#define ARC_A1   PGout(6)
#define ARC_A2   PGout(5)
#define ARC_A3   PGout(4)

#define ARC_Enable_COMA1   PEout(14)
#define ARC_Enable_COMB1   PEout(11)
#define ARC_Enable_COMC1   PEout(12)
#define ARC_Enable_COMD1   PEout(13)


#define ARC_B0   PGout(2)
#define ARC_B1   PDout(15)
#define ARC_B2   PDout(14)
#define ARC_B3   PDout(13)

#define ARC_Enable_COMA2   PGout(8)
#define ARC_Enable_COMB2   PGout(3)
#define ARC_Enable_COMC2   PDout(12)
#define ARC_Enable_COMD2   PBout(15)

#define ARC_C0   PDout(11)
#define ARC_C1   PDout(10)
#define ARC_C2   PDout(9)
#define ARC_C3   PDout(8)

#define ARC_D0   PBout(14)
#define ARC_D1   PBout(13)
#define ARC_D2   PBout(12)
#define ARC_D3   PEout(15)

//***********************************************************************//

void ALL_GPIO_CFG(void );

#endif 
