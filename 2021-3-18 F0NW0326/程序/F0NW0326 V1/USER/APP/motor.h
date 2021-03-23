#ifndef __SMC_LEC_H_
#define __SMC_LEC_H_
#include "sys.h"


 




#define Motor_PUL_Port  GPIOF
#define Motor_PUL_Pin   GPIO_Pin_10  

#define Motor_DIR_Pin   GPIO_Pin_9  
#define Motor_DIR_Port  GPIOF


#define Motor_PUL   PFout(10)
#define Motor_DIR   PFout(9)

typedef enum {
		Absolute = 0,
		Relative = 1
}Coordinate_Type ;


typedef enum {

		Motor_Sensor_RESET = 0, 		
	Motor_Sensor_SET=1
}Motor_Sensor_StatusTypedef ;


typedef enum {
		Standby = 0,
		Runing,
		Suspended,
		End,
		Error,
		Default_Status
}Motor_Status;


typedef  struct {
		//系统参数
						 uint8_t  Axis_Name ;
		volatile float    Stroke ; //电缸行程 
		volatile double   Absolute_Coordinate; //绝对坐标(相对于远点),运行之前计算一次,防止超出
		volatile float    Screw_Pitch ; //螺距
		volatile uint8_t  Microstep ;//细分设置,默认800 PUL/R  360/1.8 = 200 ;相当于细分 = 4
		volatile uint8_t  Direction ;//运行正方向
	  //用户参数

		volatile uint8_t  Forward_Direction ;//运行正方向
	
		volatile double  Start_Frequency; //      				 500  // 500Hz
		volatile double  Max_Run_Frequency; //    				 10000 //10KHz
		volatile double  Accelerate_Pulse_CNT;
		volatile uint8_t  Enable;

		volatile double   Standby_Position;
		volatile double   Product_Position;
	
		volatile uint16_t  Pulse; 
		volatile uint16_t  Speed ;//集电极开路60KPPS 差动200KPPS 60KPPS  = 60 Pulse per ms    16.667us/pulse 最小脉冲宽度8.333us 取整数 >= 10us
		volatile uint8_t   Status; //运行状态 0,待机状态,1,运行中 2,运行结束
		volatile uint8_t   err;  //出错标志位
		volatile uint16_t  TimerCount;//超时设置
		void (*Initialization_Fun)();//初始化函数
		void (*Limit_Set_Fun)( FunctionalState );//初始化函数		
		uint8_t Display_Coordinate_Value;
}Motor_Par_Typedef;//,SMC_LECPAN;





extern  Motor_Par_Typedef Motor;



void Initialize_Motor(void);
uint8_t Dot_Move( uint8_t pos);

void Set_Motor_Debug_SETUP_Flag(FunctionalState st);

void Motor_Dot_Enable_Set(void);
void Motor_Dot_Speed_Set(void);
void Motor_RESET_Speed_Set(void);
void Motor_Dot_Pos_Set(void);
void Motor_Standby_Pos_Set(void);
void Motor_Up_Pos_Set(void);
void Motor_Dot_Speed_Set(void);
void Motor_RESET_Speed_Set(void);
void GPIO_Initialize_Motor(void);
uint8_t Motor_Setup( uint32_t ,uint8_t);
void Motor_Speed_Set(char *Name, uint16_t reg_Num,char *Unit);
void Motor_Pos_Set( char *Name, uint16_t sNum);
#endif 
