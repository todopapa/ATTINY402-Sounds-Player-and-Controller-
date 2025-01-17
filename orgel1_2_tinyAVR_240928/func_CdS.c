//CdSを評価する機能ﾓｼﾞｭｰﾙ
//
//CdSの構成を下記の例に倣って､呼出し元にて定義しておくこと｡
//
//CdSは1個のみ実装可能｡
//
//CdSのｵﾝとは､CdSに手をかざして暗くし､内部抵抗値が高い状態｡
//CdSのｵﾌとは､明るくなり､内部抵抗値が低い状態｡
//
//CdSをﾎﾟｰﾄ〜GND間に配置して､ﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟした回路(暗=H)を正論理とする｡
//このときはCdS_INVを定義しない｡
//CdSをﾎﾟｰﾄ〜Vdd間に配置して､ﾎﾟｰﾄをﾌﾟﾙﾀﾞｳﾝした回路(暗=L)を負論理とする｡
//このときはCdS_INVを定義する｡
//
//100kΩ〜1MΩﾗﾝｸのCdSを使用し､ﾎﾟｰﾄの内部ﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝを利用することで
//　給電制御できるため省電力にできる｡
//外部ﾌﾟﾙｱｯﾌﾟする場合の給電制御は行っていないので､必要なら作り込むこと｡
//
//明るさの判定は､
//環境の明るさに適応するように､移動平均と比較してｵﾝ/ｵﾌ状態を判定する｡
//判定結果のﾊﾞﾀﾂｷを防ぐため､明るさの判定にﾋｽﾃﾘｼｽを持たせている｡
//　前回がｵﾌ判定だったときは､ｶﾚﾝﾄ値>(移動平均値+閾値1)でｵﾝ判定となる｡
//　前回がｵﾝ判定だったときは､ｶﾚﾝﾄ値>(移動平均値+閾値2)でｵﾝ判定となる｡
//　なお､閾値1>閾値2で設定すること｡
//
//CdSの評価は以下の2つのﾓｰﾄﾞがある｡
//・ﾘｱﾙﾓｰﾄﾞ
//　ﾊﾞﾀﾂｷ除去期間の変化は無効とする｡
//　状態が変化したときに変化の状況を返す｡
//　戻り値は､0=変化の検知なし､1=ｵﾌからｵﾝへの変化を検知､2=ｵﾝからｵﾌへの変化を検知｡
//・ﾀｲﾏｰﾓｰﾄﾞ
//　ｵﾝの継続時間が短ｵﾝ閾値になったら短ｵﾝ一致とする｡
//　ｵﾝの継続時間が長ｵﾝ閾値になったら長ｵﾝ一致とする｡
//　ｵﾝからｵﾌへ変化したときに､ｵﾝ状態であった時間が短ｵﾝ閾値超えのときは短ｵﾝ検知とする｡
//　戻り値は､0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ一致､3=短ｵﾝ一致｡
//ﾘｱﾙﾓｰﾄﾞとﾀｲﾏｰﾓｰﾄﾞは排他的で､どちらか1つのﾓｰﾄﾞを指定できる｡
//
//CdS_THRでｵﾝ/ｵﾌ判定の閾値を宣言できる｡この場合は移動平均処理を行わない｡
//
//CdS＿FUTAを宣言すると､ｵﾝ/ｵﾌの判定を反転する｡これはｵﾙｺﾞｰﾙ箱のｲﾒｰｼﾞで､
//蓋を開ける(明)とｵﾝ判定､閉じる(暗)とｵﾌ判定する｡ﾘｱﾙﾓｰﾄﾞのときにのみ有効｡
//
//CdSを評価する場合は､このﾓｼﾞｭｰﾙを#includeする｡
//負論理のときはCdS_INVを宣言する｡
//ﾘｱﾙﾓｰﾄﾞで評価するときは､CdS_REALを#defineしておく｡
//ﾀｲﾏｰﾓｰﾄﾞで評価するときは､CdS_TIMERを#defineしておく｡
//CdS_REALとCdS_TIMERを同時に#defineしないこと｡
//CdSのﾎﾟｰﾄをｱﾅﾛｸﾞ･入力ﾓｰﾄﾞで初期設定しておくこと｡
//CdSのﾎﾟｰﾄのﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝの制御はこのﾓｼﾞｭｰﾙ内で行っている｡
//Sleep関連の処理にこのﾓｼﾞｭｰﾙは関与しない｡


//==============================================
//CdS構成の定義例
//==============================================
//以下のﾘｱﾙﾓｰﾄﾞとﾀｲﾏｰﾓｰﾄﾞは択一選択すること
//#define	CdS_REAL			//CdSはﾘｱﾙﾓｰﾄﾞ
//#define	CdS_THR		100		//CdS評価の固定閾値[1/256]
//#define	CdS_FUTA			//CdS判定反転(明=ｵﾝ)

