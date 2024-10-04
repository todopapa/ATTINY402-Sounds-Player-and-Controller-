//==============================================
//TCA0ｵｰﾊﾞﾌﾛｰ(PWM周期)割込みﾊﾝﾄﾞﾗ
//・ﾊﾞｯﾌｧｱﾝﾀﾞｰﾗﾝ時はDCを更新しない(前回の値が継続する)
//==============================================
ISR(TCA0_OVF_vect)
{
	short data;

//DBS_H;
//DBG_C('[');
	TCA0.SINGLE.INTFLAGS=0b00000001;	//ｵｰﾊﾞｰﾌﾛｰ割込みﾌﾗｸﾞをｸﾘｱ

	//ﾃﾞｰﾀを取得
	if(buf_read==buf_write) return;		//ﾃﾞｰﾀが無かったら戻る
	data=buf[buf_read];			//ﾃﾞｰﾀを取出す
//DBG_S(data);
	if(buf_read==(OUT_BUF_N-1)) buf_read=0;	//ﾊﾞｯﾌｧの後尾になったら先頭に戻す
	else buf_read++;			//ﾊﾞｯﾌｧを進める

	//ﾃﾞｭｰﾃｨを更新
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
	TCA0.SINGLE.CMP0BUF=PWM_STEP/2+data;	//正相を設定
//DBG_S(TCA0.SINGLE.CMP0BUF);
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
	TCA0.SINGLE.CMP0BUF=data;		//正相を設定
//DBG_S(TCA0.SINGLE.CMP0BUF);
	TCA0.SINGLE.CMP1BUF=data;		//逆相を設定
//DBG_S(TCA0.SINGLE.CMP1BUF);
#endif
#if BTL>1				//ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
	if(data<0)				//負ﾚﾍﾞﾙのとき
	{
		TCA0.SINGLE.CMP0BUF=0;		//正相を止める
		TCA0.SINGLE.CMP1BUF=(-data)*2;	//逆相を設定
	}
	else					//正ﾚﾍﾞﾙのとき
	{
		TCA0.SINGLE.CMP1BUF=0;		//逆相を止める
		TCA0.SINGLE.CMP0BUF=data*2;	//正相を設定
	}
//DBG_S(TCA0.SINGLE.CMP0BUF);
//DBG_S(TCA0.SINGLE.CMP1BUF);
#endif
//DBG_C(']');
//DBS_L;
}


//==============================================
//PWM周期を待つ
//==============================================
void pwm_wait(void)
{

	TCA0.SINGLE.INTFLAGS=0b00000001;	//TCA0ｵｰﾊﾞｰﾌﾛｰ割込みﾌﾗｸﾞをｸﾘｱ
	while(!(TCA0.SINGLE.INTFLAGS&0b00000001));
						//PWM周期満了を待つ
}


//==============================================
//PIT割込みﾊﾝﾄﾞﾗ
//==============================================
ISR(RTC_PIT_vect)
{

	RTC.PITINTFLAGS=RTC_PI_bm;		//PIT割込みﾌﾗｸﾞをｸﾘｱ
}


//==============================================
//固有の初期設定
//==============================================
static void CB_INIT(void)
{

	//ｼｽﾃﾑ設定
	ccp_write_io((void*)&(CLKCTRL.MCLKCTRLB),0);
						//OSCﾌﾟﾘｽｹ無し(主ｸﾛｯｸ16MHz)
						//　ﾋｭｰｽﾞで16MHzｸﾛｯｸを選択しておくこと
	SLPCTRL.CTRLA=0b00000101;		//ﾊﾟﾜｰﾀﾞｳﾝﾓｰﾄﾞ､Sleep許可

	//ﾃﾞﾊﾞｸﾞ設定
#ifdef SHDBG
	dbg_init();				//ﾃﾞﾊﾞｸﾞ情報を初期化する
#endif
#ifdef SHDBS
	dbs_init();				//ﾃﾞﾊﾞｸﾞ信号を初期化する
#endif


////////////////////////////////////////////////
//ｿﾌﾄ待ち時間調整
//for(;;){DBS_H;wait_us(26);DBS_L;wait_us(26);}
//wait_ms(10);for(;;){DBG_C('U');}
////////////////////////////////////////////////


	//I2Cﾎﾟｰﾄ設定
#if VOICE_I>0				//I2Cを使うとき
#ifdef I2C_SOFT				//I2Cをｿﾌﾄ実装するとき
	I2C_SCL_PU;				//SCLをﾌﾟﾙｱｯﾌﾟする
	I2C_SDA_PU;				//SDAをﾌﾟﾙｱｯﾌﾟする
#else					//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
	PORTMUX.CTRLB=0b00010000;		//TWI0を代替ﾋﾟﾝ(SCL:PA2､SDA:PA1)へ振る
	TWI0.MBAUD=20;				//400kbps(20MHz/(2*0.4)-5=20)
	TWI0.MCTRLB=TWI_FLUSH_bm;		//内部ｽﾃｰﾄをｸﾘｱする
	TWI0.MCTRLA=0b00000001;			//I2C有効
//DBG_B(TWI0.MSTATUS);
	TWI0.MSTATUS|=TWI_BUSSTATE_IDLE_gc;	//ﾊﾞｽをｱｲﾄﾞﾙにする
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm|TWI_BUSERR_bm);
						//ﾌﾗｸﾞをｸﾘｱする
