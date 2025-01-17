//SWを評価する機能ﾓｼﾞｭｰﾙ
//
//SWの構成を下記の例に倣って､呼出し元にて定義しておくこと｡
//
//SWは複数個を実装可能｡SW毎にﾎﾟｰﾄﾚｼﾞｽﾀが違ってもよい｡
//
//SWのｵﾝとは､SWが閉じた状態｡
//SWのｵﾌとは､SWが開いた状態｡
//
//SWをﾎﾟｰﾄ〜GND間に配置して､ﾎﾟｰﾄをﾌﾟﾙｱｯﾌﾟした回路(閉=L)を負論理とする｡
//SWをﾎﾟｰﾄ〜Vdd間に配置して､ﾎﾟｰﾄをﾌﾟﾙﾀﾞｳﾝした回路(閉=H)を正論理とする｡
//
//SWの評価は以下の2つのﾓｰﾄﾞがある｡
//・ﾘｱﾙﾓｰﾄﾞ
//　規定期間内のﾊﾞﾀﾂｷは無視する｡
//　状態が変化したときに変化の状況を返す｡
//　戻り値は､0=変化の検知なし､1=ｵﾌからｵﾝへの変化を検知､2=ｵﾝからｵﾌへの変化を検知｡
//・ﾀｲﾏｰﾓｰﾄﾞ
//　ｵﾝの継続時間が短ｵﾝ閾値になったら短ｵﾝ一致とする｡
//　ｵﾝの継続時間が長ｵﾝ閾値になったら長ｵﾝ一致とする｡
//　ｵﾝからｵﾌへ変化したときに､ｵﾝ状態であった時間が短ｵﾝ閾値超えのときは短ｵﾝ検知とする｡
//　戻り値は､0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ一致､3=短ｵﾝ一致｡
//ﾘｱﾙﾓｰﾄﾞとﾀｲﾏｰﾓｰﾄﾞは排他的で､1つのSWに対してどちらか1つのﾓｰﾄﾞを指定できる｡
//
//SWを評価する場合は､このﾓｼﾞｭｰﾙを#includeする｡
//負論理のときはSW_INVを宣言する｡
//ﾘｱﾙﾓｰﾄﾞで評価するときは､SW_REALを宣言する｡
//ﾀｲﾏｰﾓｰﾄﾞで評価するときは､SW_TIMERを宣言する｡
//SWのﾎﾟｰﾄをﾃﾞｼﾞﾀﾙ入力ﾓｰﾄﾞに初期設定しておくこと｡
//SWのﾎﾟｰﾄの内部ﾌﾟﾙｱｯﾌﾟ/ﾀﾞｳﾝは必要により､呼出し元で設定しておくこと｡
//ｷｰ入力割込みとSleep関連の処理にこのﾓｼﾞｭｰﾙは関与しない｡


//==============================================
//SW構成の定義例
//==============================================
//#define	SW_REAL				//SWﾘｱﾙﾓｰﾄﾞを実装するときに宣言する
//#define	SW_TIMER			//SWﾀｲﾏｰﾓｰﾄﾞを実装するときに宣言する

//SWの構成--------------------------------------
//static const struct SW_CNF
//{
//	PORT_tn *port;				//PORTｱﾄﾞﾚｽ
//	unsigned char mode;			//b7:SWのﾓｰﾄﾞ
//						//　0=ﾘｱﾙﾓｰﾄﾞ､1=ﾀｲﾏｰﾓｰﾄﾞ
//						//b6:ﾎﾟｰﾄ入力の極性
//						//　0=負論理､1=正論理
//	unsigned char msk;			//ﾋﾞｯﾄﾏｽｸ
//}sw_cnf[]=
//{
//SW0の構成-------------------------------------
//	{GPIOD,0x80,0x10},			//PD4､ﾀｲﾏｰﾓｰﾄﾞ､負論理
//SW1の構成-------------------------------------
//	{GPIOD,0x00,0x20},			//PD5､ﾘｱﾙﾓｰﾄﾞ､負論理
//SW2の構成-------------------------------------
//	{GPIOD,0x00,0x40},			//PD6､ﾘｱﾙﾓｰﾄﾞ､負論理
//SW3の構成-------------------------------------
//	{GPIOA,0x00,0x02},			//PA1､ﾘｱﾙﾓｰﾄﾞ､負論理
//};

#define	SW_SU	(sizeof(sw_cnf)/sizeof(sw_cnf[0]))
						//SWの実装数

//ﾘｱﾙﾓｰﾄﾞの設定値
#ifndef	SW_HST_BIT			//ﾊﾞﾀﾂｷ除去期間が宣言されていないとき
#define	SW_HST_BIT	3			//ﾊﾞﾀﾂｷ除去期間[評価周期](1〜7の範囲)
#endif
#define	SW_HST_MSK	((1<<(SW_HST_BIT+1))-1)	//履歴判定ﾋﾞｯﾄﾏｽｸ
#define	SW_HST_ON	((1<<SW_HST_BIT)-1)	//履歴ｵﾝ変化判定値
#define	SW_HST_OFF	((1<<(SW_HST_BIT+1))-2)	//履歴ｵﾌ変化判定値