//CdSの構成--------------------------------------
//#define	CdS_PORT	PORTA		//CdSのﾎﾟｰﾄ
//#define	CdS_BIT		4		//CdSのﾋﾞｯﾄ
//#define	CdS_AIN		4		//CdSのAIN
//#define	CdS_INV				//CdS入力は負論理(暗=L)


//==============================================
//CdS評価の閾値等
//==============================================
#ifndef	CdS_THR1				//CdS評価の閾値1が宣言されていないとき
#define	CdS_THR1	15			//CdS評価の閾値1[1/256]
#endif
#ifndef	CdS_THR2				//CdS評価の閾値2が宣言されていないとき
#define	CdS_THR2	30			//CdS評価の閾値2[1/256]
#endif

//ﾘｱﾙﾓｰﾄﾞの設定値
#ifndef	CdS_HST_BIT			//ﾊﾞﾀﾂｷ除去期間が宣言されていないとき
#define	CdS_HST_BIT	4			//ﾊﾞﾀﾂｷ除去期間[評価周期](1〜7の範囲)
#endif
#define	CdS_HST_MSK	((1<<(CdS_HST_BIT+1))-1)//履歴判定ﾋﾞｯﾄﾏｽｸ
#define	CdS_HST_ON	((1<<CdS_HST_BIT)-1)	//履歴ｵﾝ変化判定値
#define	CdS_HST_OFF	((1<<(CdS_HST_BIT+1))-2)//履歴ｵﾌ変化判定値

//ﾀｲﾏｰﾓｰﾄﾞの設定値
#ifndef	CdS_SHORT			//短ｵﾝ時間閾値が宣言されていないとき
#define	CdS_SHORT	100			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif
#ifndef	CdS_LONG			//長ｵﾝ時間閾値が宣言されていないとき
#define	CdS_LONG	1000			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif


//==============================================
//作業域
//==============================================
static unsigned char cds_hst;			//CdSの検査履歴
						//ﾘｱﾙﾓｰﾄﾞではｵﾝ/ｵﾌ状態履歴(0=ｵﾌ､1=ｵﾝ)
						//　b0が最新状態で評価周期毎に左ｼﾌﾄ
						//ﾀｲﾏｰﾓｰﾄﾞではｵﾝ状態経過時間[評価周期]
#ifndef CdS_THR				//固定閾値が宣言されていないとき
static unsigned char cds_ave;			//ADC移動平均
#endif


//==============================================
//CdSを評価する
//戻り値
//　ﾘｱﾙﾓｰﾄﾞのとき W:評価結果(0=変化なし､1=ｵﾌからｵﾝへ変化検知､2=ｵﾝからｵﾌへ変化検知)
//　ﾀｲﾏｰﾓｰﾄﾞのとき W:評価結果(0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ検知)
//==============================================
static unsigned char cds_read(void)
{
	static unsigned char value;		//CdSのADC値
	unsigned char res;			//CdS評価戻り値

//DBG_C('\n');
//DBG_C('c');

	//ｻﾝﾌﾟﾘﾝｸﾞ待ち時間設定
	ADC0.CTRLD=3;				//3ｸﾛｯｸを設定する

	//次のADCをｷｯｸしておく
#ifndef	CdS_INV				//CdS入力が正論理(暗=H)のとき
	((PORT_tn *)&CdS_PORT)->PINnCTRL[CdS_BIT]=0b00001000;
						//CdSﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟする
#endif
	ADC0.MUXPOS=CdS_AIN;			//ADC入力ﾋﾟﾝを設定する
	ADC0.COMMAND=0b00000001;		//変換開始

	//極性を加味する
#ifdef	CdS_INV				//CdS入力が負論理(暗=L)のとき
//DBG_C('^');
	value^=0xff;				//ADC結果を補数にする
#endif

	//移動平均の初期化
#ifndef CdS_THR				//固定閾値が宣言されていないとき
//DBG_B(value);
	if(!cds_ave) cds_ave=value;		//初回のAD結果を移動平均の初期値にする
//DBG_B(cds_ave);

	//移動平均の計算(簡易計算)
	if(value>cds_ave) cds_ave++;		//ｶﾚﾝﾄ値>移動平均値のときは
						//　移動平均値をｲﾝｸﾘする
	else if(value<cds_ave) cds_ave=value;	//ｶﾚﾝﾄ値<移動平均値のときは
						//　ｶﾚﾝﾄ値を移動平均値にする
//DBG_B(cds_ave);
#endif

	//ﾀｲﾏｰﾓｰﾄﾞの処理
#ifdef CdS_TIMER				//ﾀｲﾏｰﾓｰﾄﾞを実装するとき
//DBG_C('t');

	//ｶﾚﾝﾄ値を判定
//DBG_B(cds_hst);
	res=0;					//仮にｵﾌ判定にしておく
	if(cds_hst)				//前回がｵﾝ判定だったとき
	{
#ifdef CdS_THR				//固定閾値が宣言されているとき
		if(value>(short)CdS_THR+CdS_THR1) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
#else					//固定閾値が宣言されていないとき
		if(value>(short)cds_ave+CdS_THR1) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
#endif
	}
	else					//前回がｵﾌ判定だったとき
	{
#ifdef CdS_THR				//固定閾値が宣言されているとき
		if(value>(short)CdS_THR+CdS_THR2) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値2)のときｵﾝ判定
#else					//固定閾値が宣言されていないとき
		if(value>(short)cds_ave+CdS_THR2) res=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値2)のときｵﾝ判定
