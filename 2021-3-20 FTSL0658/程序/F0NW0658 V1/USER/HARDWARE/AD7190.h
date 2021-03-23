#ifndef __AD7190ADTEST__H__
#define __AD7190ADTEST__H__	
#include"stm32f10x_it.h" 

#define AD7190_DELAY_TIME1    (2)

/* slave device ID */
#define ID_AD7190               0x04
#define AD7190_SLAVE_ID         0x01
#define AD7190_ID_MASK          0x0F
#define AD7190_RDY_STATE       ad7190_dout

#define AD7190_REG_COMM         0 // 通讯寄存器 (只写, 8-bit) 
#define AD7190_REG_STAT         0 // 状态寄存器 (只读, 8-bit) 
#define AD7190_REG_MODE         1 // 模式寄存器 (读写, 24-bit)
#define AD7190_REG_CONF         2 // 配置寄存器 (读写, 24-bit)
#define AD7190_REG_DATA         3 // 数据寄存器 (只读, 24/32-bit) 
#define AD7190_REG_ID           4 // ID寄存器   (只读, 8-bit) 
#define AD7190_REG_GPOCON       5 // 失调寄存器 (读写, 8-bit) 
#define AD7190_REG_OFFSET       6 // 偏移寄存器 (读写, 24-bit 
#define AD7190_REG_FULLSCALE    7 // 满量程     (读写, 24-bit) 
#define AD7190_REG_RESET        255 //复位寄存器（只写, 8-bit) 

#define AD7190_COMM_WEN         (0 << 7)           // 写使能. 
#define AD7190_COMM_WRITE       (0 << 6)           // 写操作.
#define AD7190_COMM_READ        (1 << 6)           // 读操作. 
#define AD7190_COMM_ADDR(x)     (((x) & 0x7) << 3) // 寄存器地址(位段). 
#define AD7190_COMM_CREAD       (1 << 2)           // 连续读数据寄存器.	


#define AD7190_STAT_RDY         (1 << 7) // AD转换完成标志位.
#define AD7190_STAT_ERR         (1 << 6) // ADC转换错误位.
#define AD7190_STAT_NOREF       (1 << 5) // ADC无外部参考电压错误位. 
#define AD7190_STAT_PARITY      (1 << 4) // 数据寄存器校验位. 
#define AD7190_STAT_CH2         (1 << 2) // 通道 2. 
#define AD7190_STAT_CH1         (1 << 1) // 通道 1. 
#define AD7190_STAT_CH0         (1 << 0) // 通道 0. 

#define AD7190_MODE_SEL(x)      (((x) & 0x7) << 21) // 操作模式选择位段.
#define AD7190_MODE_DAT_STA     (1 << 20)           // 时能状态寄存器输出.
#define AD7190_MODE_CLKSRC(x)   (((x) & 0x3) << 18) // 时钟源选择位段.
#define AD7190_MODE_SINC3       (1 << 15)           // SINC3 滤波器选择.
#define AD7190_MODE_ENPAR       (1 << 13)           // 数据寄存器校验使能.
#define AD7190_MODE_SCYCLE      (1 << 11)           // 单周期转换使能位.
#define AD7190_MODE_REJ60       (1 << 10)           // 50/60Hz 限波滤波器.
#define AD7190_MODE_RATE(x)     ((x) & 0x3FF)       // 滤波器 输出数据速率选择.

#define AD7190_MODE_CONT                0 // 连续转换模式.
#define AD7190_MODE_SINGLE              1 // 单周期转换模式.
#define AD7190_MODE_IDLE                2 // 空转模式.
#define AD7190_MODE_PWRDN               3 // 睡眠模式.
#define AD7190_MODE_CAL_INT_ZERO        4 // 内部归零校验.
#define AD7190_MODE_CAL_INT_FULL        5 // 内部满量程校验.
#define AD7190_MODE_CAL_SYS_ZERO        6 // 系统归零校验.
#define AD7190_MODE_CAL_SYS_FULL        7 // 系统满量程校验.

