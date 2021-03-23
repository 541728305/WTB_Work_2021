#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "at24wc256.h"
#include "lcd3033_serial.h"
#define  ictpic6b95_extern 
#include "ictpic6b595.h"
#include "basefunction.h"

extern u8 testmode;
extern u8 lcdcon;

u8 TPIC6B595DATA[4]={0,0,0,0};  //U63 U64 U65  U66����IC������ݴ洢������

//��ʼ��TPIC6B595�ĸ���ͨѶIO�˿�
void ictpic6b595_io_init()
{
	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	 
	
	GPIOB->CRH&=0XFFFFF0FF;	//PB10���ó���� DEV_CLK_IO 
	GPIOB->CRH|=0X00000300; 				   
	//GPIOB->ODR|=1<<10;	   	    //PB10 ����

	GPIOE->CRH&=0X0FFFFFFF;	//PE15���ó���� DEV_DAT_IO 
	GPIOE->CRH|=0X30000000; 				   
	//GPIOE->ODR|=1<<15;	   	    //PE15 ���� 

	GPIOE->CRL&=0XFFFFFF0F;	//PE1���ó���� U32 CLR 
	GPIOE->CRL|=0X00000030; 				   
	//GPIOE->ODR|=1<<1;	   	    //PE1 ����

	GPIOE->CRL&=0XFFFFFFF0;	//PE0���ó���� U32 ST 
	GPIOE->CRL|=0X00000003; 				   
	//GPIOE->ODR|=1<<0;	   	    //PE0 ����
	
	GPIOB->CRH&=0X0FFFFFFF;	//PB15���ó���� U23 CLR 
	GPIOB->CRH|=0X30000000; 				   
	//GPIOB->ODR|=1<<15;	   	    //PB15 ����

	GPIOD->CRH&=0XFFFFFFF0;	//PD8���ó���� U23 ST 
	GPIOD->CRH|=0X00000003; 				   
	//GPIOD->ODR|=1<<8;	   	    //PD8 ����
	
	GPIOE->CRH&=0XFF0FFFFF;	//PE13���ó���� U26 CLR 
	GPIOE->CRH|=0X00300000; 				   
	//GPIOE->ODR|=1<<13;	   	    //PE13 ����

	GPIOE->CRH&=0XF0FFFFFF;	//PE14���ó���� U26 ST 
	GPIOE->CRH|=0X03000000; 				   
	//GPIOE->ODR|=1<<14;	   	    //PE14 ����

	GPIOE->CRH&=0XFFFF0FFF;	//PE11���ó���� U25 CLR 
	GPIOE->CRH|=0X00003000; 				   
	//GPIOE->ODR|=1<<11;	   	    //PE11 ����

	GPIOE->CRH&=0XFFF0FFFF;	//PE12���ó���� U25 ST 
	GPIOE->CRH|=0X00030000; 				   
	//GPIOE->ODR|=1<<12;	   	    //PE12 ����
}

