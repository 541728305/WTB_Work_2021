#include "base_Config.h"
#include "zdt.h"
#include "base_Config.h"
#include "barcode.h"
#include "global.h"
#include <string.h>
#include "usart.h"
#include "lcd3033.h"
#include "delay.h"
#include "other.h"
#include "24cxx.h"
#include "other.h"
#include "menu.h"
#include "test.h"
#include "reg.h"
#include "menu.h"

char Scan_Mode_Menu[5][17]     = {  "    ����        ","  ������/ ������","    �ֶ�        ","    ɨ��ǹ      ","    �������    "}; 
char BarcodeReader_Name[2][17] = {  "    ����ʿ      ","    �Ͼ�����    "};

/*********************************************************************************************
	* File Name     :Set_Scan_Result
	* Description   :����ɨ����
  * Input         :Temp
  * return        :��
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
void Set_Scan_Result( uint8_t Temp){
	Scan.Result = Temp;
	if(Scan.Result == False ){
			memset(Scan.Barcode_Buffer,0,32);
	}		
}
/**********************************************************************************************************************
 	* File Name     :  Get_Scan_Mode
 	* Description   :  ɨ��ģʽ
  * Input         :  /
  * return        :  /
 	* Author        :  Morton
 	* Date          :  2019/3/23
************************************************************************************************************************/
Scan_Mode  Get_Scan_Mode(void){
	return Scan.Mode ;
}
/*********************************************************************************************
	* File Name     : Check_Hand_Scan
	* Description   : �ֶ�ɨ��������
  * Input         : mode ��ǰ����ģʽ�����������ܿ�
  * return        : OK����0 ��֮1
	* Author        : Morton
	* Date          : 2018/8/22
*********************************************************************************************/
uint8_t Check_Hand_Scan(uint8_t mode){
	if( mode == Auto_Test_Mode && Scan.Mode == By_Hand && Scan.Result == False ){
			lcdreset ();
			cyc4or3run ();
			lcd_printf ("�����ֶ�ɨ�裬��");
			cyc4or3run ();
			lcd_printf ("�����ξ߲���    ");
			return False;
	}

	return True;
}
/**********************************************************************************************************************
 	* File Name     :  ZDT_Upper_Cmd_Check
 	* Description   :  *buf ��������ָ�룬_Mark_Flag ������ݱ�����
  * Input         :  ��
  * return        :  ��
 	* Author        :  Morton
 	* Date          :  2019/3/21
************************************************************************************************************************/
void ZDT_Upper_Cmd_Check(char *buf, uint8_t *_Mark_Flag){	
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
}
/**********************************************************************************************************************
	* File Name     :  Read_Barcode_Format
	* Description   :  �����ʽ������
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2019/3/23
************************************************************************************************************************/
static void Read_Barcode_Format(void){
	uint8_t i;
	for( i = 0; i < Scan.Barcode_Length ; i ++){
			Scan.Barcode_Format[i]= AT24CXX_ReadLenByte(Reg[BarcodeFormat].Addr+i,1);
			if((Scan.Barcode_Format[i]>='A' && Scan.Barcode_Format[i] <= 'Z')||
				 (Scan.Barcode_Format[i]>='a' && Scan.Barcode_Format[i] <= 'z')||
				 (Scan.Barcode_Format[i]>='0' && Scan.Barcode_Format[i] <= '9')||
				 (Scan.Barcode_Format[i]=='*'))
			continue ;
			Scan.Barcode_Format[i]='*';
			AT24CXX_WriteLenByte (Reg[BarcodeFormat].Addr+i,Scan.Barcode_Format[i],1);
	}	
	Scan.Barcode_Format[Scan.Barcode_Length] = '\0';
}
/**********************************************************************************************************************
	* File Name     :  Read_Barcode_Format_Configuration
	* Description   :  ��ȡɨ��ǹ������Ϣ
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
void Read_Barcode_Format_Configuration(void){
	Scan.Barcode_Check = Reg[BarcodeCheckEnable].Value;
	cyc4or3run ();
	lcd_printf ("����У��: %s  ",Scan.Barcode_Check? "����":"�ر�");
	if(Scan.Barcode_Check == ENABLE ){
		Scan.Barcode_Length = Reg[BarcodeLength].Value ;
		Read_Barcode_Format();
	}
}
void Read_Barcode_Reader_Configuration( void ){
		Set_Scan_Result(False);
	
		Scan.Time = Reg[ScanTime].Value;
		Scan.Barcode_Reader_Type  = Reg[BarcodeReader].Value;
	  Scan.Barcode_Reader_Baud  = Reg[BarcodeReaderBPS].Value;
	
		BarcodeReader_Name[Scan.Barcode_Reader_Type][4+8]=0;
	
		cyc4or3run ();
		lcd_printf ("ɨ��ǹ: %s",&BarcodeReader_Name[Scan.Barcode_Reader_Type][4]);
		cyc4or3run ();
		lcd_printf ("������:%6dbps",Scan.Barcode_Reader_Baud);
		cyc4or3run ();
		lcd_printf ("ɨ��ʱ��:%3dS   ",Scan.Time/1000);
	
		if(Scan.Barcode_Reader_Type == KEYENCE){
			strcpy (Scan.Barcode_Reader_Start_Cmd,"LON\r\n");
			strcpy (Scan.Barcode_Reader_Stop_Cmd ,"LOFF\r\n");
		}else if(Scan.Barcode_Reader_Type == Infoscan ){
			Scan.Barcode_Reader_Start_Cmd[0] = 0x16;
			Scan.Barcode_Reader_Start_Cmd[1] = 0x54;//0x74
			Scan.Barcode_Reader_Start_Cmd[2] = 0x0D;
			Scan.Barcode_Reader_Start_Cmd[3] = '\0';
			Scan.Barcode_Reader_Stop_Cmd [0] = 0x16;
			Scan.Barcode_Reader_Stop_Cmd [0] = 0x55; //0x75
			Scan.Barcode_Reader_Stop_Cmd [0] = 0x0D;
			Scan.Barcode_Reader_Stop_Cmd [0] = '\0';
		}
		Read_Barcode_Format_Configuration();
		delay_ms (1000);
		startkeywait(1,1);
}



/**********************************************************************************************************************
	* File Name     :  Read_ICT_Set
	* Description   :  ��ȡICT������Ϣ
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
void Read_Scan_Configration(void){
		Scan.Mode = (Scan_Mode)Reg[ScanMode].Value ; 
		if(Scan.Mode == Normal)
				Read_Barcode_Reader_Configuration();
		delay_ms (200);
}
/**********************************************************************************************************************
	* File Name     :  Barcode_Format_Check
	* Description   :  �����ʽ����,�����ʽC46******XYZ*******
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2019/3/23
************************************************************************************************************************/
static uint8_t Barcode_Format_Check(char *Barcode,uint8_t Barcode_Legnth){
	uint8_t i,L = Barcode_Legnth ;
	//������볤���Ǻ��лس�����
	if(strchr(Barcode,0x0D))  L ++;
	if(strchr(Barcode,0x0A))	L ++;
	if(strlen (Barcode) != L ){
		cyc4or3run ();
		lcd_printf ("���볤��:%2d     ",strlen (Barcode));
		lcdpos(lcdcon-1,14);
		lcd_printf ("NG");
		cyc4or3run ();
		lcd_printf ("��׼����:%2d     ",Barcode_Legnth);
		return False;
	}
	for( i = 0 ;i < Barcode_Legnth ; i ++){
		if(Scan.Barcode_Format[i] != '*' && Barcode[i] != Scan.Barcode_Format[i]){
			cyc4or3run ();
			lcd_printf ("�����ʽNG      ");
			cyc4or3run ();
			lcd_printf ("%s",Scan.Barcode_Format);
			return False;
		}else if((Barcode[i] >='A'&&Barcode[i]<='Z')||
		         (Barcode[i] >='a'&&Barcode[i]<='z')||
						 (Barcode[i] >='0'&&Barcode[i]<='9')){
			continue ;
		}
		return False;				 
	}
	return True;
}
/*****************************************************************
	* File Name     : BarcodeFormat_Set                      
	* Description   : BarcodeFormat_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
uint8_t BarcodeReaderTrigger( char *buf){
	
		if(Scan.USARTx == USART1)
				uart1_init(Scan.Barcode_Reader_Baud);
		else if(Scan.USARTx == USART2)
				uart2_init(Scan.Barcode_Reader_Baud);
		else if(Scan.USARTx == USART3)
				uart3_init(Scan.Barcode_Reader_Baud);
		if( Scan.Barcode_Reader_Type == KEYENCE){
				if(Get_USART_buffer( Scan.USARTx, Scan.Barcode_Reader_Start_Cmd, buf, Scan.Time) == 0){
						Uart_printf( Scan.USARTx, Scan.Barcode_Reader_Stop_Cmd);//���ͻ���ʿɨ������
						return False;
				}					
		}else if(Scan.Barcode_Reader_Type == Infoscan){
			//Uart_lcd_printf(Scan.USARTx, "%c%c%c",0x16,0x74,0x0D);	//�����Ͼ�����ɨ������					
				Uart_printf(Scan.USARTx,"%c%c%c",0x16,0x54,0x0D);	//�����Ͼ�����ɨ������	
				if(Get_USART_buffer( Scan.USARTx, buf, buf,Scan.Time) == 0){
						Uart_printf(Scan.USARTx,"%c%c%c",0x16,0x75,0x0D);	//�����Ͼ�����ɨ������	
						delay_ms (10);
						Uart_printf(Scan.USARTx,"%c%c%c",0x16,0x55,0x0D);	//�����Ͼ�����ɨ������
						return False;					
				}
		}else{
			cyc4or3run ();
			lcd_printf ("ɨ��ǹ�ͺ�NG");
			return False;	
		}
		return True ;
}

/**********************************************************************************************************************
	* File Name     :  Software_Trigger_Scan
	* Description   :  �������ɨ��
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2018/8/14
************************************************************************************************************************/
uint8_t Software_Trigger_Scan(void){
		char rec_buf[128];
		memset (rec_buf,0,128);
		if(BarcodeReaderTrigger(rec_buf)== False)
			return False ;
		strcpy (Scan.Barcode_Buffer, rec_buf);
		cyc4or3run();
		lcd_printf ("%s",Scan.Barcode_Buffer);
		if(Scan.Barcode_Check == ENABLE){
				if(Barcode_Format_Check(Scan.Barcode_Buffer,Scan.Barcode_Length)== False )
					return False;
		}
		if(Fixture.Software == ZDT_Software  )
					Uart_printf ( Fixture.Comm_Uart, "*%s@",Scan.Barcode_Buffer ); //�ϴ������PC
		else if(Fixture .Software == WTB_Software ){
			if(strstr (Scan.Barcode_Buffer,"\r\n"))
				Uart_printf ( Fixture.Comm_Uart, "SN:%s",Scan.Barcode_Buffer ); //�ϴ������PC
			else
				Uart_printf ( Fixture.Comm_Uart, "SN:%s\r\n",Scan.Barcode_Buffer ); //�ϴ������PC
		}
		cyc4or3run ();
		lcd_printf ("ɨ��OK          ");
		return True;
}


