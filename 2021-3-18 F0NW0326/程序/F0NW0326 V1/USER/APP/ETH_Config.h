#ifndef  __ETH_CONFIG_H_
#define  __ETH_CONFIG_H_ 

#include "sys.h"



/* This is the aligned version of ip_addr_t,
   used as local variable, on the stack, etc. */
struct ip_addr {
  uint8_t  Num[4];
};

typedef  struct {
	
	uint8_t Connect_Status;
	uint8_t Mode;
	struct ip_addr ipaddr;
	struct ip_addr netmask;	
	struct ip_addr GATEWAY;	
	uint32_t PortNumber;
	USART_TypeDef* uart;
	uint32_t BaudRate_Set;
	uint32_t BaudRate_Comm;	
}Server_Def;

extern  Server_Def  ETH_default_Config;
extern  Server_Def  NET_ETH	;;
void Write_ETH_Parameter_To_EEPROM( Server_Def *p);
uint8_t Read_ETH_Parameter_From_EEPROM(Server_Def  *p );

void Get_ETH_ip_Addr( uint8_t *ip);
void InitaServerPar(void);
void  ETH_NET_Set(void);
uint8_t  Config_ETH_IP(uint8_t Fixture_Num );
#endif



