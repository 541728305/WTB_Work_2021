#include "open.h"
#include "ad7176.h"
#include "Sup_Fun.h"
#include "analog_switch.h"
#include "other.h"
#include "global.h"
#include "delay.h"
#include "lcd3033.h"
#include "string.h"
#include "dac.h"
#include "stdio.h"
#include "test.h"
#include "os.h"
#include "base_Config.h"
#include "test_config.h"

OPEN_TEST Open_Data;



//*********��·Ⱥ����*1*********ע�⣺δ����㲻����********************************* 5-7 935.  5-9 ,930, 5-13,5-15,5-12,5-1
 const  uint16_t  OpenGroup[][OpentPoint_Num]={
  //   1----2----3----4----5----6----7----8----9---10---11---12---13---14---15---16---17---18---19---20-		ShortPoint_Num                             //30
{115,68,66,48,50,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{88,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{86,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{84,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{90,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{82,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{71,43,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{96,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{98,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{113,107,101,95,89,83,77,65,102,100,116,1,7,13,19,25,31,37,49,51,14,16,0,0,0,0,0,0,0,0,},
{75,39,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{73,41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{92,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{74,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{94,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{108,106,104,8,10,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{114,112,110,2,4,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{85,29,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{87,27,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{91,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{93,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{97,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{99,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{103,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{105,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{109,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{111,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{79,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{81,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{76,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{72,70,44,46,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{69,67,45,47,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{80,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{78,38,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},





		{ NULL}	 
		  			 			     			 				
};
void OS_Open_Relay_SET(double Src, uint16_t AD_SPS,uint8_t Status ){
	Relay_Drive ( K1_Pull_Up|K13_20K_Ref |K8_Src_COMAB|K3_COMCD_IN2_3|K10_Ref_IN0_1|K15_Src_Choice,Status);
	DAC_Set_Vol(Src,5,0);
	AD_Sample_Rate_Set(AD_SPS);
	delay_ms (80);
	
}
/*********************************************************************************************
	* File Name     :Open_Res_Test
	* Description   :��·�������
  * Input         :������Ŀ���
  * return        :���Խ�� 1�� False 0�� True
	* Author        :Morton
	* Date          :2018/8/13
*********************************************************************************************/
static  double  Open_Res_Test( ){
	double  RES,Open_RES[25]={0.0},R;
	uint8_t k,CNT = 0 ;
	for(k = 0; k < 100; k ++){
		R = Res_2wire_Test_Mohm();
		if( R > Min_InsulationResistance){
			Open_RES[CNT] = R;
			CNT ++;
		}
		else {
			RES = R;
			CNT = 0;
			delay_ms(5);
		}
		if(CNT == 6){
			RES = Average_Fun (Open_RES,6); 
			return  RES;
		}
	}
	return 	RES ;
}
/*********************************************************************************************
	* File Name     :Open_RES_Value_Fun
	* Description   :�������Զ�̬��ʾ���Ծ�Ե��
  * Input         :H,���Ե�λ
  * return        :RES ���ղ�����ֵ
	* Author        :Morton
	* Date          :2019/3/20
*********************************************************************************************/
double Open_RES_Value_Fun( uint16_t H,uint16_t L){
	double RES = 0.0;					
	uint8_t k,Button_Status = 0;
	double Open_Resistor[20];
	RES =	Res_2wire_Test_Mohm();
	cyc4or3run ();
	lcd_printf ("%s-%s ",Pin_Name[H],Pin_Name[L] );
	cyc4or3run ();
	lcd_printf ("     %5.3fM     ",RES);
	if(left_start_key == 1 || right_start_key == 1 ){
			while(1){ //����ģʽ�£���̬��ʾ����ֵ
				Button_Status = GetKey_Status();
				for(k=0;k<20;k++){
					Open_Resistor[k] = Res_2wire_Test_Mohm();
					delay_us (2);
				}	
				RES = Average_Fun (Open_Resistor,10);
				lcdpos(lcdcon-1,0);
				if(RES >1)
					lcd_printf ("     %5.3fM     ",RES);
				else if(RES > 0.001){
					lcd_printf ("     %5.3fK     ",RES*1000.0);
				}else {
					lcd_printf ("     %5.3fohm  ",RES*1000000.0);
				}
				if( Button_Status == Right_Button_Pressed_Down){
						startkeywait(1,1);
						break ;
				}
				if( Button_Status == Double_Button_Pressed_Down){
						break ;
				}
		}
	}	
	return RES ;	
}


/*********************************************************************************************
	* File Name     :Step_debug_Open
	* Description   :��������NG����ʾ��ֵ
  * Input         :H,L ���Ե�λ *RES������ֵ
  * return        :Button_Status ����״̬��������⣬�Ҽ���һ��
	* Author        :Morton
	* Date          :2019/3/20
*********************************************************************************************/
uint8_t  Step_debug_Open(uint16_t H,uint16_t L, double *RES){
	uint8_t k,Button_Status ;
	double Open_Resistor[20];
	step_test_mode_get_key();	
	cyc4or3run ();
	lcd_printf ("L:����  R:��һ��");
	while(1){	
			for(k=0;k<20;k++){
				Open_Resistor[k] = Res_2wire_Test_Mohm();
				delay_us (1);
			}	
			*RES = Average_Fun (Open_Resistor,10);							
			lcdpos (lcdcon -2 ,0) ;
			if(*RES > 1)
				lcd_printf ("[%d&%d] %0.2fM  ",H,L,*RES);
			else if(*RES > 0.001){
				lcd_printf ("[%d&%d] %0.1fK  ",H,L,*RES*1000);
			}else 
				lcd_printf ("[%d&%d] %0.1fR  ",H,L,*RES*1000000);
			lcdpos (lcdcon -2 ,14) ;	
	    if(H == 1 && L ==6 ){		
				if(*RES > 0.08)
					lcd_printf ("OK");	
				else
					lcd_printf ("NG");	
			}else {				
				if(*RES > Min_InsulationResistance)
					lcd_printf ("OK");	
				else
					lcd_printf ("NG");	
		  }
			Button_Status = GetKey_Status();
			if(Button_Status == Right_Button_Pressed_Down ||Button_Status ==  Left_Button_Pressed_Down ){ 
					break ;
			}
	}	
	lcdpos(lcdcon-1,0);	
	return Button_Status;
}
/*********************************************************************************************
	* File Name     :Open_Test_Function
	* Description   :�˺���ֻ���Ա������֮���Ե�迹��δ��������
  * Input         :������Ŀ���
  * return        :���Խ�� 1�� False 0�� True
	* Author        :Morton
	* Date          :2018/8/13
*********************************************************************************************/
uint8_t  Open_Test_Function(u16 *TestStepN){
	u8 i,t,Open_Test_Result = True,Button_Status;
	double RES;
	uint16_t CNT = 0;
	(*TestStepN) ++;
	cyc4or3run();
	lcd_printf("%d> OPEN  ...  ",*TestStepN);
	Close_All_Point ();
	OS_Open_Relay_SET(1000,0,SET );
	for(i = 0; OpenGroup[i+1][0] != NULL ; i ++){ 
		Open_Two_Point(COMA,OpenGroup[i][0],COMC,OpenGroup[i][0]);
		for( t = i + 1; OpenGroup[t][0] != NULL; t ++ ){
			Open_Two_Point(COMB,OpenGroup[t][0],COMD, OpenGroup[t][0] );
//			cyc4or3run ();
//			lcd_printf ("%s_%s ",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[t][0]] );
//			cyc4or3run ();
//			lcd_printf ("CNT=%d   ",CNT );
//			while(left_start_key == 1 && right_start_key  ==1);
//			startkeywait (1,1);
			RES =	Res_2wire_Test_Mohm();
			if(Fixture.Mode  == Step_Test_Mode ){
				#if defined debug_mode
						RES = Open_RES_Value_Fun(OpenGroup[i][0],OpenGroup[t][0]);
				#endif
			}
			if(RES <  Min_InsulationResistance){	
				//***************����㴦��**********************
		
				//***************����㴦�����******************				
				Open_Two_Point(COMA,OpenGroup[i][0],COMC,OpenGroup[i][0]);
				Open_Two_Point(COMB,OpenGroup[t][0],COMD, OpenGroup[t][0] );
				delay_ms (20);				//����NG����ʱ20ms����һ��
				RES = Open_Res_Test();
				if(RES > Min_InsulationResistance){		
					  Open_Data.Value[CNT] =  RES; 	
					  Open_Data._Status[CNT] = True ;
						CNT ++ ;
						continue ;
				}	
				//***************����㴦��************************
					
				//***************����㴦�����********************				
				cyc4or3run ();
				lcd_printf ("%s_%s ",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[t][0]] );
				cyc4or3run ();
				lcd_printf ("[%d&%d] %0.2fM  ",OpenGroup[i][0],OpenGroup[t][0],RES);
				lcdpos(lcdcon -1,14); lcd_printf("NG");
				//***����NG����********************************************************************************************
				if(Fixture.Mode  == Step_Test_Mode){
						Button_Status = Step_debug_Open(OpenGroup[i][0],OpenGroup[t][0],&RES );
						if(Button_Status == Right_Button_Pressed_Down){
							if(OpenGroup[i][0] == 1 && OpenGroup[t][0] ==6 ){
								if(RES < 0.08){
										sprintf(Open_Data.RESULT,"%s&%s:%0.7fM@",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[t][0]],RES);	
										Open_Test_Result |= False ;	
								}
							}
							else {
								if(RES < Min_InsulationResistance){
									sprintf(Open_Data.RESULT,"%s&%s:%0.7fM@",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[t][0]],RES);	
									Open_Test_Result |= False ;				
								}		
							}							
						}
						if(Button_Status == Left_Button_Pressed_Down)
							t --;							
						continue ;	
				}
				//*****���Խ���******************************************************************************************					
				Open_Test_Result |= False ;		
				sprintf(Open_Data.RESULT,"%s&%s:%0.7fM@",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[t][0]],RES);	
				Open_Data.Value[CNT] =  RES; 	
				Open_Data._Status[CNT] = False;

				CNT ++ ;			
				goto Open_Test_Finish_Flag ;  //����NG��ֱ������ѭ������
			}else {
					  Open_Data.Value[CNT] =  RES; 	
					  Open_Data._Status[CNT] = True ;
						CNT ++ ;
			}
		}
	}
	Open_Test_Finish_Flag: //����NG��ֱ����ת���˴�
	if(Open_Test_Result == True){
		lcdpos(lcdcon-1,14);
		lcd_printf ("OK");
		Open_Data.Status = 0; 
		strcpy (Open_Data.RESULT,"OK");
	}else{
		Open_Data.Status = 1; 
	}
	Close_All_Point ();
	OS_Open_Relay_SET(0,0,RESET );
	return Open_Test_Result ;
}

/*********************************************************************************************
	* File Name     :Open_Test_Function
	* Description   :????????????????,??????
  * Input         :??????
  * return        :???? 1: False 0: True
	* Author        :Morton
	* Date          :2018/8/13
*********************************************************************************************/
uint8_t  Open_Test_Function_V2(u16 *TestStepN){
	u8 i,t,Open_Test_Result = True,Button_Status,point,j;
	double RES;
	(*TestStepN) ++;
	cyc4or3run();
	lcd_printf("%d> OPEN  ...  ",*TestStepN);
	Close_All_Point ();
	OS_Open_Relay_SET(1000,0,SET );
	for(i = 0 ; OpenGroup[i+1][0] != NULL ;i ++){
		point = 0;
		while(OpenGroup[i][point]){
				Open_Two_Point(COMA,OpenGroup[i][point],COMC,OpenGroup[i][point]);

				for( t = i+1 ; OpenGroup[t][0] != NULL; t ++){
						j=0;
						while(OpenGroup[t][j]){
							Open_Two_Point(COMB,OpenGroup[t][j],COMD, OpenGroup[t][j] );
							RES =	Res_2wire_Test_Mohm();
							if(Fixture.Mode  == Step_Test_Mode ){
								#if defined debug_mode
										RES = Open_RES_Value_Fun(OpenGroup[i][j],OpenGroup[t][j]);
								#endif
							}
							if(RES >  Min_InsulationResistance){	
								j ++;
								continue ;
							}	
							else
							{		
								Open_Two_Point(COMA,OpenGroup[i][point],COMC,OpenGroup[i][point]);
								Open_Two_Point(COMB,OpenGroup[t][j],COMD, OpenGroup[t][j] );
								delay_ms (2);				//??NG???2ms????
								RES = Open_Res_Test();
								if(RES > Min_InsulationResistance){	
										j ++;									
										continue ;
								}
								cyc4or3run ();
								lcd_printf ("%s_%s ",Pin_Name[OpenGroup[i][point]],Pin_Name[OpenGroup[t][j]] );
								cyc4or3run ();
								lcd_printf ("[%d&%d] %0.2fM  ",OpenGroup[i][point],OpenGroup[t][j],RES);
								lcdpos(lcdcon -1,14); lcd_printf("NG");
								//***????*********
								if(Fixture.Mode  == Step_Test_Mode){
										Button_Status = Step_debug_Open(OpenGroup[i][point],OpenGroup[t][j],&RES );
										if(Button_Status == Right_Button_Pressed_Down){
											if(RES < Min_InsulationResistance){
												sprintf(Open_Data.RESULT,"%s&%s:%0.7fM@",Pin_Name[OpenGroup[i][point]],Pin_Name[OpenGroup[t][j]],RES);	
												Open_Test_Result |= False ;				
											}	
											j ++;											
										}
										continue ;	
								}
								//*****????*******					
								Open_Test_Result |= False ;		
								sprintf(Open_Data.RESULT,"%s&%s:%0.7fM@",Pin_Name[OpenGroup[i][point]],Pin_Name[OpenGroup[t][j]],RES);				
								goto Open_Test_Finish_Flag ;  //??NG?????????
							}
				   }
			  }
				point ++;
		 }
	}
	Open_Test_Finish_Flag: //??NG????????
	if(Open_Test_Result == True){
		lcdpos(lcdcon-1,14);
		lcd_printf ("OK");
		Open_Data.Status = 0; 
		strcpy (Open_Data.RESULT,"OK");
	}else{
		Open_Data.Status = 1; 
	}
	Close_All_Point ();
	OS_Open_Relay_SET(0,0,RESET );
	return Open_Test_Result ;
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
uint8_t OS_Open_Test(uint16_t Num,double REF){
	uint8_t CNT = 0,i = 0,Test_Result = True ;
	double Mohm = 0.0,TEST_KOhm[25];
	Open_Two_Point (COMC, Item[Num].Test_H,COMD,Item[Num].Test_L);
	Open_Two_Point (COMA, Item[Num].Src_H ,COMB,Item[Num].Src_L);
	for( i= 0 ; i < 200 ;i ++){			
			Mohm  = Res_2wire_Test_Mohm();
			if(Mohm  > Item[Num].LSL && Mohm < (Item[Num].USL) ){
					CNT ++; 
			}
			else{
					Item_Data[Num].Value = Mohm;
					CNT = 0;
					delay_ms (10);	
			}
			if(CNT >= 1){
					Item_Data[Num].Value  = Mohm;
					break ;
			}
	
	}
	if(TestConfig.OS_Open == ENABLE  ){
			cyc4or3run();
			lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
	}
	
	if(Fixture.Mode  == Step_Test_Mode  ){	
			if(TestConfig.OS_Open == ENABLE || Item_Data[Num].Value < Item[Num].LSL || Item_Data[Num].Value > Item[Num].USL ){
					for( i = 0; i < 10; i ++){				
							TEST_KOhm[i]  = Res_2wire_Test_Mohm();;				
					}
					Item_Data[Num].Value  = Average_Fun(TEST_KOhm,10);
					cyc4or3run ();
					lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
					if(left_start_key == 1 || right_start_key == 1 ){
							while(left_start_key ==1&&right_start_key ==1){ //?�B�Ҧ��U�A???��?�e��
								for( i = 0; i < 10; i ++){				
										TEST_KOhm[i]  = Res_2wire_Test_Mohm();	
										delay_us (10);							
								}
								Item_Data[Num].Value  = Average_Fun(TEST_KOhm,10);
								lcdpos(lcdcon-1,0);  					
								if(Item_Data[Num].Value > 1)
									lcd_printf ("[%d&%d] %0.2fM  ",Item[Num].Src_H,Item[Num].Src_L,Item_Data[Num].Value);
								else if(Item_Data[Num].Value > 0.001){
									lcd_printf ("[%d&%d] %0.1fK  ",Item[Num].Src_H,Item[Num].Src_L,Item_Data[Num].Value*1000);
								}else 
									lcd_printf ("[%d&%d] %0.1fR  ",Item[Num].Src_H,Item[Num].Src_L,Item_Data[Num].Value*1000000);
						
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
	}

	if(Item_Data[Num].Value > Item[Num].LSL && Item_Data[Num].Value < Item[Num].USL){
		if(TestConfig.OS_Open == ENABLE ){
				lcdpos(lcdcon-1,14);  
				lcd_printf ("OK"); 
		}
	}else{
		if(Fixture.Mode == Auto_Test_Mode ){
				cyc4or3run ();
				lcd_printf ("%s",Item[Num].Name);
				cyc4or3run ();
				lcd_printf ("[%d&%d] %0.2fM  ",Item[Num].Src_H,Item[Num].Src_L,Item_Data[Num].Value);
			//  lcd_printf  ("  %7.3f%s  ",Item_Data[Num].Value,Item[Num].Unit);
		}
		lcdpos(lcdcon-1,14);  
		lcd_printf ("NG"); 
		Test_Result |= False;
	}
	return Test_Result;
}
#include "usart.h"
/*********************************************************************************************
	* File Name     : Read_Toatl_Item_Num
	* Description   : Read_Toatl_Item_Num
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
uint8_t Type_OS_Open_Test_Fun(u16 *TestStepN, uint16_t Total_Num,uint16_t *Step_Number_buffer){
		uint8_t Total_Test_Result = True;
		uint16_t j=0,Item_Step_Number = 0;
		if(Total_Num == 0)
			return True;		
		Close_All_Point ();
		OS_Open_Relay_SET(1000,0,SET );
		if(TestConfig.OS_Open == DISABLE ){
			(*TestStepN) ++;
				cyc4or3run ();
				lcd_printf ("%d>%s",*TestStepN,"Open  ...   ");	
		}	
		for( j = 0 ; j < Total_Num ; j ++){
			Item_Step_Number = Step_Number_buffer[j];
			if(TestConfig.Vsrc  == ENABLE ){
				(*TestStepN) ++;
				 cyc4or3run ();
				 lcd_printf ("%d>%s",*TestStepN,Item[Item_Step_Number].Name);
			}
			
			Item_Data[Item_Step_Number].Status = OS_Open_Test(Item_Step_Number,20000 );		
			if(Fixture.Mode  == Auto_Test_Mode && Item_Data[Item_Step_Number].Status == False){
					Total_Test_Result |= False ;
					break ;
			}
			if(Fixture.Mode  == Step_Test_Mode && Item_Data[Item_Step_Number].Status == False){
				cyc4or3run ();
				lcd_printf ("L:����  R:��һ��");
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

		Close_All_Point ();
		OS_Open_Relay_SET(0,0,RESET );
		if(TestConfig.OS_Open == DISABLE && Fixture.Mode  == Auto_Test_Mode && Total_Test_Result== True ){
			lcdpos(lcdcon -1,14);
			lcd_printf ("OK");
		}
		return Total_Test_Result ; 
}



























////*********��·Ⱥ����*2*********ע�⣺δ����㲻����*********************************
//const uint8_t  OpenGroup2[][20] = {
//  //  1----2----3----4----5----6----7----8----9---10---11---12---13---14---15---16---17---18---19---20-		ShortPoint_Num	
//		{ 129,130, 132, 134, 136, 161, 162, 197, 202, 209, 214,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ1	--LEN_E3-P	   . .		
//		{ 131,137, 138, 143, 144, 146, 148, 149, 150, 155, 156, 158, 160, 163, 164,   0,   0,   0,   0,   0    },   //��·Ⱥ2	--LEN_E3-P	   . .		
//		{ 133,207,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ3	--LEN_E3-P	   . .	  
//		{ 135,208,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ4	--LEN_E3-P	   . .					
//		{ 139,195,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ5	--LEN_E3-P	   . .		
//		{ 140,210,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ6	--LEN_E3-P	   . .	
//		{ 141,196,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ7	--LEN_E3-P	   . .					
//		{ 142,198,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ8	--LEN_E3-P	   . .			
//		{ 145,199, 212,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ9	--LEN_E3-P	   . .					
//		{ 147,200, 211,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ10	--LEN_E3-P	   . .				  
//		{ 151,203,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ11	--LEN_E3-P	  . .		
//		{ 152,210,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ12	--LEN_E3-P	   . .	
//		{ 153,204,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ13	--LEN_E3-P	   . .					
//		{ 154,201,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ14	--LEN_E3-P	   . .			
//		{ 157,215,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ15	--LEN_E3-P	   . .		
//		{ 159,216,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },   //��·Ⱥ16	--LEN_E3-P	   . .		
//		{   6, 12,  23,  26,  35,  39,  44,  53,  54,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ17	--LEN_E3-P	  									
//};
///*********************************************************************************************
//	* File Name     :Open_Test_Function_V2
//	* Description   :�˺���ֻ���Ա������֮���Ե�迹��δ��������
//  * Input         :������Ŀ���
//  * return        :���Խ�� 1�� False 0�� True
//	* Author        :Morton
//	* Date          :2018/8/13
//*********************************************************************************************/
//uint8_t  Open_Test_Function_V2(u16 TestStepN){
//	u8 i,j,t,point,Open_Test_Result = True,Button_Status ;
//	double  RES;
//	cyc4or3run ();
//	lcd_printf ("%c%cOPEN Test...  ",(u8)(TestStepN>>8),(u8)(TestStepN&0xff));
//	Close_All_Point ();
//	Turn_OFF_All_Ananlog_Switch();
//	Choice_Voltage_Src_Test();
//	AD7176_Rate_Set = 0;
//	for(i = 0 ; OpenGroup[i+1][0] != NULL ;i ++){
//			point = 0;
//			while(OpenGroup[i][point]){
//					Open_Two_Point(COMA,OpenGroup[i][point],COMC,OpenGroup[i][point]);
//					for( t = i+1 ; OpenGroup[t][0]; t ++){
//							j=0;
//							while(OpenGroup[t][j]){	
//									Open_Two_Point(COMB, OpenGroup[t][j],COMD, OpenGroup[t][j] );
//									RES = Res_2wire_Test_Mohm();
//									if(Fixture.Mode  == Step_Test_Mode ){
//										#if defined debug_mode
//											RES = Open_RES_Value_Fun(OpenGroup[i][point],OpenGroup[t][j]);
//										#endif
//									}
//									if(RES >= Min_InsulationResistance)  {
//										j++;
//									}
//									else {
//											delay_ms (10);
//											RES = Open_Res_Test();
//											if(RES > Min_InsulationResistance){		
//													j++;															
//													continue ;
//											}													
//											cyc4or3run ();
//											lcd_printf("%s_%s  ",Pin_Name[OpenGroup[i][point]],Pin_Name[OpenGroup[t][j]]);
//											cyc4or3run ();
//											lcd_printf ("[%d,%d] %0.3fM  ",OpenGroup[i][point],OpenGroup[t][j], RES);
//											lcdpos(Cursor_y()-1,14);lcd_printf("NG");
//											if(Fixture.Mode  == Step_Test_Mode ){
//													//***��������*********
//													Button_Status = Step_debug_Open(OpenGroup[i][point],OpenGroup[t][j],&RES );
//													if(Button_Status == Right_Button_Pressed_Down){
//														if(RES < Min_InsulationResistance){
//															slcd_printf(Open_Data.RESULT,"%s&%s:%0.4fM@",Pin_Name[OpenGroup[i][point]],Pin_Name[OpenGroup[t][j]],RES);	
//															Open_Test_Result |= False ;				
//														}																	
//														j++;				
//													}
//													if(Button_Status == Left_Button_Pressed_Down){
//														j --;							
//													}
//													continue ;	
//													//*****���Խ���*******	
//											}
//											Open_Test_Result |= False ;
//											slcd_printf(Open_Data.RESULT,"%s&%s:%0.4fM@",Pin_Name[OpenGroup[i][point]],Pin_Name[OpenGroup[t][j]],RES);
//											goto Open_Test_Finish_Flag ;  
//									}
//							}
//				}
//				point ++;
//		 }
//	}
//	Open_Test_Finish_Flag: 
//	if(Open_Test_Result == True){
//		lcdpos(Cursor_y()-1,14);
//		lcd_printf ("OK");
//		Open_Data.Status = 0; 
//		strcpy (Open_Data.RESULT,"OK");
//	}else{
//		Open_Data.Status = 1; 
//	}
//	Close_All_Point ();
//	Turn_OFF_All_Ananlog_Switch();
//	delay_ms (10);
//	return Open_Test_Result;
//}
///*********************************************************************************************
//	* File Name     :Open_Test_Fun_2
//	* Description   :��·����2�����������ԣ�δ���岻���ԣ���Լ����ʱ��
//  * Input         :EN_bit ������Ŀ����
//  * return        :���Խ�� 1�� False 0�� True
//	* Author        :Morton
//	* Date          :2018/8/13
//*********************************************************************************************/
//uint8_t  Open_Test_Fun_2(void){
//		uint8_t i,t,Open_Test_Result2 = True ,Button_Status ;
//		double RES;
//		for(i = 0; OpenGroup2[i+1][0] != NULL; i ++){ 
//				Open_Two_Point(COMA,OpenGroup2[i][0],COMC,OpenGroup2[i][0]);
//				for( t = i + 1; OpenGroup2[t][0] != NULL; t ++ ){
//						Open_Two_Point(COMB, OpenGroup2[t][0],COMD, OpenGroup2[t][0] );
//						RES =	Res_2wire_Test_Mohm();
//						if(Fixture.Mode  == Step_Test_Mode ){
//								#if defined debug_mode
//										RES = Open_RES_Value_Fun(OpenGroup2[i][0],OpenGroup2[t][0]);
//								#endif
//						}
//						if(RES <  Min_InsulationResistance){
//								delay_ms (2);								//����NG����ʱ2ms����һ��
//								RES = Open_Res_Test();
//								if(RES > Min_InsulationResistance){										
//										continue ;
//								}
//								cyc4or3run ();
//								lcd_printf ("%s-%s ",Pin_Name[OpenGroup2[i][0]],Pin_Name[OpenGroup2[t][0]] );
//								cyc4or3run ();
//								lcd_printf ("[%d&%d] %0.2fM  ",OpenGroup2[i][0],OpenGroup2[t][0],RES);
//								lcdpos(Cursor_y()-1,14);lcd_printf("NG");
//								if(Fixture.Mode  == Step_Test_Mode ){
//										//***��������*********
//										Button_Status = Step_debug_Open(OpenGroup2[i][0],OpenGroup2[t][0],&RES );
//										if(Button_Status == Right_Button_Pressed_Down){
//											if(RES < Min_InsulationResistance){
//												slcd_printf(Open_Data.RESULT,"%s-%s:%0.4fM@",Pin_Name[OpenGroup2[i][0]],Pin_Name[OpenGroup2[t][0]],RES);	
//												Open_Test_Result2 |= False ;				
//											}								
//										}
//										if(Button_Status == Left_Button_Pressed_Down)
//											t --;							
//										//*****���Խ���*******	
//										continue ;
//								}
//								Open_Test_Result2 |= False ;
//								slcd_printf(Open_Data.RESULT,"%s&%s:%0.4fM@",Pin_Name[OpenGroup2[i][0]],Pin_Name[OpenGroup2[t][0]],RES);
//								goto Open_Test_Finish_Flag ;  //����NG��ֱ������ѭ������
//						}
//				}
//		}
//		Open_Test_Finish_Flag: //����NG��ֱ����ת���˴�
//		return Open_Test_Result2 ;	
//}
////*********��·Ⱥ����*3*********ע�⣺δ����㲻����*********************************
//const uint8_t  Single_PIN_Group[][20] = {
//  //  1----2----3----4----5----6----7----8----9---10---11---12---13---14---15---16---17---18---19---20-		ShortPoint_Num	
//		{ 129,130, 132, 134, 136, 161, 162, 197, 202, 209, 214,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ1	--LEN_E3-P	   . .		
//		{ 131,137, 138, 143, 144, 146, 148, 149, 150, 155, 156, 158, 160, 163, 164,   0,   0,   0,   0,   0    },   //��·Ⱥ2	--LEN_E3-P	   . .		
//		{ 133,207,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ3	--LEN_E3-P	   . .	  
//		{ 135,208,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ4	--LEN_E3-P	   . .					
//		{ 139,195,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ5	--LEN_E3-P	   . .		
//		{ 140,210,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ6	--LEN_E3-P	   . .	
//		{ 141,196,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ7	--LEN_E3-P	   . .					
//		{ 142,198,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ8	--LEN_E3-P	   . .			
//		{ 145,199, 212,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ9	--LEN_E3-P	   . .					
//		{ 147,200, 211,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ10	--LEN_E3-P	   . .				  
//		{ 151,203,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ11	--LEN_E3-P	  . .		
//		{ 152,210,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ12	--LEN_E3-P	   . .	
//		{ 153,204,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ13	--LEN_E3-P	   . .					
//		{ 154,201,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ14	--LEN_E3-P	   . .			
//		{ 157,215,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ15	--LEN_E3-P	   . .		
//		{ 159,216,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },   //��·Ⱥ16	--LEN_E3-P	   . .		
//		{   6, 12,  23,  26,  35,  39,  44,  53,  54,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0    },	//��·Ⱥ17	--LEN_E3-P	  									
//};
///*********************************************************************************************
//	* File Name     :Single_PIN_Open_Test_Fun
//	* Description   :�����㿪·���ԣ����������ԣ�δ���岻���ԣ���Լ����ʱ��
//  * Input         :EN_bit ������Ŀ����
//  * return        :���Խ�� 1�� False 0�� True
//	* Author        :Morton
//	* Date          :2018/8/13
//*********************************************************************************************/
//uint8_t  Single_PIN_Open_Test_Fun( uint16_t EN_bit){
//		double RES ;
//		uint8_t i,t ,Open_Test_Result3 = True,Button_Status = 0;
//		for( i = 0; Single_PIN_Group[i][0] != NULL ; i ++){ 
//				Open_Two_Point(COMA,Single_PIN_Group[i][0],COMC, Single_PIN_Group[i][0]); //���ӹ���PIN
//				for( t = 1; Single_PIN_Group[i][t] != NULL  ; t ++){
//						Open_Two_Point(COMB,Single_PIN_Group[i][t],COMD, Single_PIN_Group[i][t]); //���Ӳ���PIN
//						RES =	Res_2wire_Test_Mohm();
//						if(Fixture.Mode  == Step_Test_Mode ){
//								#if defined debug_mode
//									RES = Open_RES_Value_Fun(Single_PIN_Group[i][0],Single_PIN_Group[i][t]);
//								#endif
//						}
//						if(RES <  Min_InsulationResistance)  {
//								delay_ms (2);	//����NG����ʱ2ms����һ��
//								RES = Open_Res_Test();
//								if(RES > Min_InsulationResistance){													
//										continue ;
//								}
//								cyc4or3run ();
//								lcd_printf ("%s-%s ",Pin_Name[Single_PIN_Group[i][0]],Single_PIN_Group[OpenGroup[i][t]] );
//								cyc4or3run ();
//								lcd_printf ("[%d&%d] %0.2fM  ",Single_PIN_Group[i][0],Single_PIN_Group[i][t],RES);
//								lcdpos(Cursor_y()-1,14);lcd_printf("NG");
//								if(Fixture.Mode  == Step_Test_Mode ){
//										//***��������*********
//										Button_Status = Step_debug_Open(Single_PIN_Group[i][0],Single_PIN_Group[i][t],&RES );
//										if(Button_Status == Right_Button_Pressed_Down){
//											if(RES < Min_InsulationResistance){
//												slcd_printf(Open_Data.RESULT,"%s-%s:%0.4fM@",Pin_Name[Single_PIN_Group[i][0]],Pin_Name[Single_PIN_Group[i][t]],RES);	
//												Open_Test_Result3 |= False ;				
//											}								
//										}
//										if(Button_Status == Left_Button_Pressed_Down)
//											t --;							
//										//*****���Խ���*******	
//										continue ;
//								}
//								Open_Test_Result3 |= False ;
//								sprintf(Open_Data.RESULT,"%s-%s:%0.4fM@",Pin_Name[Single_PIN_Group[i][0]],Pin_Name[Single_PIN_Group[i][t]],RES);	
//								goto Open_Test_Finish_Flag ;  //����NG��ֱ������ѭ������
//						}
//				}
//		}
//		Open_Test_Finish_Flag: //����NG��ֱ����ת���˴�
//		return Open_Test_Result3 ;	
//}
