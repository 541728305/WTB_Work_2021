#include "smc_lec.h"
#include "lec_set.h"
#include "head.h"

extern  SMC_Parameter_Def LEC_Parameter[SMC_LEC_Parameter_Number];
extern  SMC_LEC_Def SMC_LECPAN,SMC_LECPAN_Y;

//�������� Lec_Parameter_Set1
//��  ���� Num���������
//��  �ܣ� ���õ��ʹ�ܣ�����Ʒ�Ƿ����ϣ��������������
//��  �ߣ� Morton
//��  �ڣ� 2018.7.13
void  Lec_Parameter_Set1( uint8_t Num){
	  uint8_t  Button_Status;
		lcdreset ();
		lcdpos(0,0); lcd_printf("%s",LEC_Parameter[Num].Name);
	  lcdpos(3,0);lcd_printf ("L:ѡ��    R:ȷ��");
		lcdpos(1,0);
		switch(Num){
							case _Enable      : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"����":"�ر�"); break ;
							case _Fail_Enable : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"����":"�ر�");break ;
							case _Direction   : lcd_printf ("    %s    ",    (LEC_Parameter[Num].data)?"˳ʱ��CW":"��ʱ��CCW"); break ;
		}
		while(1){
				Button_Status = Get_start_key_val();
				if(Button_Status==Left_Button_Pressed_Down ){
						LEC_Parameter[Num].data  = !LEC_Parameter[Num].data ;
						lcdpos (1,0); 
						switch(Num){
							case _Enable      : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"����":"�ر�"); break ;
							case _Fail_Enable : lcd_printf ("      %s      ",(LEC_Parameter[Num].data)?"����":"�ر�");break ;
							case _Direction   : lcd_printf ("    %s    ",    (LEC_Parameter[Num].data)?"˳ʱ��CW":"��ʱ��CCW"); break ;
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
//�������� Lec_Parameter_Set2
//��  ���� Num���������
//����ֵ�� ��
//��  �ܣ� ���õ�װڷ�����
//��  �ߣ� Morton
//��  �ڣ� 2018.7.13
void  Lec_Parameter_Set2( uint8_t Num){
	  uint8_t  Button_Status;
		lcdreset ();
		lcdpos(0,0); lcd_printf("%s",LEC_Parameter[Num].Name);
		lcdpos (1,0); 
		switch(Num){
			case _PASS_Num    : lcd_printf ("      %2.0f��      ", LEC_Parameter[Num].data); break ;
			case _FAIL_Num    : lcd_printf ("      %2.0f��      ", LEC_Parameter[Num].data); break ;
		}
	  lcdpos(3,0); lcd_printf ("L:+.R:-.L+R:SAVE");
		while(1){
				Button_Status = Get_start_key_val();
				//*********���������ֵ��1�Ҽ���1,ͬʱ���±��浱ǰ����************************************************
				if(Button_Status==Left_Button_Pressed_Down ){
						LEC_Parameter[Num].data ++ ;
				}else	if(Button_Status == Right_Button_Pressed_Down ){
						LEC_Parameter[Num].data -- ;
				}else if(Button_Status == Double_Button_Pressed_Down ){
						break ;
				}			
				//*********��Ч���ж�*********************************************************************************
				if(LEC_Parameter[Num].data > LEC_Parameter[Num].USL)
						LEC_Parameter[Num].data = LEC_Parameter[Num].USL;
				if(LEC_Parameter[Num].data < LEC_Parameter[Num].LSL)
						LEC_Parameter[Num].data = LEC_Parameter[Num].LSL;
				//********��ʾ��ǰ����ֵ*****************************************************************************
				lcdpos (1,0); 
				switch(Num){
					case _PASS_Num    : lcd_printf ("      %2.0f��      ", LEC_Parameter[Num].data); break ;
					case _FAIL_Num    : lcd_printf ("      %2.0f��      ", LEC_Parameter[Num].data); break ;
				}

		}
		AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr,(uint8_t)LEC_Parameter[Num].data,LEC_Parameter[Num].Length);
		SMC_LECPAN.Pass_Positiom_Num  = LEC_Parameter[_PASS_Num].data ;
		SMC_LECPAN.Fail_Positiom_Num  = LEC_Parameter[_FAIL_Num].data ;
		startkeywait (1,1);
}
//�������� Lec_Parameter_Set3
//��  ���� Num���������
//����ֵ�� ��
//��  �ܣ� ���õ�״���λ�ü�ȡ��λ�ã�Ԥ��ֵ���β�����0.1mm
//��  �ߣ� Morton
//��  �ڣ� 2018.7.13

#define Debug_Step_Length_S   0.1 
#define Debug_Step_Length_M   1.0
#define Debug_Step_Length_L   5.0
#define Debug_Pulse_Width     500 //��λus Fred = 1000000/Debug_Pulse_Width/2 = 1KHz
void Lec_Parameter_Set3( uint8_t Num){
		uint8_t  Button_Status,i;
	  uint8_t  Pulse_CNT = 0;
		double  Debug_Step_Length = 0.0;
		double Step_Length = (double)SMC_LECPAN.Screw_Pitch/(360.0/1.8*(double)SMC_LECPAN.Microstep); //�����岽����
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
				//*********���������ֵ��1�Ҽ���1,ͬʱ���±��浱ǰ����************************************************
				if(Button_Status==Left_Button_Pressed_Down ){
						LEC_Parameter[Num].data += Debug_Step_Length ;
						SMC_LEC_DIR = SMC_LECPAN.Direction ; //�� ��Ϊ������
				}else	if(Button_Status == Right_Button_Pressed_Down ){
						LEC_Parameter[Num].data -= Debug_Step_Length ;
						SMC_LEC_DIR = SMC_LECPAN.Direction ; //�� ��Ϊ������
				}else if(Button_Status == Double_Button_Pressed_Down ){
						break ;
				}			
				//*********��Ч���ж�*********************************************************************************
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
				//********��ʾ��ǰ����ֵ*****************************************************************************
				lcdpos(1,0); lcd_printf("X = %6.2fmm    ",LEC_Parameter[Num].data);
		}
		//�洢���ݲ����µ�ǰ����
		AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr,(uint16_t)(LEC_Parameter[Num].data*100),LEC_Parameter[Num].Length);
		SMC_LECPAN.Pass_Positiom_Num  = LEC_Parameter[_Standby_Postion].data ; 
		SMC_LECPAN.Fail_Positiom_Num  = LEC_Parameter[_Product_Position].data ;
		startkeywait (1,1);
}

