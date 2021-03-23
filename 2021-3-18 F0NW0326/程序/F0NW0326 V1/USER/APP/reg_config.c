#include "barcode.h"
#include "other.h"
#include "hold_data.h"
#include "reg.h"
#include "lcd3033.h"
#include "24cxx.h" 
#include "delay.h"
#include "menu.h"
#include "reg.h"
#include "wtb.h"
#include "eth_config.h"
#include "base_Config.h"
#include "24cxx.h" 
#include "ad5933.h"
#include "global.h"
#include "test_config.h"
//#define Debug_Mode





const  uint8_t  version[10]           = {"V1  "};
uint8_t           filename[17]        = {"F0NW0326 FCT  "};
const  uint8_t  defult_Date[17]       = {"     2021.3.20 "};
//const  uint8_t  defult_filename[17] = {"FTSL0309     FCT"};

/*************** �޸�����**********************************
2020.11.16 V1 �������




************************************************************/



Server_Def  ETH_default_Config = {
  SET,
	3,//TCP_Server
	{100,  1, 1,  30 },
	{255,255, 255,  0},
	{100,  1, 1,    0},
	8233,
	USART1,
	9600,
	115200
}	;

Scan_Type_def Scan = {
		USART3,        
	  False,
		3000,
		No_Barcode,  
		KEYENCE,
		9600,
		DISABLE ,
		17,	
		"C46**************",
		"C46**************",		
		"LON\r\n",		
		"LOFF\r\n",    
		"*START!",
};



ACT_Parameter_Def ACT_Parameter[] = {

 //  ����-------���� ------     �׵�ַ       ����        ����                 ����     ����     ����0     Ĭ��0      
	 { 0,   "���µ�׿���    " ,   0x1110,        1,    U8_Type ,                 1,       0,       0 ,       0,  }, 
	 { 1,   "���µ���ٶ�    " ,   0x1120,       10,    Double_Type,            400,     100,      200,     200,  }, 
	 { 2,   "���µ�״���λ  " ,   0x1130,     0.15,    Double_Type ,           102,      -2,       0 ,      10,  }, 
   { 3,   "���µ�׺�ģλ  " ,   0x1140,     0.15,    Double_Type ,           102,      80,      60 ,      80,  }, 
	 { 4,   "ElecUpDown_U    " ,   0x1150,     0.15,    Double_Type ,           102,    -102,       0 ,       0,  }, 
   { 5,   "ElecUpDown_D    " ,   0x1160,     0.15,    Double_Type ,           102,    -102,       0 ,      80,  }, 
	 { 6,   "���Ͽ���        " ,   0x1170,        1,    U8_Type ,                 1,       0,       0 ,       0,  }, 
	 { 7,   "���ϲ���Ʒ����  " ,   0x1180,        1,    U8_Type ,                 1,       0,       0 ,       0,  }, 
	 { 7,   "�Ƿ�����ѹ����  " ,   0x1185,        1,    U8_Type ,                 1,       0,       0 ,       0,  }, 	 
	 { 8,   "��Ʒ��          " ,   0x1190,        1,    U8_Type ,                10,       1,       0 ,       1,  }, 
	 { 9,   "����Ʒ��        " ,   0x11A0,        1,    U8_Type ,                 4,       1,       0 ,       1,  }, 
	 {10,   "���ϵ���ٶ�    " ,   0x11B0,       10,    Double_Type ,           500,     200,       0 ,     300,  }, 	 
   {11,   "�������ϵ�      " ,   0x11C0,     0.15,    Double_Type ,           100,       0,      10 ,      10,  }, 
   {12,   "���ô�����      " ,   0x11E0,      1.5,    Double_Type ,           300,      80,      50 ,      50,  }, 
   {13,   "����NG��1       " ,   0x11F0,      1.5,    Double_Type,            300,      80,      50 ,      50,  }, 
   {14,   "����NG��2       " ,   0x1200,      1.5,    Double_Type,            300,      80,      70 ,      70,  }, 
   {15,   "����NG��3       " ,   0x1210,      1.5,    Double_Type,            300,      80,      90 ,      90,  }, 
   {16,   "����NG��4       " ,   0x1220,      1.5,    Double_Type,            300,      80,     110 ,     110,  }, 
   {17,   "����OK��1       " ,   0x1230,      1.5,    Double_Type,            400,     150,     130 ,     130,  }, 
   {18,   "����OK��2       " ,   0x1240,      1.5,    Double_Type,            400,     150,     150 ,     150,  }, 
   {19,   "����OK��3       " ,   0x1250,      1.5,    Double_Type,            400,     150,     170 ,     170,  }, 
   {20,   "����OK��4       " ,   0x1260,      1.5,    Double_Type,            400,     150,     190 ,     190,  }, 
   {21,   "����OK��5       " ,   0x1270,      1.5,    Double_Type,            400,     150,     210 ,     210,  }, 
   {22,   "����OK��6       " ,   0x1280,      1.5,    Double_Type,            400,     150,     230 ,     230,  }, 
   {23,   "����OK��7       " ,   0x1290,      1.5,    Double_Type,            400,     150,     250 ,     250,  }, 
   {24,   "����OK��8       " ,   0x12A0,      1.5,    Double_Type,            400,     150,     270 ,     270,  }, 
	 { 0,    NULL ,                     0,        0,             0 ,              0,       0,        0,       0   },
};                                   
 



