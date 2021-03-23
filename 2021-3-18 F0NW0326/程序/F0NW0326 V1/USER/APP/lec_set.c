#include "smc_lec.h"
#include "lec_set.h"
#include "head.h"

extern  SMC_Parameter_Def LEC_Parameter[SMC_LEC_Parameter_Number];
extern  SMC_LEC_Def SMC_LECPAN,SMC_LECPAN_Y;

//函数名： Lec_Parameter_Set1
//参  数： Num，参数编号
//功  能： 设置电缸使能，不良品是否脱料，电缸运行正方向
//作  者： Morton
//日  期： 2018.7.13
void  Lec_Parameter_Set1( uint8_t Num){
	  uint8_t  Button_Status;
		lcdreset ();
		lcdpos(0,0); lcd_printf("%s",LEC_Parameter[Num].Name);
	  lcdpos(3,0);lcd_printf ("L:选择    R:确认");
		lcdpos(1,0);
		switch(Num){
							case _Enable      : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"开启":"关闭"); break ;
							case _Fail_Enable : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"开启":"关闭");break ;
							case _Direction   : lcd_printf ("    %s    ",    (LEC_Parameter[Num].data)?"顺时针CW":"逆时针CCW"); break ;
		}
		while(1){
				Button_Status = Get_start_key_val();
				if(Button_Status==Left_Button_Pressed_Down ){
						LEC_Parameter[Num].data  = !LEC_Parameter[Num].data ;
						lcdpos (1,0); 
						switch(Num){
							case _Enable      : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"开启":"关闭"); break ;
							case _Fail_Enable : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"开启":"关闭");break ;
							case _Direction   : lcd_printf ("    %s    ",    (LEC_Parameter[Num].data)?"顺时针CW":"逆时针CCW"); break ;
						}
				}
				if(Button_Status == Right_Button_Pressed_Down )
					break ;
		}
		AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr,(uint8_t)LEC_Parameter[Num].data,LEC_Parameter[Num].Length);
		SMC_LECPAN.Enable       = LEC_Parameter[_Enable].data ;
		SMC_LECPAN.Direction    = LEC_Parameter[_Direction].data ;
		SMC_LECPAN.Fail_Enable  = LEC_Parameter[_Fail_Enable].data ;
		startkeywait (1,1);
}
//函数名： Lec_Parameter_Set2
//参  数： Num，参数编号
//返回值： 无
//功  能： 设置电缸摆放列数
//作  者： Morton
//日  期： 2018.7.13
void  Lec_Parameter_Set2( uint8_t Num){
	  uint8_t  Button_Status;
		lcdreset ();
		lcdpos(0,0); lcd_printf("%s",LEC_Parameter[Num].Name);
		lcdpos (1,0); 
		switch(Num){
			case _PASS_Num    : lcd_printf ("      %2.0f列      ", LEC_Parameter[Num].data); break ;
			case _FAIL_Num    : lcd_printf ("      %2.0f列      ", LEC_Parameter[Num].data); break ;
		}
	  lcdpos(3,0); lcd_printf ("L:+.R:-.L+R:SAVE");
		while(1){
				Button_Status = Get_start_key_val();
				//*********左键按下数值加1右键减1,同时按下保存当前数据************************************************
				if(Button_Status==Left_Button_Pressed_Down ){
						LEC_Parameter[Num].data ++ ;
				}else	if(Button_Status == Right_Button_Pressed_Down ){
						LEC_Parameter[Num].data -- ;
				}else if(Button_Status == Double_Button_Pressed_Down ){
						break ;
				}			
				//*********有效性判断*********************************************************************************
				if(LEC_Parameter[Num].data > LEC_Parameter[Num].USL)
						LEC_Parameter[Num].data = LEC_Parameter[Num].USL;
				if(LEC_Parameter[Num].data < LEC_Parameter[Num].LSL)
						LEC_Parameter[Num].data = LEC_Parameter[Num].LSL;
				//********显示当前设置值*****************************************************************************
				lcdpos (1,0); 
				switch(Num){
					case _PASS_Num    : lcd_printf ("      %2.0f列      ", LEC_Parameter[Num].data); break ;
					case _FAIL_Num    : lcd_printf ("      %2.0f列      ", LEC_Parameter[Num].data); break ;
				}

		}
		AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr,(uint8_t)LEC_Parameter[Num].data,LEC_Parameter[Num].Length);
		SMC_LECPAN.Pass_Positiom_Num  = LEC_Parameter[_PASS_Num].data ;
		SMC_LECPAN.Fail_Positiom_Num  = LEC_Parameter[_FAIL_Num].data ;
		startkeywait (1,1);
}
//函数名： Lec_Parameter_Set3
//参  数： Num，参数编号
//返回值： 无
//功  能： 设置电缸待机位置及取料位置，预设值单次步进量0.1mm
//作  者： Morton
//日  期： 2018.7.13

