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
				Uart_printf (USART1 ,"�Զ�ģʽ");
		}
		if(Fixture.Mode  == 1)
			Uart_printf (USART1 ,"����ģʽ");
}



extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);
extern void * test1(void);
//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
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
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	0,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