//DBG_B(TWI0.MSTATUS);
#endif
#endif

	//SPIﾎﾟｰﾄ設定
#if VOICE_C+VOICE_S>0			//SPIを使うとき
	SPI_SS_OUT;				//SSを出力ﾓｰﾄﾞ
	SPI_MISO_IN;				//MISOをﾌﾟﾙﾀﾞｳﾝ入力ﾓｰﾄﾞ
	SPI_SCK_OUT;				//SCKを出力ﾓｰﾄﾞ
	SPI_MOSI_OUT;				//MOSIを出力ﾓｰﾄﾞ
#ifndef SPI_SOFT			//内蔵SPIﾓｼﾞｭｰﾙを使うとき
	SPI0.CTRLB=0b00000101;			//ｽﾚｰﾌﾞ選択禁止､MODE1
	SPI0.CTRLA=0b00110011;			//ﾏｽﾀｰ､SPI有効
#endif
#endif

	//PWM(TCA0)設定
#if BTL==2				//ﾌﾞﾘｯｼﾞ出力のとき
	TCA0.SINGLE.PER=PWM_STEP+PWM_DB;	//PWM周期=32.125us+ﾃﾞｯﾄﾞﾊﾞﾝﾄﾞ
#else					//ｼﾝｸﾞﾙ･ｺﾝﾌﾟﾘ･ﾌﾞﾚｰｷ出力のとき
	TCA0.SINGLE.PER=PWM_STEP;		//PWM周期=32.125us
#endif
#ifdef PWM_SLOW				//PWMを極端に遅くするとき
	TCA0.SINGLE.CTRLA=0b00001111;		//ｸﾛｯｸ分周1/1024(ﾃﾞﾊﾞｸﾞ用)､TCA許可
#else
	TCA0.SINGLE.CTRLA=0b00000001;		//ｸﾛｯｸ分周無し､TCA許可
#endif
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
	TCA0.SINGLE.CTRLB=0b00010011;		//正相(WO0)を出力､ｼﾝｸﾞﾙｽﾛｰﾌﾟ動作
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
	TCA0.SINGLE.CMP0BUF=PWM_STEP/2;		//正相のDCを1/2に設定
	TCA0.SINGLE.CMP1BUF=PWM_STEP/2;		//逆相のDCを1/2に設定
	TCA0.SINGLE.CTRLB=0b00110011;		//正相(WO0)と逆相(WO1)を出力､ｼﾝｸﾞﾙｽﾛｰﾌﾟ動作
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//逆相を反転出力
#endif
#if BTL>1				//ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
	TCA0.SINGLE.CMP0BUF=0;			//正相のDCを0に設定
	TCA0.SINGLE.CMP1BUF=0;			//逆相のDCを0に設定
	TCA0.SINGLE.CTRLB=0b00110011;		//正相と逆相を出力､ｼﾝｸﾞﾙｽﾛｰﾌﾟ動作
#endif
#if BTL==3				//ﾌﾞﾘｯｼﾞ出力のとき
	((PORT_tn *)&PWM_F_PORT)->PINnCTRL[PWM_F_BIT]=0b10000000;
						//正相を反転出力
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//逆相を反転出力
#endif
	TCA0.SINGLE.INTCTRL=0b00000001;		//ｵｰﾊﾞｰﾌﾛｰ割込み許可

	//PWMﾎﾟｰﾄを出力設定
	PWM_F_PORT.DIRSET=(1<<PWM_F_BIT);	//正相を出力ﾓｰﾄﾞ
#if BTL>0				//ｺﾝﾌﾟﾘ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
	PWM_R_PORT.DIRSET=(1<<PWM_R_BIT);	//逆相を出力ﾓｰﾄﾞ
#endif

	//ﾗﾝﾌﾟ上昇
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
	while(TCA0.SINGLE.CMP0BUF<PWM_STEP/2)	//PCMﾚﾍﾞﾙ0まで上昇させる
	{
		TCA0.SINGLE.CMP0BUF++;		//DCをｲﾝｸﾘする
		pwm_wait();			//ｻﾝﾌﾟﾘﾝｸﾞ周期を待つ
	}
