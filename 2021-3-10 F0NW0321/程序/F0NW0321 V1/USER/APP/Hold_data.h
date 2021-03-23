#ifndef _HOLD_DATA_H_
#define _HOLD_DATA_H_
#include "sys.h"

typedef enum {
	ACT_UP_DOWN_EN = 0,     //   0
	ACT_UP_DOWN_SPEED,      //   1
	ACT_Up,                 //   2 
	ACT_Down,               //   3 
	ACT_Up1,                //   4 
	ACT_Down1,              //   5 
	ACT_Take_Product_EN,    //   6 
	ACT_NG_EN,              //   7 
	ACT_Push_Procuct,       //   7 	
	ACT_OK_NUM,             //   8 
	ACT_NG_NUM,             //   9 
	ACT_Speed,              //  10 
	ACT_Source,             //  11 
	ACT_Standby ,           //  12 
	ACT_NG1,                //  13 
	ACT_NG2,                //  14 
	ACT_NG3,                //  15 
	ACT_NG4,                //  16 
	ACT_OK1,                //  17 
	ACT_OK2,                //  18 
	ACT_OK3,                //  19 
	ACT_OK4,                //  20 
	ACT_OK5,                //  21 
	ACT_OK6,                //  22 
	ACT_OK7,                //  23 
	ACT_OK8,                //  24 
}ACT_Enum_Typedef ;

//#define ACT_UP_DOWN_EN                0
//#define ACT_UP_DOWN_SPEED             1
//#define ACT_Up                        2  
//#define ACT_Down                      3  
//#define ACT_Up1                       4  
//#define ACT_Down1                     5  
//#define ACT_Take_Product_EN           6  
//#define ACT_NG_EN                     7  
//#define ACT_OK_NUM                    8  
//#define ACT_NG_NUM                    9  
//#define ACT_Speed                    10  
//#define ACT_Source                   11  
//#define ACT_Standby                  12  
//#define ACT_NG1                      13  
//#define ACT_NG2                      14  
//#define ACT_NG3                      15  
//#define ACT_NG4                      16  
//#define ACT_OK1                      17  
//#define ACT_OK2                      18  
//#define ACT_OK3                      19  
//#define ACT_OK4                      20  
//#define ACT_OK5                      21  
//#define ACT_OK6                      22  
//#define ACT_OK7                      23  
//#define ACT_OK8                      24 





//typedef enum {
// ACT_UP_DOWN_EN = 0, 
//	ACT_UP_DOWN_SPEED , 
//	ACT_Up  , 
//	ACT_Down , 
//	ACT_Up1  , 
//	ACT_Down1 , 
//	ACT_Take_Product_EN , 
//	ACT_NG_EN , 
//	ACT_OK_NUM, 
//	ACT_NG_NUM, 
//	ACT_Speed , 
//	ACT_Source, 
//	ACT_Standby, 
//	ACT_NG1, 
//	ACT_NG2, 
//	ACT_NG3, 
//	ACT_NG4, 
//	ACT_OK1, 
//	ACT_OK2, 
//	ACT_OK3, 
//	ACT_OK4, 
//	ACT_OK5, 
//	ACT_OK6, 
//	ACT_OK7, 
//	ACT_OK8
//}ACT_Set_Typedef;


typedef  struct {
		uint8_t     Num; //编号
		char       *Name; // 数据名称
		uint16_t    Addr   ; //EEPROM存储地址
		double      Step_Length;
		uint8_t     Byte_Length ; // 数据长度,字节数
		double      USL;  //上限
		double      LSL;  //下限
		double      data ;//当下数据
		uint16_t    default_Value; //默认值
}ACT_Parameter_Def;



extern ACT_Parameter_Def ACT_Parameter[];



void  Write_double_data( uint16_t Addr ,double dat );
double read_double_data( uint16_t Addr );
void Read_Hold_Reg_data( void);
void Save_Hold_Reg_data(uint8_t Num );
uint8_t Get_Take_OFF_Enable_bit(uint8_t Result);
uint8_t Get_PASS_Row_Num(uint8_t Result);
#endif


