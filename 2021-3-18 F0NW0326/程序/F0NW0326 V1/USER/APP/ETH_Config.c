#include "eth_config.h"
#include "usart.h"
#include "delay.h"
#include "lcd3033.h"
#include "other.h"
#include "menu.h"
#include "24cxx.h"
#include "base_Config.h"
#include <string.h>
typedef enum{
	UDP = 0,
	TCP_Client,
	
	UDP_Server,
	TCP_Server
}NetMode;
char NetModeName[][17]= {
	"UDP",
	"TCP_Client",
	"UDP_Server",
	"TCP_Server"
};
struct ip_addr ipaddr, netmask, gw;

#define ETH_Config_RESET()  GPIO_ResetBits (GPIOF,GPIO_Pin_13)
#define ETH_Config_SET()    GPIO_SetBits (GPIOF,GPIO_Pin_13)



Server_Def  NET_ETH	;


void StringCheck( char *str ){
//	int i = 0,CNT = 0;
//	char buf[256];
//	memset(buf,0,256);
//	for( i = 0; str[i] ; i ++  ){
//		if(str[i] == '\r'|| str[i] == '\n')
//			continue;
//		else {
//			buf[CNT] = str [i];
//			CNT ++;
//		}
//	}
//	memset(str,0,i);
//	strncpy(str,buf,CNT);
}

void Get_ETH_ip_Addr( uint8_t *ip){
	ip[0]= NET_ETH.ipaddr.Num [0];
	ip[1]= NET_ETH.ipaddr.Num [1];
	ip[2]= NET_ETH.ipaddr.Num [2];
	ip[3]= NET_ETH.ipaddr.Num [3];	
}
void IP4_ADDR( struct ip_addr *ipaddr, uint8_t a,uint8_t b,uint8_t c,uint8_t d){
	ipaddr->Num[0] = a;
	ipaddr->Num[1] = b;
	ipaddr->Num[2] = c;
	ipaddr->Num[3] = d;	
}

//#define Debug_Mode

void CheckIPAdddr(char *buf, uint8_t *ip){
	int i = 0,CNT = 0,Flag = 0;
	for( i = 0;i < 4 ; i ++)
		ip[i] = 0;
	for( i= 0 ; buf[i] ; i ++){
		if(buf[i]== '"'){ //检索到第一个”开始读取IP
			Flag = 1;
			continue;
		}
		if(buf[i]== '"' && Flag)//检索到第二个”停止读取IP
			return ;

		if(Flag>0){
			if(buf[i] == '.'){
				CNT ++;
				continue ;
			}
			if(buf[i] >='0' && buf[i] <= '9')
				ip[CNT] = ip[CNT]*10 + (buf[i]-'0');
		}
		
	}
	
}
void displayETHPar( Server_Def *p , uint16_t NMs ){
	cyc4or3run ();
	lcd_printf("%s",NetModeName[p->Mode]);
	cyc4or3run();
	lcd_printf ("%d.%d.%d.%d",p->ipaddr.Num[0] ,p->ipaddr.Num[1] ,p->ipaddr.Num[2] ,p->ipaddr.Num[3]);
		cyc4or3run();
	lcd_printf ("%d.%d.%d.%d",p->netmask .Num[0] ,p->netmask.Num[1] ,p->netmask.Num[2] ,p->netmask.Num[3]);
		cyc4or3run();
	lcd_printf ("%d.%d.%d.%d-%d",p->GATEWAY.Num[0] , p->GATEWAY.Num[1] ,p->GATEWAY.Num[2] ,p->GATEWAY.Num[3],p->PortNumber);	
	delay_ms(NMs );
}

