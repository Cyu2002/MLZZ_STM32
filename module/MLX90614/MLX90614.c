#include "mlx90614.h"


/*******************************************************************************
* ������: MLX90614  Ӳ��GPIO��ʼ��
* ����  : MLX90614 ���GPIO�˿ڳ�ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MLX90614_Init( void ) {

    SMBUS_SCK_H;
    SMBUS_SDA_H;
}

/*******************************************************************************
* ������: MLX90614 ����ʼλ SMBus_StartBit
* ����  : MLX90614 ����ʼλ ������ʼλ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SMBus_StartBit( void ) {
    
    SMBUS_SDA_H;
    delay_us(5);
    SMBUS_SCK_H;     
    delay_us(5);
    SMBUS_SDA_L;       
    delay_us(5);
    SMBUS_SCK_L;    
    delay_us(5);
}

/*******************************************************************************
* ������: SMBus_StopBit
* ����: MLX90614 ��ֹͣλ STOP condition on SMBus
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SMBus_StopBit( void ) {
   
	//SMBUS_SDA_OUTPUT();
    SMBUS_SCK_L;        // Clear SCL line
    delay_us(5);   // Wait a few microseconds
    SMBUS_SDA_L;        // Clear SDA line
    delay_us(5);   // Wait a few microseconds
    SMBUS_SCK_H;        // Set SCL line
    delay_us(5);   // Stop condition setup time(Tsu:sto=4.0us min)
    SMBUS_SDA_H;        // Set SDA line
}

/*******************************************************************************
* ������: SMBus_SendByte
* ����: MLX90614 ����һ���ֽ� Send a byte on SMBus
* Input          : Tx_buffer
* Output         : None
* Return         : None
*******************************************************************************/
unsigned char SMBus_SendByte( unsigned char Tx_buffer ) {
    unsigned char   Bit_counter;
    unsigned char   Ack_bit;
    unsigned char   bit_out;
    for( Bit_counter=8; Bit_counter; Bit_counter-- ) {
        if( Tx_buffer&0x80 ) { //������λΪ1
            bit_out=1;   // �����λ��1
        } else { //������λΪ0
            bit_out=0;  // �����λ��0
        }
        SMBus_SendBit( bit_out ); // �����λ���ͳ�ȥ
        Tx_buffer<<=1;// ����һλ�����λ�Ƴ�ȥ�ȴ���һ�����λ��ѭ��8�Σ�ÿ�ζ������λ���Ϳɰ�һ���ֽڷ���ȥ��
    }
    Ack_bit=SMBus_ReceiveBit();
    return  Ack_bit;
}

/*******************************************************************************
* ������: SMBus_SendBit
* ����: MLX90614 ����һ��λ Send a bit on SMBus 82.5kHz
* Input          : bit_out
* Output         : None
* Return         : None
*******************************************************************************/
void SMBus_SendBit( unsigned char bit_out ) {
    //SMBUS_SDA_OUTPUT();
    if( bit_out==0 ) {
        SMBUS_SDA_L;
    } else {
        SMBUS_SDA_H;
    }
    delay_us(2);
    SMBUS_SCK_H;                    // Set SCL line
    delay_us(6);
    SMBUS_SCK_L;                    // Clear SCL line
    delay_us(3);
    return;
}

/*******************************************************************************
* Function Name  : SMBus_ReceiveBit
* Description    : Receive a bit on SMBus
* Input          : None
* Output         : None
* Return         : Ack_bit
*******************************************************************************/
unsigned char SMBus_ReceiveBit( void ) {
    unsigned char Ack_bit;
    SMBUS_SDA_H;          //���ſ��ⲿ������������������
	
	SMBUS_SDA_INPUT();
    delay_us(2);
    SMBUS_SCK_H;            // Set SCL line
    delay_us(5);
    if( SMBUS_SDA_PIN ) {
        Ack_bit=1;
    } else {
        Ack_bit=0;
    }
    SMBUS_SCK_L;            // Clear SCL line
    delay_us(3);
    return  Ack_bit;
}

/*******************************************************************************
* ������: SMBus_ReceiveByte
* ����: Receive a byte on SMBus ��SMBus�н���һ���ֽڵ�����
* Input          : ack_nack
* Output         : None
* Return         : RX_buffer
*******************************************************************************/
unsigned char SMBus_ReceiveByte( unsigned char ack_nack ) {
    unsigned char   RX_buffer;
    unsigned char   Bit_Counter;
    for( Bit_Counter=8; Bit_Counter; Bit_Counter-- ) {
        if( SMBus_ReceiveBit() ) { // Get a bit from the SDA line
            RX_buffer <<= 1;// If the bit is HIGH save 1  in RX_buffer
            RX_buffer |=0x01;//���Ack_bit=1�����յ�Ӧ���ź�1��0000 0001 ���л����㣬ȷ��Ϊ1
        } else {
            RX_buffer <<= 1;// If the bit is LOW save 0 in RX_buffer
            RX_buffer &=0xfe;//���Ack_bit=1�����յ�Ӧ���ź�0��1111 1110 ���������㣬ȷ��Ϊ0
        }
    }
    SMBus_SendBit( ack_nack ); // Sends acknowledgment bit ��Ӧ���źŷ���ȥ�����1���ͽ�����һ��ͨ�ţ����Ϊ0�����Ͱݰ���
    return RX_buffer;
}

/*******************************************************************************
* ������: SMBus_Delay
* ����: ��ʱ  һ��ѭ��Լ1us
* Input          : time
* Output         : None
* Return         : None
*******************************************************************************/
/*void SMBus_Delay( unsigned int time ) {
    //   unsigned int i, j;
    unsigned  j;
    //    for (i=0; i<4; i++)
    //    {
    //        for (j=0; j<time; j++);
    //    }
    for( j=0; j<time; j++ ) {
        _nop_();
        _nop_();//_nop_();_nop_();
    }
    //while(time--);
    //  _nop_();
    //  _nop_();_nop_();
}*/

