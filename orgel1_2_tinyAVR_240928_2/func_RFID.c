//RFIDӼޭ�٢MFRC522��𐧌䂷��̧�ѳ���̴ݼ�ݕ�


//----------------------------------------------
//���ع���݂̒萔��`
//----------------------------------------------
#define	MAX_LEN		9	//�]�����������ް��̍ő咷


//----------------------------------------------
//MFRC522�̴װ���ނ̒�`
//----------------------------------------------
#define	MI_OK		0	//����I��
#define	MI_NOTAG	1	//��ޖ���
#define	MI_ERR		2	//�ُ�I��


//----------------------------------------------
//MFRC522�̺���ނ̒�`
//----------------------------------------------
#define	RC522_IDLE	0x00	//NO action; Cancel the current command
#define	RC522_MEM	0x01	//Store 25 byte into the internal buffer.
#define	RC522_GENID	0x02	//Generates a 10 byte random ID number.
#define	RC522_CALCCRC	0x03	//CRC Calculate or selftest.
#define	RC522_TRANSMIT	0x04	//Transmit data
#define	RC522_NOCMDCH	0x07	//No command change.
#define	RC522_RECEIVE	0x08	//Receive Data
#define	RC522_TRANS	0x0C	//Transmit and receive data,
#define	RC522_AUTHENT	0x0E	//Authentication Key
#define	RC522_SOFTRESET	0x0F	//Reset


//----------------------------------------------
// Mifare_One��ނ̺����
//----------------------------------------------
#define	MF1_REQIDL	0x26	//find the antenna area does not enter hibernation
#define	MF1_REQALL	0x52	//find all the tags antenna area
#define	MF1_ANTICOLL	0x93	//anti-collision
#define	MF1_SELECTTAG	0x93	//selection tag
#define	MF1_AUTHENT1A	0x60	//authentication key A
#define	MF1_AUTHENT1B	0x61	//authentication key B
#define	MF1_READ	0x30	//Read Block
#define	MF1_WRITE	0xA0	//write block
#define	MF1_DECREMENT	0xC0	//debit
#define	MF1_INCREMENT	0xC1	//recharge
#define	MF1_RESTORE	0xC2	//transfer block data to the buffer
#define	MF1_TRANSFER	0xB0	//save the data in the buffer
#define	MF1_HALT	0x50	//Sleep


//----------------------------------------------
//MFRC522��ڼ޽����ڽ�̒�`
//----------------------------------------------
//Page 0:Command and Status
#define	Reserved00	0x00
#define	CommandReg	0x01
#define	CommIEnReg	0x02
#define	DivIEnReg	0x03
#define	CommIrqReg	0x04
#define	DivIrqReg	0x05
#define	ErrorReg	0x06
#define	Status1Reg	0x07
#define	Status2Reg	0x08
#define	FIFODataReg	0x09
#define	FIFOLevelReg	0x0A
#define	WaterLevelReg	0x0B
#define	ControlReg	0x0C
#define	BitFramingReg	0x0D
#define	CollReg		0x0E
#define	Reserved01	0x0F

//Page 1:Command
#define	Reserved10	0x10
#define	ModeReg		0x11
#define	TxModeReg	0x12
#define	RxModeReg	0x13
#define	TxControlReg	0x14
#define	TxAutoReg	0x15
#define	TxSelReg	0x16
#define	RxSelReg	0x17
#define	RxThresholdReg	0x18
#define	DemodReg	0x19
#define	Reserved11	0x1A
#define	Reserved12	0x1B
#define	MifareReg	0x1C
#define	Reserved13	0x1D
#define	Reserved14	0x1E
#define	SerialSpeedReg	0x1F

