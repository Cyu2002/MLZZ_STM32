#include "i2c.h"
#include "delay.h"
#include "si4703.h"

void write_reg(uint8_t addr,uint16_t data){
	i2c_start();
	i2c_send_data(addr<<1);
	i2c_send_data((uint8_t)(data>>8));
	i2c_send_data((uint8_t)data);
	i2c_stop();
}

uint16_t read_reg(uint8_t addr){
	uint16_t data;
	i2c_start();
	i2c_send_data((addr<<1)|1);
	i2c_read_data();
	i2c_read_data();
	i2c_stop();
}

void si4703_init(void){
	reset_l;
	scl_h;
	sda_l;
	sen_h;
	Delay_us(4);
	reset_h;
	Delay_us(4);
//write_reg(0,0b0001001001000010);
//write_reg(1,0b0001001001010011);
	i2c_start();
	i2c_send_data((0b0010000)<<1);
	//02h¿ªÊ¼
	i2c_send_data(0b11000000);
	i2c_send_data(0b00000001);
	
	i2c_send_data(0b10000000);//03
	i2c_send_data(0b10101110);
	
	i2c_send_data(0b00001000);//04
	i2c_send_data(0b00000000);
	
	i2c_send_data(0b00000000);//05
	i2c_send_data(0b01011111);
	
	i2c_send_data(0b00000000);//06
	i2c_send_data(0b00000000);
	
	i2c_send_data(0b11111100);//07
	i2c_send_data(0b00000100);
	
	i2c_stop();
	
}
