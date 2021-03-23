#ifndef  	_BARCODE_H__
#define   _BARCODE_H__

		#include "usart.h"
		#include "sys.h"
				#define  ZDT_CMD_Delay            5000
				typedef enum {
					KEYENCE = 0,Infoscan
				}BarcodeReaderType_Def;
				
				


				typedef enum {
						Stand_Alone_mode = 0,
						No_Barcode ,
						By_Hand,
						Normal,
						Camera
				}Scan_Mode;
				
				
				typedef struct {
					USART_TypeDef* USARTx;
					uint8_t  Result;
					uint32_t Time;
					Scan_Mode  Mode;
					uint8_t  Barcode_Reader_Type;
					uint32_t Barcode_Reader_Baud;	
					uint8_t Barcode_Check;
					uint8_t Barcode_Length;
					char     Barcode_Format[33];
					char     Barcode_Buffer[33];
					char   	 Barcode_Reader_Start_Cmd[10];
					char   	 Barcode_Reader_Stop_Cmd[10];
					char     Barcode_OK_Command[16];

				}Scan_Type_def;
				
				

				
				extern  Scan_Type_def Scan;
				
				
				
				
				void Set_Scan_Result( uint8_t Temp);
				void Read_Scan_Configration(void);
				
				uint8_t Scan_Set(void);
				unsigned char Check_Hand_Scan(unsigned char mode);
				unsigned char  Software_Trigger_Scan(void);
				
				Scan_Mode Get_Scan_Mode(void);

#endif

