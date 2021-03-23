#ifndef __REG_H___
#define __REG_H___


#define U8_Type      1
#define Char_Type    1
#define U16_Type     2
#define U32_Type     4
#define Float_Type   4
#define Double_Type  8


#include "sys.h"

typedef  struct {
		uint8_t     Num; //编号
		char       *Name; // 数据名称
		uint16_t    Addr   ; //EEPROM存储地址
		uint8_t     Byte_Length ; // 数据长度,字节数
		double      Step_Length;

		double      USL;  //上限
		double      LSL;  //下限
		double      Value ;//当下数据
		double      default_Value; //默认值
}Parameter_Typedef;


typedef  enum  {
		Fixture_Name = 0,
		FixtureNumber,    //1
		Block_Check,      //2
		Total_Num,        //3
		PASS_Num,         //4   
	
	  Dot_Enable,       //5
		Dot_CNT_Enable,   //6
		Dot_Keep_Time,    //7
		Dot_Pen_CNT,      //8
		Dot_Pen_MAX,	    //9
	
		Sample_Enable,    //10
		Sample_Cycle,     //11
	
		Cmd_Delay,        //12
		Test_Delay,       //13
	
		ScanAndPush,      //14
		ScanTime,         //15
		ScanMode,         //16
		BarcodeReader,    //17
		BarcodeReaderBPS,	//18	
		BarcodeCheckEnable,		//19
		BarcodeLength,        //20
		BarcodeFormat,        //21
		
		ETH_Mode,         //22
		ETH_IP,           //23
		ETH_IP_2,         //24
		ETH_IP_3,         //25
		ETH_IP_4,         //26 
		ETH_Netmask,      //27
		ETH_Netmask_2,    //28
		ETH_Netmask_3,    //29
		ETH_Netmask_4,		//30
		ETH_GATEWAY,      //31
		ETH_GATEWAY_2,    //32
		ETH_GATEWAY_3,    //33
		ETH_GATEWAY_4,    //34
		
		ETH_PortNum,      //35
	
		pF_Offset,        //36
		pF_Offset_2,      //37
		pF_Offset_3,	    //38
		pF_Offset_4,	    //39
		pF_Offset_5,	    //40
		pF_Offset_6,	    //41
		pF_Offset_7,	    //42
		pF_Offset_8,			//43
//		Dot_Motor_Enable,
		Dot_Motor_Speed_SET,
		Dot_Motor_Speed_RESET,
		Dot_Motor_Standbypos,
		Dot_Motor_Dotpos,
		Dot_Motor_Uppos
}Reg_Set_Typedef;


extern  Parameter_Typedef  Reg[];

void  Reset_All_Reg_Value(void);
void  Read_All_Reg_Value( uint8_t );

double  Read_Signal_Reg_Value(uint8_t Num );
void    Save_Single_Reg_Value(uint8_t Num );


void Write_pF_Capacitor_offset(void);
u8  clear_counter(void );

unsigned char System_Parameter_Set(void);
#endif





