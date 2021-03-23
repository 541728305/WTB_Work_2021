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


// ±ÌÕ∑Õ®—∂∏Ò Ω:Itemname#7#1A to 1B;5;0;ohm#1A to 1C;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm#6A to 6B;5;0;ohm\r\n


#define Total_Host_CMD_Num           10 
#define JDT_Total_Test_Item_Num      78







// MCU÷˜∂Ø÷∏¡Ó
const char  *Barcode_Scan_CMD         = "MCU-ST2#"; //MCU∑¢ÀÕ…®√Ë÷∏¡Ó
//**************************************¡™ª˙÷∏¡*************************************************************************
const char  Host_Connect_CMD[10]      = "HOST-CNC#";//…œŒªª˙¡™ª˙÷∏¡Ó
const char  Host_Disconnect_CMD[10]   = "HOST-DSC#";//…œŒªª˙Õ—ª˙÷∏¡Ó
//*********************************…®√Ë÷∏¡*******************************************************************************
const char  Barcode_MIC_KNS_CMD[10]   = "HOST-SM1#";//
const char  Barcode_MIC_AAC_CMD[10]   = "HOST-SM2#";//
const char  Barcode_MIC_ST_CMD[10]    = "HOST-SM3#";//
const char  Barcode_MIC_GTK_CMD[10]   = "HOST-SM4#";//
const char  Barcode_Scan_NC_CMD[10]   = "HOST-SOK#";//ŒﬁMIC…®√Ë÷∏¡Ó
const char  Barcode_Scan_NC1_CMD[10]  = "HOST-SMK#";//ŒﬁMIC…®√Ë÷∏¡Ó
const char  Barcode_Scan_NG_CMD[10]   = "HOST-SFL#";//…®√ËNG÷∏¡Ó
//******************************** ˝æ›±£¥Ê÷∏¡Ó***************************************************************************
const char  Host_Save_Data_OK_CMD[10] = "HOST-DOK#";// ˝æ›…œ¥´≥…π¶÷∏¡Ó
const char  Host_Save_Data_NG_CMD[10] = "HOST-DFL#";// ˝æ›…œ¥´ ß∞‹÷∏¡Ó
const char  Slave_Disconnect_CMD[10]  = "HOST-DSC#";//…œŒªª˙Õ—ª˙÷∏¡Ó
//********************************…®√Ë÷∏¡Ó*******************************************************************************
const char  Slave_Barcode_MIC_KNS_CMD[10] = "MCU-SM1#";//
const char  Slave_Barcode_MIC_AAC_CMD[10] = "MCU-SM2#";//
const char  Slave_Barcode_MIC_ST_CMD[10]  = "MCU-SM3#";//
const char  Slave_Barcode_MIC_GTK_CMD[10] = "MCU-SM4#";//
const char  Slave_Barcode_Scan_NC_CMD[10] = "MCU-SOK#";//ŒﬁMIC…®√Ë÷∏¡Ó
const char  Slave_Barcode_Scan_NC1_CMD[10]= "MCU-SMK#";//ŒﬁMIC…®√Ë÷∏¡Ó
const char  Slave_Barcode_Scan_NG_CMD[10] = "MCU-SFL#";//…®√ËNG÷∏¡Ó
//********************************MCU ˝æ›±£¥Ê÷∏¡Ó************************************************************************
const char  Slave_Save_Data_OK_CMD[10]    = "MCU-DOK#";// ˝æ›…œ¥´≥…π¶÷∏¡Ó
const char  Slave_t_Save_Data_NG_CMD[10]  = "MCU-DFL#";// ˝æ›…œ¥´ ß∞‹÷∏¡Ó
//************************************º∆À„«Â¡„**************************************************************************
const char  *Host_Clear_CNT_CMD           = "HOST-CLR#";// MCU ≤ª∑µªÿ÷∏¡Ó
//************************************÷˜ª˙±ÌÕ∑ªÒ»°√¸¡Ó******************************************************************
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
	* File Name     : …œ¥´JDT…œŒªª˙±ÌÕ∑
	* Description   : Œﬁ
  * Input         : Œﬁ
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
	* Description   : Host_Cmd_Check ºÏ≤È «∑ÒŒ™±ª∂Ø∑µªÿ÷∏¡Ó
  * Input         : *Usart_Buffer
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 2016.12.2
***************************************************************************************************************/
void Host_Cmd_Check(char *Usart_Buffer ){
	uint8_t i;
	Usart_Buffer[9] = '\0'; 
	if(strcmp( Usart_Buffer,Host_Connect_CMD )==0){ //œ¬Œªª˙¡™ª˙œÏ”¶
				Uart_lcd_printf(Fixture.Comm_Uart,"MCU-CNC#\r\n");
	}else if(strcmp( Usart_Buffer,Host_Get_Itemname)== 0){
				Upload_Test_Item();
	}
	else 	if(strcmp( Usart_Buffer,Host_Clear_CNT_CMD )==0){ //…œŒªª˙º∆ ˝«Â¡„¥¶¿Ì
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
	* Description   : Get_Scan_Result  ∆Ù∂ØÃı¬Î…®√Ë ºÏ≤È «∑ÒŒ™±ª∂Ø∑µªÿ÷∏¡Ó
  * Input         : Status, «∑Ò πƒ‹…®¬Î£¨»ÙŒ¥ πƒ‹£¨÷±Ω”∑µªÿ’Ê£¨∑¥÷Æµ»¥˝…œŒªª˙œÏ”¶
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
		lcd_printf  ("…®√Ë...         ");
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
			lcd_printf  ("≥¨ ±");
		}
		return Scan_Result ;	
}
/****************************************************************************************************************
	* File Name     : JDT_Upload_Detail_Test_Data
	* Description   : ¥Æø⁄…œ¥´≤‚ ‘ ˝æ›£¨≤¢Ω” ’…œŒªª˙ ˝æ›±£¥ÊΩ·π˚÷∏¡Ó
  * Input         : Result£¨’˚ÃÂ≤‚ ‘Ω·π˚£¨PASSŒ™’Ê  FAIL 
	* return        : Host_Save_Result,…œŒªª˙±£¥ÊOK∑µªÿ0£¨∑¥÷Æ∑«0
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
							lcd_printf  (" ˝æ›±£¥ÊNG     ");
						}
			}
		else{
			Host_Save_Result |= False ;
			cyc4or3run ();
			lcd_printf  (" ˝æ›±£¥Ê≥¨ ±    ");
		}
		
	}
		return Host_Save_Result;
}
//#endif



//#if defined  Double_Hole_Test 

//uint8_t  Fixture_Number=0;
////∫Ø ˝√˚: Fixture_Num_Set();
////≤Œ   ˝£∫Œﬁ
////∑µªÿ÷µ£∫Œﬁ
////π¶  ƒ‹£∫…œ¥´±ÌÕ∑
////»’  ∆⁄£∫2016.12.13
//void  Fixture_Num_Set(void ){
//		uint8_t  Num, Save_data,Button_Status;
//		Num = AT24CXX_ReadLenByte(Fixture_Num_Addr ,1);
//		lcdreset ();
//		cyc4or3run (); lcd_printf  ("◊Û”“—®…Ë÷√: %s  ",(Num==0)?"◊Û":"”“");
//		cyc4or3run (); lcd_printf  ("◊Ûº¸—°‘Ò”“º¸»∑»œ");
//		while(1){
//			Button_Status = Get_start_key_val();
//			if(Button_Status==Left_Button_Pressed_Down ){
//				Num ++;
//				lcdpos (0,0); lcd_printf ("◊Û”“—®…Ë÷√: %s  ",(Num%2==0)? "◊Û":"”“");
//			}
//			if(Button_Status == Right_Button_Pressed_Down )
//				break ;
//		}
//		cyc4or3run ();  lcd_printf  ("µ±«∞…Ë÷√◊¥Ã¨Œ™: ");
//		cyc4or3run ();
//		if(Num%2==0)
//			lcd_printf  ("    %s     ",("◊Û—®"));
//		else
//			lcd_printf  ("    %s     ",("”“—®"));

//		AT24CXX_WriteLenByte (Fixture_Num_Addr ,(Num%2),1);
//		delay_ms (10);
//		Save_data = AT24CXX_ReadOneByte (Fixture_Num_Addr);
//		cyc4or3run ();
//		if(Save_data==(Num%2) ){
//			lcd_printf  (" ˝æ›±£¥ÊOK      ");
//		}else{
//			lcd_printf  (" ˝æ›±£¥Ê ß∞‹    ");
//			beep (5,150);
//		}	
//		Fixture_Number = (Num%2)+1;
//		delay_ms (500);
//		RevertStartupScreen ();
//}

#endif






