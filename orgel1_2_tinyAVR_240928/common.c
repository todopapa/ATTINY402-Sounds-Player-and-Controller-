#ifdef	SHDBS				//ﾃﾞﾊﾞｸﾞ信号を出力するとき
//==============================================
//ﾃﾞﾊﾞｸﾞ信号の初期設定
//==============================================
static void dbs_init(void)
{

	DBS_PORT.OUTCLR=(1<<DBS_BIT);		//ﾃﾞﾊﾞｸﾞ信号をH
	DBS_PORT.DIRSET=(1<<DBS_BIT);		//ﾃﾞﾊﾞｸﾞ信号を出力ﾓｰﾄﾞ
}


//==============================================
//ﾃﾞﾊﾞｸﾞ信号のﾏｸﾛ定義
//==============================================
#define	DBS_H		DBS_PORT.OUTSET=(1<<DBS_BIT)
#define	DBS_L		DBS_PORT.OUTCLR=(1<<DBS_BIT)
#else
#define DBS_H
#define DBS_L
#endif


//==============================================
//1usの待ち
//==============================================
static void wait_1us(void)
{

		asm("rjmp .+0");
}


//==============================================
//us単位の待ち(@16MHz)
//待ち時間は2us以上であること
//==============================================
void wait_us(
	unsigned short us)			//待ち時間[us]
{

	us/=2;
	while(--us)
	{
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
		asm("rjmp .+0");
	}
}


//==============================================
//ms単位の待ち
//==============================================
static void wait_ms(
	unsigned short ms)			//待ち時間[ms]
{

	while(ms--)
	{
		wait_us(1000);
	}
}


#ifdef SHDBG				//ﾃﾞﾊﾞｸﾞ情報を出力するとき
#ifdef SHDBG_SOFT			//ﾃﾞﾊﾞｸﾞ情報出力のUARTをｿﾌﾄ実装するとき
//==============================================
//ﾃﾞﾊﾞｸﾞ情報の初期設定
//==============================================
static void dbg_init(void)
{

	DBG_PORT.OUTSET=1<<DBG_BIT;
	DBG_PORT.DIRSET=1<<DBG_BIT;
}


//==============================================
//送信完了の同期
//==============================================
#define	outpt_sync()


//==============================================
//ﾃﾞﾊﾞｸﾞ情報の1文字をそのまま送信する(ｿﾌﾄUART)
//==============================================
void outpt_c(					//戻り値無し
	unsigned char c)			//表示する文字ﾃﾞｰﾀ
{
	unsigned char i=0;

//DBS_H;
	if(SREG&0x80)				//割込みが許可されていたら
	{
		cli();				//　割込みを禁止する
		i=1;				//　割り込みを禁止したことを記録する
	}
	DBG_PORT.OUTCLR=1<<DBG_BIT;		//ｽﾀｰﾄﾋﾞｯﾄ
	wait_us(26);				//1ﾋﾞｯﾄ巾の待ち
	for(unsigned char n=0;n<8;n++)		//8ﾋﾞｯﾄ分繰返す
	{					//LSBからﾃﾞｰﾀﾋﾞｯﾄを送信する
		if(c&1) DBG_PORT.OUTSET=1<<DBG_BIT;
						//ﾋﾞｯﾄ値が1のときはH
		else DBG_PORT.OUTCLR=1<<DBG_BIT;//ﾋﾞｯﾄ値が0のときはL
		wait_us(26);			//1ﾋﾞｯﾄ巾の待ち
		c>>=1;				//次のﾋﾞｯﾄに進める
	}
	DBG_PORT.OUTSET=1<<DBG_BIT;		//ｽﾄｯﾌﾟﾋﾞｯﾄ
	wait_us(78);				//3ﾋﾞｯﾄ巾の待ち
	if(i) sei();				//割込みを許可する
//DBS_L;
}


#else					//内蔵UARTを使うとき
//==============================================
//ﾃﾞﾊﾞｸﾞ情報の初期設定
//==============================================
static void dbg_init(void)
{

#ifdef SHDBG_BPS			//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄが宣言されているとき
	USART0.BAUD=80000000/SHDBG_BPS;		//SHDBG_BPS[bps]@20MHz
#else					//ﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄが38.4bps(ﾃﾞﾌｫﾙﾄ)のとき
	USART0.BAUD=1666;			//38.4kbps@16MHz
#endif
	USART0.CTRLB=0b01000000;		//受信禁止､送信許可
	USART0.CTRLC=0b00001011;		//非同期､ﾊﾟﾘﾃｨ無し､ｽﾄｯﾌﾟ2ﾋﾞｯﾄ､ﾃﾞｰﾀ8ﾋﾞｯﾄ
	DBG_PORT.DIRSET=1<<DBG_BIT;
}


