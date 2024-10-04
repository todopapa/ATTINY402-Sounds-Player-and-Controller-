//==============================================
//TCA0�����۰(PWM����)�����������
//�E�ޯ̧���ް�ݎ���DC���X�V���Ȃ�(�O��̒l���p������)
//==============================================
ISR(TCA0_OVF_vect)
{
	short data;

//DBS_H;
//DBG_C('[');
	TCA0.SINGLE.INTFLAGS=0b00000001;	//���ް�۰�������׸ނ�ر

	//�ް����擾
	if(buf_read==buf_write) return;		//�ް�������������߂�
	data=buf[buf_read];			//�ް�����o��
//DBG_S(data);
	if(buf_read==(OUT_BUF_N-1)) buf_read=0;	//�ޯ̧�̌���ɂȂ�����擪�ɖ߂�
	else buf_read++;			//�ޯ̧��i�߂�

	//�ޭ�è���X�V
#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
	TCA0.SINGLE.CMP0BUF=PWM_STEP/2+data;	//������ݒ�
//DBG_S(TCA0.SINGLE.CMP0BUF);
#endif
#if BTL==1				//����؏o�͂̂Ƃ�
	TCA0.SINGLE.CMP0BUF=data;		//������ݒ�
//DBG_S(TCA0.SINGLE.CMP0BUF);
	TCA0.SINGLE.CMP1BUF=data;		//�t����ݒ�
//DBG_S(TCA0.SINGLE.CMP1BUF);
#endif
#if BTL>1				//��د�ޥ��ڰ��o�͂̂Ƃ�
	if(data<0)				//�����ق̂Ƃ�
	{
		TCA0.SINGLE.CMP0BUF=0;		//�������~�߂�
		TCA0.SINGLE.CMP1BUF=(-data)*2;	//�t����ݒ�
	}
	else					//�����ق̂Ƃ�
	{
		TCA0.SINGLE.CMP1BUF=0;		//�t�����~�߂�
		TCA0.SINGLE.CMP0BUF=data*2;	//������ݒ�
	}
//DBG_S(TCA0.SINGLE.CMP0BUF);
//DBG_S(TCA0.SINGLE.CMP1BUF);
#endif
//DBG_C(']');
//DBS_L;
}


//==============================================
//PWM������҂�
//==============================================
void pwm_wait(void)
{

	TCA0.SINGLE.INTFLAGS=0b00000001;	//TCA0���ް�۰�������׸ނ�ر
	while(!(TCA0.SINGLE.INTFLAGS&0b00000001));
						//PWM����������҂�
}


//==============================================
//PIT�����������
//==============================================
ISR(RTC_PIT_vect)
{

	RTC.PITINTFLAGS=RTC_PI_bm;		//PIT�������׸ނ�ر
}


//==============================================
//�ŗL�̏����ݒ�
//==============================================
static void CB_INIT(void)
{

	//���ѐݒ�
	ccp_write_io((void*)&(CLKCTRL.MCLKCTRLB),0);
						//OSC��ؽ�����(��ۯ�16MHz)
						//�@˭��ނ�16MHz�ۯ���I�����Ă�������
	SLPCTRL.CTRLA=0b00000101;		//��ܰ�޳�Ӱ�ޤSleep����

	//���޸ސݒ�
#ifdef SHDBG
	dbg_init();				//���޸ޏ�������������
#endif
#ifdef SHDBS
	dbs_init();				//���޸ސM��������������
#endif


////////////////////////////////////////////////
//��đ҂����Ԓ���
//for(;;){DBS_H;wait_us(26);DBS_L;wait_us(26);}
//wait_ms(10);for(;;){DBG_C('U');}
////////////////////////////////////////////////


	//I2C�߰Đݒ�
#if VOICE_I>0				//I2C���g���Ƃ�
#ifdef I2C_SOFT				//I2C���Ď�������Ƃ�
	I2C_SCL_PU;				//SCL����ٱ��߂���
	I2C_SDA_PU;				//SDA����ٱ��߂���
#else					//����I2CӼޭ�ق��g���Ƃ�
	PORTMUX.CTRLB=0b00010000;		//TWI0�������(SCL:PA2�SDA:PA1)�֐U��
	TWI0.MBAUD=20;				//400kbps(20MHz/(2*0.4)-5=20)
	TWI0.MCTRLB=TWI_FLUSH_bm;		//�����ðĂ�ر����
	TWI0.MCTRLA=0b00000001;			//I2C�L��
//DBG_B(TWI0.MSTATUS);
	TWI0.MSTATUS|=TWI_BUSSTATE_IDLE_gc;	//�޽����قɂ���
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm|TWI_BUSERR_bm);
						//�׸ނ�ر����
//DBG_B(TWI0.MSTATUS);
#endif
#endif

	//SPI�߰Đݒ�
#if VOICE_C+VOICE_S>0			//SPI���g���Ƃ�
	SPI_SS_OUT;				//SS���o��Ӱ��
	SPI_MISO_IN;				//MISO������޳ݓ���Ӱ��
	SPI_SCK_OUT;				//SCK���o��Ӱ��
	SPI_MOSI_OUT;				//MOSI���o��Ӱ��
#ifndef SPI_SOFT			//����SPIӼޭ�ق��g���Ƃ�
	SPI0.CTRLB=0b00000101;			//�ڰ�ޑI���֎~�MODE1
	SPI0.CTRLA=0b00110011;			//Ͻ���SPI�L��
#endif
#endif

	//PWM(TCA0)�ݒ�
#if BTL==2				//��د�ޏo�͂̂Ƃ�
	TCA0.SINGLE.PER=PWM_STEP+PWM_DB;	//PWM����=32.125us+�ޯ�������
#else					//�ݸ�٥����إ��ڰ��o�͂̂Ƃ�
	TCA0.SINGLE.PER=PWM_STEP;		//PWM����=32.125us
#endif
#ifdef PWM_SLOW				//PWM���ɒ[�ɒx������Ƃ�
	TCA0.SINGLE.CTRLA=0b00001111;		//�ۯ�����1/1024(���޸ޗp)�TCA����
#else
	TCA0.SINGLE.CTRLA=0b00000001;		//�ۯ����������TCA����
#endif
#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
	TCA0.SINGLE.CTRLB=0b00010011;		//����(WO0)���o�ͤ�ݸ�ٽ۰�ߓ���
#endif
#if BTL==1				//����؏o�͂̂Ƃ�
	TCA0.SINGLE.CMP0BUF=PWM_STEP/2;		//������DC��1/2�ɐݒ�
	TCA0.SINGLE.CMP1BUF=PWM_STEP/2;		//�t����DC��1/2�ɐݒ�
	TCA0.SINGLE.CTRLB=0b00110011;		//����(WO0)�Ƌt��(WO1)���o�ͤ�ݸ�ٽ۰�ߓ���
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//�t���𔽓]�o��
#endif
#if BTL>1				//��د�ޥ��ڰ��o�͂̂Ƃ�
	TCA0.SINGLE.CMP0BUF=0;			//������DC��0�ɐݒ�
	TCA0.SINGLE.CMP1BUF=0;			//�t����DC��0�ɐݒ�
	TCA0.SINGLE.CTRLB=0b00110011;		//�����Ƌt�����o�ͤ�ݸ�ٽ۰�ߓ���
#endif
#if BTL==3				//��د�ޏo�͂̂Ƃ�
	((PORT_tn *)&PWM_F_PORT)->PINnCTRL[PWM_F_BIT]=0b10000000;
						//�����𔽓]�o��
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//�t���𔽓]�o��
#endif
	TCA0.SINGLE.INTCTRL=0b00000001;		//���ް�۰�����݋���

	//PWM�߰Ă��o�͐ݒ�
	PWM_F_PORT.DIRSET=(1<<PWM_F_BIT);	//�������o��Ӱ��
#if BTL>0				//����إ��د�ޥ��ڰ��o�͂̂Ƃ�
	PWM_R_PORT.DIRSET=(1<<PWM_R_BIT);	//�t�����o��Ӱ��
#endif

	//���ߏ㏸
#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
	while(TCA0.SINGLE.CMP0BUF<PWM_STEP/2)	//PCM����0�܂ŏ㏸������
	{
		TCA0.SINGLE.CMP0BUF++;		//DC��ݸ؂���
		pwm_wait();			//�����ݸގ�����҂�
	}
#endif
//DBG_C('P');

	//RTC�ݒ�
	ccp_write_io((void*)&(CLKCTRL.OSC32KCTRLA),CLKCTRL_RUNSTDBY_bm);
						//32kOSC���펞�ғ�
	RTC.CLKSEL=RTC_CLKSEL_INT1K_gc;		//�ۯ����͓���1kHzOSC
	RTC.PITCTRLA=RTC_PERIOD_CYC32_gc|RTC_PITEN_bm;
						//PIT��1/32�����PIT����

//DBG_C('"');

#if PART_N>0				//�ٺްى��t����������Ƃ�
	//song_idx���ݸ���邽�߂̂��܂��Ȃ�
	void song_idx_dmy(void);		//song_idx�̴���
	song_idx_dmy();				//��а��ق���
