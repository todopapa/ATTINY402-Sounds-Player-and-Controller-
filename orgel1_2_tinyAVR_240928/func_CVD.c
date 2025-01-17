//CVDを評価する機能ﾓｼﾞｭｰﾙ
//
//CVDを内部ﾌﾟﾙｱｯﾌﾟすると検知感度が低いので､100kΩ外部ﾌﾟﾙｱｯﾌﾟを推奨する｡
//その場合は CVD_EXPU を宣言する｡
//
//CVDの構成を下記の例に倣って､呼出し元にて定義しておくこと｡
//
//CVDは複数個を実装可能｡CVD毎にﾎﾟｰﾄﾚｼﾞｽﾀが違ってもよい｡
//
//CVDのｵﾝとは､ﾀｯﾁした状態｡
//CVDのｵﾌとは､ﾀｯﾁしない状態｡
//
//CVDの評価は以下の2つのﾓｰﾄﾞがある｡
//・ﾘｱﾙﾓｰﾄﾞ
//　規定期間内のﾊﾞﾀﾂｷは無視する｡
//　状態が変化したときに変化の状況を返す｡
//　戻り値は､0=変化の検知なし､1=ｵﾌからｵﾝへの変化を検知､2=ｵﾝからｵﾌへの変化を検知｡
//・ﾀｲﾏｰﾓｰﾄﾞ
//　ｵﾝの継続時間が短ｵﾝ閾値になったら短ｵﾝ一致とする｡
//　ｵﾝの継続時間が長ｵﾝ閾値になったら長ｵﾝ一致とする｡
//　ｵﾝからｵﾌへ変化したときに､ｵﾝ状態であった時間が短ｵﾝ閾値超えのときは短ｵﾝ検知とする｡
//　戻り値は､0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ一致､3=短ｵﾝ一致｡
//ﾘｱﾙﾓｰﾄﾞとﾀｲﾏｰﾓｰﾄﾞは排他的で､1つのCVDに対してどちらか1つのﾓｰﾄﾞを指定できる｡
//
//CVDを評価する場合は､このﾓｼﾞｭｰﾙを#includeする｡
//ﾘｱﾙﾓｰﾄﾞで評価するときは､CVD_REALを宣言する｡
//ﾀｲﾏｰﾓｰﾄﾞで評価するときは､CVD_TIMERを宣言する｡
//Sleep関連の処理にこのﾓｼﾞｭｰﾙは関与しない｡


//==============================================
//CVD構成の定義例
//==============================================
//#define	CVD_REAL			//CVDﾘｱﾙﾓｰﾄﾞを実装するときに宣言する
//#define	CVD_TIMER			//CVDﾀｲﾏｰﾓｰﾄﾞを実装するときに宣言する

//CVDの構成--------------------------------------
//static const struct CVD_CNF
//{
//	PORT_t *port;				//PORTｱﾄﾞﾚｽ
//	unsigned char mode;			//b7:SWのﾓｰﾄﾞ
//						//　0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ
//						//b2-0:ﾋﾞｯﾄ番号
//	unsigned char ain;			//AIN番号
//} cvd_cnf[]=
//{
//CVD0の構成-------------------------------------
//	{GPIOA,0x000000f0,0x02,1,0x80},		//PA1､A1､ﾀｲﾏｰﾓｰﾄﾞ
//CVD1の構成-------------------------------------
//	{GPIOD,0x0f000000,0x40,6,0x00},		//PD6､A6､ﾘｱﾙﾓｰﾄﾞ
//CVD2の構成-------------------------------------
//	{GPIOD,0x00f00000,0x20,5,0x00},		//PD5､A5､ﾘｱﾙﾓｰﾄﾞ
//CVD3の構成-------------------------------------
//	{GPIOD,0x000f0000,0x10,7,0x00},		//PD4､A7､ﾘｱﾙﾓｰﾄﾞ
//};

#define	CVD_SU	(sizeof(cvd_cnf)/sizeof(cvd_cnf[0]))
						//CVDの実装数

//==============================================
//CVD評価の閾値等
//==============================================
#ifdef	CVD_EXPU			//CVDを外部ﾌﾟﾙｱｯﾌﾟするとき
#ifndef	CVD_CNT				//評価の回数宣言されていないとき
#define	CVD_CNT		8			//　評価の回数を宣言する
#endif
#ifndef	CVD_THR1			//評価の閾値1が宣言されていないとき
#define	CVD_THR1	10			//　閾値1を宣言する
#endif
#ifndef	CVD_THR2			//評価の閾値2が宣言されていないとき
#define	CVD_THR2	20			//　閾値2を宣言する
#endif
#ifndef	CVD_INC				//移動平均計算の増分値が宣言されていないとき
#define	CVD_INC		1			//　増分値を宣言する
#endif
#ifndef	CVD_WAIT			//ｻﾝﾌﾟﾘﾝｸﾞ待ち時間が宣言されていないとき
#define	CVD_WAIT	3	//100kΩ想定	//　ｻﾝﾌﾟﾘﾝｸﾞ待ち時間を宣言する
#endif
#else					//CVDを内部ﾌﾟﾙｱｯﾌﾟするとき
#ifndef	CVD_CNT				//評価の回数宣言されていないとき
#define	CVD_CNT		8			//　評価の回数を宣言する
#endif
#ifndef	CVD_THR1			//評価の閾値1が宣言されていないとき
#define	CVD_THR1	10			//　閾値1を宣言する
#endif
#ifndef	CVD_THR2			//評価の閾値2が宣言されていないとき
#define	CVD_THR2	20			//　閾値2を宣言する
#endif
#ifndef	CVD_INC				//移動平均計算の増分値が宣言されていないとき
#define	CVD_INC		3			//　増分値を宣言する
#endif
#ifndef	CVD_WAIT			//Aｻﾝﾌﾟﾘﾝｸﾞ待ち時間が宣言されていないとき
#define	CVD_WAIT	0			//　ｻﾝﾌﾟﾘﾝｸﾞ待ち時間を宣言する
#endif
#endif

