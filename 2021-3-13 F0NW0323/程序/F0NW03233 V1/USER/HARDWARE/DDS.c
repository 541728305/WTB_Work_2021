#include"dds.h"
#include"head.h"

void Initalize_DDS(){	
	Write_data(0x2100);
	Write_data(0x4000);
	Write_data(0x4000);
	Write_data(0x2900);
	Write_data(0x8000);
	Write_data(0x8000);
	Write_data(0xC000);
	Write_data(0xF000);
	Write_data(0x2000);
}

void Write_data( uint16_t  data){
	 uint8_t i;
	 DDS_SPI_Nss =0;
	 delay_us (10);	
	 DDS_SPI_Sck =0;
	 delay_us (10);	
	 for(i=0;i<16;i++){
			if(data&0x8000)
				DDS_SPI_Mosi =1;
			else
				DDS_SPI_Mosi =0;
			delay_us (5);
			DDS_SPI_Sck =0;	
			delay_us (5);
			DDS_SPI_Sck =1;
			data =data <<1;
	}
	delay_us (10);
	DDS_SPI_Nss =1;
}
//Fre=Fre_Hz*2^28/f_MCLK
void Set_DDS_Fre(u32 Fre_Hz){
	u32  DDS_data;
	uint16_t  DDS_Data_H,DDS_Data_L;
	DDS_data= Fre_Hz*26.8435456/4.80;   //268.435456/ 50
	DDS_Data_L=(DDS_data&0x3fff)|0x4000;	
	DDS_Data_H=((DDS_data>>14)&0x3fff)|0x4000;
	Write_data(0x2000);	
	Write_data(DDS_Data_L);	
	Write_data(DDS_Data_H);	
}

double  Cap_Measure(u8 Test_Pin_H,u8 Test_Pin_L,double  Cap_Vaue){
	u32   Fre=0;
	double Cap_Value=0.0,Vol;
	lcdpos (3,0); lcd_printf ("CAP=%3.2lfpF",Cap_Vaue);
	Close_All_Point();//cpld_cs High ,清楚所有模拟开关连接，防止误操作烧坏主板   
	Open_Two_Point ('B',Test_Pin_H,'C',Test_Pin_L);
	if(Cap_Vaue<100.0)                              //<100pF  1MHz
		Fre =1000000;
	if(Cap_Vaue>=100.0&&Cap_Vaue<1000.0)        	  //100pF~1000pF,100KHz
		Fre =100000;
	if(Cap_Vaue>=1000.0&&Cap_Vaue<10000.0)       		 //1nF~10nF
		Fre =10000;
	if(Cap_Vaue>=10000.0&&Cap_Vaue<100000.0)     		 //10nF~100nF
		Fre =1000;
	if(Cap_Vaue>=100000.0&&Cap_Vaue<1000000.0)    		//100nF~1000nF
		Fre =100;
	if(Cap_Vaue>=1000000.0&&Cap_Vaue<10000000.0)  		 //1uF-10uF
		Fre =20;
	Set_DDS_Fre (Fre);
	lcdpos (0,0); lcd_printf ("Fre=%07dHz",Fre );
	//Relay_Drive(Cap_Test_K9 ,SET);
	delay_ms (10);
	Vol=AD7190_AD_To_V (AD7190_CH_AIN3P_AINCOM);
	lcdpos (2,0);  lcd_printf ("V=%2.3lfmV",Vol);
	Cap_Value=Vol*10000.0/(21*3.1415926*(float)Fre)/3;   //Vol/100K=Vref*2*3.14*Fre*Cap  Cap=Vol/100K/Vref*2*3.14*Fre(F)
	return Cap_Value;
}
