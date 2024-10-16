//SW�CdS�CVD��CH32V003�d�q�ٺްق𐧌䂷����ع���݂̋��ʋ@�\��
//SW�CdS�CVD�ͤ���̻���قł͂��ꂼ��1���������Ă���
//SW�߰Ă���ٱ���/�޳݂͌ďo�����ōs���Ă������ơ
//CdS�߰Ă���ٱ��ߐ����func_CdS.c�ōs���Ă���
//CVD�߰Ă���ٱ���/�޳݂�ݒ肵�Ȃ����ơ


//���L�̵�߼�ݐݒ���ďo�����Ő錾���Ă������ơ
//#define	SLEEP_EN	//Sleep�@�\����������Ƃ��ɐ錾����
//#define	SHAUTO		//�����J�n����Ƃ��ɐ錾����
//#define	KYOKU_RAND	//�Ȕԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEIN_RAND	//����N�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEII_RAND	//����I�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEIC_RAND	//����C�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
//#define	ONSEIS_RAND	//����S�ԍ�������ϲ�ނ���Ƃ��ɐ錾����
#define		SW_EN		//SW����������Ƃ��ɐ錾����
//#define	TRG_EN	    //TRIGGER�@�\(piezo����)����������Ƃ��ɐ錾����
//#define	CdS_EN		//CdS����������Ƃ��ɐ錾����
//#define	CVD_EN		//CVD����������Ƃ��ɐ錾����


//�ٺްٔ��ւ̉��p�ł͈ȉ���錾���Ă�������
//#define	CdS_FUTA	//�W���J����(��)�Ƶݔ��肷��
//#define	CdS_THR	100	//����臒l���Œ�̐錾�l�ɂ���


//==============================================
//�\�����(�ʱ��ع���݂����Ŏg������)
//==============================================
#define	SLEEP_TMR	1000			//Sleep�ɓ���O�̎���[ms]
						//�@����̕]�����Ԃ����������邱��


#ifdef SW_EN				//SW����������Ƃ�
//==============================================
//SW�\���̒�`
//==============================================
static const struct SW_CNF
{
	PORT_t *port;				//PORT���ڽ
	unsigned char mode;			//b7:SW��Ӱ��
						//�@0=ر�Ӱ�ޤ1=��ϰӰ��
						//b6:�߰ē��͂̋ɐ�
						//�@0=���_���1=���_��
	unsigned char msk;			//�ޯ�Ͻ�
}sw_cnf[]=
{

//SW0�̍\��-------------------------------------
#ifdef SW0_BIT
#ifdef SW0_TIMER
#define SW0_MODE 0x80
#define SW_TIMER
#endif
#ifdef SW0_REAL
#define SW0_MODE 0x00
#define SW_REAL
#endif
#ifdef SW0_INV
#define SW0_POL 0x00
#else
#define SW0_POL 0x40
#endif
	{&SW0_PORT,SW0_MODE|SW0_POL,1<<SW0_BIT},
#endif

//SW1�̍\��-------------------------------------
#ifdef SW1_BIT
#ifdef SW1_TIMER
#define SW1_MODE 0x80
#define SW_TIMER
#endif
#ifdef SW1_REAL
#define SW1_MODE 0x00
#define SW_REAL
#endif
#ifdef SW1_INV
#define SW1_POL 0x00
#else
#define SW1_POL 0x40
#endif
	{&SW1_PORT,SW1_MODE|SW1_POL,1<<SW1_BIT},
#endif

//SW2�̍\��-------------------------------------
#ifdef SW2_BIT
#ifdef SW2_TIMER
#define SW2_MODE 0x80
#define SW_TIMER
#endif
#ifdef SW2_REAL
#define SW2_MODE 0x00
#define SW_REAL
#endif
#ifdef SW2_INV
#define SW2_POL 0x00
#else
#define SW2_POL 0x40
#endif
	{&SW2_PORT,SW2_MODE|SW2_POL,1<<SW2_BIT},
#endif

//SW3�̍\��-------------------------------------
#ifdef SW3_BIT
#ifdef SW3_TIMER
#define SW3_MODE 0x80
#define SW_TIMER
#endif
#ifdef SW3_REAL
#define SW3_MODE 0x00
#define SW_REAL
#endif
#ifdef SW3_INV
#define SW3_POL 0x00
#else
#define SW3_POL 0x40
#endif
	{&SW3_PORT,SW3_MODE|SW3_POL,1<<SW3_BIT},
#endif
};

#define	SW_REAL					//SWر�Ӱ�ނ���������Ƃ��ɐ錾����
#define	SW_TIMER				//SW��ϰӰ�ނ���������Ƃ��ɐ錾����
#include "func_SW.c"				//SW�]��Ӽޭ�ق��č���
#endif