//ﾘｱﾙﾓｰﾄﾞの設定値
#ifndef	CVD_HST_BIT			//ﾊﾞﾀﾂｷ除去期間[評価周期](1〜7の範囲)が
					//　宣言されていないとき
#define	CVD_HST_BIT	3			//　ﾊﾞﾀﾂｷ除去期間を宣言する
#endif
#define	CVD_HST_MSK	((1<<(CVD_HST_BIT+1))-1)//履歴判定ﾋﾞｯﾄﾏｽｸ
#define	CVD_HST_ON	((1<<CVD_HST_BIT)-1)	//履歴ｵﾝ変化判定値
#define	CVD_HST_OFF	((1<<(CVD_HST_BIT+1))-2)//履歴ｵﾌ変化判定値

//ﾀｲﾏｰﾓｰﾄﾞの設定値
#ifndef	CVD_SHORT			//短ｵﾝ時間閾値[ms]が宣言されていないとき
#define	CVD_SHORT	100			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif
#ifndef	CVD_LONG			//長ｵﾝ時間閾値[ms]が宣言されていないとき
#define	CVD_LONG	1000			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif


//==============================================
//作業域
//==============================================
static struct HIST				//履歴情報
{
	unsigned char cvd_hst;			//CVDの検査履歴(記録)
						//ﾘｱﾙﾓｰﾄﾞではｵﾝ/ｵﾌ状態履歴(0=ｵﾌ､1=ｵﾝ)
						//　b0が最新状態で評価周期毎に左ｼﾌﾄ
						//ﾀｲﾏｰﾓｰﾄﾞではｵﾝ状態経過時間[評価周期]
	unsigned short cvd_ave;			//ADC移動平均(記録)
}cvd_hist[CVD_SU]={0};