//�������� Lec_Parameter_Set4
//��  ���� Num���������
//����ֵ�� ��
//��  �ܣ� ��Ʒ����Ʒλ�����ã�Ԥ��ֵ���β�����0.1mm
//��  �ߣ� Morton
//��  �ڣ� 2018.7.13
void Lec_Parameter_Set4( uint8_t Num){
		uint8_t  Button_Status,i,j;
	  uint8_t  Pulse_CNT = 0,SET_Num = LEC_Parameter[Num-3].data ;
		double  Debug_Step_Length = Debug_Step_Length_L; //���Բ�������Ϊ���
		double  Step_Length = (double)SMC_LECPAN.Screw_Pitch/(360.0/1.8*(double)SMC_LECPAN.Microstep); //�����岽����
		Pulse_CNT  = Debug_Step_Length/Step_Length ;
		if(SET_Num < 0.0 || SET_Num >10.0)
				SET_Num = 5 ;
	 	for( j = 0 ; j < SET_Num ; j ++ ){
				lcdpos (0,0); lcd_printf ("%s",LEC_Parameter [Num].Name);
				lcdpos (0,14) ; lcd_printf ("%02d",j+1);
				lcdpos (1,0); lcd_printf ("L:  ���ô������");
				lcdpos (2,0); lcd_printf ("R:  ������������");
			  lcdpos (3,0); lcd_printf ("L+R:    �˳�    ");
				Button_Status = Get_start_key_val();
//-------->1<--------���Ҽ�ͬʱ�����˳���������-----------------------------------------------------------
				if(Button_Status == Double_Button_Pressed_Down){  
						break ;
				}
//-------->2<--------����������������-------------------------------------------------------------------
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
								//*********���������ֵ��1�Ҽ���1,ͬʱ���±��浱ǰ����************************************************
								if(Button_Status==Left_Button_Pressed_Down ){
										LEC_Parameter[Num].data += Debug_Step_Length ;
										SMC_LEC_DIR = SMC_LECPAN.Direction ; //�� ��Ϊ������
								}else	if(Button_Status == Right_Button_Pressed_Down ){
										LEC_Parameter[Num].data -= Debug_Step_Length ;
										SMC_LEC_DIR = SMC_LECPAN.Direction ; //�� ��Ϊ������
								}else if(Button_Status == Double_Button_Pressed_Down ){
										break ;
								}			
								//*********��Ч���ж�*********************************************************************************
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
								//********��ʾ��ǰ����ֵ*****************************************************************************
								lcdpos(1,0); lcd_printf("X%02d = %6.2fmm  ",j+1,LEC_Parameter[Num].data);
						}
						//�洢���ݲ����µ�ǰ����
						AT24CXX_WriteLenByte (LEC_Parameter[Num].Addr + 2*j,(uint16_t)(LEC_Parameter[Num].data*100),LEC_Parameter[Num].Length);
						switch(Num){
								case _PASS_Position : SMC_LECPAN.Pass_Position [i] = LEC_Parameter[Num].data ; break ;
								case _Fail_Position : SMC_LECPAN.Fail_Position [i] = LEC_Parameter[Num].data ; break ;
						}
					
						startkeywait (1,1); //�������ú���
//-------->3<--------����-------------------------------------------------------------------
				}else if(Button_Status == Right_Button_Pressed_Down ) {
						continue ;
				}
		}
}
