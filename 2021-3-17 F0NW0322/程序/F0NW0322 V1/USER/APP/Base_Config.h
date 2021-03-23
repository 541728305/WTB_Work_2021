#ifndef __BASE_CONFIG_H_
#define __BASE_CONFIG_H_

#include "sys.h"



typedef enum {
	None = 0,
	Valve,
	ACT_Controller,	
}Fixture_UpDown_Type ;

typedef enum 
{
	JDT_Software = 0,
	WTB_Software ,
	ZDT_Software,

}Uplod_Software;

typedef enum 
{
	SmallFixture = 0,
	AutoFixture
}Mechanical_Struct;
	
typedef enum 
{
	__USART = 0,
	__ETH
}Communication_Mode;

typedef enum 
{
	__byValve = 0,
	__byMotor
}Dot_Typedef;


typedef enum 
{
	Push_Previous = 0,
	Push_Next
}Scan_Way_Typedef;

typedef enum {
	Main_Board = 0,
	Switch_Board,
	Relay_Board
}MUX_Switch_Typedef ;


typedef  struct {
	
	Uplod_Software      Software;         // 上位机
	Communication_Mode  Comm_Mode;        // 通讯方式 ,UART Or ETH        
	USART_TypeDef      *Comm_Uart;	      // 通讯串口号 配置 UART1-4 
	Fixture_UpDown_Type UpDown;           // 下压方式 手动 气缸 电缸 3种  
	Mechanical_Struct   Mech_Struct;      //一体机Or小治具	
	
	FunctionalState     Take_Product;     // 取料开启总开关 
	FunctionalState     Sen_Trigger_Gas;  // 光栅触发真空吸配置 
  FunctionalState     Block_Check;	    // 工位号是否匹配针模载板  
	FunctionalState     Sample_Notice;    // 样本提示 
	FunctionalState     Dot;	            // 打点
  FunctionalState     USB_Move;
	uint8_t     Dot_Type;
	uint8_t     Scan_Way;            //扫码方式 压合前还是后  	
	uint8_t     PCS_Num;             //单穴或多穴
	uint8_t     Mode;                //治具当前运行模式 
  uint8_t     Status;              //治具状态 running or standby
	uint16_t    Gas_Keep_Time;       // 真空吸保持时间 
	uint16_t    Check_PIN_H;         // 模块匹配点位 
	uint16_t    Check_PIN_L;         // 模块匹配点位 
	uint32_t    Sample_Time;	       // 距离测样本时间 
	uint16_t    Test_Wait;           // 测试前延时 
	uint16_t    Cmd_Delay;           // 指令等待时间 
	uint16_t    Take_Product_Delay;  // 取料真空吸保持时间 
	
  uint16_t   Max_Point;
	
	MUX_Switch_Typedef Board ; 


}Base_Config_Typedef;



extern  Base_Config_Typedef Fixture;
void Init_Fixture(void);
uint8_t  Get_TEST_Station(void);
void   TEST_Station_Set(void );
uint8_t  UploadFixtureConfig(char *buf);
#endif