#ifdef TRG_EN				//�g���K���͂���������Ƃ�
//==============================================
//�g���K�\���̒�`
//==============================================
#endif

#ifdef CdS_EN				//CdS����������Ƃ�
//==============================================
//CdS�\���̒�`
//==============================================
#include "func_CdS.c"				//CdS�]��Ӽޭ�ق��č���
#endif


#ifdef CVD_EN				//CVD����������Ƃ�
//==============================================
//CVD�\���̒�`
//==============================================
static const struct CVD_CNF
{
	PORT_t *port;				//PORT���ڽ
	unsigned char mode;			//b7:SW��Ӱ��(0=ر�Ӱ�ޤ1=��ϰӰ��)
						//b2-0:�ޯĔԍ�
	unsigned char ain;			//AIN�ԍ�
}cvd_cnf[]=
{

//CVD0�̍\��-------------------------------------
#ifdef CVD0_BIT
#ifdef CVD0_TIMER
#define CVD0_MODE 0x80
#define CVD_TIMER
#endif
#ifdef CVD0_REAL
#define CVD0_MODE 0x00
#define CVD_REAL
#endif
	{&CVD0_PORT,CVD0_MODE|CVD0_BIT,CVD0_AIN},
#endif

//CVD1�̍\��-------------------------------------
#ifdef CVD1_BIT
#ifdef CVD1_TIMER
#define CVD1_MODE 0x80F
#define CVD_TIMER
#endif
#ifdef CVD1_REAL
#define CVD1_MODE 0x00
#define CVD_REAL
#endif
	{&CVD1_PORT,CVD1_MODE|CVD1_BIT,CVD1_AIN},
#endif

//CVD2�̍\��-------------------------------------
#ifdef CVD2_BIT
#ifdef CVD2_TIMER
#define CVD2_MODE 0x80
#define CVD_TIMER
#endif
#ifdef CVD2_REAL
#define CVD2_MODE 0x00
#define CVD_REAL
#endif
	{&CVD2_PORT,CVD2_MODE|CVD2_BIT,CVD2_AIN},
#endif

//CVD3�̍\��-------------------------------------
#ifdef CVD3_BIT
#ifdef CVD3_TIMER
#define CVD3_MODE 0x80
#define CVD_TIMER
#endif
#ifdef CVD3_REAL
#define CVD3_MODE 0x00
#define CVD_REAL
#endif
	{&CVD3_PORT,CVD3_MODE|CVD3_BIT,CVD3_AIN},
#endif

};

#include "func_CVD.c"				//CVD�]��Ӽޭ�ق��č���
#endif


//==============================================
//LED����ϸ�
//==============================================
#define	LED0_H		LED0_PORT.OUTSET=(1<<LED0_BIT)
#define	LED0_L		LED0_PORT.OUTCLR=(1<<LED0_BIT)
#define	LED1_H		LED1_PORT.OUTSET=(1<<LED1_BIT)
#define	LED1_L		LED1_PORT.OUTCLR=(1<<LED1_BIT)
#define	LED2_H		LED2_PORT.OUTSET=(1<<LED2_BIT)
#define	LED2_L		LED2_PORT.OUTCLR=(1<<LED2_BIT)
#define	LED3_H		LED3_PORT.OUTSET=(1<<LED3_BIT)
#define	LED3_L		LED3_PORT.OUTCLR=(1<<LED3_BIT)
#define	LED4_H		LED4_PORT.OUTSET=(1<<LED4_BIT)
#define	LED4_L		LED4_PORT.OUTCLR=(1<<LED4_BIT)
#define	LED5_H		LED5_PORT.OUTSET=(1<<LED5_BIT)
#define	LED5_L		LED5_PORT.OUTCLR=(1<<LED5_BIT)
#define	LED6_H		LED6_PORT.OUTSET=(1<<LED6_BIT)
#define	LED6_L		LED6_PORT.OUTCLR=(1<<LED6_BIT)


//==============================================
//����ϲ�ނ�ADC�ݒ�(PA1:A1)
//==============================================
#define	RAND_AIN		5		//AIN�ԍ�(SW2/CVD0)


//==============================================
//�ŗL�̍�ƈ�
//==============================================
#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)
static unsigned char rand_x;			//����ϲ�ނ̎�
#endif
#if PART_N>0
static unsigned char kyoku;
#ifdef KYOKU_RAND
static unsigned char kyoku_rand_msk;
#endif
#endif
#if VOICE_N>0
static unsigned char onseiN;
#ifdef ONSEIN_RAND
static unsigned char onseiN_rand_msk;
#endif
#endif
#if VOICE_I>0
static unsigned char onseiI;
#ifdef ONSEII_RAND
static unsigned char onseiI_rand_msk;
#endif
#endif
#if VOICE_C>0
static unsigned char onseiC;
#ifdef ONSEIC_RAND
static unsigned char onseiC_rand_msk;
#endif
#endif
#if VOICE_S>0
static unsigned char onseiS;
#ifdef ONSEIS_RAND
static unsigned char onseiS_rand_msk;
#endif
#endif