/*********************************************************************************************
	* File Name     :Read_NET_Mode
	* Description   :
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
uint8_t Read_NET_ip_Address (Server_Def *p){
		int i = 0 ,j = 0 ;
		char buf[128];
		uint8_t ch[5]={0,0,0,0,0};
		for( i = 0; i < 10; i ++){
				if(Get_USART_buffer(p->uart, "AT+IP=?\r\n",buf ,500)>0){
				  #if defined Debug_Mode
						StringCheck(buf);
						lcdreset();
						cyc4or3run ();
						lcd_printf("%s",buf);
						step_test_mode_get_key();
					#endif			
					if(strstr(buf,"OK")){
						CheckIPAdddr(buf,ch);
						for( j = 0 ;j < 4 ;j ++)
							p->ipaddr.Num[j]= ch[j];
						return 0;
					}else if(strstr(buf,"ERROR")){
						return 1;
					}
				} 
		}
		return 1;
}
/*********************************************************************************************
	* File Name     :Read_NET_Mode
	* Description   :
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
uint8_t Read_NET_netmask(Server_Def *p){
		int i = 0 ,j = 0;
		char buf[128];
		uint8_t ch[5];
		for( i = 0; i < 10; i ++){
				if(Get_USART_buffer(p->uart, "AT+MASK=?\r\n",buf ,500)>0){
					#if defined Debug_Mode
						StringCheck(buf);
						lcdreset();
						cyc4or3run ();
						lcd_printf("%s",buf);
						step_test_mode_get_key();
					#endif			
					if(strstr(buf,"OK")){
						CheckIPAdddr(buf,ch);
						for( j = 0 ;j < 4 ;j ++)
							p->netmask.Num[j]= ch[j];
						return 0;
					}else if(strstr(buf,"ERROR")){
						return 1;
					}
				} 
		}
		return 1;
}
/*********************************************************************************************
	* File Name     :Read_NET_Mode
	* Description   :
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
uint8_t Read_NET_GATEWAY(Server_Def *p){
		int i = 0,j=0 ;
		char buf[128];
		uint8_t ch[5];
		for( i = 0; i < 10; i ++){
				if(Get_USART_buffer(p->uart, "AT+GATEWAY=?\r\n",buf ,500)>0){
					#if defined Debug_Mode
						StringCheck(buf);
						lcdreset();
						cyc4or3run ();
						lcd_printf("%s",buf);
						step_test_mode_get_key();
					#endif			
					if(strstr(buf,"OK")){
						CheckIPAdddr(buf,ch);
						for( j = 0 ;j < 4 ;j ++)
							p->GATEWAY.Num[j]= ch[j];
						return 0;
					}else if(strstr(buf,"ERROR")){
						return 1;
					}
				} 
		}
		return 1;
}
/*********************************************************************************************
	* File Name     :Read_NET_ip_Address
	* Description   :
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
uint8_t  Read_NET_Mode(Server_Def *p){
		int i = 0 ;
		char buf[128];
		for( i = 0; i < 10; i ++){
				if(Get_USART_buffer(p->uart, "AT+MODE=?\r\n",buf ,500)>0){
					#if defined Debug_Mode
						StringCheck(buf);
						lcdreset();
						cyc4or3run ();
						lcd_printf("%s",buf);
						step_test_mode_get_key();
					#endif			
					if(strstr(buf,"OK")){
						if(strstr (buf ,"Server") && strstr (buf,"TCP")){
							p->Mode = TCP_Server ;
						}else if(strstr (buf ,"Server") && strstr (buf,"UDP")){
							p->Mode = UDP_Server ;
						}else if(strstr (buf ,"Client") && strstr (buf,"TCP")){
							p->Mode = TCP_Client;
						}
						return 0;
					}else if(strstr(buf,"ERROR")){
						return 1;
					}
				} 
		}
		return 1;
}
/*********************************************************************************************
	* File Name     :Net_Connect_Test
	* Description   :初始化以太网接口参数
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
uint8_t Net_Connect_Test(Server_Def *p ){
	uint8_t i=0;
	char buf[128];
	ETH_Config_SET();
	delay_ms (500);
	for( i = 0; i < 10; i ++){
		if(Get_USART_buffer(p->uart,"AT\r",buf ,500)>0){
			if(strstr(buf,"OK")){
				p->Connect_Status = SET ;
				return 0;
			}
		} 
	}
	cyc4or3run ();
	lcd_printf("网口模块NG      ");
	delay_ms(1000);
	return 1;
}
/*********************************************************************************************
	* File Name     :Read_NET_Mode
	* Description   :
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
uint8_t Read_NET_PORT_Number(Server_Def *p){
		int i = 0,j=0 ,Flag = 0;
		char buf[128];
		uint32_t  Port = 0;
		for( i = 0; i < 10; i ++){
				if(Get_USART_buffer(p->uart, "AT+LPORT=?\r\n",buf ,500)>0){
					#if defined Debug_Mode
						StringCheck(buf);
						lcdreset();
						cyc4or3run ();
						lcd_printf("%s",buf);
						step_test_mode_get_key();
					#endif			
					if(strstr(buf,"OK")){
						for( j = 0 ; buf[j]; j ++ ){
							if(buf[j] == '=' && (buf[j+1]>= '0' && buf[j+1] <= '9')){
								Flag = 1;
								continue;
							}
							if(Flag){
								if(buf[j]>= '0' && buf[j] <= '9'){
									Port = Port*10 +  buf[j]-'0';
								}else{
									p->PortNumber = Port ;
									return 0;
								}
							}					
						}		
						return 1;
					}else if(strstr(buf,"ERROR")){
						return 1;
					}
				} 
		}
		return 1;
}
/*********************************************************************************************
	* File Name     : Ip_Set_fun
	* Description   : Item_Name ,ip, Length
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
void Ip_Set_fun( char *Item_Name, uint8_t *ip,uint8_t Length){
		uint8_t Button_Status = 0,cursor_position = 0,t,j = 0,Number = 0;
		char buf[64];
		if(Length > 32)
				Length = 32;
		lcdreset();
		lcdpos (0,0);  lcd_printf( "%s",Item_Name);
	  lcdpos (1,0);  lcd_printf("%3d.%3d.%3d.%3d",ip[0],ip[1],ip[2],ip[3]);
//	  lcdpos (2,0); lcd_printf("L:SET  R:NEXT   ");
		lcdpos (3,0);   lcd_printf("L:+ R:- L+R:MOVE");
		while(1){
				memset(buf ,0,16);
				sprintf(buf,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);			
				t = strlen (buf);// < 16)
				while(t<15 ){
					buf[t] = ' ';
					t ++;
				}				
				lcdpos (1,0); lcd_printf("%s",buf);
			  Button_Status = Getkey_Cursor(buf[cursor_position],cursor_position/16+1,cursor_position%16,ENABLE);
				//无按键操作,模拟光标闪烁
				if(Button_Status == Left_Button_Pressed_Down){ //合法字符从0x20-0x7F
						ip[Number] ++ ; 
				}else if(Button_Status == Right_Button_Pressed_Down){
						ip[Number] --;
				}else if(Button_Status == Double_Button_Pressed_Down ){
						Number ++;
						if(Number >=4 ){
							  startkeywait(1,1);
							  lcdpos (3,0);   lcd_printf("L:修改  R:保存  ");
								Button_Status = Getkey_Cursor(buf[cursor_position],cursor_position/16+1,cursor_position%16,ENABLE);
								if(Button_Status == Left_Button_Pressed_Down){
									cursor_position = 0;
									Number = 0;
									lcdpos (3,0);   lcd_printf("L:+ R:- L+R:MOVE");
									startkeywait(1,1);
								}
								else 
									break;
						}else {
							for(j = cursor_position +1; j < 16 ; j ++ ){
								if(buf[j] == '.')
									break ;
							}
							cursor_position = j +1;
						}
				}
	
		}
		startkeywait(1,1);	
	
}





/*********************************************************************************************
	* File Name     : Read_Parameter_From_ETHModulea
	* Description   : Set ETH   parameter 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
uint8_t Read_Parameter_From_ETHModulea(Server_Def *p ){
	GPIO_InitTypeDef GPIO_InitStructure;	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_ResetBits (GPIOF,GPIO_Pin_13);
	ETH_Config_SET();	
	if(p->uart == USART1)
		uart1_init(p->BaudRate_Set);
	else if (p->uart == USART2)
		uart2_init(p->BaudRate_Set);
	else if (p->uart == USART3)
		uart3_init(p->BaudRate_Set);
	if(Net_Connect_Test(p) == False)
		return 1;
	if(Read_NET_Mode(p) == False)
		return 1;
	if(Read_NET_ip_Address(p) == False)
		return 1;
	if(Read_NET_netmask(p) == False)
		return 1;
	if(Read_NET_GATEWAY(p) == False)
		return 1;
	if(Read_NET_PORT_Number(p) == False)
		return 1;
	ETH_Config_RESET();
	if(p->uart == USART1){
		uart1_init(p->BaudRate_Comm);
	}
	else if (p->uart == USART2)
	{
		uart2_init(p->BaudRate_Comm);
	}
	else if (p->uart == USART3)
	{
		uart3_init(p->BaudRate_Comm);
	}
	return 0;
}
/*********************************************************************************************
	* File Name     : Write_Parameter_To_ETHModulea
	* Description   : Set ETH   parameter 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
uint8_t Write_Parameter_To_ETHModulea(Server_Def *p ){
	char buf[128],rev[128];
	GPIO_InitTypeDef GPIO_InitStructure;	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_ResetBits (GPIOF,GPIO_Pin_13);
	ETH_Config_SET();	delay_ms(500);
	if(p->uart == USART1)
		uart1_init(p->BaudRate_Set);
	else if (p->uart == USART2)
		uart2_init(p->BaudRate_Set);
	else if (p->uart == USART3)
		uart3_init(p->BaudRate_Set);
	if(Net_Connect_Test(p) == False)
		return 1;
	memset(buf,0,128);
	memset(rev,0,128);
	sprintf(buf,"AT+MODE=%d\r\n",p->Mode);
	if(Get_USART_buffer(p->uart, buf ,rev,500)>0){
		if(strstr(rev,"OK")==0){
		//	#if defined Debug_Mode
				StringCheck(buf);
				lcdreset();
				cyc4or3run ();
				lcd_printf("%s",buf);
				step_test_mode_get_key();
		//	#endif	
			return 1;
		}
	}
	memset(buf,0,128);
	memset(rev,0,128);
	sprintf(buf,"AT+IP=\"%d.%d.%d.%d\"\r\n",p->ipaddr.Num[0],p->ipaddr.Num[1],p->ipaddr.Num[2],p->ipaddr.Num[3]);
	if(Get_USART_buffer(p->uart, buf ,rev,500)>0){
		if(strstr(rev,"OK")==0)
			return 1;
	}
	memset(buf,0,128);
	memset(rev,0,128);
	sprintf(buf,"AT+MASK=\"%d.%d.%d.%d\"\r\n",p->netmask.Num[0],p->netmask.Num[1],p->netmask.Num[2],p->netmask.Num[3]);
	if(Get_USART_buffer(p->uart, buf ,rev,500)>0){
		if(strstr(rev,"OK")==0)
			return 1;
	}
	memset(buf,0,128);
	memset(rev,0,128);
	sprintf(buf,"AT+GATEWAY=\"%d.%d.%d.%d\"\r\n",p->GATEWAY.Num[0],p->GATEWAY.Num[1],p->GATEWAY.Num[2],p->GATEWAY.Num[3]);
	if(Get_USART_buffer(p->uart, buf ,rev,500)>0){
		if(strstr(rev,"OK")==0)
			return 1;
	}	
	memset(buf,0,128);
	memset(rev,0,128);
	sprintf(buf,"AT+LPORT=%d\r\n",p->PortNumber);
	if(Get_USART_buffer(p->uart, buf ,rev,500)>0){
		if(strstr(rev,"OK")==0)
			return 1;
	}	
	if(Get_USART_buffer(p->uart, "ATW\r\n" ,rev,500)>0){
		if(strstr(rev,"OK")==0){
				cyc4or3run();
			lcd_printf("网口参数写入NG");
			return 1;
		}
	}	
	cyc4or3run();
	lcd_printf("网口参数写入OK");
	ETH_Config_RESET();
	if(p->uart == USART1){
		uart1_init(p->BaudRate_Comm);
	}
	else if (p->uart == USART2)
	{
		uart2_init(p->BaudRate_Comm);
	}
	else if (p->uart == USART3)
	{
		uart3_init(p->BaudRate_Comm);
	}
	return 0;
}
uint8_t SET_ParmeterYesOrNO(char *Name ){
	lcdreset();
	cyc4or3run ();
	lcd_printf("是否?           ");
	cyc4or3run();
	lcd_printf("%s",Name);
	cyc4or3run();
	lcd_printf("                ");
	cyc4or3run();
	lcd_printf("L:NO  R:YES     ");
	if(Get_start_key_val() == Right_Button_Pressed_Down)
		return  1;
	else
		return  0;
}


/*********************************************************************************************
	* File Name     :InitaServerPar
	* Description   :初始化以太网接口参数
  * Input         :/
  * return        :无
	* Author        :Morton
	* Date          :2018/8/22
*********************************************************************************************/
#include "wtb.h"