/*****************************************************************
	* File Name     : Scan_Push_Privious_Or_Next                      
	* Description   : Scan_Push_Privious_Or_Next                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
void Scan_Push_Privious_Or_Next(void)
{
	char Name[2][17] = {"ѹ��ǰɨ��","ѹ�Ϻ�ɨ��"};
	Fixture.Scan_Way  =Reg[ScanAndPush].Value ; 
	Choice_Menu("ɨ��ʱ������",Name,2, &(Fixture.Scan_Way));	
	Reg[ScanAndPush].Value  = Fixture.Scan_Way;
	Save_Single_Reg_Value (ScanAndPush);	
}
/*****************************************************************
	* File Name     : Scan_Time_Set                      
	* Description   : Scan_Time_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void Scan_Time_Set(void){
	Scan.Time                 = Reg[ScanTime].Value  ;	
	Choice_Menu_Num("ɨ��ʱ������    ",1000,20000,500,&Scan.Time,"ms    ");
	Reg[ScanTime].Value  =  Scan.Time ;		
	Save_Single_Reg_Value (ScanTime);	
}

/*****************************************************************
	* File Name     : BarcodeMode_Set                      
	* Description   : BarcodeMode_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeMode_Set(void){

	uint8_t Mode =Reg[ScanMode].Value;	
	Choice_Menu("����ģʽ����:   ",Scan_Mode_Menu,5,&Mode);
	Scan.Mode = (Scan_Mode)Mode;
	Reg[ScanMode].Value = Scan.Mode;
	Save_Single_Reg_Value (ScanMode);
	
}
/*****************************************************************
	* File Name     : BarcodeReader_Set                      
	* Description   : BarcodeReader_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeReader_Set(void){
		Scan.Barcode_Reader_Type  = Reg[BarcodeReader].Value ;	
		Choice_Menu("ɨ��ǹ��������  ",BarcodeReader_Name,2,&Scan.Barcode_Reader_Type);	
		Reg[BarcodeReader].Value = Scan.Barcode_Reader_Type ;
		Save_Single_Reg_Value (BarcodeReader);		
}

/*****************************************************************
	* File Name     : BarcodeReaderBauds_Set                      
	* Description   : BarcodeReaderBauds_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeReaderBauds_Set(void){
		uint8_t Baud_bit = 0,i=0;
		char  Baud_Choice[8][17]   = {"    9600bps     ","    19200bps    ","    38400bps    ",
															   	"    57600bps    ","    76800bps    ","    115200bps   "};
		uint32_t Baud_Rate[8] = {9600,19200,38400,57600,76800,115200 };

		
		Scan.Barcode_Reader_Baud  = Reg[BarcodeReaderBPS].Value ;
		for( i = 0; i < 6 ; i ++){
			if(Scan.Barcode_Reader_Baud == Baud_Rate[i]){
				Baud_bit = i; break ;
			}
		}
		Choice_Menu("����������      ",Baud_Choice,6,&Baud_bit);		
		Scan.Barcode_Reader_Baud = Baud_Rate [Baud_bit];
		Reg[BarcodeReaderBPS].Value = Baud_Rate [Baud_bit] ;
		Save_Single_Reg_Value (BarcodeReaderBPS);			
}
/*****************************************************************
	* File Name     : BarcodeCheckEnable_Set                      
	* Description   : BarcodeCheckEnable_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeCheckEnable_Set(void){
	char Barcode_Check_Status[2][17] = {"      �ر�      ","      ����      "};
	Scan.Barcode_Check = Reg[BarcodeCheckEnable].Value  ;
	Choice_Menu("����������    ",Barcode_Check_Status,2,&Scan.Barcode_Check);	
	Reg[BarcodeCheckEnable].Value = Scan.Barcode_Check;
	Save_Single_Reg_Value (BarcodeCheckEnable);		
	
}
/*****************************************************************
	* File Name     : BarcodeLength_Set                      
	* Description   : BarcodeLength_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeLength_Set(void){
	uint32_t Length = Reg[BarcodeLength].Value;
	Choice_Menu_Num("���볤������    ", Reg[BarcodeLength].LSL,
																			Reg[BarcodeLength].USL,
																			Reg[BarcodeLength].Step_Length ,
																			&Length,"λ" );
	Scan.Barcode_Length = Length;
	Reg[BarcodeLength].Value = Scan.Barcode_Length;
	Save_Single_Reg_Value (BarcodeLength);
}

/*****************************************************************
	* File Name     : BarcodeFormat_Set                      
	* Description   : BarcodeFormat_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeFormat_Set(void){
	uint8_t i = 0;
	Read_Barcode_Format();
	Scan.Barcode_Format[Scan.Barcode_Length] = '\0';
	String_Set_Fun("�����ʽ����    ",Reg[BarcodeFormat].Addr,(char *)Scan.Barcode_Format,Scan.Barcode_Length);
	for( i = 0 ; i < Scan.Barcode_Length ; i ++ ){
		AT24CXX_WriteLenByte (Reg[BarcodeFormat].Addr+i,Scan.Barcode_Format[i],1);
	}
}

/*****************************************************************
	* File Name     : BarcodeFormat_Set                      
	* Description   : BarcodeFormat_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020                             
*****************************************************************/ 
void BarcodeReaderTriggerTest(void){
		char rec_buf[128],KeyValue = 0;
		uint8_t Length = 0;
		lcdreset ();
		lcdpos(3,0); lcd_printf ("L:����  R:�˳� ");
		while(1){
			startkeywait (1,1);
			KeyValue = Get_start_key_val ();
			if(KeyValue == Left_Button_Pressed_Down ){
					lcdpos(0,0); lcd_printf ("ɨ��...          ");
					lcdpos (1,0); lcd_printf ("                ");
					lcdpos (2,0); lcd_printf ("                ");
					lcdpos(3,0); lcd_printf ("L:����  R:�˳� ");
					memset (rec_buf,0,128);
				  lcdpos (0,7);
					if(BarcodeReaderTrigger(rec_buf) == True){
							lcd_printf ("OK");
							Length = strlen (rec_buf);
							if(strstr(rec_buf,"\r"))
								Length --;
							if(strstr(rec_buf,"\n"))
								Length --;
							lcdpos (1, 0); lcd_printf ("%s",rec_buf);
							lcdpos (0,12); lcd_printf ("%2dλ",Length);
					}else{
						  lcd_printf ("NG");
					}
			}else if(KeyValue == Right_Button_Pressed_Down ){
				 break ;
			}
		}
}

