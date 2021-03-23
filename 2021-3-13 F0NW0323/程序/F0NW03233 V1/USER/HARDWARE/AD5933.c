#include "AD5933.h"
#include "sys.h"
#include "sup_fun.h"
#include "delay.h"
#include "lcd3033.h"
#include "math.h"
#include "myiic.h"
#include "usart.h"
#include "sup_fun.h"
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"	  
#include "other.h"
#include "math.h"
#define K9_Calibration_10K  K23_CAP_REF

#define I2C0_DELAY_TIME  10

typedef struct {
	
		uint8_t  Vpp[Range_Num]; //������ѹ
		uint8_t  PGA_Gain[Range_Num];
		double   frequency[Range_Num];
		double   Calibration_resistor[Range_Num];
		double   Gain_resistor[Range_Num];
		double   Gain_Coefficient[Range_Num];
		uint32_t Calibration_Res_Relay[Range_Num];
		uint32_t RFB_Relay[Range_Num];
	
}Network_analyzer_def;



Network_analyzer_def Impedance_Test = {
		{ AD5933_Vpp_1000mV      },
		{ AD599_PGA_Gain_1X     },
		{ 30000,                },
		{ 10000,                },
		{ 10000,                },	
		{   0.0,                },	
    { K9_Calibration_10K    },
    { 0x00000000,           }		
};

/*********************************************************************
	* ��������Init_Mini_CAP_Test_GPIO
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/
static void Init_Mini_CAP_Test_GPIO(void )
{	
	//PB1 SDA  PB0 SCL
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1); 		
}
/*********************************************************************
	* ��������I2C0__Start
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/
void I2C0_Start(void){
	I2C0_SDA_OUT();     
	I2C0_SDA=1;	  
	I2C0_SCL=1;
	delay_us(I2C0_DELAY_TIME);
 	I2C0_SDA=0; 
	delay_us(I2C0_DELAY_TIME);
	I2C0_SCL=0;
	delay_us(I2C0_DELAY_TIME);
}
 /*********************************************************************
	* ��������I2C0_Stop
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/
void I2C0_Stop(void){
	I2C0_SDA_OUT();
	I2C0_SCL=0;
	I2C0_SDA=0;
 	delay_us(I2C0_DELAY_TIME);
	I2C0_SCL=1; 
	I2C0_SDA=1;
	delay_us(I2C0_DELAY_TIME);							   	
}
/*********************************************************************
	* ��������I2C0_NAck
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/		    
void I2C0_NAck(void){
	I2C0_SCL=0;
	I2C0_SDA_OUT();
	I2C0_SDA=1;
	delay_us(I2C0_DELAY_TIME);
	I2C0_SCL=1;
	delay_us(I2C0_DELAY_TIME);
	I2C0_SCL=0;
}	
/*********************************************************************
	* ��������I2C0_Ack
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/		    
void I2C0_Ack(void){
	I2C0_SCL=0;
	I2C0_SDA_OUT();
	I2C0_SDA=0;
	delay_us(I2C0_DELAY_TIME);
	I2C0_SCL=1;
	delay_us(I2C0_DELAY_TIME);
	I2C0_SCL=0;
}
/*********************************************************************
	* ��������I2C0_Wait_Ack
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/
uint8_t I2C0_Wait_Ack(void){
	uint8_t ucErrTime=0;
	I2C0_SDA_IN();      
	I2C0_SDA=1;delay_us(I2C0_DELAY_TIME);	   
	I2C0_SCL=1;delay_us(I2C0_DELAY_TIME);	 
	while(I2C0_READ_SDA){
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C0_Stop();
			lcd_printf ("Device NO ACK   ");
			return 1;
		}
	}
	I2C0_SCL=0;
	delay_us(I2C0_DELAY_TIME);	 
	return 0;  
}
/*********************************************************************
	* ��������I2C0_Send_Ack
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/
void I2C0_Send_Ack(u8 ack)
{
	I2C0_SDA_OUT();
	if(ack)	I2C0_SDA=1;
	else    I2C0_SDA=0;
	delay_us(I2C0_DELAY_TIME); 
	I2C0_SCL=1;
	delay_us(I2C0_DELAY_TIME); 
	I2C0_SCL=0;
}
/*********************************************************************
	* ��������I2C0_Send_Byte
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/					  
void I2C0_Send_Byte(uint8_t txd){                        
    uint8_t t;   
		I2C0_SDA_OUT(); 	    
    I2C0_SCL=0;
    for(t=0;t<8;t++){              
		if(txd&0x80)
			I2C0_SDA=1;
		else
			I2C0_SDA=0;
		txd<<=1; 	  
		delay_us(I2C0_DELAY_TIME);   
		I2C0_SCL=1;
		delay_us(I2C0_DELAY_TIME); 
		I2C0_SCL=0;	
		delay_us(I2C0_DELAY_TIME);
    }	 
} 

/*********************************************************************
	* ��������I2C0_Read_Byte
	* ��  �ܣ���
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/8/13
**********************************************************************/		
uint8_t I2C0_Read_Byte(unsigned char ack){
	unsigned char i,receive=0;
	I2C0_SDA_IN();
  for(i=0;i<8;i++ )
	{
    I2C0_SCL=0; 
    delay_us(I2C0_DELAY_TIME);
		I2C0_SCL=1;
    receive<<=1;
    if(I2C0_READ_SDA)
			receive++;   
		delay_us(I2C0_DELAY_TIME); 
   }					 
   if (!ack)
     I2C0_NAck();
   else
     I2C0_Ack(); 
   return receive;
}
			 				          
