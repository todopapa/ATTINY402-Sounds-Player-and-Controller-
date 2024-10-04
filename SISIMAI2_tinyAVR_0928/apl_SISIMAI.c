//==============================================
//�\�����(�ʱ��ع���݂����Ŏg������)
//==============================================
//#define	SLEEP_TMR	100			//Sleep�ɓ���O�̎���[ms]
#define	SLEEP_TMR	4000			//Sleep�ɓ���O�̎���[ms]
						//�@����̕]�����Ԃ����������邱�� (������E���Ƃ��͒������邱�Ɓj
						
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

	//Ӱ�������߰Đݒ�
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
//	MTR_PORT.DIRCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif
}


#ifdef	SLEEP_EN			//Sleep�@�\����������Ƃ�
//==============================================
//Sleep����
//==============================================
static void apl_sleep(void)
{
//DBG_C('\n');
//DBG_C('<');
	//Ӱ����~;
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
    MTR_PORT.DIRSET=1<<MTR_BIT;     // MTR_BIT���o�̓|�[�g�ɐݒ肷��
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
    MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif

#if VOICE_S>0
	//W25����ܰ�޳�
//DBG_C('a');
	W25_PWR_DOWN();				//W25����ܰ�޳݂���
#endif

	//PWM���~
//DBG_C('b');
	dev_pwm_stop();				//PWM���~����
	
//�g���K�|�[�g�����荞�݋֎~
	TRG_PORT.DIRSET=1<<TRG_BIT;		//�ض��߰Ă��o��Ӱ��
((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
//�g���K�|�[�g�̊��荞�݂��N���A
PORTA.INTFLAGS=0xff;			//��ݕω��������׸ނ�ر����
	
//SLEEPDEEPӰ�ނֈڍs
//DBG_C('i');
DBG_SYNC();
	TRG_PORT.DIRCLR=1<<TRG_BIT;		//�ض��߰Ă����Ӱ��
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000001;
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001001;
						//�ضނ���ٱ��߂��Ȃ�������݂���(�e�X�g�Ńv���A�b�v�j
	wait_ms(10);				//�d�����莞�Ԃ�҂�
	PORTA.INTFLAGS=0xff;			//��ݕω��������׸ނ�ر����
#ifdef PORTB				//PORTB�����݂���Ƃ�
	PORTB.INTFLAGS=0xff;			//��ݕω��������׸ނ�ر����
#endif
	sleep_cpu();				//�����݂���������܂�Sleep����
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001000;
						//�ضނ���ٱ��߂��Ȃ�������݂��Ȃ�(�e�X�g�Ńv���A�b�v�j
//	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT;	//SCK���o��Ӱ�ށiYM �����SCK�Ƌ��p�ł͂Ȃ����߃R�����g�A�E�g�j
	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT;	//SCK���o��Ӱ�ށiYM 0725��SCK�Ƌ��p�ɂ��邽�ߕ����j
//DBG_C('j');

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
	static unsigned char kyoku;		//�Ȕԍ�
#endif
#if VOICE_N>0				//����N�Đ�����������Ƃ�
	static unsigned char onseiN;		//����N�ԍ�
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
	static unsigned char onseiI;		//����I�ԍ�
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
	static unsigned short onseiC;		//����C�ԍ�
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
	static unsigned short onseiS;		//����S�ԍ�
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
//DBG_C('X');
//DBG_S(sleep_tmr);
	if(++sleep_tmr<SLEEP_TMR/KOYUU_PR) return;
					//�@Sleep�������������̂Ƃ��͖߂�
	apl_sleep();			//�@Sleep����
	sleep_tmr=0;			//�@Sleep������ر����
#endif

#if PART_N>0				//�ٺްى��t����������Ƃ�
//DBG_B(song.no);
	song_idx=(struct SONG_IDX *)((unsigned short)song_idx|0x8000);
						//��۸����ׯ���ֈʒu�t����
//DBG_S(song_idx);
//DBG_D(song_idx,16);
	if(++kyoku>song_idx->no) kyoku=1;	//�����ԍ���i�߂�
	SONG_SEL(kyoku);			//���t�J�n����
#endif
#if VOICE_N>0	
					//����N�Đ�����������Ƃ�
	if(++onseiN>VOICEN_SU) onseiN=1;	//�����ԍ���i�߂�
	VOICEN_SEL(0,onseiN);			//�Đ��J�n����
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
	if(++onseiI>VOICEI_SU) onseiI=1;	//�����ԍ���i�߂�
	VOICEI_SEL(onseiI);			//�Đ��J�n����
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
	if(++onseiC>VOICEC_SU) onseiC=1;	//�����ԍ���i�߂�
	VOICEC_SEL(onseiC);			//�Đ��J�n����
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
	if(++onseiS>VOICES_SU) onseiS=1;	//�����ԍ���i�߂�
	VOICES_SEL(onseiS);			//�Đ��J�n����
#endif

#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
//	MTR_PORT.OUTCLR=1<<MTR_BIT;		//Ӱ�����ғ�
	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����ғ�(�_�����]YM)
#endif
}


#if	PART_N>0			//�ٺްى��t����������Ƃ�
//==============================================
//���t�I�����̏���(����ޯ��֐�)
//==============================================
static void CB_SONG_END(void)
{
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
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
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif
}
#endif


#if	VOICE_I>0			//����I�Đ�����������Ƃ�
//==============================================
//����I�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICEI_END(void)
{
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif
}
#endif


#if	VOICE_C>0			//����C�Đ�����������Ƃ�
//==============================================
//����C�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICEC_END(void)
{
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif
}
#endif


#if	VOICE_S>0			//����S�Đ�����������Ƃ�
//==============================================
//����S�Đ��I�����̏���(����ޯ��֐�)
//==============================================
static void CB_VOICES_END(void)
{
#ifdef MTR_BIT				//Ӱ�������߰Ă���������Ă���Ƃ�
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//Ӱ�����~
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//Ӱ�����~�i�_�����] YM)
#endif
}
#endif
