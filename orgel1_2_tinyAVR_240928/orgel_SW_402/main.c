//#define	SHDBG		//���޸ޏ����o�͂���Ƃ��ɐ錾����
//#define	SHDBG_SOFT	//���޸ޏ��o�͂�UART���Ď�������Ƃ��ɐ錾����
//#define	SHDBG_BPS	115200	//����UART�̂Ƃ����޸ޏ����ްڰĂ�錾����
				//�@(��̫�Ēl��38400bps)
//#define	SHDBS		//���޸ސM�����o�͂���Ƃ��ɐ錾����

//#define	SPI2		//2��SPI�̂Ƃ��ɐ錾����
				//�@�錾���Ȃ��Ƃ���3��SPI�ƂȂ�
#define		SLEEP_EN	//Sleep�@�\����������Ƃ��ɐ錾����
//#define	SHAUTO			//�����J�n����Ƃ��ɐ錾����
//#define	KYOKU_RAND	//�Ȕԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEIN_RAND	//����N�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEII_RAND	//����I�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEIC_RAND	//����C�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEIS_RAND	//����S�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
#define	SW_EN		//SW����������Ƃ��ɐ錾����
//#define	TRG_EN			 //�g���K���͂���������Ƃ��ɐ錾����
//#define	CdS_EN		//CdS����������Ƃ��ɐ錾����
//#define	CVD_EN		//CVD����������Ƃ��ɐ錾����
//#define	CVD_EXPU	//CVD���O����ٱ���(100k������)����Ƃ��ɐ錾����


//�ٺްٔ��ւ̉��p�ł͈ȉ���錾���Ă�������
//#define	CdS_FUTA	//�W���J����(��)�Ƶݔ��肷��
//#define	CdS_THR	100	//����臒l���Œ�̐錾�l�ɂ���


