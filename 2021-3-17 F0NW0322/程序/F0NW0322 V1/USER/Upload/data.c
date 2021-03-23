#include "data.h"
#include "wtb.h"
#include "zdt.h"
#include "test_config.h"
#include "short.h"
#include "open.h"
#include "lcd3033.h"
#include "os.h"
#include "other.h"
#include <string.h>
#include "reg.h"
#include "usart.h"
#include "barcode.h"
#include "test.h"
#include "base_Config.h"
#include "rf.h"






/**********************************************************************************************************************
	* File Name     :  Get_Test_Item_Num
	* Description   :  上载测试表头
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/18
************************************************************************************************************************/
uint16_t  Get_Short_Num(void){
		uint16_t i,j,SHORT_TEST_NUM =0;
		for ( i = 0 ; ShortGroup[i][0] ; i ++){
				j = 1 ;
				while(ShortGroup[i][j]){
						SHORT_TEST_NUM ++;
						j ++;
				}
		}
		return SHORT_TEST_NUM;
}

/**********************************************************************************************************************
	* File Name     :  Get_Test_Item_Num
	* Description   :  上载测试表头
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/18
************************************************************************************************************************/
uint16_t Get_Open_Num(void){
		uint16_t i,j,OPEN_TEST_NUM = 0;
		for ( i = 0 ; OpenGroup[i][0] ; i ++){
				j = i+1 ;
				while(OpenGroup[j][0]){
						OPEN_TEST_NUM ++;
						j ++;
				}
		}
		return OPEN_TEST_NUM;
}
/*********************************************************************************************
	* File Name     : Read_Toatl_Item_Num
	* Description   : Read_Toatl_Item_Num
  * Input         : /
	* return        : /
	* Version       : V1.0
	* Author        : Morton
	* Date          : 12-OCT-2019
*********************************************************************************************/
uint16_t Get_Component_Num(void){
	uint16_t i = 0,	Total_Num = 0;;

	for( i =0 ; Item[i].Name ; i ++){
		Total_Num ++;
	}
	return Total_Num;
}
 /**********************************************************************************************************************
	* File Name     :  Init_Test_data
	* Description   :  初始化测试数据
  * Input         :  、
  * return        :  、
	* Author        :  Morton
	* Date          :  2019/3/18
**********************************************************************************************************************/
uint16_t Init_Test_data(void){

	uint16_t i=0,op_data_Num = 0,Total_Test_Item_Num = 0;
  uint16_t Short_Num = Get_Short_Num();
  uint16_t Open_Num  = Get_Open_Num();
	uint16_t Component_Num  = Get_Component_Num();
	if(TestConfig.Short == ENABLE  ){
		for( i = 0; i < Short_Num ;i ++){
				SHORT_RES.Status[i] = 99;
				SHORT_RES.Value[i] = 999.9;
				Total_Test_Item_Num ++;		
		}
		//Uart_printf ( USART1,"Short CNT: :%d->%d   ",  Total_Test_Item_Num,SHORT_TEST_NUM);
	}
	if(TestConfig.OPEN  == ENABLE && Open_Num > 0 ){
		for( i = 0 ; i < Open_Num; i ++){
				Open_Data._Status [i] = 99;
				Open_Data.Value [i] = 0.0;
		}
		Open_Data.Status = 99;
		memset (Open_Data.RESULT ,0,50) ;
		if(TestConfig.OpenList == ENABLE ){
			Total_Test_Item_Num += Open_Num;
		}else {
			Total_Test_Item_Num += 1;
		}
//		Uart_printf ( USART1,"Open CNT:%d->%d   ",  Total_Test_Item_Num,OPEN_TEST_NUM);
	}	
	if(TestConfig.Component  == ENABLE  && Component_Num > 0){
		for( i = 0; Item[i].Name ; i ++){
			Item_Data[i].Status = 99;
			if(Item[i].Type == OS_Open )
					op_data_Num ++;
			Total_Test_Item_Num ++;
		}
		if( op_data_Num > 0){
			if(TestConfig.OpenList == DISABLE)				
					Total_Test_Item_Num = Total_Test_Item_Num - op_data_Num + 1;
		}
//		Uart_printf ( USART1,"Component CNT:%d->%d   ",  Total_Test_Item_Num,Total_Component_Num);
	}	
	if(TestConfig.RF  == ENABLE ){
				memset(RF_Total_Result,True ,4);
	}
return Total_Test_Item_Num;
}

