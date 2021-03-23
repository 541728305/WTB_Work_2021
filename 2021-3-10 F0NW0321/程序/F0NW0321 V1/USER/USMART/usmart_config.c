#include "usmart.h"
#include "usmart_str.h" 
#include "delay.h"	
#include "usart.h"		
#include "sys.h"
#include "sup_fun.h"
#include "short.h"
#include "open.h"
#include "zdt.h"
#include "24cxx.h"
#include "test.h"
#include "base_Config.h"
void Mode_Set(uint8_t Mode){
		Fixture.Mode  = Mode;
		if(Fixture.Mode  == 0){
				Uart_printf (USART1 ,"自动模式");
		}
		if(Fixture.Mode  == 1)
			Uart_printf (USART1 ,"单步模式");
}



extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);
extern void * test1(void);
//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//如果使能了读写操作
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif

	(void*)Mode_Set,"void Mode_Set(uint8_t Mode)",
	(void*)Relay_Drive,"void Relay_Drive(uint32_t  Num, u8 Status)",		
	(void*)delay_ms,"void delay_ms(u16 nms)",
	(void*)delay_us,"void delay_us(u32 nus)",	 	

	(uint8_t*)Short_Test_Function,"uint8_t Short_Test_Function(u16 TestStepN)",
//	(uint8_t*)Open_Test_Function_V2,"uint8_t Open_Test_Function_V2(u16 TestStepN)",
	(uint8_t*)Open_Test_Function,"uint8_t Open_Test_Function(u16 TestStepN)",
	(void*)AT24CXX_WriteLenByte,"void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)",
	(u32*)AT24CXX_ReadLenByte,"u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)",
#if defined ZDT_Upper_Commputer
//		(void*) Barcode_Reader_Type_Set,"void Barcode_Reader_Type_Set(void)",
//		(uint8_t*) Software_Trigger_Scan,"uint8_t Software_Trigger_Scan(void)",
#endif


};						  
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//函数数量
	0,	  	//参数数量
	0,	 	//函数ID
	0,		//参数显示类型,0,10进制;1,16进制
	0,		//参数类型.bitx:,0,数字;1,字符串	    
	0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
	0,		//函数的参数,需要PARM_LEN个0初始化
};   



















