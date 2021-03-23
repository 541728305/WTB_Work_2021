#include "test_config.h"
#include "ad7176.h"
#include "short.h"
#include "Sup_Fun.h"
#include "analog_switch.h"
#include "other.h"
#include "global.h"
#include "delay.h"
#include "usart.h"
#include "lcd3033.h"
#include <string.h>
#include "os.h"
#include "test.h"
#include "menu.h"
#include "base_Config.h"


SHORT_DATA_Typedef SHORT_RES;


      
//*********短路群定义**********注意：未定义点不测试*********************************94PIN+16 ==110

 const  uint16_t   ShortGroup[ ][ShortPoint_Num]={ 
  //    1-----2-----3-----4-----5-----6-----7-----8-----9----10----11----12----13----14----15----16----17----18----19----20				
	
	{15,99,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{17,97,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{12,104,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{18,98,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{16,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{14,102,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{35,43,32,38,44,79,71,84,78,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{21,93,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{20,96,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{30,86,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{8,108,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{19,95,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{25,89,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{4,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{3,111,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{37,77,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{41,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{39,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{22,94,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{23,91,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{45,47,69,67,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{46,48,70,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{5,109,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{7,107,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{36,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{34,82,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{9,105,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{42,74,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{40,76,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{11,103,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{24,92,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{28,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{26,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{33,81,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{29,85,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{31,83,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{1,51,2,113,114,116,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{49,50,52,65,115,66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{13,101,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{10,106,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{27,87,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{6,110,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},

		{ NULL}	     			
 				                                                                                                          
};   








	uint16_t ErrorMsg[128+1],Point[384+1];                                                                                                                                
 /*****************************************************************************************                                     
	* File Name     :Short_Gooup_Edit_Check                                                                                       
	* Description   :短路群编辑检查                                                                                               
  * Input         :无                                                                                                           
  * return        :、                                                                                                           
	* Author        :Morton                                                                                                       
	* Date          :2018/8/13                                                                                                    
*********************************************************************************************/                                  
void Short_Gooup_Edit_Check( void){                                                                                             
	uint16_t i,j,EN_bit = ENABLE;

	uint16_t CNT = 0,k = 0,NG_Flag = True;
	lcdreset();
	cyc4or3run (); lcd_printf ("短路群编辑检查中");
	cyc4or3run (); lcd_printf ("...             ");
	if(EN_bit){
		memset (ErrorMsg,0,128+1);	
		memset (Point,   0,384+1);		 //	复位数组
		
		for( i = 0 ; ShortGroup[i][0]; i ++){
			j = 0;
			while (ShortGroup[i][j])  //判断当前点位是否已被 mark，若被mark是重复编辑点
			{  
				if(Point[ShortGroup[i][j]]){	
						ErrorMsg[CNT] = ShortGroup[i][j];
						CNT ++;					
				}
				Point[ShortGroup[i][j]] = ShortGroup[i][j]; //已编辑点位Mark
				j ++;
			}
		}
		if(ErrorMsg[0] != 0){
			k = 0;CNT = 0;
			cyc4or3run (); 
			lcd_printf ("重复编辑PIN:");		//重复点位点检	
			while(ErrorMsg[k]){ 
				lcd_printf ("%d,",ErrorMsg[k]); k ++;CNT++;
				if(CNT > 10){
					  CNT = 0;
						step_test_mode_get_key ();
				}
			}
				step_test_mode_get_key ();
				NG_Flag |= False;
		}
		memset (ErrorMsg,0,128 +1); CNT = 0;

		for ( i = 1 ; i <= Fixture.Max_Point ; i ++){	
			if(Point[i] == i|| ( i > 44 ))             //点检是否被Mark，若没有则为漏编辑
				continue ;
			else {
					ErrorMsg[CNT] = i;
					CNT ++;	
			}
		}	
		if(ErrorMsg[0] != 0){
			k = 0;CNT = 0;
			lcdreset ();
			cyc4or3run ();
			lcd_printf ("未编辑PIN=      ");
			while(ErrorMsg[k]){ 
				lcd_printf ("%d,",ErrorMsg[k]); k ++;CNT ++;	
				if(CNT > 10){
					  CNT = 0;
						step_test_mode_get_key ();
				}
			}
			step_test_mode_get_key ();
			NG_Flag |= False;
		}		
		if(NG_Flag == True){
			lcdpos (lcdcon-1,14); lcd_printf ("OK");
			step_test_mode_get_key ();
		}
	}
}
/*****************************************************************************************
	* File Name     :Short_Res_Test
	* Description   :短路电阻测试
  * Input         :无
  * return        :短路电阻值
	* Author        :Morton
	* Date          :2018/8/13
*********************************************************************************************/
static  double Short_Res_Test(uint16_t H,uint16_t L){
		double  Res_Value = 0.0, NG_Res_Value=0.0,Short_RES[10], Test_Resistor = 0.0;
		uint8_t i,t = 0 ;
		for(i = 0 ; i < 150 ; i ++){
				if((i%25)==0){
					Open_Two_Point(COMA,H,COMC,H);
					Open_Two_Point(COMB,L,COMD,L);					
					delay_ms (10);
				}
				delay_us (2);
				Test_Resistor = Res_2wire_Test();
				if(Test_Resistor > 0 && Test_Resistor < (Max_ConductionImpedance*5)){
						Short_RES[t] = Test_Resistor;
						t ++;
				}else{
						t = 0;
						NG_Res_Value = Test_Resistor;
				}
				if(t == 6){
						Res_Value = Average_Fun (Short_RES,6); 
						return  Res_Value;
				}
				delay_us(1);
		}
	  Res_Value  = NG_Res_Value;
		return Res_Value ;
}

/*********************************************************************************************
	* File Name     :Short_Test_Function
	* Description   :短路测试
  * Input         :测试项目编号
  * return        :测试结果 1： False 0： True
	* Author        :Morton
	* Date          :2018/8/13
*********************************************************************************************/
double Step_Test_RES(  uint16_t H ,uint16_t  L){
	uint8_t Button_Status,k;
	double R,Short_RES[25] ;
	R = Res_2wire_Test();
	if(R < 50 && R > 10.0){
		R /= 5.0;
	}
	cyc4or3run ();
	lcd_printf ("  %6.3fohm     ",R);
	cyc4or3run ();
	lcd_printf ("PIN: %3d,%3d    ",H,L );
	if(left_start_key == 1 || right_start_key == 1 ){
			while(1){ //单步模式下，动态显示电阻值
				Button_Status = GetKey_Status();
				for(k = 0; k < 20; k ++){
					Short_RES[k] = Res_2wire_Test( );
					delay_us (50);
				}
				R = Average_Fun (Short_RES,20); 
				if(R < 50 && R > 10.0){
					R /= 5.0;
				}
				lcdpos (lcdcon-2,0);
				lcd_printf ("  %6.3fohm    ",R);
				if( Button_Status == Right_Button_Pressed_Down ){
						startkeywait  (1,1);
						break ;
				}
				if( Button_Status == Double_Button_Pressed_Down){
						break ;
				}
			}
	}
	return R;
}	

//void Product_Direction_Check(){	
//	if(Read_Product_Dir_Check_bit()== SET)	{
//		Procuct_Direction_Set(RESET );	
//		cyc4or3run();
//		if(Short_Res_Test(18,20) < 50){
//				Procuct_Direction_Set(RESET );	
//				lcd_printf("产品正向定位    ");
//		}else if(Short_Res_Test(18+64,20+64) < 50){
//				Procuct_Direction_Set(SET );	
//				lcd_printf("产品反向定位    ");
//		}else {
//				lcd_printf("默认正向定位    ");
//		}	
//		delay_ms (300);		
//	}else{
//		Procuct_Direction_Set(RESET );	
//	}	
//}

/*********************************************************************************************
	* File Name     : Short_Test_Function
	* Description   : 短路测试
  * Input         : 测试项目编号
  * return        : 测试结果 1： False 0： True
	* Author        : Morton
	* Date          : 2018/8/13
*********************************************************************************************/
uint8_t Short_Test_Function(u16 *TestStepN){
	uint16_t i,j,CNT = 0;
	uint8_t  Short_Test_Result = True,Button_Status ;
	double  RES ;
	Close_All_Point ();
	AD_Sample_Rate_Set(1);
	Enable_RES_Test_Analog_Switch();
//	Product_Direction_Check();
	if(display_EN == DISABLE ){
		(*TestStepN) ++;
		cyc4or3run ();
		lcd_printf ("%d> SHORT ...  ",*TestStepN);			
	}
	for(i = 0;ShortGroup[i][0]; i ++){
		j=1; 
		Open_Two_Point(COMA,ShortGroup[i][0],COMC,ShortGroup[i][0]);
		while(ShortGroup[i][j]){
			if(display_EN == ENABLE){
				(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s-%s",(*TestStepN),Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]]);
			}
			else if(display_EN == DISABLE  && Fixture.Mode  == Step_Test_Mode  ){
				cyc4or3run ();
				lcd_printf ("%s-%s",Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]]);
			}
			Open_Two_Point(COMB, ShortGroup[i][j],COMD, ShortGroup[i][j] );
			delay_us (1);
			if(Fixture.Mode  == Auto_Test_Mode ){
				RES = Res_2wire_Test( );
				if((RES < 50 && RES > 10.0)&& Fixture.Mode  == Auto_Test_Mode ){
						RES /= 5.0;
				}
			}
			if(Fixture.Mode  == Step_Test_Mode ){
					RES = Step_Test_RES(ShortGroup[i][0],ShortGroup[i][j] );
			}
			//************测试值OK********************
			if(RES < Max_ConductionImpedance && RES > 0.0){ 
					SHORT_RES.Status[CNT] = 0;
					SHORT_RES.Value[CNT] = RES;
					//******************显示阻值****************************
					if(display_EN == ENABLE && Fixture.Mode  == Auto_Test_Mode ){
						cyc4or3run ();
						lcd_printf ("  %6.3fohm     ",RES);
					}
					//******************显示阻值****************************
					if(Fixture.Mode  == Step_Test_Mode ||  display_EN == ENABLE){
							lcdpos(lcdcon-1,14);	
							lcd_printf ("OK");
					}					
					j++,CNT ++;
			}
		 //************测试值NG********************
			else{
				//**********************************自动测试机复测*********************************
				if(Fixture.Mode  == Auto_Test_Mode){
					delay_ms (10);
					RES = Short_Res_Test(ShortGroup[i][0],ShortGroup[i][j]);
					if(RES < 50 && RES > 10.0){
							RES /= 5.0;
					}
					SHORT_RES.Value[CNT] = RES;
					if(RES < Max_ConductionImpedance && RES > 0.0){
						SHORT_RES.Status[CNT] = 0;
						//******************显示阻值****************************
						if(display_EN == ENABLE && Fixture.Mode  == Auto_Test_Mode ){
								cyc4or3run ();
								lcd_printf ("  %6.3fohm     ",RES);
						}
						if(Fixture.Mode  == Step_Test_Mode ||  display_EN == ENABLE){
								lcdpos(lcdcon-1,14);	
								lcd_printf ("OK");
						}	
					 //******************显示阻值****************************						
						j++,CNT ++;
						continue ;
					}
				}
				//***********************************复测结束*************************************
				if(Fixture.Mode  == Auto_Test_Mode){
						SHORT_RES.Value[CNT] = RES;
						if(display_EN == DISABLE ){
								cyc4or3run ();
								lcd_printf ("%s-%s   ",Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]]);
						}
						cyc4or3run ();
						lcd_printf ("[%d,%d] %0.3f ",ShortGroup[i][0],ShortGroup[i][j],RES );
						Short_Test_Result |= False ;			
						lcdpos (lcdcon  -1 ,14) ;
						lcd_printf ("NG");	
						SHORT_RES.Status[CNT] = 1;
				}
				if( Fixture.Mode  == Step_Test_Mode ){
						SHORT_RES.Status[CNT] = 1;
						SHORT_RES.Value[CNT] = RES;
						lcdpos (lcdcon-2 ,14) ; 
						lcd_printf ("NG");	
						cyc4or3run ();
						lcd_printf ("L:复测  R:下一步");
						lcdpos(lcdcon-2,0);
						startkeywait(1,1);
						Button_Status = Get_start_key_val ();
						if(Button_Status == Right_Button_Pressed_Down ){ 
							Short_Test_Result |= False ;
							j++,CNT ++;						
						}
						continue ;
				}			
				goto  Short_Test_Finish_Flag;
			}	
		}
	 }
Short_Test_Finish_Flag: //出现NG后直接跳转至此处
	if(Short_Test_Result== True && display_EN == DISABLE  ){
		lcdpos (lcdcon -1,14);	
		lcd_printf ("OK");
	}
	Disable_RES_Test_Analog_Switch();
	Close_All_Point ();
	return Short_Test_Result ;
}


/*********************************************************************************************
	* File Name     : KOhm_RES_Test
	* Description   : KOhm Test function
  * Input         : Num
  * return        : Test Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t OS_Short_Test(uint16_t Num,double REF){
	uint8_t CNT = 0,i = 0,Test_Result = True ;
	double ohm = 0.0,TEST_Ohm[25];
	Open_Two_Point (COMC, Item[Num].Test_H,COMD,Item[Num].Test_L);
	Open_Two_Point (COMA, Item[Num].Src_H ,COMB,Item[Num].Src_L);
	if(Fixture.Mode  == Auto_Test_Mode ){
		for( i= 0 ; i < 200 ;i ++){			
				ohm  = Res_2wire_Test();
				if(ohm  > Item[Num].LSL && ohm < (Item[Num].USL) ){
						TEST_Ohm[CNT] = ohm;
						CNT ++; 
				}
				else{
						Item_Data[Num].Value = ohm;
						CNT = 0;
						delay_us (10);	
				}
				if(CNT >= 1){
						Item_Data[Num].Value  =ohm ;// Average_Fun (TEST_Ohm,5);
						break ;
				}
		
		}
		if(TestConfig.OS_Short == ENABLE || Fixture.Mode == Step_Test_Mode  ){
				cyc4or3run();
				lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
		}
	}
	if(Fixture.Mode  == Step_Test_Mode  ){	
		for( i = 0; i < 10; i ++){				
				TEST_Ohm[i]  = Res_2wire_Test();			
		}
		Item_Data[Num].Value  = Average_Fun(TEST_Ohm,10);
		cyc4or3run ();
		lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
		if(left_start_key == 1 || right_start_key == 1 ){
				while(left_start_key ==1&&right_start_key ==1){ //?˙家Α???ボ?甧
					for( i = 0; i < 10; i ++){				
							TEST_Ohm[i]  = Res_2wire_Test();	
							delay_us (10);							
					}
					Item_Data[Num].Value  = Average_Fun(TEST_Ohm,10);
					lcdpos(lcdcon-1,0);  					
					lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);		
					delay_ms (10);
					if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
						lcdpos(lcdcon-1,14); lcd_printf ("OK");  
					}else{
						lcdpos(lcdcon-1,14); lcd_printf ("NG");  
					}
				}
				startkeywait(1,1);
		}
	}

	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.OS_Short == ENABLE ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}
	}else{
		if(Fixture.Mode == Auto_Test_Mode ||TestConfig.OS_Short == DISABLE   ){
				cyc4or3run ();
				lcd_printf ("%s",Item[Num].Name);
				cyc4or3run ();
			  lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
		}
		lcdpos(lcdcon-1,14);  
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
//	Uart_printf(Fixture.Comm_Uart,"#%d*%0.4f\r\n",Num,Item[Num].Value );
	return Test_Result;
}

/*********************************************************************************************
	* File Name     : Read_Toatl_Item_Num
	* Description   : Read_Toatl_Item_Num
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
uint8_t Type_OS_Short_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t Total_Test_Result = True;
		uint16_t  j=0,Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;		
		Close_All_Point ();
		AD_Sample_Rate_Set(0);
		Enable_RES_Test_Analog_Switch();
		if(TestConfig.OS_Short  == DISABLE && Fixture.Mode  == Auto_Test_Mode){
			(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"Short  ...   ");	
		}	
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(TestConfig.OS_Short  == ENABLE || Fixture.Mode  == Step_Test_Mode ){
				(*TestStepN) ++;
				 cyc4or3run ();
				 lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
			}
			Item_Data[Item_Step_Number].Status =	OS_Short_Test(Item_Step_Number,20000 );		
			if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					Total_Test_Result |= False ;
					break ;
			}
			if(Fixture.Mode  == Step_Test_Mode && Item_Data[Item_Step_Number].Status == False){
				cyc4or3run ();
				lcd_printf ("L:复测  R:下一步");
				lcdcon -- ;
				Clear_buffer(3);
				if (step_test_mode_get_key () == Left_Button_Pressed_Down ){
						j --;
						(*TestStepN) --;
						continue ;
				}
				Total_Test_Result |= False ;
			}			
		}
		if(TestConfig.OS_Short == DISABLE && Fixture.Mode  == Auto_Test_Mode && Total_Test_Result== True ){
			lcdpos(lcdcon -1,14);
			lcd_printf ("OK");
		}

		Disable_RES_Test_Analog_Switch();
		Close_All_Point ();
		return Total_Test_Result ; 
}






/*********************************************************************************************
	* File Name     : ViewShortGroup
	* Description   : ViewShortGroup
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 18-April-2020
*********************************************************************************************/
void  ViewShortGroup(void){
	uint16_t i = 0,j = 0,Num = 0,Length = 0,str_Num = 0;
	char buf[10];
	for( i = 0 ; ShortGroup[i][0]; i ++){
		Num ++;
	}	
	for( i = 0; i < Num ; i ++)
	{
			lcdreset ();
			cyc4or3set (3);
			lcd_printf ("%d-%d",Num,i+1);
			lcdpos(1,0);		j = 0; str_Num = 0;
			while(ShortGroup[i][j]){	
				memset (buf, 0,10);
				if(ShortGroup[i][j+1]){
					sprintf(buf,"%d,",ShortGroup[i][j]);
				}
				else{
					sprintf(buf,"%d",ShortGroup[i][j]);
				}
				Length = strlen (buf);
				if((str_Num + Length) <= 48){
					lcd_printf ("%s",buf);
					str_Num += Length;
				}else{
					step_test_mode_get_key ();
					lcdpos(1,0); lcd_printf ("                ");
					lcdpos(2,0); lcd_printf ("                ");
					lcdpos(3,0); lcd_printf ("                ");
					lcdpos(1,0);
					lcd_printf ("%s",buf);			
					str_Num = Length ;
				}
				j++;
			}
			step_test_mode_get_key ();
		}
}
