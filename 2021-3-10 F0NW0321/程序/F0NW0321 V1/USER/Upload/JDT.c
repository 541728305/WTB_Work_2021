#include "jdt.h"
#include "base_Config.h"
//#define  JDT_Upper_Commputer

#if defined  JDT_Upper_Commputer 

#include "string.h"
#include "usart.h"
#include "os.h"
#include "test.h"
#include "lcd3033.h"
#include "delay.h"
#include "other.h"
#include "24cxx.h"
#include "sup_fun.h"
#include "short.h"
#include "open.h"


// 表头通讯格式:Itemname#7#1A to 1B;5;0;ohm#1A to 1C;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm\r\n


#define Total_Host_CMD_Num           10 
#define JDT_Total_Test_Item_Num      78







// MCU主动指令
const char  *Barcode_Scan_CMD         = "MCU-ST2#"; //MCU发送扫描指令
//**************************************联机指?*************************************************************************
const char  Host_Connect_CMD[10]      = "HOST-CNC#";//上位机联机指令
const char  Host_Disconnect_CMD[10]   = "HOST-DSC#";//上位机脱机指令
//*********************************扫描指?*******************************************************************************
const char  Barcode_MIC_KNS_CMD[10]   = "HOST-SM1#";//
const char  Barcode_MIC_AAC_CMD[10]   = "HOST-SM2#";//
const char  Barcode_MIC_ST_CMD[10]    = "HOST-SM3#";//
const char  Barcode_MIC_GTK_CMD[10]   = "HOST-SM4#";//
const char  Barcode_Scan_NC_CMD[10]   = "HOST-SOK#";//无MIC扫描指令
const char  Barcode_Scan_NC1_CMD[10]  = "HOST-SMK#";//无MIC扫描指令
const char  Barcode_Scan_NG_CMD[10]   = "HOST-SFL#";//扫描NG指令
//********************************数据保存指令***************************************************************************
const char  Host_Save_Data_OK_CMD[10] = "HOST-DOK#";//数据上传成功指令
const char  Host_Save_Data_NG_CMD[10] = "HOST-DFL#";//数据上传失败指令
const char  Slave_Disconnect_CMD[10]  = "HOST-DSC#";//上位机脱机指令
//********************************扫描指令*******************************************************************************
const char  Slave_Barcode_MIC_KNS_CMD[10] = "MCU-SM1#";//
const char  Slave_Barcode_MIC_AAC_CMD[10] = "MCU-SM2#";//
const char  Slave_Barcode_MIC_ST_CMD[10]  = "MCU-SM3#";//
const char  Slave_Barcode_MIC_GTK_CMD[10] = "MCU-SM4#";//
const char  Slave_Barcode_Scan_NC_CMD[10] = "MCU-SOK#";//无MIC扫描指令
const char  Slave_Barcode_Scan_NC1_CMD[10]= "MCU-SMK#";//无MIC扫描指令
const char  Slave_Barcode_Scan_NG_CMD[10] = "MCU-SFL#";//扫描NG指令
//********************************MCU数据保存指令************************************************************************
const char  Slave_Save_Data_OK_CMD[10]    = "MCU-DOK#";//数据上传成功指令
const char  Slave_t_Save_Data_NG_CMD[10]  = "MCU-DFL#";//数据上传失败指令
//************************************计算清零**************************************************************************
const char  *Host_Clear_CNT_CMD           = "HOST-CLR#";// MCU 不返回指令
//************************************主机表头获取命令******************************************************************
const char  *Host_Get_Itemname = "Itemname#";


