/*--------------------------------------------------------------------------
TPIC6B595������ʽ							 	
--------------------------------------------------------------------------*/
#ifndef __ICTPIC6B595_H__
#define __ICTPIC6B595_H__	
#include "sys.h"

#ifndef     ictpic6b95_extern 
#define  ictpic6b95_extern   extern 
#endif



#define  J1802_green_p14  PGout(9)
#define  J1802_white_p15  PDout(3)
#define  J1802_red_p40    PDout(4)


//////////////////////////////////////////////
#define  J1802_id_p12    PAout(5)
#define  USB_id_p12      PAin(6)
//////////////////////////////////////////////


#define  USB_RED_p40      PGin(13)
#define  USB_GREEN_p14    PGin(12)
#define  USB_WHITE_p15    PGin(11)
#define  USB_BLACK_gnd    PGin(10)


/*����IO�� ��������*/

//IO��������
#define ic_6b595_clk 	   PBout(10) 
#define ic_6b595_sda 	   PEout(15)

#define u25_st             PEout(12)
#define u25_clr            PEout(11)

#define u26_st             PEout(14)
#define u26_clr            PEout(13)

#define u22_st             PEout(0)
#define u22_clr            PEout(1)

#define u23_st             PDout(8)
#define u23_clr            PBout(15)







//IC��Ŷ���
#define  U25        (0)
#define  U26        (1)
#define  U22        (2)
#define  U23        (3)

#define TPIC6B595_DELAY_TIME  (50)

//  01  ����         big_cylinder_down_set
//  02  ��USB��·    usb_head_insert_set   
//  03  �������     point_up_set     
//  04  �������     point_box_right_set  
//  05  ��ѹ��       connet_back_off_set down_move_right_cylinder_set
//  06  ������ת���� cycle_cylinder_set     
//  07  ��������     suck_up_down_set   fixed_product_suck_cylinder_set
//  08  ����         take_off_suck_cylinder_set
//  09  ѹסUSB��ͷ  push_sort_set   soft_PCB_get_ready_cylinder_set


//����IC���Ź��ܶ���

	//U25 define*****
	
#define  take_off_suck_cylinder_set	     0x01 //������������������� 
#define  take_off_suck_cylinder_cls	     0x81 

#define  suck_up_down_set                0x02 //�����������¿���
#define  suck_up_down_cls                0x82 





#define  point_up_set                    0x05 //������¿���
#define  point_up_cls                    0x85

#define  point_box_right_set             0x06 //������ҿ���
#define  point_box_right_cls             0x86

#define  connet_back_off_set             0x07 //�Խ�ͷѹ���ƶ�����
#define  connet_back_off_cls             0x87

#define  cycle_cylinder_set              0x08 //������ת���׿���  
#define  cycle_cylinder_cls              0x88 //

	//U26 define  *******
	




//#define  device_n_set                  0x0b  ����ʹ��
//#define  device_n_cls                  0x8b





/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define  control1_set       0x0f      //����ʹ��
#define  control1_cls       0x8f


#define  control2_set       0x0e      //����ʹ��
#define  control2_cls       0x8e

#define  K5_K6_set          0x1b            //HALL�ϵ�������AD����
#define  K5_K6_cls          0x9b

#define  K7_set             0x1c //��������Կ���2
#define  K7_cls             0x9c  

#define  K8_set             0x17 //��������Կ���1
#define  K8_cls             0x97 


//#define  device_n_set                    0x0d  ����ʹ��
//#define  device_n_cls                    0x8d

//#define  device_n_set                    0x0e  ����ʹ��
//#define  device_n_cls                    0x8e

//#define  device_n_set                    0x0f  ����ʹ��
//#define  device_n_cls                    0x8f
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define  speak_set                       0x14 //�����������
#define  speak_cls                       0x94 //

//#define  device_n_set                    0x15  ����ʹ��
//#define  device_n_cls                    0x95

//#define  device_n_set                    0x16  ����ʹ��
//#define  device_n_cls                    0x96

#define  os_test_line_in_set             0x18 //OS������·�������
#define  os_test_line_in_cls             0x98

#define  i_in_to_ad_set                  0x1e//  ����ʹ��
#define  i_in_to_ad_cls                  0x9e


//#define  u70b_data_out_set               0x13 //��������������
#define  u70b_data_out_cls 			     0x93 // 

#define  dz1_st2_set                     0x14 //DZ1 ���� ���� 2
#define  dz1_st2_cls                     0x94 //

#define  line_test_in_ad_set             0x15 //��·����AD���Ե�λ�������
#define  line_test_in_ad_cls             0x95 //

#define  dz1_test_power_select_5v_set    0x16 //CCDͨѶ��·�������
#define  dz1_test_power_select_5v_cls    0x96 //

#define  dz1_st1_set                     0x17 //DZ1 ���� ���� 1
#define  dz1_st1_cls                     0x97 //

#define  dz1_test_in_ad_set              0x18 //DZ1 ���� in AD ����
#define  dz1_test_in_ad_cls              0x98 //

	//U66 define
	
	


#define  u3_vdd_set                      0x1d //��������3
#define  u3_vdd_cls                      0x9d //

#define  u3_in_out_set                   0x1e //��������2
#define  u3_in_out_cls                   0x9e //

#define  DZ1_line_change_set             0x1f //��������1
#define  DZ1_line_change_cls             0x9f //



	
	


void   ictpic6b595_io_init(void);
void   writeic6b595(u8 IC );
//void   deviceinstal(u8 device);
void   beep_time(u16 time);
void   ngbeep(void);

unsigned char os_test(u16 TestStepN);
void check_usb_line(void);
void os_test_io_init(void);
u8 os_test2(void);


#endif

