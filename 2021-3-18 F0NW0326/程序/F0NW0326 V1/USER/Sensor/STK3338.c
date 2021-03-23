#include "sensor.h"
#include <string.h>
#include "sensor.h"
#include "Sup_Fun.h"



Sensor_Current_TypeDef STK3338_Current[] = {
	/* Name**********Src   ***Value****Unit******USL*****LSL****Delay****result*/	
	{ "I_VCSEL",     3300,   0.0,     "mA",      30,    0.05,      50,     99},
	{ "I_Sleep",     1800,   0.0,     "uA",      5.0,   0.00,     50,     99},
	{ "I_ALS",       1800,   0.0,     "uA",      288,    192,     50,     99},	
	{ "I_PS",        1800,   0.0,     "uA",      312,    208,     50,     99},

	{ NULL },		
	
};
ALS_Sensor_TypeDef STK3338_ALS[]= {
//	***   *Name;  ***  Addr;***  Num;***  Value;*** *Unit;***  USL;***  LSL;***  Time;***Condition *** Status;
	{ "ID",               0x3E,     1,        0,     "Counts",    0x58,    0x58,     50,     0x0000,        99    },
	{ "Dark",             0x13,     2,        0,     "Counts",      10,       0,     50,     0x0000,        99    },	
	{ "White",            0x13,     2,        0,     "Counts",    6095,    4505,     50,     White_Light ,  99    },	
	{ "IR",               0x13,     2,        0,     "Counts",    2500,     500,     50,     IR_Light ,     99    },
	{ "PROX_ON",          0x11,     2,        0,     "Counts",     518,     382,     50,     Gray_Card ,    99    },	
	{ "PROX_OFF",         0x11,     2,        0,     "Counts",     100,       0,     500,    0x0000   ,     99    },																																																				
	{ NULL },			     
};


