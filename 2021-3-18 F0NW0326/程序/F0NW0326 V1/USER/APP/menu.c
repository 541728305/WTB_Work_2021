#include "menu.h"
#include "other.h"
#include "lcd3033.h"
#include "24cxx.h"
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
#include "id.h"
#include "usb_move.h"


mode_fun_def _Test_Mode[] = {
//--编号--------名称-------------函数名--------*********-------使能位---密码保护	
	
	
	{ 1, "自动测试      ",   List_Auto_Test_Fun,                 ENABLE ,  DISABLE  },
	{ 2, "单步测试      ",   List_Step_Test_Fun,                 ENABLE ,  DISABLE  },
	{ 3, "清计数器      ",   clear_counter,                      ENABLE ,  DISABLE  },
	{ 4, "找点模式      ",   Search_Point_Function,              ENABLE ,  DISABLE  },
	{ 5, "扫码设置      ",   Scan_Set,                           ENABLE ,  DISABLE  },
	{ 6, "调试模式      ",   DebugMode,                          ENABLE ,  DISABLE  },	
//	{ 7, "上下电缸      ",   Up_Down_EACT_set,                   ENABLE ,  DISABLE  },	
//	{ 8, "脱料电缸      ",   Take_Product_EACT_set,              ENABLE , DISABLE  },					
//	{ 9, "打点设置      ",   Dot_Set,                            ENABLE ,  DISABLE  },
//	{10, "样本测提示    ",   Smaple_Notice_Set,                  ENABLE ,  DISABLE  },
	{11, "参数配置      ",   System_Parameter_Set,               ENABLE ,   DISABLE  },	
//	{14, "读取IC地址    ",   Read_IC_ID_Debug,                   ENABLE,   DISABLE  },
//	{14, "pF电容校准    ",   pF_Capacitor_Calibration_Fun,       ENABLE,   DISABLE  },
//	{14, "-USB电机设置  ",   USB_Move_Set,                       ENABLE,   DISABLE  },		

		
	{12, "软件调试      ",   Usmart_Debug_Fun,                   DISABLE ,  DISABLE  },
	{13, "料号名设置    ",   System_Name_Set_Fun,                DISABLE ,  DISABLE  },

	
	{15,  NULL ,             NULL,                                 DISABLE,  DISABLE  },
	
	//	{ 5, "电容校准      ",   Max_CAP_Calibration,                ENABLE , DISABLE  },	
};

