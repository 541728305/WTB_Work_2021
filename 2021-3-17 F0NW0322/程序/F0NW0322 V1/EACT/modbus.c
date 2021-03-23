#include "usart.h"
#include "sup_fun.h"
#include "stdlib.h"
// X40-X4F 表示并行UI输入状态和控制状态的内部继电器
// Y0 -Y1F Y30 冰箱IO发出指示一样
//D0400-D043F 保存步数信息寄存器，在这里写入数据，可变更数据内容
//D9000-D9006 保存运行时的位置速度等信息
//D91009D9110 用于直接执行指定位置速度等信息的动作时使用
#include "sys.h"
#include "usart.h"
#include "crc.h"
#include "modbus.h"
#include <string.h>
#include "delay.h"
#include "lcd3033.h"	
#include "global.h"
//#define debug_mode 

LEC_Run_Parameter *LEC_SET;
LEC_Frame         *Lec_Ptr;

typedef union{
		 struct{
				uint16_t IN   :6;
				uint16_t SETUP:1;
				uint16_t HOLD :1;
				uint16_t DRIVE:1;
				uint16_t RESET:1;
				uint16_t SVON :1;
				uint16_t      :5;		 
		}Y;
		uint16_t OUT;
}EACT_OUT_Typedef;

typedef union{	
		struct{	
				uint16_t OUT   :6;	 
				uint16_t BUSY  :1;
				uint16_t AREA  :1;  
				uint16_t SETON :1;
				uint16_t INP   :1;	 
				uint16_t SVRE  :1;
				uint16_t STOP  :1;
				uint16_t ALARM :1;
				uint16_t       :3;						
		} X;
		uint16_t IN;
}EACT_IN_Typedef;