/*****************************************************************************************
	* ��������AD5933_write
	* ��  �ܣ�AD5933д����
	* ��  ����Reg_Addr �Ĵ�����ַ Write_Data ��д������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static uint8_t AD5933_write(uint8_t Reg_Addr,uint8_t  Write_Data ){
	uint8_t Result = 0;
	I2C0_Start();
	I2C0_Send_Byte((AD5933_Slave_Addr<<1)|Write);
	Result |= I2C0_Wait_Ack();
	I2C0_Send_Byte(Reg_Addr);
	Result |= I2C0_Wait_Ack();
	I2C0_Send_Byte(Write_Data);
	Result |= I2C0_Wait_Ack();
	I2C0_Stop();
	return Result;
}

/*---------------------------------
u8 AD5933CreateBlockCommand(u8 RegAdd)
���ܣ������Ĵ���ָ��
������RegAdd   �Ĵ�����   
����: 1 ����ʧ�� �� 0 �����ɹ�
------------------------------------*/
static u8 AD5933_Create_Block_Command(u8 RegAdd)
{
	 I2C0_Start();			        //��������
   I2C0_Send_Byte((AD5933_Slave_Addr<<1)|Write);//��������ID д
   I2C0_Wait_Ack();		     	//���մ�����Ӧ��λ	
	 I2C0_Send_Byte(0xB0);//������ָ��
   I2C0_Wait_Ack();		     	//���մ�����Ӧ��λ
   I2C0_Send_Byte(RegAdd);   //���ʹ�������ָ���ַ----���Ĵ����͵�ַ
   I2C0_Wait_Ack();		     	//���մ�����Ӧ��λ�־
   I2C0_Stop();		//��������ָ�������ʹ��Ȩ��
   return (0);
}
/*****************************************************************************************
	* ��������AD5933_read
	* ��  �ܣ�AD5933��ȡ����
	* ��  ����Reg_Addr �Ĵ�����ַ 
	* ����ֵ����ȡ������
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static uint8_t AD5933_read(uint8_t Reg_Addr){
	uint8_t Result = 0;	
	AD5933_Create_Block_Command(Reg_Addr);
	I2C0_Start();			        //��������
	I2C0_Send_Byte((AD5933_Slave_Addr<<1)|Read); 
	I2C0_Wait_Ack();	     	//���մ�����Ӧ��λ
	Result=I2C0_Read_Byte(0);
	IIC_Stop();  
	return Result;
}

/*****************************************************************************************
	* ��������AD5933_Set_Start_Fre
	* ��  �ܣ�������ʱ����������DDS��ʼ���Ƶ��
						��ʼƵ���� = [���Ƶ��/(MCLK/4)]*2^27
	* ��  ����Fre  ������Ƶ��ֵ
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static void AD5933_Set_Start_Fre( double Fre ){
		double Start_frequency = (Fre/(AD5933_MCLK/4))*pow(2,27);
		uint32_t Start_frequency_Code = (uint32_t)Start_frequency;
		#ifdef LCR_debug  			
			Uart_Printf(USART1, "Start_frequency=%0.3f   %08X\r\n",Fre,Start_frequency_Code);			
		#endif
		AD5933_write ( 0x84, (Start_frequency_Code)&0xFF);
		AD5933_write ( 0x83, (Start_frequency_Code>>8)&0xFF);    
		AD5933_write ( 0x82, (Start_frequency_Code>>16)&0xFF);
}

/*****************************************************************************************
	* ��������AD5933_Set_Start_Fre
	* ��  �ܣ�������ʱ�������������Ƶ������
						��ʼƵ�������� = [���Ƶ��/(MCLK/4)]*2^27
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static void AD5933_Set_frequency_increment( double frequency_increment ){
		double frequency = (frequency_increment/(AD5933_MCLK/4))*pow(2,27);
		uint32_t frequency_Code = (uint32_t)frequency;
		#ifdef LCR_debug  			
			Uart_Printf(USART1, "frequency_increment=%0.3f   %08X\r\n",frequency_increment,frequency_Code);			
		#endif
		AD5933_write ( 0x87, (frequency_Code)&0xFF);
		AD5933_write ( 0x86, (frequency_Code>>8)&0xFF);    
		AD5933_write ( 0x85, (frequency_Code>>16)&0xFF);	
}
/*****************************************************************************************
	* ��������AD5933_Set_Start_Fre
	* ��  �ܣ�������ʱ�������������Ƶ������
						��ʼƵ�������� = [���Ƶ��/(MCLK/4)]*2^27
	* ��  ����Ƶ��������,���511
  * ����ֵ: ��
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static void AD5933_Set_frequency_increment_Number( uint16_t frequency_increment_Number ){
		frequency_increment_Number &= 0x1FF;		
		#ifdef LCR_debug  			
			Uart_Printf(USART1, "frequency_increment=%0.3f   %08X\r\n",frequency_increment_Number,frequency_increment_Number);			
		#endif
		AD5933_write ( 0x89, (frequency_increment_Number)&0xFF);
		AD5933_write ( 0x88, (frequency_increment_Number>>8)&0xFF);    
}
/*****************************************************************************************
	* ��������AD5933_Set_settling_time
	* ��  �ܣ������¼��������� , ���511*4 = 2044*33.33us=68.126ms 
	* ��  ����time����ʱ��,��λus
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static void AD5933_Set_settling_time( double  time){
		uint16_t settling_time_Code;
		uint16_t settling_time = (uint32_t)(time /33.33);
		if(settling_time <= 0x1F){
			settling_time_Code = settling_time;
		}else if(settling_time > 0x1F && settling_time <=1022 ){
			settling_time_Code = ((settling_time&0x1F)|(1<<9));
		}else {
			settling_time_Code = ((settling_time&0x1F)|(3<<9));
		}
		#ifdef LCR_debug  			
			Uart_Printf(USART1, "settling_time=%0.3fus   %d   %04X\r\n",time,settling_time,settling_time_Code);			
		#endif
		 AD5933_write ( 0x8B, settling_time_Code&0xFF);
		 AD5933_write ( 0x8A, settling_time_Code>>8);
}
/*****************************************************************************************
	* ��������Get_Real_imag_data
	* ��  �ܣ���ȡʵ�����鲿�Ĵ���ֵ 
	* ��  ����data,���ݴ洢��ַ
	* ����ֵ����ȡ�ɹ�����0,��֮����1
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static uint8_t  Get_Real_imag_data (signed short int *data ,uint8_t CNT ){
	uint8_t i;
	unsigned int real_byte_high;
	unsigned int real_byte_low;
	unsigned int imag_byte_high;
	unsigned int imag_byte_low;
	signed short int imag_data;
	signed short int real_data;//write(output3,25); // output "start sweep" to uart
	uint8_t status_register;
	for( i = 0; i < CNT ; i++){
			status_register = AD5933_read(AD5933_Status_REG);     // read the status register
			#ifdef LCR_debug  			
				Uart_Printf(USART1, "status register=%02X\r\n",status_register);			
			#endif
			status_register = (status_register & 0x2); // mask off the valid data bit
			if( ((status_register)|0xFD )==  0xFF){  // valid data should be present after start freqy command
					real_byte_high = AD5933_read(0x94);
					real_byte_low  = AD5933_read(0x95);
					imag_byte_high = AD5933_read(0x96);
					imag_byte_low  =  AD5933_read(0x97);
					real_data = ((real_byte_high << 8) |  real_byte_low);
					imag_data = ((imag_byte_high << 8) |  imag_byte_low);
					#ifdef LCR_debug  			 
						Uart_Printf(USART1, "real=%04X   %d\r\n",real_data,real_data);
						Uart_Printf(USART1, "imag=%04X   %d\r\n",imag_data,imag_data);
					#endif
					data[0] = real_data;
					data[1] = imag_data;
			} else{
					return 1;
			}
			AD5933_write(0x80,0x43);
// 			AD5933_write(0x80,0x47); //�ظ�Ƶ��ɨ�� 1000mV��
//			AD5933_write(0x80,0x45); //�ظ�Ƶ��ɨ�� 400mV��
//  			AD5933_write(0x80,0x43); //�ظ�Ƶ��ɨ�� 200mV��
// 			AD5933_write(0x80,0x41); //�ظ�Ƶ��ɨ��  2V��
//	    AD5933_write ( 0x80, AD5933_Fre_Increment);
	}
	return 0;
}
/*****************************************************************************************
	* ��������Set_Test_Parameter
	* ��  �ܣ����������ʼ������
	* ��  ����Start_Fre,frequency_increment,increment_Number
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static void AD5933_Set_Parameter(double   Start_Fre,
												  double   frequency_increment,
												  uint16_t increment_Number,		
												  double   settling_time
												){											
		AD5933_Set_Start_Fre(Start_Fre); // program 30khz start frequency assuming internal osc of 16.776Khz
		AD5933_Set_frequency_increment(frequency_increment);// Transmit to frequency increment register 
		AD5933_Set_frequency_increment_Number(increment_Number);// program 10 frequency increments Transmit to NUMBER OF INCREMENTS register 
		AD5933_Set_settling_time(100); // Transmit to settling time cycles register program 15 output cycles at each frequency before a adc conversion
		#ifdef LCR_debug  	
		{		
			uint8_t i;
			for( i = 0x80;i <= 0x8F;i ++){
					Uart_Printf(USART1, "reg(%02X)=%02X\r\n",i,AD5933_read(i));		
			}
		}				
		#endif											
}											
/*****************************************************************************************
	* ��������AD5933_Calibration
	* ��  �ܣ���ʼ��AD5933
	* ��  ����Calibration_resistor У׼������ֵ
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static double AD5933_Calibration(uint8_t   range ){
		double amplitude =0.0,Gain_ratio=0.0;
		s16 reg_data[2] ={0,0};
		Get_Real_imag_data(reg_data,5);
		amplitude = sqrt(reg_data[0]*reg_data[0] + reg_data[1]*reg_data[1]);
	  Gain_ratio = (pow(10,12)/Impedance_Test.Calibration_resistor[range])/amplitude;
		#ifdef LCR_debug  			
			Uart_Printf(USART1, "real[%d]=%d\r\n",range,reg_data[0]);
			Uart_Printf(USART1, "imag[%d]=%d\r\n",range,reg_data[1]);
			Uart_Printf(USART1, "amplitude[%d]=%0.3f\r\n",range,amplitude);		
			Uart_Printf(USART1, "Gain_ratio[%d]=%0.6f\r\n",range,Gain_ratio);	
		#endif
		return Gain_ratio;
}
/*****************************************************************************************
	* ��������Mini_Capacitor_Test
	* ��  �ܣ�LCR����
						Zx=1/(����ϵ��*����)
						Zc = 1/(2*PI*f*Cx)   Cx=1/(2*PI*f*Zc)
						ZL = 2*PI*f*L ,      Lx=ZL/(2*PI*f)         
					 ��е�λpH,���ݵ�λpF,���赥λ ohm
	* ��  ����range ��λ,
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
double LCR_Test(uint8_t Network_type,uint8_t range,uint8_t Test_Num){
		double Temp =0.0,amplitude,Impedance;
		signed short int dat[2];
		AD5933_Set_Parameter(Impedance_Test.frequency[range],0,10,1000);
		AD5933_write ( 0x80, AD5933_Standby_Mode);// Transmit to CONTROL register // place the AD5933 in standby mode
		AD5933_write ( 0x81, AD5933_Internal_Clock);   // Choose the internal system clock
		AD5933_write ( 0x80, Impedance_Test.Vpp[range]|Impedance_Test.PGA_Gain[range]);   // Choose range 1 (2vp-p, 1.6v) PGA = x1	 
		AD5933_write ( 0x80, AD5933_Init_Start_Fre);// initialise the sensor with contents of start frequency regsister with range 1 (2vp-p, 1.6v) PGA = x1
		AD5933_write ( 0x80, AD5993_Start_Fre_Scan);   // start of frequency sweep  (2vp-p, 1.6v) PGA = x1
		Get_Real_imag_data(dat,2);
		if (Get_Real_imag_data(dat,2)){
			return 999.99;
		}
		amplitude = sqrt(dat[0]*dat[0] + dat[1]*dat[1]);
		Impedance = 1/(Impedance_Test.Gain_Coefficient[range]*amplitude);
		switch(Network_type){
			case __Inductor :  Temp = 1*Impedance/(2*3.141592654*Impedance_Test.frequency[range]); break;
			case __Capacitor:  Temp = 1/(Impedance*2*3.141592654*Impedance_Test.frequency[range]); break;
			case __Resistor :  Temp = Impedance; break;
		}	 	
		#ifdef LCR_debug  			
			Uart_Printf(USART1, "amplitude=%0.3f\r\n",amplitude);			
			Uart_Printf(USART1, "Impedance=%0.3fohm\r\n",Impedance);
			Uart_Printf(USART1, "LCR=%0.3f\r\n",Temp);
		#endif	
		return Temp;
}


/*****************************************************************************************
	* ��������Init_AD5933
	* ��  �ܣ���ʼ��AD5933
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
static uint8_t AD5933_Hardware_Check(void){
		char   ch[10] ,Result = 0,i;
		double T;
		Result |= AD5933_write(0x81,AD5933_Internal_Clock);	
		Result |= AD5933_write(0x80,AD5933_Temperature);
		if(Result){
				lcdreset();
				cyc4or3run();
				lcd_printf("      ��ʾ      ");
				cyc4or3run  ();
				lcd_printf("���ݲ���Ӳ���쳣");
				cyc4or3run();
				lcd_printf("system error 032");
				beep (3,200 );
				while(1);
		}
		for( i = 0; i < 100; i ++){
			ch[1] = AD5933_read(0x92);
			ch[0] = AD5933_read(0x93);
			T = (double)((ch[1]<<8)+ch[0])/32.0;
			if(T > 10.0 && T < 45.0){
				cyc4or3run ();
				lcd_printf("T=%5.2fC      OK",T);
				break ;
			}else{
				if( i == 99){
						lcdreset ();
						cyc4or3run ();
						lcd_printf ("      ��ʾ      ");
						cyc4or3run();
						lcd_printf("���ݲ���Ӳ���쳣");
						cyc4or3run ();
						lcd_printf("system error 033");
						cyc4or3run ();
						lcd_printf("T=%5.2fC      OK",T);
						beep (3,200 );
						while(1);
					}
			}
		}
		return 0;
	
}
/*****************************************************************************************
	* ��������Init_AD5933
	* ��  �ܣ���ʼ��AD5933
	* ��  ������
	* ����ֵ����
	* ��  �ߣ�Morton
	* ��  �ڣ�2018/10/20
*********************************************************************************************/
void AD5933_Initalize(void){
		uint8_t i,j;
		double ratio[12];
		Init_Mini_CAP_Test_GPIO();
		AD5933_Hardware_Check();
		delay_ms (1);
		for( i = 0;i < Range_Num ;i ++ ){ //�õ�������λ������ϵ��
				Relay_Drive (Impedance_Test.RFB_Relay[i]|Impedance_Test.Calibration_Res_Relay[i],SET );
				delay_ms (100);
				AD5933_Set_Parameter(Impedance_Test.frequency[i],0,10,1000);
				AD5933_write ( 0x80, AD5933_Standby_Mode);// Transmit to CONTROL register // place the AD5933 in standby mode
				AD5933_write ( 0x81, AD5933_Internal_Clock);   // Choose the internal system clock
				AD5933_write ( 0x80, Impedance_Test.Vpp[i]|Impedance_Test.PGA_Gain[i]);   // Choose range 1 (2vp-p, 1.6v) PGA = x1	 
				AD5933_write ( 0x80, AD5933_Init_Start_Fre);// initialise the sensor with contents of start frequency regsister with range 1 (2vp-p, 1.6v) PGA = x1
				AD5933_write ( 0x80, AD5993_Start_Fre_Scan);   // start of frequency sweep  (2vp-p, 1.6v) PGA = x1
				for( j =0; j < 10; j ++)
						ratio[j] = AD5933_Calibration(i);
				Impedance_Test.Gain_Coefficient[i] = Average_Fun(ratio,10);
				cyc4or3run();
				lcd_printf ("Ratio%d=%0.1f",i,Impedance_Test.Gain_Coefficient[i]/1000.0);
				Relay_Drive (Impedance_Test.RFB_Relay[i]|Impedance_Test.Calibration_Res_Relay[i],RESET );
				delay_ms (100);
		}
	  //AD5933_write ( 0x80, AD5933_Temp_Measure);
}
