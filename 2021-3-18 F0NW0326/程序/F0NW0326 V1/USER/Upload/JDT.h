#ifndef _UPLOAD_DATA_
#define _UPLOAD_DATA_

//#define   JDT_Upper_Commputer 

#if defined  JDT_Upper_Commputer 

		unsigned char  Upload_Test_Data(void );
		void Host_Cmd_Check(char *Usart_Buffer );
		unsigned char  Upload_Detail_Test_Data(unsigned char  Result);
		void  Fixture_Num_Set(void );
#endif


#endif