///TCIP6b595�ײ���������///////
void writeic6b595(u8 IC )
{	
	u8 i;
	u8 write_da=~TPIC6B595DATA[IC]; 
	ic_6b595_clk  = 1 ;
	ic_6b595_sda  = 1 ;
	if( IC == U25 )
	{		
		delay_us(TPIC6B595_DELAY_TIME);
		u25_clr=1;
		delay_us(TPIC6B595_DELAY_TIME);
		u25_clr=0;
	}
	else if(IC==U26)
	{	
		delay_us(TPIC6B595_DELAY_TIME);	
	    u26_clr=1;
		delay_us(TPIC6B595_DELAY_TIME);
		u26_clr=0;
	}
	else if(IC==U22)
	{	
		delay_us(TPIC6B595_DELAY_TIME);
	    u22_clr=1;
		delay_us(TPIC6B595_DELAY_TIME);
		u22_clr=0;
	}
	else if (IC == U23 )
	{ 		
		delay_us(TPIC6B595_DELAY_TIME);
		u23_clr=1;
		delay_us(TPIC6B595_DELAY_TIME);
		u23_clr=0;
	}
	else
	{
		 lcdreset();
		 lcdpos(0,0);
		 printf("TPIC6B595 д�쳣");
		 lcdpos(1,0);
		 printf("IC��:%02u         ",(u16)(IC));
		 while(1) ;
	}  		
	
	for(i=0;i<8;i++)
	{ 		
		if((write_da&0x80 )==0x80)
		ic_6b595_sda = 	1;
		else
		ic_6b595_sda = 	0;
		write_da<<=1;
		delay_us(TPIC6B595_DELAY_TIME+10);
		ic_6b595_clk=0;
		delay_us(TPIC6B595_DELAY_TIME+10);
		ic_6b595_clk=1;
		delay_us(TPIC6B595_DELAY_TIME+10);
	}
	if( IC == U25 )
	{
	  u25_st=0;
		delay_us(110);
		u25_st=1;
	}
	else if( IC == U26)
	{
	  u26_st=0;
		delay_us(110);
		u26_st=1;	
	}
	else if (IC == U22 )
	{
	  u22_st=0;
		delay_us(TPIC6B595_DELAY_TIME<<1);
		u22_st=1;
	}
	else if (IC == U23 )
	{
	  u23_st=0;
		delay_us(TPIC6B595_DELAY_TIME<<1);
		u23_st=1;
	}
}
///TCIP6b595������������///////
void 	deviceinstal(u8 device)
{ 	
	u8 dev;
	u8 i;
	dev=device&0x7f; 	
	for(i=0;(dev==0)&&(i<4);i++)
	{
		TPIC6B595DATA[i]=0;
	    writeic6b595( i ); 
		if(i==3) return;
	}	
    if( dev> 32)
	{
	 	lcdreset();
		lcdpos(0,0);
		printf("TPIC6B595 д����");
		lcdpos(1,0);
		printf("��������Χ, ��");
		lcdpos(2,0);
		printf("������.      ");
		while(1);
	}
	else 
	{
		i=(dev-1)>>3;
		if(device&0x80)	TPIC6B595DATA[i]&=(~(1<<(dev-1-(i<<3))));	
		else   			TPIC6B595DATA[i]|=  (1<<(dev-1-(i<<3))) ;
		writeic6b595( U25+i) ;
	}	
}

//����������������ĺ�����
void beep_time(u16 time)
{
 	deviceinstal(speak_set);
    delay_ms(time);
 	deviceinstal(speak_cls);
}

//������������3��
void ngbeep()
{
 	beep_time(100);
 	delay_ms(100);
 	beep_time(100);
 	delay_ms(100);
 	beep_time(100);
	delay_ms(100);
}