/************************************************************************************************
	* File Name     :  Upload_Test_Item
	* Description   :  上载测试表头
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/18
*************************************************************************************************/
uint8_t  Find_Insulation_Reuslt( uint8_t Group_Num, char *buf){
	uint16_t i = 0;
	for( i = 0; Item[i].Name ; i ++){
		if( Item[i].Group != Group_Num )
			continue ;
		if(Item_Data[i].Status == False  && Item[i].Type == OS_Open ){
			sprintf (buf,"%s:%0.7f",Item[i].Name,Item_Data[i].Value);
			return False;
		}
	}
	sprintf (buf,"OK");
	return True;
}
/************************************************************************************************
	* File Name     :  Upload_Test_Item
	* Description   :  上载测试表头
  * Input         :  无
  * return        :  无
	* Author        :  Morton
	* Date          :  2019/3/18
*************************************************************************************************/
void WTB_Software_Upload_Test_Item(void){
		uint16_t  i,j,Insulation_Flag = RESET,Total_Test_Item_Num = 0;
		uint8_t   TEST_Station = Reg[FixtureNumber].Value ;
		Total_Test_Item_Num = Init_Test_data();
		Uart_printf (Fixture.Comm_Uart  ,"SL_ITE_%d_Itemname#%d",TEST_Station,Total_Test_Item_Num/Fixture.PCS_Num);	
		if(TestConfig.Short  == ENABLE  ){
				for ( i = 0 ; ShortGroup[i][0]; i ++){
						j = 1 ;
						while(ShortGroup[i][j]){
								Uart_printf( Fixture.Comm_Uart,"#%s-%s;%g;0;ohm;O/S",Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]],Max_ConductionImpedance );     
								j ++;
						}
				}
	  }
		if(TestConfig.OPEN  == ENABLE  ){
				if(TestConfig.OpenList == DISABLE ){
						Uart_printf (Fixture.Comm_Uart ,"#OPEN;TBD;%g;Mohm;O/S",Min_InsulationResistance );
				}else {					
						for ( i = 0 ; OpenGroup[i][0]; i ++){
								j = i+1 ;
								while(OpenGroup[j][0]){
										Uart_printf( Fixture.Comm_Uart,"#%s-%s;99;%g;Mohm;O/S",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[j][0]],Min_InsulationResistance ); 																														
										j ++;
								}
						}								
				}
		}
		if(TestConfig.Component  == ENABLE ){
			for( i = 0; Item[i].Name ; i ++){	
					if(Item[i].Group == 1){
						if(TestConfig.OpenList == DISABLE  && Item[i].Type == OS_Open    ){
							if(Insulation_Flag == RESET&& TestConfig.OPEN  == DISABLE ){
								Uart_printf( Fixture.Comm_Uart,"#Open;TBD;2;Mohm;O/S"); 
								Insulation_Flag = SET ;
							}
						}else {
								Uart_printf( Fixture.Comm_Uart,"#%s;%g;%g;%s;%s",Item[i].Name,Item[i].USL ,Item[i].LSL,Item[i].Unit,Item[i].Class ); 
						}
					}
			}
		}		
		if(TestConfig.FCT  == ENABLE ){
			
		}
		Uart_printf (Fixture.Comm_Uart ,"\r\n");	
}
/*******************************************************************************************************
	* File Name     :  Upload_Test_data
	* Description   :  上传测试数据，就接收上位机保存数据情况
  * Input         :  Result
  * return        :  收到指令返回0，反之返回1
	* Author        :  Morton
	* Date          :  2019/3/18
********************************************************************************************************/
uint8_t WTB_Software_Upload_Data(uint8_t Test_Result){
	  char buf[64];
 
    uint8_t TEST_Station = Reg[FixtureNumber].Value ;
		uint16_t i=0,j = 0,Upload_data_Result = True ;
		uint16_t Insulation_Flag = RESET ;

		Uart_printf(Fixture.Comm_Uart,"SL_DAT_@%d",TEST_Station);
		//*******上传短路阻值*****************
		if(TestConfig.Short  == ENABLE  ){
			for(i = 0;i < Get_Short_Num ();i ++){
				if(SHORT_RES.Status[i] <=1)
						Uart_printf(Fixture.Comm_Uart,"#%d*%0.4f",SHORT_RES.Status[i],SHORT_RES.Value[i]);
				else
						Uart_printf(Fixture.Comm_Uart,"#1*");
			}	
		}
		//*******上传绝缘测试结果*******************************************
	
		if(TestConfig.OPEN  == ENABLE ){
			if(TestConfig.OpenList == DISABLE ){
					if(Open_Data.Status == True &&  Get_Currennt_Type_CNT(Type_OS_Open,Step_buffer,Max_Step_Nummber) > 0 && TestConfig.Component ==ENABLE){
						
					}
					else{
							if(Open_Data.Status <= 1)
								Uart_printf(Fixture.Comm_Uart,"#%d*%s",Open_Data.Status ,Open_Data.RESULT );	
							else
								Uart_printf(Fixture.Comm_Uart,"#1*");
				  }
			}else {
					for(i = 0;i <  Get_Open_Num ();i ++){
						if(Open_Data._Status[i] <= 1 )						
								Uart_printf(Fixture.Comm_Uart,"#%d*%0.4f",Open_Data._Status[i],Open_Data.Value[i]);
						else
								Uart_printf(Fixture.Comm_Uart,"#1*");
					}			
			}
		}
		if(TestConfig.Component  == ENABLE ){
			  for( j = 0 ; j < Fixture.PCS_Num ; j ++){
					Insulation_Flag = RESET;
					for( i = 0; Item[i].Name ; i ++){
						if(Item[i].Group == j+1){
								if(Item[i].Type == OS_Open && TestConfig.OpenList == DISABLE ){
										if( Insulation_Flag == RESET ){	
											memset (buf,0,64);
											Uart_printf(Fixture.Comm_Uart,"#%d*%s",Find_Insulation_Reuslt(j+1, buf),buf );
											Insulation_Flag = SET ;
										}								
								}else{				
									if(Item_Data[i].Status <=1 )
											Uart_printf(Fixture.Comm_Uart,"#%d*%0.4f",Item_Data[i].Status,Item_Data[i].Value );
									else
											Uart_printf(Fixture.Comm_Uart,"#1*");
								}
						}
					}
			 }
		}	
	if(Test_Result == True){
			Uart_printf(Fixture.Comm_Uart,"#PASS\r\n");
	}else{
			Uart_printf(Fixture.Comm_Uart,"#FAIL\r\n");
	}	
	if(Fixture.Mode  == Step_Test_Mode||Scan.Mode == Stand_Alone_mode )
			return True;
	if(TestConfig.RF == ENABLE )
			return True;
	
	
	if(Fixture.Mech_Struct == SmallFixture )	//*****PCS 治具需检验上位机保存数据结果，一体机直接跳过******************
	{
		Upload_data_Result |= WTB_Software_Get_Save_Result(Test_Result);

	}else{
		Upload_data_Result = True ;
	}
	Soft_Start_Test = RESET ;
	return Upload_data_Result;
}


