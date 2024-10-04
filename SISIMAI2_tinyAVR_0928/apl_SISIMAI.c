//==============================================
//構成情報(個別ｱﾌﾟﾘｹｰｼｮﾝだけで使うもの)
//==============================================
//#define	SLEEP_TMR	100			//Sleepに入る前の時限[ms]
#define	SLEEP_TMR	4000			//Sleepに入る前の時限[ms]
						//　操作の評価時間よりも長くすること (動作を拾うときは長くすること）
						
//==============================================
//ﾋﾟﾝ変化割込みﾊﾝﾄﾞﾗ
//==============================================
ISR(PORTA_PORT_vect)
{
	PORTA.INTFLAGS=0xff;			//ﾋﾟﾝ変化割込みﾌﾗｸﾞをｸﾘｱする
}

#ifdef PORTB				//PORTBが実在するとき
ISR(PORTB_PORT_vect)
{
	PORTB.INTFLAGS=0xff;			//ﾋﾟﾝ変化割込みﾌﾗｸﾞをｸﾘｱする
}
#endif


//==============================================
//ｱﾌﾟﾘの初期設定
//==============================================
static void apl_init(void)
{

//DBG_C('\n');
//DBG_C('$');

	//ﾓｰﾀｰ制御ﾎﾟｰﾄ設定
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
//	MTR_PORT.DIRCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
}