#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)
//==============================================
//����ϲ�ނ��ޯ�Ͻ�����݂��v�Z����
//==============================================
static unsigned char rand_msk(
	unsigned char no)			//������
{
//DBG_C('\n');
//DBG_C('p');
//DBG_B(no);
	if(no>127) return(0xff);
	if(no>63) return(0x7f);
	if(no>31) return(0x3f);
	if(no>15) return(0x1f);
	if(no>7) return(0x0f);
	if(no>3) return(0x07);
	return(0x03);
}


//==============================================
//����ϲ��
//==============================================
static unsigned char rand(void)
{

//DBG_C('r');
	rand_x=(rand_x<<2)+rand_x+1;
//DBG_B(rand_x);
	return(rand_x);
}
#endif


//==============================================
//��ݕω������������
//==============================================
ISR(PORTA_PORT_vect)
{
	PORTA.INTFLAGS=0xff;			//��ݕω��������׸ނ�ر����
}

#ifdef PORTB				//PORTB�����݂���Ƃ�
ISR(PORTB_PORT_vect)
{
	PORTB.INTFLAGS=0xff;			//��ݕω��������׸ނ�ر����
}
#endif


//==============================================
//���؂̏����ݒ�
//==============================================
static void apl_init(void)
{

//DBG_C('\n');
//DBG_C('$');

//Ӱ�������߰Đݒ�  24/05/23 YM �ǉ�
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�@(�_�����] 24/05/23 YM)
	MTR_PORT.DIRSET=1<<MTR_BIT;		//�o��Ӱ��
	#endif

#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)
	//����ϲ�ނ̎�
//DBG_C('r');
	ADC0.MUXPOS=RAND_AIN;			//���͂�ݒ肷��
	ADC0.COMMAND=0b00000001;		//�ϊ��J�n
	while(ADC0.COMMAND&0b00000001);		//�ϊ�������҂�
	rand_x=ADC0.RES;			//�ϊ����ʂ���ɂ���

	//����ϲ�ނ��ޯ�Ͻ�����ݐݒ�
#if (PART_N>0)&&defined(KYOKU_RAND)
	kyoku_rand_msk=rand_msk(song_idx->no);
//DBG_B(kyoku_rand_msk);
#endif
#if (VOICE_N>0)&&defined(ONSEIN_RAND)
	onseiN_rand_msk=rand_msk(VOICEN_SU);
//DBG_B(onseiN_rand_msk);
#endif
#if (VOICE_I>0)&&defined(ONSEII_RAND)
	onseiI_rand_msk=rand_msk(VOICEI_SU);
//DBG_B(onseiI_rand_msk);
#endif
#if (VOICE_C>0)&&defined(ONSEIC_RAND)
	onseiC_rand_msk=rand_msk(VOICEC_SU);
//DBG_B(onseiC_rand_msk);
#endif
#if (VOICE_S>0)&&defined(ONSEIS_RAND)
	onseiS_rand_msk=rand_msk(VOICES_SU);
//DBG_B(onseiS_rand_msk);
#endif
#endif

#ifdef LED_EN				//LED����������Ƃ�
	//LED�߰Đݒ�
#ifdef LED0_BIT				//LED0����������Ƃ�
	LED0_PORT.DIRSET=1<<LED0_BIT;
#endif
#ifdef LED1_BIT				//LED1����������Ƃ�
	LED1_PORT.DIRSET=1<<LED1_BIT;
#endif
#ifdef LED2_BIT				//LED2����������Ƃ�
	LED2_PORT.DIRSET=1<<LED2_BIT;
#endif
#ifdef LED3_BIT				//LED3����������Ƃ�
	LED3_PORT.DIRSET=1<<LED3_BIT;
#endif
#ifdef LED4_BIT				//LED4����������Ƃ�
	LED4_PORT.DIRSET=1<<LED4_BIT;
#endif
#endif

	//SW�߰Đݒ�
#ifdef SW_EN				//SW����������Ƃ�
#ifdef SW0_BIT				//SW0����������Ƃ�
#ifdef SW0_INV				//���͂����_���̂Ƃ�
	((PORT_tn *)&SW0_PORT)->PINnCTRL[SW0_BIT]=0b00001001;
					//��ٱ��߂��養����݂���
#else					//���͂����_��(�O������޳�)�̂Ƃ�
	((PORT_tn *)&SW0_PORT)->PINnCTRL[SW0_BIT]=0b00000001;
					//��ٱ��߂��Ȃ�������݂���
