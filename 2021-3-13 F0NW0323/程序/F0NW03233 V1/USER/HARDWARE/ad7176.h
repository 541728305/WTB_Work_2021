
#ifndef __AD7176_H__
#define __AD7176_H__	

#include "sys.h"


/* AD7176 �Ĵ������Ƽ����ַ */
#define AD717X_COMM_REG       0x00
#define AD717X_STATUS_REG     0x00
#define AD717X_ADCMODE_REG    0x01
#define AD717X_IFMODE_REG     0x02
#define AD717X_REGCHECK_REG   0x03
#define AD717X_DATA_REG       0x04
#define AD717X_GPIOCON_REG    0x06
#define AD717X_ID_REG         0x07
#define AD717X_CHMAP0_REG     0x10
#define AD717X_CHMAP1_REG     0x11
#define AD717X_CHMAP2_REG     0x12
#define AD717X_CHMAP3_REG     0x13
#define AD717X_SETUPCON0_REG  0x20
#define AD717X_SETUPCON1_REG  0x21
#define AD717X_SETUPCON2_REG  0x22
#define AD717X_SETUPCON3_REG  0x23
#define AD717X_FILTCON0_REG   0x28
#define AD717X_FILTCON1_REG   0x29
#define AD717X_FILTCON2_REG   0x2A
#define AD717X_FILTCON3_REG   0x2B
#define AD717X_OFFSET0_REG    0x30
#define AD717X_OFFSET1_REG    0x31
#define AD717X_OFFSET2_REG    0x32
#define AD717X_OFFSET3_REG    0x33
#define AD717X_GAIN0_REG      0x38
#define AD717X_GAIN1_REG      0x39
#define AD717X_GAIN2_REG      0x3A
#define AD717X_GAIN3_REG      0x3B
//#define AD7190_REG_RESET      0xFF



/* ͨѶ�Ĵ���λ���ܶ���  AD717X_COMM_REG    8λ�Ĵ���   */
#define AD717X_COMM_REG_WEN    (0 << 7)     //bit7 ��AD����ͨ�ţ���λ����Ϊ0
#define AD717X_COMM_REG_WR     (0 << 6)     //bit6 =0 ��ʾ��д����
#define AD717X_COMM_REG_RD     (1 << 6)     //bit6 =0 ��ʾ�Ƕ�����
#define AD717X_COMM_REG_RA(x)  ((x) & 0x3F) //�������Ĵ����ĵ�ַ

/* ͨ��ӳ��Ĵ���0��1��2��3 ��λ���� */
#define AD717X_CHMAP_REG_CH_EN         (1 << 15)            //ͨ��ʹ��
#define AD717X_CHMAP_REG_SETUP_SEL(x)  (((x) & 0x3) << 12)  //���üĴ�����ѡ��
#define AD717X_CHMAP_REG_AINPOS(x)     (((x) & 0x1F) << 5)  //ģ���źŸ߶�ѡ��
#define AD717X_CHMAP_REG_AINNEG(x)     (((x) & 0x1F) << 0)  //ģ���źŵͶ�ѡ��

/* Filter Configuration Register 0-3 bits */
#define AD717X_FILT_CONF_REG_SINC3_MAP    (1 << 15)
#define AD717X_FILT_CONF_REG_ENHFILTEN    (1 << 11)
#define AD717X_FILT_CONF_REG_ENHFILT(x)   (((x) & 0x7) << 8)
#define AD717X_FILT_CONF_REG_ORDER(x)     (((x) & 0x3) << 5)
#define AD717X_FILT_CONF_REG_ODR(x)       (((x) & 0x1F) << 0) //������������

#define AD717X_SLOW  AD717X_FILT_CONF_REG_ENHFILTEN | AD717X_FILT_CONF_REG_ODR(1)//����
#define AD717X_FAST  AD717X_FILT_CONF_REG_ORDER(3) //����
#define AD717X_ULTRAFAST  0  //��������

#define AIN0    0  //ģ������ͨ��0
#define AIN1    1  //ģ������ͨ��1
#define AIN2    2  //ģ������ͨ��2
#define AIN3    3  //ģ������ͨ��3
#define AIN4    4  //ģ������ͨ��4
#define VREFP   21 //ģ������ͨ��Vref+
#define VREFN   22 //ģ������ͨ��Vref-
void STM32_Software_Reset_Hander(void);
void AD_Sample_Rate_Set(uint8_t i);
void    Initialize_AD7176(void );
double  Average_Fun(double *dat  , uint8_t  Num);
void MCUISP_Hander(void);
uint8_t Read_AD7176_Voltage_mV(uint32_t AinP,uint32_t AinN, double * readmV);
uint8_t Read_AD7176_Average_Voltage_mV(uint32_t AinP,uint32_t AinN,uint32_t timer, double * readmV);
#endif