/*
tinyAVR�d�q�ٺްى��t+�����Đ�ver1_2
����͍��̿������

�E���ޯĂ�tiny402(����16MHz�ۯ�)

�ESW��CVD�����킹��3�܂Ŏ����\��������̱��ع���݂ł͂��ꂼ��1��
�@�g���Ă���

�ESW���߰�-GND�Ԃɐݒu������_��(����=L)�œ��͂���
�ESW�̒Z�݂�׳������݂ɋȂ����t�J�n��������Đ��J�n����
�ESW�̒��݂ŉ��t���f��Đ����f����

�ECVD��CVD�߯���߰Ă���10k���̒�R������߰Ăɓ��͂���
�@10k�����߰ĕی�̂��߂ł��褕K�{�ł͂Ȃ��
�ECVD�̒ZCVD��׳������݂ɋȂ����t�J�n��������Đ��J�n����
�ECVD�̒�CVD�ŉ��t���f��Đ����f����

�ECdS��1�̂ݎ������Ă���
�ECdS���߰�-GND�Ԃɐݒu������_��(��=H)�œ��͂���
�ECdS�̒Z�݂�׳������݂ɋȂ����t�J�n��������Đ��J�n����
�ECdS�̒��݂ŉ��t���f��Đ����f����

�ESHAUTO��錾���邱�ƂŤ�����I�ɋȂ����t�J�n��y�щ������Đ��J�n����
�E�����ް�����۸����ׯ���I2C�ׯ���SD���ޤSPI�ׯ���̉��ꂩ�Ɋi�[���Ă����


//==============================================
//�O������؂��g��Ȃ��Ƃ�
//==============================================
tiny402���߰Ă̊�����
1:VDD
2:(PA6)SW1/���޸ޏ��/���޸ސM��/(AIN6)CdS/(AIN6)CVD0/(TxD)���޸ޏ��
3:(PA7)SW2/(AIN7)CVD1
4:(PA1)/(WO1)�t���o��
5:(PA2)SW3/(AIN2)CVD2
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)�����o��
8:GND


//==============================================
//I2C�ׯ����؂��g���Ƃ�
//==============================================
24FC����ݐ�
���1:A0(Vss�Ɍq��)
���2:A1(Vss�Ɍq��)
���3:A2(Vss�Ɍq��)
���4:Vss
���5:SDA(1.5k�ŊO����ٱ���)
���6:SCL(1.5k�ŊO����ٱ���)
���7:WP(Vcc�Ɍq��)
���8:Vcc

tiny402���߰Ă̊�����
1:VDD
2:(PA6)SW1/���޸ޏ��/���޸ސM��/(AIN6)CdS/(AIN6)CVD0/(TxD)���޸ޏ��
3:(PA7)SDA
4:(PA1)/(WO1)�t���o��
5:(PA2)SCL
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)�����o��
8:GND


//==============================================
//SD���ނ��g���Ƃ�
//==============================================
SD���޽ۯĂ���ݐ�(SPIӰ��)
9:��(�s�g�p)
1:CS(2��SPI�ł͎��萔��H�����CLK�Ɍq��)
2:DI
3:Vss1
4:Vdd
5:CLK
6:Vss2
7:DO(��R�����DI�Ɍq��)
8:IRQ(�s�g�p)

tiny402���߰Ă̊�����(3��SPI)
1:VDD
2:(PA6)SW1/���޸ޏ��/���޸ސM��/(AIN6)CdS/(AIN6)CVD0/(TxD)���޸ޏ��
3:(PA7)MOSI(SDC��DI�Ɍq��)
4:(PA1)SS(SDC��CS�Ɍq��)/(WO1)�t���o��
5:(PA2)SCK(SDC��CLK�Ɍq��)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)�����o��
8:GND

tiny402���߰Ă̊�����(2��SPI)
1:VDD
2:(PA6)SW1/���޸ޏ��/���޸ސM��/(AIN6)CdS/(AIN6)CVD0/(TxD)���޸ޏ��
3:(PA7)MOSI(SDC��DI�Ɍq��)
4:(PA1)/(WO1)�t���o��
5:(PA2)SCK(SDC��CLK�Ɍq��)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)�����o��
8:GND


//==============================================
//SPI�ׯ����؂��g���Ƃ�
//==============================================
W25Q����ݐ�(�W��SPIӰ��)
1:CS(2��SPI�ł͎��萔��H�����CLK�Ɍq��)
2:DO(2��SPI�3��SPI�ł͒�R�����DI�Ɍq��)
3:WP(GND�ɐڑ�)
4:GND
5:DI
6:CLK
7:HOLD(Vcc�ɐڑ�)
8:Vcc

tiny402���߰Ă̊�����(3��SPI)
1:VDD
2:(PA6)SW1/���޸ޏ��/���޸ސM��/(AIN6)CdS/(AIN6)CVD0/(TxD)���޸ޏ��
3:(PA7)MOSI(M25Q��DI�Ɍq��)
4:(PA1)SS(M25Q��CS�Ɍq��)/(WO1)�t���o��
5:(PA2)SCK(M25Q��CLK�Ɍq��)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)�����o��
8:GND

tiny402���߰Ă̊�����(2��SPI)
1:VDD
2:(PA6)SW1/���޸ޏ��/���޸ސM��/(AIN6)CdS/(AIN6)CVD0/(TxD)���޸ޏ��
3:(PA7)MOSI(M25Q��DI�Ɍq��)
4:(PA1)/(WO1)�t���o��
5:(PA2)SCK(M25Q��CLK�Ɍq��)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)�����o��
8:GND

tiny402���߰Ă̊�����(3��SPI) 240928 YM
1:VDD
2:(PA6)MOTOR_ON�M��/(TxD)���޸ޏ��
3:(PA7)MOSI�o��(M25Q��DI�Ɍq��)/MISO(10k�����M25Q��DO�Ɍq��)
4:(PA1)SS�o��(M25Q��CS�Ɍq��)
5:(PA2)SCK�o��(M25Q��CLK�Ɍq��)/SW2���́i�s�G�]�M���j
6:(PA0)SW0����/UPDI�v���O�����M�����o��
7:(PA3)/(WO0)�����o�� PWM_P
8:GND

*/


