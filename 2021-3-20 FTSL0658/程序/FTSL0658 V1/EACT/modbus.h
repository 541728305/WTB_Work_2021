#ifndef __MODBUS_H_
#define __MODBUS_H_

#include "sys.h"

//????
#define X40_OUT0     0x0040
#define X41_OUT1     0x0041
#define X42_OUT2     0x0042
#define X43_OUT3     0x0043
#define X44_OUT4     0x0044
#define X45_OUT5     0x0045
//**0x46-0x47
#define X48_BUSY     0x0048
#define X49_SVRE     0x0049
#define X4A_SETON    0x004A
#define X4B_INP      0x004B
#define X4C_AREA     0x004C
#define X4D_WAREA    0x004D
#define X4E_ESTOP    0x004E
#define X4F_ALARM    0x004F
//????
#define Y10_IN0      0x0010
#define Y11_IN1      0x0011
#define Y12_IN2      0x0012
#define Y13_IN3      0x0013
#define Y14_IN4      0x0014
#define Y15_IN5      0x0015
// Y16-Y17
#define Y18_HOLD     0x0018
#define Y19_SVON     0x0019
#define Y1A_DRIVE    0x001A
#define Y1B_RESET    0x001B
#define Y1C_SETUP    0x001C
//Y1D-1F
//Y30
#define Y30_Serial_EN  0x30
//???
#define		Absolute_Coordinate  0x0001
#define		Relative_Coordinate  0x0002

//#define Safe_Grating_Sensor  SensorIO8
 

#define LEC_Serial_Port       USART2	
#define Debug_Serial_Port     USART1
#define ReadCoils_Code       	0x01
#define ReadInputReg_Code    	0x02
#define ReadHoldingReg_Code  	0x03
#define WriteSingleCoil_Code 	0x05
#define WriteHoldingReg_Code 	0x10
#define READ_WAIT             80


#pragma pack (1) 
typedef struct  {
	uint8_t  ID ;
	uint8_t  Function_code;
	uint16_t Begin_Addr;
	uint16_t Num;	
}LEC_Frame;


typedef struct  {
	uint16_t  MOVE_Type ; //D9102
	uint16_t  Speed;      //D9103
	uint32_t  Positon;    //D9104
	uint16_t  ACC;        //D9106
	uint16_t  EDC;        //D9107
	uint16_t  Push_Force; //D9108
	uint16_t  Threshold;  //D9109
	uint16_t  Push_Speed; //D910A
	uint16_t  MAX_Force;  //D910B
	uint32_t  AREA_1;     //D910C
	uint32_t  AREA_2;     //D910E
	uint32_t  Range;
}LEC_Run_Parameter;
#pragma pack () 


typedef enum{
	OFF,  //保护关闭
	HOLD, //暂停
	RETURN, //原路返回
	PWR_OFF //掉电
}ACT_Protect_Mode;



typedef struct  {
	char     *Name;
	uint8_t  ID;                 //轴名称
	int      Orig_Direction;           //正方向, 远点在电机侧 1 远离电机侧为 -1
	double Stroke;
	uint16_t Max_Speed;
	uint16_t Run_Speed;
	double   Previous_Coordinate; //当前坐标
	double   Positional_Range;    //定位精度
	double   Protect_Range_USL;
	double   Protect_Range_LSL;
	ACT_Protect_Mode  Protect_Mode;
}Act_typedef;



//0x0400-0x07FF (NO.0-63) 32*64= 2048
//   D0400-1********D0401-2****D0402-4
// Absolute/Relative+Speed+Position
// Status data    D9000-4 = Current postion
//                D9004-4 = running postin 

typedef enum{
		LEC_Normal = 0,
		OverTime,
		Frame_Error,
		CRC_Error
}LEC_Status;
uint16_t  Convert_Big(uint16_t x) ;
uint32_t  Half_Convert_Big_uint32_t(uint32_t x);
uint8_t Get_LEC_Current_Postion(uint8_t id, double *postion);
uint8_t Read_InputStatus( uint8_t id, uint8_t SIGNALE);
uint8_t Running_Position(Act_typedef Act, uint16_t Type, double Coordinate ,uint16_t  speed,uint8_t );
LEC_Status FReadCoils(uint8_t id,uint16_t Addr ,uint8_t Read_Num,uint8_t *Read_buf);
LEC_Status FWriteSingleCoil(uint8_t id,uint16_t Addr ,uint8_t Status);
LEC_Status FReadInputStatusReg(uint8_t id,uint16_t Addr ,uint16_t Read_Num,uint8_t *Read_buf);
LEC_Status FWriteHoldingReg(uint8_t id,uint16_t Addr ,uint16_t Length,uint16_t *Write_data);
LEC_Status FReadHoldingReg(uint8_t id,uint16_t Addr ,uint16_t Read_Num,uint16_t *Read_buf);


uint8_t Axis_Running_Position(Act_typedef X_Act, uint16_t X_Type, double X_postion ,uint16_t  X_speed,
															Act_typedef Y_Act, uint16_t Y_Type, double Y_postion ,uint16_t  Y_speed);
#endif

