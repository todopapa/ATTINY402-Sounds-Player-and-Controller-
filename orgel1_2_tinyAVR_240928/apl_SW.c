//SW･CdS･CVDでCH32V003電子ｵﾙｺﾞｰﾙを制御するｱﾌﾟﾘｹｰｼｮﾝの共通機能部
//SW･CdS･CVDは､このｻﾝﾌﾟﾙではそれぞれ1個を実装している｡
//SWﾎﾟｰﾄのﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝは呼出し元で行っておくこと｡
//CdSﾎﾟｰﾄのﾌﾟﾙｱｯﾌﾟ制御はfunc_CdS.cで行っている｡
//CVDﾎﾟｰﾄはﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝを設定しないこと｡


//下記のｵﾌﾟｼｮﾝ設定を呼出し元で宣言しておくこと｡
//#define	SLEEP_EN	//Sleep機能を実装するときに宣言する
//#define	SHAUTO		//自動開始するときに宣言する
//#define	KYOKU_RAND	//曲番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIN_RAND	//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEII_RAND	//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIC_RAND	//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIS_RAND	//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
#define		SW_EN		//SWを実装するときに宣言する
//#define	TRG_EN	    //TRIGGER機能(piezo入力)を実装するときに宣言する
//#define	CdS_EN		//CdSを実装するときに宣言する
//#define	CVD_EN		//CVDを実装するときに宣言する


//ｵﾙｺﾞｰﾙ箱への応用では以下を宣言しておくこと
//#define	CdS_FUTA	//蓋を開ける(明)とｵﾝ判定する
//#define	CdS_THR	100	//判定閾値を固定の宣言値にする


//==============================================
//構成情報(個別ｱﾌﾟﾘｹｰｼｮﾝだけで使うもの)
//==============================================
#define	SLEEP_TMR	1000			//Sleepに入る前の時限[ms]
						//　操作の評価時間よりも長くすること