/*******************************************************************************
* ������: SMBus_Init
* ����: SMBus��ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MLX90614_SMBus_Init( void ) {
    MLX90614_Init();
}

/*******************************************************************************
 * ������: SMBus_ReadMemory
 * ����: READ _data FROM RAM/EEPROM  ��RAM��EEPROM�ж�ȡ����
 * Input          : slaveAddress, command
 * Return         : _data
 * SMBus_ReadMemory(0x00, 0x07) 0x00 ��ʾIIC�豸�Ĵӵ�ַ ��0x07����Ĵ�����ʼ��ȡ
*******************************************************************************/
unsigned int SMBus_ReadMemory( unsigned char slaveAddress, unsigned char command ) {
    unsigned short _data;         // _data storage (_dataH:_dataL)
    unsigned char Pec;              // PEC byte storage
    unsigned char _dataL=0;         // Low _data byte storage
    unsigned char _dataH=0;         // High _data byte storage
    unsigned char arr[6];           // Buffer for the sent bytes
    unsigned char PecReg;           // Calculated PEC byte storage
    unsigned char ErrorCounter; // Defines the number of the attempts for communication with MLX90614
    ErrorCounter=0x00;  // Initialising of ErrorCounter
    slaveAddress <<= 1; //2-7λ��ʾ�ӻ���ַ �ӻ���ַ����һλ���Ѷ�дλ�ճ���
    do {
repeat:
        SMBus_StopBit();                //If slave send NACK stop comunication
        --ErrorCounter;                 //Pre-decrement ErrorCounter
        if( !ErrorCounter ) {           //ErrorCounter=0?
            break;                      //Yes,go out from do-while{}
        }
        SMBus_StartBit();               //Start condition
        if( SMBus_SendByte( slaveAddress ) ) { //Send SlaveAddress ���λWr=0��ʾ������д����
            goto    repeat;             //Repeat comunication again
        }
        if( SMBus_SendByte( command ) ) { //Send command
            goto    repeat;             //Repeat comunication again
        }
        SMBus_StartBit();                   //Repeated Start condition
        if( SMBus_SendByte( slaveAddress+1 ) ) { //Send SlaveAddress ���λRd=1��ʾ������������
            goto    repeat;                 //Repeat comunication again
        }
        _dataL = SMBus_ReceiveByte( ACK );  //Read low _data,master must send ACK
        _dataH = SMBus_ReceiveByte( ACK ); //Read high _data,master must send ACK
        Pec = SMBus_ReceiveByte( NACK ); //Read PEC byte, master must send NACK
        SMBus_StopBit();                //Stop condition
        arr[5] = slaveAddress;      //
        arr[4] = command;           //
        arr[3] = slaveAddress+1;    //Load array arr
        arr[2] = _dataL;                //
        arr[1] = _dataH;                //
        arr[0] = 0;                 //
        PecReg=PEC_Calculation( arr ); //Calculate CRC ����У��
    } while( PecReg != Pec ); //If received and calculated CRC are equal go out from do-while{}
    _data = ( _dataH<<8 ) | _dataL; //_data=_dataH:_dataL
	
	//return 15500;
    return _data;
}

/*******************************************************************************
* ������: PEC_calculation
* ���� : ����У��
* Input          : pec[]
* Output         : None
* Return         : pec[0]-this byte contains calculated crc value
*******************************************************************************/
unsigned char PEC_Calculation( unsigned char pec[] ) {
    unsigned char   crc[6];//��Ŷ���ʽ
    unsigned char   BitPosition=47;//��������������λ��6*8=48 ���λ����47λ
    unsigned char   shift;
    unsigned char   i;
    unsigned char   j;
    unsigned char   temp;
    do {
        /*Load pattern value 0x00 00 00 00 01 07*/
        crc[5]=0;
        crc[4]=0;
        crc[3]=0;
        crc[2]=0;
        crc[1]=0x01;
        crc[0]=0x07;
        /*Set maximum bit position at 47 ( six bytes byte5...byte0,MSbit=47)*/
        BitPosition=47;
        /*Set shift position at 0*/
        shift=0;
        /*Find first "1" in the transmited message beginning from the MSByte byte5*/
        i=5;
        j=0;
        while( ( pec[i]&( 0x80>>j ) )==0 && i>0 ) {
            BitPosition--;
            if( j<7 ) {
                j++;
            } else {
                j=0x00;
                i--;
            }
        }/*End of while */
        /*Get shift value for pattern value*/
        shift=BitPosition-8;
        /*Shift pattern value */
        while( shift ) {
            for( i=5; i<0xFF; i-- ) {
                if( ( crc[i-1]&0x80 ) && ( i>0 ) ) {
                    temp=1;
                } else {
                    temp=0;
                }
                crc[i]<<=1;
                crc[i]+=temp;
            }/*End of for*/
            shift--;
        }/*End of while*/
        /*Exclusive OR between pec and crc*/
        for( i=0; i<=5; i++ ) {
            pec[i] ^=crc[i];
        }/*End of for*/
    } while( BitPosition>8 ); /*End of do-while*/
    return pec[0];
}

/*******************************************************************************
* ������: SMBus_ReadTemp
* ����: ���㲢�����¶�ֵ
* Return         : SMBus_ReadMemory(0x00, 0x07)*0.02-273.15
*******************************************************************************/
float SMBus_ReadTemp( void ) {
    float temp;
    temp = ( SMBus_ReadMemory( SA,RAM_ACCESS|RAM_TOBJ1 )*0.02-273.15 );
    return temp;
}
