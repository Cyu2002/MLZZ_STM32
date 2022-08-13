#ifndef _RDA5820_H
#define _RDA5820_H


#include "main.h"
#include "RDA_IIC.h"

//address
#define RDA_ADD		0X11

//Register Definition

#define CHIPID 		0X00
#define Register1	 0x02
//DHIZ[15],DMUTE[14],MONO[13],BASS[12],SEEKUP[9],SEEK[8],SKMODE[7],CLK_MODE[6:4],ANTENNA[2],SOFTRESET[1],ENABLE[0]
//bit0 ENABLE 芯片上电1 芯片不上电0
//bit1 SOFTRESET 芯片软复位1 不复位0
//bit2 ANTENNA 1使用内部小天线 0使用正常的外部天线(内部小天线速度慢很多)
//bit6-bit4 时钟频率选择,根据实际频率选择 000 32.768khz
// bit7 SKMODE 0循环搜索 1到达上线或者下限时停止搜索
//bit8 SEEK 0搜索已经停止 1搜索开始
//bit9 搜索方向 0向下 1向上
//bit12 BASS 0不使能低音增强 1使能低音增强
//bit13 MONO 声道选择 0立体声 1非立体声
//bit14 DMUTE 静音选择 0静音 1非静音
//bit15 DHIZ 音频输出高阻抗选择 0选择高阻抗 1不选择高阻抗
#define Register2 	0x03
//bit15-6 当前频道,通过baud可以计算当前频率
//bit4 调谐 0关闭调谐 1启动调谐
//bit3-2 baud 频段选择 四种选择
//bit1-0 步进选择 00为100K
#define Register3 	0x04
//STCIEN[14](搜索完成中断),DE[11],I2S_ENABLE[6],GPIO3~1[5:0]
//bit14 1开启调谐调频中断 0关闭中断 中断引脚显示在GPIO2上
//bit11 去加重时间选择 0 75us 1 50us
//bit6 i2s使能 0不使能 1使能
//bit5-bit0 三个GPIO的功能选择 建议都是00

#define Register4 	0x05
//INT_MODE[15],SEEKTH[14:8](设定信号强度),LNA_PORT_SEL[7:6],LNA_ICSEL_BIT[5:4],VOLUME[3:0];
//bit15 中断模式 0短时间中断 1直到清除0c才取消中断
//bit14-8 搜索阈值 高于这个值认为是有效台
//bit7-6 输入低噪声放大模式 00无输入
//bit5-4 输入低噪声电流 00 1.8ma
//bit3-0 音量 0000最低1111最高
#define Register5	 0x06
#define Register6 	0x07
#define Register7 	0x0A
//STC[14](搜索完成标志),SF[13](搜索失败标志),ST[10] (立体声标志),READCHAN[9:0](频率).
//bit14 搜台完成标志 0未完成 1完成
//bit13 搜台失败标志 0成功 1失败
//bit10 立体声指示 0单声道 1立体声
//bit9-bit0 当前频率指示,可以计算出当前频率
#define Register8	 0x0B
//RSSI[15:9](信号强度),FM_TRUE[8](站点标志),FM_READY[7](fm就绪标志)
//bit15-9 当前信号强度
//bit8 1当前频率是一个有效台 0不是
//bit7 1 已经准备好软件搜台 0没准备好
#define Register9	 0x0C

#define Register10	 0x0D
//AUTO_SEEK[15](全/半自动搜台),CHAN_SCAN[14](搜空/忙台),CHIP_FUN[3:0](工作模式)
//bit15 1全自动搜台 0手动搜台
//bit14 为FM发射搜索一个空闲频率
//bit3-0 选择工作模式 0000 rx模式
#define Register11 	0x0E
#define Register12 	0x0F
#define Register13 	0x40//WORK MODE
#define Register14	 0x41
 //MEM_CLR[15](内存清除),RPT_TIME[14:9](RDS应答次数),MEM_DEPTH[8:0](FIFO大小,最大256)
//bit15 1复位fifo 0不复位
//bit14-9 传输数据是RDS应答次数
//bit8-0 fifo的深度 0-256
#define Register15	 0x67



u8 Rda5820Init(void);
void RDA_SendData(u8 REGADD,u16 DATA);
u16 RDA_ReadData(u8 REGADD);
void Rda5820RxMode(void);
void Rda5820TxMode(void);
u8 Rda5820RssiGet(void);
void Rda5820VolSet(u8 vol);
void Rda5820MuteSet(u8 mute);
void Rda5820RssiSet(u8 rssi);
void Rda5820TxPagSet(u8 gain);
void Rda5820TxPgaSet(u8 gain);
void Rda5820BandSet(u8 band);
void Rda5820SpaceSet(u8 spc);
void Rda5820FreqSet(u16 freq);
u16 Rda5820FreqGet(void);
void RdaSeek(void);
void TXpwa(u8 data);
void FM_Gain(void);
u8 RDA_check(void);
uint8_t RDA5820_SetFreq_0(double freq);


#endif
