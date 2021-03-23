#include "global.h"
#include "sys.h"

/*********************************************************************************************
	* File Name     : GPIO_Clock_Enable
	* Description   : GPIO_Clock_Enable,Enbale SW+DP  disable JTAG
  * Input         : void
	* return        : void
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-Feb-2016
*********************************************************************************************/
void GPIO_Clock_Enable(){
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
   GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE); 
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); 
}
//GPIO_Define PD13,14,15
void GPIO_LCD_CFG(void)
{		
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE,&GPIO_InitStructure);
}

//IIC  PG2 SDA PG3  SCL
void GPIO_IIC_CFG(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_2|GPIO_Pin_3);	

}
//#define   SMALL_CAP_TEST_GATE_BIT_0           PFout(5)  //档位选择bit0  JP18 --10
//#define   SMALL_CAP_TEST_GATE_BIT_1           PFout(6)  //档位选择bit1  JP18 --9
//#define   SMALL_CAP_TEST_GATE_BIT_2           PFout(7)  //档位选择bit2  JP18 --8
//#define OUT_IO_1    PEout(6)
//#define OUT_IO_2    PCout(13)
//#define OUT_IO_3    PCout(14)
//#define OUT_IO_4    PCout(15)
//#define OUT_IO_5    PFout(0)
//#define OUT_IO_6    PFout(1)
//#define OUT_IO_7    PFout(2)
//#define OUT_IO_8    PFout(3)
//#define OUT_IO_9    PFout(4)
//#define OUT_IO_10   PFout(5)
//#define OUT_IO_11   PFout(6)
//#define OUT_IO_12   PFout(7)

//#define OUT_IO_13   PEout(4)
//#define OUT_IO_14   PEout(5)

//#define   SMALL_CAP_TEST_TYPE_SELECT_BIT_0    PFout(9) //元件类型选择bit0  JP18 --6
//#define   SMALL_CAP_TEST_TYPE_SELECT_BIT_1    PFout(8) //元件类型选择bit1  JP18 --7
void GPIO_Drive_CFG(){
		// TPIC6B595 PF15 - Sck,PF14-MOSI
		GPIO_InitTypeDef GPIO_InitStructure;	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4;
		GPIO_Init(GPIOD, &GPIO_InitStructure);	


		// RGB Light  PG-3.4.5
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
		GPIO_SetBits (GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	  //OUT
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_SetBits (GPIOC, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		GPIO_SetBits (GPIOE, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
		GPIO_Init(GPIOF, &GPIO_InitStructure);	
		GPIO_SetBits (GPIOF, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

/* Configure SPI2 pins: NSS, SCK, MISO and MOSI */
void GPIO_AD7190_CFG(){
	
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits (GPIOB,GPIO_Pin_13);
}

void GPIO_Sensor_CFG(){
	//PC 4,5 Gata Sensor 1-2 
	GPIO_InitTypeDef GPIO_InitStructure; 
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_0|\
															 GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}
//PE 11
void GPIO_Beep_CFG(){
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
//PB0 FSYNC PC5 CLK  PC4 SDA
void GPIO_DSS_CFG(){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/*********************************************************************************************
	* File Name     : GPIO_Analog_Switch_CFG
	* Description   : GPIO_Analog_Switch_CFG
  * Input         : void
	* return        : void
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-Feb-2016
*********************************************************************************************/
void GPIO_Analog_Switch_CFG(){
		//PB -12-15   4
		GPIO_InitTypeDef  GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		//PD -8-15 8
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|\
																GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;;
		GPIO_Init (GPIOD ,&GPIO_InitStructure );
		//PE-7-15	 5
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_Init (GPIOE ,&GPIO_InitStructure );
		//PG-2-8	 7
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
		GPIO_Init (GPIOG ,&GPIO_InitStructure );
		// Eanble A1-D1 = 0
		GPIO_ResetBits (GPIOE ,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14); 
		GPIO_ResetBits (GPIOD ,GPIO_Pin_12); //C
		GPIO_ResetBits (GPIOB ,GPIO_Pin_15); //D
		// Eanble A2-D2 = 0
		GPIO_ResetBits (GPIOG ,GPIO_Pin_3|GPIO_Pin_8); 

}

void GPIO_Motor_CFG(){
	//PA-0,1 
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	GPIO_ResetBits (GPIOF ,GPIO_Pin_9|GPIO_Pin_10); 
}
void GPIO_Voltage_Gain_CFG(){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

}
/*********************************************************************************************
	* File Name     : GPIO_Voltage_Source_CFG
	* Description   : cGPIO_Voltage_Source_CFG
  * Input         : void
	* return        : void
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-Feb-2016
*********************************************************************************************/
void GPIO_Voltage_Source_CFG(){
	GPIO_InitTypeDef  GPIO_InitStructure;
	//稳压管电源控制IO,电磁铁PF11,12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7 |GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOF,&GPIO_InitStructure);	
	GPIO_ResetBits (GPIOF ,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14 |GPIO_Pin_15 ); 
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
  GPIO_Init(GPIOG,&GPIO_InitStructure);
	
	GPIO_ResetBits (GPIOG ,GPIO_Pin_0|GPIO_Pin_1 );  //关闭音源供电
}
/*********************************************************************************************
	* File Name     : GPIO_AD7176_CFG
	* Description   : configration AD7176 interface GPIO
  * Input         : void
	* return        : void
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-Feb-2016
*********************************************************************************************/
void GPIO_AD7176_CFG(){	
	//PB- PB9 ADC-SYNC PE0-ADC_Nss PE1-ADC-Sck PE2 ADC-Out PE3-ADC-IN
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits (GPIOE ,GPIO_Pin_0|GPIO_Pin_1);
	GPIO_SetBits (GPIOB ,GPIO_Pin_5|GPIO_Pin_9);
}
/*********************************************************************************************
	* File Name     : GPIO_Magnet_PWR_CFG
	* Description   : 初始化电磁铁控制IO口
  * Input         : ,
	* return        : ,
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-Feb-2016
*********************************************************************************************/
void GPIO_Magnet_PWR_CFG(){
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
}

void GPIO_CAP_Test_CFG(){
	//PC5 -PC4-PA7
	GPIO_InitTypeDef GPIO_InitStructure; 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits (GPIOC ,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);

}
/*********************************************************************************************
	* File Name     : ALL_GPIO_CFG
	* Description   : 初始化各个硬件的IO口
  * Input         : ,
	* return        : ,
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void ALL_GPIO_CFG(){
		GPIO_Clock_Enable( ); 

		GPIO_Analog_Switch_CFG();
		GPIO_AD7176_CFG();


		GPIO_Motor_CFG();
	//	GPIO_Beep_CFG();
		GPIO_Sensor_CFG(); 
   GPIO_CAP_Test_CFG();	
		GPIO_LCD_CFG();		
		GPIO_IIC_CFG(); 
		GPIO_Drive_CFG();
//	GPIO_Magnet_PWR_CFG();
}
	
//  GPIO_Voltage_Source_CFG();
// 	GPIO_AD7190_CFG(); 
// 	GPIO_Voltage_Gain_CFG();
// 	GPIO_Analog_Relay_CFG();
//	GPIO_DSS_CFG();