//==============================================
//ͯ��̧�ق̌č���
//==============================================
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "../port_tn.h"				//I/Oport�̏����struct��`
#include "orgel_cnf.h"				//�ٺްى��t�����Ɖ����Đ��̍\�����č���
#include "../orgel.h"				//���؂�ͯ��̧��


//==============================================
//�\�����(���ع���݂����ޯ����޲��Ɋւ�����)
//==============================================
//���޸ސM�����߰Ē�`
#define	DBS_PORT	PORTA			//���޸ސM�����߰�
#define	DBS_BIT		6			//���޸ސM�����ޯ�

//���޸ޏ����߰Ē�`
#define	DBG_PORT	PORTA			//���޸ޏ����߰�
#define	DBG_BIT		6			//���޸ޏ����ޯ�

//PWM���߰Ē�`
#define	PWM_F_PORT	PORTA			//PWM�������߰�
#define	PWM_F_BIT	3			//PWM�������ޯ�
#define	PWM_R_PORT	PORTA			//PWM�t�����߰�
#define	PWM_R_BIT	1			//PWM�t�����ޯ�

//I2C���߰Ē�`
#define	I2C_SOFT			//I2C���Ď�������
#define I2C_SCL_PORT	PORTA			//I2C_SCL���߰�
#define I2C_SCL_BIT	2			//I2C_SCL���ޯ�
#define I2C_SDA_PORT	PORTA			//I2C_SDA���߰�
#define I2C_SDA_BIT	7			//I2C_SDA���ޯ�

//SPI���߰Ē�`
#define	SPI_SOFT				//SPI���Ď�������
#define SPI_SCK_PORT	PORTA			//SPI_SCK���߰�
#define SPI_SCK_BIT	2			//SPI_SCK���ޯ�
#define SPI_MOSI_PORT	PORTA			//SPI_MOSI���߰�
#define SPI_MOSI_BIT	7			//SPI_MOSI���ޯ�
#ifdef SPI2				//2��SPI�̂Ƃ�
#define	SS_WAIT_TIME	50			//SSȹްđ҂�����[us]
#define SPI_SS_PORT	PORTA			//SPI_SS���߰�
#define SPI_SS_BIT	2			//SPI_SS���ޯ�
#else					//3��SPI�̂Ƃ�
#define	SPI3					//3��SPI�Őڑ�����
#define SPI_SS_PORT	PORTA			//SPI_SS���߰�
#define SPI_SS_BIT	1			//SPI_SS���ޯ�
#endif
#define SPI_MISO_PORT	PORTA			//SPI_MISO���߰�
#define SPI_MISO_BIT	7			//SPI_MISO���ޯ�

//LED���߰Ē�`
#if(0)
#ifndef RFID_EN				//RFID���������Ȃ��Ƃ�
#define	LED0_PORT	PORTC			//LED0���߰�
#define	LED0_BIT	0			//LED0���ޯ�
#define	LED1_PORT	PORTD			//LED1���߰�
#define	LED1_BIT	2			//LED1���ޯ�
#define	LED2_PORT	PORTD			//LED2���߰�
#define	LED2_BIT	3			//LED2���ޯ�
#define	LED3_PORT	PORTC			//LED3���߰�
#define	LED3_BIT	2			//LED3���ޯ�
#endif
#endif

//SW���߰Ē�`
#define	SW0_PORT	PORTA		//SW0���߰�
#define	SW0_BIT		0			//SW0���ޯāiPA0 UPDI)
#define	SW0_INV					//SW0���͕͂��_��
					//�ȉ�����ϰӰ�ނ�ر�Ӱ�ނ͑���
#define SW0_TIMER				//SW0����ϰӰ��
//#define	SW0_REAL			//SW0��ر�Ӱ��

//�ضޓ��͂��߰Ē�`
#define	TRG_PORT	PORTA		//�ضނ��߰�
#define	TRG_BIT		0			//�ضނ��ޯāiPA0 UPDI)