Menu_List_Typedef Scan_List[] = 
{
	{"ɨ�跽ʽ������",BarcodeMode_Set            },
	{"ɨ��ʱ��      ",Scan_Push_Privious_Or_Next },
	{"ɨ��ǹ�ͺ�    ",BarcodeReader_Set          },	
	{"ɨ�貨����  ��",BarcodeReaderBauds_Set     },
	{"ɨ��ʱ��      ",Scan_Time_Set              },	
	{"ɨ�����      ",BarcodeReaderTriggerTest   },
	{"�����顡����",BarcodeCheckEnable_Set     },
	{"���볤�ȡ�����",BarcodeLength_Set          },	
	{"�����ʽ������",BarcodeFormat_Set          },		
	{NULL }
};

/*********************************************************************************************
  * File Name     : Scan_Set
	* Description   : Scan_Set
  * Input         : /
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 16-April-2020   
*********************************************************************************************/
uint8_t Scan_Set(void){
	if(Fixture.Mech_Struct == SmallFixture)
		Menu_List_Fun("ɨ������",Scan_List);	
	else {
		lcdreset ();
		lcdpos (2,0); lcd_printf("ɨ��������");
		step_test_mode_get_key ();
		return 1;
	}
	RevertStartupScreen();
	return 1;
}