Parameter_Typedef  Reg[] = {         
	//**���****����*******    ****�洢��ַ****�ֽ���*********����******USL******LSL******Value*****default_Value
	
	{ 0,        "�ξ�����    ",      0x0000,       U8_Type,     1,      255,      0,        0,         0    },	
	{ 1,        "�ξ߹�λ��  ",      0x0010,       U8_Type,     1,        4,      1,        1,         1    },
	{ 2,        "ģ��ʶ��    ",      0x0018,       U8_Type,     1,        1,      0,        1,         1    },	
	{ 3,        "������      ",      0x0020,       U32_Type,    4,    60000,      0,        0,         0    },
	{ 4,        "��Ʒ��      ",      0x0030,       U32_Type,    4,    60000,      0,        0,         0    },	
	                                                                                                       
	{ 5,        "���ʹ��    ",      0x0040,       U32_Type,    1,        1,      0,        0,         0    },
	{ 6,        "���ʼ��  ",      0x0048,       U32_Type,    1,        1,      0,        0,         0    },		
	{ 7,        "���ʱ��    ",      0x0050,       U32_Type,  100,     2000,    300,        0,       800    },	
	{ 8,        "�Ѵ�����  ",      0x0060,       U32_Type,   10,    60000,      0,        0,         0    },	
	{ 9,        "��������  ",      0x0070,       U32_Type,   10,    60000,      0,        0,        10    },	
	                                                                                                       
	{10,        "������ʾ    ",      0x0080,       U32_Type,    1,        1,      0,        0,         0    },
	{11,        "����ʱ��    ",      0x0090,       U32_Type,    1,     1440,      1,        0,       120    },	
	                                                                                                       
	{12,        "ָ����ʱ    ",      0x00A0,       U32_Type,  100,    20000,    500,        0,      3000    },
	{13,        "�����ӳ�    ",      0x00A8,       U32_Type,   50,     5000,    300,        0,       600    },	
	                                                                                                       
	{14,        "ɨ��ʱ��    ",      0x00B0,       U32_Type,    1,        1,      0,        0,         0    },		
	{15,        "ɨ��ʱ��    ",      0x00C0,       U16_Type,  100,    10000,    500,     3000,      3000    },
	{16,        "ɨ�跽ʽ    ",      0x00D0,        U8_Type,    1,        4,      0,        1,         1    },	
	{17,        "ɨ��ǹ�ͺ�  ",      0x00D8,        U8_Type,    1,        1,      0,        0,         0    },		
	{18,        "ɨ��ǹ������",      0x00E0,       U32_Type,    1,   115200,   9600,     9600,      9600    },
	{19,        "������    ",      0x00E8,        U8_Type,    1,        1,      0,        0,         0    },
	{20,        "���볤��    ",      0x00F0,        U8_Type,    1,       32,      1,       17,        17    },
	{21,        "�����ʽ    ",      0x0100,        U8_Type,    1,      255,      0,        0,         0    },
	                                                                                                       
	{22,        "����ģʽ    ",      0x0120,       U8_Type,     1,        3,      0,        0,         3    },
	                                                                                                       
	{23,        "����IP      ",      0x0130,       U8_Type,     1,      255,      0,      100,       100    },	
	{24,        "����IP      ",      0x0131,       U8_Type,     1,      255,      0,        1,         1    },	
	{25,        "����IP      ",      0x0132,       U8_Type,     1,      255,      0,        1,         1    },	
	{26,        "����IP      ",      0x0133,       U8_Type,     1,      255,      0,       10,        10    },	
	                                                                                                       
	{27,        "������������",      0x0140,       U8_Type,     1,      255,      0,      255,       255    },
	{28,        "������������",      0x0141,       U8_Type,     1,      255,      0,      255,       255    },
	{29,        "������������",      0x0142,       U8_Type,     1,      255,      0,      255,       255    },
	{30,        "������������",      0x0143,       U8_Type,     1,      255,      0,        0,         0    },
	                                                                                                       
	{31,        "��������    ",      0x0150,       U8_Type,     1,      255,      0,      100,      100    },
	{32,        "��������    ",      0x0151,       U8_Type,     1,      255,      0,        1,        1    },
	{33,        "��������    ",      0x0152,       U8_Type,     1,      255,      0,        1,        1    },
	{34,        "��������    ",      0x0153,       U8_Type,     1,      255,      0,        0,        0    },
	                                                                                                       
	{35,        "����˿ں�  ",      0x0160,      U32_Type,     1,   500000,      0,     8233,      8233    },	
	                                                                                                       
	{36,        "pF���ݲ���  ",      0x0170,   Double_Type,     4,     2000,      0,        0,         0    },
	{37,        "pF���ݲ���  ",      0x0178,   Double_Type,     4,     2000,      0,        0,         0    },
	{38,        "pF���ݲ���  ",      0x0180,   Double_Type,     4,     2000,      0,        0,         0    },
	{39,        "pF���ݲ���  ",      0x0188,   Double_Type,     4,     2000,      0,        0,         0    },
	{40,        "pF���ݲ���  ",      0x0190,   Double_Type,     4,     2000,      0,        0,         0    },
	{41,        "pF���ݲ���  ",      0x0198,   Double_Type,     4,     2000,      0,        0,         0    },
	{42,        "pF���ݲ���  ",      0x01A0,   Double_Type,     4,     2000,      0,        0,         0    },
	{43,        "pF���ݲ���  ",      0x01A8,   Double_Type,     4,     2000,      0,        0,         0    },
	
	{45,        "�������ٶ�",      0x01B8,      U32_Type,    10,      300,     30,        0,       100    },
	{46,        "���̧���ٶ�",      0x01C0,      U32_Type,    10,      300,     30,        0,       200    },
	{47,        "�������λ��",      0x01C8,   Double_Type,     1,       40,      0,        0,        20    },
	{48,        "������λ��",      0x01D0,   Double_Type,   0.1,       40,      0,        0,        40    },
	{49,        "���̧��λ��",      0x01D8,   Double_Type,     1,       40,      0,        0,         2    },
	{50,        "���λ��1   ",      0x01E0,   Double_Type,     4,       40,      0,        0,         0    },

	
  { 0,        NULL,                     0,             0,     0,        0,      0,        0,         0    },	
};                                                                                                       
                                                                                                         




