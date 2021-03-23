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
	
	Uplod_Software      Software;         // ��λ��
	Communication_Mode  Comm_Mode;        // ͨѶ��ʽ ,UART Or ETH        
	USART_TypeDef      *Comm_Uart;	      // ͨѶ���ں� ���� UART1-4 
	Fixture_UpDown_Type UpDown;           // ��ѹ��ʽ �ֶ� ���� ��� 3��  
	Mechanical_Struct   Mech_Struct;      //һ���OrС�ξ�	
	
	FunctionalState     Take_Product;     // ȡ�Ͽ����ܿ��� 
	FunctionalState     Sen_Trigger_Gas;  // ��դ������������� 
  FunctionalState     Block_Check;	    // ��λ���Ƿ�ƥ����ģ�ذ�  
	FunctionalState     Sample_Notice;    // ������ʾ 
	FunctionalState     Dot;	            // ���
  FunctionalState     USB_Move;
	uint8_t     Dot_Type;
	uint8_t     Scan_Way;            //ɨ�뷽ʽ ѹ��ǰ���Ǻ�  	
	uint8_t     PCS_Num;             //��Ѩ���Ѩ
	uint8_t     Mode;                //�ξߵ�ǰ����ģʽ 
  uint8_t     Status;              //�ξ�״̬ running or standby
	uint16_t    Gas_Keep_Time;       // ���������ʱ�� 
	uint16_t    Check_PIN_H;         // ģ��ƥ���λ 
	uint16_t    Check_PIN_L;         // ģ��ƥ���λ 
	uint32_t    Sample_Time;	       // ���������ʱ�� 
	uint16_t    Test_Wait;           // ����ǰ��ʱ 
	uint16_t    Cmd_Delay;           // ָ��ȴ�ʱ�� 
	uint16_t    Take_Product_Delay;  // ȡ�����������ʱ�� 
	
  uint16_t   Max_Point;
	
	MUX_Switch_Typedef Board ; 


}Base_Config_Typedef;



extern  Base_Config_Typedef Fixture;
void Init_Fixture(void);
uint8_t  Get_TEST_Station(void);
void   TEST_Station_Set(void );
uint8_t  UploadFixtureConfig(char *buf);
#endif