#endif
#endif
#ifdef SW1_BIT				//SW1����������Ƃ�
#ifdef SW1_INV				//���͂����_���̂Ƃ�
	((PORT_tn *)&SW1_PORT)->PINnCTRL[SW1_BIT]=0b00001001;
					//��ٱ��߂��養����݂���
#else					//���͂����_��(�O������޳�)�̂Ƃ�
	((PORT_tn *)&SW1_PORT)->PINnCTRL[SW1_BIT]=0b00000001;
					//��ٱ��߂��Ȃ�������݂���
#endif
#endif
#ifdef SW2_BIT				//SW2����������Ƃ�
#ifdef SW2_INV				//���͂����_���̂Ƃ�
	((PORT_tn *)&SW2_PORT)->PINnCTRL[SW2_BIT]=0b00001001;
					//��ٱ��߂��養����݂���
#else					//���͂����_��(�O������޳�)�̂Ƃ�
	((PORT_tn *)&SW2_PORT)->PINnCTRL[SW2_BIT]=0b00000001;
					//��ٱ��߂��Ȃ�������݂���
#endif
#endif
#ifdef SW3_BIT				//SW3����������Ƃ�
#ifdef SW3_INV				//���͂����_���̂Ƃ�
	((PORT_tn *)&SW3_PORT)->PINnCTRL[SW3_BIT]=0b00001001;
					//��ٱ��߂��養����݂���
#else					//���͂����_��(�O������޳�)�̂Ƃ�
	((PORT_tn *)&SW3_PORT)->PINnCTRL[SW3_BIT]=0b00000001;
					//��ٱ��߂��Ȃ�������݂���
#endif
#endif
#endif

	//CVD�߰Đݒ�
#ifdef CVD_EN				//CVD����������Ƃ�
#ifdef CVD0_BIT				//CVD0����������Ƃ�
#ifdef CVD_EXPU				//CVD���O����ٱ��߂���Ƃ�
	((PORT_tn *)&CVD0_PORT)->PINnCTRL[CVD0_BIT]=0b00000000;
					//������ٱ��߂��Ȃ�
#else					//CVD�������ٱ��߂���Ƃ�
	((PORT_tn *)&CVD0_PORT)->PINnCTRL[CVD0_BIT]=0b00001000;
					//������ٱ��߂���
#endif
#endif
#ifdef CVD1_BIT				//CVD1����������Ƃ�
#ifdef CVD_EXPU				//CVD���O����ٱ��߂���Ƃ�
	((PORT_tn *)&CVD1_PORT)->PINnCTRL[CVD1_BIT]=0b00000000;
					//������ٱ��߂��Ȃ�
#else					//CVD�������ٱ��߂���Ƃ�
	((PORT_tn *)&CVD1_PORT)->PINnCTRL[CVD1_BIT]=0b00001000;
					//������ٱ��߂���
#endif
#endif
#ifdef CVD2_BIT				//CVD2����������Ƃ�
#ifdef CVD_EXPU				//CVD���O����ٱ��߂���Ƃ�
	((PORT_tn *)&CVD2_PORT)->PINnCTRL[CVD2_BIT]=0b00000000;
					//������ٱ��߂��Ȃ�
#else					//CVD�������ٱ��߂���Ƃ�
	((PORT_tn *)&CVD2_PORT)->PINnCTRL[CVD2_BIT]=0b00001000;
					//������ٱ��߂���
#endif
#endif
#ifdef CVD3_BIT				//CVD0����������Ƃ�
#ifdef CVD_EXPU				//CVD���O����ٱ��߂���Ƃ�
	((PORT_tn *)&CVD3_PORT)->PINnCTRL[CVD3_BIT]=0b00000000;
					//������ٱ��߂��Ȃ�
#else					//CVD�������ٱ��߂���Ƃ�
	((PORT_tn *)&CVD3_PORT)->PINnCTRL[CVD3_BIT]=0b00001000;
					//������ٱ��߂���
#endif
#endif
#endif

//DBG_C('%');
}


#ifdef	SLEEP_EN			//Sleep�@�\����������Ƃ�
//==============================================
//Sleep����
//==============================================
static void apl_sleep(void)
{
	//Ӱ����~;�@24/05/23 �ǉ� YM
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�@�i�_�����]�@YM�j
	#endif
#if (defined(SW0_REAL)&&defined(SW_EN))||(defined(CdS_REAL)&&defined(CdS_EN))||(defined(CVD0_REAL)&&defined(CVD_EN))
	unsigned char res;
#endif

//DBG_C('\n');
//DBG_C('<');
	//LED����
#ifdef LED_EN				//LED����������Ƃ�
#ifdef LED0				//LED0����������Ƃ�
	LED0_L;
#endif
#ifdef LED1				//LED1����������Ƃ�
	LED1_L;
#endif
#ifdef LED2				//LED2����������Ƃ�
	LED2_L;
#endif
#ifdef LED3				//LED3����������Ƃ�
	LED3_L;
