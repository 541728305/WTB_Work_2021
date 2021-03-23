#ifndef __SUP_FUN_H_
#define __SUP_FUN_H_
#include "stm32f10x_it.h" 



//#define                (uint16_t)(0x0010) // 1<<5  //
//*******************************气缸操作控制 1--16****************************************************************
#define K1_Pull_Up                 (uint32_t)(0x00000800) // 1<<0 
#define K2_1V8_COMAB               (uint32_t)(0x00002000) // 1<<0 
#define K3_COMCD_IN2_3             (uint32_t)(0x00000100) // 1<<0  
#define K4_CAP_RMS                 (uint32_t)(0x00004000) // 1<<0  
#define K5_IIC_COMCD               (uint32_t)(0x00000040) // 1<<0  
#define K6_100mA_Src               (uint32_t)(0x00000080) // 1<<0  
#define K7_CAP_COMAB               (uint32_t)(0x00008000) // 1<<0 
#define K8_Src_COMAB               (uint32_t)(0x00000020) // 1<<0 
#define K9_K11_TVS                 (uint32_t)(0x00000200) // 1<<0  
#define K10_Ref_IN0_1              (uint32_t)(0x00000010) // 1<<0  
#define K12_10R_Ref          			 (uint32_t)(0x00000008) // 1<<0 
#define K13_20K_Ref          			 (uint32_t)(0x00000004) // 1<<0  
#define K14_1K_Ref                 (uint32_t)(0x00000002)
#define K15_Src_Choice             (uint32_t)(0x00000001)
#define No_Connect1                (uint32_t)(0x00000400) // 1<<0 
#define Beep_CTR                   (uint32_t)(0x00001000) // 1<<0  





#define K20_CAP7_CTL              (uint32_t)(0x00010000) // 1<<0 
#define K19_CAP6_CTL              (uint32_t)(0x00020000) // 1<
#define K18_CAP5_CTL              (uint32_t)(0x00040000) // 1<<0 
#define K17_CAP4_CTL              (uint32_t)(0x00080000) // 1<<0  
#define K16_CAP3_CTL              (uint32_t)(0x00800000) // 1<<0 
#define K22_CAP2_CTL              (uint32_t)(0x00200000) // 1<<0 
#define K21_CAP1_CTL              (uint32_t)(0x00100000) // 1<<0  

 



#define K23_CAP_REF               (uint32_t)(0x00400000) // 1<<0 


#define OUT_IO_1    PEout(6)
#define OUT_IO_2    PCout(13)
#define OUT_IO_3    PCout(14)
#define OUT_IO_4    PCout(15)
#define OUT_IO_5    PFout(0)
#define OUT_IO_6    PFout(1)
#define OUT_IO_7    PFout(2)
#define OUT_IO_8    PFout(3)
#define OUT_IO_9    PFout(4)
#define OUT_IO_10   PFout(5)
#define OUT_IO_11   PFout(6)
#define OUT_IO_12   PFout(7)

#define OUT_IO_13   PEout(4)
#define OUT_IO_14   PEout(5)

#define OUT_IO_15   PCout(1)
#define OUT_IO_16   PCout(2)
#define OUT_IO_17   PCout(3)


#define   MOVE1     (uint32_t)(0x00000001)
#define   MOVE2     (uint32_t)(0x00000002)
#define   MOVE3     (uint32_t)(0x00000004)
#define   MOVE4     (uint32_t)(0x00000008)			                    
#define   MOVE5     (uint32_t)(0x00000010)
#define   MOVE6     (uint32_t)(0x00000020)
#define   MOVE7     (uint32_t)(0x00000040)
#define   MOVE8     (uint32_t)(0x00000080)                    
#define   MOVE9     (uint32_t)(0x00000100)
#define   MOVE10    (uint32_t)(0x00000200)
#define   MOVE11    (uint32_t)(0x00000400)
#define   MOVE12    (uint32_t)(0x00000800)                   
#define   MOVE13    (uint32_t)(0x00001000)
#define   MOVE14    (uint32_t)(0x00002000)

#define   MOVE15    (uint32_t)(0x00004000)
#define   MOVE16    (uint32_t)(0x00008000)
#define   MOVE17    (uint32_t)(0x00010000)

#define  Red_Light         MOVE15
#define  Yellow_Light      MOVE16
#define  Green_Light       MOVE17


                
#define  Red2         MOVE6
#define  Green2       MOVE7
#define  Red3         MOVE8
#define  Green3       MOVE9
#define  Red4         MOVE10
#define  Green4       MOVE11



#define  Big_Cylinder_Down      MOVE4
#define  Pre_Push_Cylinder_Up   MOVE4
#define  Pre_Push_Cylinder_DOWN   MOVE5
#define  Fixe_Products				  MOVE2

#define  Pre_Push_Cylinder       MOVE6
#define  USB_Block_Rress        MOVE2
//#define  SWITCH_RESET           MOVE4




#define  Relax_Product          MOVE2
#define  Vertical_Move          MOVE3
#define  GAS_Pressure           MOVE4







//#define  Pre_Push_Cylinder_Down  MOVE1
//



#define  Pen_Box                MOVE6
#define  Dot_Pen                MOVE5


#define  USB_Block              MOVE2



#define Baipanji   MOVE14





//#define Switch_ON_Up                5//按键气缸1
//#define Switch_ON_Down              6//按键气缸2
//#define Take_Away_Products          7
//#define Switch_ON_Up2               8//按键气缸2

//#define Horizontal_Move             10
//#define AJ_Block_SET                12

  

//*******************************Senosr CTR **************************************************************************


#define Up_Sensor    5
#define Down_sensor  6

#define SEN_SET      0
#define SEN_RESET    1

#define  Safe_Grating_Sensor  			 SENSOR4
#define  MOVE_Check_Sensor           SENSOR7


#define  Motor_Origin_Sensor         SENSOR3
#define  Motor_Limit_Sensor          SENSOR11

#define  Vertical_Up_Sensor          7
#define  Vertical_Down_Sensor        8


void beep(u8 timer,u16 time);

void LED_Light_Check( uint8_t Num,uint16_t ms);

void Drive_Baipanji(void);
void Debug_Banpanji(void);

uint8_t  Read_Sensor_Status(uint8_t Num );

void  MOVE_debug_Fun(void);
void Valve_Drive( uint32_t Num, uint8_t Status);
void Relay_Drive(uint32_t  Num, u8 Status);

void Display_Test_Result(uint8_t Result);
#endif
