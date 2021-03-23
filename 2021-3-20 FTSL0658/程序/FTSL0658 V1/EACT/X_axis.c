#include "X_axis.h"
#include "modbus.h"
#include "delay.h"
#include "usart.h"
#include "lcd3033.h"	
#include "other.h"
#include "sup_fun.h"
#include "global.h"
#include "hold_data.h"
#include "menu.h"
#include "base_Config.h"

extern ACT_Parameter_Def ACT_Parameter[];
Act_typedef X_Axis = {"X ��"};



uint8_t Debug_Set = DISABLE;	


/*********************************************************************************************
 * File Name     : Take_OFF_Products
 * Description   : ���϶���
 * Input         : ��
 * return        : ��
 * Version       : 
 * Author        : Morton
 * Date          : 2019/6/18
*********************************************************************************************/
uint8_t Rank_Num =0 ;
uint8_t NG_Rank_Num = 0;
void Take_OFF_Products( uint8_t Result){
	if(Get_Take_OFF_Enable_bit(0) == DISABLE )
		return ;
	if(Get_Take_OFF_Enable_bit(1)== DISABLE && Result == False )
		return ;
	
	TAKE_OFF_EACT_MOVE(ACT_Source,ENABLE );
	delay_ms (80);
	while(Safe_Grating_Sensor == 0)	delay_ms (100);
	Valve_Drive (Vertical_Move ,SET); //������ѹ
	while( Read_Sensor_Status(Vertical_Down_Sensor));
	Valve_Drive(GAS_Pressure,SET );      //����
	delay_ms (500);
	while(Safe_Grating_Sensor == 0)delay_ms (100);
	Valve_Drive(Vertical_Move ,RESET); //������ѹ
	while( Read_Sensor_Status(Vertical_Up_Sensor));
	Valve_Drive(Relax_Product ,RESET);
	
	delay_ms (100);
	if(Result == True ){
		TAKE_OFF_EACT_MOVE(ACT_OK1+Rank_Num,ENABLE );
		if(Get_Take_OFF_Enable_bit(2)== ENABLE){
				Valve_Drive (Vertical_Move ,SET); //������ѹ
				while( Read_Sensor_Status(Vertical_Down_Sensor));
		}
		delay_ms (80);
	  Valve_Drive(GAS_Pressure,RESET );      //����
		if(Get_Take_OFF_Enable_bit(2)== ENABLE){
			  delay_ms (10);
				Valve_Drive(Vertical_Move ,RESET); //������ѹ
				while( Read_Sensor_Status(Vertical_Up_Sensor));
		}		
		
		
		Rank_Num ++;
	}else{
		TAKE_OFF_EACT_MOVE(ACT_NG1,ENABLE );
			delay_ms (80);
	    Valve_Drive(GAS_Pressure,RESET );      //����
	}

	if(Rank_Num == Get_PASS_Row_Num(0)){	 //�������̻�
		Drive_Baipanji();		
		Rank_Num = 0;
	}
}











