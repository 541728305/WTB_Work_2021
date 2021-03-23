#include "ad7190.h"
#include"head.h"
extern u8 lcdcon; 
u8 AD_7190_RUN_STATE=1;
uint8_t buf[3];	
extern uint8_t stdio_as;

/*	������д��AD7190����  */
void SPI_Write(u8 registerAdd, u8 * data,u8 bytesNumber)
{
    u8 byte = 0;
	u8 i;
	if(bytesNumber==3) 	//�����д�Ĵ��� 
	{
		data[bytesNumber] = AD7190_COMM_WRITE | AD7190_COMM_ADDR(registerAdd);//����ͨѶ�Ĵ���
		byte=bytesNumber;
	 	ad7190_cs=0;
		delay_us(AD7190_DELAY_TIME1);
        for(i=0;i<8;i++) //����ͨѶ�Ĵ���
		{
			ad7190_sclk=0;
			if((data[byte] & 0x80) == 0x80)
			{
				ad7190_din=1;//д1
			}
			else
			{
				ad7190_din=0;//д0
			}
			delay_us(AD7190_DELAY_TIME1);
			ad7190_sclk=1;
			delay_us(AD7190_DELAY_TIME1);
			data[byte] <<= 1;	//Rotate data
		}
		delay_us(AD7190_DELAY_TIME1);
		ad7190_cs=1;
		delay_us(AD7190_DELAY_TIME1);
		delay_us(AD7190_DELAY_TIME1);
	}

 	ad7190_cs=0;
	delay_us(AD7190_DELAY_TIME1);
    for(byte=bytesNumber-1 ; byte < bytesNumber; byte--) //���ͼĴ�������
    {
        for(i=0;i<8;i++)
		{
			ad7190_sclk=0;
			if((data[byte] & 0x80) == 0x80)
			{
				ad7190_din=1;//д1
			}
			else
			{
				ad7190_din=0;//д0
			}
			delay_us(AD7190_DELAY_TIME1);
			ad7190_sclk=1;
			delay_us(AD7190_DELAY_TIME1);
			data[byte] <<= 1;	//Rotate data
		}
    }
	delay_us(AD7190_DELAY_TIME1);
	ad7190_cs=1;
}

/** SPI ���ݶ�����****/
void SPI_Read(u8 registerAdd,u8* data,u8 bytesNumber)
{
    u8 byte = 0;
    u8 i;
	long unsigned time=0x05ffff;

	data[bytesNumber] = AD7190_COMM_READ | AD7190_COMM_ADDR(registerAdd);//����ͨѶ�Ĵ���
    SPI_Write(registerAdd, &data[bytesNumber],1);//дͨѶ�Ĵ���

	ad7190_cs=0;
	delay_us(AD7190_DELAY_TIME1);

	if(	registerAdd == AD7190_REG_DATA)	//���Ҫ��ȡ���ݼĴ�������Ҫ�ȵ�AD����
	{
	    while((time>0)&&( ad7190_dout==1));
		if(time==0) 
		{
		   AD_7190_RUN_STATE=1;//�����ʱ������λ�쳣��־
		   return;
		}
	}
	 
	for(byte=bytesNumber-1; byte < bytesNumber ; byte--)
    {
		for(i=0; i<8; i++)
		{
		    ad7190_sclk=0;
			data[byte] <<= 1;		//Rotate data
			delay_us(AD7190_DELAY_TIME1);
			if(ad7190_dout==1) 
			{
				data[byte] |= 1;//��ȡ���״̬	
			}
			ad7190_sclk=1; 						
			delay_us(AD7190_DELAY_TIME1);
		}
    }
	delay_us(AD7190_DELAY_TIME1);
	ad7190_cs=1;     
}



/***************************************************************************//**
 * @����ָ������ת������ֵ.
*******************************************************************************/
unsigned long AD7190_ContinuousReadAvg(u8 sampleNumber)
{
    unsigned long readDatas[11] ,sum=0; 
	u8 mode_register_data[4];
	u8 ch[7];
    u8 min=0, max=0;
	u8 count,i;

	/*
	AD7190_MODE_SEL(AD7190_MODE_SINGLE) | //������ת��ģʽ.
    AD7190_MODE_CLKSRC(AD7190_CLK_EXT_MCLK1_2)| //�ⲿʱ��.�������ӵ� MCLK1 �� MCLK2����.
    AD7190_MODE_RATE(0x015);			  //�˲��� �����������ѡ��
	*/
	mode_register_data[2]=0x28;//������ת��ģʽ.
	mode_register_data[1]=0x00;//�ⲿʱ��.�������ӵ� MCLK1 �� MCLK2����.
	mode_register_data[0]=0x08;//�˲��� �����������ѡ��
	if(sampleNumber>11)
	{
	 	lcdreset();
		lcdpos(0,0);
		lcd_printf("AD�����������  ");
		lcdpos(1,0);
		lcd_printf("�������!     ");
		while(1){		beep(1,200);}
	} 	
		 
    for(count = 0 ; count < sampleNumber ; count++)
    {
		SPI_Write(AD7190_REG_MODE, mode_register_data,3); //дģʽ�Ĵ���
		SPI_Read(AD7190_REG_DATA,ch,3);
		if(AD_7190_RUN_STATE==1) return (0);
		readDatas[count] =ch[2];
		readDatas[count]<<=8;
		readDatas[count]|=ch[1];
		readDatas[count]<<=8;
		readDatas[count]|=ch[0];
	}

    for(count=1;count< sampleNumber;count++)
    {
		     if(readDatas[count]<readDatas[min]) min=count;
		else if(readDatas[count]>readDatas[max]) max=count;
    }
	for(count=0,i=0;count < sampleNumber;count++)
	{
		if((count==min) ||(count==max))continue;
		sum+=readDatas[count];
		i++;
	}	    
    return (sum/i) ;
}

