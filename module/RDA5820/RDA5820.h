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
//bit0 ENABLE оƬ�ϵ�1 оƬ���ϵ�0
//bit1 SOFTRESET оƬ��λ1 ����λ0
//bit2 ANTENNA 1ʹ���ڲ�С���� 0ʹ���������ⲿ����(�ڲ�С�����ٶ����ܶ�)
//bit6-bit4 ʱ��Ƶ��ѡ��,����ʵ��Ƶ��ѡ�� 000 32.768khz
// bit7 SKMODE 0ѭ������ 1�������߻�������ʱֹͣ����
//bit8 SEEK 0�����Ѿ�ֹͣ 1������ʼ
//bit9 �������� 0���� 1����
//bit12 BASS 0��ʹ�ܵ�����ǿ 1ʹ�ܵ�����ǿ
//bit13 MONO ����ѡ�� 0������ 1��������
//bit14 DMUTE ����ѡ�� 0���� 1�Ǿ���
//bit15 DHIZ ��Ƶ������迹ѡ�� 0ѡ����迹 1��ѡ����迹
#define Register2 	0x03
//bit15-6 ��ǰƵ��,ͨ��baud���Լ��㵱ǰƵ��
//bit4 ��г 0�رյ�г 1������г
//bit3-2 baud Ƶ��ѡ�� ����ѡ��
//bit1-0 ����ѡ�� 00Ϊ100K
#define Register3 	0x04
//STCIEN[14](��������ж�),DE[11],I2S_ENABLE[6],GPIO3~1[5:0]
//bit14 1������г��Ƶ�ж� 0�ر��ж� �ж�������ʾ��GPIO2��
//bit11 ȥ����ʱ��ѡ�� 0 75us 1 50us
//bit6 i2sʹ�� 0��ʹ�� 1ʹ��
//bit5-bit0 ����GPIO�Ĺ���ѡ�� ���鶼��00

#define Register4 	0x05
//INT_MODE[15],SEEKTH[14:8](�趨�ź�ǿ��),LNA_PORT_SEL[7:6],LNA_ICSEL_BIT[5:4],VOLUME[3:0];
//bit15 �ж�ģʽ 0��ʱ���ж� 1ֱ�����0c��ȡ���ж�
//bit14-8 ������ֵ �������ֵ��Ϊ����Ч̨
//bit7-6 ����������Ŵ�ģʽ 00������
//bit5-4 ������������� 00 1.8ma
//bit3-0 ���� 0000���1111���
#define Register5	 0x06
#define Register6 	0x07
#define Register7 	0x0A
//STC[14](������ɱ�־),SF[13](����ʧ�ܱ�־),ST[10] (��������־),READCHAN[9:0](Ƶ��).
//bit14 ��̨��ɱ�־ 0δ��� 1���
//bit13 ��̨ʧ�ܱ�־ 0�ɹ� 1ʧ��
//bit10 ������ָʾ 0������ 1������
//bit9-bit0 ��ǰƵ��ָʾ,���Լ������ǰƵ��
#define Register8	 0x0B
//RSSI[15:9](�ź�ǿ��),FM_TRUE[8](վ���־),FM_READY[7](fm������־)
//bit15-9 ��ǰ�ź�ǿ��
//bit8 1��ǰƵ����һ����Ч̨ 0����
//bit7 1 �Ѿ�׼���������̨ 0û׼����
#define Register9	 0x0C

#define Register10	 0x0D
//AUTO_SEEK[15](ȫ/���Զ���̨),CHAN_SCAN[14](�ѿ�/æ̨),CHIP_FUN[3:0](����ģʽ)
//bit15 1ȫ�Զ���̨ 0�ֶ���̨
//bit14 ΪFM��������һ������Ƶ��
//bit3-0 ѡ����ģʽ 0000 rxģʽ
#define Register11 	0x0E
#define Register12 	0x0F
#define Register13 	0x40//WORK MODE
#define Register14	 0x41
 //MEM_CLR[15](�ڴ����),RPT_TIME[14:9](RDSӦ�����),MEM_DEPTH[8:0](FIFO��С,���256)
//bit15 1��λfifo 0����λ
//bit14-9 ����������RDSӦ�����
//bit8-0 fifo����� 0-256
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
