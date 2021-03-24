#include "mic.h"

#include "math.h"
typedef  struct {
	uint8_t BIAS;
	uint8_t AGND;
	uint8_t OUT_P_CLK;
	uint8_t OUT_N_DAT;
	double  Vsrc;
	char *MIC_I;  double  I;   double  I_LSL;   double  I_USL; 
	char *MIC_V;  double  Vpp; double  Vpp_LSL; double  Vpp_USL; 
	char *MIC_S;  double  dB;  double  dB_LSL;  double  dB_USL; 
}	MIC_Test_TypeDef ;

//MIC_Test_TypeDef MIC_TEST={
//		MIC_BIAS_Pin,	 MIC_AGND_Pin,
//		MIC_IN_P_Pin,  MIC_IN_N_Pin,
//	
//		1500,     3600,      2800,  0.0, //供电电压 V
//		200,      120,       50,    0.0, //输入电流 uA
//		12,       14,        10,    0.0, //输出电压
//		-38,     -35,       -41,    0.0  //dB
//};



u8 MIC_test(u16 TestStepN){
	uint8_t  Test_Result;

	return Test_Result;
}