/**************************************************************************
	* File Name     : Init_Up_Down_EACT
	* Description   : ��ʼ�������˶����
  * Input         : ��
  * return        : ��ȡOK 0 ��֮��0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
void Init_Take_OFF_EACT(void){
	uint16_t i = 0;
		
	if(ACT_Parameter[ACT_Take_Product_EN].data != ENABLE){
		return ;
	}

		if(left_start_key == 0 && right_start_key == 0){
			delay_ms (10);
			for( i = 0; i < 100; i ++ ){
				if(left_start_key == 1 || right_start_key == 1)
					break ;
				delay_ms (50);
			}
			if( i>80)
				Take_Product_EACT_set();
		}
	uart3_init(38400);
	X_Axis.ID = 0x01;
	X_Axis.Orig_Direction = 1;
	X_Axis.Stroke = 600;
	X_Axis.Max_Speed = 500;
	X_Axis.Run_Speed = 300;
	X_Axis.Protect_Mode = HOLD  ;	
	X_Axis.Protect_Range_LSL = 0;
	X_Axis.Protect_Range_USL = 400;	
	cyc4or3run ();
	lcd_printf("%s��ͨѶ����... ",X_Axis.Name);	
	while(FWriteSingleCoil(X_Axis.ID,Y30_Serial_EN,ENABLE) != LEC_Normal ) delay_ms(100);
	lcdpos (lcdcon-1,14);	
	lcd_printf ("OK"); 
	delay_ms (100);
	cyc4or3run ();
	lcd_printf("%s���״̬... ",X_Axis.Name );	lcdpos (lcdcon-1,14);
	if(Read_InputStatus(X_Axis.ID,X4F_ALARM) == SET ){
			lcd_printf ("NG");
			FWriteSingleCoil(X_Axis.ID,Y1B_RESET,SET );
			while(Read_InputStatus(X_Axis.ID,X4F_ALARM) != SET) delay_ms (100);
			FWriteSingleCoil(X_Axis.ID,Y1B_RESET,RESET);
	}
	lcd_printf ("OK"); 
  delay_ms (100);
	cyc4or3run ();
	lcd_printf("%s����ϵ�... ",X_Axis.Name);	lcdpos (lcdcon-1,14);
	FWriteSingleCoil(X_Axis.ID,Y19_SVON,ENABLE);
	while(Read_InputStatus(X_Axis.ID,X49_SVRE) != SET );
	lcd_printf ("OK"); 
 delay_ms (100);
	cyc4or3run ();
	lcd_printf("%s��׻���... ",X_Axis.Name);	lcdpos (lcdcon-1,14);
	FWriteSingleCoil(X_Axis.ID,Y1C_SETUP,ENABLE);
	while(Read_InputStatus(X_Axis.ID,X4A_SETON) != SET || Read_InputStatus(X_Axis.ID,X48_BUSY) != RESET || Read_InputStatus(0x01,X4B_INP ) != SET ){
		if(Safe_Grating_Sensor == SEN_SET ){
				FWriteSingleCoil(X_Axis.ID,Y18_HOLD,ENABLE);	
				lcdpos(lcdcon-1, 0); lcd_printf("��դ���ڵ�...   ");
				while(Safe_Grating_Sensor == SEN_SET ) delay_ms (100);
				delay_ms (300);
				lcdpos(lcdcon-1, 0); lcd_printf("%s��׻���... ",X_Axis.Name);
				FWriteSingleCoil(X_Axis.ID,Y18_HOLD,DISABLE);			
		}else if(MOVE_Check_Sensor == SEN_RESET){
				FWriteSingleCoil(X_Axis.ID,Y18_HOLD,ENABLE);	
				lcdpos(lcdcon-1, 0); lcd_printf("��������δ̧��  ");
				while(MOVE_Check_Sensor == SEN_RESET ) delay_ms (100);
				delay_ms (300);
				lcdpos(lcdcon-1, 0); lcd_printf("%s��׻���... ",X_Axis.Name);
				FWriteSingleCoil(X_Axis.ID,Y18_HOLD,DISABLE);
		}
	}
	lcdpos (lcdcon-1,14);
	lcd_printf ("OK"); 
	delay_ms (100);
	X_Axis.Previous_Coordinate = 0.0;
	FWriteSingleCoil(X_Axis.ID,Y1C_SETUP,DISABLE);	
	FWriteSingleCoil(X_Axis.ID,Y1C_SETUP,DISABLE);
	FWriteSingleCoil(X_Axis.ID,Y1C_SETUP,DISABLE);
}

/***************************************************
	* File Name     : Take_Product_Enable_Set
	* Description   : Take_Product_Enable_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_Enable_Set( uint8_t Num ){
	char str[2][17]={"      �ر�      ","      ����      "};
	uint8_t 	Val = ACT_Parameter[Num].data;	
	Choice_Menu( (char *)ACT_Parameter[Num].Name,str,2,&Val);
	ACT_Parameter[Num].data = Val;
	Save_Hold_Reg_data(Num);	
}
/***************************************************
	* File Name     : Take_Product_Num_Set
	* Description   : Take_Product_Num_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_Num_Set( uint8_t Num,char *Unit ){

		 uint32_t  dat = ACT_Parameter[Num].data;	
		 Choice_Menu_Num((char *)ACT_Parameter[Num].Name ,
														 ACT_Parameter[Num].LSL ,
														 ACT_Parameter[Num].USL ,
														 ACT_Parameter[Num].Step_Length ,
														 &dat, Unit);		
		ACT_Parameter[Num].data = dat;
		Save_Hold_Reg_data(Num);
	
}
/***************************************************
	* File Name     : Take_Product_Num_Set
	* Description   : Take_Product_Num_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_Position_Set( uint8_t Num,uint8_t Row ){
	uint8_t i = 0,key =0;
	double  Coordinate = 0.0;
	if(ACT_Parameter[ACT_Take_Product_EN].data != ENABLE){
		lcdreset();
		lcdpos (2,0); lcd_printf ("���Ϲ���δ����");
		step_test_mode_get_key ();
		return ;
	}
	FWriteSingleCoil(X_Axis.ID ,Y19_SVON,DISABLE );		
	for(i = 0; i < Row; i ++){
		lcdreset ();
		lcdpos(0,0);			
		lcd_printf("%s",ACT_Parameter[Num +i ].Name  );
		lcdpos(1,0);
		lcd_printf("��Χ:%3.0f-%3.0fmm  ",ACT_Parameter[Num+i].LSL ,ACT_Parameter[Num+i].USL );
		Get_LEC_Current_Postion(X_Axis.ID,&Coordinate);
		lcdpos(2,0);	
		lcd_printf("X=%8.3fmm    ",ACT_Parameter[Num+i].data ); //
		lcdpos(3,0);lcd_printf("L:��һ��  R:����");;
		while(1){
			Get_LEC_Current_Postion(X_Axis.ID,&Coordinate);
			lcdpos(2,0);	
			lcd_printf("Y=%8.3fmm    ",Coordinate); //
			
			key = GetKey_Status();
			if(key == Left_Button_Pressed_Down ){
				break ;
			}else if(key == Right_Button_Pressed_Down ){
				if( Coordinate > ACT_Parameter[Num +i].LSL && Coordinate < ACT_Parameter[Num +i].USL ){					
						lcdpos(3,0);lcd_printf("���ݱ���...     ");
						Get_LEC_Current_Postion(X_Axis.ID,&Coordinate);
						ACT_Parameter[Num +i ].data = Coordinate;
						Save_Hold_Reg_data(Num+i);
						lcdpos(3,0);lcd_printf("���ݱ���OK      ");
						break ;
				}else {
						lcdpos(2,0);	
						lcd_printf("�������ݳ����"); //
				
				}		
				startkeywait (1,1);
			}
		}
		startkeywait (1,1);
	}	
	Debug_Set = ENABLE ;	
}
/***************************************************
	* File Name     : Take_Product_EACT_Enable_Set
	* Description   : Take_Product_EACT_Enable_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_Enable_Set(void){
	uint8_t Privious_Set = ACT_Parameter[ACT_Take_Product_EN].data ;
	Take_Product_Enable_Set(ACT_Take_Product_EN);
	if(Privious_Set == DISABLE && ACT_Parameter[ACT_Take_Product_EN].data == ENABLE){
		Init_Take_OFF_EACT();
	}else if(Privious_Set == ENABLE && ACT_Parameter[ACT_Take_Product_EN].data == DISABLE ){
		FWriteSingleCoil(X_Axis.ID ,Y19_SVON,DISABLE );		
	}
}
/***************************************************
	* File Name     : Take_Product_NG_Enable_Set
	* Description   : Take_Product_NG_Enable_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_NG_Enable_Set(void){
	Take_Product_Enable_Set(ACT_NG_EN);
}


/***************************************************
	* File Name     : Take_Product_NG_Enable_Set
	* Description   : Take_Product_NG_Enable_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_Push_Enable_Set(void){
	Take_Product_Enable_Set(ACT_Push_Procuct);
}

/***************************************************
	* File Name     : Take_Product_EACT_Speed_Set
	* Description   : Take_Product_EACT_Speed_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_Speed_Set(void){
		Take_Product_Num_Set(ACT_Speed,"mm/s");
}
/***************************************************
	* File Name     : Take_Product_EACT_NG_Num_Set
	* Description   : Take_Product_EACT_NG_Num_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_NG_Num_Set(void){
			Take_Product_Num_Set(ACT_NG_NUM,"��");
}
/***************************************************
	* File Name     : Take_Product_EACT_OK_Num_Set
	* Description   : Take_Product_EACT_OK_Num_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_OK_Num_Set(void){
		Take_Product_Num_Set(ACT_OK_NUM,"��");
}
/***************************************************
	* File Name     : Take_Product_EACT_OK_Postion_Set
	* Description   : Take_Product_EACT_OK_Postion_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_OK_Postion_Set(void){
	Take_Product_Position_Set(ACT_OK1,ACT_Parameter[ACT_OK_NUM].data);
}
/***************************************************
	* File Name     : Take_Product_EACT_NG_Postion_Set
	* Description   : Take_Product_EACT_NG_Postion_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_NG_Postion_Set(void){
	Take_Product_Position_Set(ACT_NG1,ACT_Parameter[ACT_NG_NUM].data);
}
/***************************************************
	* File Name     : Take_Product_EACT_Standby_Postion_Set
	* Description   : Take_Product_EACT_Standby_Postion_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_Standby_Postion_Set(void){
	Take_Product_Position_Set(ACT_Standby,1);
}
/***************************************************
	* File Name     : Take_Product_EACT_Product_Postion_Set
	* Description   : Take_Product_EACT_Product_Postion_Set
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 16-April-2020
***************************************************/
void  Take_Product_EACT_Product_Postion_Set(void){
		Take_Product_Position_Set(ACT_Source,1);
}