/*****************************************************************
	* File Name     : Save_Reg_data                      
	* Description   : Save_Reg_data                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
void Save_Single_Reg_Value(uint8_t Num ){
		uint32_t dat = 0;
		if(Reg[Num].Value > Reg[Num].USL || Reg[Num].Value < Reg[Num].LSL )
		{
			Reg[Num].Value = Reg[Num].default_Value ;
			Uart_printf (USART1,"%s: Error --->%f:(%f,%f)\r\n",Reg[Num].Name,Reg[Num].Value ,Reg[Num].LSL ,Reg[Num].USL ); 
		}
		if(Reg[Num].Byte_Length <= 4 ){
			dat = (uint32_t )Reg[Num].Value  ;
			AT24CXX_WriteLenByte(Reg[Num].Addr,dat,Reg[Num].Byte_Length);	
		}else if(Reg[Num].Byte_Length == Double_Type ){
				Write_double_data(Reg[Num].Addr,Reg[Num].Value );
				if(read_double_data(Reg[Num].Addr) != Reg[Num].Value){
					cyc4or3run ();
					lcd_printf ("reg_W error=%d",Num );
					while(1);
				}
		}else{
			Uart_printf (USART1,"Data  NO Write%s: Error --->%f:(%f,%f)\r\n",Reg[Num].Name,Reg[Num].Value ,Reg[Num].LSL ,Reg[Num].USL ); 
		}
}


/*****************************************************************
	* File Name     : Save_Reg_data                      
	* Description   : Save_Reg_data                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
double  Read_Signal_Reg_Value(uint8_t Num ){
	if(Reg[Num].Byte_Length <=4 )
		{
				Reg[Num].Value =  AT24CXX_ReadLenByte(Reg[Num].Addr,Reg[Num].Byte_Length);
			
				if(Reg[Num].Value  > Reg[Num].USL || Reg[Num].Value < Reg[Num].LSL )
				{
					Reg[Num].Value = Reg[Num].default_Value ;
					Save_Single_Reg_Value(Num);
				}
				
		}else if(Reg[Num].Byte_Length == Double_Type ){
			
			  Reg[Num].Value = read_double_data(Reg[Num].Addr) ;
			
				if(Reg[Num].Value > Reg[Num].USL || Reg[Num].Value < Reg[Num].LSL )
				{
					Reg[Num].Value = Reg[Num].default_Value ;
					Save_Single_Reg_Value(Num);
				}
		}
		return Reg[Num].Value;
}



/*********************************************************************************************
	* File Name     : clear_counter
	* Description   : clear Conter
  * Input         : ��
  * return        : �� 
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/ 
uint8_t clear_counter(){

	
	Reg[Total_Num].Value = 0;
	Reg[PASS_Num].Value = 0;
	Save_Single_Reg_Value(Total_Num );
	Save_Single_Reg_Value(PASS_Num );
	
	lcdreset ();
	lcdpos (1,0);
	lcd_printf  ("    �������    ");
	RevertStartupScreen();
	return 0;
}
/*****************************************************************************************************************
	* File Name     :  Display_Total_Rate
	* Description   :  ��ʾTOTAL��RATE
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  24-June-2019
*****************************************************************************************************************/
void Display_Total_Rate(){
		float Rate;
		Save_Single_Reg_Value(Total_Num );
		Save_Single_Reg_Value(PASS_Num );
		if(Reg[Total_Num].Value >0 )
				Rate=Reg[PASS_Num].Value/Reg[Total_Num].Value*100.0 ;
		else
				Rate = 0.0;		
		cyc4or3run();
		lcd_printf  ("T=%5d,P=%5.1f%c",(uint32_t)Reg[Total_Num].Value,Rate,'%');	
}