//ﾀｲﾏｰﾓｰﾄﾞの設定値
#ifndef	SW_SHORT			//短ｵﾝ時間閾値が宣言されていないとき
#define	SW_SHORT	100			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif
#ifndef	SW_LONG				//長ｵﾝ時間閾値が宣言されていないとき
#define	SW_LONG		1000			//ﾃﾞﾌｫﾙﾄ値[ms]を設定する
#endif


//==============================================
//作業域
//==============================================
static unsigned char sw_hst[SW_SU];		//SWの検査履歴
						//ﾘｱﾙﾓｰﾄﾞではｵﾝ/ｵﾌ状態履歴(0=ｵﾌ､1=ｵﾝ)
						//　b0が最新状態で評価周期毎に左ｼﾌﾄ
						//ﾀｲﾏｰﾓｰﾄﾞではｵﾝ状態経過時間[評価周期]


//==============================================
//SWを評価する
//ﾊﾟﾗﾒｰﾀ:評価対象のSW番号[0起算]
//戻り値
//　ﾘｱﾙﾓｰﾄﾞのとき W:評価結果(0=変化なし､1=ｵﾌからｵﾝへ変化検知､2=ｵﾝからｵﾌへ変化検知)
//　ﾀｲﾏｰﾓｰﾄﾞのとき W:評価結果(0=検知なし､1=短ｵﾝ検知､2=長ｵﾝ検知)
//==============================================
static unsigned char sw_read(
	unsigned char no)			//評価対象のSW番号[0起算]
{
	unsigned char *p;			//ﾊﾞｲﾄﾃﾞｰﾀへのﾎﾟｲﾝﾀ
	unsigned char value;			//SWの値(0=ｵﾌ､1=ｵﾝ)
	unsigned char res;			//SW評価戻り値

//DBG_C('\n');
//DBG_C('S');
//DBG_B(no);
	if(no>=SW_SU) return(0);		//SW番号が実装数を超えていたら戻る
//DBG_S(sw_cnf[no].port);
	value=sw_cnf[no].port->IN&sw_cnf[no].msk;//ﾎﾟｰﾄを読込む
//DBG_B(value);
	if(!(sw_cnf[no].mode&0x40)) value^=sw_cnf[no].msk;
						//負論理のときは反転する
//DBG_B(value);
	p=sw_hst+no;				//履歴へのﾎﾟｲﾝﾀを設定する
	if(sw_cnf[no].mode&0x80)		//ﾀｲﾏｰﾓｰﾄﾞのとき
	{

	//ﾀｲﾏｰﾓｰﾄﾞの処理
#ifdef SW_TIMER				//ﾀｲﾏｰﾓｰﾄﾞを実装するとき
//DBG_C('t');
		if(value)			//SWがｵﾝのとき
		{
//DBG_C('+');
			if((++*p==0)) --*p;	//ｵﾝ継続時間をｲﾝｸﾘして
						//　ｵｰﾊﾞﾌﾛｰしたら戻す
//DBG_B(*p);
			if(*p==SW_LONG/KOYUU_PR) res=2;
						//長ｵﾝ閾値に一致したら｢2｣を返す
			else if(*p==SW_SHORT/KOYUU_PR) res=3;
						//短ｵﾝ閾値に一致したら｢3｣を返す
			else res=0;		//その他は｢0｣を返す
		}
		else				//SWがｵﾌのとき
		{
//DBG_C('-');
//DBG_B(*p);
			if(*p>SW_LONG/KOYUU_PR) res=0;
						//長ｵﾝ閾値を超えていたら｢0｣を返す
			else if(*p>SW_SHORT/KOYUU_PR) res=1;
						//短ｵﾝ閾値を超えていたら｢1｣を返す
			else res=0;		//｢0｣を返す
			*p=0;			//履歴をｸﾘｱする
		}
//DBG_B(res);
#else					//ﾀｲﾏｰﾓｰﾄﾞを実装しないとき
		res=0;
#endif
	}
	else					//ﾘｱﾙﾓｰﾄﾞのとき
	{
//DBG_C('r');
#ifdef SW_REAL				//ﾘｱﾙﾓｰﾄﾞを実装するとき
		*p<<=1;				//履歴をｼﾌﾄしておく
//DBG_B(*p);
//DBG_B(value);
		if(value) *p|=1;		//SWがｵﾝのときは最新履歴をｵﾝする
//DBG_B(*p);
		switch(*p&SW_HST_MSK)		//履歴で判定する
		{
		case SW_HST_ON:			//ｵﾝ判定ﾊﾟﾀｰﾝのときは
			res=1;			//　｢1｣を返す
			break;
		case SW_HST_OFF:		//ｵﾌ判定ﾊﾟﾀｰﾝのときは
			res=2;			//　｢2｣を返す
			break;
		default:			//その他のときは
			res=0;			//　｢0｣を返す
		}
//DBG_B(res);
#else					//ﾘｱﾙﾓｰﾄﾞを実装しないとき
		res=0;
#endif
	}
	return(res);
}