/*********************************************************************************************
	* File Name     :Choice_Menu
	* Description   :菜单选择，Name设置名称，Menu菜单选项，MAX菜单最大长度，Current_Choice当前菜单选项
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2019/3/23
	* 修  改： /
*********************************************************************************************/
void Choice_Menu(	char *Name,
									char (*Menu)[17],
									uint8_t MAX,
									uint8_t *Current_Choice
								){
		uint8_t Choice_bit = *Current_Choice,Button_Status;
		if( *Current_Choice >= MAX)
				Choice_bit = 0;
		lcdreset ();
		lcdpos( 0,0); lcd_printf ("%s",Name);
		lcdpos( 1,0); lcd_printf ("%s",Menu[Choice_bit]);
		lcdpos( 3,0); lcd_printf ("L-选择  R-保存  ");
		while(1){
				Button_Status = Get_start_key_val();
				if(Button_Status==Left_Button_Pressed_Down ){
						Choice_bit ++;
						if(Choice_bit >= MAX )
								Choice_bit = 0;
				}
				if(Button_Status == Right_Button_Pressed_Down ){
						break ;
				}
				lcdpos(1,0); lcd_printf("%s",Menu[Choice_bit]);
				startkeywait  (1,1);
		}
		cyc4or3run ();  lcd_printf ("当前设置状态为: ");
		cyc4or3run ();  lcd_printf ("%s",Menu[Choice_bit]);
		*Current_Choice = Choice_bit;
		step_test_mode_get_key ();
}
/*********************************************************************************************
	* File Name     :Choice_Menu
	* Description   :菜单选择，Name设置名称，Menu菜单选项，MAX菜单最大长度，Current_Choice当前菜单选项
  * Input         :无
  * return        :无
	* Author        :Morton
	* Date          :2019/3/23
	* 修  改： /
*********************************************************************************************/
void Choice_Menu_Num(	char    *Name,
											uint32_t MIN, 
											uint32_t MAX,
											uint32_t Step_Length,
											uint32_t *Current_Value,
											char      *unit
								    ){
		uint8_t Button_Status;
		lcdreset ();
		lcdpos( 0,0); lcd_printf ("%s",Name);
		lcdpos( 1,0); lcd_printf ("%10d%s",*Current_Value,unit );
		lcdpos( 3,0); lcd_printf ("L:+ R:- L+R:SAVE");
		while(1){
				Button_Status = Get_start_key_val();
				if(Button_Status == Left_Button_Pressed_Down ){
						(*Current_Value) += Step_Length;
						if(*Current_Value > MAX || *Current_Value < MIN )
								*Current_Value = MAX ;
				}
				else if(Button_Status == Right_Button_Pressed_Down ){
						(*Current_Value) -= Step_Length;
						if(*Current_Value > MAX || *Current_Value < MIN )
								*Current_Value = MIN ;
				}if(Button_Status == Double_Button_Pressed_Down ){
					 break ;
				}
				lcdpos( 1,0); lcd_printf ("%10d%s",*Current_Value,unit );
		}
		cyc4or3run ();  lcd_printf ("当前设置值为:   ");
		cyc4or3run ();  lcd_printf ("%10d%s",*Current_Value,unit );
		step_test_mode_get_key  ();
}
/*********************************************************************************************
	* File Name     :Password_Input
	* Description   :密码输入函数
  * Input         :password 密码 Num 密码长度
  * return        :输入正确,返回结果
	* Author        :Morton
	* Date          :2018/11/18
*********************************************************************************************/
uint8_t Password_Input( char *password ,uint8_t Num ){
	uint8_t result ,i,Button_Status;
	char Input_word[16]; 
	lcdreset ();
	cyc4or3run ();
	lcd_printf ("请输入密码:     ");
	cyc4or3run ();
	for( i = 0 ;i < Num ; i ++){
		lcd_printf ("*");
		Input_word[i] = '*';
	}
	Input_word[i] = '\0';
	cyc4or3run ();
	lcd_printf ("L:设置  R:移位  ");
	cyc4or3run ();
	lcd_printf ("L+R:确认输入    ");
	i = 0; 
	lcdcon = 1;
	while(1){
		Button_Status = Getkey_Cursor(Input_word[i],lcdcon,i, ENABLE);
		if(Button_Status == Left_Button_Pressed_Down ){
			Input_word[i] ++;
			if(Input_word[i] <'0' || Input_word[i] > '9'){
				Input_word[i] = '0';
			}
		}else if(Button_Status == Right_Button_Pressed_Down ){		
			i ++;
			if(i >= Num )
				i = 0;		
			startkeywait  (1,1);
		}else if(Button_Status == Double_Button_Pressed_Down ){
				break ;
		}
	}
	cyc4or3run ();
	if(strcmp(Input_word,password) == 0){
		result = True ;

		lcd_printf ("密码正确      ");
	}else{
		result = False ;
		lcd_printf ("密码错误      ");	
		delay_ms (2000);
	}
	return result;
}
//返回值:  无  32-' ' 35-'#',42-'*',45-'-',46-'.',
//             48-57:'0'-'9'
//             64-'@'
//             65-90:'A'-'Z'
//             95-'_'
//             97-122:'a'-'z'
void char_Check(char *str){
		if(*str == 123)
				*str = 32 ;
		if(*str == 33)
			*str = 35;
		if(*str == 36)
			*str= 42;
		if(*str == 43)
			*str = 45;
		if(*str== 46)
			*str = 48;
		if(*str == 58)
			*str= 64;
		if(*str == 91)
			*str= 95;
		if(*str == 96)
			*str= 97;
}
/**********************************************************************************************************************
	* File Name     :  String_Set_Fun
	* Description   :  设置字符串,左键设置字符,右键下一个,左键+右键保存
  * Input         :  Item_Name,设置信息提示语,str 默认字符串
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/14
************************************************************************************************************************/
void  String_Set_Fun(char *Item_Name , uint16_t Addr, char *str, uint8_t Length ){
		uint8_t Button_Status = 0,cursor_position = 0;
		if(Length > 32)
				Length = 32;
		lcdreset();
		lcdpos (0,0);  lcd_printf( "%s",Item_Name);
	  lcdpos (1,0);  lcd_printf("%s",str);
//	  lcdpos (2,0); lcd_printf("L:SET  R:NEXT   ");
		lcdpos (3,0);   lcd_printf("L:S R:M L+R:SAVE");
		while(1){
			  Button_Status = Getkey_Cursor(str[cursor_position],cursor_position/16+1,cursor_position%16,ENABLE);
				//无按键操作,模拟光标闪烁
				if(Button_Status == Left_Button_Pressed_Down){ //合法字符从0x20-0x7F
						str[cursor_position] ++ ;    
						char_Check(&str[cursor_position]);
						lcdpos(cursor_position/16+1,cursor_position%16); lcd_printf( "%c",str[cursor_position]);
				}else if(Button_Status == Right_Button_Pressed_Down){
						cursor_position ++;
						if(cursor_position == Length) //循环到行末,从头开始
								cursor_position = 0x00;
						startkeywait  (1,1);
				}else if(Button_Status == Double_Button_Pressed_Down ){
						break;
				}
	
		}
		startkeywait(1,1);
		lcdpos (3,0);
		lcd_printf ("数据保存中...   ");
		AT24CXX_Write(Addr,(uint8_t *)str,Length);
		delay_ms (100);
		lcdpos (lcdcon -1 ,14);
		lcd_printf ("OK");
}