#endif

	//ADC�ݒ�
	ADC0.CTRLA=0b00000001;			//10�ޯĕ���\����R���s���Ȃ��ADC�L��
	ADC0.CTRLC=0b00010011;			//��d����VDD��ۯ���1/16

	//���߰Ă���ٱ���
	PORTA.PIN0CTRL=0b00001000;
	PORTA.PIN1CTRL=0b00001000;
	PORTA.PIN2CTRL=0b00001000;
	PORTA.PIN3CTRL=0b00001000;
	PORTA.PIN4CTRL=0b00001000;
	PORTA.PIN5CTRL=0b00001000;
	PORTA.PIN6CTRL=0b00001000;
	PORTA.PIN7CTRL=0b00001000;
#ifdef PORTB
	PORTB.PIN2CTRL=0b00001000;
	PORTB.PIN3CTRL=0b00001000;
	PORTB.PIN4CTRL=0b00001000;
	PORTB.PIN5CTRL=0b00001000;
#endif
#ifdef PORTC
	PORTC.PIN0CTRL=0b00001000;
	PORTC.PIN1CTRL=0b00001000;
	PORTC.PIN2CTRL=0b00001000;
	PORTC.PIN3CTRL=0b00001000;
#endif

	//���؂̏����ݒ�(LED�ݒ�ͱ��؂̏������Ŏ��{)
	apl_init();

	//����J�n
	sei();					//�����݋���
//DBG_C('=');
}


#ifdef	SLEEP_EN			//Sleep�@�\����������Ƃ�
//==============================================
//PWM���~
//==============================================
static void dev_pwm_stop(void)
{

//DBG_C('\n');
//DBG_C('s');
	//PWM�����ݒ�~
	TCA0.SINGLE.INTCTRL=0b00000000;		//���ް�۰�����݋֎~
	pwm_wait();				//�����ݸގ�����҂�

#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
//DBG_C('1');
	while(TCA0.SINGLE.CMP0BUF)		//DC��0�܂����߉��~������
	{
		TCA0.SINGLE.CMP0BUF--;		//DC���޸؂���
		pwm_wait();			//�����ݸގ�����҂�
	}
#endif
#if BTL==1				//����؏o�͂̂Ƃ�
//DBG_C('2');
	TCA0.SINGLE.CMP0BUF=0;			//������DC��0�ɂ���
	TCA0.SINGLE.CMP1BUF=0;			//�t����DC��0�ɂ���
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b00000000;
						//�t����񔽓]�o��
	pwm_wait();				//�����ݸގ�����҂�
#endif
#if BTL>1				//��د�ޥ��ڰ��o�͂̂Ƃ�
//DBG_C('3');
	TCA0.SINGLE.CMP0BUF=0;			//������DC��0�ɂ���
	TCA0.SINGLE.CMP1BUF=0;			//�t����DC��0�ɂ���
#if BTL==3				//��ڰ��o�͂̂Ƃ�
//DBG_C('4');
	((PORT_tn *)&PWM_F_PORT)->PINnCTRL[PWM_F_BIT]=0b00000000;
						//������񔽓]�o��
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b00000000;
						//�t����񔽓]�o��
	pwm_wait();				//�����ݸގ�����҂�
#endif
#endif
//DBG_C('6');
}


//==============================================
//PWM���ĊJ
//==============================================
static void dev_pwm_start(void)
{

//DBG_C('\n');
//DBG_C('r');
#if BTL==0				//�ݸ�ُo�͂̂Ƃ�
//DBG_C('6');
	while(TCA0.SINGLE.CMP0BUF++<PWM_STEP/2)
						//DC��50%�ɂȂ�܂Ųݸ؂���
	{
		pwm_wait();			//�����ݸގ�����҂�
	}
#endif
#if BTL==1				//����؏o�͂̂Ƃ�
//DBG_C('7');
	TCA0.SINGLE.CMP0BUF=PWM_STEP/2;		//������DC��50%�ɂ���
	TCA0.SINGLE.CMP1BUF=PWM_STEP/2;		//�t����DC��50%�ɂ���
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//�t���𔽓]�o��
#endif
#if BTL==3				//��ڰ��o�͂̂Ƃ�
//DBG_C('8');
	((PORT_tn *)&PWM_F_PORT)->PINnCTRL[PWM_F_BIT]=0b10000000;
						//�����𔽓]�o��
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//�t���𔽓]�o��
#endif

	//PWM�����ݍĊJ
	TCA0.SINGLE.INTCTRL=0b00000001;		//���ް�۰�����݋���
}
#endif