/**********************************************************************************************************************
 	* File Name     :  ZDT_Software_Upload_Test_Item
 	* Description   :  串口上传测试表头,
  * Input         :  无
  * return        :  无
 	* Author        :  Morton
 	* Date          :  2016.12.5
************************************************************************************************************************/
void ZDT_Software_Upload_Test_Item(void ){
		uint16_t  i,j;
		Uart_printf( Fixture.Comm_Uart,"*" ); 
		if(TestConfig.Short == ENABLE  ){
				for ( i = 0 ; ShortGroup[i][0]; i ++){
						j = 1 ;
						while(ShortGroup[i][j]){
								Uart_printf( Fixture.Comm_Uart,"%s-%s(ohm)=%g_0#",Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]],Max_ConductionImpedance );     
								j ++;
						}
				}
	  }
		if(TestConfig.OPEN  == ENABLE  ){
			if(TestConfig.OpenList == DISABLE ){
					if(TestConfig.OPEN  == ENABLE )
							Uart_printf( Fixture.Comm_Uart,"open(Mohm)=99_%g#",Min_InsulationResistance  ); 
					else
							Uart_printf( Fixture.Comm_Uart,"open(Mohm)=99_%g&",Min_InsulationResistance ); 
			}else {
					for ( i = 0 ; OpenGroup[i][0]; i ++){
							j = i+1 ;
							while(OpenGroup[j][0]){
									if((TestConfig.OPEN == DISABLE || Get_Component_Num() == 0)&& (OpenGroup[i+2][0] == NULL && OpenGroup[j+1][0] == NULL)) 
												Uart_printf( Fixture.Comm_Uart,"%s-%s(Mohm)=99_%g&",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[j][0]],Min_InsulationResistance ); 										
									else 	
											Uart_printf( Fixture.Comm_Uart,"%s-%s(Mohm)=99_%g#",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[j][0]],Min_InsulationResistance ); 																					
									j ++;
							}
					}
				}					
	  }
		if(TestConfig.Component  == ENABLE ){
				for( i = 0; Item[i].Name ; i ++){
					if(Item[i+1].Name || TestConfig.FCT  == ENABLE)
						Uart_printf( Fixture.Comm_Uart,"%s(%s)=%g_%g#",Item[i].Name,Item[i].Unit,Item[i].USL ,Item[i].LSL ); 
					else
						Uart_printf( Fixture.Comm_Uart,"%s(%s)=%g_%g&",Item[i].Name,Item[i].Unit,Item[i].USL ,Item[i].LSL );
				}
		}
		
		
		if(TestConfig.FCT  == ENABLE ){
	
		}
		Uart_printf( Fixture.Comm_Uart,"\r\n");
}


