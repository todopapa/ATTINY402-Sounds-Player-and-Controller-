// 24/07/24 �g���K���͂�UPDI�|�[�g��UPDI�v���O���������Ȃ��s����������̂�
//�g���K���͂�UPDI�|�[�g�iPA0�j����ASCLK�|�[�g�iPA2)�Ƌ��p�ɕύX����B

//#define	SHDBG		//���޸ޏ����o�͂���Ƃ��ɐ錾����
//#define	SHDBG_SOFT	//���޸ޏ��o�͂�UART���Ď�������Ƃ��ɐ錾����
//#define	SHDBG_BPS	115200	//����UART�̂Ƃ����޸ޏ����ްڰĂ�錾����
				//�@(��̫�Ēl��38400bps)
//#define	SHDBS		//���޸ސM�����o�͂���Ƃ��ɐ錾����

#define		SLEEP_EN	//Sleep�@�\����������Ƃ��ɐ錾����


/*
tinyAVR�d�q�ٺްى��t+�����Đ�ver1_2
����͍��̿������

�E���ޯĂ�tiny402(����16MHz�ۯ�)


//==============================================
//��݊�����
//==============================================
W25Q����ݐ�(�W��SPIӰ��)
1:CS
2:DO
3:WP(GND�ɐڑ�)
4:GND
5:DI
6:CLK
7:HOLD(Vcc�ɐڑ�)
8:Vcc

tiny402���߰Ă̊�����(3��SPI) �ύX�O�I���W�i��
1:VDD
2:(PA6)SCK(M25Q��CLK�Ɍq��)/�ضޓ���
3:(PA7)SS(M25Q��CS�Ɍq��)
4:(PA1)Ӱ������o��(���_��)/���޸ޏ��/���޸ސM��/(WO1)�t���o��/(TxD)���޸ޏ��
5:(PA2)MOSI(M25Q��DI�Ɍq��)�MISO(��R�����M25Q��DO�Ɍq��)
6:(PA0)/UPDI
7:(PA3)/(WO0)�����o��
8:GND

tiny402���߰Ă̊�����(3��SPI) YM�ύX��
1:VDD
2:(PA2)SCK(M25Q��CLK�Ɍq��)  /�ضޓ��͂����p�i10k�����o�R���Đڑ����邱�� �j
3:(PA1)SS(M25Q��CS�Ɍq��)
4:(PA6)Ӱ������o��(���_��)/���޸ޏ��/���޸ސM��/(WO1)�t���o��/(TxD)���޸ޏ��
5:(PA7)MOSI(M25Q��DI�Ɍq��)�MISO(��R�����M25Q��DO�Ɍq��)
6:(PA0)/UPDI_SW1���� 
7:(PA3)/(WO0)�����o�́i�ύX�Ȃ��j
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
#define	DBS_BIT		1			//���޸ސM�����ޯ�

//���޸ޏ����߰Ē�`
#define	DBG_PORT	PORTA			//���޸ޏ����߰�
#define	DBG_BIT		1			//���޸ޏ����ޯ�

//PWM���߰Ē�`
#define	PWM_F_PORT	PORTA			//PWM�������߰�
#define	PWM_F_BIT	3			//PWM�������ޯ�
#if BTL>0				//����إ��د�ޥ��ڰ��o�͂̂Ƃ�
#define	PWM_R_PORT	PORTA			//PWM�t�����߰�
#define	PWM_R_BIT	1			//PWM�t�����ޯ�
#endif

//SPI���߰Ē�`
// TINY orgel1_2_0520�@�Ɠ����s���z�ɂ��� �ύX by YM
#define	SPI_SOFT				//SPI���Ď�������
#define SPI3					//3��SPI�Őڑ�����
#define SPI_SCK_PORT	PORTA			//SPI_SCK���߰�
#define SPI_SCK_BIT	2			//SPI_SCK���ޯā@6��2
#define SPI_MOSI_PORT	PORTA			//SPI_MOSI���߰�
#define SPI_MOSI_BIT	7			//SPI_MOSI���ޯ� 2��7
#define SPI_SS_PORT	PORTA			//SPI_SS���߰�
#define SPI_SS_BIT	1			//SPI_SS���ޯā@2��1
#define SPI_MISO_PORT	PORTA			//SPI_MISO���߰�
#define SPI_MISO_BIT	7			//SPI_MISO���ޯ� 2��7

#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
//Ӱ��������߰Ē�` �ύX by YM
#define	MTR_PORT	PORTA			//Ӱ�����߰�
#define	MTR_BIT		6			//Ӱ�����ޯā@1��6
#else					//����إ��د�ޥ��ڰ��o�͂̂Ƃ�
#if VOICE_S==0				//SPI���������Ȃ��Ƃ�
#define	MTR_PORT	PORTA			//Ӱ�����߰�
#define	MTR_BIT		6			//Ӱ�����ޯā@7��6
#endif

#endif

//�ضޓ��͂��߰Ē�` �ύX by YM
#define	TRG_PORT	PORTA			//�ضނ��߰�
//#define	TRG_BIT		0			//�ضނ��ޯā@6��0 �iUPDI�Ƌ��p�j
#define	TRG_BIT		2			//�ضނ��ޯā@0��2 �iSCLK�Ƌ��p�j�ɕύX 240724

#if	PART_N>0
//==============================================
//�ݸ��ް��̲��ޯ��
//==============================================
extern struct SONG_IDX SONG_IDX;		//�Ȳ��ޯ������
static struct SONG_IDX *song_idx=&SONG_IDX;	//�Ȳ��ޯ���ւ��߲��
#endif


#if	VOICE_S>0
//==============================================
//�����ް�(SPI�ׯ��)�̲��ޯ��
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{

#if(1)	//�{�ԗp
	//voice_SISIMAI\W25Q16.hex���g��
//	vos_mac(0x000000,0x04879a,8000)		//sisimai1ch8bit8ksps.wav
//�@//�@�N���X�}�X�\���O�i�t���[�������g�� 16kbps�j0817 �W���O���x���擪�ɏ��Ԃ�ς���
	vos_mac(0x000000,0x2ae280,16000)	//gingle_hade.wav
	vos_mac(0x2ae280,0x0e2835,16000)	//Silent_Night_cover.wav
	vos_mac(0x390ab5,0x1396e5,16000)	//morobito-cover-.wav


#else	//ýėp
	//��è�װţ�̉����ް�(voice_Mirrorna\W25Q16.hex)���g��
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav
#endif
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
#include "../apl_SISIMAI.c"