void InitaServerPar(void){
	int i = 0;
	NET_ETH.uart = USART1;
	NET_ETH.BaudRate_Set = 9600;
	NET_ETH.BaudRate_Comm = 115200;
	if(Read_Parameter_From_ETHModulea(&NET_ETH ) == False){
		return ;
	}
	if( Read_ETH_Parameter_From_EEPROM( &NET_ETH ) == False ){
		cyc4or3run();
		lcd_printf("..........");
		cyc4or3run();
		lcd_printf("..........");
		cyc4or3run();
		lcd_printf("..........");
		//step_test_mode_get_key();
		NET_ETH.Mode = ETH_default_Config.Mode;
		for( i = 0; i < 4 ; i ++ )
				NET_ETH.ipaddr.Num [i] = ETH_default_Config.ipaddr.Num [i] ;
		for( i = 0; i < 4 ; i ++ )
				NET_ETH.netmask.Num [i] = ETH_default_Config.netmask.Num [i] ;		
		for( i = 0; i < 4 ; i ++ )
				NET_ETH.GATEWAY.Num [i] = ETH_default_Config.GATEWAY.Num [i] ;	
		NET_ETH.PortNumber = ETH_default_Config.PortNumber;
		Write_ETH_Parameter_To_EEPROM( &ETH_default_Config );
		if(Write_Parameter_To_ETHModulea( &ETH_default_Config ) == False ){
			cyc4or3run ();
			lcd_printf("网口参数配置NG  ");
			step_test_mode_get_key();
		}else{
			
				if(Config_ETH_IP(Get_TEST_Station()  )==False){
					cyc4or3run ();
					lcd_printf ("网口模块配置NG");
					step_test_mode_get_key ();
				}
		}
	}
	displayETHPar( &NET_ETH ,1000);
}

