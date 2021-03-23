#include "hold_data.h"
#include "sys.h"
#include "24cxx.h" 
#include "lcd3033.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include  "reg.h"






/**********************************************************************************
	* File Name     : Get_Take_OFF_Enable_bit
	* Description   : 获取脱料使能位
  * Input         : 无
  * return        :    返回脱料使能位
	* Author        : Morton
	* Date          : 2018/11/18
***********************************************************************************/
uint8_t Get_Take_OFF_Enable_bit(uint8_t Result){ 
	return ACT_Parameter[ACT_Take_Product_EN+Result].data ;
}
/**********************************************************************************
	* File Name     : Get_PASS_Row_Num
	* Description   : 获取摆盘良品列数
  * Input         : 无
  * return        :    摆盘良品列数
	* Author        : Morton
	* Date          : 2018/11/18
***********************************************************************************/
uint8_t Get_PASS_Row_Num(uint8_t Result){
	return ACT_Parameter[ACT_OK_NUM+Result].data ;
}

/**********************************************************************************
	* File Name     : Save_Hold_Reg_data
	* Description   : 保存数据
  * Input         : Num 数据编号
  * return        : 
	* Author        : Morton
	* Date          : 2018/11/18
***********************************************************************************/
void Save_Hold_Reg_data(uint8_t Num ){
		uint32_t dat;
		if(ACT_Parameter[Num].Byte_Length <= 4 ){
			dat = (uint32_t )ACT_Parameter[Num].data ;
			AT24CXX_WriteLenByte(ACT_Parameter[Num].Addr,dat,ACT_Parameter[Num].Byte_Length);	
		}else if(ACT_Parameter[Num].Byte_Length == Double_Type ){
				Write_double_data(ACT_Parameter[Num].Addr,ACT_Parameter[Num].data);
				if(read_double_data(ACT_Parameter[Num].Addr) != ACT_Parameter[Num].data){
					cyc4or3run ();
					lcd_printf ("Write_Error=%d",Num );
					while(1);
				}
		}
}
/**********************************************************************************
	* File Name     : Save_Hold_Reg_data
	* Description   : 从eeprom中读取所有数据
  * Input         : 、
  * return        : 
	* Author        : Morton
	* Date          : 2018/11/18
***********************************************************************************/
void Read_Hold_Reg_data( void){
	uint8_t i;
	for( i = 0 ; ACT_Parameter[i].Name; i ++){
		if(ACT_Parameter[i].Byte_Length <=4 ){
				ACT_Parameter[i].data =  AT24CXX_ReadLenByte(ACT_Parameter[i].Addr,ACT_Parameter[i].Byte_Length);
				if(ACT_Parameter[i].data > ACT_Parameter[i].USL || ACT_Parameter[i].data <ACT_Parameter[i].LSL ){
					ACT_Parameter[i].data = ACT_Parameter[i].default_Value ;
					Save_Hold_Reg_data(i);
				}
		}else if(ACT_Parameter[i].Byte_Length == Double_Type ){
			  ACT_Parameter[i].data = read_double_data(ACT_Parameter[i].Addr) ;
				if(ACT_Parameter[i].data > ACT_Parameter[i].USL || ACT_Parameter[i].data <ACT_Parameter[i].LSL ){
					ACT_Parameter[i].data = ACT_Parameter[i].default_Value ;
					Save_Hold_Reg_data(i);
				}
		}
	}
}