//CdS���߰Ē�`
#define	CdS_PORT	PORTA			//CdS���߰�
#define	CdS_BIT		6			//CdS���ޯ�
#define	CdS_AIN		6			//CdS��AIN
//#define	CdS_INV				//CdS���͕͂��_��(��=L)
					//�ȉ�����ϰӰ�ނ�ر�Ӱ�ނ͑���
#define CdS_TIMER				//CdS����ϰӰ��
//#define	CdS_REAL			//CdS��ر�Ӱ��
//#define	CdS_THR		100		//CdS�]���̌Œ�臒l[1/256]
//#define	CdS_FUTA			//CdS���蔽�](��=��)

//CVD���߰Ē�`
#define	CVD0_PORT	PORTA			//CVD0���߰�
#define	CVD0_BIT	6			//CVD0���ޯ�
#define	CVD0_AIN	6			//CVD0��AIN
					//�ȉ�����ϰӰ�ނ�ر�Ӱ�ނ͑���
#define CVD0_TIMER				//CVD0����ϰӰ��
//#define	CVD0_REAL			//CVD0��ر�Ӱ��

//MFRC���߰Ē�`
#define MFRC_RST_PORT		PORTD		//RC522_RST���߰�
#define MFRC_RST_BIT		7		//RC522_RST���ޯ�
#define MFRC_SCK_PORT		PORTC		//RC522_SCK���߰�
#define MFRC_SCK_BIT		0		//RC522_SCK���ޯ�
#define MFRC_NSS_PORT		PORTC		//RC522_NSS���߰�
#define MFRC_NSS_BIT		2		//RC522_NSS���ޯ�
#define MFRC_MOSI_PORT		PORTD		//RC522_MOSI���߰�
#define MFRC_MOSI_BIT		2		//RC522_MOSI���ޯ�
#define MFRC_MISO_PORT		PORTD		//RC522_MISO���߰�
#define MFRC_MISO_BIT		3		//RC522_MISO���ޯ�


//���[�^����ǉ��@24/05/23�@YM
#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
//Ӱ��������߰Ē�`
#define	MTR_PORT	PORTA			//Ӱ�����߰�
#define	MTR_BIT		6			//Ӱ�����ޯ� PA1��PA6
#else					//����إ��د�ޥ��ڰ��o�͂̂Ƃ�
#if VOICE_S==0				//SPI���������Ȃ��Ƃ�
#define	MTR_PORT	PORTA			//Ӱ�����߰�
#define	MTR_BIT		7			//Ӱ�����ޯ� �iSPI��MOMIbit�ɐݒ�j
#endif
#endif


#if	PART_N>0
//==============================================
//�ݸ��ް��̲��ޯ��
//==============================================
extern struct SONG_IDX SONG_IDX;		//�Ȳ��ޯ������
static struct SONG_IDX *song_idx=&SONG_IDX;	//�Ȳ��ޯ���ւ��߲��
#endif


#if	VOICE_N>0
//==============================================
//�����ް�
//==============================================
#include	"../voice_WAN.c"
#include	"../voice_DAME.c"
//#include	"../voice_CHIKO.c"


//==============================================
//�����ް�(��۸����ׯ��)�̲��ޯ��
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_WAN,sizeof(voice_WAN),8000)
	von_mac(voice_DAME,sizeof(voice_DAME),8000)
//	von_mac(voice_CHIKO,sizeof(voice_CHIKO),8000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


#if	VOICE_I>0
//==============================================
//�����ް�(I2C�ׯ��)�̲��ޯ��
//==============================================
static const struct VOICEI_HDR voiceI_idx[]=
{

	//��è�װţ�̉����ް�(Mirrorna_24FC512.X��Mirrorna_24FC512.X)���g��
	voi_mac(0x0000,0x4B88,8000,0xa0)	//KIRAKIRAOMEME
	voi_mac(0x4B88,0x1B8A,8000,0xa0)	//AIDORUMITAI
	voi_mac(0x6712,0x30B0,8000,0xa0)	//KYOUNOOSHARE
	voi_mac(0x97C2,0x2076,8000,0xa0)	//EGAOGASUTEKI
	voi_mac(0xB838,0x3626,8000,0xa0)	//KIRARIN

};
#define VOICEI_SU	(sizeof(voiceI_idx)/sizeof(voiceI_idx[0]))
#endif