const  char  *Host_CMD[] = {
//	Host_Connect_CMD,
		Host_Disconnect_CMD,
		Barcode_MIC_KNS_CMD,
		Barcode_MIC_AAC_CMD,
		Barcode_MIC_ST_CMD,
		Barcode_MIC_GTK_CMD,
		Barcode_Scan_NC_CMD,
		Barcode_Scan_NC1_CMD,
		Barcode_Scan_NG_CMD,
		Host_Save_Data_OK_CMD,
		Host_Save_Data_NG_CMD
};
const  char *Slave_CMD[]= {
		Slave_Disconnect_CMD,
		Slave_Barcode_MIC_KNS_CMD,
		Slave_Barcode_MIC_AAC_CMD,
		Slave_Barcode_MIC_ST_CMD,
		Slave_Barcode_MIC_GTK_CMD,
		Slave_Barcode_Scan_NC_CMD,
		Slave_Barcode_Scan_NC1_CMD,
		Slave_Barcode_Scan_NG_CMD,
		Slave_Save_Data_OK_CMD,
		Slave_t_Save_Data_NG_CMD
};

/****************************************************************************************************************
	* File Name     : 上传JDT上位机表头
	* Description   : 无
  * Input         : 无
	* return        :
	* Version       : 
	* Author        :
	* Date          :
***************************************************************************************************************/
static  void Upload_Test_Item( void ){
		uint16_t i,j;
		Uart_printf (Fixture.Comm_Uart ,"SL_ITE_Itemname#%d#",JDT_Total_Test_Item_Num);
		// Short  --- 73
		for ( i = 0 ; ShortGroup[i][0]; i ++){
				j = 1 ;
				while(ShortGroup[i][j]){
						Uart_printf( Fixture.Comm_Uart,"%s-%s;20;0;ohm#",Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]] );     
						j ++;
				}
		}
		Uart_printf (Fixture.Comm_Uart ,"OPEN;MAX;1;Mohm#");
		 
		Uart_printf (Fixture.Comm_Uart ,"D1_VF+R1;3.185,;2.985;V#");
		Uart_printf (Fixture.Comm_Uart ,"D1_Light;OK;OK;NA#");
		Uart_printf (Fixture.Comm_Uart ,"D1_IR;10;0;uA#");
		Uart_printf (Fixture.Comm_Uart ,"Steel;5;0;ohm#");
//		Uart_lcd_printf (USART1 ,"#STLD;5;0;ohm");
		Uart_printf (Fixture.Comm_Uart ,"\r\n");
}

