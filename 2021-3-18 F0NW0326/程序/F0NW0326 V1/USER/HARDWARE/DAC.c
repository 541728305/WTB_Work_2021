#include "DAC.h"
#include "lcd3033.h"
#include "delay.h"
#include "sup_fun.h"
#include "other.h"
#include "ad7176.h"
#include <stdio.h>
#include "global.h"
#include "stm32f10x_dac.h"
#define Hardware_Gain   5.7

/*********************************************************************************************
	* File Name     : Dac_Init
	* Description   : DAC通道1输出初始化
  * Input         : vol:0~3300,代表0~3.3V
	* return        : Switch ON Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/

void Dac_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		DAC_InitTypeDef DAC_InitType;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能PORTA通道时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //模拟输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 输出高
						
		DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
		DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
		DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
		DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
		DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1

		DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
		
		DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
}




/*********************************************************************************************
	* File Name     : DAC_Set_Vol
	* Description   : DAC_Set_Vol
  * Input         : vol:0~3300,代表0~3.3V
	* return        : Switch ON Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void DAC_Set_Vol_Ref(u16 vol){
	  double  temp ;
		temp =(float) vol/Hardware_Gain;
		temp=temp*4096/3300;
		DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
		delay_ms(20);
}


/*********************************************************************************************
	* File Name     : DAC_Set_Vol
	* Description   : DAC_Set_Vol
  * Input         : vol:0~3300,代表0~3.3V
	* return        : Switch ON Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
uint8_t  DAC_Set_Vol(u16 REF,double Tolerance,uint8_t Display_EN){
		int i = 50,Flag = 0;
		double  AD_Vol,SET_DAC = REF;
		DAC_Set_Vol_Ref(REF);
		Read_AD7176_Average_Voltage_mV(AIN0 ,AIN4,30,&AD_Vol);
		if(REF < 50)
			return 0;
		if(AD_Vol > (REF-200) && AD_Vol < (REF+200)  ){
			while(i > 0){				
					SET_DAC -= (AD_Vol-REF);						
					DAC_Set_Vol_Ref(SET_DAC);	
					Read_AD7176_Average_Voltage_mV(AIN0 ,AIN4,50,&AD_Vol);
					if(AD_Vol>(REF-Tolerance)&&AD_Vol <(REF+Tolerance))
						break;
					i --;
			}
			if(i==0)
				Flag = 1;
		}else{
			Flag = 1;
		}
		if(Display_EN ){
			cyc4or3run();
			lcd_printf  ("V=%3.2fmV",AD_Vol);
		}
		return Flag;
}
#include "other.h"
/*********************************************************************************************
	* File Name     : Self_Test_DAC_line
	* Description   : Self_Test_DAC_line ON Status Test
  * Input         : vol:0~3300,代表0~3.3V
	* return        : Switch ON Test_Result
	* Version       : V1.0
	* Author        : Morton
	* Date          : 24-June-2019
*********************************************************************************************/
void Self_Test_DAC_line( u16 vol){
		double AD_Vol,V[100];
		uint16_t  i,Flag=0;
		int DAC_Set_Vol_Result = True;
		Dac_Init();
		Relay_Drive (K15_Src_Choice|K12_10R_Ref|K10_Ref_IN0_1,SET);
		delay_ms (100);
		DAC_Set_Vol(vol,5.0,0);
		for(i=0;i<100;i++){
					Read_AD7176_Average_Voltage_mV(AIN0 ,AIN4,50,&AD_Vol);
					if(AD_Vol < 2050.0 && AD_Vol > 1950.0){ //电压在20%内波动OK
						V[Flag] = AD_Vol;
						Flag++;
					}
					else
						Flag = 0;
					if(Flag >10){
							DAC_Set_Vol_Result = True ;
							cyc4or3run ();
							lcd_printf  ("V=%3.2fmV",Average_Fun (V,10));
							lcdpos (lcdcon-1,14);
							lcd_printf  ("OK");
							break ;
					}else{
							DAC_Set_Vol_Result = False ;
					}
					delay_ms (1);
		}
		if(DAC_Set_Vol_Result == False){
				cyc4or3run ();
				lcd_printf  ("V=%3.2fmV NG",AD_Vol);
				beep (2,100);
				while(left_start_key == 0 |right_start_key == 0) delay_ms (10);
		}
		Relay_Drive (K15_Src_Choice|K12_10R_Ref|K10_Ref_IN0_1,RESET);
		delay_ms (200);
}