//Page 2:CFG
#define	Reserved20	0x20
#define	CRCResultRegM	0x21
#define	CRCResultRegL	0x22
#define	Reserved21	0x23
#define	ModWidthReg	0x24
#define	Reserved22	0x25
#define	RFCfgReg	0x26
#define	GsNReg		0x27
#define	CWGsPReg	0x28
#define	ModGsPReg	0x29
#define	TModeReg	0x2A
#define	TPrescalerReg	0x2B
#define	TReloadRegH	0x2C
#define	TReloadRegL	0x2D
#define	TCounterValRegH	0x2E
#define	TCounterValRegL	0x2F

//Page 3:TestRegister
#define	Reserved30	0x30
#define	TestSel1Reg	0x31
#define	TestSel2Reg	0x32
#define	TestPinEnReg	0x33
#define	TestPinValueReg	0x34
#define	TestBusReg	0x35
#define	AutoTestReg	0x36
#define	VersionReg	0x37
#define	AnalogTestReg	0x38
#define	TestDAC1Reg	0x39
#define	TestDAC2Reg	0x3A
#define	TestADCReg	0x3B
#define	Reserved31	0x3C
#define	Reserved32	0x3D
#define	Reserved33	0x3E
#define	Reserved34	0x3F


//----------------------------------------------
//�L���ް��̐錾
//----------------------------------------------
static unsigned char MF_TaskState;		//��������ð�
						//�@�@b7:��ޏ��̗L��/����(0=�����1=�L��)
						//�@�@b6-b0:�ð�ϼݏ��
static unsigned char MF_TagType[2];		//��ނ�����
						//�@�@0x4400=Mifare_UltraLight
						//�@�@0x0400=Mifare_One(S50)
						//�@�@0x0200=Mifare_One(S70)
						//�@�@0x0800=Mifare_Pro(X)
						//�@�@0x4403=Mifare_DESFire
static unsigned char MF_TagSerial[5];		//��ނ̼رٔԍ�
						//�@�@�ŏI�޲Ă�BCC
static unsigned char data[MAX_LEN];		//�]���ް�
static unsigned char len;			//�]���ް���(�S���޲Đ�)
static unsigned char lenb;			//�]���ް���(�ŏI�޲Ă��ޯĐ�)
static unsigned char crc[2];			//CRC�v�Z����
static unsigned char status;			//MFRC522�̽ð��


//----------------------------------------------
//MFRC�߰ı���ϸ�
//----------------------------------------------
#define	MFRC_RST_H	MFRC_RST_PORT.OUTSET=1<<MFRC_RST_BIT
#define	MFRC_RST_L	MFRC_RST_PORT.OUTCLR=1<<MFRC_RST_BIT
#define	MFRC_RST_OUT	MFRC_RST_PORT.DIRSET=1<<MFRC_RST_BIT
#define	MFRC_NSS_H	MFRC_NSS_PORT.OUTSET=1<<MFRC_NSS_BIT
#define	MFRC_NSS_L	MFRC_NSS_PORT.OUTCLR=1<<MFRC_NSS_BIT
#define	MFRC_NSS_OUT	MFRC_NSS_PORT.DIRSET=1<<MFRC_NSS_BIT
#define	MFRC_SCK_H	MFRC_SCK_PORT.OUTSET=1<<MFRC_SCK_BIT
#define	MFRC_SCK_L	MFRC_SCK_PORT.OUTCLR=1<<MFRC_SCK_BIT
#define	MFRC_SCK_OUT	MFRC_SCK_PORT.DIRSET=1<<MFRC_SCK_BIT
#define	MFRC_MOSI_H	MFRC_MOSI_PORT.OUTSET=1<<MFRC_MOSI_BIT
#define	MFRC_MOSI_L	MFRC_MOSI_PORT.OUTCLR=1<<MFRC_MOSI_BIT
#define	MFRC_MOSI_OUT	MFRC_MOSI_PORT.DIRSET=1<<MFRC_MOSI_BIT
#define	MFRC_MISO_R	(MFRC_MISO_PORT.IN&1<<MFRC_MISO_BIT)


