#ifndef _CO2_H
#define _CO2_H

#include "main.h"
#include "CO2_IIC.h"

#define SGP30_address  0x58
#define Init_air_quality 0x2003
#define Measure_air_quality 0x2008

#define WR 0
#define RR 1 



void SGP_30_Init(void);
void SGP_30_Writedata(u16 data);
u32 SGP_30_Readdata();

#endif