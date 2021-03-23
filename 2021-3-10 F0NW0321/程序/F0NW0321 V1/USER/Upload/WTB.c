#include "wtb.h"
#include "reg.h"
#include "menu.h"
#include "other.h"
#include "usart.h"
#include "os.h"
#include "lcd3033.h"
#include "delay.h"
#include "string.h"
#include <stdio.h>
#include "test.h"
#include "ad7176.h"
#include "barcode.h"
#include "data.h"
#include "base_Config.h"
#include "test_config.h"
#include "sup_fun.h"
extern  Scan_Type_def Scan;



typedef struct {
	char SoftwareCmd[20];
	uint8_t (*fun)(char *);
}SoftwareCmdHandlerTypedef ; 


char  Host_Save_NG[15]      = "HO_DAT_0_NG#";
char  Host_Save_OK[15]      = "HO_DAT_0_OK#";
char  RETEST_Comm[15]       = "RETEST";
char  MCUISP[20]            = "DOWN_PROGRAM#";
char  MCUISP_ACK[30]        = "SYSTEM-MCU-RESET\r\n";
uint8_t  Connect_Falg = RESET ;
uint8_t  Soft_Start_Test = RESET ;




uint8_t Connect_Handler(char *);           
uint8_t Get_TestItem_Handler(char *);       
uint8_t Get_TestDetailItem_Handler(char *); 
uint8_t SoftwareClearHandler(char *);       
uint8_t SoftwareStartTestHandler(char *);   
uint8_t GetStationNum_Handler( char *buf); 
uint8_t SoftwareMCUISPHandler(char *);      
uint8_t SoftwareReadHandler(char *);        
uint8_t SoftwareResetHandler(char *);       

typedef enum {
	Connect = 0,
	TestItem,
	TestItem2,
	CNTClear,
	StartTest,
	StartTest2,
	AppUpdate,
	ReadE2PROM,
	ResetE2PROM
}SoftwareCmdTypdef;

SoftwareCmdHandlerTypedef Cmd_Handler[] = {
	{ "HO_CNC_0#",        Connect_Handler            },
	{ "HO_ITE_0#",        Get_TestItem_Handler       },
	{ "OP_ITE_0#",        Get_TestDetailItem_Handler },
	{ "HO_CLS_0#",        SoftwareClearHandler       },
	{ "HO_TES_0#",        SoftwareStartTestHandler   },
	{ "OP_TES_0#",        SoftwareStartTestHandler   },
	{ "FixtureNumber",    GetStationNum_Handler      },
	{ "SHORTGROUP",       UploadShortGroup           },	
	{ "FixtureConfig",    UploadFixtureConfig        },
//	{ "READ_TEST_DATA",   Upload_Test_Data           },
	{ "DOWN_PROGRAM#",    SoftwareMCUISPHandler      },
	{ "READ_EEPROM_DATA", SoftwareReadHandler        },
	{ "RESET_EEPROM_DATA",SoftwareResetHandler       },	
	{ "NULL" }
};

const char *CmdNotice[] = {
	"联机",
	"获取表头",
	"获取表头，绝缘项目展开",
	"清除下位机计数器",
	"启动下位机测试",
	"启动下位机测试，绝缘项目需展开",
	"查看治具工位号",
	"查看短路群",
	"查询治具配置信息"
//	"查询测试数据",
	"下位机程序升级指令",
	"读取EEPROM信息",
	"复位EEPROM信息",
};
	
