#ifndef __AD7190ADTEST__H__
#define __AD7190ADTEST__H__	
#include"stm32f10x_it.h" 

#define AD7190_DELAY_TIME1    (2)

/* slave device ID */
#define ID_AD7190               0x04
#define AD7190_SLAVE_ID         0x01
#define AD7190_ID_MASK          0x0F
#define AD7190_RDY_STATE       ad7190_dout

#define AD7190_REG_COMM         0 // ͨѶ�Ĵ��� (ֻд, 8-bit) 
#define AD7190_REG_STAT         0 // ״̬�Ĵ��� (ֻ��, 8-bit) 
#define AD7190_REG_MODE         1 // ģʽ�Ĵ��� (��д, 24-bit)
#define AD7190_REG_CONF         2 // ���üĴ��� (��д, 24-bit)
#define AD7190_REG_DATA         3 // ���ݼĴ��� (ֻ��, 24/32-bit) 
#define AD7190_REG_ID           4 // ID�Ĵ���   (ֻ��, 8-bit) 
#define AD7190_REG_GPOCON       5 // ʧ���Ĵ��� (��д, 8-bit) 
#define AD7190_REG_OFFSET       6 // ƫ�ƼĴ��� (��д, 24-bit 
#define AD7190_REG_FULLSCALE    7 // ������     (��д, 24-bit) 
#define AD7190_REG_RESET        255 //��λ�Ĵ�����ֻд, 8-bit) 

#define AD7190_COMM_WEN         (0 << 7)           // дʹ��. 
#define AD7190_COMM_WRITE       (0 << 6)           // д����.
#define AD7190_COMM_READ        (1 << 6)           // ������. 
#define AD7190_COMM_ADDR(x)     (((x) & 0x7) << 3) // �Ĵ�����ַ(λ��). 
#define AD7190_COMM_CREAD       (1 << 2)           // ���������ݼĴ���.	


#define AD7190_STAT_RDY         (1 << 7) // ADת����ɱ�־λ.
#define AD7190_STAT_ERR         (1 << 6) // ADCת������λ.
#define AD7190_STAT_NOREF       (1 << 5) // ADC���ⲿ�ο���ѹ����λ. 
#define AD7190_STAT_PARITY      (1 << 4) // ���ݼĴ���У��λ. 
#define AD7190_STAT_CH2         (1 << 2) // ͨ�� 2. 
#define AD7190_STAT_CH1         (1 << 1) // ͨ�� 1. 
#define AD7190_STAT_CH0         (1 << 0) // ͨ�� 0. 

#define AD7190_MODE_SEL(x)      (((x) & 0x7) << 21) // ����ģʽѡ��λ��.
#define AD7190_MODE_DAT_STA     (1 << 20)           // ʱ��״̬�Ĵ������.
#define AD7190_MODE_CLKSRC(x)   (((x) & 0x3) << 18) // ʱ��Դѡ��λ��.
#define AD7190_MODE_SINC3       (1 << 15)           // SINC3 �˲���ѡ��.
#define AD7190_MODE_ENPAR       (1 << 13)           // ���ݼĴ���У��ʹ��.
#define AD7190_MODE_SCYCLE      (1 << 11)           // ������ת��ʹ��λ.
#define AD7190_MODE_REJ60       (1 << 10)           // 50/60Hz �޲��˲���.
#define AD7190_MODE_RATE(x)     ((x) & 0x3FF)       // �˲��� �����������ѡ��.

#define AD7190_MODE_CONT                0 // ����ת��ģʽ.
#define AD7190_MODE_SINGLE              1 // ������ת��ģʽ.
#define AD7190_MODE_IDLE                2 // ��תģʽ.
#define AD7190_MODE_PWRDN               3 // ˯��ģʽ.
#define AD7190_MODE_CAL_INT_ZERO        4 // �ڲ�����У��.
#define AD7190_MODE_CAL_INT_FULL        5 // �ڲ�������У��.
#define AD7190_MODE_CAL_SYS_ZERO        6 // ϵͳ����У��.
#define AD7190_MODE_CAL_SYS_FULL        7 // ϵͳ������У��.