//----------------------------------------------
//SPI��1�޲Ă𑗎�M����
//----------------------------------------------
unsigned char MFRC_spi_trans(			//��M�����ް���Ԃ�
	unsigned char data)			//���M�����ް�
{
	unsigned char n; 

//DBG_C('<');
//DBG_B(data);

	for(n=0;n<8;n++)
	{
		if(data&0x80) MFRC_MOSI_H;	//MSB����MOSI��
		else MFRC_MOSI_L;		//�@���f����
		data<<=1;			//�ް�������Ă��Ă���
		MFRC_SCK_H;			//SCK��H
		if(MFRC_MISO_R) data|=1;	//MISO���ް��ɔ��f����
		MFRC_SCK_L;			//SCK��L
	}

//DBG_B(data);
//DBG_C('>');

	return(data);				//��M�ް���Ԃ�
}


//----------------------------------------------
//MFRC522��ڼ޽���Ǎ���
//----------------------------------------------
unsigned char MFRC_read_reg(			//ڼ޽��l��Ԃ�
	unsigned char reg)			//ڼ޽����ڽ
{
	unsigned char value;

//DBG_C('r');
//DBG_B(reg);

	MFRC_NSS_L;				//����ނ��J�n
	MFRC_spi_trans(((reg<<1)&0x7E)|0x80);	//ڼ޽����ڽ�𑗂�
	value=MFRC_spi_trans(0);			//ڼ޽��l�𓾂�
	MFRC_NSS_H;				//����ނ��I��

//DBG_B(value);
//DBG_C('.');

	return(value);				//ڼ޽��l��Ԃ�
}


//----------------------------------------------
//MFRC522��ڼ޽���������
//----------------------------------------------
void MFRC_write_reg(
	unsigned char reg,			//ڼ޽����ڽ
	unsigned char value)			//ڼ޽��ݒ�l
{

//DBG_C('w');
//DBG_B(reg);
//DBG_B(value);

	MFRC_NSS_L;				//����ނ��J�n
	MFRC_spi_trans((reg<<1)&0x7E);		//ڼ޽����ڽ�𑗂�
	MFRC_spi_trans(value);			//ڼ޽��ݒ�l�𑗂�
	MFRC_NSS_H;				//����ނ��I��

//DBG_C('.');

}


//----------------------------------------------
//MFRC522��ڼ޽����ޯľ�Ă���
//----------------------------------------------
void MFRC_set_reg(
	unsigned char reg,			//ڼ޽����ڽ
	unsigned char mask)			//�ޯ�Ͻ�
{
	unsigned char value;

	value=MFRC_read_reg(reg);		//���ݒl��Ǎ���
	value|=mask;				//�ޯľ�Ă���
	MFRC_write_reg(reg,value);		//�����߂�
}


//----------------------------------------------
//MFRC522��ڼ޽����ޯĸر����
//----------------------------------------------
void MFRC_clr_reg(
	unsigned char reg,			//ڼ޽����ڽ
	unsigned char mask)			//�ޯ�Ͻ�
{
	unsigned char value;

	value=MFRC_read_reg(reg);		//���ݒl��Ǎ���
	value&=(~mask);				//�ޯĸر����
	MFRC_write_reg(reg,value);		//�����߂�
}


//----------------------------------------------
//MFRC522�����ް�ޮ݂��擾����
//----------------------------------------------
unsigned char MFRC_get_version(void)
{
	unsigned char value;

	value=MFRC_read_reg(VersionReg);	//�ް�ޮ�ڼ޽���Ǎ���
	return(value);				//�ް�ޮ݂�Ԃ�
}