#if	VOICE_C>0
//==============================================
//�����ް�(SD����)�̲��ޯ��
//==============================================
static const struct VOICEC_HDR voiceC_idx[]=
{

	//�������ݼ����̉����ް�(SD��ANPANMAN.wav)���g��
	voc_mac(0x00029e,0x00e367,8000)		//anpan
	voc_mac(0x002000,0x000080,8000)		//anpan�̈ꕔ(ýėp)
	voc_mac(0x004000,0x000080,8000)		//anpan�̈ꕔ(ýėp)

};
#define VOICEC_SU	(sizeof(voiceC_idx)/sizeof(voiceC_idx[0]))
#endif


#if	VOICE_S>0
//==============================================
//�����ް�(SPI�ׯ��)�̲��ޯ��
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{
	//voice_ToyStory\W25Q16_12ksps8bit.hex���g��
//	vos_mac(0x000000,0x0afc83,12000)	//ToyStory_12ksps8bit
/*�@���������R�����g�A�E�g���Ă���
	//��è�װţ�̉����ް�(voice_Mirrorna\W25Q16.hex)���g��
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav
*/
//�@�N���X�}�X�\���O�i�t���[�������g�� 16kbps�j
vos_mac(0x000000,0x0e2835,16000)	//Silent_Night_cover.wav
vos_mac(0x0e2835,0x2ae280,16000)	//gingle_hade.wav
vos_mac(0x390ab5,0x1396e5,16000)	//morobito-cover-.wav

// �e���g���̃T�C���g�̉����f�[�^
/*
		vos_mac(0x000000,0x075300,16000)	//wav\1_1khz-0db-30sec#.wav
		vos_mac(0x075300,0x075300,16000)	//wav\2_400hz-0db-30sec#.wav
		vos_mac(0x0ea600,0x04e200,16000)	//wav\3_100hz-6db-20sec#.wav
		vos_mac(0x138800,0x04e200,16000)	//wav\4_400hz-6db-20sec#.wav
		vos_mac(0x186a00,0x04e200,16000)	//wav\5_1khz-6db-20sec#.wav
		vos_mac(0x1d4c00,0x04e200,16000)	//wav\6_2khz-6db-20sec#.wav
		vos_mac(0x222e00,0x04e200,16000)	//wav\7_5khz-6db-20sec#.wav
*/
//�@�A���p���}���L�[�{�[�h�̉����f�[�^�i�f���������g�� 8kbps�j
/*
	vos_mac(0x000000,0x14d32a,8000)	//wav\demo_all_1.wav
	vos_mac(0x14d32a,0x14c802,8000)	//wav\demo_all_2.wav
	vos_mac(0x299b2c,0x1030e2,8000)	//wav\demo_all_3.wav
	vos_mac(0x39cc0e,0x03d18e,8000)	//wav\demo_all_4.wav
	vos_mac(0x3d9d9c,0x07d1d2,8000)	//wav\demo_all_5.wav
*/
// TRUTH�ŉ����̃e�X�g
 //   vos_mac	(0x000000,0x3d9f28,16000)  //TRUTH.wav
};

#define VOICES_SU	(sizeof(voiceS_idx)/sizeof(voiceS_idx[0]))
#endif


//==============================================
//���ʺ��ނ̌č���
//==============================================
#include "../common.c"				//���ʺ��ނ��č���
#include "../orgel.c"				//orgel�ݼ�݂��č���


//==============================================
//���޲��ˑ����̌č���
//==============================================
#include "../dev_xxx.c"				//tinyAVR


//==============================================
//���ع���݈ˑ����̌č���
//==============================================
#include "../apl_SW.c"