/**********************************************************************************************************************
	* File Name     :  Read_System_Name
	* Description   :  ��ȡ�Ϻ���
  * Input         :  ��
  * return        :  ��
	* Author        :  Morton
	* Date          :  2019/3/14
************************************************************************************************************************/
void Read_System_Name( void ){
		uint8_t ch[16],i;
		AT24CXX_Read(Reg[Fixture_Name].Addr ,ch,16);
		for ( i = 0 ; i < 16 ; i ++){
				if(ch[i] >= 0x10 && ch[i] <= 0x7F){
						continue ;
				}
				else {
					AT24CXX_Write(Reg[Fixture_Name].Addr,filename,16);
					return ;
				}
		}
		for ( i = 0; i < 16; i ++){
				filename[i] =ch[i];
		}
}
/**********************************************************************************************************************
 	* File Name     :  System_Name_Set_Fun
 	* Description   :  �Ϻ�������
  * Input         :  ��
  * return        :  ��
 	* Author        :  Morton
 	* Date          :  2019/3/14
************************************************************************************************************************/
unsigned char System_Name_Set_Fun(){
//		uint8_t i,ch[16];
//		AT24CXX_Read(Reg[Fixture_Name].Addr,ch,16);
//		for ( i = 0 ; i < 16 ; i ++){
//				filename [i] = ch[i] ;
//		}
//		lcdreset ();
//		cyc4or3run ();
//		lcd_printf ("��ǰ�Ϻ���:     ");
//		cyc4or3run ();
//		lcd_printf ("%s",filename); //defult_filename
//		cyc4or3run ();
//		lcd_printf ("L:�ָ�Ĭ��      ");
//		cyc4or3run ();
//		lcd_printf ("R:�޸ĵ�ǰ����  ");
//		if(Get_start_key_val()== Left_Button_Pressed_Down ){
//			for ( i = 0 ; i < 16 ; i ++){
//					filename [i] = defult_filename[i] ;
//			}
//		}
//		String_Set_Fun("�Ϻ�����",Reg[Fixture_Name].Addr,(char *)filename,16);
//		RevertStartupScreen();
		return 0;
}
#include <string.h>
#include <stdlib.h>
/**********************************************************************************************************************
 	* File Name     :  Get_Compile_Time
 	* Description   :  Get_Compile_Time
  * Input         :  ��
  * return        :  ��
 	* Author        :  Morton
 	* Date          :  2020/Jun/8
************************************************************************************************************************/
void Get_Compile_Time(char *Compile_Date)
{
	uint16_t Year,Month,Day;
  const char *pMonth[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};  
  const char Date[12] = __DATE__;//ȡ����ʱ�� 
  uint8_t i;
  for(i = 0; i < 12; i++)
  if(memcmp(Date, pMonth[i], 3) == 0)
	  Month = i + 1, i = 12;
  Year = (uint16_t)atoi(Date + 7); //Date[9]Ϊ��λ��ݣ�Date[7]Ϊ�������
  Day = (uint8_t)atoi(Date + 4);
	sprintf (Compile_Date,"%d.%d.%d",Year,Month,Day);
//Jun  8 2020
}
/**********************************************************************************************************************
 	* File Name     :  RevertStartupScreen
 	* Description   :  ��ԭĬ�ϲ��Խ���
  * Input         :  ��
  * return        :  ��
 	* Author        :  Morton
 	* Date          :  2019/3/14
************************************************************************************************************************/
void RevertStartupScreen(void){
		uint8_t ip[4];
		char date[12];
	  Get_Compile_Time(date);
		lcdreset  ();
		cyc4or3set(4);
		cyc4or3run();
		lcd_printf("%s",filename);	
		cyc4or3run();
		lcd_printf("%s%s",version,date);	
		cyc4or3run();
		if(Fixture.Software == WTB_Software ){
			Set_Test_Satation(Reg[FixtureNumber].Value);
			if(Fixture.Comm_Mode == __ETH){
					Get_ETH_ip_Addr(ip);
					lcd_printf ("��λ%d %d.%d.%d.%d",Get_TEST_Station(),ip[0],ip[1],ip[2],ip[3]);
			}else if(Fixture.Comm_Mode == __USART){
					lcd_printf ("��λ-%d WTB��λ��",Get_TEST_Station());
			}
		}
		if(Fixture.Software == ZDT_Software ){
			 lcd_printf("��λ��: V4.29.3 ");
		}
		Display_Total_Rate();
}