//----------------------------------------------
//MFRC522������������
//----------------------------------------------
void MFRC_init(void)
{
	unsigned char value;

//DBG_C('i');

	MFRC_write_reg(CommandReg,RC522_SOFTRESET);
						//���ؾ�Ă���
	do
	{
		wait_ms(50);			//50ms�҂�
		value=MFRC_read_reg(CommandReg);//�����ڼ޽����擾����
	}
	while(value&0x10);			//��ܰ�޳��ޯĂ��ر�����܂ő҂�

	MFRC_write_reg(TxModeReg,0x00);		//�ްڰĂ�ؾ��
	MFRC_write_reg(RxModeReg,0x00);
	MFRC_write_reg(ModWidthReg,0x26);	//ModWidth��ؾ��
	MFRC_write_reg(TModeReg,0x80);		//TAuto=1; timer starts automatically at the
						//�@end of the transmission in all
						//�@communication
						//�@modes at all speeds
        MFRC_write_reg(TPrescalerReg,0xA9);	//TPreScaler=TModeReg[3..0]:TPrescalerReg,
						//�@ie 0x0A9 = 169 => f_timer=40kHz,
						//�@ie a timer period of 25��s.
        MFRC_write_reg(TReloadRegH,0x03);	//Reload timer with 0x3E8=1000,
        MFRC_write_reg(TReloadRegL,0xE8);	//�@ie 25ms before timeout.
        MFRC_write_reg(TxAutoReg,0x40);		//Default 0x00.Force a 100%ASK modulation
						//�@independent of the ModGsPReg register
						//�@setting
        MFRC_write_reg(ModeReg,0x3D);		//Default 0x3F.Set the preset value for
						//�@the CRC coprocessor for the CalcCRC
						//�@command to
						//�@0x6363(ISO14443-3 part 6.2.4)
	MFRC_set_reg(TxControlReg,0x03);	//���ł��

//DBG_C('.');
}


//----------------------------------------------
//MFRC522����ނֺ�����ް���]������(�O��)
//
//BjarteJohansen�̂���{�ł͍ŏI���M�ް����ޯĐ����Ăяo�����Őݒ肳���Ă��邪�
//�����ł͑��ϐ��lenb��ň����p������̊֐��ŢBitFramingReg��ɐݒ肷������ɂ���
//----------------------------------------------
void MFRC_trans_tag1(void)
{
	unsigned char n;

//DBG_C('t');
//DBG_B(*data);
//DBG_B(*(data+1));
//DBG_B(len);

	MFRC_write_reg(CommIEnReg,0xf7);	//�����ݐݒ��������
	MFRC_clr_reg(CommIrqReg,0x80);		//�����݋���������
	MFRC_set_reg(FIFOLevelReg,0x80);	//FIFO��ر���Ă���
	MFRC_write_reg(CommandReg,RC522_IDLE);	//�����~���Ă���

	for(n=0;n<len;n++) MFRC_write_reg(FIFODataReg,data[n]);
						//������ް���FIFO�֑���

	MFRC_write_reg(CommandReg,RC522_TRANS);	//������ް��̓]���w��

	MFRC_write_reg(BitFramingReg,lenb|0x80);//�ŏI�޲Ă��ޯĐ���ݒ肵�ē]�����J�n����

//DBG_C('.');

}