/****************************************************************************************************************
	* File Name     : Host_Cmd_Check
	* Description   : Host_Cmd_Check 检查是否为被动返回指令
  * Input         : *Usart_Buffer
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 2016.12.2
***************************************************************************************************************/
void Host_Cmd_Check(char *Usart_Buffer ){
	uint8_t i;
	Usart_Buffer[9] = '\0'; 
	if(strcmp( Usart_Buffer,Host_Connect_CMD )==0){ //下位机联机响应
				Uart_lcd_printf(Fixture.Comm_Uart,"MCU-CNC#\r\n");
	}else if(strcmp( Usart_Buffer,Host_Get_Itemname)== 0){
				Upload_Test_Item();
	}
	else 	if(strcmp( Usart_Buffer,Host_Clear_CNT_CMD )==0){ //上位机计数清零处理
				clear_counter();
	}else
	{
		for(i=0;i<Total_Host_CMD_Num;i++){
			if(strcmp( Usart_Buffer, Host_CMD[i] )==0)
				Uart_lcd_printf(Fixture.Comm_Uart,"%s\r\n",Slave_CMD[i]);
		}
	}
	
}
/****************************************************************************************************************
	* File Name     : Get_Scan_Result
	* Description   : Get_Scan_Result  启动条码扫描 检查是否为被动返回指令
  * Input         : Status,是否使能扫码，若未使能，直接返回真，反之等待上位机响应
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 2016.12.2
***************************************************************************************************************/
u8 Get_PC_Scan_Result(u8 Status){
		uint16_t  Scan_Result = True;
		char buf[32];
		if(Status ==  DISABLE)
			return True ;
		lcdreset ();
		cyc4or3run ();  
		lcd_printf  ("扫描...         ");
		uart1_init(38400); 
		lcdpos (lcdcon-1 ,12); 
		if (Get_USART_buffer(Fixture.Comm_Uart,Barcode_Scan_CMD,buf,3000)){
			if((strcasecmp ( buf,Barcode_Scan_NC_CMD)==0)||(strcasecmp ( buf,Barcode_Scan_NC1_CMD)==0)){
					Scan_Result = True ;
					lcd_printf  ("OK");
			}else if(strcasecmp ( buf ,Barcode_Scan_NG_CMD)==0){
					Scan_Result = False  ;
					lcd_printf  ("NG");
			}
		}else {
			Scan_Result = False;
			lcd_printf  ("超时");
		}
		return Scan_Result ;	
}
/****************************************************************************************************************
	* File Name     : JDT_Upload_Detail_Test_Data
	* Description   : 串口上传测试数据，并接收上位机数据保存结果指令
  * Input         : Result，整体测试结果，PASS为真  FAIL 
	* return        : Host_Save_Result,上位机保存OK返回0，反之非0
	* Version       : V1.0
	* Author        : Morton
	* Date          : 2016.12.2
***************************************************************************************************************/
uint8_t  JDT_Upload_Detail_Test_Data(u8 Result){
		uint8_t Host_Save_Result = True ;
		char  buf[64];
//		if( Test_Item_Num < JDT_Total_Test_Item_Num ){
//				for(i=0;i<(JDT_Total_Test_Item_Num - Test_Item_Num);i++)
//						Uart_printf(Fixture.Comm_Uart,"1*no data#");
//		}
		if(Result==True )
				Uart_printf(Fixture.Comm_Uart,"PASS\r\n");
		else
				Uart_printf(Fixture.Comm_Uart,"FAIL\r\n");
		if(Fixture.Mode  == Step_Test_Mode ){
			return True ;
		}	
		if(Scan_Barcode_Enable == DISABLE ){
				Host_Save_Result = True ;
		}else {
			if (_Get_USART_buffer(Fixture.Comm_Uart,buf,3000)){
						if(strcasecmp ( buf ,Host_Save_Data_OK_CMD)==0){
							Host_Save_Result = True ;
						}
						if(strcasecmp ( buf,Host_Save_Data_NG_CMD)==0){
							Host_Save_Result = False  ;
							cyc4or3run (); 
							lcd_printf  ("数据保存NG     ");
						}
			}
		else{
			Host_Save_Result |= False ;
			cyc4or3run ();
			lcd_printf  ("数据保存超时    ");
		}
		
	}
		return Host_Save_Result;
}
//#endif



//#if defined  Double_Hole_Test 

//uint8_t  Fixture_Number=0;
////函数名: Fixture_Num_Set();
////参  数：无
////返回值：无
////功  能：上传表头
////日  期：2016.12.13
//void  Fixture_Num_Set(void ){
//		uint8_t  Num, Save_data,Button_Status;
//		Num = AT24CXX_ReadLenByte(Fixture_Num_Addr ,1);
//		lcdreset ();
//		cyc4or3run (); lcd_printf  ("左右穴设置: %s  ",(Num==0)?"左":"右");
//		cyc4or3run (); lcd_printf  ("左键选择右键确认");
//		while(1){
//			Button_Status = Get_start_key_val();
//			if(Button_Status==Left_Button_Pressed_Down ){
//				Num ++;
//				lcdpos (0,0); lcd_printf ("左右穴设置: %s  ",(Num%2==0)? "左":"右");
//			}
//			if(Button_Status == Right_Button_Pressed_Down )
//				break ;
//		}
//		cyc4or3run ();  lcd_printf  ("当前设置状态为: ");
//		cyc4or3run ();
//		if(Num%2==0)
//			lcd_printf  ("    %s     ",("左穴"));
//		else
//			lcd_printf  ("    %s     ",("右穴"));

//		AT24CXX_WriteLenByte (Fixture_Num_Addr ,(Num%2),1);
//		delay_ms (10);
//		Save_data = AT24CXX_ReadOneByte (Fixture_Num_Addr);
//		cyc4or3run ();
//		if(Save_data==(Num%2) ){
//			lcd_printf  ("数据保存OK      ");
//		}else{
//			lcd_printf  ("数据保存失败    ");
//			beep (5,150);
//		}	
//		Fixture_Number = (Num%2)+1;
//		delay_ms (500);
//		RevertStartupScreen ();
//}

#endif






