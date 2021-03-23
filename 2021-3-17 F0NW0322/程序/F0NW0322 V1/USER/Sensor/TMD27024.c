#include <string.h>
#include "sensor.h"
#include "Sup_Fun.h"



uint8_t  AlS_Slave_Addr = 0x49;


Sensor_Current_TypeDef TMD27024_Current[] = {
	/* Name**********Src   ***Value****Unit******USL*****LSL****Delay****result*/
	
	{ "I_VCSEL",     3300,   0.0,     "mA",      35.0,  0.05,     50,     99},
	{ "Idd_Sleep",   1800,   0.0,     "uA",      5.0,   0.00,     50,     99},
	{ "Idd_Idle",    1800,   0.0,     "uA",      60,      10,     50,     99},
	{ "Idd_Act",     1800,   0.0,     "uA",      140,    105,     50,     99},	
	{ NULL },		
};
ALS_Sensor_TypeDef TMD27024_ALS[]= {
//	***   *Name;  ***  Addr;***  Num;***  Value;*** *Unit;***  USL;***  LSL;***  Time;***Condition *** Status;
	{ "ID",              0x92,     1,        0,     "Counts",    0x10,    0x10,     50,     0x0000,        99    },
	{ "Dark",            0x94,     2,        0,     "Counts",      10,       0,     50,     0x0000,        99    },		
	{ "White",           0x94,     2,        0,     "Counts",    6095,    4505,     50,     White_Light,   99    },	
	{ "IR",              0x96,     2,        0,     "Counts",      50,      10,     50,     IR_Light ,     99    },
	{ "PROX_ON",         0x9C,     2,        0,     "Counts",    2000,     800,     50,     Gray_Card,     99    },	
	{ "PROX_OFF",        0x9C,     2,        0,     "Counts",     100,       0,    500,     0x0000,        99    },																																																				
	{ NULL },			
};