/****************************************************************************************************
 	* File Name     :  Set_Test_Satation
 	* Description   :  读取测试工位信息
  * Input         :  无
  * return        :  无
 	* Author        :  Morton
 	* Date          :  2019/3/18
******************************************************************************************************/
void Set_Test_Satation(uint8_t TEST_Station){

//	  if(Fixture.Mech_Struct == SmallFixture )
//			TEST_Station = 1;
		Cmd_Handler[0].SoftwareCmd[7] = TEST_Station+'0';
		Cmd_Handler[1].SoftwareCmd[7] = TEST_Station+'0';
		Cmd_Handler[2].SoftwareCmd[7] = TEST_Station+'0';
		Cmd_Handler[3].SoftwareCmd[7] = TEST_Station+'0';
		Cmd_Handler[4].SoftwareCmd[7] = TEST_Station+'0';
		Cmd_Handler[5].SoftwareCmd[7] = TEST_Station+'0';
		Host_Save_NG[7]    = TEST_Station+'0';
		Host_Save_OK[7]    = TEST_Station+'0';
		Connect_Falg  = RESET;
}




uint8_t Get_Soft_Start_Status(void){
		return Soft_Start_Test ;
}
/*****************************************************************
	* File Name     : Connect_Handler                      
	* Description   : Connect_Handler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t GetStationNum_Handler( char *buf){
	uint8_t TEST_Station = Reg[FixtureNumber].Value ;
	Uart_printf(Fixture.Comm_Uart ,"本治具是: 工位%d \r\n",TEST_Station);
	return True;
}

/*****************************************************************
	* File Name     : Connect_Handler                      
	* Description   : Connect_Handler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t Connect_Handler( char *buf){
	uint8_t TEST_Station = Reg[FixtureNumber].Value ;
	Uart_printf(Fixture.Comm_Uart ,"SL_CNC_%dOK#\r\n",TEST_Station);
	if(Connect_Falg == RESET){
		Connect_Falg = SET ;
		lcdpos(2,8);
		lcd_printf ("联机成功");
	}
	return True;
}

/*****************************************************************
	* File Name     : Get_TestItem_Handler                      
	* Description   : Get_TestItem_Handler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t Get_TestItem_Handler( char *buf){
		TestConfig.OpenList = DISABLE ;
		WTB_Software_Upload_Test_Item();
		return True;
}
/*****************************************************************
	* File Name     : Get_TestDetailItem_Handler                      
	* Description   : Get_TestDetailItem_Handler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t Get_TestDetailItem_Handler( char *buf){
	TestConfig.OpenList = ENABLE;
	WTB_Software_Upload_Test_Item();	
	return True ;
}

/*****************************************************************
	* File Name     : SoftwareClearHandler                      
	* Description   : SoftwareClearHandler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t SoftwareClearHandler( char *buf){
	uint8_t TEST_Station = Reg[FixtureNumber].Value ;
	clear_counter();
	Uart_printf(Fixture.Comm_Uart ,"SL_CLS_%dOK#\r\n",TEST_Station);
	RevertStartupScreen();
	return True;
}
/*****************************************************************
	* File Name     : SoftwareStartTestHandler                      
	* Description   : SoftwareStartTestHandler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t SoftwareStartTestHandler( char *buf){
		uint8_t TEST_Station = Reg[FixtureNumber].Value ;
		if(strstr(buf,Cmd_Handler[StartTest].SoftwareCmd))
			TestConfig.OpenList  = DISABLE ;
		if(strstr(buf,Cmd_Handler[StartTest2].SoftwareCmd))
			TestConfig.OpenList = ENABLE ;
		if(Fixture.Mech_Struct == SmallFixture ){
			if(Scan.Mode == By_Hand && Scan.Result == False ){
				Set_Scan_Result(True);
				lcdreset ();
				lcdpos (1,0); lcd_printf ("手动扫描OK, 请启");
				lcdpos (2,0); lcd_printf ("动测试...      " );
				return True ;
			}
		}else {
			Uart_printf(Fixture.Comm_Uart ,"SL_TES_%d_OK#\r\n",TEST_Station);	
			Soft_Start_Test = SET ;	
			return True;
		}	
		return False;
}

/*****************************************************************
	* File Name     : SoftwareMCUISPHandler                      
	* Description   : SoftwareMCUISPHandler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t SoftwareMCUISPHandler( char *buf){
	Uart_printf(USART1,"%s",MCUISP_ACK);	
	lcdreset ();
	lcdpos (1,0);
	lcd_printf ("程序升级中 ...  ");
	MCUISP_Hander();
	return True ;
}
/*****************************************************************
	* File Name     : SoftwareReadHandler                      
	* Description   : SoftwareReadHandler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t SoftwareReadHandler( char *buf){
	Read_All_Reg_Value(1);
	return True ;
}
/*****************************************************************
	* File Name     : SoftwareResetHandler                      
	* Description   : SoftwareResetHandler                      
  * Input         : /                         
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 17-April-2020                             
*****************************************************************/ 
uint8_t SoftwareResetHandler( char *buf){
	Reset_All_Reg_Value();
	return True;
}