uint8_t  Config_ETH_IP(uint8_t Fixture_Num ){
	NET_ETH.ipaddr.Num[3] = ETH_default_Config.ipaddr.Num[3]+Fixture_Num-1; 
	Write_ETH_Parameter_To_EEPROM(&NET_ETH);
	if(Write_Parameter_To_ETHModulea( &NET_ETH )== False){
		cyc4or3run ();
		lcd_printf("网口参数配置NG  ");
		step_test_mode_get_key();
		return 1;
	}
	return 0;
}
/*********************************************************************************************
	* File Name     : ETH_NET_Set
	* Description   : Set ETH   parameter 
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 23-OCT-2019
*********************************************************************************************/
void ETH_NET_Set(void){
	uint8_t i=0;
	
	if(Fixture.Comm_Mode != __ETH){
		lcdreset ();
		lcdpos (2,0); lcd_printf("串口通讯模式");
		step_test_mode_get_key ();
		return ;
	}
	
	displayETHPar(&NET_ETH,1000);
	startkeywait(1,1);
	
	if(SET_ParmeterYesOrNO("恢复默认设置    ")){
		NET_ETH.Mode = ETH_default_Config.Mode;
		for( i = 0; i < 4 ; i ++ )
				NET_ETH.ipaddr.Num [i] = ETH_default_Config.ipaddr.Num [i] ;
		for( i = 0; i < 4 ; i ++ )
				NET_ETH.netmask.Num [i] = ETH_default_Config.netmask.Num [i] ;		
		for( i = 0; i < 4 ; i ++ )
				NET_ETH.GATEWAY.Num [i] = ETH_default_Config.GATEWAY.Num [i] ;	
		NET_ETH.PortNumber = ETH_default_Config.PortNumber;

		
	}else{
			if(SET_ParmeterYesOrNO("设置网络模式    "))
					Choice_Menu("网络模式设置    ",NetModeName,4, (uint8_t *)(&NET_ETH.Mode) );
			if(SET_ParmeterYesOrNO("设置IP          "))
					Ip_Set_fun ("IP设置          ",NET_ETH.ipaddr.Num,15);
			if(SET_ParmeterYesOrNO("设置子网掩码    "))
					Ip_Set_fun ("子网掩码设置    ",NET_ETH.netmask.Num,15);
			if(SET_ParmeterYesOrNO("设置网关        "))	
					Ip_Set_fun ("网关设置        ",NET_ETH.GATEWAY.Num,15);	
			if(SET_ParmeterYesOrNO("设置端口号      "))	
					Choice_Menu_Num("端口号设置      ",0,65535, 1,(uint32_t *)(&NET_ETH.PortNumber ),"" );
	}
	Write_ETH_Parameter_To_EEPROM(&NET_ETH);
	if(Write_Parameter_To_ETHModulea( &NET_ETH )== False){
		cyc4or3run ();
		lcd_printf("网口参数配置NG  ");
	}
	step_test_mode_get_key();
}