//==============================================
//CVDを評価する
//ﾊﾟﾗﾒｰﾀ:評価対象のCVD番号[0起算]
//戻り値
//　ﾘｱﾙﾓｰﾄﾞのとき W:評価結果(0=変化なし､1=ｵﾌからｵﾝへ変化検知､2=ｵﾝからｵﾌへ変化検知)
//　ﾀｲﾏｰﾓｰﾄﾞのとき W:評価結果(0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ検知)
//==============================================
unsigned char cvd_read(				//ﾀｯﾁ評価結果を返す
	unsigned char no)			//評価対象のCVD番号(0起算)
{
	unsigned short value;			//CVDのADC値
	unsigned char res;			//CVD評価戻り値
	const struct CVD_CNF *p;		//CVD構成表へのﾎﾟｲﾝﾀ
	struct HIST *q;				//履歴情報へのﾎﾟｲﾝ
	static unsigned char init_tmr;		//初期化ﾀｲﾏｰ
	unsigned char n,m;

	//定常動作待ち
	if(init_tmr<1500/KOYUU_PR)		//初期化ﾀｲﾏｰが未満了のときは
	{
		init_tmr++;			//初期化ﾀｲﾏｰをｲﾝｸﾘする
		return(0);			//何もせず戻る
	}

	//ｻﾝﾌﾟﾘﾝｸﾞ待ち時間設定
	ADC0.CTRLD=CVD_WAIT;			//ｻﾝﾌﾟﾘﾝｸﾞ待ち

//DBG_C('\n');
//DBG_C('v');
//DBG_B(no);
	//構成表へのﾎﾟｲﾝﾀを設定
	if(no>=CVD_SU) return(0);		//実装数を超えていたら戻る
	p=cvd_cnf+no;				//構成表のｴﾝﾄﾘを得る
	m=1<<(p->mode&0x07);			//ﾋﾞｯﾄﾏｽｸを得る
//DBG_S(p);
//DBG_D(p,12);

	//履歴情報へのﾎﾟｲﾝﾀ
	q=cvd_hist+no;				//履歴情報へのﾎﾟｲﾝﾀを得る
//DBG_S(q);
//DBG_D(q,4);

	//CVDのADC
	value=0;
	for(n=0;n<CVD_CNT;n++)
	{
		p->port->OUTCLR=m;		//ﾎﾟｰﾄをL
		p->port->DIRSET=m;		//ﾎﾟｰﾄを出力ﾓｰﾄﾞ
		ADC0.MUXPOS=p->ain;		//ADC入力ﾋﾟﾝを設定する
		cli();				//割込み禁止
		p->port->DIRCLR=m;		//ﾎﾟｰﾄを入力ﾓｰﾄﾞ
		ADC0.COMMAND=0b00000001;	//変換開始
		sei();				//割込み許可
		while(ADC0.COMMAND);		//変換完了を待つ
//DBG_C('+');
//DBG_S(0x3ff-ADC0.RES);
		value+=(0x3ff-ADC0.RES);	//変換結果を取込む
	}
//DBG_C('=');
//DBG_S(value);

	//移動平均
	if(q->cvd_ave)				//定常動作のとき
	{
		if(value>q->cvd_ave) q->cvd_ave+=CVD_INC;
						//ADC結果が移動平均を超えたら
						//　移動平均を増加させる
		else q->cvd_ave=value;		//超えてなければ
						//　ADC結果を移動平均とする
	}
	else					//初回動作のとき
	{
		q->cvd_ave=value;		//移動平均を初期化する
	}
//DBG_C('-');
//DBG_S(q->cvd_ave);

	//ﾀｲﾏｰﾓｰﾄﾞの処理
	if(p->mode&0x80)			//ﾀｲﾏｰﾓｰﾄﾞのとき
	{
#ifdef CVD_TIMER			//ﾀｲﾏｰﾓｰﾄﾞを実装するとき
//DBG_C('t');

		//ｶﾚﾝﾄ値を判定
//DBG_B(q->cvd_hst);
		res=0;				//仮にｵﾌ判定にしておく
		if(q->cvd_hst)			//前回がｵﾝ判定だったとき
		{
			if(value>q->cvd_ave+CVD_THR1*CVD_CNT) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
		}
		else				//前回がｵﾌ判定だったとき
		{
			if(value>q->cvd_ave+CVD_THR2*CVD_CNT) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値2)のときｵﾝ判定
		}
//DBG_B(res);

		//履歴を評価
		if(res)				//ｵﾝ判定のとき
		{
//DBG_C('+');
			if((++(q->cvd_hst)==0)) q->cvd_hst--;
						//ｵﾝ継続時間をｲﾝｸﾘして
						//　ｵｰﾊﾞﾌﾛｰしたら戻す
//DBG_B(q->cvd_hst);
			if(q->cvd_hst==CVD_LONG/KOYUU_PR) res=2;
						//長ｵﾝ閾値に一致したら｢2｣を返す
			else if(q->cvd_hst==CVD_SHORT/KOYUU_PR) res=3;
						//短ｵﾝ閾値に一致したら｢3｣を返す
			else res=0;
		}
		else				//ｵﾌ判定のとき
		{
//DBG_C('-');
//DBG_B(q->cvd_hst);
			if(q->cvd_hst>CVD_LONG/KOYUU_PR) res=0;
						//長ｵﾝ閾値を超えていたら｢0｣を返す
			else if(q->cvd_hst>CVD_SHORT/KOYUU_PR) res=1;
						//短ｵﾝ閾値を超えていたら｢1｣を返す
			else res=0;		//その他は｢0｣を返す
			q->cvd_hst=0;		//履歴をｸﾘｱする
		}

//DBG_B(res);
#else					//ﾀｲﾏｰﾓｰﾄﾞを実装しないとき
		return(0);
#endif
	}

	//ﾘｱﾙﾓｰﾄﾞの処理
	else
	{
#ifdef CVD_REAL				//ﾘｱﾙﾓｰﾄﾞを実装するとき
//DBG_C('r');
		q->cvd_hst<<=1;			//履歴をｼﾌﾄしておく
//DBG_B(q->cvd_hst);
//DBG_B(value);
		if(q->cvd_hst&0x02)		//前回がｵﾝ判定だったとき
		{
			if(value>(short)q->cvd_ave+CVD_THR1*CVD_CNT) cvd_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
		}
		else				//前回がｵﾌ判定だったとき
		{
			if(value>(short)q->cvd_ave+CVD_THR2*CVD_CNT) cvd_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
		}
//DBG_B(q->cvd_hst);
		switch(cvd_hst&CVD_HST_MSK)	//履歴で判定する
		{
		case CVD_HST_ON:		//ｵﾝ判定ﾊﾟﾀｰﾝのときは
			res=1;			//　｢1｣を返す
			break;
		case CVD_HST_OFF:		//ｵﾌ判定ﾊﾟﾀｰﾝのときは
			res=2;			//　｢2｣を返す
			break;
		default:
			res=0;			//その他は｢0｣を返す
		}
//DBG_B(res);
#else					//ﾘｱﾙﾓｰﾄﾞを実装しないとき
		return(0);
#endif
	}

//DBG_B(res);
	return(res);				//評価結果を返す
}
