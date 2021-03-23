#include"pca9535.h"
#include"head.h"
uint16_t    U81_PCA9535_Data = 0xFFFF;
void IIC_Start1(void){
	SDA_OUT1();     
	IIC_SDA1=1;	  	  
	IIC_SCL1=1;
	delay_us(IIC_DELAY_TIME);
 	IIC_SDA1=0; 
	delay_us(IIC_DELAY_TIME);
	IIC_SCL1=0;
}	  
void IIC_Stop1(void){
	SDA_OUT1();
	IIC_SCL1=0;
	IIC_SDA1=0;
 	delay_us(IIC_DELAY_TIME);
	IIC_SCL1=1; 
	IIC_SDA1=1;
	delay_us(IIC_DELAY_TIME);							   	
}
u8 IIC_Wait_Ack1(void){
	u8 ucErrTime=0;
	SDA_IN1();      
	IIC_SDA1=1;delay_us(IIC_DELAY_TIME);	   
	IIC_SCL1=1;delay_us(IIC_DELAY_TIME);	 
	while(READ_SDA1)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop1();
	//		lcd_printf("Device NO ACK   ");
			return 1;
		}
	}
	IIC_SCL1=0;
	delay_us(IIC_DELAY_TIME);	 
	return 0;  
} 
void IIC_Ack1(void){
	IIC_SCL1=0;
	SDA_OUT1();
	IIC_SDA1=0;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL1=1;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL1=0;
}
		    
void IIC_NAck1(void){
	IIC_SCL1=0;
	SDA_OUT1();
	IIC_SDA1=1;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL1=1;
	delay_us(IIC_DELAY_TIME);
	IIC_SCL1=0;
}					 				     
			  
void IIC_Send_Byte1(u8 txd){                        
    u8 t;   
		SDA_OUT1(); 	    
    IIC_SCL1=0;
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			IIC_SDA1=1;
		else
			IIC_SDA1=0;
		txd<<=1; 	  
		delay_us(IIC_DELAY_TIME);   
		IIC_SCL1=1;
		delay_us(IIC_DELAY_TIME); 
		IIC_SCL1=0;	
		delay_us(IIC_DELAY_TIME);
    }	 
} 	      
u8 IIC_Read_Byte1(unsigned char ack){
	unsigned char i,receive=0;
	SDA_IN1();
  for(i=0;i<8;i++ )
	{
    IIC_SCL1=0; 
    delay_us(IIC_DELAY_TIME);
		IIC_SCL1=1;
    receive<<=1;
    if(READ_SDA1)
			receive++;   
		delay_us(IIC_DELAY_TIME); 
   }					 
   if (!ack)
     IIC_NAck1();
   else
     IIC_Ack1(); 
   return receive;
}


u8 Write_CMD_Analog_Relay( u8  Slave_Addr, u8 Reg_Addr ,u8 Command ){
	IIC_Start1 ();
	IIC_Send_Byte1((Slave_Addr <<1)|Write );
	if(IIC_Wait_Ack1 ())
		return 1;
	IIC_Send_Byte1(Reg_Addr);
	if(IIC_Wait_Ack1 ())
		return 1;
	IIC_Send_Byte1(Command);
	if(IIC_Wait_Ack1 ())
		return 1;
	IIC_Stop ();
	return 0;
}

u8 Write_Data_Analog_Relay( uint16_t  Analog_Switch_Data){
	if(Write_CMD_Analog_Relay(Slave_Addr_PCA9535_U81,PCA9535_Output_Port_Reg_L ,(uint8_t )(Analog_Switch_Data&0xFF))==0)
	   Write_CMD_Analog_Relay(Slave_Addr_PCA9535_U81,PCA9535_Output_Port_Reg_H ,(uint8_t )(Analog_Switch_Data>>8));
	else {
		cyc4or3run ();
		lcd_printf ("ERROR: U81       ");
		while(1);
	}
	return 0;
}
extern uint16_t  U81_PCA9535_Data;

void Analog_Relay( uint16_t  Num ,u8 Status){
	if(Num ){
		if(Status == SET )
			U81_PCA9535_Data  &= ~Num;
		if(Status == RESET )
			U81_PCA9535_Data  |= Num;
	}
	else 
		U81_PCA9535_Data = 0xFFFF;
	Write_Data_Analog_Relay(U81_PCA9535_Data);

}
void Close_All_Analog_Relay(){
	U81_PCA9535_Data = 0xFFFF;
	Write_Data_Analog_Relay(U81_PCA9535_Data);
}


//�������� Write_CMD_PCA9535
//��  �ܣ� ��PCA9535д��8bit ����
//��  ���� Slave_Addr���ӻ���ַ��Reg_Addr�Ĵ�����ַ Command ��д�������   
//����ֵ��ͨѶOk ����True  NG ���� False
u8 Write_CMD_PCA9535( u8  Slave_Addr, u8 Reg_Addr ,u8 Command ){
	IIC_Start ();
	IIC_Send_Byte((Slave_Addr <<1)|Write );
	if(IIC_Wait_Ack ())
		return 1;
	IIC_Send_Byte(Reg_Addr);
	if(IIC_Wait_Ack ())
		return 1;
	IIC_Send_Byte(Command);
	if(IIC_Wait_Ack ())
		return 1;
	IIC_Stop ();
	return 0;
}
//��������Read_Data_PCA9535
//��  �ܣ���ĳ��PCA9535��ȡ���ݣ��������ݴ���data��
//��  ����Slave_Addr���ӻ���ַ��Reg_Addr�Ĵ�����ַ *data ��Ĵ�����ָ��
//����ֵ��ͨѶOk ����True  NG ���� False
u8  Read_Data_PCA9535(u8 Slave_Addr, u8 Reg_Addr, u8 *data){
	IIC_Start ();
	IIC_Send_Byte((Slave_Addr <<1)|Write );
	if(IIC_Wait_Ack ())		return 1;
	IIC_Send_Byte(Reg_Addr);
	if(IIC_Wait_Ack ())  	return 1;
	IIC_Start ();
	IIC_Send_Byte((Slave_Addr <<1)|Read );
	if(IIC_Wait_Ack ()) return 1;
	*data = IIC_Read_Byte(0);
	IIC_Stop ();
	return 0;
}


//�������� Initalize_PCA9535
//��  �ܣ� ��ʼ��PCA9535 U79����Ϊ���룬���ڼ��Sensor���룬 U81����Ϊ�������������ģ��̵���
//��  ���� ��
//����ֵ�� ��
void Initalize_PCA9535(){
	//����U79Ϊ����
	if(Write_CMD_PCA9535(Slave_Addr_PCA9535_U79,PCA9535_Config_Reg_H,0xFF ) == 0){
	   Write_CMD_PCA9535(Slave_Addr_PCA9535_U79,PCA9535_Config_Reg_L,0xFF );
	}	else{
			cyc4or3run ();
			lcd_printf ("ERROR: U79       ");
			while(1);
	}
		//����U81Ϊ���
	if(Write_CMD_Analog_Relay(Slave_Addr_PCA9535_U81,PCA9535_Config_Reg_H,0x00 ) == 0){
		 Write_CMD_Analog_Relay(Slave_Addr_PCA9535_U81,PCA9535_Config_Reg_L,0x00 );
	}	else{
			cyc4or3run ();
			lcd_printf ("ERROR: U81       ");
			while(1);
	}
	//����U81�����Ϊ��
	U81_PCA9535_Data = 0xFFFF;
	Write_Data_Analog_Relay(U81_PCA9535_Data);
}