/*********************************************************************************************
	* File Name     : WriteETHPar
	* Description   : Write ETH  configration parameter to EEROM 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
void Write_ETH_Parameter_To_EEPROM( Server_Def *p){
	int i= 0;
	if(p->Mode < 4)
			AT24CXX_WriteLenByte (Reg[ETH_Mode].Addr ,p->Mode,1);
	else{
		p->Mode  = 3;
		AT24CXX_WriteLenByte (Reg[ETH_Mode].Addr ,p->Mode,1);
	}
	for( i = 0; i < 4 ;i ++){
		AT24CXX_WriteLenByte (Reg[ETH_IP].Addr +i, p->ipaddr.Num[i], 1);
	}
	for( i = 0; i < 4 ;i ++){
		AT24CXX_WriteLenByte (Reg[ETH_Netmask].Addr+i, p->netmask.Num[i], 1);
	}	
	for( i = 0; i < 4 ;i ++){
		AT24CXX_WriteLenByte (Reg[ETH_GATEWAY].Addr+i, p->GATEWAY .Num[i], 1);
	}		
	AT24CXX_WriteLenByte (Reg[ETH_PortNum].Addr, p->PortNumber, 4);
}
/*********************************************************************************************
	* File Name     : ReadETHPar
	* Description   : Read ETH  configration parameter from EEROM 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
uint8_t Read_ETH_Parameter_From_EEPROM(Server_Def  *p ){
	int i= 0,Error_Flag = RESET;
	Server_Def Save;
	Save.Mode = AT24CXX_ReadLenByte(Reg[ETH_Mode].Value,1);
	if(Save.Mode >= 4){
		Save.Mode  = 3;
		AT24CXX_WriteLenByte (Reg[ETH_Mode].Value,Save.Mode,1);
	}
	if(Save.Mode != p->Mode)
			Error_Flag = SET;
	
	for( i = 0; i < 4 ;i ++){
		Save.ipaddr.Num[i] = AT24CXX_ReadLenByte(Reg[ETH_IP].Addr+i,1);
		if(Save.ipaddr.Num[i] != p->ipaddr.Num[i])
			Error_Flag = SET;
	}
	for( i = 0; i < 4 ;i ++){
		Save.netmask.Num[i] = AT24CXX_ReadLenByte(Reg[ETH_Netmask].Addr+i,1);
		if(Save.netmask.Num[i] != p->netmask.Num[i])
			Error_Flag = SET;
	}	
	for( i = 0; i < 4 ;i ++){
		Save.GATEWAY.Num[i] = AT24CXX_ReadLenByte(Reg[ETH_GATEWAY].Addr+i,1);
		if(Save.GATEWAY.Num[i] != p->GATEWAY.Num[i])
			Error_Flag = SET;
	}	
	Save.PortNumber = AT24CXX_ReadLenByte(Reg[ETH_PortNum].Addr,4);
	if(Save.PortNumber != p->PortNumber)
		Error_Flag = SET;
	
	return Error_Flag;
}

/*********************************************************************************************
	* File Name     : Read_pF_Capacitor_offset
	* Description   : Read_pF_Capacitor_offset
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/

void Read_pF_Capacitor_offset( uint8_t En){
		u8 j; 
		double offset = 0.0;
		uint16_t Total_Num,Item_Step_Number = 0,buf[32];
		Total_Num = Get_Currennt_Type_CNT(Type_pF_Cap,buf,32 );
		if(Total_Num == 0){
			return ;
		}
		if(En == ENABLE)
				AD5933_Initalize();
		for( j = 0; j < Total_Num ; j ++){
			 Item_Step_Number = buf[j];
			 offset = read_double_data(Reg[pF_Offset].Addr + j*8);
				if(offset > 10000 || offset < 0.0){
					offset = 0;
					Write_double_data (Reg[pF_Offset].Addr + j*8,offset);
				}
			Item_Data[Item_Step_Number].offset  = offset;
			if(left_start_key ==0||right_start_key ==0){
			 cyc4or3run ();
			 lcd_printf("%s=%7.3f%s    ",	Item[Item_Step_Number].Name,Item_Data[Item_Step_Number].offset,Item[Item_Step_Number].Unit );
			}
		}
}
/*********************************************************************************************
	* File Name     : Write_pF_Capacitor_offset
	* Description   : Write_pF_Capacitor_offset
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
void Write_pF_Capacitor_offset(void){
		u8 j; 
		double offset = 0.0;
		uint16_t Total_Num,Item_Step_Number = 0,buf[32];
		Total_Num = Get_Currennt_Type_CNT(Type_pF_Cap,buf,32 );
		if(Total_Num == 0){
			cyc4or3run ();
			lcd_printf ("�޴������      ");
			return ;
		}
		for( j = 0; j < Total_Num ; j ++){
			 Item_Step_Number = buf[j];
			 offset = Item_Data[Item_Step_Number].offset ;
			 Write_double_data (Reg[pF_Offset].Addr + j*8,offset);
		}
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
void  Read_All_Reg_Value( uint8_t En){
	uint8_t i;
	if(En == ENABLE)
		Uart_printf (USART1 ,"\r\n//**���****����*******    ****�洢��ַ****�ֽ���******����******USL******LSL******Value*****default_Value\r\n");

	for( i = 0 ; Reg[i].Name; i ++)
	{
		if(Reg[i].Byte_Length <=4 )
		{
				Reg[i].Value =  AT24CXX_ReadLenByte(Reg[i].Addr,Reg[i].Byte_Length);
			
				if(Reg[i].Value  > Reg[i].USL || Reg[i].Value < Reg[i].LSL )
				{
					Reg[i].Value = Reg[i].default_Value ;
					Save_Single_Reg_Value(i);
				}
		}else if(Reg[i].Byte_Length == Double_Type ){
			
			  Reg[i].Value = read_double_data(Reg[i].Addr) ;
			
				if(Reg[i].Value > Reg[i].USL || Reg[i].Value < Reg[i].LSL )
				{
					Reg[i].Value = Reg[i].default_Value ;
					Save_Single_Reg_Value(i);
				}	
		}
		if(En == ENABLE) 
			Uart_printf (USART1 ,"%2d       %s          0x%04X  %4d      %7.0f      %7.1f      %7.1f       %7.1f      %7.1f\r\n",Reg[i].Num ,Reg[i].Name ,Reg[i].Addr ,Reg[i].Byte_Length ,Reg[i].Step_Length ,Reg[i].USL ,Reg[i].LSL ,Reg[i].Value ,Reg[i].default_Value );
	
	}
	if(TestConfig.Component == ENABLE )
			Read_pF_Capacitor_offset( !En);
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
void  Reset_All_Reg_Value(void)
{
	uint8_t i = 0;
	for( i = 0 ; Reg[i].Name; i ++){
			Reg[i].Value = Reg[i].default_Value ;
			Save_Single_Reg_Value(i);				
	}	
}