/**************************************************************************
	* File Name     : Convert_Big
	* Description   : 大小端转换
  * Input         : x 原始数据
  * return        : 转换后数据
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint16_t  Convert_Big(uint16_t x)  {
	return   (x<<8)+(x>>8);
}
/**************************************************************************
	* File Name     : Half_Convert_Big_uint32_t
	* Description   : 大小端转换
  * Input         : x 原始数据
  * return        : 转换后数据
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint32_t  Half_Convert_Big_uint32_t(uint32_t x)  {
	return   (((x&0xFFFF)<<16)|((x&0xFFFF0000)>>16));
}
/*********************************************************************************************
	* File Name     : FReadCoils
	* Description   : 读取线圈状态
  * Input         : Addr
  * return        : 
	* Author        : Morton
	* Date          : 2019/4/11
*********************************************************************************************/
LEC_Status  FReadCoils(uint8_t id,uint16_t Addr ,uint8_t Read_Num,uint8_t *Read_buf){
	uint8_t buf[128],Num = 0,i;
	uint16_t LEC_Crc;
	Lec_Ptr = (LEC_Frame *)buf ;
	Lec_Ptr->ID = id;
	Lec_Ptr->Function_code = ReadCoils_Code;
	Lec_Ptr->Begin_Addr = Convert_Big (Addr);
	Lec_Ptr->Num =Convert_Big(Read_Num);
	LEC_Crc = Modbus_CRC16(buf,6);
	buf[6]= (LEC_Crc&0xFF);buf[7] = (LEC_Crc>>8);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Send(8):");
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,8);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n");
	#endif
	_Uart_printf (LEC_Serial_Port,buf,8);
	memset ((char *)buf ,0 ,128);
	Num = _Get_USART_buffer(LEC_Serial_Port,(char*)buf,READ_WAIT);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Receive(%d):",Num);
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,Num);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
	#endif
	if (Num > 0){
		if(Modbus_CRC16(buf,Num-2) == (buf[Num-2]|(buf[Num-1]<<8))){
			if(Lec_Ptr->ID != id||Lec_Ptr->Function_code != ReadCoils_Code||buf[2] > 16)
					return Frame_Error ;
			for(i = 0; i < buf[2];i ++){
				Read_buf[i] = buf[3+i];
			}
		}
		else{
			return CRC_Error ;
		}
	}else{
		return OverTime ;
	}
	return LEC_Normal ;
}
/*********************************************************************************************
	* File Name     : FWriteSingleCoil
	* Description   : 写数据
  * Input         : Address ；Start_Addr；Length；*Write_data
  * return        : 
	* Author        : Morton
	* Date          : 2019/1/4
*********************************************************************************************/
LEC_Status  FWriteSingleCoil(uint8_t id,uint16_t Addr ,uint8_t Status){
	uint8_t buf[128],Num = 0;
	uint16_t LEC_Crc;
	Lec_Ptr = (LEC_Frame *)buf ;
	Lec_Ptr->ID = id;
	Lec_Ptr->Function_code = WriteSingleCoil_Code;
	Lec_Ptr->Begin_Addr = Convert_Big (Addr);
	Lec_Ptr->Num =(Status==ENABLE ? 0x00FF : 0x0000);
	LEC_Crc = Modbus_CRC16(buf,6);
	buf[6]= (LEC_Crc&0xFF);buf[7] = (LEC_Crc>>8);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Send(8):");
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,8);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n");
	#endif
	_Uart_printf (LEC_Serial_Port,buf,8);
	memset ((char *)buf ,0 ,128);
	Num = _Get_USART_buffer(LEC_Serial_Port,(char*)buf,READ_WAIT);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Receive(%d):",Num);
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,Num);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
	#endif
	if (Num > 0){
		if(Modbus_CRC16(buf,Num-2) == (buf[Num-2]|(buf[Num-1]<<8))){
			if(Lec_Ptr->ID            != id || 
				 Lec_Ptr->Function_code != WriteSingleCoil_Code ||
				 Lec_Ptr->Begin_Addr    != Convert_Big (Addr) ||
				 Lec_Ptr->Num           != (Status==ENABLE ? 0x00FF : 0x0000)){
						#ifdef debug_mode
								Uart_lcd_printf (Debug_Serial_Port,"FWriteSingleCoil Frame data Error\r\n");
								Uart_lcd_printf (Debug_Serial_Port,"id=%02X\r\n",Lec_Ptr->ID);
								Uart_lcd_printf (Debug_Serial_Port,"Function_code=%02X\r\n",Lec_Ptr->Function_code);
								Uart_lcd_printf (Debug_Serial_Port,"Lec_Ptr->Begin_Addr=%04X\r\n",Lec_Ptr->Begin_Addr);
								Uart_lcd_printf (Debug_Serial_Port,"Lec_Ptr->Num=%04X\r\n",Lec_Ptr->Num);
								Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
						#endif
						return Frame_Error ;
				 }
		}
		else{
			#ifdef debug_mode
					Uart_lcd_printf(Debug_Serial_Port,"CRC错误");
					Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
			#endif
			return CRC_Error ;
		}
	}else{
			#ifdef debug_mode
					Uart_lcd_printf(Debug_Serial_Port,"超时");
					Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
			#endif
		return OverTime ;
	}
	return LEC_Normal ;
};
/*********************************************************************************************
	* File Name     : FReadInputStatusReg
	* Description   : 读取线圈状态
  * Input         : Addr
  * return        : 
	* Author        : Morton
	* Date          : 2019/4/11
*********************************************************************************************/
LEC_Status  FReadInputStatusReg(uint8_t id,uint16_t Addr ,uint16_t Read_Num,uint8_t *Read_buf){
	uint8_t buf[128],Num = 0,i;
	uint16_t LEC_Crc;
	Lec_Ptr = (LEC_Frame *)buf ;
	Lec_Ptr->ID = id;
	Lec_Ptr->Function_code = ReadInputReg_Code;
	Lec_Ptr->Begin_Addr = Convert_Big (Addr);
	Lec_Ptr->Num =Convert_Big(Read_Num);
	LEC_Crc = Modbus_CRC16(buf,6);
	buf[6]= (LEC_Crc&0xFF);buf[7] = (LEC_Crc>>8);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Send(8):");
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,8);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n");
	#endif
	_Uart_printf (LEC_Serial_Port,buf,8);
	memset ((char *)buf ,0 ,128);
	Num = _Get_USART_buffer(LEC_Serial_Port,(char*)buf,READ_WAIT);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Receive(%d):",Num);
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,Num);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
	#endif
	if (Num > 0){
		LEC_Crc = Modbus_CRC16(buf,Num-2);
		if( LEC_Crc == (buf[Num-2]|(buf[Num-1]<<8))){
			if(Lec_Ptr->ID != id||Lec_Ptr->Function_code != ReadInputReg_Code||buf[2] > 16)
					return Frame_Error ;
			for(i = 0; i < buf[2];i ++){
				Read_buf[i] = buf[3+i];
			}
		}
		else{
			#ifdef debug_mode
				Uart_lcd_printf (Debug_Serial_Port,"ReadInputStatus CRC error:%02X-%02X\r\n",LEC_Crc&0xFF,(LEC_Crc>>8));
			#endif
			return CRC_Error ;
		}
	}else{
		return OverTime ;
	}
	return LEC_Normal ;
};	
 /*********************************************************************************************
	* File Name     : FReadHoldingReg
	* Description   : 读取线圈状态
  * Input         : Addr
  * return        : 
	* Author        : Morton
	* Date          : 2019/4/11
*********************************************************************************************/
LEC_Status  FReadHoldingReg(uint8_t id,uint16_t Addr ,uint16_t Read_Num,uint16_t *Read_buf){
	uint8_t buf[128],Num = 0,i;
	uint16_t LEC_Crc;
	Lec_Ptr = (LEC_Frame *)buf ;
	Lec_Ptr->ID = id;
	Lec_Ptr->Function_code = ReadHoldingReg_Code;
	Lec_Ptr->Begin_Addr = Convert_Big (Addr);
	Lec_Ptr->Num = Convert_Big(Read_Num); //字数
	LEC_Crc = Modbus_CRC16(buf,6);
	buf[6]= (LEC_Crc&0xFF);buf[7] = (LEC_Crc>>8);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Send(8):");
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,8);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n");
	#endif
	_Uart_printf (LEC_Serial_Port,buf,8);
	memset ((char *)buf ,0 ,128);
	Num = _Get_USART_buffer(LEC_Serial_Port,(char*)buf,READ_WAIT);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Receive(%d):",Num);
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,Num);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
	#endif
	if (Num > 0){
		if(Modbus_CRC16(buf,Num-2) == (buf[Num-2]|(buf[Num-1]<<8))){
			if(Lec_Ptr->ID != id||Lec_Ptr->Function_code != ReadHoldingReg_Code||buf[2] != (Read_Num*2))
					return Frame_Error ;
			for(i = 0; i < Read_Num; i ++ ){
				Read_buf[i] = (buf[3+i*2]<<8)+buf[4+i*2];
			}
		}
		else{
			#ifdef debug_mode
				Uart_lcd_printf (Debug_Serial_Port,"ReadInputStatus CRC error:%02X-%02X\r\n",LEC_Crc&0xFF,(LEC_Crc>>8));
			#endif
			return CRC_Error ;
		}
	}else{
		return OverTime ;
	}
	return LEC_Normal ;
};
/*********************************************************************************************
	* File Name     : WriteData
	* Description   : 写数据
  * Input         : Address ；Start_Addr；Length；*Write_dataWriteData_Code
  * return        : 
	* Author        : Morton
	* Date          : 2019/1/4
*********************************************************************************************/
LEC_Status FWriteHoldingReg(uint8_t id,uint16_t Addr ,uint16_t Length,uint16_t *Write_data){
	uint8_t buf[128],Num = 0,i;
	uint16_t LEC_Crc;
	Lec_Ptr = (LEC_Frame *)buf ;
	Lec_Ptr->ID = id;
	Lec_Ptr->Function_code = WriteHoldingReg_Code;
	Lec_Ptr->Begin_Addr    = Convert_Big(Addr);
	Lec_Ptr->Num           = Convert_Big(Length); //字数
	buf[6] = Length*2 ;
	for( i = 0 ; i < Length; i ++){
		buf[7+i*2]  = (Write_data[i]>>8);
		buf[7+i*2+1] = (Write_data[i]&0xFF);
	}
	LEC_Crc = Modbus_CRC16(buf,7+Length*2);
	buf[7+Length*2]= (LEC_Crc&0xFF);buf[8+Length*2] = (LEC_Crc>>8);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Send(%d):",9+Length*2);
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,9+Length*2);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n");
	#endif
	_Uart_printf (LEC_Serial_Port,buf,9+Length*2);
	memset ((char *)buf ,0 ,128);
	Num = _Get_USART_buffer(LEC_Serial_Port,(char*)buf,READ_WAIT);
	#ifdef debug_mode
			Uart_lcd_printf(Debug_Serial_Port,"Receive(%d):",Num);
			Uart_Prinf_Hex(Debug_Serial_Port,(char *)buf,Num);
			Uart_lcd_printf (Debug_Serial_Port,"\r\n\r\n");
	#endif
	if (Num > 0){
		if(Modbus_CRC16(buf,Num-2) == (buf[Num-2]|(buf[Num-1]<<8))){
			if( Lec_Ptr->ID != id ||
					Lec_Ptr->Function_code != WriteHoldingReg_Code||
					Lec_Ptr->Begin_Addr    != Convert_Big(Addr)||
					Lec_Ptr->Num           != Convert_Big(Length)){
						#ifdef debug_mode
								Uart_lcd_printf (Debug_Serial_Port,"FWriteHoldingReg Frame data Error\r\n");
								Uart_lcd_printf (Debug_Serial_Port,"id=%02X\r\n",Lec_Ptr->ID);
								Uart_lcd_printf (Debug_Serial_Port,"Function_code=%02X\r\n",Lec_Ptr->Function_code);
								Uart_lcd_printf (Debug_Serial_Port,"Lec_Ptr->Begin_Addr=%04X\r\n",Lec_Ptr->Begin_Addr);
								Uart_lcd_printf (Debug_Serial_Port,"Lec_Ptr->Num=%04X\r\n",Lec_Ptr->Num);
						#endif
						return Frame_Error ;
					}
		}
		else{
			#ifdef debug_mode
			Uart_lcd_printf (Debug_Serial_Port,"FWriteHoldingReg CRC error\r\n");
			#endif
			return CRC_Error ;
		}
	}else{
		#ifdef debug_mode
				Uart_lcd_printf (Debug_Serial_Port,"FWriteHoldingReg Overtime\r\n");
		#endif
		return OverTime ;
	}
	return LEC_Normal ;
}
uint8_t Communication_Test(){
	
	return 0;	
}
/**************************************************************************
	* File Name     : Read_InputStatus
	* Description   : 读取X40-X4F输入状态
  * Input         : SIGNALE 检测信号
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t Read_InputStatus( uint8_t id, uint8_t SIGNALE){
		uint8_t buf[10];
		uint16_t Input_REG;
		if(FReadInputStatusReg(id,X40_OUT0,0x10,buf) == RESET){
			Input_REG = ((buf[1]<<8)|buf [0]);
			return ((Input_REG&(1<<((SIGNALE&0x0F)))) ? SET:RESET);
		}else{
			return 99;
		}
}
/**************************************************************************
	* File Name     : Get_LEC_Current_Postion
	* Description   : 获取电缸当前位置
  * Input         : postion 位置
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t Get_LEC_Current_Postion(uint8_t id,  double *postion){
	uint16_t buf[10];
	if(FReadHoldingReg(id,0x9000,0x02,buf)){
		return 1;
	}
	*postion = (double)((buf[0]<<16)|buf[1])/100.0;
	return 0;
}



extern  Act_typedef Y_Axis;
extern  Act_typedef X_Axis;
/**************************************************************************
	* File Name     : Protect_Fun
	* Description   : 光栅保护触发处理函数
  * Input         : Act 电缸内部参数 Type 坐标类型 Coordinate 目标位置 speed 运行速度 Current_pos 当前坐标
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t Protect_Fun(Act_typedef Act, uint16_t Type,uint16_t  speed ){
	uint16_t pbuf[128],pStart_buf[10] = {0x1000};
	uint32_t postion ;
	if(Act.Protect_Mode == HOLD ){
			FWriteSingleCoil(Act.ID,Y18_HOLD,ENABLE);	
			while(Safe_Grating_Sensor == SEN_SET ) delay_ms (100);
			delay_ms (300);
			FWriteSingleCoil(Act.ID,Y18_HOLD,DISABLE);
			return 0;			
	}else if(Act.Protect_Mode == RETURN){			
			if(Act.Previous_Coordinate  < 0){
				 postion = (uint32_t)(Act.Previous_Coordinate*100.0*(-1));
				 postion = (~postion)+1 ;
			}else{
				postion =(uint32_t)(Act.Previous_Coordinate*100.0);
			}
			LEC_SET             = (LEC_Run_Parameter *)pbuf;
			LEC_SET->MOVE_Type  =  Absolute_Coordinate;
			LEC_SET->Speed      =  speed;
			LEC_SET->Positon    =  Half_Convert_Big_uint32_t(postion);
			LEC_SET->ACC        =  5000;
			LEC_SET->EDC        =  5000;
			LEC_SET->Push_Force =  0;
			LEC_SET->Threshold  =  0;
			LEC_SET->Push_Speed =  20;
			LEC_SET->MAX_Force  =  100;
			LEC_SET->AREA_1     =  Half_Convert_Big_uint32_t(0);
			LEC_SET->AREA_2     =  Half_Convert_Big_uint32_t(0);
			LEC_SET->Range      =  Half_Convert_Big_uint32_t(10);
			if (FWriteHoldingReg(Act.ID,0x9102,0x10,pbuf)==LEC_Normal){
					if(FWriteHoldingReg(Act.ID,0x9100,0x01,pStart_buf)==LEC_Normal){
						while(Read_InputStatus(Act.ID,X4B_INP) != SET )
						if(Act.ID == Y_Axis.ID){
								Get_LEC_Current_Postion(Act.ID,&(Y_Axis.Previous_Coordinate));
						}
						return 1;
					}
			}
			FWriteSingleCoil(Act.ID,Y19_SVON,DISABLE);	
			cyc4or3run (); lcd_printf ("电缸动作异常     ");
			while(1) ;
	}
	return 0;
}

/**************************************************************************
	* File Name     : Check_Coordinate
	* Description   : 检查坐标设置是否有误
  * Input         : Act 电缸内部参数 Type 坐标类型 Coordinate 目标位置
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t Check_Coordinate(Act_typedef Act, uint16_t Type, double Coordinate){
	if(Type == Absolute_Coordinate){
		if(abs(Coordinate) > Act.Stroke ){
			cyc4or3run ();
			lcd_printf ("坐标错误:%0.1f",Coordinate);
			while(1);
		}
	}else{
		if(( abs(Act.Previous_Coordinate) + Coordinate) > Act.Stroke||
			 ( abs(Act.Previous_Coordinate  + Coordinate)) < 0.0){
				cyc4or3run ();
				lcd_printf ("坐标错误:%0.1f",Coordinate);
				while(1);
		}
	}
	return 0;
}
/**************************************************************************
	* File Name     : Get_LEC_Current_Postion
	* Description   : 获取电缸当前位置
  * Input         : postion 位置
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t Running_Position(Act_typedef Act, uint16_t Type, double Coordinate ,uint16_t  speed,uint8_t  Pos_Check){
	uint16_t buf[128],Start_buf[10] = {0x1000};
	uint32_t postion ;
	double Current_pos,LSL,USL;	
	#ifdef debug_mode
		if(Type == Absolute_Coordinate ){
			Uart_lcd_printf (Debug_Serial_Port,"运行至绝对坐标=%0.3fmm\r\n",Coordinate);
		}else{
			Uart_lcd_printf (Debug_Serial_Port,"运行至相对坐标=%0.3fmm\r\n",Coordinate);
		}
	#endif
	if(Check_Coordinate(Act,Type,Coordinate)){
		return 1;
	}
	if(Type == Relative_Coordinate )
		Coordinate *= (Act.Orig_Direction);
//	if(Act.Orig_Direction == -1){
//			LSL = -Act.Protect_Range_USL ;
//			USL = -Act.Protect_Range_LSL ;
//	}else{
			LSL = Act.Protect_Range_LSL ;
			USL = Act.Protect_Range_USL ;
//	}
	if(Coordinate < 0){
		 postion = (uint32_t)(Coordinate*100.0*(-1));
		 postion = (~postion)+1 ;
	}else{
		 postion = (uint32_t)(Coordinate*100.0);
	}	
	#ifdef debug_mode
			Uart_lcd_printf (Debug_Serial_Port,"Stroke->%0.3f\r\n",Act.Stroke);
			Uart_lcd_printf (Debug_Serial_Port,"1-LSL->%0.3f\r\n",Act.Protect_Range_LSL);
			Uart_lcd_printf (Debug_Serial_Port,"1-USL->%0.3f\r\n",Act.Protect_Range_USL);
			Uart_lcd_printf (Debug_Serial_Port,"2-LSL->%0.3f\r\n",LSL);
			Uart_lcd_printf (Debug_Serial_Port,"2-USL->%0.3f\r\n",USL);
	#endif
	LEC_SET = (LEC_Run_Parameter *)buf;
	LEC_SET->MOVE_Type  =  Type;
	LEC_SET->Speed      =  speed;
	LEC_SET->Positon    =  Half_Convert_Big_uint32_t(postion);
	LEC_SET->ACC        =  5000;
	LEC_SET->EDC        =  5000;
	LEC_SET->Push_Force =  0;
	LEC_SET->Threshold  =  0;
	LEC_SET->Push_Speed =  20;
	LEC_SET->MAX_Force  =  100;
	LEC_SET->AREA_1     =  Half_Convert_Big_uint32_t(0);
	LEC_SET->AREA_2     =  Half_Convert_Big_uint32_t(0);
	LEC_SET->Range      =  Half_Convert_Big_uint32_t(10);
	if (FWriteHoldingReg(Act.ID,0x9102,0x10,buf)==LEC_Normal ){
		delay_ms (50);
		if(FWriteHoldingReg(Act.ID,0x9100,0x01,Start_buf)==LEC_Normal){
				if(Pos_Check == DISABLE &&MOVE_Check_Sensor == SEN_SET )
					return 0;
			
				while(Read_InputStatus(Act.ID,X4B_INP) != SET ){
					Get_LEC_Current_Postion(Act.ID,&(Current_pos));
				//	lcdpos (lcdcon-1,0);lcd_printf("Y=%8.3fmm  ",Current_pos);
					if(Safe_Grating_Sensor == SEN_SET &&  Current_pos > LSL && Current_pos < USL){
							if(Protect_Fun( Act,  Type, speed)){
								while(Safe_Grating_Sensor == SEN_SET) delay_ms (100);	
								return 1;
							}
					}else if(MOVE_Check_Sensor == SEN_RESET &&Act.ID == 2 ){
							FWriteSingleCoil(Act.ID,Y18_HOLD,ENABLE);	
							cyc4or3run ();
							lcd_printf ("脱料气缸未抬起  ");
							while(MOVE_Check_Sensor == SEN_RESET) delay_ms (100);	
							delay_ms (300);	
						  FWriteSingleCoil(Act.ID,Y18_HOLD,DISABLE);	
					}
				}		
				Get_LEC_Current_Postion(Act.ID,&(Current_pos));
				#ifdef debug_mode
						Uart_lcd_printf (Debug_Serial_Port,"定位结束%0.3f---%0.3f\r\n",Current_pos,Act.Previous_Coordinate);
				#endif
				
				if(Act.ID == Y_Axis.ID){
					Act.Previous_Coordinate = Current_pos;
				}
				if(Act.ID == X_Axis.ID){
					Act.Previous_Coordinate = Current_pos;
				}
				if( abs(Current_pos-Coordinate) > 0.1 && Type == Absolute_Coordinate){
					return 1;
				}
				return 0;
		}
	}
	return 1;
}

/**************************************************************************
	* File Name     : Protect_Fun
	* Description   : 光栅保护触发处理函数
  * Input         : Act 电缸内部参数 Type 坐标类型 Coordinate 目标位置 speed 运行速度 Current_pos 当前坐标
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t XY_Protect_Fun( Act_typedef X_Act, uint16_t X_Type,uint16_t  X_speed,
												Act_typedef Y_Act, uint16_t Y_Type,uint16_t  Y_speed ){
	uint16_t pbuf[128],pStart_buf[10] = {0x1000};
	uint32_t postion ;
	if(X_Act.Protect_Mode == HOLD ){
			FWriteSingleCoil(X_Act.ID,Y18_HOLD,ENABLE);	
			while(Safe_Grating_Sensor == SEN_SET ) delay_ms (100);
			delay_ms (300);
			FWriteSingleCoil(X_Act.ID,Y18_HOLD,DISABLE);
			return 0;			
	}else if(X_Act.Protect_Mode == RETURN){			
			if(X_Act.Previous_Coordinate  < 0){
				 postion = (uint32_t)(X_Act.Previous_Coordinate*100.0*(-1));
				 postion = (~postion)+1 ;
			}else{
				postion =(uint32_t)(X_Act.Previous_Coordinate*100.0);
			}
			LEC_SET             = (LEC_Run_Parameter *)pbuf;
			LEC_SET->MOVE_Type  =  Absolute_Coordinate;
			LEC_SET->Speed      =  X_speed;
			LEC_SET->Positon    =  Half_Convert_Big_uint32_t(postion);
			LEC_SET->ACC        =  5000;
			LEC_SET->EDC        =  5000;
			LEC_SET->Push_Force =  0;
			LEC_SET->Threshold  =  0;
			LEC_SET->Push_Speed =  20;
			LEC_SET->MAX_Force  =  100;
			LEC_SET->AREA_1     =  Half_Convert_Big_uint32_t(0);
			LEC_SET->AREA_2     =  Half_Convert_Big_uint32_t(0);
			LEC_SET->Range      =  Half_Convert_Big_uint32_t(10);
			if (FWriteHoldingReg(X_Act.ID,0x9102,0x10,pbuf)==LEC_Normal){
					if(FWriteHoldingReg(X_Act.ID,0x9100,0x01,pStart_buf)==LEC_Normal){
						while(Read_InputStatus(X_Act.ID,X4B_INP) != SET )
						if(X_Act.ID == Y_Axis.ID){
								Get_LEC_Current_Postion(X_Act.ID,&(Y_Axis.Previous_Coordinate));
						}
						return 1;
					}
			}
			FWriteSingleCoil(X_Act.ID,Y19_SVON,DISABLE);	
			cyc4or3run (); lcd_printf ("电缸动作异常     ");
			while(1) ;
	}
	return 0;
}
/**************************************************************************
	* File Name     : Get_LEC_Current_Postion
	* Description   : 获取电缸当前位置
  * Input         : postion 位置
  * return        : 读取OK 0 反之非0
	* Author        : Morton
	* Date          : 2019/4/26
**************************************************************************/
uint8_t Axis_Running_Position(Act_typedef X_Act, uint16_t X_Type, double X_postion ,uint16_t  X_speed,
															Act_typedef Y_Act, uint16_t Y_Type, double Y_postion ,uint16_t  Y_speed){
	uint16_t buf[128],Start_buf[10] = {0x1000};
	uint32_t x_pos,y_pos ;															
	double X_Current_pos;
	double Y_Current_pos;//,Y_LSL,Y_USL;
	if(Check_Coordinate(X_Act,X_Type,X_postion)||Check_Coordinate(Y_Act,Y_Type,Y_postion)){
		return 1;
	}

	if(X_postion < 0){
		 x_pos = (uint32_t)(X_postion*100.0*(-1));
		 x_pos = (~x_pos)+1 ;
	}else{
		 x_pos = (uint32_t)(X_postion*100.0);
	}																
	//**************** Y ********************															
	if(Y_Type == Relative_Coordinate )
		 Y_postion *= (Y_Act.Orig_Direction);
//	if(Y_Act.Orig_Direction == -1){
//			Y_LSL = -Y_Act.Protect_Range_USL ;
//			Y_USL = -Y_Act.Protect_Range_LSL ;
//	}else{
//			Y_LSL = Y_Act.Protect_Range_LSL ;
//			Y_USL = Y_Act.Protect_Range_USL ;
//	}
	if(Y_postion < 0){
		 y_pos = (uint32_t)(Y_postion*100.0*(-1));
		 y_pos = (~y_pos)+1 ;
	}else{
		 y_pos = (uint32_t)(Y_postion*100.0);
	}																
																															
	LEC_SET = (LEC_Run_Parameter *)buf;
	LEC_SET->MOVE_Type  =  X_Type;
	LEC_SET->Speed      =  X_speed;
	LEC_SET->Positon    =  Half_Convert_Big_uint32_t((uint32_t)(X_postion*100));
	LEC_SET->ACC        =  5000;
	LEC_SET->EDC        =  5000;
	LEC_SET->Push_Force =  0;
	LEC_SET->Threshold  =  0;
	LEC_SET->Push_Speed =  20;
	LEC_SET->MAX_Force  =  100;
	LEC_SET->AREA_1     =  Half_Convert_Big_uint32_t(0);
	LEC_SET->AREA_2     =  Half_Convert_Big_uint32_t(0);
	LEC_SET->Range      =  Half_Convert_Big_uint32_t(10);														
	if (FWriteHoldingReg(X_Act.ID ,0x9102,0x10,buf)==LEC_Normal ){	
		LEC_SET->MOVE_Type  =  Y_Type;
		LEC_SET->Speed      =  Y_speed;
		LEC_SET->Positon    =  Half_Convert_Big_uint32_t((uint32_t)(Y_postion*100));
		if (FWriteHoldingReg(Y_Act.ID,0x9102,0x10,buf)==LEC_Normal ){
				delay_ms (50);
				if(FWriteHoldingReg(X_Act.ID,0x9100,0x01,Start_buf)==LEC_Normal){
					if(FWriteHoldingReg(Y_Act.ID,0x9100,0x01,Start_buf)==LEC_Normal)
						while(Read_InputStatus(X_Act.ID,X4B_INP) != SET && Read_InputStatus(Y_Act.ID,X4B_INP) != SET ){
								Get_LEC_Current_Postion(X_Act.ID,&(X_Current_pos));
							  Get_LEC_Current_Postion(Y_Act.ID,&(Y_Current_pos));
								if(Safe_Grating_Sensor == SEN_SET  ){			
										if(Protect_Fun( Y_Act,  Y_Type, Y_speed)){
											while(Safe_Grating_Sensor == SEN_SET)             delay_ms (100);	
											while(Read_InputStatus(X_Act.ID,X4B_INP) != SET)  delay_ms (100);	
											Get_LEC_Current_Postion(X_Act.ID,&(X_Current_pos));
											Get_LEC_Current_Postion(Y_Act.ID,&(Y_Current_pos));						

											if(X_Act.ID == X_Axis.ID){
												X_Axis.Previous_Coordinate = X_Current_pos;
											}
											if(Y_Act.ID == Y_Axis.ID){
												Y_Axis.Previous_Coordinate = Y_Current_pos;
											}
											return 1;
										}				
								}
						}
						Get_LEC_Current_Postion(X_Act.ID,&(X_Current_pos));
						Get_LEC_Current_Postion(Y_Act.ID,&(Y_Current_pos));						
						#ifdef debug_mode
								Uart_lcd_printf (Debug_Serial_Port,"X 定位结束%0.3f---%0.3f\r\n",X_Current_pos,X_Act.Previous_Coordinate);
								Uart_lcd_printf (Debug_Serial_Port,"Y 定位结束%0.3f---%0.3f\r\n",Y_Current_pos,Y_Act.Previous_Coordinate);
						#endif
						if(X_Act.ID == X_Axis.ID){
							X_Axis.Previous_Coordinate = X_Current_pos;
						}
						if(Y_Act.ID == Y_Axis.ID){
							Y_Axis.Previous_Coordinate = Y_Current_pos;
						}						
						return 0;
				}	
		}
	}
	return 1;
}

