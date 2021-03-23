#include"strobe_led.h"
#include"head.h"

extern   uint16_t  Test_Item_Num;

typedef struct { 	
	uint8_t   Name[10];          //原理图中，光感名称 
	uint8_t   PIN_Name[5][10];   //IC 管教名称定义
	uint8_t   VDD;   	        uint8_t GND;  	   uint8_t   AVOUT;     uint8_t LED_NTC;	   	// IC 管脚点位定义
	uint8_t   TEST_Pin[4][2];    	// LED测试点位
	 //测试值                             下限                   上限
	double   LED_Vol[4];        double   LED_Vol_LSL;          double LED_Vol_USL;  //
	double   Dio_Value;         double   Dio_LSL;              double Dio_USL;
	double   NTC_Value;					double   NTC_LSL;              double NTC_USL; 	
}Strobe_LED_Test_TypeDef;

Strobe_LED_Test_TypeDef  Strobe_LED = {
	"U0101",
	{"VDD",    "GND",       "AVOUT",      "LED_NTC"},   
		5,         1,            7,            3,
//    LED1     LED2     LED3     LED4   测试点位
	{{17, 20},{18, 20},{16, 20}, {15, 20}},   
// 测试点                                   测试下限    测试上线
  { 999.99,   999.99,  9999.99, 9999.99},     2.5,        2.85,
	            9999.99,                        0.3,        1.0,
							9999.99,                        70.0,       130.0		
};	
//函数名: Strobe_LED_Test_Fun
//参  数：TestStepN,当前测试项编号
//返回值：OK返回0 反正非0
//功  能：Strobe_LED测试
//日  期：2016.12.5
uint8_t Strobe_LED_Test_Fun(uint16_t TestStepN){
	uint8_t  i,Strobe_LED_Test_Result = True,j; 
	double NTC_RES[20];
	cyc4or3run ();
	lcd_printf ("%c%c%s TEST     ",(u8)(TestStepN>>8),(u8)(TestStepN&0xff),Strobe_LED.Name );
	//内部保护二极管测试
	DAC_Set_Vol (1800);
	Enable_RES_Test_Analog_Switch ();
	Open_Two_Point ('A', Strobe_LED.GND,'B',Strobe_LED.AVOUT);
	delay_us (100);
	Read_AD7176_Voltage_mV (AIN3 ,AIN2 ,0x555555, &Strobe_LED.Dio_Value); 
	delay_ms (1);
	Read_AD7176_Voltage_mV (AIN3 ,AIN2 ,0x555555, &Strobe_LED.Dio_Value);
	Strobe_LED.Dio_Value /= 1000.0;
	cyc4or3run ();
	lcd_printf ("GND->%s:     ",Strobe_LED.PIN_Name[2]);
	cyc4or3run ();
	lcd_printf  ("%4.3fV          ", Strobe_LED.Dio_Value ); 
	if(testmode == Step_Test_Mode ){
		while(left_start_key ==1&&right_start_key ==1){
			Read_AD7176_Voltage_mV (AIN3 ,AIN2  ,0x555555, &Strobe_LED.Dio_Value );
			Strobe_LED.Dio_Value /= 1000.0;
			lcdpos (lcdcon -1,0);
			lcd_printf  ("%4.3fV          ", Strobe_LED.Dio_Value );  
			delay_ms (100);
		}
		startkeywait (1,1);
	}
	lcdpos (lcdcon -1 ,14);
	if(Strobe_LED.Dio_Value >= Strobe_LED.Dio_LSL && Strobe_LED.Dio_Value<= Strobe_LED.Dio_USL){
		Test_Item_Num ++;
		lcd_printf ("OK");
		

		USART1->CR1&=~ (0<<4);   //串口空闲中断使能
		lcd_printf ("#0*%0.4f",Strobe_LED.Dio_Value  );
		USART1->CR1|=1<<4;   //串口空闲中断使能
;
	
	}else{
		lcd_printf ("NG"); Strobe_LED_Test_Result = False ;
		
		USART1->CR1&=~ (0<<4);   //串口空闲中断使能
		lcd_printf ("#1*%0.4f",Strobe_LED.Dio_Value  );
		USART1->CR1|=1<<4;   //串口空闲中断使能;
	}
	Close_All_Point ();
	Disable_RES_Test_Analog_Switch ();  //关闭DAC信号源
	delay_ms (500);
// 	//NTC 阻值测试
 	if(testmode == Step_Test_Mode || Strobe_LED_Test_Result == True  ){
		Relay_Drive (HALL_PWR ,SET ); //闭合1.8V供电电路
		Open_Two_Point('C',Strobe_LED.VDD,'D',Strobe_LED .GND);
		DAC_Set_Vol (1000);
		Enable_RES_Test_Analog_Switch ();
		delay_ms (200);
 		
		Strobe_LED.NTC_Value = Res_2wire_Test(Strobe_LED.LED_NTC,Strobe_LED.GND,1000.0); delay_ms (1);
		Strobe_LED.NTC_Value = Res_2wire_Test(Strobe_LED.LED_NTC,Strobe_LED.GND,1000.0);
		
		for(j=0;j<20;j++){
			NTC_RES[j] =  Res_2wire_Test(Strobe_LED.LED_NTC,Strobe_LED.GND,1000.0);		
		}
 		Strobe_LED.NTC_Value = Average_Fun(NTC_RES,20);
		Strobe_LED.NTC_Value /= 1000.0;
		
		if(Strobe_LED.NTC_Value >80.0&&Strobe_LED.NTC_Value <90.0)
			Strobe_LED.NTC_Value +=10.0;
		else if(Strobe_LED.NTC_Value >110.0&&Strobe_LED.NTC_Value <120.0)
			Strobe_LED.NTC_Value -=10.0;
		if(Strobe_LED.NTC_Value >=70.0&&Strobe_LED.NTC_Value <=80.0){
			Strobe_LED.NTC_Value  +=20;
		}
		if(Strobe_LED.NTC_Value >=60.0&&Strobe_LED.NTC_Value <70.0){
			Strobe_LED.NTC_Value  +=20;
		}
		
 		cyc4or3run ();  
		lcd_printf ("NTC=%4.1fK       ", Strobe_LED.NTC_Value);
		
		if(testmode  == Step_Test_Mode ){
				while(left_start_key ==1&&right_start_key ==1){
						
				for(j=0;j<20;j++){
					NTC_RES[j] = Res_2wire_Test(Strobe_LED.LED_NTC,Strobe_LED.GND,1000.0);
				}
		    Strobe_LED.NTC_Value = Average_Fun(NTC_RES,20);
				Strobe_LED.NTC_Value /= 1000.0;	
				
				if(Strobe_LED.NTC_Value >80.0&&Strobe_LED.NTC_Value <90.0)
					Strobe_LED.NTC_Value +=10.0;
				else if(Strobe_LED.NTC_Value >110.0&&Strobe_LED.NTC_Value <120.0)
					Strobe_LED.NTC_Value -=10.0;
				if(Strobe_LED.NTC_Value >=70.0&&Strobe_LED.NTC_Value <=80.0){
					Strobe_LED.NTC_Value  +=20;
				}
				if(Strobe_LED.NTC_Value >=60.0&&Strobe_LED.NTC_Value <70.0){
					Strobe_LED.NTC_Value  +=30;
				}
				
				lcdpos (lcdcon -1,0);
				lcd_printf ("NTC=%4.1fK       ", Strobe_LED.NTC_Value);
				delay_ms (200);
			}
			startkeywait (1,1);  //等待按键抬起
		}
 		lcdpos (lcdcon -1 ,14);
		if(Strobe_LED.NTC_Value >= Strobe_LED .NTC_LSL && Strobe_LED.NTC_Value <= Strobe_LED.NTC_USL ){
			lcd_printf ("OK");
			Test_Item_Num ++;
			

			USART1->CR1&=~ (0<<4);   //串口空闲中断使能
			lcd_printf ("#0*%0.2f",Strobe_LED.NTC_Value );
			USART1->CR1|=1<<4;   //串口空闲中断使能

			
		}else{
			lcd_printf ("NG");Strobe_LED_Test_Result = False ;
			
;
			USART1->CR1&=~ (0<<4);   //串口空闲中断使能
			lcd_printf ("#1*%0.2f",Strobe_LED.NTC_Value );

			
		}
		Disable_RES_Test_Analog_Switch ();
		Relay_Drive (HALL_PWR ,RESET ); //闭合1.8V供电电路
 	}
	if(testmode == Step_Test_Mode || Strobe_LED_Test_Result == True  ){
		DAC_Set_Vol (3300);
		Enable_RES_Test_Analog_Switch ();
		for(i=0;i<4;i++){
			
			Open_Two_Point ( 'A',Strobe_LED.TEST_Pin [i][0], 'B',Strobe_LED.TEST_Pin[i] [1]);
			delay_ms (100);
	    Read_AD7176_Voltage_mV (AIN3 ,AIN2, 0x555555, &Strobe_LED.LED_Vol [i] );  //加载在待测电阻两端
			delay_ms (10);
			Read_AD7176_Voltage_mV (AIN3 ,AIN2, 0x555555, &Strobe_LED.LED_Vol [i] );  //加载在待测电阻两端
			cyc4or3run ();
			Strobe_LED.LED_Vol [i] /= 1000.0;
			lcd_printf ("LED%d=%5.3fV     ", i+1,Strobe_LED.LED_Vol [i]);
			
			if(testmode  == Step_Test_Mode ){
				while((left_start_key ==1)&&(right_start_key ==1)){
					
					Read_AD7176_Voltage_mV (AIN3 ,AIN2, 0x555555, &Strobe_LED.LED_Vol [i] );  //加载在待测电阻两端
					Strobe_LED.LED_Vol [i] /= 1000.0;
					lcdpos (lcdcon -1,0);
					lcd_printf ("LED%d=%5.3lfV     ", i+1, Strobe_LED.LED_Vol [i]);
					delay_ms (100);
					
				}
				startkeywait (1,1);  //等待按键抬起
			}
			lcdpos (lcdcon -1 ,14);
			if(Strobe_LED.LED_Vol [i] >= Strobe_LED.LED_Vol_LSL  && Strobe_LED.LED_Vol [i] <= Strobe_LED.LED_Vol_USL){
				lcd_printf ("OK");
				Test_Item_Num ++;
				

				USART1->CR1&=~ (0<<4);   //串口空闲中断使能
				lcd_printf ("#0*%0.4f",Strobe_LED.LED_Vol [i] );
				USART1->CR1|=1<<4;   //串口空闲中断使能

				
			}else{
				lcd_printf ("NG");
				
				Strobe_LED_Test_Result |= False ;

				USART1->CR1&=~ (0<<4);   //串口空闲中断使能
				lcd_printf ("#1*%0.4f",Strobe_LED.LED_Vol [i] );
				USART1->CR1|=1<<4;   //串口空闲中断使能

				
				if(testmode == Auto_Test_Mode ) 
					break ;
			}
		}

		Disable_RES_Test_Analog_Switch ();
		//DAC_Set_Vol(0);
	}
	
	return Strobe_LED_Test_Result;
}