void AD7190_Init(u8 ENdisplay)
{
	u8 ch[7];

	GPIO_AD7190_CFG(); //IO�ڳ�ʼ�� 
	delay_us(5);
    ch[0] = 0xFF;
    ch[1] = 0xFF;
    ch[2] = 0xFF;
    ch[3] = 0xFF;
    ch[4] = 0xFF;
    ch[5] = 0xFF;
    ch[6] = 0xFF;
    SPI_Write(AD7190_REG_RESET, ch, 7); //���ͳ�ʼ������
    delay_us(600);

	ch[0] = 0;
    ch[1] = 0;
	SPI_Read(AD7190_REG_ID,ch,1);//��ID�Ĵ���

	if( (ch[0] & AD7190_ID_MASK) != ID_AD7190) //�쳣����-----�ȴ�
    {
       lcdreset();
	   lcdpos(0,0);
	   lcd_printf("ϵͳAD��ʼ���쳣"); 
	   lcdpos(1,0);
	   lcd_printf("����AD7190��·"); 
	   lcdpos(2,0);
	   lcd_printf("SYS AD-ID:%02XH   ",(u16)(ch[0]));
	   while(1)
	   {
			beep(1,20);
	   }
    }
	ch[6]=ch[0];	
	ch[2] = 0x00;  //b7:ն�� b4 Vref      	
	ch[1] = 0x02;  //ͨ��=1 AIN3+ & AIN4-
	ch[0] = 0x10;  //�л��� ˫���� ����=1
 	SPI_Write(AD7190_REG_CONF, ch,3); //write configuration register,unipolar operation,gain=1,channel:AIN1 to AIN2//buff
	ch[0] = 0;
   ch[1] = 0;
	ch[2] = 0;
	SPI_Read(AD7190_REG_CONF,ch,3);//�����üĴ��� 
	if((ch[2]!=0x00)||(ch[1]!=0x02)||(ch[0]!=0x10))
	{
       lcdreset();
	   lcdpos(0,0);
	   lcd_printf("ϵͳAD���üĴ���"); 
	   lcdpos(1,0);
	   lcd_printf("�����쳣, ����"); 
	   lcdpos(2,0);
	   lcd_printf("AD7190��·.     "); 
	   while(1)
	   {
				beep(1,20);
	   }
	}
	if(ENdisplay) //��ʾID�Ĵ���
	{
		lcdpos(3,0);
		lcd_printf("AD��ʼ��OK  %02XH ", (u16)(ch[6]));
		delay_ms(1500);
    }
 	AD_7190_RUN_STATE=0;			
}

u8 Change_AD7190_Channel(u8 channel){
	u8 ch[4];
	u8 i;
	AD7190_Init(0);
	ch[2] = 0x00;  //b7:ն�� b4 Vref      	
	ch[1] = channel;  //ͨ��=1 AIN3+ & AIN4-
	ch[0] = 0x10;  //�л��� ˫���� ����=1
 	SPI_Write(AD7190_REG_CONF, ch,3); //write configuration register,unipolar operation,gain=1,channel:AIN1 to AIN2//buff
	for(i=0;i<5;i++)
	{ 
 	    if(AD_7190_RUN_STATE==1)   
		{
			AD7190_Init(0);
 	        SPI_Write(AD7190_REG_CONF, ch,3); //write configuration register,unipolar operation,gain=1,channel:AIN1 to AIN2//buff
			continue;
		} 	 	
	}
	return 1;
}

float  AD7190_AD_To_V(u8 sampleNumber)
{
  unsigned long readData ;
	float adv;	
	readData=AD7190_ContinuousReadAvg(sampleNumber);
	if(readData&0x800000)
		adv=(readData-8388608L)*(5000.0/8388608.0);
	else
		adv=0.0;
	return (adv) ;
} 


//double   Voltage_Gain_Test( u8 Gain ){
//		double vol=0.0;
//		Relay_Drive (Voltage_Test_Gain_K14 ,SET);
//		Change_AD7190_Channel(AD7190_CH_AIN1P_AINCOM);
//		while(1){
//				vol = AD7190_AD_To_V(10);
//				cyc4or3run ();
//				lcd_printf ("V_L=%2.3lfmV",vol);
//		}
//		return vol ;
//}