/********************************************
	* File Name     : Menu_Click
	* Description   : Menu_Click
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
********************************************/
 
uint8_t  Menu_Click( char *Menu_Name, Menu_List_Typedef *List, uint8_t *Value ){
	uint8_t  i = 0,Test_Mode_Count = 0,Row = 1,Button_Status=0,Current_Menu = 0;
	uint8_t  Save_List_Flag = RESET ;
	for( i = 0;List[i].Name; i ++ )
		Test_Mode_Count ++;
	lcdreset();
	lcdpos(0,0);
	lcd_printf("【%s%02u项】",Menu_Name,(u16)(Test_Mode_Count));	
	cyc4or3set (3);
	for( i = 0 ; (i < 3 && List[i].Name ); i ++){
		cyc4or3run ();
		lcd_printf("%2d%s",Current_Menu+1,  List[i].Name	);
	  Current_Menu ++;
	}	
	imageclear ();
	Set_Reverse(ENABLE,Row,0,16);
	Current_Menu = 0;
	if(*Value != Current_Menu)
		Save_List_Flag = SET;
	while(1){
				if(Save_List_Flag == RESET){
					startkeywait (1,1);
					Button_Status = Get_start_key_val();
				}
				else{
					Button_Status = Left_Button_Pressed_Down;
					if(Current_Menu == (*Value-1))
						Save_List_Flag = RESET ;
				}
				if( Button_Status == Right_Button_Pressed_Down ){ 
						break ;
				}
				else if(Button_Status == Left_Button_Pressed_Down ){  	
						Current_Menu ++;
						if(List[Current_Menu].Name == NULL){
							Current_Menu  = 0;
						}								
						if(Row < 3|| Test_Mode_Count < 4){
							Row++; 							
							if(Row > Test_Mode_Count ){
								Set_Reverse(DISABLE,Row-1,0,16);
								Row = 1;
							}
							Set_Reverse(DISABLE,Row-1,0,16);
							Set_Reverse(ENABLE, Row,  0,16);							

						}else{ 					
							cyc4or3run();
							lcd_printf ("%2d%s",Current_Menu+1,List[Current_Menu].Name);									
						}							
				}else if(Button_Status == Double_Button_Pressed_Down  ){
					  
					break ;
				}					
		}
	*Value = Current_Menu;
	return Button_Status;
}
/********************************************
	* File Name     : Menu_List_Fun
	* Description   : Menu_List_Fun
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
********************************************/
void Menu_List_Fun( char *Menu_Name, Menu_List_Typedef *List){
		uint8_t Fun_Num = 0,Return_Value = 0;
		while(1){
			Return_Value = Menu_Click(Menu_Name,List,&Fun_Num);
			if(Return_Value==Right_Button_Pressed_Down )
				List[Fun_Num].fun ();
			else if(Return_Value==Double_Button_Pressed_Down  )
				break ;
		}
		startkeywait(1,1);
}



Menu_List_Typedef Parameter_List[] = {
	{ "工位设置      ",   TEST_Station_Set            },	
	{ "本地IP设置　　",   ETH_NET_Set                 },
	{ "指令等待时间  ",   Cmd_Dealy_Set               },	
	{ "测试前延时设置",   Test_Previous_Wait_Time_Set },
	{ NULL }
};
/**********************************************************************************************************************
	* File Name     :  System_Parameter_Set
	* Description   :  系统参数设置
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/14
************************************************************************************************************************/
unsigned char System_Parameter_Set(void){
	Menu_List_Fun("参数设置",Parameter_List);
	RevertStartupScreen();
	return 0;
}