/**********************************************************************************************************************
 	* File Name     :  Upload_Detail_Test_Data
 	* Description   :  串口上传测试数据，并接收上位机数据保存结果指令
  * Input         :  Result，整体测试结果，PASS为真  FAIL 
  * return        :  Host_Save_Result,上位机保存OK返回0，反之非0
 	* Author        :  Morton
 	* Date          :  2016.12.5
************************************************************************************************************************/
uint8_t  ZDT_Software_Upload_Data(u8 Result){

		uint16_t Host_Save_Result = False ,i;		
		if( Get_Scan_Mode() == Stand_Alone_mode )
				return True ;	
		Uart_printf(Fixture.Comm_Uart,"*");
		//*******上传短路阻值*****************
		if(TestConfig.Short  == ENABLE  ){
			for(i = 0;i < Get_Short_Num ();i ++){
				if(SHORT_RES.Status[i] == True )
						Uart_printf(Fixture.Comm_Uart,"%0.4f#",SHORT_RES.Value[i]);
				else if(SHORT_RES.Status[i] == False )
						Uart_printf(Fixture.Comm_Uart,"%0.4f@#",SHORT_RES.Value[i]);
				else
						Uart_printf(Fixture.Comm_Uart," #");
			}	
		}
		//*******上传绝缘测试结果*******************************************
	
		if(TestConfig.OPEN  == ENABLE ){
			if(TestConfig.OpenList == DISABLE ){
					if(Open_Data.Status <= 1)
							Uart_printf(Fixture.Comm_Uart,"%s#",Open_Data.RESULT );	
					else
						Uart_printf(Fixture.Comm_Uart," #");
			}else {
					for(i = 0;i < Get_Open_Num ();i ++){
						if(Open_Data._Status[i] == True )
								Uart_printf(Fixture.Comm_Uart,"%0.4f#",Open_Data.Value[i]);
						else if(Open_Data._Status[i] == False )
								Uart_printf(Fixture.Comm_Uart,"%0.4f@#",Open_Data.Value[i]);
						else
								Uart_printf(Fixture.Comm_Uart," #");
					}	
				
			}
		}
		if(TestConfig.Component  == ENABLE ){
				for( i = 0; Item[i].Name ; i ++){
					if(Item_Data[i].Status == True )
							Uart_printf(Fixture.Comm_Uart,"%0.4f#",Item_Data[i].Value);
					else if(Item_Data[i].Status == False )
							Uart_printf(Fixture.Comm_Uart,"%0.4f@#",Item_Data[i].Value);
					else
							Uart_printf(Fixture.Comm_Uart," #");
				}
		}
		if( Result == True)
				Uart_printf(Fixture.Comm_Uart, "F-OK$\r\n");
		else
				Uart_printf(Fixture.Comm_Uart, "F-NG$\r\n");
		if(Fixture.Mode  == Step_Test_Mode ){
				return True ;
		}
		
		if(Fixture.Mode  == Step_Test_Mode||Scan.Mode == Stand_Alone_mode )
			return True ;
		
		Host_Save_Result |= ZDT_Software_Get_Save_Result();	
		Set_Scan_Result(False);
		return Host_Save_Result;
}



