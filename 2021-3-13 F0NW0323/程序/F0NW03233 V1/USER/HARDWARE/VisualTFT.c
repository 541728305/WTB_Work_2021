#include"tft.h"
#include"head.h"
#define TFT_GLOBALS
u8 GetScreenIDNum;


void TFT_Init(void){	 
	uart3_init(115200);
}

void SendBeginCMD(void){
  USART_SendData(USART3,0xEE);   
}
void SendEndCmd(void){
  USART_SendData(USART3,0xFF);
  USART_SendData(USART3,0xFC);
  USART_SendData(USART3,0xFF);
  USART_SendData(USART3,0xFF);
}

void SetScreen(u16  screen_id){
	SendBeginCMD();
	
	USART_SendData(USART3,0xB1);
	USART_SendData(USART3,0x00);
	USART_SendData(USART3,screen_id>>8);
	USART_SendData(USART3,screen_id&0xff);
	
	SendEndCmd();
}
void SetScreenlay(u8 screen_lay){
	SendBeginCMD();
	USART_SendData(USART3,0xA2);
	USART_SendData(USART3,screen_lay);
	SendEndCmd();
}

void Overlay_Display(u8 Displayscreen_lay){
	SendBeginCMD();
	USART_SendData(USART3,0xA4);
	if(Displayscreen_lay==0)
	{
	 USART_SendData(USART3,0x01);
	 USART_SendData(USART3,0x00);
	}
	else if(Displayscreen_lay==1) 
	{
	 USART_SendData(USART3,0x00);
	 USART_SendData(USART3,0x01);
	}
	SendEndCmd();
}

void write_lay(u8 screen_lay){
	SendBeginCMD();
	USART_SendData(USART3,0xA1);
	USART_SendData(USART3,screen_lay);
	SendEndCmd();
}





