


#ifndef AD9959_AD9959_H
#define AD9959_AD9959_H

#include "main.h"
#include "stdbool.h"
#include "gpio.h"
#include "main.h"

#define AD9959_CS_1 HAL_GPIO_WritePin(AD9959_CS_GPIO_Port,AD9959_CS_Pin,GPIO_PIN_SET)
#define AD9959_SCLK_1 HAL_GPIO_WritePin(AD9959_SCLK_GPIO_Port,AD9959_SCLK_Pin,GPIO_PIN_SET)
#define AD9959_UPDATE_1 HAL_GPIO_WritePin(AD9959_UPDATE_GPIO_Port,AD9959_UPDATE_Pin,GPIO_PIN_SET)
#define AD9959_PS0_1 HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port,AD9959_PS0_Pin,GPIO_PIN_SET)
#define AD9959_PS1_1 HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port,AD9959_PS1_Pin,GPIO_PIN_SET)
#define AD9959_PS2_1 HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port,AD9959_PS2_Pin,GPIO_PIN_SET)
#define AD9959_PS3_1 HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port,AD9959_PS3_Pin,GPIO_PIN_SET)
#define AD9959_SDIO0_1 HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port,AD9959_SDIO0_Pin,GPIO_PIN_SET)
#define AD9959_SDIO1_1 HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port,AD9959_SDIO1_Pin,GPIO_PIN_SET)
#define AD9959_SDIO2_1 HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port,AD9959_SDIO2_Pin,GPIO_PIN_SET)
#define AD9959_SDIO3_1 HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port,AD9959_SDIO3_Pin,GPIO_PIN_SET)
#define AD9959_PDC_1 HAL_GPIO_WritePin(AD9959_PDC_GPIO_Port,AD9959_PDC_Pin,GPIO_PIN_SET)
#define AD9959_RESET_1 HAL_GPIO_WritePin(AD9959_RESET_GPIO_Port,AD9959_RESET_Pin,GPIO_PIN_SET)

#define AD9959_CS_0 HAL_GPIO_WritePin(AD9959_CS_GPIO_Port,AD9959_CS_Pin,GPIO_PIN_RESET)
#define AD9959_SCLK_0 HAL_GPIO_WritePin(AD9959_SCLK_GPIO_Port,AD9959_SCLK_Pin,GPIO_PIN_RESET)
#define AD9959_UPDATE_0 HAL_GPIO_WritePin(AD9959_UPDATE_GPIO_Port,AD9959_UPDATE_Pin,GPIO_PIN_RESET)
#define AD9959_PS0_0 HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port,AD9959_PS0_Pin,GPIO_PIN_RESET)
#define AD9959_PS1_0 HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port,AD9959_PS1_Pin,GPIO_PIN_RESET)
#define AD9959_PS2_0 HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port,AD9959_PS2_Pin,GPIO_PIN_RESET)
#define AD9959_PS3_0 HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port,AD9959_PS3_Pin,GPIO_PIN_RESET)
#define AD9959_SDIO0_0 HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port,AD9959_SDIO0_Pin,GPIO_PIN_RESET)
#define AD9959_SDIO1_0 HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port,AD9959_SDIO1_Pin,GPIO_PIN_RESET)
#define AD9959_SDIO2_0 HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port,AD9959_SDIO2_Pin,GPIO_PIN_RESET)
#define AD9959_SDIO3_0 HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port,AD9959_SDIO3_Pin,GPIO_PIN_RESET)
#define AD9959_PDC_0 HAL_GPIO_WritePin(AD9959_PDC_GPIO_Port,AD9959_PDC_Pin,GPIO_PIN_RESET)
#define AD9959_RESET_0 HAL_GPIO_WritePin(AD9959_RESET_GPIO_Port,AD9959_RESET_Pin,GPIO_PIN_RESET)



typedef enum {
    AD9959_CHANNEL_0 = 0x10U,
    AD9959_CHANNEL_1 = 0x20U,
    AD9959_CHANNEL_2 = 0x40U,
    AD9959_CHANNEL_3 = 0x80U,
} AD9959_CHANNEL;

typedef enum {
    AD9959_REG_CSR       =   0x00U,  //CSR ??????????????
    AD9959_REG_FR1       =   0x01U,  //FR1 ??????????1
    AD9959_REG_FR2       =   0x02U,  //FR2 ??????????2
    AD9959_REG_CFR       =   0x03U,  //CFR ??????????????
    AD9959_REG_CFTW0     =   0x04U,  //CTW0 ????????????????????
    AD9959_REG_CPOW0     =   0x05U,  //CPW0 ????????????????????
    AD9959_REG_ACR       =   0x06U,  //ACR ??????????????
    AD9959_REG_LSRR      =   0x07U,  //LSR ??????????????????
    AD9959_REG_RDW       =   0x08U,  //RDW ??????????????????????
    AD9959_REG_FDW       =   0x09U,  //FDW ??????????????????????
	
} AD9959_REG_ADDR;

#define 	Channel_Word_1      0x0A
#define	Channel_Word_2      0x0B
#define	Channel_Word_3      0x0C
#define	Channel_Word_4      0x0D
#define	Channel_Word_5      0x0E
#define	Channel_Word_6      0x0F
#define	Channel_Word_7      0x10
#define	Channel_Word_8      0x11
#define	Channel_Word_9      0x12
#define	Channel_Word_10      0x13
#define	Channel_Word_11      0x14
#define	Channel_Word_12      0x15
#define	Channel_Word_13      0x16
#define	Channel_Word_14      0x17
#define	Channel_Word_15      0x18

#define IS_AD9959_REG_ADDR(REG_ADDR)    (((REG_ADDR) == AD9959_REG_CSR  ) || \
                                         ((REG_ADDR) == AD9959_REG_FR1  ) || \
                                         ((REG_ADDR) == AD9959_REG_FR2  ) || \
                                         ((REG_ADDR) == AD9959_REG_CFR  ) || \
                                         ((REG_ADDR) == AD9959_REG_CFTW0) || \
                                         ((REG_ADDR) == AD9959_REG_CPOW0) || \
                                         ((REG_ADDR) == AD9959_REG_ACR  ) || \
                                         ((REG_ADDR) == AD9959_REG_LSRR ) || \
                                         ((REG_ADDR) == AD9959_REG_RDW  ) || \
                                         ((REG_ADDR) == AD9959_REG_FDW  ))

#define IS_AD9959_CHANNEL(CHANNEL)      (((CHANNEL) == AD9959_CHANNEL_0 ) || \
                                         ((CHANNEL) == AD9959_CHANNEL_1 ) || \
                                         ((CHANNEL) == AD9959_CHANNEL_2 ) || \
                                         ((CHANNEL) == AD9959_CHANNEL_3 ))

void ad9959_init(void);
void ad9959_reset(void);
void ad9959_io_init(void);
void ad9959_io_update(void);
void ad9959_write_data(AD9959_REG_ADDR register_address, uint8_t number_of_registers, const uint8_t *register_data, bool update);
void ad9959_write_phase(AD9959_CHANNEL channel, uint16_t phase);
void ad9959_write_frequency(AD9959_CHANNEL channel, uint32_t frequency);
void ad9959_write_amplitude(AD9959_CHANNEL channel, uint16_t amplitude);
void ad9959_modulation_Init(u8 mod_way,u8 mod_lev);
void ad9959_Amod_set(u32 *ASK,u8 num);





#endif //AD9959_AD9959_H

