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
 	* Description   :  ��ֹ��λ������
  * Input         :  ��
  * return        :  ��
 	* Author        :  Morton
 	* Date          :  2016.12.5
************************************************************************************************************************/
void ZDT_Software_Sotp(void){
		Uart_printf ( Fixture.Comm_Uart , "%s",Stop_Upper_Cmd );  //��դ�쳣����ֹ��λ��
}


/**********************************************************************************************************************
 	* File Name     :  ZDT_Upper_Cmd_Check
 	* Description   :  *buf ��������ָ�룬_Mark_Flag ������ݱ�����
  * Input         :  ��
  * return        :  ��
 	* Author        :  Morton
 	* Date          :  2019/3/21
************************************************************************************************************************/
void ZDT_Software_Cmd_Check(char *buf, uint8_t *_Mark_Flag){	
		if(Scan.Mode == By_Hand && Scan.Result == False ){
			if(strstr(buf,Scan.Barcode_OK_Command)){
					Set_Scan_Result(True);
					lcdreset ();
					lcdpos (1,0); lcd_printf ("�ֶ�ɨ��OK, ����");
					lcdpos (2,0); lcd_printf ("������...      " );
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
				lcd_printf ("���������� ...  ");
				MCUISP_Hander();
				*_Mark_Flag = RESET ;
				return ;
		}
}
/**********************************************************************************************************************
	* File Name     :  Get_Scan_Result
	* Description   :  ��������ɨ�������ɨ��
  * Input         :  Status,�Ƿ�ʹ��ɨ�룬��δʹ�ܣ�ֱ�ӷ����棬��֮�ȴ���λ����Ӧ
  * return        :  ɨ��OK ����0�� NG or Overtime
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
uint8_t ZDT_Software_Get_Scan_Result(void){
		char rec_buf[128];
		u16 Scan_Result = True;
		if(Scan.Mode == Stand_Alone_mode || Scan.Mode == By_Hand ){ //����ģʽ
				return True ;
		}
		else if(Scan.Mode == No_Barcode ){ //������ģʽ
				lcdreset ();
				cyc4or3set (4);
				cyc4or3run (); 
				Uart_printf ( Fixture.Comm_Uart, "*NO SCAN@" );  //�ϴ�α����
				lcd_printf ("������...       ");
		}else  if( Scan.Mode == Normal ){ //�Զ�ɨ��ģʽ
				lcdreset ();
				cyc4or3set(4);
				cyc4or3run (); 
				lcd_printf ("ɨ��...       ");
				if( Software_Trigger_Scan() == False){
						Scan_Result = False ;	
						cyc4or3run ();
						lcd_printf ("ɨ��ʧ��        ");
						return False;
				}
		}else if( Scan.Mode == Camera ){
				lcdreset ();
				cyc4or3set (4);
				cyc4or3run  (); 
				lcd_printf ("������...       ");
				memset (rec_buf,0,128);
				if (Get_USART_buffer( Fixture.Comm_Uart, "*MIC^", rec_buf,5000) > 0){
						cyc4or3run ();
						lcd_printf ("%s",rec_buf);
			 
						if((strstr( rec_buf, Scan.Barcode_OK_Command ))){
							lcd_printf ("ɨ��OK          ");
							Scan_Result  =  True ;
						}
						else if((strstr( rec_buf, "Barcode_NG" ))){
							 lcd_printf ("ɨ��NG          ");
							 Scan_Result =  False ;
						}else{
								lcd_printf ("ɨ��NG          ");
							 Scan_Result =  False ;
						}							
				}else {
					  cyc4or3run ();
						lcd_printf ("ɨ�볬ʱ        ");
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
				lcd_printf ("��λ��ָ�ʱ  ");
		}	
		
		return Scan_Result ;	
}


/**********************************************************************************************************************
	* File Name     :  Get_Scan_Result
	* Description   :  ��������ɨ�������ɨ��
  * Input         :  Status,�Ƿ�ʹ��ɨ�룬��δʹ�ܣ�ֱ�ӷ����棬��֮�ȴ���λ����Ӧ
  * return        :  ɨ��OK ����0�� NG or Overtime
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
				lcd_printf ("���ݱ��泬ʱ    ");
		}	
		return Host_Save_Result;
}