/***************************************************
	* File Name     : Show_Take_PASS_Product
	* Description   : Show_Take_PASS_Product
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 9-May-2020
***************************************************/
void Show_Take_PASS_Product(){
	if(Debug_Set == ENABLE 	 ){
		Init_Take_OFF_EACT ();
		Debug_Set = DISABLE ;
	}
	Take_OFF_Products(True );
}
/***************************************************
	* File Name     : Show_Take_FAIL_Product
	* Description   : Show_Take_FAIL_Product
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 9-May-2020
***************************************************/
void Show_Take_FAIL_Product(){
	if(Debug_Set == ENABLE 	 ){
		Init_Take_OFF_EACT ();
		Debug_Set = DISABLE ;
	}
	Take_OFF_Products(False);
}


Menu_List_Typedef Eact_Take_Product_List[] = 
{
	{"���Ͽ���      ",Take_Product_EACT_Enable_Set           },
	{"�������Ͽ���  ",Take_Product_NG_Enable_Set             },	
	{"�����Ƿ���ѹ  ",Take_Product_Push_Enable_Set           },		
	{"�ٶ�����      ",Take_Product_EACT_Speed_Set            },
	{"��Ʒ����      ",Take_Product_EACT_OK_Num_Set           },
	{"����Ʒ����    ",Take_Product_EACT_NG_Num_Set           },
	{"���ϵ�        ",Take_Product_EACT_Product_Postion_Set  },
	{"������        ",Take_Product_EACT_Standby_Postion_Set  },	
	{"��Ʒ��        ",Take_Product_EACT_OK_Postion_Set       },	
	{"����Ʒ��      ",Take_Product_EACT_NG_Postion_Set       },	
	{"��Ʒȡ����ʾ  ",Show_Take_PASS_Product                 },	
	{"����Ʒȡ����ʾ",Show_Take_FAIL_Product                 },	
	
	{NULL }
};