#endif
	}
//DBG_B(res);

	//履歴を評価
	if(res)					//ｵﾝ判定のとき
	{
//DBG_C('+');
		if((++cds_hst==0)) cds_hst--;	//ｵﾝ継続時間をｲﾝｸﾘして
						//　ｵｰﾊﾞﾌﾛｰしたら戻す
//DBG_B(cds_hst);
		if(cds_hst==CdS_LONG/KOYUU_PR) res=2;
						//長ｵﾝ閾値に一致したら｢2｣を返す
		else if(cds_hst==CdS_SHORT/KOYUU_PR) res=3;
						//短ｵﾝ閾値に一致したら｢3｣を返す
		else res=0;
	}
	else					//ｵﾌ判定のとき
	{
//DBG_C('-');
//DBG_B(cds_hst);
		if(cds_hst>CdS_LONG/KOYUU_PR) res=0;
						//長ｵﾝ閾値を超えていたら｢0｣を返す
		else if(cds_hst>CdS_SHORT/KOYUU_PR) res=1;
						//短ｵﾝ閾値を超えていたら｢1｣を返す
		else res=0;			//その他は｢0｣を返す
		cds_hst=0;			//履歴をｸﾘｱする
	}
#endif

	//ﾘｱﾙﾓｰﾄﾞの処理
#ifdef CdS_REAL				//ﾘｱﾙﾓｰﾄﾞを実装するとき
//DBG_C('r');
	cds_hst<<=1;				//履歴をｼﾌﾄしておく
//DBG_B(cds_hst);
//DBG_B(value);
	if(cds_hst&0x02)			//前回がｵﾝ判定だったとき
	{
#ifdef CdS_THR				//固定閾値が宣言されてるとき
		if(value>(short)CdS_THR+CdS_THR1) cds_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
#else					//固定閾値が宣言されていないとき
		if(value>(short)cds_ave+CdS_THR1) cds_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値1)のときｵﾝ判定
#endif
	}
	else					//前回がｵﾌ判定だったとき
	{
#ifdef CdS_THR				//固定閾値が宣言されてるとき
		if(value>(short)CdS_THR+CdS_THR2) cds_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値2)のときｵﾝ判定
#else					//固定閾値が宣言されていないとき
		if(value>(short)cds_ave+CdS_THR2) cds_hst|=1;
						//ｶﾚﾝﾄ値>(移動平均値+閾値2)のときｵﾝ判定
#endif
	}
#ifdef CdS_FUTA				//判定を反転するとき
	cds_hst^=1;				//判定を反転する
#endif
//DBG_B(cds_hst);
	switch(cds_hst&CdS_HST_MSK)		//履歴で判定する
	{
	case CdS_HST_ON:			//ｵﾝ判定ﾊﾟﾀｰﾝのときは
		res=1;				//　｢1｣を返す
		break;
	case CdS_HST_OFF:			//ｵﾌ判定ﾊﾟﾀｰﾝのときは
		res=2;				//　｢2｣を返す
		break;
	default:
		res=0;				//その他は｢0｣を返す
	}
#endif

//DBG_C('=');
//DBG_B(res);

	//ADC結果を取得する
	while(ADC0.COMMAND);			//変換完了を待つ
	value=ADC0.RES>>2;			//変換結果の上位8ﾋﾞｯﾄを取出す
//DBG_B(value);
#ifndef	CdS_INV				//CdS入力が正論理(暗=H)のとき
//DBG_C('~');
	((PORT_tn *)&CdS_PORT)->PINnCTRL[CdS_BIT]=0b00000000;
						//CdSﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟ停止
#endif

	//評価結果を返す
	return(res);
}