void os_test_io_init()
{
	RCC->APB2ENR|=1<<5;     //ʹ��PORTDʱ��
	RCC->APB2ENR|=1<<8;     //ʹ��PORTGʱ��	 
	///////////////////////////////////////////////////////////////////////////////////////
	
		
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��	
	
	GPIOA->CRL&=0XFF0FFFFF;	  //PA5���ó����   J1802---12  USB_ID  ��ӦUSB�ߵ���ɫ�� 
	GPIOA->CRL|=0X00300000; 				   
	GPIOA->ODR|=1<<5;	   	    //PA5 ����
	
	GPIOA->CRL&=0XF0FFFFFF;	  //PA6���ó�����   USB_ID  ��ӦUSB�ߵĺ�ɫ�� 
	GPIOA->CRL|=0X08000000; 				   
	GPIOA->ODR|=1<<6;	   	    //PA6 ����
	
	
	///////////////////////////////////////////////////////////////////////////////////////
	
	//���������
	GPIOG->CRH&=0XFFFFFF0F;	//PG9���ó����   J1802---14  USB_DP  ��ӦUSB�ߵ���ɫ�� 
	GPIOG->CRH|=0X00000030; 				   
	GPIOG->ODR|=1<<9;	   	    //PG9 ����
	
	GPIOD->CRL&=0XFFFF0FFF;	//PD3���ó����   J1802---15  USB_DM  ��ӦUSB�ߵİ�ɫ��  
	GPIOD->CRL|=0X00003000; 				   
	GPIOD->ODR|=1<<3;	   	    //PD3 ����
	
	GPIOD->CRL&=0XFFF0FFFF;	//PD4���ó����   J1802---40  USB_DP  ��ӦUSB�ߵĺ�ɫ��  
	GPIOD->CRL|=0X00030000; 				   
	GPIOD->ODR|=1<<4;	   	    //PD4 ����
	
	
	//���������		
	GPIOG->CRH&=0XFFFFF0FF;	//PG10���ó�����   USB_DP  ��ӦUSB�ߵĺ�ɫ�� 
	GPIOG->CRH|=0X00000800; 				   
	GPIOG->ODR|=1<<10;	   	    //PG10 ����
	
	GPIOG->CRH&=0XFFFF0FFF;	//PG11���ó�����   USB_DP  ��ӦUSB�ߵİ�ɫ�� 
	GPIOG->CRH|=0X00008000; 				   
	GPIOG->ODR|=1<<11;	   	    //PG11 ����
	
	GPIOG->CRH&=0XFFF0FFFF;	//PG12���ó�����   USB_DP  ��ӦUSB�ߵ���ɫ�� 
	GPIOG->CRH|=0X00080000; 				   
	GPIOG->ODR|=1<<12;	   	    //PG12 ����
	
	GPIOG->CRH&=0XFF0FFFFF;	//PG12���ó�����   USB_DP  ��ӦUSB�ߵĺ�ɫ�� 
	GPIOG->CRH|=0X00800000; 				   
	GPIOG->ODR|=1<<13;	   	    //PG13 ����	
	
}


void io_out_put(u8 output)
{
/*  IO�ڵ�Ӱ���ϵ 
	       J1802_gnd_p7                 λ0
#define  J1802_green_p14  PGout(9)    λ1
#define  J1802_white_p15  PDout(3)    λ2
#define  J1802_red_p40    PDout(4)    λ3
*/	
		output=  (~(1<<output));
	  if(output&1)                      //GND
		  deviceinstal(mic_power_on_cls);		
		else
		  deviceinstal(mic_power_on_set);		
		
		if(output&2)  J1802_green_p14=1;  //GREEN
    else           J1802_green_p14=0;
		
		if(output&4)  J1802_white_p15=1;  //WHITE
    else           J1802_white_p15=0;
		
		if(output&8)  J1802_red_p40=1;    //RED
    else           J1802_red_p40=0;	
		
		if(output&16)  J1802_id_p12=1 ;    //USB_ID
		else           J1802_id_p12=0;	
			
	  delay_ms(30);
}


u8  io_input()
{
	/*
#define  USB_BLACK_gnd    PGin(10)  λ0
#define  USB_GREEN_p14    PGin(12)	λ1
#define  USB_WHITE_p15    PGin(11)	λ2
#define  USB_RED_p40      PGin(13)  λ3

#define  USB_ID_p40      PGin(13)  λ3	
  */		
// 	u8 read_data=0;
	u16  read_data=0;
	if(USB_BLACK_gnd==1)  read_data|=1;
	if(USB_GREEN_p14==1)  read_data|=2;
	if(USB_WHITE_p15==1)  read_data|=4;
	if(USB_RED_p40==1)    read_data|=8;
	////////////////////////////////////////////////
	if(USB_id_p12==1)    read_data|=16;
  return (read_data);	
}