/**************************************************************************
	* File Name     : Up_Down_EACT_set
	* Description   : �����˶���ײ�������
  * Input         : ��
  * return        : ��ȡOK 0 ��֮��0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t  Take_Product_EACT_set(void)
{
	if(Fixture.Take_Product == DISABLE ){
		lcdreset ();
		lcdpos (2,0); lcd_printf("����������");
		step_test_mode_get_key ();
		return 1;
	}else{
		Menu_List_Fun("���µ������",Eact_Take_Product_List);	
		if(ACT_Parameter[ACT_Take_Product_EN].data == ENABLE ){
			Init_Take_OFF_EACT();
			Running_Position(X_Axis,Absolute_Coordinate,ACT_Parameter[ACT_Standby].data,ACT_Parameter[ACT_Speed].data,ENABLE);	
		}
  }	
	RevertStartupScreen ();//��ʾ����	
	return 0;
}

/**************************************************************************
	* File Name     :  Up_Down_EACT_set
	* Description   : �����˶���ײ�������
  * Input         : ��
  * return        : ��ȡOK 0 ��֮��0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t TAKE_OFF_EACT_MOVE( uint8_t Num,uint8_t Pos_Check){
	uint8_t Temp = 0 ;
	if(ACT_Parameter[ACT_Take_Product_EN].data != ENABLE){
		return 0;
	}
	while( Read_Sensor_Status(Vertical_Up_Sensor));
	X_Axis.Protect_Mode      =  HOLD  ;
	X_Axis.Protect_Range_LSL = 0;
	X_Axis.Protect_Range_USL = ACT_Parameter[ACT_Standby].data; 
	Temp = Running_Position(X_Axis,Absolute_Coordinate,ACT_Parameter[Num].data,ACT_Parameter[ACT_Speed].data,Pos_Check);	
	return Temp;
}