#ifdef	SLEEP_EN			//Sleep機能を実装するとき
//==============================================
//Sleep処理
//==============================================
static void apl_sleep(void)
{
//DBG_C('\n');
//DBG_C('<');
	//ﾓｰﾀｰ停止;
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
    MTR_PORT.DIRSET=1<<MTR_BIT;     // MTR_BITを出力ポートに設定する
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
    MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif

#if VOICE_S>0
	//W25をﾊﾟﾜｰﾀﾞｳﾝ
//DBG_C('a');
	W25_PWR_DOWN();				//W25をﾊﾟﾜｰﾀﾞｳﾝする
#endif

	//PWMを停止
//DBG_C('b');
	dev_pwm_stop();				//PWMを停止する
	
//トリガポートを割り込み禁止
	TRG_PORT.DIRSET=1<<TRG_BIT;		//ﾄﾘｶﾞﾎﾟｰﾄを出力ﾓｰﾄﾞ
((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
//トリガポートの割り込みをクリア
PORTA.INTFLAGS=0xff;			//ﾋﾟﾝ変化割込みﾌﾗｸﾞをｸﾘｱする
	
//SLEEPDEEPﾓｰﾄﾞへ移行
//DBG_C('i');
DBG_SYNC();
	TRG_PORT.DIRCLR=1<<TRG_BIT;		//ﾄﾘｶﾞﾎﾟｰﾄを入力ﾓｰﾄﾞ
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000001;
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001001;
						//ﾄﾘｶﾞをﾌﾟﾙｱｯﾌﾟしない､割込みする(テストでプルアップ）
	wait_ms(10);				//電圧安定時間を待つ
	PORTA.INTFLAGS=0xff;			//ﾋﾟﾝ変化割込みﾌﾗｸﾞをｸﾘｱする
#ifdef PORTB				//PORTBが実在するとき
	PORTB.INTFLAGS=0xff;			//ﾋﾟﾝ変化割込みﾌﾗｸﾞをｸﾘｱする
#endif
	sleep_cpu();				//割込みが発生するまでSleepする
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001000;
						//ﾄﾘｶﾞをﾌﾟﾙｱｯﾌﾟしない､割込みしない(テストでプルアップ）
//	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT;	//SCKを出力ﾓｰﾄﾞ（YM 今回はSCKと共用ではないためコメントアウト）
	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT;	//SCKを出力ﾓｰﾄﾞ（YM 0725はSCKと共用にするため復活）
//DBG_C('j');

	//PWMを再稼働
//DBG_C('l');
	dev_pwm_start();			//PWMを開始する

	//W25をﾊﾟﾜｰｱｯﾌﾟ
#if	VOICE_S>0
//DBG_C('m');
	W25_PWR_UP();				//W25をﾊﾟﾜｰｱｯﾌﾟする
#endif
//DBG_C('>');
}
#endif


//==============================================
//固有の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_KOYUU(void)
{
#ifdef SLEEP_EN				//Sleep機能を実装するとき
	static unsigned short sleep_tmr=0;	//Sleepﾀｲﾏｰ
#endif
	unsigned char res;
#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
	static unsigned char kyoku;		//曲番号
#endif
#if VOICE_N>0				//音声N再生を実装するとき
	static unsigned char onseiN;		//音声N番号
#endif
#if VOICE_I>0				//音声I再生を実装するとき
	static unsigned char onseiI;		//音声I番号
#endif
#if VOICE_C>0				//音声C再生を実装するとき
	static unsigned short onseiC;		//音声C番号
#endif
#if VOICE_S>0				//音声S再生を実装するとき
	static unsigned short onseiS;		//音声S番号
#endif

//DBG_C('\n');
//DBG_C('k');

	//稼働ﾁｪｯｸ
#ifdef SLEEP_EN				//Sleep機能を実装するとき
//DBG_C('e');
	res=0;					//仮に非稼働にしておく
#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
	res|=song.no;				//稼働しているときは稼働中の設定
#endif
#if VOICE_N>0				//音声N再生を実装するとき
	res|=voiceN[0].no;			//稼働しているときは稼働中の設定
#endif
#if VOICE_I>0				//音声I再生を実装するとき
	res|=voiceI.no;				//稼働しているときは稼働中の設定
#endif
#if VOICE_C>0				//音声C再生を実装するとき
	res|=voiceC.no;				//稼働しているときは稼働中の設定
#endif
#if VOICE_S>0				//音声S再生を実装するとき
	res|=voiceS.no;				//稼働しているときは稼働中の設定
#endif
//DBG_B(res);
	if(res)					//稼働しているときは
	{
		sleep_tmr=0;			//　Sleep時限をｸﾘｱする
	}
//DBG_C('X');
//DBG_S(sleep_tmr);
	if(++sleep_tmr<SLEEP_TMR/KOYUU_PR) return;
					//　Sleep時限が未満了のときは戻る
	apl_sleep();			//　Sleepする
	sleep_tmr=0;			//　Sleep時限をｸﾘｱする
#endif

#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
//DBG_B(song.no);
	song_idx=(struct SONG_IDX *)((unsigned short)song_idx|0x8000);
						//ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭへ位置付ける
//DBG_S(song_idx);
//DBG_D(song_idx,16);
	if(++kyoku>song_idx->no) kyoku=1;	//音声番号を進める
	SONG_SEL(kyoku);			//演奏開始する
#endif
#if VOICE_N>0	
					//音声N再生を実装するとき
	if(++onseiN>VOICEN_SU) onseiN=1;	//音声番号を進める
	VOICEN_SEL(0,onseiN);			//再生開始する
#endif
#if VOICE_I>0				//音声I再生を実装するとき
	if(++onseiI>VOICEI_SU) onseiI=1;	//音声番号を進める
	VOICEI_SEL(onseiI);			//再生開始する
#endif
#if VOICE_C>0				//音声C再生を実装するとき
	if(++onseiC>VOICEC_SU) onseiC=1;	//音声番号を進める
	VOICEC_SEL(onseiC);			//再生開始する
#endif
#if VOICE_S>0				//音声S再生を実装するとき
	if(++onseiS>VOICES_SU) onseiS=1;	//音声番号を進める
	VOICES_SEL(onseiS);			//再生開始する
#endif

#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
//	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを稼働
	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを稼働(論理反転YM)
#endif
}


#if	PART_N>0			//ｵﾙｺﾞｰﾙ演奏を実装するとき
//==============================================
//演奏終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_SONG_END(void)
{
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
}
#endif


#if	VOICE_N>0			//音声N再生を実装するとき
//==============================================
//音声0再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEN_END(
	unsigned char ch)			//音声Nのch番号
{
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
}
#endif


#if	VOICE_I>0			//音声I再生を実装するとき
//==============================================
//音声I再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEI_END(void)
{
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
}
#endif


#if	VOICE_C>0			//音声C再生を実装するとき
//==============================================
//音声C再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEC_END(void)
{
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
}
#endif


#if	VOICE_S>0			//音声S再生を実装するとき
//==============================================
//音声S再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICES_END(void)
{
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
//	MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを停止
	MTR_PORT.DIRCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
}
#endif