#define AD7190_CLK_EXT_MCLK1_2          0 // 外部时钟.晶振连接到 MCLK1 和 MCLK2引脚.
#define AD7190_CLK_EXT_MCLK2            1 // 外部时钟 从MCLK2脚输入； MCLK1脚悬空 
#define AD7190_CLK_INT                  2 // 内部4.92MHz时钟.引脚MCLK2 为三态.
#define AD7190_CLK_INT_CO               3 // 内部4.92MHz时钟.该内部时钟会从MCLK2引脚输出.


#define AD7190_CONF_CHOP        (1 << 23)            // 斩波使能.
#define AD7190_CONF_REFSEL      (1 << 20)            // REFIN1/REFIN2 参考电压选择.
#define AD7190_CONF_CHAN(x)     (((x) & 0xFF) << 8)  // 通道选择位段.
#define AD7190_CONF_BURN        (1 << 7)             // 内部500毫安激励电流使能.
#define AD7190_CONF_REFDET      (1 << 6)             // 基准电压检测时能位.
#define AD7190_CONF_BUF         (1 << 4)             // 模拟输入端缓冲区使能.
#define AD7190_CONF_UNIPOLAR    (1 << 3)             // 1单极/0双极工作模式选择位.
#define AD7190_CONF_GAIN(x)     ((x) & 0x7)          // 增益选择位段.


#define AD7190_CH_AIN1P_AIN2M      0x01 // 通道1(+)---通道(-)       
#define AD7190_CH_AIN3P_AIN4M      0x02 // 通道3(+)---通道4(-)       
#define AD7190_CH_TEMP_SENSOR      0x04 // 温度  传感器       
#define AD7190_CH_AIN2P_AIN2M      0x08 // 通道2(+)---通道2(-)       
#define AD7190_CH_AIN1P_AINCOM     0x10 // 通道1(+)---模拟输入公共端       
#define AD7190_CH_AIN2P_AINCOM     0x20 // 通道2(+)---模拟输入公共端       
#define AD7190_CH_AIN3P_AINCOM     0x40 // 通道3(+)---模拟输入公共端       
#define AD7190_CH_AIN4P_AINCOM     0x80 // 通道4(+)---模拟输入公共端
                                           
#define AD7190_CONF_GAIN_1		0 // 增益 1    +-5 V
#define AD7190_CONF_GAIN_8		3 // 增益 8    +-625 mV
#define AD7190_CONF_GAIN_16		4 // 增益 16   +-312.5 mV
#define AD7190_CONF_GAIN_32		5 // 增益 32   +-156.2 mV
#define AD7190_CONF_GAIN_64		6 // 增益 64   +-78.125 mV
#define AD7190_CONF_GAIN_128	7 // 增益 128  +-39.06 mV

#define AD7190_GPOCON_BPDSW     (1 << 6) // 电桥关闭时能位
#define AD7190_GPOCON_GP32EN    (1 << 5) // 数字输出 P3 和 P2 使能
#define AD7190_GPOCON_GP10EN    (1 << 4) // 数字输出 P1 和 P0 使能
#define AD7190_GPOCON_P3DAT     (1 << 3) // P3 状态输出
#define AD7190_GPOCON_P2DAT     (1 << 2) // P2 状态输出
#define AD7190_GPOCON_P1DAT     (1 << 1) // P1 状态输出
#define AD7190_GPOCON_P0DAT     (1 << 0) // P0 状态输出



void AD7190_Init(u8 ENdisplay);
void SPI_Read(u8 registerAdd,u8* data,u8 bytesNumber);
void SPI_Write(u8 registerAdd, u8 * data,u8 bytesNumber);
float  AD7190_AD_To_V(u8 sampleNumber);
u8 Change_AD7190_Channel(u8 channel);
#endif  