#ifdef SW_EN				//SWを実装するとき
//==============================================
//SW構成の定義
//==============================================
static const struct SW_CNF
{
	PORT_t *port;				//PORTｱﾄﾞﾚｽ
	unsigned char mode;			//b7:SWのﾓｰﾄﾞ
						//　0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ
						//b6:ﾎﾟｰﾄ入力の極性
						//　0=負論理､1=正論理
	unsigned char msk;			//ﾋﾞｯﾄﾏｽｸ
}sw_cnf[]=
{

//SW0の構成-------------------------------------
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

//SW1の構成-------------------------------------
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

//SW2の構成-------------------------------------
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

//SW3の構成-------------------------------------
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

#define	SW_REAL					//SWﾘｱﾙﾓｰﾄﾞを実装するときに宣言する
#define	SW_TIMER				//SWﾀｲﾏｰﾓｰﾄﾞを実装するときに宣言する
#include "func_SW.c"				//SW評価ﾓｼﾞｭｰﾙを呼込む
#endif

#ifdef TRG_EN				//トリガ入力を実装するとき
//==============================================
//トリガ構成の定義
//==============================================
#endif

#ifdef CdS_EN				//CdSを実装するとき
//==============================================
//CdS構成の定義
//==============================================
#include "func_CdS.c"				//CdS評価ﾓｼﾞｭｰﾙを呼込む
#endif


#ifdef CVD_EN				//CVDを実装するとき
//==============================================
//CVD構成の定義
//==============================================
static const struct CVD_CNF
{
	PORT_t *port;				//PORTｱﾄﾞﾚｽ
	unsigned char mode;			//b7:SWのﾓｰﾄﾞ(0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ)
						//b2-0:ﾋﾞｯﾄ番号
	unsigned char ain;			//AIN番号
}cvd_cnf[]=
{

//CVD0の構成-------------------------------------
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

//CVD1の構成-------------------------------------
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

//CVD2の構成-------------------------------------
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

//CVD3の構成-------------------------------------
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

#include "func_CVD.c"				//CVD評価ﾓｼﾞｭｰﾙを呼込む
#endif


//==============================================
//LEDｱｸｾｽﾏｸﾛ
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
//ﾗﾝﾀﾞﾏｲｽﾞのADC設定(PA1:A1)
//==============================================
#define	RAND_AIN		5		//AIN番号(SW2/CVD0)


//==============================================
//固有の作業域
//==============================================
#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)
static unsigned char rand_x;			//ﾗﾝﾀﾞﾏｲｽﾞの種
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
//ﾗﾝﾀﾞﾏｲｽﾞのﾋﾞｯﾄﾏｽｸﾊﾟﾀｰﾝを計算する
//==============================================
static unsigned char rand_msk(
	unsigned char no)			//実装数
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
//ﾗﾝﾀﾞﾏｲｽﾞ
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

//ﾓｰﾀｰ制御ﾎﾟｰﾄ設定  24/05/23 YM 追加
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止　(論理反転 24/05/23 YM)
	MTR_PORT.DIRSET=1<<MTR_BIT;		//出力ﾓｰﾄﾞ
	#endif

#if defined(KYOKU_RAND)||defined(ONSEIN_RAND)||defined(ONSEII_RAND)||defined(ONSEIC_RAND)||defined(ONSEIS_RAND)
	//ﾗﾝﾀﾞﾏｲｽﾞの種
//DBG_C('r');
	ADC0.MUXPOS=RAND_AIN;			//入力を設定する
	ADC0.COMMAND=0b00000001;		//変換開始
	while(ADC0.COMMAND&0b00000001);		//変換完了を待つ
	rand_x=ADC0.RES;			//変換結果を種にする

	//ﾗﾝﾀﾞﾏｲｽﾞのﾋﾞｯﾄﾏｽｸﾊﾟﾀｰﾝ設定
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

#ifdef LED_EN				//LEDを実装するとき
	//LEDﾎﾟｰﾄ設定
#ifdef LED0_BIT				//LED0を実装するとき
	LED0_PORT.DIRSET=1<<LED0_BIT;
#endif
#ifdef LED1_BIT				//LED1を実装するとき
	LED1_PORT.DIRSET=1<<LED1_BIT;
#endif
#ifdef LED2_BIT				//LED2を実装するとき
	LED2_PORT.DIRSET=1<<LED2_BIT;
#endif
#ifdef LED3_BIT				//LED3を実装するとき
	LED3_PORT.DIRSET=1<<LED3_BIT;
#endif
#ifdef LED4_BIT				//LED4を実装するとき
	LED4_PORT.DIRSET=1<<LED4_BIT;
#endif
#endif

	//SWﾎﾟｰﾄ設定
#ifdef SW_EN				//SWを実装するとき
#ifdef SW0_BIT				//SW0を実装するとき
#ifdef SW0_INV				//入力が負論理のとき
	((PORT_tn *)&SW0_PORT)->PINnCTRL[SW0_BIT]=0b00001001;
					//ﾌﾟﾙｱｯﾌﾟする､割込みする
#else					//入力が正論理(外部ﾌﾟﾙﾀﾞｳﾝ)のとき
	((PORT_tn *)&SW0_PORT)->PINnCTRL[SW0_BIT]=0b00000001;
					//ﾌﾟﾙｱｯﾌﾟしない､割込みする
#endif
#endif
#ifdef SW1_BIT				//SW1を実装するとき
#ifdef SW1_INV				//入力が負論理のとき
	((PORT_tn *)&SW1_PORT)->PINnCTRL[SW1_BIT]=0b00001001;
					//ﾌﾟﾙｱｯﾌﾟする､割込みする
#else					//入力が正論理(外部ﾌﾟﾙﾀﾞｳﾝ)のとき
	((PORT_tn *)&SW1_PORT)->PINnCTRL[SW1_BIT]=0b00000001;
					//ﾌﾟﾙｱｯﾌﾟしない､割込みする
#endif
#endif
#ifdef SW2_BIT				//SW2を実装するとき
#ifdef SW2_INV				//入力が負論理のとき
	((PORT_tn *)&SW2_PORT)->PINnCTRL[SW2_BIT]=0b00001001;
					//ﾌﾟﾙｱｯﾌﾟする､割込みする
#else					//入力が正論理(外部ﾌﾟﾙﾀﾞｳﾝ)のとき
	((PORT_tn *)&SW2_PORT)->PINnCTRL[SW2_BIT]=0b00000001;
					//ﾌﾟﾙｱｯﾌﾟしない､割込みする
#endif
#endif
#ifdef SW3_BIT				//SW3を実装するとき
#ifdef SW3_INV				//入力が負論理のとき
	((PORT_tn *)&SW3_PORT)->PINnCTRL[SW3_BIT]=0b00001001;
					//ﾌﾟﾙｱｯﾌﾟする､割込みする
#else					//入力が正論理(外部ﾌﾟﾙﾀﾞｳﾝ)のとき
	((PORT_tn *)&SW3_PORT)->PINnCTRL[SW3_BIT]=0b00000001;
					//ﾌﾟﾙｱｯﾌﾟしない､割込みする
#endif
#endif
#endif

	//CVDﾎﾟｰﾄ設定
#ifdef CVD_EN				//CVDを実装するとき
#ifdef CVD0_BIT				//CVD0を実装するとき
#ifdef CVD_EXPU				//CVDを外部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD0_PORT)->PINnCTRL[CVD0_BIT]=0b00000000;
					//内部ﾌﾟﾙｱｯﾌﾟしない
#else					//CVDを内部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD0_PORT)->PINnCTRL[CVD0_BIT]=0b00001000;
					//内部ﾌﾟﾙｱｯﾌﾟする
#endif
#endif
#ifdef CVD1_BIT				//CVD1を実装するとき
#ifdef CVD_EXPU				//CVDを外部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD1_PORT)->PINnCTRL[CVD1_BIT]=0b00000000;
					//内部ﾌﾟﾙｱｯﾌﾟしない
#else					//CVDを内部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD1_PORT)->PINnCTRL[CVD1_BIT]=0b00001000;
					//内部ﾌﾟﾙｱｯﾌﾟする
#endif
#endif
#ifdef CVD2_BIT				//CVD2を実装するとき
#ifdef CVD_EXPU				//CVDを外部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD2_PORT)->PINnCTRL[CVD2_BIT]=0b00000000;
					//内部ﾌﾟﾙｱｯﾌﾟしない
#else					//CVDを内部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD2_PORT)->PINnCTRL[CVD2_BIT]=0b00001000;
					//内部ﾌﾟﾙｱｯﾌﾟする
#endif
#endif
#ifdef CVD3_BIT				//CVD0を実装するとき
#ifdef CVD_EXPU				//CVDを外部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD3_PORT)->PINnCTRL[CVD3_BIT]=0b00000000;
					//内部ﾌﾟﾙｱｯﾌﾟしない
#else					//CVDを内部ﾌﾟﾙｱｯﾌﾟするとき
	((PORT_tn *)&CVD3_PORT)->PINnCTRL[CVD3_BIT]=0b00001000;
					//内部ﾌﾟﾙｱｯﾌﾟする
#endif
#endif
#endif

//DBG_C('%');
}


#ifdef	SLEEP_EN			//Sleep機能を実装するとき
//==============================================
//Sleep処理
//==============================================
static void apl_sleep(void)
{
	//ﾓｰﾀｰ停止;　24/05/23 追加 YM
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止　（論理反転　YM）
	#endif
#if (defined(SW0_REAL)&&defined(SW_EN))||(defined(CdS_REAL)&&defined(CdS_EN))||(defined(CVD0_REAL)&&defined(CVD_EN))
	unsigned char res;
#endif

//DBG_C('\n');
//DBG_C('<');
	//LED消灯
#ifdef LED_EN				//LEDを実装するとき
#ifdef LED0				//LED0を実装するとき
	LED0_L;
#endif
#ifdef LED1				//LED1を実装するとき
	LED1_L;
#endif
#ifdef LED2				//LED2を実装するとき
	LED2_L;
#endif
#ifdef LED3				//LED3を実装するとき
	LED3_L;
#endif
#ifdef LED4				//LED4を実装するとき
	LED4_L;
#endif
#ifdef LED5				//LED5を実装するとき
	LED5_L;
#endif
#ifdef LED6				//LED6を実装するとき
	LED6_L;
#endif
#endif

#if VOICE_S>0
	//W25をﾊﾟﾜｰﾀﾞｳﾝ
//DBG_C('a');
	W25_PWR_DOWN();				//W25をﾊﾟﾜｰﾀﾞｳﾝする
#endif

	//PWMを停止
//DBG_C('b');
	dev_pwm_stop();				//PWMを停止する

	//Sleep処理
#if defined(CdS_EN)||defined(CVD_EN)	//CdSかCVDを実装するとき
					//PITで間欠動作する
	for(;;)
	{
		//SLEEPDEEPﾓｰﾄﾞへ移行
//DBG_C('c');
DBG_SYNC();
//	DBS_H;					//Sleepを表示する
		RTC.PITINTCTRL=RTC_PITEN_bm;	//PIT割込み許可
		sleep_cpu();			//割込みが発生するまでSleepする
		RTC.PITINTCTRL=0;		//PIT割込み禁止
//	DBS_L;					//Wakeupを表示する
//DBG_C('d');

#ifdef SW_EN				//SWを実装するとき
		//SWを評価する
//DBG_C('e');
//DBG_B(sw_hst[0]);
#ifdef SW0_TIMER			//ﾀｲﾏｰﾓｰﾄﾞのとき
		sw_read(0);			//SW0を評価する
//DBG_B(sw_hst[0]);
		if(sw_hst[0])			//SW0がｵﾝになったら
		{
			sw_hst[0]--;		//履歴を巻き戻す
			break;			//Sleepから抜ける
		}
#endif
#ifdef SW0_REAL				//ﾘｱﾙﾓｰﾄﾞのとき
		res=sw_read(0);			//SW0を評価する
//DBG_B(res);
		if(res)				//変化があったら
		{
			sw_hst[0]>>=1;		//評価を巻き戻す
			break;			//Sleepから抜ける
		}
#endif
#endif

#ifdef CdS_EN				//CdSを実装するとき
		//CdSを評価する
//DBG_C('f');
//DBG_B(cds_hst);
#ifdef CdS_TIMER			//ﾀｲﾏｰﾓｰﾄﾞのとき
		cds_read();			//CdSを評価する
//DBG_B(cds_hst);
		if(cds_hst)			//CdSがｵﾝになったら
		{
			cds_hst--;		//履歴を巻き戻す
			break;			//Sleepから抜ける
		}
#endif
#ifdef CdS_REAL				//ﾘｱﾙﾓｰﾄﾞのとき
		res=cds_read();			//CdSを評価する
//DBG_B(res);
		if(res)				//変化があったら
		{
			cds_hst>>=1;		//評価を巻き戻す
			break;			//Sleepから抜ける
		}
#endif
#endif

#ifdef CVD_EN				//CVDを実装するとき
		//CVDを評価する
//DBG_C('g');
//DBG_B(cvd_hist[0].cvd_hst);
#ifdef CVD_TIMER			//ﾀｲﾏｰﾓｰﾄﾞのとき
		cvd_read(0);			//CVD0を評価する
//DBG_B(cvd_hist[0].cvd_hst);
		if(cvd_hist[0].cvd_hst)		//CVD0がｵﾝになったら
		{
			cvd_hist[0].cvd_hst--;	//評価を巻き戻す
			break;			//Sleepから抜ける
		}
#endif
#ifdef CVD_REAL				//ﾘｱﾙﾓｰﾄﾞのとき
		res=cvd_read(0);		//CVD0を評価する
//DBG_B(res);
		if(res)				//変化があったら
		{
			cvd_hist[0].cvd_hst>>=1;
						//評価を巻き戻す
			break;			//Sleepから抜ける
		}
#endif
#endif
	}

#else					//CdSもCVDも実装しないとき(TRGモード時追加　YM)
	//SLEEPDEEPﾓｰﾄﾞへ移行
//DBG_C('i');
DBG_SYNC();
	TRG_PORT.DIRCLR=1<<TRG_BIT;		//ﾄﾘｶﾞﾎﾟｰﾄを入力ﾓｰﾄﾞ
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000001;
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001001;
	//ﾄﾘｶﾞをﾌﾟﾙｱｯﾌﾟしない､割込みする（SW0でテストのためプルアップ入れる）
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000001;
	//ﾄﾘｶﾞをﾌﾟﾙｱｯﾌﾟしない､割込みする（piezoでテストのためプルアップ外す）		
	wait_ms(10);				//電圧安定時間を待つ
	PORTA.INTFLAGS=0xff;			//ﾋﾟﾝ変化割込みﾌﾗｸﾞをｸﾘｱする
	
	sleep_cpu();				//割込みが発生するまでSleepする
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00001000;
	//ﾄﾘｶﾞをﾌﾟﾙｱｯﾌﾟしない､割込みしない → SW0でテストのためプルアップする
//	((PORT_tn *)&TRG_PORT)->PINnCTRL[TRG_BIT]=0b00000000;
	//ﾄﾘｶﾞをﾌﾟﾙｱｯﾌﾟしない､割込みする（piezoでテストのためプルアップ外す）
//	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT;	//SCKを出力ﾓｰﾄﾞ（YM 0607 今回はSCKと共用ではないためコメントアウト）
//DBG_C('j');
#endif

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
	struct SONG_IDX *p;
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
	else					//稼働していないときは
	{
//DBG_C('X');
//DBG_S(sleep_tmr);
		if(++sleep_tmr>SLEEP_TMR/KOYUU_PR)
						//　Sleep時限を超えたら
		{
			apl_sleep();		//　Sleepする
			sleep_tmr=0;		//　Sleep時限をｸﾘｱする
		}
	}
#endif

	//操作ﾁｪｯｸ
	res=0;					//仮に操作無しにしておく
#ifdef SW_EN				//SWを実装するとき
//DBG_C('s');
	if(!res) res=sw_read(0);		//SW0を評価する
//DBG_B(res);
#endif
#ifdef CdS_EN
//DBG_C('c');				//CdSを実装するとき
	if(!res) res=cds_read();		//CdSを評価する
//DBG_B(res);
#endif
#ifdef CVD_EN
//DBG_C('n');				//CVDを実装するとき
	if(!res) res=cvd_read(0);		//CVD0を評価する
//DBG_B(res);
#endif

	//操作の実行
	switch(res)				//操作内容で処理する
	{
	case 0:				//操作がないとき
#ifdef SHAUTO				//自動開始するとき
//DBG_C('a');

//モータ稼働追加　24/05/23 YM
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを稼働（論理反転YM)
#endif

#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
//DBG_C('o');
//DBG_B(song.no);
		if(!song.no)			//演奏してなかったら
		{
			p=(struct SONG_IDX *)song_idx;
						//曲ｲﾝﾃﾞｯｸｽのｱﾄﾞﾚｽを得る
#ifdef KYOKU_RAND			//曲番号をﾗﾝﾀﾞﾏｲｽﾞするとき
//DBG_C('\n');
			kyoku+=(rand()&kyoku_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
			while(kyoku>p->no) kyoku-=p->no;
						//実装数内に収める
#else					//曲番号を順に進めるとき
			if(++kyoku>p->no) kyoku=1;
						//曲番号を進める
#endif
//DBG_B(kyoku);
			SONG_SEL(kyoku);    //演奏開始する
			
		}
#endif
#if VOICE_N>0				//音声N再生を実装するとき
//DBG_C('n');
//DBG_B(voiceN[0].no);
		if(!voiceN[0].no)		//再生してなかったら
		{
#ifdef ONSEIN_RAND			//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするとき
			onseiN+=(rand()&onseiN_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
			while(onseiN>VOICEN_SU) onseiN-=VOICEN_SU;
						//実装数内に収める
#else					//音声N番号を順に進めるとき
			if(++onseiN>VOICEN_SU) onseiN=1;
						//音声番号を進める
#endif
//DBG_B(onseiN);
			VOICEN_SEL(0,onseiN);	//再生開始する
		}
#endif
#if VOICE_I>0				//音声I再生を実装するとき
//DBG_C('i');
//DBG_B(voiceI.no);
		if(!voiceI.no)			//再生してなかったら
		{
#ifdef ONSEII_RAND			//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするとき
			onseiI+=(rand()&onseiI_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
			while(onseiI>VOICEI_SU) onseiI-=VOICEI_SU;
						//実装数内に収める
#else					//音声I番号を順に進めるとき
			if(++onseiI>VOICEI_SU) onseiI=1;
						//音声番号を進める
#endif
//DBG_B(onseiI);
			VOICEI_SEL(onseiI);	//再生開始する
		}
#endif
#if VOICE_C>0				//音声C再生を実装するとき
//DBG_C('c');
//DBG_B(voiceC.no);
		if(!voiceC.no)			//再生してなかったら
		{
#ifdef ONSEIC_RAND			//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするとき
			onseiC+=(rand()&onseiC_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
			while(onseiC>VOICEC_SU) onseiC-=VOICEC_SU;
						//実装数内に収める
#else					//音声C番号を順に進めるとき
			if(++onseiC>VOICEC_SU) onseiC=1;
						//音声番号を進める
#endif
//DBG_B(onseiC);
			VOICEC_SEL(onseiC);	//再生開始する
		}
#endif
#if VOICE_S>0				//音声S再生を実装するとき
//DBG_C('s');
//DBG_B(voiceS.no);
		if(!voiceS.no)			//再生してなかったら
		{
#ifdef ONSEIS_RAND			//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするとき
			onseiS+=(rand()&onseiS_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
			while(onseiS>VOICES_SU) onseiS-=VOICES_SU;
						//実装数内に収める
#else					//音声S番号を順に進めるとき
			if(++onseiS>VOICES_SU) onseiS=1;
						//音声番号を進める
#endif
//DBG_B(onseiS);
			VOICES_SEL(onseiS);	//再生開始する
		}
#endif
#endif
		break;
	case 1:				//短ｵﾝ検知のとき
	
//モータ稼働追加　24/05/23 YM
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
MTR_PORT.OUTSET=1<<MTR_BIT;		//ﾓｰﾀｰを稼働（論理反転 YM)
#endif

#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
		p=(struct SONG_IDX *)song_idx;	//曲ｲﾝﾃﾞｯｸｽのｱﾄﾞﾚｽを得る
#ifdef KYOKU_RAND			//曲番号をﾗﾝﾀﾞﾏｲｽﾞするとき
//DBG_C('\n');
		kyoku+=(rand()&kyoku_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
//DBG_B(kyoku);
		while(kyoku>p->no) kyoku-=p->no;//実装数内に収める
//DBG_B(kyoku);
#else					//曲番号を順に進めるとき
		if(++kyoku>p->no) kyoku=1;	//曲番号を進める
#endif
//DBG_B(kyoku);
		SONG_SEL(kyoku);		//演奏開始する
#endif
#if VOICE_N>0				//音声N再生を実装するとき
#ifdef ONSEIN_RAND			//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするとき
		onseiN+=(rand()&onseiN_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
		while(onseiN>VOICEN_SU) onseiN-=VOICEN_SU;
						//実装数内に収める
#else					//音声N番号を順に進めるとき
		if(++onseiN>VOICEN_SU) onseiN=1;
						//音声番号を進める
#endif
//DBG_B(onseiN);
		VOICEN_SEL(0,onseiN);		//再生開始する
#endif
#if VOICE_I>0				//音声I再生を実装するとき
#ifdef ONSEII_RAND			//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするとき
		onseiI+=(rand()&onseiI_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
		while(onseiI>VOICEI_SU) onseiI-=VOICEI_SU;
						//実装数内に収める
#else					//音声I番号を順に進めるとき
		if(++onseiI>VOICEI_SU) onseiI=1;
						//音声番号を進める
#endif
//DBG_B(onseiI);
		VOICEI_SEL(onseiI);		//再生開始する
#endif
#if VOICE_C>0				//音声C再生を実装するとき
#ifdef ONSEIC_RAND			//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするとき
		onseiC+=(rand()&onseiC_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
		while(onseiC>VOICEC_SU) onseiC-=VOICEC_SU;
						//実装数内に収める
#else					//音声C番号を順に進めるとき
		if(++onseiC>VOICEC_SU) onseiC=1;
						//音声番号を進める
#endif
//DBG_B(onseiC);
		VOICEC_SEL(onseiC);		//再生開始する
#endif
#if VOICE_S>0				//音声S再生を実装するとき
#ifdef ONSEIS_RAND			//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするとき
//DBG_C('\n');
		onseiS+=(rand()&onseiS_rand_msk)+1;
						//ﾗﾝﾀﾞﾑに増加する
//DBG_B(onseiS);
		while(onseiS>VOICES_SU) onseiS-=VOICES_SU;
						//実装数内に収める
#else					//音声S番号を順に進めるとき
		if(++onseiS>VOICES_SU) onseiS=1;
						//音声番号を進める
//DBG_B(onseiS);
#endif
//DBG_B(onseiS);
		VOICES_SEL(onseiS);		//再生開始する
#endif
		break;
	case 2:				//長ｵﾝ一致のとき
	
//ﾓｰﾀｰ停止;　24/05/23 追加 YM
#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
#endif
	
#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
		SONG_SEL(0);			//演奏中断する
#endif
#if VOICE_N>0				//音声N再生を実装するとき
		VOICEN_SEL(0,0);		//再生中断する
#endif
#if VOICE_I>0				//音声I再生を実装するとき
		VOICEI_SEL(0);			//再生中断する
#endif
#if VOICE_C>0				//音声C再生を実装するとき
		VOICEC_SEL(0);			//再生中断する
#endif
#if VOICE_S>0				//音声S再生を実装するとき
		VOICES_SEL(0);			//再生中断する
#endif
		break;
	}

	//LED点滅
#if PART_N>0				//ｵﾙｺﾞｰﾙ演奏を実装するとき
	if(song.no)				//演奏中のとき
	{
#ifdef LED_EN				//LEDを実装するとき
#ifdef LED0_BIT				//LED0を実装するとき
		if(part[0].onpu_cd&0x0001) LED0_H;
		else LED0_L;
#endif
#ifdef LED1_BIT				//LED1を実装するとき
		if(part[0].onpu_cd&0x0002) LED1_H;
		else LED1_L;
#endif
#ifdef LED2_BIT				//LED2を実装するとき
		if(part[0].onpu_cd&0x0004) LED2_H;
		else LED2_L;
#endif
#ifdef LED3_BIT				//LED3を実装するとき
		if(part[0].onpu_cd&0x0008) LED3_H;
		else LED3_L;
#endif
#ifdef LED4_BIT				//LED4を実装するとき
		if(part[0].onpu_cd&0x0010) LED4_H;
		else LED_L;
#endif
#ifdef LED5_BIT				//LED5を実装するとき
#if PART_N==1				//1ﾊﾟｰﾄのみ実装するとき
		if(part[0].onpu_cd&0x0020) LED5_H;
		else LED5_L;
#else					//2ﾊﾟｰﾄ以上実装するとき
		if(part[1].onpu_cd&0x0001) LED5_H;
		else LED_L;
#endif
#endif
#ifdef LED6_BIT				//LED6を実装するとき
#if PART_N==1				//1ﾊﾟｰﾄのみ実装するとき
		if(part[0].onpu_cd&0x0040) LED6_H;
		else LED6_L;
#else					//2ﾊﾟｰﾄ以上実装するとき
		if(part[1].onpu_cd&0x0002) LED6_H;
		else LED6_L;
#endif
#endif
#endif
	}
#endif
}


#if	PART_N>0			//ｵﾙｺﾞｰﾙ演奏を実装するとき
//==============================================
//演奏終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_SONG_END(void)
{
	//モータ停止を追加 24/05/23 YM
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
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
	//モータ停止を追加 24/05/23 YM
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
	#endif
}
#endif


#if	VOICE_I>0			//音声I再生を実装するとき
//==============================================
//音声I再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEI_END(void)
{
	//モータ停止を追加 24/05/23 YM
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
	#endif
}
#endif


#if	VOICE_C>0			//音声C再生を実装するとき
//==============================================
//音声C再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICEC_END(void)
{
	//モータ停止を追加 24/05/23 YM
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
	#endif
}
#endif


#if	VOICE_S>0			//音声S再生を実装するとき
//==============================================
//音声S再生終了時の処理(ｺｰﾙﾊﾞｯｸ関数)
//==============================================
static void CB_VOICES_END(void)
{
	//モータ停止を追加 24/05/23 YM
	#ifdef MTR_BIT				//ﾓｰﾀｰ制御ﾎﾟｰﾄが実装されているとき
	MTR_PORT.OUTCLR=1<<MTR_BIT;		//ﾓｰﾀｰを停止（論理反転 YM)
	#endif
}
#endif