unsigned char os_test(u16 TestStepN)
{
	  u8 i,j;
	  u8 OS_AM=0;
	  u8 con;
	  u8 read_data=0;
	  u8 read_ng=0;
// 	  u8 read_ok=0;
	  u8 line_num=0;
	  deviceinstal(os_test_line_in_set);   //��ͨ�̵���
	  cyc4or3run();
	  printf("%c%cOS����      ",(u8)(TestStepN>>8),(u8)(TestStepN&0xff));	
    delay_ms(200);	
	  for(i=0;i<4;i++)
	  {
			   io_out_put(i);  //��������
		     for(con=0,j=0;j<30;j++)
			    {
					   read_data=io_input();
					   if((read_data) == ((~(1<<i))&0x1f)) {con++; line_num =i+1;} //read_ok=read_data;
					   else {read_ng=read_data;con=0;line_num =i+1;}
					   if(con>=5) break;
             delay_ms(1);					 
		       }
				 if(con<5)
				 {
						 if((read_ng&0x1f)==0x1f)
						 {
								 cyc4or3run();
								 printf("USB line%2d��·NG",(u8)(line_num));
						 }
						 else
						 {
								  cyc4or3run();
								  printf("USB line%2d��·NG",(u8)(line_num));
						 }
						 if(testmode==1)
						    step_test_mode_get_key();
						 else 
						 {
							  deviceinstal(mic_power_on_cls);
							  deviceinstal(os_test_line_in_cls);						 
								return (1);	
						 }							 
						 OS_AM=1;
				 }
				 else
				 {
					   if(testmode==1)
						 {
								 cyc4or3run();
								 printf("USB line%2d����OK",(u8)(line_num));
						     step_test_mode_get_key();
						 }
					 
				 }
		}
		if((testmode==1)&&(OS_AM==0))	//�������ԣ����Ҳ���OK
		{
			 cyc4or3run();
			 printf("    OS����OK    ");
			 step_test_mode_get_key();
		}
		else if((testmode==0) &&(OS_AM==0))  //�������Բ���OK
		{
				lcdpos(lcdcon-1,14);
				printf("OK");				
		}
		deviceinstal(mic_power_on_cls);		
   	deviceinstal(os_test_line_in_cls);			
	  return (OS_AM);
}

void check_usb_line()
{
	  u8 i,j;
	  u8 con;
	  u8 read_data;
	  u8 read_ng=0;
	  lcdpos(2,0);
   	deviceinstal(os_test_line_in_set);			
	  printf("USB ��·�Լ�    ");		
	  for(i=0;i<4;i++)
	  {
			   io_out_put(i);  //��������
		     for(con=0,j=0;j<50;j++)
			   {
					   read_data=io_input();
					   if((read_data) == 0x1f) con++;
					   else {read_ng=read_data;con=0;}
					   if(con>=5) break;
             delay_ms(1);					 
		     }
				 if(con<5)
				 {
						 if((read_ng&0x1f)==0x1f)
						 {
								 lcdpos(2,0);
								 printf("OS�Լ쿪·NG");
						 }
						 else
						 {
								 lcdpos(2,0);
								 printf("OS�Լ��·NG");
						 }
						 if(testmode==1)
						 step_test_mode_get_key();
						 deviceinstal(mic_power_on_cls);	
						 while(1){ngbeep();}
							 
				 }
		}
		deviceinstal(mic_power_on_cls);			
   	deviceinstal(os_test_line_in_cls);			
	
}
// u8 os_test2()
// {
// 	  u8 i,j;
// 	  u8 con;
// 	  u8 read_data;
//     u8 read_ng;
//    	deviceinstal(os_test_line_in_set);			
// 	  for(i=0;i<4;i++)
// 	  {
// 			   io_out_put(i);  //��������
// 		     for(con=0,j=0;j<50;j++)
// 			   {
// 					   read_data=io_input();
// 					   if((read_data) == 0x0f) con++;
// 					       else {read_ng=read_data;con=0;}
// 					   if(con>=5) break;
//              delay_ms(5);					 
// 		     }
// 				 if(con<5)
// 				 {
// 						 cyc4or3run();
// 						 printf("OS��·����NG    ");
// 						 if(testmode==1)
// 						 step_test_mode_get_key();
// 						 deviceinstal(mic_power_on_cls);	
//    	         deviceinstal(os_test_line_in_cls);			
// 						 return(1);							 
// 				 }
// 		}
// 		deviceinstal(mic_power_on_cls);			
//    	deviceinstal(os_test_line_in_cls);			
// 	  return (0);
// }