#define AD7190_CLK_EXT_MCLK1_2          0 // �ⲿʱ��.�������ӵ� MCLK1 �� MCLK2����.
#define AD7190_CLK_EXT_MCLK2            1 // �ⲿʱ�� ��MCLK2�����룻 MCLK1������ 
#define AD7190_CLK_INT                  2 // �ڲ�4.92MHzʱ��.����MCLK2 Ϊ��̬.
#define AD7190_CLK_INT_CO               3 // �ڲ�4.92MHzʱ��.���ڲ�ʱ�ӻ��MCLK2�������.


#define AD7190_CONF_CHOP        (1 << 23)            // ն��ʹ��.
#define AD7190_CONF_REFSEL      (1 << 20)            // REFIN1/REFIN2 �ο���ѹѡ��.
#define AD7190_CONF_CHAN(x)     (((x) & 0xFF) << 8)  // ͨ��ѡ��λ��.
#define AD7190_CONF_BURN        (1 << 7)             // �ڲ�500������������ʹ��.
#define AD7190_CONF_REFDET      (1 << 6)             // ��׼��ѹ���ʱ��λ.
#define AD7190_CONF_BUF         (1 << 4)             // ģ������˻�����ʹ��.
#define AD7190_CONF_UNIPOLAR    (1 << 3)             // 1����/0˫������ģʽѡ��λ.
#define AD7190_CONF_GAIN(x)     ((x) & 0x7)          // ����ѡ��λ��.


#define AD7190_CH_AIN1P_AIN2M      0x01 // ͨ��1(+)---ͨ��(-)       
#define AD7190_CH_AIN3P_AIN4M      0x02 // ͨ��3(+)---ͨ��4(-)       
#define AD7190_CH_TEMP_SENSOR      0x04 // �¶�  ������       
#define AD7190_CH_AIN2P_AIN2M      0x08 // ͨ��2(+)---ͨ��2(-)       
#define AD7190_CH_AIN1P_AINCOM     0x10 // ͨ��1(+)---ģ�����빫����       
#define AD7190_CH_AIN2P_AINCOM     0x20 // ͨ��2(+)---ģ�����빫����       
#define AD7190_CH_AIN3P_AINCOM     0x40 // ͨ��3(+)---ģ�����빫����       
#define AD7190_CH_AIN4P_AINCOM     0x80 // ͨ��4(+)---ģ�����빫����
                                           
#define AD7190_CONF_GAIN_1		0 // ���� 1    +-5 V
#define AD7190_CONF_GAIN_8		3 // ���� 8    +-625 mV
#define AD7190_CONF_GAIN_16		4 // ���� 16   +-312.5 mV
#define AD7190_CONF_GAIN_32		5 // ���� 32   +-156.2 mV
#define AD7190_CONF_GAIN_64		6 // ���� 64   +-78.125 mV
#define AD7190_CONF_GAIN_128	7 // ���� 128  +-39.06 mV

#define AD7190_GPOCON_BPDSW     (1 << 6) // ���Źر�ʱ��λ
#define AD7190_GPOCON_GP32EN    (1 << 5) // ������� P3 �� P2 ʹ��
#define AD7190_GPOCON_GP10EN    (1 << 4) // ������� P1 �� P0 ʹ��
#define AD7190_GPOCON_P3DAT     (1 << 3) // P3 ״̬���
#define AD7190_GPOCON_P2DAT     (1 << 2) // P2 ״̬���
#define AD7190_GPOCON_P1DAT     (1 << 1) // P1 ״̬���
#define AD7190_GPOCON_P0DAT     (1 << 0) // P0 ״̬���



void AD7190_Init(u8 ENdisplay);
void SPI_Read(u8 registerAdd,u8* data,u8 bytesNumber);
void SPI_Write(u8 registerAdd, u8 * data,u8 bytesNumber);
float  AD7190_AD_To_V(u8 sampleNumber);
u8 Change_AD7190_Channel(u8 channel);
#endif  