#endif
#ifdef LED4				//LED4����������Ƃ�
	LED4_L;
#endif
#ifdef LED5				//LED5����������Ƃ�
	LED5_L;
#endif
#ifdef LED6				//LED6����������Ƃ�
	LED6_L;
#endif
#endif

#if VOICE_S>0
	//W25����ܰ�޳�
//DBG_C('a');
	W25_PWR_DOWN();				//W25����ܰ�޳݂���
#endif

	//PWM���~
//DBG_C('b');
	dev_pwm_stop();				//PWM���~����

	//Sleep����
#if defined(CdS_EN)||defined(CVD_EN)	//CdS��CVD����������Ƃ�
					//PIT�ŊԌ����삷��
	for(;;)
	{
		//SLEEPDEEPӰ�ނֈڍs
//DBG_C('c');
DBG_SYNC();
//	DBS_H;					//Sleep��\������
		RTC.PITINTCTRL=RTC_PITEN_bm;	//PIT�����݋���
		sleep_cpu();			//�����݂���������܂�Sleep����
		RTC.PITINTCTRL=0;		//PIT�����݋֎~
//	DBS_L;					//Wakeup��\������
//DBG_C('d');

#ifdef SW_EN				//SW����������Ƃ�
		//SW��]������
//DBG_C('e');
//DBG_B(sw_hst[0]);
#ifdef SW0_TIMER			//��ϰӰ�ނ̂Ƃ�
		sw_read(0);			//SW0��]������
//DBG_B(sw_hst[0]);
		if(sw_hst[0])			//SW0���݂ɂȂ�����
		{
			sw_hst[0]--;		//�����������߂�
			break;			//Sleep���甲����
		}
#endif
#ifdef SW0_REAL				//ر�Ӱ�ނ̂Ƃ�
		res=sw_read(0);			//SW0��]������
//DBG_B(res);
		if(res)				//�ω�����������
		{
			sw_hst[0]>>=1;		//�]���������߂�
			break;			//Sleep���甲����
		}
#endif
#endif

#ifdef CdS_EN				//CdS����������Ƃ�
		//CdS��]������
//DBG_C('f');
//DBG_B(cds_hst);
#ifdef CdS_TIMER			//��ϰӰ�ނ̂Ƃ�
		cds_read();			//CdS��]������
//DBG_B(cds_hst);
		if(cds_hst)			//CdS���݂ɂȂ�����
		{
			cds_hst--;		//�����������߂�
			break;			//Sleep���甲����
		}
#endif
#ifdef CdS_REAL				//ر�Ӱ�ނ̂Ƃ�
		res=cds_read();			//CdS��]������
//DBG_B(res);
		if(res)				//�ω�����������
		{
			cds_hst>>=1;		//�]���������߂�
			break;			//Sleep���甲����
		}
#endif
#endif

#ifdef CVD_EN				//CVD����������Ƃ�
		//CVD��]������
//DBG_C('g');
//DBG_B(cvd_hist[0].cvd_hst);
#ifdef CVD_TIMER			//��ϰӰ�ނ̂Ƃ�
		cvd_read(0);			//CVD0��]������
//DBG_B(cvd_hist[0].cvd_hst);
		if(cvd_hist[0].cvd_hst)		//CVD0���݂ɂȂ�����
		{
			cvd_hist[0].cvd_hst--;	//�]���������߂�
			break;			//Sleep���甲����
		}
#endif
#ifdef CVD_REAL				//ر�Ӱ�ނ̂Ƃ�
		res=cvd_read(0);		//CVD0��]������
//DBG_B(res);
		if(res)				//�ω�����������
		{
			cvd_hist[0].cvd_hst>>=1;
						//�]���������߂�
			break;			//Sleep���甲����
		}
#endif
#endif
	}

#else					//CdS��CVD���������Ȃ��Ƃ�(TRG���[�h���ǉ��@YM)
	//SLEEPDEEPӰ�ނֈڍs
//DBG_C('i');
DBG_SYNC();
	TRG_PORT.DIRCLR=1<<TRG_BIT;		//�ض��߰Ă����Ӱ��
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000001;
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001001;
	//�ضނ���ٱ��߂��Ȃ�������݂���iSW0�Ńe�X�g�̂��߃v���A�b�v�����j
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000001;
	//�ضނ���ٱ��߂��Ȃ�������݂���ipiezo�Ńe�X�g�̂��߃v���A�b�v�O���j		
	wait_ms(10);				//�d�����莞�Ԃ�҂�
	PORTA.INTFLAGS=0xff;			//��ݕω��������׸ނ�ر����
	
	sleep_cpu();				//�����݂���������܂�Sleep����
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001000;
	//�ضނ���ٱ��߂��Ȃ�������݂��Ȃ� �� SW0�Ńe�X�g�̂��߃v���A�b�v����
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
	//�ضނ���ٱ��߂��Ȃ�������݂���ipiezo�Ńe�X�g�̂��߃v���A�b�v�O���j