/*********************************************************************************************
	* File Name     : UploadShortGroup
	* Description   : UploadShortGroup
  * Input         : /
	* return        : Volts (Uint :V)
	* Version       : V1.0
	* Author        : Morton
	* Date          : 18-April-2020
*********************************************************************************************/
uint8_t  UploadShortGroup(char *buf){
	uint16_t i = 0,j = 0;
	Uart_printf (Fixture.Comm_Uart,"\r\n短路群如下:\r\n");
	for( i = 0 ; ShortGroup[i][0]; i ++){
		Uart_printf (Fixture.Comm_Uart,"Group%2d:  ", i+1);
		j = 0;
		while (ShortGroup[i][j])  //判断当前点位是否已被 mark，若被mark是重复编辑点
		{  
			Uart_printf (Fixture.Comm_Uart,"%3d, ", ShortGroup[i][j]);
			j ++;
		}
		Uart_printf (Fixture.Comm_Uart,"\r\n");
	}
	return True ;
}



uint8_t  Upload_Test_Data(char *buf){
	uint16_t  i,j,Number = 0,CNT = 0;
	char str[64],Space[32];
	Uart_printf (Fixture.Comm_Uart,"NO.*****Test_Item****************USL*****LSL******Value*****Unit****Result\r\n");
		//*******上传短路阻值*****************
		if(TestConfig.Short  == ENABLE  ){
				for ( i = 0 ; ShortGroup[i][0]; i ++){
						j = 1 ;
						while(ShortGroup[i][j]){
						Number ++;
						Uart_printf( Fixture.Comm_Uart,"%3d     ",Number);
						// Item Name
						memset (str,0,64);
						memset (Space,0,64);
						sprintf (str,"%s-%s",Pin_Name[ShortGroup[i][0]],Pin_Name[ShortGroup[i][j]] );
						memset (Space,' ',25-strlen (str));
						strcat(str,Space);
						Uart_printf( Fixture.Comm_Uart,"%s",str);
						// USL
						memset (str,0,64);
						memset (Space,0,64);
						sprintf (str,"%g",Max_ConductionImpedance );
						memset (Space,' ',8-strlen (str));
						strcat(str,Space);
						Uart_printf( Fixture.Comm_Uart,"%s",str);							
						// LSL
						memset (str,0,64);
						memset (Space,0,64);
						sprintf (str,"%g",0.0 );
						memset (Space,' ',8-strlen (str));
						strcat(str,Space);
						Uart_printf( Fixture.Comm_Uart,"%s",str);							
						// ValueSHORT_RES.Status[i],
						memset (str,0,64);
						memset (Space,0,64);
						sprintf (str,"%0.4f",SHORT_RES.Value[CNT]);
						memset (Space,' ',12-strlen (str));
						strcat(str,Space);
						Uart_printf( Fixture.Comm_Uart,"%s",str);	
						// Unit
						memset (str,0,64);
						memset (Space,0,64);
						sprintf (str,"ohm");
						memset (Space,' ',8-strlen (str));
						strcat(str,Space);
						Uart_printf( Fixture.Comm_Uart,"%s",str);				
						// Result
						memset (str,0,64);
						Uart_printf( Fixture.Comm_Uart,"%s",SHORT_RES.Status[CNT] == True ?"PASS":"FAIL");		
						Uart_printf( Fixture.Comm_Uart,"\r\n");			
						j ++; CNT ++;
					}
				}
				
		}
		//*******上传绝缘测试结果*******************************************
	
		if(TestConfig.OPEN  == ENABLE ){
			CNT = 0;
			if(TestConfig.OpenList == DISABLE ){
				Number ++;
				Uart_printf( Fixture.Comm_Uart,"%3d     ",Number);
				// Item Name
				memset (str,0,64);
				memset (Space,0,64);
				sprintf (str,"OPEN");
				memset (Space,' ',25-strlen (str));
				strcat(str,Space);
				Uart_printf( Fixture.Comm_Uart,"%s",str);
				// USL
				memset (str,0,64);
				memset (Space,0,64);
				sprintf (str,"TBD");
				memset (Space,' ',8-strlen (str));
				strcat(str,Space);
				Uart_printf( Fixture.Comm_Uart,"%s",str);							
				// LSL
				memset (str,0,64);
				memset (Space,0,64);
				sprintf (str,"%g",Min_InsulationResistance  );
				memset (Space,' ',8-strlen (str));
				strcat(str,Space);
				Uart_printf( Fixture.Comm_Uart,"%s",str);							
				// ValueSHORT_RES.Status[i],
				memset (str,0,64);
				memset (Space,0,64); //Open_Data.Status ,Open_Data.RESULT
				sprintf (str,"%s",Open_Data.RESULT);
				memset (Space,' ',12-strlen (str));
				strcat(str,Space);
				Uart_printf( Fixture.Comm_Uart,"%s",str);	
				// Unit
				memset (str,0,64);
				memset (Space,0,64);
				sprintf (str,"Mohm");
				memset (Space,' ',8-strlen (str));
				strcat(str,Space);
				Uart_printf( Fixture.Comm_Uart,"%s",str);				
				// Result
				memset (str,0,64);
				Uart_printf( Fixture.Comm_Uart,"%s",Open_Data.Status == True ?"PASS":"FAIL");		
				Uart_printf( Fixture.Comm_Uart,"\r\n");	
				
			}else {
						for ( i = 0 ; OpenGroup[i][0]; i ++){
								j = i+1 ;
								while(OpenGroup[j][0]){	
									Number ++;
									Uart_printf( Fixture.Comm_Uart,"%3d     ",Number);
									// Item Name
									memset (str,0,64);
									memset (Space,0,64);
									sprintf (str,"%s-%s",Pin_Name[OpenGroup[i][0]],Pin_Name[OpenGroup[j][0]]);
									memset (Space,' ',25-strlen (str));
									strcat(str,Space);
									Uart_printf( Fixture.Comm_Uart,"%s",str);
									// USL
									memset (str,0,64);
									memset (Space,0,64);
									sprintf (str,"TBD");
									memset (Space,' ',8-strlen (str));
									strcat(str,Space);
									Uart_printf( Fixture.Comm_Uart,"%s",str);							
									// LSL
									memset (str,0,64);
									memset (Space,0,64);
									sprintf (str,"%g",Min_InsulationResistance  );
									memset (Space,' ',8-strlen (str));
									strcat(str,Space);
									Uart_printf( Fixture.Comm_Uart,"%s",str);							
									// ValueSHORT_RES.Status[i],
									memset (str,0,64);
									memset (Space,0,64); //Open_Data.Status ,Open_Data.RESULT
									sprintf (str,"%0.4f",Open_Data.Value[CNT]);
									memset (Space,' ',12-strlen (str));
									strcat(str,Space);
									Uart_printf( Fixture.Comm_Uart,"%s",str);	
									// Unit
									memset (str,0,64);
									memset (Space,0,64);
									sprintf (str,"Mohm");
									memset (Space,' ',8-strlen (str));
									strcat(str,Space);
									Uart_printf( Fixture.Comm_Uart,"%s",str);				
									// Result
									memset (str,0,64);
									Uart_printf( Fixture.Comm_Uart,"%s",Open_Data._Status[CNT] == True ?"PASS":"FAIL");		
									Uart_printf( Fixture.Comm_Uart,"\r\n");	
									j ++;CNT ++;
								}
						}			
			}
		}
		if(TestConfig.Component  == ENABLE ){
				for( i = 0; Item[i].Name ; i ++){
					Number ++;
					Uart_printf( Fixture.Comm_Uart,"%3d     ",Number);
					// Item Name
					memset (str,0,64);
					memset (Space,0,64);
					sprintf (str,"%s",Item[i].Name );
					memset (Space,' ',25-strlen (str));
					strcat(str,Space);
					Uart_printf( Fixture.Comm_Uart,"%s",str);
					// USL
					memset (str,0,64);
					memset (Space,0,64);
					sprintf (str,"%g",Item[i].USL );
					memset (Space,' ',8-strlen (str));
					strcat(str,Space);
					Uart_printf( Fixture.Comm_Uart,"%s",str);							
					// LSL
					memset (str,0,64);
					memset (Space,0,64);
					sprintf (str,"%g",Item[i].LSL  );
					memset (Space,' ',8-strlen (str));
					strcat(str,Space);
					Uart_printf( Fixture.Comm_Uart,"%s",str);							
					// ValueSHORT_RES.Status[i],
					memset (str,0,64);
					memset (Space,0,64); //Open_Data.Status ,Open_Data.RESULT
					sprintf (str,"%0.4f",Item_Data[i].Value );
					memset (Space,' ',12-strlen (str));
					strcat(str,Space);
					Uart_printf( Fixture.Comm_Uart,"%s",str);	
					// Unit
					memset (str,0,64);
					memset (Space,0,64);
					sprintf (str,"%s",Item[i].Unit);
					memset (Space,' ',8-strlen (str));
					strcat(str,Space);
					Uart_printf( Fixture.Comm_Uart,"%s",str);				
					// Result
					memset (str,0,64);
					Uart_printf( Fixture.Comm_Uart,"%s",Item_Data[i].Status == True ?"PASS":"FAIL");		
					Uart_printf( Fixture.Comm_Uart,"\r\n");	
				}
		}		
		if(TestConfig.FCT  == ENABLE ){
	
		}
		Uart_printf( Fixture.Comm_Uart,"\r\n");	
	
	return True;
}