#define Debug_Step_Length_S   0.1 
#define Debug_Step_Length_M   1.0
#define Debug_Step_Length_L   5.0
#define Debug_Pulse_Width     500 //单位us Fred = 1000000/Debug_Pulse_Width/2 = 1KHz
void Lec_Parameter_Set3( uint8_t Num){
		uint8_t  Button_Status,i;
	  uint8_t  Pulse_CNT = 0;
		double  Debug_Step_Length = 0.0;
		double Step_Length = (double)SMC_LECPAN.Screw_Pitch/(360.0/1.8*(double)SMC_LECPAN.Microstep); //单脉冲步进量
		switch(Num){
			case _Standby_Postion :  Debug_Step_Length = Debug_Step_Length_M; break ;
			case _Product_Position:  Debug_Step_Length = Debug_Step_Length_S; break ;
		}
		Pulse_CNT  = Debug_Step_Length/Step_Length ;
		lcdreset ();
		lcdpos(0,0); lcd_printf("%s",LEC_Parameter[Num].Name);
	  lcdpos(1,0); lcd_printf("X = %6.2fmm    ",LEC_Parameter[Num].data);
		lcdpos(3,0); lcd_printf ("L:+.R:-.L+R:SAVE");
		while(1){
				Button_Status = Get_start_key_val();
				//*********左键按下数值加1右键减1,同时按下保存当前数据************************************************
				if(Button_Status==Left_Button_Pressed_Down ){
						LEC_Parameter[Num].data += Debug_Step_Length ;
						SMC_LEC_DIR = SMC_LECPAN.Direction ; //＋ ，为正方向
				}else	if(Button_Status == Right_Button_Pressed_Down ){
						LEC_Parameter[Num].data -= Debug_Step_Length ;
						SMC_LEC_DIR = SMC_LECPAN.Direction ; //＋ ，为负方向
				}else if(Button_Status == Double_Button_Pressed_Down ){
						break ;
				}			
				//*********有效性判断*********************************************************************************
				if(LEC_Parameter[Num].data > LEC_Parameter[Num].USL)
						LEC_Parameter[Num].data = LEC_Parameter[Num].USL;
				else if(LEC_Parameter[Num].data < LEC_Parameter[Num].LSL)
						LEC_Parameter[Num].data = LEC_Parameter[Num].LSL;
				else {
						for( i = 0 ; i < Pulse_CNT ; i ++)
							SMC_LEC_PUL = 0 ;
							delay_us (Debug_Pulse_Width);
							SMC_LEC_PUL = 1 ;
							delay_us (Debug_Pulse_Width);
				}
				//********显示当前设置值*****************************************************************************
				lcdpos(1,0); lcd_printf("X = %6.2fmm    ",LEC_Parameter[Num].data);
		}
		//存储数据并更新当前设置
		AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr,(uint16_t)(LEC_Parameter[Num].data*100),LEC_Parameter[Num].Length);
		SMC_LECPAN.Pass_Positiom_Num  = LEC_Parameter[_Standby_Postion].data ; 
		SMC_LECPAN.Fail_Positiom_Num  = LEC_Parameter[_Product_Position].data ;
		startkeywait (1,1);
}

