#include "main.h"

void write_reg(uint8_t addr,uint16_t data);
void si4703_init(void);

#define sen_h HAL_GPIO_WritePin(SEN_GPIO_Port,SEN_Pin,1)
#define sen_l HAL_GPIO_WritePin(SEN_GPIO_Port,SEN_Pin,0)