//==============================================
//送信完了の同期
//==============================================
static unsigned char outpt_flag;		//初回送信済みの表示
static void outpt_sync(void)
{

	if(outpt_flag)				//初回送信済みのときは
	{
		while(!(USART0.STATUS&0x40));	//送信完了を待つ
	}
}


//==============================================
//1文字を送信
//==============================================
static void outpt_c(
	unsigned char c)			//送信する文字
{

	outpt_flag=1;				//初回送信済みの印
	while(!(USART0.STATUS&0x20));		//送信ﾃﾞｰﾀﾚｼﾞｽﾀが空くまで待つ
	USART0.TXDATAL=c;			//ﾃﾞｰﾀを送信する
	USART0.STATUS|=0x40;			//送信完了ﾌﾗｸﾞをｸﾘｱしておく
}
#endif


//==============================================
//文字列(文字列の最後は\0)を送信
//==============================================
static void outpt_a(
	unsigned char *a)			//送信する文字列
{

	while(*a) outpt_c(*a++);		//文字列を送信する
}


//==============================================
//charを16進2文字にして送信する
//==============================================
static void outpt_b(
	unsigned char b)			//送信するﾊﾞｲﾄﾃﾞｰﾀ
{
	unsigned char c;

	c=b>>4;					//上位ﾆﾌﾞﾙを取出す
	if(c>9) c+=55;				//16進文字に変換する
	else c+=48;
	outpt_c(c);				//1文字を送信する
	c=(unsigned char)(b&0x0f);		//下位ﾆﾌﾞﾙを取出す
	if(c>9) c+=55;				//16進文字に変換する
	else c+=48;
	outpt_c(c);				//1文字を送信する
}


//==============================================
//shortを16進4文字にして送信する
//==============================================
static void outpt_s(
	unsigned short s)			//送信するshortﾃﾞｰﾀ
{

	outpt_b(s>>8);				//上位ﾊﾞｲﾄを16進で送信する
	outpt_b(s);				//下位ﾊﾞｲﾄを16進で送信する
}


//==============================================
//longを16進8文字にして送信する
//==============================================
static void outpt_l(
	unsigned long l)			//送信するlongﾃﾞｰﾀ
{

	outpt_b(l>>24);				//最上位ﾊﾞｲﾄを16進で送信する
	outpt_b(l>>16);
	outpt_b(l>>8);
	outpt_b(l);				//最下位ﾊﾞｲﾄを16進で送信する
}


//==============================================
//複数ﾊﾞｲﾄを16進2文字にして送信する
//==============================================
static void outpt_d(
	unsigned char *d,			//送信するﾊﾞｲﾄﾃﾞｰﾀのｱﾄﾞﾚｽ
	unsigned char l)			//ﾊﾞｲﾄ数
{

	outpt_c('[');
	while(--l)
	{
		outpt_b(*d++);
		outpt_c('.');
	}
	outpt_b(*d++);
	outpt_c(']');
}


//==============================================
//ﾃﾞﾊﾞｸﾞ情報の16ﾋﾞｯﾄを10進5文字に変換して送信する
//==============================================
static void outpt_i(
	unsigned short i)			//送信する16ﾋﾞｯﾄﾃﾞｰﾀ
{
	unsigned char b[10];

	b[0]=i/10000;				//10000の桁を求める
	i-=b[0]*10000;
	b[1]=i/1000;				//1000の桁を求める
	i-=b[1]*1000;
	b[2]=i/100;				//100の桁を求める
	i-=b[2]*100;
	b[3]=i/10;				//10の桁を求める
	i-=b[3]*10;
	b[4]=i;					//1桁を求める
	outpt_c(b[0]+'0');			//10進文字に変換して送信する
	outpt_c(b[1]+'0');
	outpt_c(b[2]+'0');
	outpt_c(b[3]+'0');
	outpt_c(b[4]+'0');
}


//==============================================
//ﾃﾞﾊﾞｸﾞ情報のﾏｸﾛ定義
//==============================================
#define DBG_C(c) outpt_c((unsigned char)c)
#define DBG_A(a) outpt_a((unsigned char *)a)
#define DBG_B(b) outpt_b((unsigned char)b)
#define DBG_S(s) outpt_s((unsigned short)s)
#define DBG_L(l) outpt_l((unsigned int)l)
#define DBG_D(d,l) outpt_d((unsigned char *)d,l)
#define DBG_I(s) outpt_i((unsigned short)s)
#define DBG_SYNC() outpt_sync()
#else
#define DBG_C(c)
#define DBG_A(a)
#define DBG_B(b)
#define DBG_S(s)
#define DBG_L(l)
#define DBG_D(d,l)
#define DBG_I(s)
#define DBG_SYNC()
#endif