//	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT;	//SCK���o��Ӱ�ށiYM 0607 �����SCK�Ƌ��p�ł͂Ȃ����߃R�����g�A�E�g�j
//DBG_C('j');
#endif

	//PWM���ĉғ�
//DBG_C('l');
	dev_pwm_start();			//PWM���J�n����

	//W25����ܰ����
#if	VOICE_S>0
//DBG_C('m');
	W25_PWR_UP();				//W25����ܰ���߂���
#endif
//DBG_C('>');
}
#endif


//==============================================
//�ŗL�̏���(����ޯ��֐�)
//==============================================
static void CB_KOYUU(void)
{
#ifdef SLEEP_EN				//Sleep�@�\����������Ƃ�
	static unsigned short sleep_tmr=0;	//Sleep��ϰ
#endif
	unsigned char res;
#if PART_N>0				//�ٺްى��t����������Ƃ�
	struct SONG_IDX *p;
#endif

//DBG_C('\n');
//DBG_C('k');

	//�ғ�����
#ifdef SLEEP_EN				//Sleep�@�\����������Ƃ�
//DBG_C('e');
	res=0;					//���ɔ�ғ��ɂ��Ă���
#if PART_N>0				//�ٺްى��t����������Ƃ�
	res|=song.no;				//�ғ����Ă���Ƃ��͉ғ����̐ݒ�
#endif
#if VOICE_N>0				//����N�Đ�����������Ƃ�
	res|=voiceN[0].no;			//�ғ����Ă���Ƃ��͉ғ����̐ݒ�
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
	res|=voiceI.no;				//�ғ����Ă���Ƃ��͉ғ����̐ݒ�
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
	res|=voiceC.no;				//�ғ����Ă���Ƃ��͉ғ����̐ݒ�
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
	res|=voiceS.no;				//�ғ����Ă���Ƃ��͉ғ����̐ݒ�
#endif
//DBG_B(res);
	if(res)					//�ғ����Ă���Ƃ���
	{
		sleep_tmr=0;			//�@Sleep������ر����
	}
	else					//�ғ����Ă��Ȃ��Ƃ���
	{
//DBG_C('X');
//DBG_S(sleep_tmr);
		if(++sleep_tmr>SLEEP_TMR/KOYUU_PR)
						//�@Sleep�����𒴂�����
		{
			apl_sleep();		//�@Sleep����
			sleep_tmr=0;		//�@Sleep������ر����
		}
	}
#endif

	//��������
	res=0;					//���ɑ��얳���ɂ��Ă���
#ifdef SW_EN				//SW����������Ƃ�
//DBG_C('s');
	if(!res) res=sw_read(0);		//SW0��]������
//DBG_B(res);
#endif
#ifdef CdS_EN
//DBG_C('c');				//CdS����������Ƃ�
	if(!res) res=cds_read();		//CdS��]������
//DBG_B(res);
#endif
#ifdef CVD_EN
//DBG_C('n');				//CVD����������Ƃ�
	if(!res) res=cvd_read(0);		//CVD0��]������
//DBG_B(res);
#endif

	//����̎��s
	switch(res)				//������e�ŏ�������
	{
	case 0:				//���삪�Ȃ��Ƃ�
#ifdef SHAUTO				//�����J�n����Ƃ�
//DBG_C('a');

//���[�^�ғ��ǉ��@24/05/23 YM
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����ғ��i�_�����]YM)
#endif

#if PART_N>0				//�ٺްى��t����������Ƃ�
//DBG_C('o');
//DBG_B(song.no);
		if(!song.no)			//���t���ĂȂ�������
		{
			p=(struct SONG_IDX *)song_idx;
						//�Ȳ��ޯ���̱��ڽ�𓾂�
#ifdef KYOKU_RAND			//�Ȕԍ�������ϲ�ނ���Ƃ�
//DBG_C('\n');
			kyoku+=(rand()&kyoku_rand_msk)+1;
						//����тɑ�������
			while(kyoku>p->no) kyoku-=p->no;
						//���������Ɏ��߂�
#else					//�Ȕԍ������ɐi�߂�Ƃ�
			if(++kyoku>p->no) kyoku=1;
						//�Ȕԍ���i�߂�
#endif
//DBG_B(kyoku);
			SONG_SEL(kyoku);    //���t�J�n����
			
		}