//----------------------------------------------
//MFRC522����ނֺ�����ް���]������(�㔼)
//----------------------------------------------
unsigned char MFRC_trans_tag2(void)		//�������ʂ�Ԃ�
						//�@MI_ERR:�ُ�I��
						//�@MI_NOTAG:��ޖ���
						//�@MI_OK:����I��
{
	unsigned char value;
	unsigned char lastBits,n;

//DBG_C('a');

	value=MFRC_read_reg(CommIrqReg);	//���s��Ԃ��擾����

//DBG_B(value);

	MFRC_clr_reg(BitFramingReg,0x80);	//�]�����~�߂�

	if(value&0x31)				//��M���������ޏI�����ѱ�Ă̂����ꂩ�̂Ƃ�
	{
		if(!(MFRC_read_reg(ErrorReg)&0x1D))
						//�ޯ̧�����۰��ؼޮݤCRC����ĺق�
						//�@������̴װ�������Ƃ�
		{
			if(value&0x01) return(MI_NOTAG);
						//��ѱ�Ă̂Ƃ���MI_NOTAG��Ԃ�

			value=MFRC_read_reg(FIFOLevelReg);
						//�����ް����޲Đ��𓾂�

//DBG_B(value);

			lastBits=MFRC_read_reg(ControlReg)&0x07;
						//�ŏI�ް����ޯĐ��𓾂�

//DBG_B(lastBits);

						//�ޯĐ��ɕϊ�����
			if(lastBits) len=(value-1)*8+lastBits;
			else len=value*8;

//DBG_B(len);

			if(value==0) value=1;
			if(value>MAX_LEN) value=MAX_LEN;
						//���e����ő咷�ȓ��ɋK������

//DBG_B(value);

			for(n=0;n<value;n++) data[n]=MFRC_read_reg(FIFODataReg);
						//�����ް�����o��
			return(MI_OK);
		}
		else return(MI_ERR);
	}
	else return(MI_ERR);
}


//----------------------------------------------
//MFRC522��CRC���v�Z����(�O��)
//----------------------------------------------
void MFRC_calculateCRC1(void)
{
	unsigned char n;

//DBG_C('c');
//DBG_B(*data);
//DBG_B(*(data+1));
//DBG_B(len);

	MFRC_clr_reg(DivIrqReg,0x04);		//CRC�v�Z�̊����݂�ر���Ă���
	MFRC_set_reg(FIFOLevelReg,0x80);	//FIFO��ر���Ă���

	for(n=0;n<len;n++) MFRC_write_reg(FIFODataReg,data[n]);
						//������ް���FIFO�֑���

	MFRC_write_reg(CommandReg,RC522_CALCCRC);
						//CRC�v�Z���J�n����

//DBG_C('.');

}


//----------------------------------------------
//MFRC522��CRC���v�Z����(�㔼)
//----------------------------------------------
void MFRC_calculateCRC2(void)
{

//DBG_C('d');

	crc[0]=MFRC_read_reg(CRCResultRegL);	//CRC�v�Z���ʂ�
	crc[1]=MFRC_read_reg(CRCResultRegM);	//�@��o��

//DBG_B(crc[0]);
//DBG_B(crc[1]);
//DBG_C('.');

}