/*******************************************************************************************************
	* File Name     :  WTB_Upper_Cmd_Check
	* Description   :  上位机指令处理函数
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/18
*******************************************************************************************************/
void WTB_Software_Cmd_Check( char *buf, uint8_t *_Mark_Flag){
	uint8_t i = 0;
	char Space[20];
	if(strstr (buf,"help?")||strstr (buf,"HELP?")){
			Uart_printf (Fixture.Comm_Uart,"\r\n程序支持以下指令:\r\n" );
			for( i = 0; !strstr ( Cmd_Handler[i+1].SoftwareCmd,"NULL")  ; i ++  ){
				Uart_printf (Fixture.Comm_Uart,"%2d:  ",i+1 );
				Uart_printf (Fixture.Comm_Uart,"%s",Cmd_Handler[i].SoftwareCmd);
				memset (Space,0,20);
				memset (Space,' ',20-strlen (Cmd_Handler[i].SoftwareCmd) );
				Uart_printf (Fixture.Comm_Uart,Space);
				Uart_printf (Fixture.Comm_Uart," --->%s\r\n",CmdNotice[i]);
			}
			*_Mark_Flag = RESET ;
	}
	for( i = 0; !strstr ( Cmd_Handler[i].SoftwareCmd,"NULL"); i ++  ){
		if(strstr (buf,Cmd_Handler[i].SoftwareCmd)){
			if(Cmd_Handler[i].fun (buf) == True)
				*_Mark_Flag = RESET ;
			break ;
		}
	}
}
/**********************************************************************************************************************
	* File Name     :  Get_Scan_Result
	* Description   :  启动条码扫描件触发扫描
  * Input         :  Status,是否使能扫码，若未使能，直接返回真，反之等待上位机响应
  * return        :  扫描OK ，非0： NG or Overtime
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
uint8_t WTB_Software_Get_Scan_Result(void){
		char rec_buf[128];
		u16 Scan_Result = True;
		if(Scan.Mode == Stand_Alone_mode || Scan.Mode == By_Hand ){ //单机模式
				return True ;
		}
		else if(Scan.Mode == No_Barcode ){ //无条码模式
				lcdreset ();
				cyc4or3set (4);
				cyc4or3run (); 
				if(TestConfig.RF == DISABLE )
					Uart_printf ( Fixture.Comm_Uart, "SN:NOSCAN\r\n" );  //上传伪条码
				else
					Uart_printf ( Fixture.Comm_Uart, "START\r\n" );  //上传伪条码
				lcd_printf ("无条码...       ");
		}else  if( Scan.Mode == Normal ){ //自动扫码模式
				lcdreset ();
				cyc4or3set(4);
				cyc4or3run (); 
				lcd_printf ("扫码...       ");
				if( Software_Trigger_Scan() == False){
						Scan_Result = False ;	
						cyc4or3run ();
						lcd_printf ("扫描失败        ");
						return False;
				}
		}else if( Scan.Mode == Camera ){
				lcdreset ();
				cyc4or3set (4);
				cyc4or3run (); 
				lcd_printf ("相机解码中..");
				memset (rec_buf,0,128);
				if (Get_USART_buffer( Fixture.Comm_Uart, "MCU-ST2#\r\n", rec_buf,Fixture.Cmd_Delay) > 0){
	 
						if(strstr( rec_buf, Cmd_Handler[StartTest].SoftwareCmd )||strstr( rec_buf,Cmd_Handler[StartTest2].SoftwareCmd)){
							
							if(strstr(rec_buf,Cmd_Handler[StartTest].SoftwareCmd))
									TestConfig.OpenList = DISABLE ;
							if(strstr(rec_buf,Cmd_Handler[StartTest2].SoftwareCmd))
									TestConfig.OpenList = ENABLE ;
							
							
//							lcdreset ();
//							cyc4or3set (4);
//							cyc4or3run ();
//							lcd_printf ("扫码OK          ");
//							cyc4or3run ();
//							lcd_printf ("请将产品放到测试");
//							cyc4or3run ();
//							lcd_printf ("位, 双手启动测试");
//							Valve_Drive (Fixe_Products ,RESET);
//							startkeywait(1,1);
//							startkeywait(0,0);
							
							
							Scan_Result  =  True ;							
						}
						else if((strstr( rec_buf, "Barcode_NG" ))){
							 lcd_printf ("扫码NG          ");
							 Scan_Result =  False ;
						}	else{
							 cyc4or3run ();
							 lcd_printf("指令异常");
							 cyc4or3run ();
						   lcd_printf ("%s",rec_buf);	
							 Scan_Result =  False ;						
						}							
				}else {
					  cyc4or3run ();
						lcd_printf ("扫码超时        ");
						Scan_Result = False ;
				}
				return Scan_Result;		
		}

		memset (rec_buf,0,128);
		if(Get_USART_buffer( Fixture.Comm_Uart, rec_buf, rec_buf,Fixture.Cmd_Delay)){
				if(strstr( rec_buf,Cmd_Handler[StartTest].SoftwareCmd)||strstr( rec_buf,Cmd_Handler[StartTest2].SoftwareCmd) ){
					
						if(strstr(rec_buf,Cmd_Handler[StartTest].SoftwareCmd))
								TestConfig.OpenList = DISABLE ;
						if(strstr(rec_buf,Cmd_Handler[StartTest2].SoftwareCmd))
								TestConfig.OpenList = ENABLE ;
				
						Scan_Result = True ;
				}
				else {
						Scan_Result = False  ;
						cyc4or3run ();
						lcd_printf ("Error:%s",rec_buf);
				}
		}
		else{
				Scan_Result = False  ;
				cyc4or3run ();
				lcd_printf ("上位机指令超时  ");
		}	
		
		return Scan_Result ;	
}


/*****************************************************************
	* File Name     : WTB_Software_Get_Save_Result                      
	* Description   : WTB_Software_Get_Save_Result                      
  * Input         : Test_Result                              
	* return        : data save Result                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
uint8_t WTB_Software_Get_Save_Result( uint8_t Test_Result){
	uint8_t Upload_data_Result = True;
	char rec_buf[100];
	memset(rec_buf,0,100);
	if(Get_USART_buffer( Fixture.Comm_Uart, rec_buf, rec_buf,Fixture.Cmd_Delay)==0){
			cyc4or3run();
			lcd_printf("保存数据超时    ");
			Upload_data_Result = False;
	}else{
			if(strstr( rec_buf,Host_Save_NG)){
					Upload_data_Result = False;
			}else if(strstr( rec_buf,Host_Save_OK)){
					Upload_data_Result = True;
			}else if(strstr( rec_buf,RETEST_Comm)){
				  Upload_data_Result = 99;
			}else{
					cyc4or3run();
					lcd_printf("指令异常:%s",rec_buf);
					Upload_data_Result = False;
			}
	}	
		return Upload_data_Result;
}


