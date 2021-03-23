#include "zdt.h"
#include "test_config.h"
#include "base_Config.h"
#include "other.h"
#include "usart.h"
#include "lcd3033.h"
#include "delay.h"
#include "barcode.h"
#include "ad7176.h"
#include  <string.h>
extern char  MCUISP[20]  ;   //      = "DOWN_PROGRAM#";
extern char  MCUISP_ACK[30]; //        = "SYSTEM-MCU-RESET\r\n";
extern  Scan_Type_def  Scan;


const char  *Stop_Upper_Cmd = "*END^";
const char  *ZDT_Upper_Computer_DOK_CMD = "*OK!" ; 
const char  *ZDT_Upper_Computer_DNG_CMD = "*NG!" ; 



/**********************************************************************************************************************
 	* File Name     :  Stop_Upper
 	* Description   :  终止上位机测试
  * Input         :  无
  * return        :  无
 	* Author        :  Morton
 	* Date          :  2016.12.5
************************************************************************************************************************/
void ZDT_Software_Sotp(void){
		Uart_printf ( Fixture.Comm_Uart , "%s",Stop_Upper_Cmd );  //光栅异常，终止上位机
}


/**********************************************************************************************************************
 	* File Name     :  ZDT_Upper_Cmd_Check
 	* Description   :  *buf 串口数据指针，_Mark_Flag 标记数据被处理
  * Input         :  无
  * return        :  无
 	* Author        :  Morton
 	* Date          :  2019/3/21
************************************************************************************************************************/
void ZDT_Software_Cmd_Check(char *buf, uint8_t *_Mark_Flag){	
		if(Scan.Mode == By_Hand && Scan.Result == False ){
			if(strstr(buf,Scan.Barcode_OK_Command)){
					Set_Scan_Result(True);
					lcdreset ();
					lcdpos (1,0); lcd_printf ("手动扫描OK, 请启");
					lcdpos (2,0); lcd_printf ("动测试...      " );
				  *_Mark_Flag = RESET ;
					return ;
			}else {
					cyc4or3run ();
					lcd_printf ("Error:%s",buf);
			}
		}
		if(strstr(buf,MCUISP) && Fixture.Comm_Uart == USART1 ){ //software trigger system reset 
				Uart_printf(USART1,"%s",MCUISP_ACK);	
				lcdreset ();
				lcdpos (1,0);
				lcd_printf ("程序升级中 ...  ");
				MCUISP_Hander();
				*_Mark_Flag = RESET ;
				return ;
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
uint8_t ZDT_Software_Get_Scan_Result(void){
		char rec_buf[128];
		u16 Scan_Result = True;
		if(Scan.Mode == Stand_Alone_mode || Scan.Mode == By_Hand ){ //单机模式
				return True ;
		}
		else if(Scan.Mode == No_Barcode ){ //无条码模式
				lcdreset ();
				cyc4or3set (4);
				cyc4or3run (); 
				Uart_printf ( Fixture.Comm_Uart, "*NO SCAN@" );  //上传伪条码
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
				cyc4or3run  (); 
				lcd_printf ("解码中...       ");
				memset (rec_buf,0,128);
				if (Get_USART_buffer( Fixture.Comm_Uart, "*MIC^", rec_buf,5000) > 0){
						cyc4or3run ();
						lcd_printf ("%s",rec_buf);
			 
						if((strstr( rec_buf, Scan.Barcode_OK_Command ))){
							lcd_printf ("扫码OK          ");
							Scan_Result  =  True ;
						}
						else if((strstr( rec_buf, "Barcode_NG" ))){
							 lcd_printf ("扫码NG          ");
							 Scan_Result =  False ;
						}else{
								lcd_printf ("扫码NG          ");
							 Scan_Result =  False ;
						}							
				}else {
					  cyc4or3run ();
						lcd_printf ("扫码超时        ");
						ZDT_Software_Sotp();
						Scan_Result = False ;
				}
				return Scan_Result;		
		}

		memset (rec_buf,0,128);
		if(Get_USART_buffer( Fixture.Comm_Uart, rec_buf, rec_buf,ZDT_CMD_Delay)){
				if(strstr( rec_buf,Scan.Barcode_OK_Command)){
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


/**********************************************************************************************************************
	* File Name     :  Get_Scan_Result
	* Description   :  启动条码扫描件触发扫描
  * Input         :  Status,是否使能扫码，若未使能，直接返回真，反之等待上位机响应
  * return        :  扫描OK ，非0： NG or Overtime
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
uint8_t ZDT_Software_Get_Save_Result(void){
		char rec_buf[64];
		uint8_t  Host_Save_Result = True ;
		memset (rec_buf,0,128);
		if(Get_USART_buffer( Fixture.Comm_Uart, rec_buf, rec_buf,ZDT_CMD_Delay)){
				if(strstr( rec_buf,ZDT_Upper_Computer_DOK_CMD)){
						Host_Save_Result = True ;
				}
				else if(strstr ( rec_buf,ZDT_Upper_Computer_DNG_CMD)){
						Host_Save_Result = False  ;
				}else{
						Host_Save_Result = False  ;
						cyc4or3run ();
						lcd_printf ("Error:%s",rec_buf);
				}
		}else{
				Host_Save_Result = False  ;
				cyc4or3run ();
				lcd_printf ("数据保存超时    ");
		}	
		return Host_Save_Result;
}

