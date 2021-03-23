#include "base_Config.h"
#include "timer.h"
#include "sample.h"
#include "reg.h"
#include "menu.h"
#include "eth_config.h"
#include "lcd3033.h"
#include "test.h"
#include "other.h"
#include "menu.h"
#include "other.h"
#include "lcd3033.h"
//#include "24cxx.h"
#include "delay.h"
#include "os.h"
#include "usmart.h"
#include "sup_fun.h"
#include "barcode.h"
#include "usart.h"
#include "other.h"
#include <string.h>
#include "Y_axis.h"
#include "X_axis.h"
#include "pF.h"
#include "cmd.h"
#include "os_study.h"
#include "reg.h"
#include "list_test.h"
#include "eth_config.h"
#include "base_Config.h"
#include "sample.h"
#include "dot.h"
#include "debug.h"
#include "reg.h"
#include "test_config.h"
#include "id.h"
#include "usb_move.h"
Base_Config_Typedef Fixture;
const char  Updown_Name[][16] = {
	{ "�ֶ���ѹ"},
	{ "������ѹ"},	
	{ "�����ѹ"},
};
const char  Software_Name[][16] = {
	{ "JDT"},
	{ "WTB"},	
	{ "ZDT"},
};
const char  Switch_Board_Name[3][16] = {
	{ "���ذ�(��)      "},
	{ "���ذ�(ģ�⿪��)"},	
//	{ "���ذ�(�̵��)"  },
};
const char  Scan_Mode_Name[][16] = 
{
			{	"����ģʽ"     },
			{	"������/������"},
			{	"�ֶ�ɨ��"     },
			{	"ɨ��ǹ"       },
			{	"�������"     }
};