//----------------------------------------------
//MFRC522����ނ���رٔԍ����擾����(�������)
//----------------------------------------------
unsigned char MFRC_TASK(void)			//��ޏ��̗L����Ԃ�(0=�������1=��L��)
{

//DBG_C('+');
//DBG_B(MF_TaskState);

	switch(MF_TaskState&0x7f)		//����ðĂŕ��򂷂�
	{
	case 0:
//��ނ����o����
		data[0]=MF1_REQIDL;		//��ނ����o����
		len=1;				//������ް�����
		lenb=7;				//�@7�ޯ�
		MFRC_trans_tag1();		//������ް���]������
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 1:
		status=MFRC_trans_tag2();	//�����𓾂�
//DBG_B(status);
//DBG_B(len);
		if(len!=16) status=MI_ERR;	//������16�ޯĂłȂ�������װ�Ƃ���
//DBG_B(data[0]);
//DBG_B(data[1]);

		if(status!=MI_OK)		//�װ�̂Ƃ���
		{
			MF_TagSerial[0]=0;	//��ނ̼رٔԍ���ر���Ă���
			MF_TagSerial[1]=0;
			MF_TagSerial[2]=0;
			MF_TagSerial[3]=0;
			MF_TagSerial[4]=0;	//�ŏI�޲Ă�BCC1
			MF_TaskState=0;		//��ޏ��𢖳����ɂ��ĽðĂ��ŏ��ɖ߂�
			break;
		}
		MF_TagType[0]=data[0];		//��ނ����߂�
		MF_TagType[1]=data[1];		//�@�擾����
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 2:
//�ؼޮ݂��������
		data[0]=MF1_ANTICOLL;		//�ؼޮ݉������
		data[1]=0x20;			//�ؼޮ݉���̎w��
		len=2;				//������ް�����2�޲�
		lenb=0;
		MFRC_trans_tag1();		//������ް���]������
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 3:
		status=MFRC_trans_tag2();	//�����𓾂�
//DBG_B(status);
//DBG_B(len);
		if(len!=40) status=MI_ERR;	//������40�ޯĂłȂ�������װ�Ƃ���

		if(!(status==MI_OK))		//�װ�̂Ƃ���
		{
			MF_TaskState=0x08;	//�@��ޏ�񢖳����ɂ��ĽðĂ�HALT�֔�΂�
			break;
		}
//DBG_B(data[0]);
//DBG_B(data[1]);
//DBG_B(data[2]);
//DBG_B(data[3]);
//DBG_B(data[4]);

		if((MF_TagSerial[0]!=data[0])||	//�O�����ނƼرٔԍ����Ⴄ�Ƃ���
			(MF_TagSerial[1]!=data[1])||
			(MF_TagSerial[2]!=data[2])||
			(MF_TagSerial[3]!=data[3]))
		{
			MF_TagSerial[0]=data[0];//�رٔԍ����捞��
			MF_TagSerial[1]=data[1];
			MF_TagSerial[2]=data[2];
			MF_TagSerial[3]=data[3];
			MF_TagSerial[4]=data[4];//�ŏI�޲Ă�BCC1
			MF_TaskState|=0x80;	//��ޏ��L����ɐݒ肷��
			MF_TaskState++;		//�ðĂ�i�߂�
		}
		break;

	case 4:
//��ނ�I������
		data[0]=MF1_SELECTTAG;		//��ނ�I������
		data[1]=0x70;			//��ޑI���̎w��
		data[2]=MF_TagSerial[0];	//�رٔԍ�
		data[3]=MF_TagSerial[1];
		data[4]=MF_TagSerial[2];
		data[5]=MF_TagSerial[3];
		data[6]=MF_TagSerial[4];	//�ŏI�޲Ă�BCC1
		len=7;
		MFRC_calculateCRC1();		//CRC���v�Z����
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 5:
		MFRC_calculateCRC2();		//CRC���擾����
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 6:
		data[7]=crc[0];			//CRC0
		data[8]=crc[1];			//CRC1
		len=9;				//������ް�����9�޲�
		lenb=0;
		MFRC_trans_tag1();		//������ް���]������
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 7:
		MFRC_trans_tag2();		//�����𓾂�
//DBG_B(status);
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 8:
//��ޏ������I������
		data[0]=MF1_HALT;		//��ޏ������I������
		data[1]=0;			//ADR
		len=2;				//������ް�����2�޲�
		lenb=0;
		MFRC_calculateCRC1();
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 9:
		MFRC_calculateCRC2();		//CRC���擾����
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 10:
		data[2]=crc[0];			//CRC0
		data[3]=crc[1];			//CRC1
		len=4;				//������ް�����4�޲�
		lenb=0;
		MFRC_trans_tag1();		//������ް���]������
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 11:
		MFRC_trans_tag2();		//�����𓾂�
		MF_TaskState++;			//�ðĂ�i�߂�
		break;

	case 12:
		MFRC_clr_reg(Status2Reg,0x08);//�Í������
		if(MF_TaskState&0x80)		//��ޏ��g����L����̂Ƃ���
		{
			MF_TaskState=0;		//�ðĂ��ŏ��ɖ߂�
			return(1);		//��ޏ��L�裂�Ԃ�
		}
		else				//��ޏ��g���������̂Ƃ���
		{
			MF_TaskState=0;		//�ðĂ��ŏ��ɖ߂�
			break;		//��ޏ�񢖳�����Ԃ�
		}
	}
	return(0);
}
