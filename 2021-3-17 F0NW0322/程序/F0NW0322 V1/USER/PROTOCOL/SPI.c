#include"head.h"
#include"stm32f10x_spi.h"
#include"spi.h"

void SPI1_Config(void){
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_SPI1 ,ENABLE);
	//PA_4567
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//nss
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);//set nss high
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;  //sck mosi
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;   //miso
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;	  //
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;	//
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_64;
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial=7;
	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_Cmd(SPI1,ENABLE);
}
void SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB???? 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2???? 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15?????? 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15??

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //??SPI???????????:SPI??????????
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//??SPI????:????SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//??SPI?????:SPI????8????
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//??????????:?????
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//???????????
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS?????(NSS??)????(??SSI?)??:??NSS???SSI???
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//??????????:????????16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//???????MSB???LSB???:?????MSB???
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC???????
	SPI_Init(SPI2, &SPI_InitStructure);  //??SPI_InitStruct???????????SPIx???
 
	SPI_Cmd(SPI2, ENABLE); //??SPI??
	SPI2_ReadWriteByte(0xff);//????	 
}  

 uint8_t SPI_SendByte(uint8_t byte){
	uint8_t tmp;		
	SPI_I2S_SendData(SPI1,byte);	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET); 
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET);
	tmp=SPI_I2S_ReceiveData(SPI1);	 	
	return tmp;
}
uint16_t SPI_Trans_Frame(uint8_t cmd,uint16_t data){
	uint16_t tmp;
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);	  
	SPI_SendByte(cmd);  //send cmd
	tmp=SPI_SendByte(data>>8 );
	tmp=(tmp<<8)|SPI_SendByte(data&0xFF);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	return tmp;
}


 
 
void SPI2_SetSpeed(u8 SpeedSet)
{
	SPI2->CR1&=0XFFC7; 
	SPI2->CR1|=SpeedSet;
	SPI_Cmd(SPI2,ENABLE); 
} 

u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //?????SPI???????:????????
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //????SPIx??????
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //?????SPI???????:?????????
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //????SPIx???????					    
}