#endif
#if VOICE_N>0				//����N�Đ�����������Ƃ�
//DBG_C('n');
//DBG_B(voiceN[0].no);
		if(!voiceN[0].no)		//�Đ����ĂȂ�������
		{
#ifdef ONSEIN_RAND			//����N�ԍ�������ϲ�ނ���Ƃ�
			onseiN+=(rand()&onseiN_rand_msk)+1;
						//����тɑ�������
			while(onseiN>VOICEN_SU) onseiN-=VOICEN_SU;
						//���������Ɏ��߂�
#else					//����N�ԍ������ɐi�߂�Ƃ�
			if(++onseiN>VOICEN_SU) onseiN=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiN);
			VOICEN_SEL(0,onseiN);	//�Đ��J�n����
		}
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
//DBG_C('i');
//DBG_B(voiceI.no);
		if(!voiceI.no)			//�Đ����ĂȂ�������
		{
#ifdef ONSEII_RAND			//����I�ԍ�������ϲ�ނ���Ƃ�
			onseiI+=(rand()&onseiI_rand_msk)+1;
						//����тɑ�������
			while(onseiI>VOICEI_SU) onseiI-=VOICEI_SU;
						//���������Ɏ��߂�
#else					//����I�ԍ������ɐi�߂�Ƃ�
			if(++onseiI>VOICEI_SU) onseiI=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiI);
			VOICEI_SEL(onseiI);	//�Đ��J�n����
		}
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
//DBG_C('c');
//DBG_B(voiceC.no);
		if(!voiceC.no)			//�Đ����ĂȂ�������
		{
#ifdef ONSEIC_RAND			//����C�ԍ�������ϲ�ނ���Ƃ�
			onseiC+=(rand()&onseiC_rand_msk)+1;
						//����тɑ�������
			while(onseiC>VOICEC_SU) onseiC-=VOICEC_SU;
						//���������Ɏ��߂�
#else					//����C�ԍ������ɐi�߂�Ƃ�
			if(++onseiC>VOICEC_SU) onseiC=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiC);
			VOICEC_SEL(onseiC);	//�Đ��J�n����
		}
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
//DBG_C('s');
//DBG_B(voiceS.no);
		if(!voiceS.no)			//�Đ����ĂȂ�������
		{
#ifdef ONSEIS_RAND			//����S�ԍ�������ϲ�ނ���Ƃ�
			onseiS+=(rand()&onseiS_rand_msk)+1;
						//����тɑ�������
			while(onseiS>VOICES_SU) onseiS-=VOICES_SU;
						//���������Ɏ��߂�
#else					//����S�ԍ������ɐi�߂�Ƃ�
			if(++onseiS>VOICES_SU) onseiS=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiS);
			VOICES_SEL(onseiS);	//�Đ��J�n����
		}
#endif
#endif
		break;
	case 1:				//�Z�݌��m�̂Ƃ�
	
//���[�^�ғ��ǉ��@24/05/23 YM
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����ғ��i�_�����] YM)
#endif

#if PART_N>0				//�ٺްى��t����������Ƃ�
		p=(struct SONG_IDX *)song_idx;	//�Ȳ��ޯ���̱��ڽ�𓾂�
#ifdef KYOKU_RAND			//�Ȕԍ�������ϲ�ނ���Ƃ�
//DBG_C('\n');
		kyoku+=(rand()&kyoku_rand_msk)+1;
						//����тɑ�������
//DBG_B(kyoku);
		while(kyoku>p->no) kyoku-=p->no;//���������Ɏ��߂�
//DBG_B(kyoku);
#else					//�Ȕԍ������ɐi�߂�Ƃ�
		if(++kyoku>p->no) kyoku=1;	//�Ȕԍ���i�߂�
#endif
//DBG_B(kyoku);
		SONG_SEL(kyoku);		//���t�J�n����
#endif
#if VOICE_N>0				//����N�Đ�����������Ƃ�
#ifdef ONSEIN_RAND			//����N�ԍ�������ϲ�ނ���Ƃ�
		onseiN+=(rand()&onseiN_rand_msk)+1;
						//����тɑ�������
		while(onseiN>VOICEN_SU) onseiN-=VOICEN_SU;
						//���������Ɏ��߂�
#else					//����N�ԍ������ɐi�߂�Ƃ�
		if(++onseiN>VOICEN_SU) onseiN=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiN);
		VOICEN_SEL(0,onseiN);		//�Đ��J�n����
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
#ifdef ONSEII_RAND			//����I�ԍ�������ϲ�ނ���Ƃ�
		onseiI+=(rand()&onseiI_rand_msk)+1;
						//����тɑ�������
		while(onseiI>VOICEI_SU) onseiI-=VOICEI_SU;
						//���������Ɏ��߂�
#else					//����I�ԍ������ɐi�߂�Ƃ�
		if(++onseiI>VOICEI_SU) onseiI=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiI);
		VOICEI_SEL(onseiI);		//�Đ��J�n����
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
#ifdef ONSEIC_RAND			//����C�ԍ�������ϲ�ނ���Ƃ�
		onseiC+=(rand()&onseiC_rand_msk)+1;
						//����тɑ�������
		while(onseiC>VOICEC_SU) onseiC-=VOICEC_SU;
						//���������Ɏ��߂�
#else					//����C�ԍ������ɐi�߂�Ƃ�
		if(++onseiC>VOICEC_SU) onseiC=1;
						//�����ԍ���i�߂�
#endif
//DBG_B(onseiC);
		VOICEC_SEL(onseiC);		//�Đ��J�n����
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
#ifdef ONSEIS_RAND			//����S�ԍ�������ϲ�ނ���Ƃ�
//DBG_C('\n');
		onseiS+=(rand()&onseiS_rand_msk)+1;
						//����тɑ�������
//DBG_B(onseiS);
		while(onseiS>VOICES_SU) onseiS-=VOICES_SU;
						//���������Ɏ��߂�
#else					//����S�ԍ������ɐi�߂�Ƃ�
		if(++onseiS>VOICES_SU) onseiS=1;
						//�����ԍ���i�߂�
//DBG_B(onseiS);
#endif
//DBG_B(onseiS);
		VOICES_SEL(onseiS);		//�Đ��J�n����
#endif
		break;
	case 2:				//���݈�v�̂Ƃ�
	
//Ӱ����~;�@24/05/23 �ǉ� YM
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif
	
#if PART_N>0				//�ٺްى��t����������Ƃ�
		SONG_SEL(0);			//���t���f����
#endif
#if VOICE_N>0				//����N�Đ�����������Ƃ�
		VOICEN_SEL(0,0);		//�Đ����f����
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
		VOICEI_SEL(0);			//�Đ����f����
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
		VOICEC_SEL(0);			//�Đ����f����
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
		VOICES_SEL(0);			//�Đ����f����
#endif
		break;
	}

	//LED�_��
#if PART_N>0				//�ٺްى��t����������Ƃ�
	if(song.no)				//���t���̂Ƃ�
	{
#ifdef LED_EN				//LED����������Ƃ�
#ifdef LED0_BIT				//LED0����������Ƃ�
		if(part[0].onpu_cd&0x0001) LED0_H;
		else LED0_L;
#endif
#ifdef LED1_BIT				//LED1����������Ƃ�
		if(part[0].onpu_cd&0x0002) LED1_H;
		else LED1_L;
#endif
#ifdef LED2_BIT				//LED2����������Ƃ�
		if(part[0].onpu_cd&0x0004) LED2_H;
		else LED2_L;
#endif
#ifdef LED3_BIT				//LED3����������Ƃ�
		if(part[0].onpu_cd&0x0008) LED3_H;
		else LED3_L;
#endif
#ifdef LED4_BIT				//LED4����������Ƃ�
		if(part[0].onpu_cd&0x0010) LED4_H;
		else LED_L;
#endif
#ifdef LED5_BIT				//LED5����������Ƃ�
#if PART_N==1				//1�߰Ă̂ݎ�������Ƃ�
		if(part[0].onpu_cd&0x0020) LED5_H;
		else LED5_L;
#else					//2�߰Ĉȏ��������Ƃ�
		if(part[1].onpu_cd&0x0001) LED5_H;
		else LED_L;
#endif
#endif
#ifdef LED6_BIT				//LED6����������Ƃ�
#if PART_N==1				//1�߰Ă̂ݎ�������Ƃ�
		if(part[0].onpu_cd&0x0040) LED6_H;
		else LED6_L;
#else					//2�߰Ĉȏ��������Ƃ�
		if(part[1].onpu_cd&0x0002) LED6_H;
		else LED6_L;
#endif
#endif
#endif
	}
#endif
}


#if	PART_N>0			//�ٺްى��t����������Ƃ�
//==============================================
//���t�I�����̏���(����ޯ��֐�)
//==============================================
static void CB_SONG_END(void)
{
	//���[�^��~��ǉ� 24/05/23 YM
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
	#endif
}
#endif


#if	VOICE_N>0			//����N�Đ�����������Ƃ�
//==============================================
//����0�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICEN_END(
	unsigned char ch)			//����N��ch�ԍ�
{
	//���[�^��~��ǉ� 24/05/23 YM
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
	#endif
}
#endif


#if	VOICE_I>0			//����I�Đ�����������Ƃ�
//==============================================
//����I�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICEI_END(void)
{
	//���[�^��~��ǉ� 24/05/23 YM
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
	#endif
}
#endif


#if	VOICE_C>0			//����C�Đ�����������Ƃ�
//==============================================
//����C�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICEC_END(void)
{
	//���[�^��~��ǉ� 24/05/23 YM
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
	#endif
}
#endif


#if	VOICE_S>0			//����S�Đ�����������Ƃ�
//==============================================
//����S�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICES_END(void)
{
	//���[�^��~��ǉ� 24/05/23 YM
	#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
	#endif
}
#endif
