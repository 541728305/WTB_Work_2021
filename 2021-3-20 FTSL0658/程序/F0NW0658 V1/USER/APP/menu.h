#ifndef _MENU_H_
#define  _MENU_H_
#include "sys.h"
typedef struct {
	uint8_t   Num ;
	char     *Name;
	uint8_t  (*fun)();
	uint8_t   En_bit;
	uint8_t   password_protect;
}mode_fun_def;



typedef struct {
	char     *Name;
	void    (*fun)();
}Menu_List_Typedef;


extern  mode_fun_def  _Test_Mode[];


void Menu_List_Fun(char *Menu_Name, Menu_List_Typedef *List);
void Read_SMT_information(void);
void Barcode_Format_Set(void);
uint8_t Get_TestMode(void);
uint8_t Password_Input( char *password ,uint8_t Num );
uint8_t  Read_Product_Dir_Check_bit(void);
void Read_System_Name( void );
unsigned char System_Name_Set_Fun(void);
void String_Set_Fun(char *Item_Name , uint16_t Addr, char *str, uint8_t Length );
void Choice_Menu(	char *Name, char (*Menu)[17],uint8_t MAX,uint8_t *Current_Choice);
void Choice_Menu_Num(	char    *Name,uint32_t MIN,uint32_t MAX,uint32_t Step_Length,uint32_t *Current_Value,char *unit);
void Read_SMT_information(void);
#endif