/*****************************************************************
	* File Name     : Init_Fixture                      
	* Description   : Init_Fixture                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 27-April-2020                             
*****************************************************************/ 
uint8_t  UploadFixtureConfig(char *buf){
	
  //С�ξ߻�һ���	
	Uart_printf (Fixture.Comm_Uart ,"\r\n");
	Uart_printf (Fixture.Comm_Uart ,"�ξ�����  :%s\r\n",Fixture.Mech_Struct  == SmallFixture ?"С�ξ�":"һ���");
	Uart_printf (Fixture.Comm_Uart ,"��ѹ��ʽ  :%s\r\n",Updown_Name[(uint8_t)Fixture.UpDown]);
	Uart_printf (Fixture.Comm_Uart ,"��Ƭ����  :%d\r\n",Fixture.PCS_Num);	
	Uart_printf (Fixture.Comm_Uart ,"���ذ�����:%s\r\n",Switch_Board_Name[Fixture.Board]);	
	Uart_printf (Fixture.Comm_Uart ,"������  :%d\r\n",Fixture.Max_Point);
	Uart_printf (Fixture.Comm_Uart ,"ͨѶ��ʽ  :");	
	if(Fixture.Comm_Mode  == __USART){
	Uart_printf (Fixture.Comm_Uart ,"����\r\n");	
	}else{
	Uart_printf (Fixture.Comm_Uart ,"����:\r\n             IP:%d.%d.%d.%d \r\n",NET_ETH.ipaddr.Num[0],NET_ETH.ipaddr.Num[1],NET_ETH.ipaddr.Num[2],NET_ETH.ipaddr.Num[3]);	
	Uart_printf (Fixture.Comm_Uart ,"             NetMask:%d.%d.%d.%d \r\n",NET_ETH.netmask.Num[0],NET_ETH.netmask.Num[1],NET_ETH.netmask.Num[2],NET_ETH.netmask.Num[3]);	
  Uart_printf (Fixture.Comm_Uart ,"             GATEWAY:%d.%d.%d.%d \r\n",NET_ETH.GATEWAY.Num[0],NET_ETH.GATEWAY.Num[1],NET_ETH.GATEWAY.Num[2],NET_ETH.GATEWAY.Num[3]);	
	}
	Uart_printf (Fixture.Comm_Uart ,"��λ��    :%s\r\n",Software_Name[(uint8_t)Fixture.Software]);
	if(Fixture.Block_Check  == ENABLE ){
	Uart_printf (Fixture.Comm_Uart ,"��ģƥ��  :���� H=%d,L=%d\r\n",Fixture.Check_PIN_H,Fixture.Check_PIN_L);
	}
	Uart_printf (Fixture.Comm_Uart ,"����ǰ��ʱ:%g ms\r\n",Reg[Test_Delay].Value);
	Uart_printf (Fixture.Comm_Uart ,"ɨ��ʱ��  :%s\r\n",Fixture.Scan_Way ==Push_Next ?"��ѹ֮��":"��ѹ֮ǰ");	

	if(Scan.Mode == Normal ){
	Uart_printf (Fixture.Comm_Uart ,"ɨ������  :%s %dbps %d ms\r\n",
		                                         Scan.Barcode_Reader_Type == Infoscan? "�Ͼ�����":"����ʿ",
		                                         Scan.Barcode_Reader_Baud	,Scan.Time);		
	}else{
	Uart_printf (Fixture.Comm_Uart ,"ɨ������  :%s\r\n",Scan_Mode_Name[Scan.Mode]);	
	}
	
	if(	Fixture.Sen_Trigger_Gas  == ENABLE )
	Uart_printf (Fixture.Comm_Uart ,"��դ������:����,���� %d ms\r\n",Fixture.Gas_Keep_Time);			
	if(Fixture.Take_Product == ENABLE)//  ;  // �����Ƿ���
	Uart_printf (Fixture.Comm_Uart ,"����      :����,�������ʱ %d ms\r\n",Fixture.Take_Product_Delay);	

			
	if(	Fixture.Dot == ENABLE){// ;        // ����Ƿ���RESET
	Uart_printf (Fixture.Comm_Uart ,"���      :����; ���ʼ��:%s  %g/%g \r\n",Reg[Dot_CNT_Enable].Value == ENABLE?"����":"�ر�",Reg[Dot_Pen_CNT].Value ,Reg[Dot_Pen_MAX].Value);	
	}
	if(Fixture.Sample_Notice == ENABLE)	
	Uart_printf (Fixture.Comm_Uart ,"������ʾ  :����, ����:%g����;��ǰʱ��: %02d:%02d:%02d    \r\n",Reg[Sample_Cycle].Value ,(Fixture.Sample_Time/60/60)%60,
																										                                                                   (Fixture.Sample_Time/60)%60   ,
																										                                                                   (Fixture.Sample_Time%60));	
	Uart_printf (Fixture.Comm_Uart ,"ָ��ȴ�  : %d ms\r\n",Fixture.Cmd_Delay);	

	Uart_printf (Fixture.Comm_Uart ,"\r\n");

	return  True ;
}
/*****************************************************************
	* File Name     : Init_Fixture                      
	* Description   : Init_Fixture                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
void Init_Fixture(void){
	uint8_t i = 0;
	uint16_t buf[32];
	
	uint16_t pF_Num = Get_Currennt_Type_CNT(Type_pF_Cap,buf,32 );
	uint16_t ID_Num = Get_Currennt_Type_CNT(Type_IC_ID,buf,32 );
	Fixture.Mech_Struct  = SmallFixture    ;  //С�ξ߻�һ���	
	Fixture.UpDown       = Valve;             //��ѹ��ʽ
	Fixture.PCS_Num      = 1;                // �Ƿ�Ϊ��Ƭ����
	Fixture.Board        = Switch_Board   ;
	Fixture.Max_Point    = 128;

	Fixture.Comm_Mode    = __USART ;          // ͨѶ��ʽ�����ڻ�����
	Fixture.Comm_Uart    = USART1 ;          // ͨѶ����
	Fixture.Software     = WTB_Software;     // ��λ��ѡ��

	Fixture.Block_Check  = DISABLE ;         // �Ƿ�ƥ��ģ����
	Fixture.Check_PIN_H  = 9 ;               // ģ����ߵ�
	Fixture.Check_PIN_L  = 10;               // ģ����͵�

	Fixture.Test_Wait    = Reg[Test_Delay].Value;               //����ǰ��ʱ
	Fixture.Scan_Way     = Reg[ScanAndPush].Value ;        // ɨ�跽ʽ ����ѹ֮ǰ��֮��	
	
	Fixture.Sen_Trigger_Gas  = DISABLE  ;     // ��դ�Ƿ񴥷���λ�����
	Fixture.Gas_Keep_Time    = 30000;        // ��λ���������ʱ��ms	
		
	Fixture.Take_Product       = DISABLE  ;  // �����Ƿ���
	Fixture.Take_Product_Delay = 500;        // ������ʱ
			
	Fixture.Dot            = DISABLE  ;        // ����Ƿ���RESET
	Fixture.Dot_Type       = __byValve ;
	
	Fixture.Sample_Notice  = DISABLE     ;	


	Fixture.Cmd_Delay  = Reg[Cmd_Delay].Value ;
	Fixture.Status = 1;
	Fixture.Mode   = 0;       // ��ǰ����ģʽ
	Fixture.Sample_Time = 0;  //��������

  Fixture.USB_Move = DISABLE  ;


	if(Reg[Sample_Enable].Value  == ENABLE ){
		Init_Smaple_Test_Notice();
	}

	for( i = 0; _Test_Mode[i].Name ; i ++){
			if(_Test_Mode[i].fun == Up_Down_EACT_set &&Fixture.UpDown != ACT_Controller ){
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			if(_Test_Mode[i].fun == Take_Product_EACT_set &&Fixture.Take_Product== DISABLE){
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			if(_Test_Mode[i].fun == Dot_Set && Fixture.Dot == DISABLE  ){
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			if(_Test_Mode[i].fun == Smaple_Notice_Set && Fixture.Sample_Notice == DISABLE){
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			if(_Test_Mode[i].fun == Scan_Set && Fixture.Mech_Struct == AutoFixture ){
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			if(_Test_Mode[i].fun == pF_Capacitor_Calibration_Fun &&pF_Num == 0 ){				
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			if(_Test_Mode[i].fun == Read_IC_ID_Debug && ID_Num == 0 ){				
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}			
			if(_Test_Mode[i].fun == USB_Move_Set && Fixture.USB_Move == DISABLE ){				
				_Test_Mode[i].En_bit = DISABLE ;
				continue ;
			}
			
	}
}


/*********************************************************************************************
	* File Name     :TEST_Station_Set
	* Description   :���Թ�λ����
  * Input         :��
  * return        :��
	* Author        :Morton
	* Date          :2018/3/20
	* ��  �ģ� /
*********************************************************************************************/
void  TEST_Station_Set(void ){
	  uint8_t TEST_Station = Reg[FixtureNumber].Value -1;
		char Menu[4][17]={ "    ��λ-1      ",
											 "    ��λ-2      ",
										   "    ��λ-3      ",
										   "    ��λ-4      "
									};
		
		Choice_Menu("���Թ�λ����:   ",Menu,4,&TEST_Station);
		TEST_Station ++;
		Reg[FixtureNumber].Value = 		TEST_Station;					
		Save_Single_Reg_Value(FixtureNumber);							
		if(Fixture.Comm_Mode == __ETH ){							
			if(Config_ETH_IP(TEST_Station)==False){
				cyc4or3run ();
				lcd_printf ("����ģ������NG");
				step_test_mode_get_key ();
			}
		}
		RevertStartupScreen ();
}

/*****************************************************************
	* File Name     : Read_Reg_data                      
	* Description   : Read_Reg_data                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
uint8_t Get_TEST_Station(void){
	
	return Read_Signal_Reg_Value(FixtureNumber);//].Value;
}

