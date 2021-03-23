#include "cmd.h"
#include "wtb.h"
#include "jdt.h"
#include "zdt.h"
#include "reg.h"
#include "menu.h"
#include "other.h"
#include "base_Config.h"



/*****************************************************************
	* File Name     : Cmd_Dealy_Set                      
	* Description   : Cmd_Dealy_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
void Test_Previous_Wait_Time_Set(void ){
	uint32_t Num = 0;
	Num = Reg[Test_Delay].Value ;
	Choice_Menu_Num("测试前延时设置",  Reg[Test_Delay].LSL ,
																		 Reg[Test_Delay].USL,
																		 Reg[Test_Delay].Step_Length ,
																		&Num,"ms");
	Reg[Cmd_Delay].Value = Num ;
	Save_Single_Reg_Value (Test_Delay);
	Fixture.Test_Wait = Reg[Test_Delay].Value;
	RevertStartupScreen();

} 
/*****************************************************************
	* File Name     : Cmd_Dealy_Set                      
	* Description   : Cmd_Dealy_Set                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
void Cmd_Dealy_Set(void ){
	uint32_t Num = 0;
	Num = Reg[Cmd_Delay].Value ;
	Choice_Menu_Num("指令等待时间设置",Reg[Cmd_Delay].LSL ,
																		 Reg[Cmd_Delay].USL,
																		 Reg[Cmd_Delay].Step_Length ,
																		&Num,"ms");
	Reg[Cmd_Delay].Value = Num ;
	Save_Single_Reg_Value (Cmd_Delay);
	Fixture.Cmd_Delay = Reg[Cmd_Delay].Value;
	RevertStartupScreen();

}                                                             
/*****************************************************************
	* File Name     : Software_Cmd_Hander                      
	* Description   : Software_Cmd_Hander                      
  * Input         : buf  Length                              
	* return        : /                                        
	* Version       : V1.0                                     
	* Author        : Morton                                   
	* Date          : 6-April-2020                             
*****************************************************************/ 
void Software_Cmd_Hander(  char  *buf ,uint8_t  *Length){    
	if(Fixture.Software == WTB_Software )
			WTB_Software_Cmd_Check(buf,Length);
	else if(Fixture .Software == ZDT_Software )
			ZDT_Software_Cmd_Check(buf,Length);
			
}