//函数名： Lec_Parameter_Set4
//参  数： Num，参数编号
//返回值： 无
//功  能： 良品不良品位置设置，预设值单次步进量0.1mm
//作  者： Morton
//日  期： 2018.7.13
void Lec_Parameter_Set4( uint8_t Num){
		uint8_t  Button_Status,i,j;
	  uint8_t  Pulse_CNT = 0,SET_Num = LEC_Parameter[Num-3].data ;
		double  Debug_Step_Length = Debug_Step_Length_L; //调试步长设置为最大
		double  Step_Length = (double)SMC_LECPAN.Screw_Pitch/(360.0/1.8*(double)SMC_LECPAN.Microstep); //单脉冲步进量
		Pulse_CNT  = Debug_Step_Length/Step_Length ;
		if(SET_Num < 0.0 || SET_Num >10.0)
				SET_Num = 5 ;
	 	for( j = 0 ; j < SET_Num ; j ++ ){
				lcdpos (0,0); lcd_printf ("%s",LEC_Parameter [Num].Name);
				lcdpos (0,14) ; lcd_printf ("%02d",j+1);
				lcdpos (1,0); lcd_printf ("L:  设置此项参数");
				lcdpos (2,0); lcd_printf ("R:  跳过此项设置");
			  lcdpos (3,0); lcd_printf ("L+R:    退出    ");
				Button_Status = Get_start_key_val();
//-------->1<--------左右键同时按下退出此项设置-----------------------------------------------------------
				if(Button_Status == Double_Button_Pressed_Down){  
						break ;
				}
//-------->2<--------按左键进入该项设置-------------------------------------------------------------------
				if(Button_Status == Left_Button_Pressed_Down ){	 
						switch(Num){
								case _PASS_Position : LEC_Parameter[Num].data = SMC_LECPAN.Pass_Position [j]; break ;
								case _Fail_Position : LEC_Parameter[Num].data = SMC_LECPAN.Fail_Position [j]; break ;
						}
						lcdpos(1,0); lcd_printf("X%02d = %6.2fmm  ",j+1,LEC_Parameter[Num].data);
						lcdpos(2,0);lcd_printf ("                ");
						lcdpos(3,0); lcd_printf ("L:+.R:-.L+R:SAVE");
						while(1){
								Button_Status = Get_start_key_val();
								//*********左键按下数值加1右键减1,同时按下保存当前数据************************************************
								if(Button_Status==Left_Button_Pressed_Down ){
										LEC_Parameter[Num].data += Debug_Step_Length ;
										SMC_LEC_DIR = SMC_LECPAN.Direction ; //＋ ，为正方向
								}else	if(Button_Status == Right_Button_Pressed_Down ){
										LEC_Parameter[Num].data -= Debug_Step_Length ;
										SMC_LEC_DIR = SMC_LECPAN.Direction ; //＋ ，为负方向
								}else if(Button_Status == Double_Button_Pressed_Down ){
										break ;
								}			
								//*********有效性判断*********************************************************************************
								if(LEC_Parameter[Num].data > LEC_Parameter[Num].USL)
										LEC_Parameter[Num].data = LEC_Parameter[Num].USL;
								else if(LEC_Parameter[Num].data < LEC_Parameter[Num].LSL)
										LEC_Parameter[Num].data = LEC_Parameter[Num].LSL;
								else {
										for( i = 0 ; i < Pulse_CNT ; i ++)
											SMC_LEC_PUL = 0 ;
											delay_us (Debug_Pulse_Width);
											SMC_LEC_PUL = 1 ;
											delay_us (Debug_Pulse_Width);
								}						
								//********显示当前设置值*****************************************************************************
								lcdpos(1,0); lcd_printf("X%02d = %6.2fmm  ",j+1,LEC_Parameter[Num].data);
						}
						//存储数据并更新当前设置
						AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr + 2*j,(uint16_t)(LEC_Parameter[Num].data*100),LEC_Parameter[Num].Length);
						switch(Num){
								case _PASS_Position : SMC_LECPAN.Pass_Position [i] = LEC_Parameter[Num].data ; break ;
								case _Fail_Position : SMC_LECPAN.Fail_Position [i] = LEC_Parameter[Num].data ; break ;
						}
					
						startkeywait (1,1); //调用设置函数
//-------->3<--------跳过-------------------------------------------------------------------
				}else if(Button_Status == Right_Button_Pressed_Down ) {
						continue ;
				}
		}
}
