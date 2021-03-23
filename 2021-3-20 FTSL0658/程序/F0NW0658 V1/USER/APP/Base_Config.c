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
	{ "手动下压"},
	{ "气缸下压"},	
	{ "电缸下压"},
};
const char  Software_Name[][16] = {
	{ "JDT"},
	{ "WTB"},	
	{ "ZDT"},
};
const char  Switch_Board_Name[3][16] = {
	{ "开关板(无)      "},
	{ "开关板(模拟开关)"},	
//	{ "开关板(继电板)"  },
};
const char  Scan_Mode_Name[][16] = 
{
			{	"单机模式"     },
			{	"无条码/假条码"},
			{	"手动扫码"     },
			{	"扫描枪"       },
			{	"相机解码"     }
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
	
  //小治具或一体机	
	Uart_printf (Fixture.Comm_Uart ,"\r\n");
	Uart_printf (Fixture.Comm_Uart ,"治具类型  :%s\r\n",Fixture.Mech_Struct  == SmallFixture ?"小治具":"一体机");
	Uart_printf (Fixture.Comm_Uart ,"下压方式  :%s\r\n",Updown_Name[(uint8_t)Fixture.UpDown]);
	Uart_printf (Fixture.Comm_Uart ,"连片测试  :%d\r\n",Fixture.PCS_Num);	
	Uart_printf (Fixture.Comm_Uart ,"开关板配置:%s\r\n",Switch_Board_Name[Fixture.Board]);	
	Uart_printf (Fixture.Comm_Uart ,"最大点数  :%d\r\n",Fixture.Max_Point);
	Uart_printf (Fixture.Comm_Uart ,"通讯方式  :");	
	if(Fixture.Comm_Mode  == __USART){
	Uart_printf (Fixture.Comm_Uart ,"串口\r\n");	
	}else{
	Uart_printf (Fixture.Comm_Uart ,"网口:\r\n             IP:%d.%d.%d.%d \r\n",NET_ETH.ipaddr.Num[0],NET_ETH.ipaddr.Num[1],NET_ETH.ipaddr.Num[2],NET_ETH.ipaddr.Num[3]);	
	Uart_printf (Fixture.Comm_Uart ,"             NetMask:%d.%d.%d.%d \r\n",NET_ETH.netmask.Num[0],NET_ETH.netmask.Num[1],NET_ETH.netmask.Num[2],NET_ETH.netmask.Num[3]);	
  Uart_printf (Fixture.Comm_Uart ,"             GATEWAY:%d.%d.%d.%d \r\n",NET_ETH.GATEWAY.Num[0],NET_ETH.GATEWAY.Num[1],NET_ETH.GATEWAY.Num[2],NET_ETH.GATEWAY.Num[3]);	
	}
	Uart_printf (Fixture.Comm_Uart ,"上位机    :%s\r\n",Software_Name[(uint8_t)Fixture.Software]);
	if(Fixture.Block_Check  == ENABLE ){
	Uart_printf (Fixture.Comm_Uart ,"针模匹配  :开启 H=%d,L=%d\r\n",Fixture.Check_PIN_H,Fixture.Check_PIN_L);
	}
	Uart_printf (Fixture.Comm_Uart ,"测试前延时:%g ms\r\n",Reg[Test_Delay].Value);
	Uart_printf (Fixture.Comm_Uart ,"扫描时机  :%s\r\n",Fixture.Scan_Way ==Push_Next ?"下压之后":"下压之前");	

	if(Scan.Mode == Normal ){
	Uart_printf (Fixture.Comm_Uart ,"扫描配置  :%s %dbps %d ms\r\n",
		                                         Scan.Barcode_Reader_Type == Infoscan? "南京比邻":"基恩士",
		                                         Scan.Barcode_Reader_Baud	,Scan.Time);		
	}else{
	Uart_printf (Fixture.Comm_Uart ,"扫描配置  :%s\r\n",Scan_Mode_Name[Scan.Mode]);	
	}
	
	if(	Fixture.Sen_Trigger_Gas  == ENABLE )
	Uart_printf (Fixture.Comm_Uart ,"光栅触发气:开启,保持 %d ms\r\n",Fixture.Gas_Keep_Time);			
	if(Fixture.Take_Product == ENABLE)//  ;  // 脱料是否开启
	Uart_printf (Fixture.Comm_Uart ,"脱料      :开启,吸真空延时 %d ms\r\n",Fixture.Take_Product_Delay);	

			
	if(	Fixture.Dot == ENABLE){// ;        // 打点是否开启RESET
	Uart_printf (Fixture.Comm_Uart ,"打点      :开启; 打点笔监控:%s  %g/%g \r\n",Reg[Dot_CNT_Enable].Value == ENABLE?"开启":"关闭",Reg[Dot_Pen_CNT].Value ,Reg[Dot_Pen_MAX].Value);	
	}
	if(Fixture.Sample_Notice == ENABLE)	
	Uart_printf (Fixture.Comm_Uart ,"样本提示  :开启, 周期:%g分钟;当前时间: %02d:%02d:%02d    \r\n",Reg[Sample_Cycle].Value ,(Fixture.Sample_Time/60/60)%60,
																										                                                                   (Fixture.Sample_Time/60)%60   ,
																										                                                                   (Fixture.Sample_Time%60));	
	Uart_printf (Fixture.Comm_Uart ,"指令等待  : %d ms\r\n",Fixture.Cmd_Delay);	

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
	Fixture.Mech_Struct  = SmallFixture    ;  //小治具或一体机	
	Fixture.UpDown       = Valve;             //下压方式
	Fixture.PCS_Num      = 1;                // 是否为连片测试
	Fixture.Board        = Switch_Board   ;
	Fixture.Max_Point    = 128;

	Fixture.Comm_Mode    = __USART ;          // 通讯方式，串口或网口
	Fixture.Comm_Uart    = USART1 ;          // 通讯串口
	Fixture.Software     = WTB_Software;     // 上位机选择

	Fixture.Block_Check  = DISABLE ;         // 是否匹配模块编号
	Fixture.Check_PIN_H  = 9 ;               // 模块检测高点
	Fixture.Check_PIN_L  = 10;               // 模块检测低点

	Fixture.Test_Wait    = Reg[Test_Delay].Value;               //测试前延时
	Fixture.Scan_Way     = Reg[ScanAndPush].Value ;        // 扫描方式 ，下压之前或之后	
	
	Fixture.Sen_Trigger_Gas  = DISABLE  ;     // 光栅是否触发定位真空吸
	Fixture.Gas_Keep_Time    = 30000;        // 定位真空吸保持时间ms	
		
	Fixture.Take_Product       = DISABLE  ;  // 脱料是否开启
	Fixture.Take_Product_Delay = 500;        // 脱料延时
			
	Fixture.Dot            = DISABLE  ;        // 打点是否开启RESET
	Fixture.Dot_Type       = __byValve ;
	
	Fixture.Sample_Notice  = DISABLE     ;	


	Fixture.Cmd_Delay  = Reg[Cmd_Delay].Value ;
	Fixture.Status = 1;
	Fixture.Mode   = 0;       // 当前运行模式
	Fixture.Sample_Time = 0;  //样本计数

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
	* Description   :测试工位设置
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2018/3/20
	* 修  改： /
*********************************************************************************************/
void  TEST_Station_Set(void ){
	  uint8_t TEST_Station = Reg[FixtureNumber].Value -1;
		char Menu[4][17]={ "    工位-1      ",
											 "    工位-2      ",
										   "    工位-3      ",
										   "    工位-4      "
									};
		
		Choice_Menu("测试工位设置:   ",Menu,4,&TEST_Station);
		TEST_Station ++;
		Reg[FixtureNumber].Value = 		TEST_Station;					
		Save_Single_Reg_Value(FixtureNumber);							
		if(Fixture.Comm_Mode == __ETH ){							
			if(Config_ETH_IP(TEST_Station)==False){
				cyc4or3run ();
				lcd_printf ("网口模块配置NG");
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