#endif
//DBG_C('P');

	//RTC設定
	ccp_write_io((void*)&(CLKCTRL.OSC32KCTRLA),CLKCTRL_RUNSTDBY_bm);
						//32kOSCを常時稼働
	RTC.CLKSEL=RTC_CLKSEL_INT1K_gc;		//ｸﾛｯｸ源は内部1kHzOSC
	RTC.PITCTRLA=RTC_PERIOD_CYC32_gc|RTC_PITEN_bm;
						//PITは1/32分周､PIT許可

//DBG_C('"');

#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
	//song_idxをﾘﾝｸするためのおまじない
	void song_idx_dmy(void);		//song_idxのｴﾝﾄﾘ
	song_idx_dmy();				//ﾀﾞﾐｰｺｰﾙする
#endif

	//ADC設定
	ADC0.CTRLA=0b00000001;			//10ﾋﾞｯﾄ分解能､自由走行しない､ADC有効
	ADC0.CTRLC=0b00010011;			//基準電圧はVDD､ｸﾛｯｸは1/16

	//空きﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟ
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

	//ｱﾌﾟﾘの初期設定(LED設定はｱﾌﾟﾘの初期化で実施)
	apl_init();

	//動作開始
	sei();					//割込み許可
//DBG_C('=');
}


#ifdef	SLEEP_EN			//Sleep機能を実装するとき
//==============================================
//PWMを停止
//==============================================
static void dev_pwm_stop(void)
{

//DBG_C('\n');
//DBG_C('s');
	//PWM割込み停止
	TCA0.SINGLE.INTCTRL=0b00000000;		//ｵｰﾊﾞｰﾌﾛｰ割込み禁止
	pwm_wait();				//ｻﾝﾌﾟﾘﾝｸﾞ周期を待つ

#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//DBG_C('1');
	while(TCA0.SINGLE.CMP0BUF)		//DCを0までﾗﾝﾌﾟ下降させる
	{
		TCA0.SINGLE.CMP0BUF--;		//DCをﾃﾞｸﾘする
		pwm_wait();			//ｻﾝﾌﾟﾘﾝｸﾞ周期を待つ
	}
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
//DBG_C('2');
	TCA0.SINGLE.CMP0BUF=0;			//正相のDCを0にする
	TCA0.SINGLE.CMP1BUF=0;			//逆相のDCを0にする
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b00000000;
						//逆相を非反転出力
	pwm_wait();				//ｻﾝﾌﾟﾘﾝｸﾞ周期を待つ
#endif
#if BTL>1				//ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
//DBG_C('3');
	TCA0.SINGLE.CMP0BUF=0;			//正相のDCを0にする
	TCA0.SINGLE.CMP1BUF=0;			//逆相のDCを0にする
#if BTL==3				//ﾌﾞﾚｰｷ出力のとき
//DBG_C('4');
	((PORT_tn *)&PWM_F_PORT)->PINnCTRL[PWM_F_BIT]=0b00000000;
						//正相を非反転出力
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b00000000;
						//逆相を非反転出力
	pwm_wait();				//ｻﾝﾌﾟﾘﾝｸﾞ周期を待つ
#endif
#endif
//DBG_C('6');
}


//==============================================
//PWMを再開
//==============================================
static void dev_pwm_start(void)
{

//DBG_C('\n');
//DBG_C('r');
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//DBG_C('6');
	while(TCA0.SINGLE.CMP0BUF++<PWM_STEP/2)
						//DCが50%になるまでｲﾝｸﾘする
	{
		pwm_wait();			//ｻﾝﾌﾟﾘﾝｸﾞ周期を待つ
	}
#endif
#if BTL==1				//ｺﾝﾌﾟﾘ出力のとき
//DBG_C('7');
	TCA0.SINGLE.CMP0BUF=PWM_STEP/2;		//正相のDCを50%にする
	TCA0.SINGLE.CMP1BUF=PWM_STEP/2;		//逆相のDCを50%にする
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//逆相を反転出力
#endif
#if BTL==3				//ﾌﾞﾚｰｷ出力のとき
//DBG_C('8');
	((PORT_tn *)&PWM_F_PORT)->PINnCTRL[PWM_F_BIT]=0b10000000;
						//正相を反転出力
	((PORT_tn *)&PWM_R_PORT)->PINnCTRL[PWM_R_BIT]=0b10000000;
						//逆相を反転出力
#endif

	//PWM割込み再開
	TCA0.SINGLE.INTCTRL=0b00000001;		//ｵｰﾊﾞｰﾌﾛｰ割込み許可
}
#endif
