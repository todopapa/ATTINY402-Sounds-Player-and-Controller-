//CH32V003電子ｵﾙｺﾞｰﾙVer1_2のｴﾝｼﾞﾝ部
//音価･音高･音符ﾃﾞｰﾀの設計は｢ドキュメント\CH32V003電子オルゴール.xls｣を参照
//音声ﾃﾞｰﾀと曲ﾃﾞｰﾀの枠組みはorgel.hを参照
//ｿﾝｸﾞ･音符ﾃﾞｰﾀの枠組みはorgel.incを参照
//ﾎﾟｰﾄ割当て､ﾀｲﾐﾝｸﾞ設定は固有処理部を参照


//==============================================
//I2Cｱｸｾｽのﾏｸﾛ定義
//==============================================
#define	I2C_SCL_PU	((PORT_tn *)&I2C_SCL_PORT)->PINnCTRL[I2C_SCL_BIT]=0b00001000;
#define	I2C_SCL_H	I2C_SCL_PORT.DIRCLR=1<<I2C_SCL_BIT
#define	I2C_SCL_L	I2C_SCL_PORT.DIRSET=1<<I2C_SCL_BIT
#define	I2C_SDA_PU	((PORT_tn *)&I2C_SDA_PORT)->PINnCTRL[I2C_SDA_BIT]=0b00001000;
#define	I2C_SDA_H	I2C_SDA_PORT.DIRCLR=1<<I2C_SDA_BIT
#define	I2C_SDA_L	I2C_SDA_PORT.DIRSET=1<<I2C_SDA_BIT
#define	I2C_SDA		(I2C_SDA_PORT.IN&1<<I2C_SDA_BIT)


//==============================================
//SPIｱｸｾｽのﾏｸﾛ定義
//==============================================
#define	SPI_SS_OUT	SPI_SS_PORT.DIRSET=1<<SPI_SS_BIT
#define	SPI_SS_H	SPI_SS_PORT.OUTSET=1<<SPI_SS_BIT
#define	SPI_SS_L	SPI_SS_PORT.OUTCLR=1<<SPI_SS_BIT
#define	SPI_SCK_OUT	SPI_SCK_PORT.DIRSET=1<<SPI_SCK_BIT
#define	SPI_SCK_H	SPI_SCK_PORT.OUTSET=1<<SPI_SCK_BIT
#define	SPI_SCK_L	SPI_SCK_PORT.OUTCLR=1<<SPI_SCK_BIT
#define	SPI_MOSI_OUT	SPI_MOSI_PORT.DIRSET=1<<SPI_MOSI_BIT
#define	SPI_MOSI_H	SPI_MOSI_PORT.OUTSET=1<<SPI_MOSI_BIT
#define	SPI_MOSI_L	SPI_MOSI_PORT.OUTCLR=1<<SPI_MOSI_BIT
#define	SPI_MISO_IN	SPI_MISO_PORT.DIRCLR=1<<SPI_MISO_BIT
#define	SPI_MISO	(SPI_MISO_PORT.IN&1<<SPI_MISO_BIT)


//==============================================
//音声N音量ﾃｰﾌﾞﾙ
//==============================================
static const unsigned short voiceN_vol[]={
	(unsigned long)VOICE0_VOL*PWM_STEP/100,
	(unsigned long)VOICE1_VOL*PWM_STEP/100,
	(unsigned long)VOICE2_VOL*PWM_STEP/100
};


//==============================================
//音価ﾃｰﾌﾞﾙ(音価ｺｰﾄﾞをﾌﾟﾘｽｹｰﾙ値に変換する)
//==============================================
static const unsigned char onka_tbl[]={
	2,	//1=32分3連符		=kR32
	4,	//2=16分3連符		=kR16
	6,	//3=32分音符		=kK32
	8,	//4=8分3連符		=kR8
	9,	//5=付点32分音符	=kP32
	12,	//6=16分音符		=kK16
	16,	//7=4分3連符		=kR4
	18,	//8=付点16分音符	=kP16
	24,	//9=8分音符		=kK8
	32,	//10=2分3連符		=kR2
	36,	//11=付点8分音符	=kP8
	48,	//12=4分音符		=kK4
	64,	//13=全3連符		=kR1
	72,	//14=付点4分音符	=kP4
	96,	//15=2分音符		=kK2
	144,	//16=付点2分音符	=kP2
	192,	//17=全音符		=kK1
	80,	//18=kW80		=kW80
	84,	//19=kW84		=kW84
	168,	//20=kW168		=kW168
	255,	//21=kW255		=kW255
};


//==============================================
//音高ｺｰﾄﾞをｵｸﾀｰﾌﾞ･音名に変換するﾃｰﾌﾞﾙ
//　上位ﾆﾌﾞﾙ:ｵｸﾀｰﾌﾞ番号(0起算)(音符ﾃﾞｰﾀ上のｵｸﾀｰﾌﾞ番号とは逆順になっていることに留意すること)
//　下位ﾆﾌﾞﾙ:音名番号(0起算)(音符ﾃﾞｰﾀ上の音名番号とは境界が異なることに留意すること)
//==============================================
static const unsigned char onkou_mei_tbl[]={
	0x58,	//0:Do
	0x59,	//1:DoS/ReF
	0x5a,	//2:Re
	0x5b,	//3:ReS/MiF
	0x40,	//4:Mi
	0x41,	//5:Fa
	0x42,	//6:FaS/SoF
	0x43,	//7:So
	0x44,	//8:SoS/LaF
	0x45,	//9:La
	0x46,	//10:LaS/SiF
	0x47,	//11:Si
	0x48,	//12:Do
	0x49,	//13:DoS/ReF
	0x4a,	//14:Re
	0x4b,	//15:ReS/MiF
	0x30,	//16:Mi
	0x31,	//17:Fa
	0x32,	//18:FaS/SoF
	0x33,	//19:So
	0x34,	//20:SoS/LaF
	0x35,	//21:La
	0x36,	//22:LaS/SiF
	0x37,	//23:Si
	0x38,	//24:Do
	0x39,	//25:DoS/ReF
	0x3a,	//26:Re
	0x3b,	//27:ReS/MiF
	0x20,	//28:Mi
	0x21,	//29:Fa
	0x22,	//30:FaS/SoF
	0x23,	//31:So
	0x24,	//32:SoS/LaF
	0x25,	//33:La
	0x26,	//34:LaS/SiF
	0x27,	//35:Si
	0x28,	//36:Do
	0x29,	//37:DoS/ReF
	0x2a,	//38:Re
	0x2b,	//39:ReS/MiF
	0x10,	//40:Mi
	0x11,	//41:Fa
	0x12,	//42::FaS/SoF
	0x13,	//43:So
	0x14,	//44:SoS/LaF
	0x15,	//45:La
	0x16,	//46:LaS/SiF
	0x17,	//47:Si
	0x18,	//48:Do
	0x19,	//49:DoS/ReF
	0x1a,	//50:Re
	0x1b,	//51:ReS/MiF
	0x00,	//52:Mi
	0x01,	//53:Fa
	0x02,	//54:FaS/SoF
	0x03,	//55:So
	0x04,	//56:SoS/LaF
	0x05,	//57:La
	0x06,	//58:LaS/SiF
	0x07,	//59:Si
	0x08,	//60:Do
	0x09,	//61:DoS/ReF
	0x0a,	//62:Re
	0x0b,	//63:ReS/MiF
};


//==============================================
//音高ﾃｰﾌﾞﾙ
//==============================================
#define	smp_mac(fff)	((unsigned long)fff*256/10*256/25*PWM_PR/10*SONG_PS/4000+5)/10
						//fff=周波数[0.01Hz]
static const unsigned short onkou_tbl[]={
	smp_mac(131851),	//4:Mi
	smp_mac(139691),	//5:Fa
	smp_mac(147998),	//6:FaS/SoF
	smp_mac(156798),	//7:So
	smp_mac(166122),	//8:SoS/LaF
	smp_mac(176000),	//9:La
	smp_mac(186466),	//10:LaS/SiF
	smp_mac(197553),	//11:Si
	smp_mac(209300),	//0:Do
	smp_mac(221746),	//1:DoS/ReF
	smp_mac(234932),	//2:Re
	smp_mac(248902),	//3:ReS/MiF
};


//==============================================
//制御ﾃｰﾌﾞﾙ
//==============================================
static struct KYOTUU kyotuu;			//共通制御ﾃｰﾌﾞﾙ
#if	PART_N>0
static struct SONG song;			//演奏制御ﾃｰﾌﾞﾙ
static struct PART part[PART_N];		//ﾊﾟｰﾄ制御ﾃｰﾌﾞﾙ
#endif
#if	VOICE_N>0
static struct VOICEN voiceN[VOICE_N];		//音声N再生制御ﾃｰﾌﾞﾙ
#endif
#if	VOICE_I>0
static struct VOICEI voiceI;			//音声I再生制御ﾃｰﾌﾞﾙ
#endif
#if	VOICE_C>0
static struct VOICEC voiceC;			//音声C再生制御ﾃｰﾌﾞﾙ
#endif
#if	VOICE_S>0
static struct VOICES voiceS;			//音声S再生制御ﾃｰﾌﾞﾙ
#endif


//==============================================
//PWM出力ﾊﾞｯﾌｧ
//==============================================
static volatile short buf[OUT_BUF_N];		//ﾊﾞｯﾌｧ
static volatile unsigned char buf_write,buf_read;
						//ﾊﾞｯﾌｧの書込み､読込み位置


//==============================================
//ﾐｭｰﾄ設定処理
//==============================================
//未実装


#if PART_N>0
//==============================================
//曲ﾃﾞｰﾀ初期化処理
//==============================================
static void song_init(void)
{
	struct PART *part_pt;
	unsigned char m,*q;

//DBG_C('\n');
	if((song.part_su=song.song_hdr->part_su)>PART_N) song.part_su=PART_N;
						//ｿﾝｸﾞﾃﾞｰﾀの実装ﾊﾟｰﾄ数がｴﾝｼﾞﾝ側の
						//　最大ﾊﾟｰﾄ数を超えていたら
						//　ｴﾝｼﾞﾝ側の最大ﾊﾟｰﾄ数に制限する
//DBG_B(song.part_su);
	song.key=song.song_hdr->key;		//移調度を取込む
//DBG_B(song.key);
	song.onka_psn=song.song_hdr->onka_psn;	//音価ﾌﾟﾘｽｹｰﾙ値を取込む
//DBG_S(song.onka_psn);
	song.song_ps=0;				//演奏ﾌﾟﾘｽｹｰﾗをｸﾘｱ
	song.onka_ps=0;				//音価ﾌﾟﾘｽｹｰﾗをｸﾘｱ
//DBG_D(&song,sizeof(song));
	for(m=0,q=(unsigned char *)part;m<sizeof(part);m++,q++) *q=0;
						//ﾊﾟｰﾄ個別制御ﾃｰﾌﾞﾙをｸﾘｱ
	for(m=0,part_pt=part;m<song.part_su;m++,part_pt++)
						//ﾊﾟｰﾄ個別制御ﾃｰﾌﾞﾙの初期設定
	{
//DBG_C('\n');
//DBG_C('m');
//DBG_B(m);
//DBG_S(part_pt);
		part_pt->song_part=&(song.song_hdr->part[m]);
						//ﾊﾟｰﾄ情報へのﾎﾟｲﾝﾀを取得する
//DBG_S(part_pt->song_part);
		part_pt->onpu=(unsigned short *)part_pt->song_part->onpu;
						//音源波形へのﾎﾟｲﾝﾀを取得する
//DBG_S(part_pt->ongen);
		part_pt->ongen=(struct WAVE_HDR *)part_pt->song_part->ongen;
						//音源波形へのﾎﾟｲﾝﾀを取得する
//DBG_S(part_pt->ongen);
		part_pt->enve=(struct ENVE_HDR *)part_pt->song_part->enve;
						//ｴﾝﾍﾞﾛｰﾌﾟ波形へのﾎﾟｲﾝﾀを取得する
//DBG_S(part_pt->enve);
		part_pt->pitch=(struct PITCH_HDR *)part_pt->song_part->pitch;
						//ﾋﾟｯﾁﾍﾞﾝﾄﾞ波形へのﾎﾟｲﾝﾀを取得する
//DBG_S(part_pt->pitch);
//DBG_D(&part[m],sizeof(part[m]));
	}
}


//==============================================
//曲選択処理(API関数)
//==============================================
static void SONG_SEL(
	unsigned char no)			//曲番号(0は演奏中止)
{

//DBG_C('\n');
//DBG_C('s');
//DBG_B(no);
//DBG_S(song_idx);
	song_idx=(struct SONG_IDX *)((unsigned short)song_idx|0x8000);
						//ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭへ位置付ける
//DBG_S(song_idx);
//DBG_D(song_idx,16);
//DBG_C('\n');
//DBG_B(song.no);
	if(no)					//演奏開始のとき
	{
//DBG_B(song_idx->no);
		if(song.no==no) return;		//演奏中の曲声番号と同じときは戻る
		if(no>song_idx->no) return;	//実装数を超えているときは戻る
		song.no=no;			//曲番号を記憶
//DBG_B(song.no);
//DBG_S(song_idx->song_hdr[song.no-1]);
		song.song_hdr=(struct SONG_HDR *)song_idx->song_hdr[song.no-1];
						//曲ﾍｯﾀﾞへのﾎﾟｲﾝﾀを取得
//DBG_S(song.song_hdr);
//DBG_D(song.song_hdr,64);
		song_init();			//曲ﾃﾞｰﾀを初期化
	}
	else					//演奏中止のとき
	{
		song.no=0;			//演奏終了にする
		song.pcm=0;			//全ﾊﾟｰﾄ分のPWMﾃﾞｭｰﾃｨ値を
						//　ｸﾘｱしておく
	}
//DBG_C('>');
}


//==============================================
//ｵﾙｺﾞｰﾙ演奏処理
//==============================================
static void song_exe(void)
{
	struct PART *part_pt;			//ﾊﾟｰﾄ個別制御ﾃｰﾌﾞﾙﾎﾟｲﾝﾀ
	unsigned char n,m,c;
	short j;
	union					//8ﾋﾞｯﾄｼﾌﾄ演算の効率化
	{
		unsigned short sss;
		unsigned char bbb[2];
	} sssbbb;

//DBG_C('<');
	//初期化
	song.pcm=0;				//全ﾊﾟｰﾄ分のPWM値を0にしておく
	m=0;					//演奏中のﾊﾟｰﾄ数をｸﾘｱしておく

	//音価ﾌﾟﾘｽｹｰﾗを更新
//DBG_S(song.onka_ps);
	if(song.onka_ps) song.onka_ps--;	//音価ﾌﾟﾘｽｹｰﾗが残っていればﾃﾞｸﾘ
	else song.onka_ps=song.onka_psn;	//満了していたら初期化する

	//ﾊﾟｰﾄ演奏処理
	for(n=0,part_pt=part;n<song.part_su;n++,part_pt++)
						//実装ﾊﾟｰﾄ数だけ繰返す
	{
//DBG_B(n);
		if(!part_pt->song_part) continue;
						//演奏が終了しているﾊﾟｰﾄは飛ばす
		m++;				//演奏中のﾊﾟｰﾄ数をｲﾝｸﾘ

		//音符を取出す
//DBG_C('t');
		while(!part_pt->onka_zan)	//音価残が無くなったら次の音符へ進む
						//　通常音符が現れるか､音符終了まで繰返す
						//　つまり､制御音符は一気に処理する
		{
//DBG_C('\n');
//DBG_C('>');
//DBG_B(n);
//DBG_C('+');
//DBG_S(part_pt->song_part->onpu);
//DBG_S(part_pt->onpu_of);
			if(part_pt->onpu_of==0xffff)
						//KB演奏のときは
			{
//DBG_C('b');
				part_pt->onpu_cd=part_pt->onpu_kb;
						//KB演奏用ﾊﾞｯﾌｧから音符ｺｰﾄﾞを取出す
				part_pt->onpu_kb=0;
						//KB演奏用ﾊﾞｯﾌｧをｸﾘｱしておく
			}
			else			//ｵﾙｺﾞｰﾙ演奏のときは
				part_pt->onpu_cd=*(part_pt->onpu+part_pt->onpu_of++);
						//音符ｺｰﾄﾞを取得し､音符ｽﾃｯﾌﾟを進めておく
//DBG_S(part_pt->onpu_cd);
			if(part_pt->onpu_cd&0x2000)//機能ｺｰﾄﾞ2のとき
			{
				if(part_pt->onpu_cd&0x1000)
						//ﾘﾋﾟｰﾄ分岐以外のとき
				{
					if(part_pt->onpu_cd&0x0800)
							//波形切換えのとき
					{
//DBG_C('w');
						switch(part_pt->onpu_cd&0x0700)
						{
						case 0x0000:	//音源波形のとき
//DBG_C('o');
							part_pt->ongen=
								(struct WAVE_HDR *)
								*(part_pt->onpu+
								part_pt->onpu_of++);
								//音源波形ｱﾄﾞﾚｽを取得し､
								//　音符ｽﾃｯﾌﾟを進めておく
//DBG_S(part_pt->ongen);
							break;
						case 0x0100:	//ｴﾝﾍﾞﾛｰﾌﾟ波形のとき
//DBG_C('e');
							part_pt->enve=
								(struct ENVE_HDR *)
								*(part_pt->onpu+
								part_pt->onpu_of++);
								//ｴﾝﾍﾞﾛｰﾌﾟ波形ｱﾄﾞﾚｽを取得し､
								//　音符ｽﾃｯﾌﾟを進めておく
//DBG_S(part_pt->enve);
							break;
						case 0x0200:	//ﾋﾟｯﾁﾍﾞﾝﾄﾞ波形のとき
//DBG_C('p');
							part_pt->pitch=
								(struct PITCH_HDR *)
								*(part_pt->onpu+
								part_pt->onpu_of++);
								//ﾋﾟｯﾁﾍﾞﾝﾄﾞ波形ｱﾄﾞﾚｽを取得し､
								//　音符ｽﾃｯﾌﾟを進めておく
//DBG_S(part_pt->pitch);
							break;
						}
					}
					else if(part_pt->onpu_cd&0x0400)
							//各種値設定のとき
					{
//DBG_C('k');
						switch(part_pt->onpu_cd&0x0300)
						{
						case 0x0000:	//ﾍﾞﾛｼﾃｨ設定のとき
//DBG_C('v');
							part_pt->velo=
								((unsigned long)
								(part_pt->onpu_cd&0x00ff)*
								PWM_STEP)/256;
//DBG_S(part_pt->velo);
							break;
						case 0x0100:	//ｴﾝﾍﾞﾛｰﾌﾟﾀｲﾑ設定のとき
//DBG_C('e');
							part_pt->enve_psn=
								part_pt->song_part->enve_psn*
								(part_pt->onpu_cd&0x00ff);
//DBG_S(part_pt->enve_psn);
							break;
						case 0x0200:	//ﾃﾝﾎﾟ設定のとき
//DBG_C('t');

							song.onka_psn=
								(song.song_hdr->onka_psn*
								(part_pt->onpu_cd&0x00ff))>>7;
//DBG_S(song.onka_psn);
							break;
						case 0x0300:	//ﾋﾟｯﾁﾍﾞﾝﾄﾞﾀｲﾑ設定のとき
//DBG_C('p');

							part_pt->pitch_psn=
								part_pt->song_part->pitch_psn*
								(part_pt->onpu_cd&0x00ff);
//DBG_S(part_pt->pitch);
							break;
						}

					}
					else		//無条件分岐のとき
					{
//DBG_C('j');
						part_pt->onpu_of=part_pt->onpu_cd&0x03ff;
							//分岐先を設定する
//DBG_S(part_pt->onpu_of);
					}
				}
				else		//ﾘﾋﾟｰﾄ分岐のとき
				{
//DBG_C('r');
					c=(part_pt->onpu_cd&0x0c00)>>10;
							//ﾘﾋﾟｰﾄ番号を得る
//DBG_B(c);
//DBG_B(part_pt->rpt[c]);
					if(part_pt->rpt[c])
							//ﾘﾋﾟｰﾄ回数残があるとき
					{
//DBG_C('z');
						part_pt->rpt[c]--;
							//ﾘﾋﾟｰﾄ回数残をﾃﾞｸﾘする
//DBG_B(part_pt->rpt[c]);
						part_pt->onpu_of=part_pt->onpu_cd&0x03ff;
							//分岐先を設定する
//DBG_S(part_pt->onpu_of);
					}
				}
			}
			else if(part_pt->onpu_cd&0x1f00)
						//演奏音符のとき
			{
//DBG_C('\n');
//DBG_C('u');
				sssbbb.sss=part_pt->onpu_cd;
						//音符の音価ｺｰﾄﾞから音価残を設定
				part_pt->onka_zan=onka_tbl[((sssbbb.bbb[1]&0x1f)-1)];
//DBG_B(part_pt->onka_zan);
				if(part_pt->onpu_cd&0x007f)
						//発音音符のとき
				{
//DBG_C('\n');
//DBG_C('h');
//DBG_B(song.key);
					c=((part_pt->onpu_cd&0x003f)+song.key)&0x3f;
						//音高に移調度を加味して､範囲内に規制する
//DBG_B(c);
					c=onkou_mei_tbl[c];
						//ｵｸﾀｰﾌﾞ番号と音名ｺｰﾄﾞを得る
//DBG_B(c);
					part_pt->ongen_tobi=onkou_tbl[c&0x0f];
						//音名のｻﾝﾌﾟﾙ飛び数を得る
//DBG_S(part_pt->ongen_tobi);
					if(c>>=4) part_pt->ongen_tobi>>=c;
						//ｵｸﾀｰﾌﾞ番号でｼﾌﾄする
//DBG_S(part_pt->ongen_tobi);
				}
				else part_pt->ongen_tobi=0;
						//休符のときはｻﾝﾌﾟﾙ飛び数を0にする
//DBG_S(part_pt->ongen_tobi);
				if(!(part_pt->onpu_cd&0x0080))
						//ﾀｲ･ｽﾗｰでないとき
				{
//DBG_C('c');
					part_pt->enve_of=0;
						//ｴﾝﾍﾞﾛｰﾌﾟ波形ﾃｰﾌﾞﾙｵﾌｾｯﾄをｸﾘｱ
					part_pt->enve_ps=0;
						//ｴﾝﾍﾞﾛｰﾌﾟ処理対応のﾌﾟﾘｽｹｰﾗを初期化
					part_pt->pitch_of=0;
						//ﾋﾟｯﾁﾍﾞﾝﾄﾞ波形ﾃｰﾌﾞﾙｵﾌｾｯﾄをｸﾘｱ
					part_pt->pitch_ps=0;
						//ﾋﾟｯﾁﾍﾞﾝﾄﾞ処理対応のﾌﾟﾘｽｹｰﾗを初期化
				}
			}
			else if(part_pt->onpu_cd&0x0040)
						//ﾘﾋﾟｰﾄ回数設定のとき
			{
//DBG_C('r');
				c=(part_pt->onpu_cd&0x0030)>>4;
						//ﾘﾋﾟｰﾄ番号を得る
//DBG_B(c);
				part_pt->rpt[c]=part_pt->onpu_cd&0x000f;
//DBG_B(part_pt->rpt[c]);
			}
			else if(part_pt->onpu_cd&0x0020)
						//転調設定のとき
			{
//DBG_C('i');
				if((c=part_pt->onpu_cd&0x001f)==0)
					song.key=song.song_hdr->key;
							//増減値が0のときは
							//　ｿﾝｸﾞﾍｯﾀﾞのｷｰに戻す
				else
				{			//増減値が0でなければ
					song.key+=c;	//ｶﾚﾝﾄのｷｰから増減する
					if(c>15) song.key-=32;
							//負数のときに是正する
				}
//DBG_B(song.key);
			}
			else if(part_pt->onpu_cd&0x0010)
			{
						//KB演奏移行のとき
				part_pt->onpu_of=0xffff;//KB演奏にする
//DBG_S(part_pt->onpu_of);
			}
			else break;		//演奏終了のとき
		}

		//音符の発音
//DBG_C('h');
//DBG_B(part_pt->onka_zan);
		if(part_pt->onka_zan)		//音価残があれば(音符終了でなければ)
						//　演奏処理を実行する
		{

			//音価を更新
//DBG_C('a');
//DBG_S(song.onka_ps);
			if(!song.onka_ps)	//音価ﾌﾟﾘｽｹｰﾗが満了していたら
				part_pt->onka_zan--;
						//音価残をﾃﾞｸﾘする
//DBG_B(part_pt->onka_zan);

			//発音処理
//DBG_B(part_pt->ongen_tobi);
			if(part_pt->ongen_tobi)	//発音音符のとき
			{

				//ｴﾝﾍﾞﾛｰﾌﾟ処理
//DBG_C('\n');
//DBG_C('e');
//DBG_S(part_pt->enve_psn);
				if(part_pt->enve_psn)
						//ｴﾝﾍﾞﾛｰﾌﾟが設定されているときは
						//　ｴﾝﾍﾞﾛｰﾌﾟ処理を行う
				{
//DBG_C('s');
//DBG_S(part_pt->enve_ps);
					if(!part_pt->enve_ps)
						//ｴﾝﾍﾞﾛｰﾌﾟ処理のﾀｲﾐﾝｸﾞのとき
					{
//DBG_C('t');
//DBG_S(part_pt->velo);
//DBG_B(part_pt->enve_of);
//DBG_B(part_pt->enve->data[part_pt->enve_of]);
						part_pt->velo_enve=((unsigned long)
							part_pt->velo*
							part_pt->enve->
							data[part_pt->enve_of])/256;
						//ｴﾝﾍﾞﾛｰﾌﾟ処理後のﾍﾞﾛｼﾃｨ値を求める
//DBG_S(part_pt->velo_enve);

//DBG_B(part_pt->enve->smp);
						//ｻﾝﾌﾟﾙｵﾌｾｯﾄを進める
						if(part_pt->enve_of<
							part_pt->enve->smp)
							part_pt->enve_of++;
							//ｻﾝﾌﾟﾙｵﾌｾｯﾄを進めて､最後に規制する
//DBG_B(part_pt->enve_of);
					}
					if(part_pt->enve_ps++>part_pt->enve_psn)
					{
						//ｴﾝﾍﾞﾛｰﾌﾟのﾌﾟﾘｽｹｰﾗをｲﾝｸﾘして満了したら
						part_pt->enve_ps=0;
							//ｴﾝﾍﾞﾛｰﾌﾟのﾌﾟﾘｽｹｰﾗをｸﾘｱ
					}
				}
				else		//ｴﾝﾍﾞﾛｰﾌﾟが設定されていないときは
				{
					part_pt->velo_enve=part_pt->velo;
						//　ﾍﾞﾛｼﾃｨ設定値をそのまま使う
				}
//DBG_S(part_pt->velo_enve);

				//音源ｻﾝﾌﾟﾙ値を得る
//DBG_C('\n');
//DBG_C('w');
//DBG_S(part_pt->ongen_of);
				sssbbb.sss=part_pt->ongen_of;
//DBG_B(sssbbb.bbb[1]);
				j=(short)(part_pt->ongen->data[sssbbb.bbb[1]])-128;
						//音源ｻﾝﾌﾟﾙ値を得る
//DBG_S(j);
				j=((long)part_pt->velo_enve*j)/256;
						//ﾍﾞﾛｼﾃｨを加味する
//DBG_S(j);
				song.pcm+=j;	//全ﾊﾟｰﾄ分のPWMﾃﾞｭｰﾃｨ値に､
						//　このﾊﾟｰﾄ分を加算する
//DBG_S(song.pcm);

				//音源ｻﾝﾌﾟﾙｵﾌｾｯﾄを進める
//DBG_C('o');
//DBG_S(part_pt->ongen_of);
//DBG_S(part_pt->ongen_tobi);
				part_pt->ongen_of+=part_pt->ongen_tobi;
						//波形ﾃﾞｰﾀのｵﾌｾｯﾄを進めて､
						//　ｻﾝﾌﾟﾙ数は256固定のため
						//　ｵｰﾊﾞﾌﾛｰは無視する
//DBG_S(part_pt->ongen_of);

				//ﾋﾟｯﾁﾍﾞﾝﾄﾞ処理
//DBG_C('\n');
//DBG_C('p');
				if(part_pt->pitch_psn)
						//ﾋﾟｯﾁﾍﾞﾝﾄﾞが設定されているときは
						//　ﾋﾟｯﾁﾍﾞﾝﾄﾞ処理を行う
				{
//DBG_C('\n');
//DBG_S(part_pt->pitch_ps);
					if(!part_pt->pitch_ps)
						//ﾋﾟｯﾁﾍﾞﾝﾄﾞ処理のﾀｲﾐﾝｸﾞのとき
					{

						//ﾋﾟｯﾁﾍﾞﾝﾄﾞｻﾝﾌﾟﾙ値を得る
						j=part_pt->pitch->data
							[part_pt->pitch_of];
							//ﾋﾟｯﾁﾍﾞﾝﾄﾞｻﾝﾌﾟﾙ値を得る
//DBG_S(j);
//DBG_S(part_pt->ongen_tobi);
						part_pt->ongen_tobi=
							part_pt->ongen_tobi+j-128;
							//音源ｻﾝﾌﾟﾙ飛び数を増減する

						//ﾋﾟｯﾁﾍﾞﾝﾄﾞｻﾝﾌﾟﾙｵﾌｾｯﾄを進める
//DBG_S(part_pt->ongen_tobi);
						if(part_pt->pitch_of<
							part_pt->pitch->smp)
							part_pt->pitch_of++;
							//ｻﾝﾌﾟﾙｵﾌｾｯﾄを進めて､最後に規制する
//DBG_B(part_pt->pitch_of);
					}
					if(part_pt->pitch_ps++>part_pt->pitch_psn)
					{
						//ﾋﾟｯﾁﾍﾞﾝﾄﾞのﾌﾟﾘｽｹｰﾗをｲﾝｸﾘして満了したら
						part_pt->pitch_ps=0;
							//ﾋﾟｯﾁﾍﾞﾝﾄﾞのﾌﾟﾘｽｹｰﾗをｸﾘｱ
//DBG_S(part_pt->pitch_ps);
					}
				}
			}
		}

		else				//音符終了のとき
		{
			//ﾊﾟｰﾄ終了処理
//DBG_C('t');
			if(part_pt->onpu_of!=0xffff)
						//ｵﾙｺﾞｰﾙ演奏のときは
				part_pt->song_part=0;
						//ﾊﾟｰﾄ演奏終了を表示する
		}
//DBG_C('r');
	}
//DBG_B(m);
	if(!m)					//全ﾊﾟｰﾄが終了したら
	{
//DBG_S(song.song_hdr->next);
		if(song.song_hdr->next)		//連続演奏するとき
		{
			song.song_hdr=(struct SONG_HDR *)song.song_hdr->next;
						//曲ﾍｯﾀﾞへのﾎﾟｲﾝﾀを取得
//DBG_S(song.song_hdr);
//DBG_D(song.song_hdr,64);
			song_init();		//曲ﾃﾞｰﾀを初期化
		}
		else				//単曲演奏のとき
		{
			song.no=0;		//曲演奏終了の表示
			CB_SONG_END();		//演奏終了時ｺｰﾙﾊﾞｯｸ関数を呼ぶ
		}
	}
//DBG_C('>');
}
#endif


#if VOICE_N>0
//==============================================
//音声N選択処理(API関数)
//==============================================
static void VOICEN_SEL(				//戻り値無し
	unsigned char ch,			//ch番号
	unsigned char no)			//音声番号(0は再生中止)
{
	struct VOICEN *voiceN_pt;		//音声N再生制御ﾃｰﾌﾞﾙﾎﾟｲﾝﾀ

//DBG_C('\n');
//DBG_C('s');
//DBG_B(ch);
//DBG_B(no);
//DBG_D(voiceN_idx,sizeof(voiceN_idx));
//DBG_C('i');
	voiceN_pt=voiceN+ch;			//音声N再生制御ﾃｰﾌﾞﾙﾎﾟｲﾝﾀを設定
	if(no)					//再生開始のとき
	{
		if(no>sizeof(voiceN_idx)/sizeof(voiceN_idx[0])) return;
						//実装数を超えているときは戻る
		if(voiceN_pt->no!=no)		//発声中の音声番号と異なるときのみ
						//　音声を切り替える
		{
			voiceN_pt->no=no--;	//音声番号を設定
			voiceN_pt->begin=voiceN_idx[no].adr;
						//音声ﾃﾞｰﾀの開始ｱﾄﾞﾚｽを設定
//DBG_S(voiceN_pt->begin);
			voiceN_pt->end=voiceN_pt->begin+voiceN_idx[no].len;
						//音声ﾃﾞｰﾀの終了ｱﾄﾞﾚｽを設定
//DBG_S(voiceN_pt->end);
			voiceN_pt->psn=voiceN_idx[no].psn;
						//再生処理ﾌﾟﾘｽｹｰﾙ値を設定
//DBG_B(voiceN_pt->psn);
			voiceN_pt->pcm=0;	//PCM値を初期化
//DBG_B(voiceN_pt->pcm);
		}
	}
	else					//再生中断のとき
	{
		voiceN_pt->no=0;		//再生終了にする
	}
//DBG_D(voiceN_pt,sizeof(voiceN[0]));
}


//==============================================
//音声N再生処理
//==============================================
static void voiceN_exe(
	unsigned char ch)			//ch番号
{
	struct VOICEN *voiceN_pt;		//音声N再生制御ﾃｰﾌﾞﾙﾎﾟｲﾝﾀ

//DBG_C('\n');
//DBG_C('p');
//DBG_B(ch);
	voiceN_pt=voiceN+ch;			//音声N再生制御ﾃｰﾌﾞﾙﾎﾟｲﾝﾀを設定する
	voiceN_pt->pcm=*voiceN_pt->begin++-128;//音声ﾃﾞｰﾀを取出取出して､
						//　8ﾋﾞｯﾄPCM形式をsignedに変換
//DBG_S(voiceN_pt->pcm);
//DBG_S(voiceN_vol[ch]);
	voiceN_pt->pcm=(long)voiceN_pt->pcm*voiceN_vol[ch]/128;
						//音量配分を掛ける
//DBG_S(voiceN_pt->pcm);
	if(voiceN_pt->begin==voiceN_pt->end)	//音声ﾃﾞｰﾀが最後のとき
	{
//DBG_C('e');
		voiceN_pt->no=0;		//再生終了にする
		CB_VOICEN_END(ch);		//音声再生終了処理(ｺｰﾙﾊﾞｯｸ関数)を呼出す
	}
}
#endif


#if VOICE_I>0				//I2Cﾒﾓﾘを使うとき
#ifdef I2C_SOFT				//I2Cをｿﾌﾄ実装するとき
//==============================================
//I2Cｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_start(void)
{

//DBG_C('s');
	I2C_SCL_H;				//SCLをH(High-Z)
	wait_1us();
	I2C_SDA_L;				//SCLがHのままSDAをL
	wait_1us();
	I2C_SCL_L;				//SCLをL
	wait_1us();
	I2C_SDA_H;				//SDAをH(High-Z)
	wait_1us();
}


//==============================================
//I2Cｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_stop(void)
{

//DBG_C('p');
	I2C_SDA_L;				//SDAをL
	wait_1us();
	I2C_SCL_H;				//SCLをH(High-Z)
	wait_1us();
	I2C_SDA_H;				//SCLがHのままSDAをH(High-Z)
	wait_1us();
}


//==============================================
//I2C送信
//==============================================
static void i2c_send(
	unsigned char data)			//送信ﾃﾞｰﾀ
{
	unsigned char n=8;

//DBG_C('d');
	while(n--)				//8ﾋﾞｯﾄ分繰返す
	{
		if(data&0x80) I2C_SDA_H;	//送信ﾋﾞｯﾄを設定する
		else I2C_SDA_L;
		data<<=1;			//ﾋﾞｯﾄを進める
		wait_1us();
		I2C_SCL_H;			//SCLをH(High-Z)
		wait_1us();
		I2C_SCL_L;			//SCLをL
		wait_1us();
	}
	I2C_SDA_H;				//SDAをHigh-Z(ACK受信)
	wait_1us();
	I2C_SCL_H;				//SCLをH(High-Z)
	wait_1us();
	I2C_SCL_L;				//SCLをL
	wait_1us();
}


//==============================================
//I2C受信+ACK応答
//==============================================
static unsigned char i2c_recv_ack(void)		//受信ﾃﾞｰﾀを返す
{
	unsigned char n=8,data=0;

//DBG_C('k');
	while(n--)				//8ﾋﾞｯﾄ分繰返す
	{
		I2C_SCL_H;			//SCLをH(High-Z)
		wait_1us();
		data<<=1;			//ﾋﾞｯﾄを進める
		if(I2C_SDA) data|=1;		//受信ﾋﾞｯﾄを取込む
		I2C_SCL_L;			//SCLをL
		wait_1us();
	}
	I2C_SDA_L;				//SDAをL(ACK)
	wait_1us();
	I2C_SCL_H;				//SCLをH(High-Z)
	wait_1us();
	I2C_SCL_L;				//SCLをL
	I2C_SDA_H;				//SDAをH(High-Z)
	wait_1us();
	return(data);				//受信ﾃﾞｰﾀを返す
}


//==============================================
//I2C受信+NOACK応答
//==============================================
static unsigned char i2c_recv_noack(void)	//受信ﾃﾞｰﾀを返す
{
	unsigned char n=8,data=0;

//DBG_C('n');
	while(n--)				//8ﾋﾞｯﾄ分繰返す
	{
		I2C_SCL_H;			//SCLをH(High-Z)
		wait_1us();
		data<<=1;			//ﾋﾞｯﾄを進める
		if(I2C_SDA) data|=1;		//受信ﾋﾞｯﾄを取込む
		I2C_SCL_L;			//SCLをL
		wait_1us();
	}
	I2C_SDA_H;				//SDAをH(High-Z)(NOACK)
	wait_1us();
	I2C_SCL_H;				//SCLをH(High-Z)
	wait_1us();
	I2C_SCL_L;				//SCLをL
	wait_1us();
	return(data);				//受信ﾃﾞｰﾀを返す
}


#else					//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
//==============================================
//I2Cｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_start(
	unsigned char slave)			//ｽﾚｰﾌﾞｱﾄﾞﾚｽ
{
	unsigned char w;

//DBG_C('s');
//DBG_B(slave);
	//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ後にｽﾚｰﾌﾞｱﾄﾞﾚｽを送信
//DBG_B(TWI0.MSTATUS);
	TWI0.MADDR=slave;			//ｽﾚｰﾌﾞｱﾄﾞﾚｽをｾｯﾄ
//DBG_B(TWI0.MSTATUS);

	//ACKを待つ
	w=0;
	while(!(TWI0.MSTATUS&TWI_RIF_bm)&&!(TWI0.MSTATUS&TWI_WIF_bm))
						//送受信完了を待つ
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm);	//送受信完了をｸﾘｱする
//DBG_B(TWI0.MSTATUS);
}


//==============================================
//I2Cﾘﾋﾟｰﾄｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_rep_start(
	unsigned char slave)			//ｽﾚｰﾌﾞｱﾄﾞﾚｽ
{

//DBG_C('e');
	//ｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ後にｽﾚｰﾌﾞｱﾄﾞﾚｽを送信
//DBG_B(TWI0.MSTATUS);
	TWI0.MADDR=slave;			//ｽﾚｰﾌﾞｱﾄﾞﾚｽをｾｯﾄ
//DBG_B(TWI0.MSTATUS);
}


//==============================================
//I2Cｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
//==============================================
static void i2c_stop(void)
{

//DBG_C('p');
	TWI0.MCTRLB|=TWI_MCMD_STOP_gc;		//ｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
//DBG_B(TWI0.MSTATUS);
}


//==============================================
//I2Cﾃﾞｰﾀ送信
//==============================================
static void i2c_send(
	unsigned char data)
{
	unsigned char w;

//DBG_C('d');
//DBG_B(data);
	//ﾃﾞｰﾀを送信
//DBG_B(TWI0.MSTATUS);
	TWI0.MDATA=data;			//送信ﾃﾞｰﾀをｾｯﾄ
//DBG_B(TWI0.MSTATUS);

	//送信完了を待つ
	w=0;
	while(!(TWI0.MSTATUS&TWI_WIF_bm))	//送信完了を待つ 
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
}


//==============================================
//I2C受信+ACK応答
//==============================================
static unsigned char i2c_recv_ack(void)
{
	unsigned char data;
	unsigned char w;

//DBG_C('a');
	//受信を待つ
	w=0;
	while(!(TWI0.MSTATUS&TWI_RIF_bm))	//受信完了を待つ
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm);	//送受信をｸﾘｱする
//DBG_B(TWI0.MSTATUS);
	TWI0.MCTRLB&=~(1<<TWI_ACKACT_bp);	//ACK応答をｾｯﾄする
//DBG_B(TWI0.MCTRLB);
	data=TWI0.MDATA;			//受信ﾃﾞｰﾀを取出す
//DBG_B(data);
	TWI0.MCTRLB|=TWI_MCMD_RECVTRANS_gc;	//ACK応答する
//DBG_B(TWI0.MCTRLB);
	return(data);					
}


//==============================================
//I2C受信+NOACK応答
//==============================================
static unsigned char i2c_recv_noack(void)
{
	unsigned char data;
	unsigned char w;

//DBG_C('n');
	//受信を待つ
	w=0;
	while(!(TWI0.MSTATUS&TWI_RIF_bm))	//受信完了を待つ
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm);	//送受信をｸﾘｱする
//DBG_B(TWI0.MSTATUS);
	TWI0.MCTRLB|=TWI_ACKACT_NACK_gc;	//NACK応答をｾｯﾄする
//DBG_B(TWI0.MCTRLB);
	data=TWI0.MDATA;			//受信ﾃﾞｰﾀを取出す
//DBG_B(data);
	return(data);					
}
#endif


//==============================================
//音声I選択処理(API関数)
//==============================================
static void VOICEI_SEL(				//戻り値無し
	unsigned short no)			//音声番号(0は再生中止)
{


//I2C評価中
#if 0
unsigned char dddd;
for(;;)
{
	wait_ms(10);
//DBG_C('\n');

	i2c_start();
	i2c_addr(0xa0);
	i2c_send(0x55);
	i2c_send(0x02);
	i2c_start();
	i2c_addr(0xa1);
	dddd=i2c_recv_ack();
//DBG_B(dddd);
	dddd=i2c_recv_ack();
//DBG_B(dddd);
	dddd=i2c_recv_noack();
//DBG_B(dddd);
	i2c_stop();
//	for(;;);
}
#endif


//DBG_C('\n');
//DBG_C('s');
//DBG_S(no);
//DBG_D(voiceI_idx,sizeof(voiceI_idx));
//DBG_C('i');
	if(voiceI.no!=no)			//発声中の音声番号と異なるときは
	{
		if(voiceI.no)			//再生中のときは
		{
			wait_us(50);		//おまじない(通常ﾙｰﾄの転送終了を待つ)
						//　400kbpsでの適正値
			i2c_recv_noack();	//受信+NOACK応答
			i2c_stop();		//I2Cｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
			voiceI.no=0;		//再生停止にする
			voiceI.pcm=0;		//PCM値を初期化
//DBG_B(voiceI.pcm);
		}
	}

	if(no)					//再生開始のとき
	{
		if(no>sizeof(voiceI_idx)/sizeof(voiceI_idx[0])) return;
						//実装数を超えているときは戻る
		voiceI.no=no--;			//音声番号を設定して､番号を0起算にする
		voiceI.begin=voiceI_idx[no].adr;//音声ﾃﾞｰﾀの開始ｱﾄﾞﾚｽを設定
//DBG_S(voiceI.begin);
		voiceI.end=voiceI.begin+voiceI_idx[no].len;
						//音声ﾃﾞｰﾀの終了ｱﾄﾞﾚｽを設定
//DBG_S(voiceI.end);
		voiceI.psn=voiceI_idx[no].psn;	//再生処理ﾌﾟﾘｽｹｰﾙ値を設定
//DBG_B(voiceI.psn);
		voiceI.sla=voiceI_idx[no].sla;	//I2Cｽﾚｰﾌﾞｱﾄﾞﾚｽを設定
//DBG_B(voiceI.sla);
#ifdef I2C_SOFT				//I2Cをｼﾌﾄ実装するとき
		i2c_start();			//I2Cｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
		i2c_send(voiceI.sla);		//ｽﾚｰﾌﾞｱﾄﾞﾚｽ(W)送信
#else					//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
		i2c_start(voiceI.sla);		//I2Cｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ､ｽﾚｰﾌﾞｱﾄﾞﾚｽ(W)送信
#endif
		i2c_send(voiceI.begin>>8);	//ｱﾄﾞﾚｽ上位送信
		i2c_send(voiceI.begin);		//ｱﾄﾞﾚｽ下位送信
#ifdef I2C_SOFT				//I2Cをｼﾌﾄ実装するとき
		i2c_start();			//I2Cｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ
		i2c_send(voiceI.sla|1);		//ｽﾚｰﾌﾞｱﾄﾞﾚｽ+読込み指定送信
#else					//内蔵I2Cﾓｼﾞｭｰﾙを使うとき
		i2c_rep_start(voiceI.sla|1);	//I2Cﾘﾋﾟｰﾄｽﾀｰﾄｺﾝﾃﾞｨｼｮﾝ､ｽﾚｰﾌﾞｱﾄﾞﾚｽ(R)送信
#endif
	}
//DBG_D(&voiceI,sizeof(voiceI));
}


//==============================================
//音声I再生処理
//==============================================
static void voiceI_exe(void)
{
	unsigned char data;

//DBG_C('\n');
//DBG_C('p');
//DBS_H;
	if(++voiceI.begin==voiceI.end)		//音声ﾃﾞｰﾀが最後のとき
	{
		data=i2c_recv_noack();		//受信+NOACK応答
	}
	else					//音声ﾃﾞｰﾀが途中のとき
	{
		data=i2c_recv_ack();		//受信+ACK応答
	}
//DBS_L;
//DBG_B(data);
	voiceI.pcm=(short)data-128;		//音声ﾃﾞｰﾀをsignedに変換
//DBG_S(voiceI.pcm);
	voiceI.pcm=(long)voiceI.pcm*((long)VOICEI_VOL*PWM_STEP/100)/128;
						//音量配分を掛ける
//DBG_S(voiceI.pcm);
	if(voiceI.begin==voiceI.end)		//音声ﾃﾞｰﾀが最後のとき
	{
//DBG_C('e');
		voiceI.no=0;			//再生終了にする
		i2c_stop();			//I2Cｽﾄｯﾌﾟｺﾝﾃﾞｨｼｮﾝ
		voiceI.pcm=0;			//PCM値を初期化
		CB_VOICEI_END();		//音声再生終了処理(ｺｰﾙﾊﾞｯｸ関数)を呼出す
	}
}
#endif


#if (VOICE_C+VOICE_S)>0			//SDまたはSPIﾒﾓﾘを使うとき
#ifdef SPI_SOFT				//SPIをｿﾌﾄ実装するとき
//==============================================
//SSのﾈｹﾞｰﾄ待ち
//==============================================
#ifdef	SS_WAIT_TIME			//SS待ち時間が定義されているとき
#define	SPI_SS_WAIT()	wait_us(SS_WAIT_TIME);	//SSがﾈｹﾞｰﾄするまで待つ
#else					//SS待ち時間が定義されていないとき
#define	SPI_SS_WAIT()				//SSﾈｹﾞｰﾄ待ちをしない
#endif


//==============================================
//SPI送受信
//==============================================
static unsigned char spi_trans(			//受信したﾃﾞｰﾀを返す
	unsigned char data,			//送信するﾃﾞｰﾀ
	unsigned char sck_h)			//最終ﾋﾞｯﾄのSCKの扱い
						//　(2線SPI時のﾊﾟﾜｰﾀﾞｳﾝのため)
						//　0=Lにする､1=Hを保持する
{
	unsigned char c=8;

//DBS_H;
//DBG_C('(');
//DBG_B(data);
	while(c--)
	{
		if(data&0x80) SPI_MOSI_H;	//ﾃﾞｰﾀﾋﾞｯﾄを
		else SPI_MOSI_L;		//　MOSIに乗せる
#if defined(SPI2)||defined(SPI3)	//2線SPIまたは3線SPIのとき
		SPI_MOSI_OUT;			//MOSIを出力ﾓｰﾄﾞ
#endif
#ifdef SPI2 				//2線SPIのとき
		__disable_irq();		//割込み禁止
#endif
		SPI_SCK_H;			//SCKをH
#if defined(SPI2)||defined(SPI3)	//2線SPIまたは3線SPIのとき
		SPI_MISO_IN;			//MISOを入力ﾓｰﾄﾞ
		wait_1us();
#endif
		data<<=1;			//ﾃﾞｰﾀを次に進める
		if(SPI_MISO) data++;		//MISOをﾃﾞｰﾀに取込む
		if(c||(!sck_h))			//最終ﾋﾞｯﾄ以外かﾊﾟﾜｰﾀﾞｳﾝ以外は
		{
			SPI_SCK_L;		//SCKをL
		}
#ifdef SPI2 				//2線SPIのとき
		__enable_irq();			//割込み許可
#endif
	};
//DBG_B(data);
//DBG_C(')');
//DBS_L;
	return(data);				//受信したﾃﾞｰﾀを返す
}


//==============================================
//SPIﾘｾｯﾄ
//==============================================
static void spi_reset(void)
{

	SPI_SS_H;				//SSをﾈｹﾞｰﾄする
	SPI_SS_WAIT();				//SSﾈｹﾞｰﾄ時間を待つ
}


#else					//内蔵SPIﾓｼﾞｭｰﾙを使うとき
//==============================================
//内蔵SPIﾓｼﾞｭｰﾙを使うときのﾏｸﾛ置換え
//==============================================
#define	SPI_SS_WAIT()				//SSﾈｹﾞｰﾄ待ちをしない
#define spi_trans(x,y) spi_trans_(x)		//最終ﾋﾞｯﾄのSCK扱いを無視する


//==============================================
//SPI送受信
//==============================================
static unsigned char spi_trans_(		//受信したﾃﾞｰﾀを返す
	unsigned char data)			//送信するﾃﾞｰﾀ
{

//DBS_H;
//DBG_C('(');
//DBG_B(data);
	SPI0.DATA=data;				//送受信開始
	while(!(SPI0.INTFLAGS&0x80));		//送受信完了を待つ
//DBG_B(data);
//DBG_C(')');
//DBS_L;
	return(SPI0.DATA);			//受信したﾃﾞｰﾀを返す
}


//==============================================
//SPIﾘｾｯﾄ
//==============================================
static void spi_reset(void)
{

	SPI_SS_H;				//SSをﾈｹﾞｰﾄする
}
#endif
#endif


#if VOICE_C>0				//SDを使うとき
//==============================================
//SDからｺﾏﾝﾄﾞﾚｽﾎﾟﾝｽを受信する
//==============================================
static unsigned char mmsd_resp(void)		//ﾚｽﾎﾟﾝｽを返す(0=OK､0x11=ﾀｲﾑｱｳﾄ)
{
	unsigned char n=255,res;

//DBG_C('!');
	while(n--)
	{
		res=spi_trans(0xff,0);
//DBG_B(res);
		if((res&0x80)==0) break;	//b7が0のときは抜ける
	}
	return(res);				//ﾚｽﾎﾟﾝｽを返す
}


//==============================================
//SDｱｸｾｽを初期化する
//==============================================
static unsigned char mmsd_init(void)		//ﾚｽﾎﾟﾝｽを返す(0=OK､0x11=ﾀｲﾑｱｳﾄ､その他ｴﾗｰ)
{
	unsigned char n,res;

	//SDを非選択にする
//DBG_C('\n');
//DBG_C('u');
	spi_reset();				//SPIをﾘｾｯﾄする

	//ﾀﾞﾐｰｸﾛｯｸを送信する
//DBG_C('d');
	for(n=0;n<10;n++)			//74以上(80)の
	{
		spi_trans(0xff,0);		//ﾀﾞﾐｰｸﾛｯｸを送信する
	}

	//SDを選択する
//DBG_C('s');
	SPI_SS_L;				//ﾁｯﾌﾟｾﾚｸﾄ
	wait_us(10);
	spi_trans(0xff,0);			//ﾀﾞﾐｰｸﾛｯｸを送信する

//DBG_C('r');
	spi_trans(CMD0,0);			//CMD0を送信する
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(CMD0CRC,0);
	res=mmsd_resp();			//ﾚｽﾎﾟﾝｽを得る
//DBG_B(res);
	if(res&0x80) return(0x11);		//ﾚｽﾎﾟﾝｽのMSBが1のときはﾀｲﾑｱｳﾄを返す
	if(res!=0x01) return(0x12);		//ｱｲﾄﾞﾙでなかったらｴﾗｰを返す

	//初期化の完了を待つ
//DBG_C('i');
	do
	{
		spi_trans(0xff,0);		//ﾀﾞﾐｰ転送しないとCMD1が0x05になる
		spi_trans(CMD1,0);		//CMD1を送信する
		spi_trans(0,0);
		spi_trans(0,0);
		spi_trans(0,0);
		spi_trans(0,0);
		spi_trans(1,0);
		res=mmsd_resp();		//ﾚｽﾎﾟﾝｽを得る
//DBG_B(res);
		if(res&0x80) return(0x13);	//ﾚｽﾎﾟﾝｽのMSBが1のときはﾀｲﾑｱｳﾄを返す
	}
	while(res==0x01);			//ｱｲﾄﾞﾙのときは繰返す
	if(res) return(0x14);			//ﾚｽﾎﾟﾝｽが0でなかったらｴﾗｰを返す

	//ﾌﾞﾛｯｸ長(512[ﾊﾞｲﾄ]設定)を送信する
//DBG_C('l');
	
	spi_trans(0xff,0);			//ﾀﾞﾐｰ転送しないとCMD16が0x01になる
	spi_trans(CMD16,0);			//CMD16を送信する
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(2,0);
	spi_trans(0,0);
	spi_trans(1,0);
	res=mmsd_resp();			//ﾚｽﾎﾟﾝｽを得る
//DBG_B(res);
	if(res&0x80) return(0x15);		//ﾚｽﾎﾟﾝｽのMSBが1のときはﾀｲﾑｱｳﾄを返す
	if(res) return(0x16);			//ﾚｽﾎﾟﾝｽが0でなかったらｴﾗｰを返す
	return(0);
}


//==============================================
//SD読込み開始
//==============================================
static void mmsd_read(void)
{

	//ﾚﾃﾞｨﾁｪｯｸ
//DBG_C('\n');
//DBG_C('r');
//DBG_L(voiceC.begin);
	do
	{
		while(spi_trans(0xff,0)!=0xff){};
						//0xffが返るまでﾀﾞﾐｰﾃﾞｰﾀを送る

	//ｼﾝｸﾞﾙﾌﾞﾛｯｸﾘｰﾄﾞ設定
//DBG_C('b');
		spi_trans(CMD17,0);		//CMD17を送信する
		spi_trans(voiceC.begin>>16,0);	//SDｶｰﾄﾞのｱﾄﾞﾚｽ(MSB)
		spi_trans(voiceC.begin>>8,0);	//SDｶｰﾄﾞのｱﾄﾞﾚｽ
		spi_trans(voiceC.begin,0);	//SDｶｰﾄﾞのｱﾄﾞﾚｽ
		spi_trans(0,0);			//SDｶｰﾄﾞのｱﾄﾞﾚｽ(LSB)
		spi_trans(1,0);			//CRC
	}
	while(mmsd_resp());			//ﾚｽﾎﾟﾝｽが0になるまで繰返す

	//ﾃﾞｰﾀﾄｰｸﾝ開始待ち
//DBG_C('t');
	while(spi_trans(0xff,0)!=0xfe){};	//ﾃﾞｰﾀ受信開始まで繰返す
//DBG_C('o');
}


//==============================================
//音声C選択処理(API関数)
//==============================================
static void VOICEC_SEL(				//戻り値無し
	unsigned short no)			//音声番号(0は再生中止)
{

//DBG_C('\n');
//DBG_C('s');
//DBG_S(no);
//DBG_D(voiceC_idx,40);
//DBG_C('i');
	if(no)					//再生開始のとき
	{
		if(no>sizeof(voiceC_idx)/sizeof(voiceC_idx[0])) return;
						//実装数を超えているときは戻る
		if(voiceC.no!=no)		//発声中の音声番号と異なるときのみ
						//　音声を切り替える
		{
			voiceC.no=no--;		//音声番号を設定
			voiceC.begin=voiceC_idx[no].adr;
						//音声ﾃﾞｰﾀの開始ｱﾄﾞﾚｽを設定
//DBG_L(voiceC.begin);
			voiceC.end=voiceC.begin+voiceC_idx[no].len*2;
						//音声ﾃﾞｰﾀの終了ｱﾄﾞﾚｽを設定
//DBG_L(voiceC.end);
			voiceC.psn=voiceC_idx[no].psn;
						//再生処理ﾌﾟﾘｽｹｰﾙ値を設定
//DBG_B(voiceC.psn);
			voiceC.pcm=0;		//PCM値を初期化
//DBG_B(voiceC.pcm);
			voiceC.bct=0;		//ﾌﾞﾛｯｸ内ﾊﾞｲﾄｱﾄﾞﾚｽを初期化
//DBG_S(voiceC.bct);
		}
	}
	else					//再生中断のとき
	{
		if(voiceC.no)			//再生中だったとき
		{
			voiceC.begin=voiceC.end-2;
						//最終ﾍﾟｰｼﾞにしておく
			voiceC.no=0xffff;	//再生終了中にする
		}
	}
//DBG_D(&voiceC,sizeof(voiceC));
}


//==============================================
//音声C再生処理
//==============================================
static void voiceC_exe(void)
{
//	short pcm;

//DBG_C('\n');
//DBG_C('p');
//DBG_S(voiceC.bct);
	if(!(voiceC.bct++))			//ﾍﾟｰｼﾞ先頭のとき
	{
//DBG_C('r');
		mmsd_read();			//SD読込み開始を設定する
	}
	voiceC.pcm=(short)spi_trans(0xff,0)-128;//音声ﾃﾞｰﾀを取出して､
						//　8ﾋﾞｯﾄPCM形式をsignedに変換
//DBG_S(voiceC.pcm);
	voiceC.pcm=(long)voiceC.pcm*((long)VOICEC_VOL*PWM_STEP/100)/128;
						//音量配分を掛ける
//DBG_S(voiceC.pcm);
	if(voiceC.bct==512)			//ﾌﾞﾛｯｸの最後になったら
	{
		voiceC.bct=0;			//ﾌﾞﾛｯｸ内ﾊﾞｲﾄｱﾄﾞﾚｽをｸﾘｱする
		if((voiceC.begin+=2)==voiceC.end)
						//音声ﾃﾞｰﾀの最後になったら
		{
//DBG_C('e');
//DBG_S(voiceC.no);
			if(voiceC.no!=0xffff)
			{
				voiceC.no=0;	//再生終了にする
				CB_VOICEC_END();//音声再生終了処理(ｺｰﾙﾊﾞｯｸ関数)を呼出す
			}
			voiceC.no=0;		//再生終了にする
		}
	}
}
#endif


#if VOICE_S>0				//SPIﾒﾓﾘを使うとき
//==============================================
//W25をﾊﾟﾜｰﾀﾞｳﾝ(API関数)
//==============================================
static void W25_PWR_DOWN(void)
{

	voiceS.no=0;				//音声再生終了にする
	spi_reset();				//SPIをﾘｾｯﾄする
	SPI_SS_L;				//ﾁｯﾌﾟｾﾚｸﾄ
#ifdef SPI2				//2線SPIのとき
	spi_trans(W25_PwrDwn,1);		//ﾊﾟﾜｰﾀﾞｳﾝｺﾏﾝﾄﾞ
#else					//2線SPIでないとき
	spi_trans(W25_PwrDwn,0);		//ﾊﾟﾜｰﾀﾞｳﾝｺﾏﾝﾄﾞ
#endif
	spi_reset();				//SPIをﾘｾｯﾄする
}


//==============================================
//W25をﾊﾟﾜｰｱｯﾌﾟ(API関数)
//==============================================
static void W25_PWR_UP(void)
{

	spi_reset();				//SPIをﾘｾｯﾄする
	wait_us(10);
	SPI_SS_L;				//ﾁｯﾌﾟｾﾚｸﾄ
#ifdef SPI2				//2線SPIのとき
	spi_trans(W25_Re_PwrDwn,1);		//ﾊﾟﾜｰﾀﾞｳﾝ解除ｺﾏﾝﾄﾞ
#else					//2線SPIでないとき
	spi_trans(W25_Re_PwrDwn,0);		//ﾊﾟﾜｰﾀﾞｳﾝ解除ｺﾏﾝﾄﾞ
#endif
	spi_reset();				//SPIをﾘｾｯﾄする
}


//==============================================
//音声S選択処理(API関数)
//==============================================
static void VOICES_SEL(				//戻り値無し
	unsigned short no)			//音声番号(0は再生中止)
{

//DBG_C('\n');
//DBG_C('s');
//DBG_S(no);
//DBG_C('i');
	if(no)					//再生開始のとき
	{
		if(no>sizeof(voiceS_idx)/sizeof(voiceS_idx[0])) return;
						//実装数を超えているときは戻る
		if(voiceS.no!=no)		//発声中の音声番号と異なるときのみ
						//　音声を切り替える
		{
			voiceS.no=no--;		//音声番号を設定
			voiceS.begin=voiceS_idx[no].adr;
						//音声ﾃﾞｰﾀの開始ｱﾄﾞﾚｽを設定
//DBG_L(voiceS.begin);
			voiceS.end=voiceS.begin+voiceS_idx[no].len;
						//音声ﾃﾞｰﾀの終了ｱﾄﾞﾚｽを設定
//DBG_L(voiceS.end);
			voiceS.ps=voiceS.psn=voiceS_idx[no].psn;
						//再生処理ﾌﾟﾘｽｹｰﾙ値を設定
//DBG_B(voiceS.psn);
			voiceS.pcm=0;		//PCM値を初期化
//DBG_S(voiceS.pcm);
			spi_reset();		//SPIをﾘｾｯﾄする
			SPI_SS_L;		//ﾁｯﾌﾟｾﾚｸﾄ
			spi_trans(W25_ReadData,0);
						//ReadDataｺﾏﾝﾄﾞ
			spi_trans(voiceS.begin>>16,0);
						//ｱﾄﾞﾚｽ(MSB)
			spi_trans(voiceS.begin>>8,0);
						//ｱﾄﾞﾚｽ
			spi_trans(voiceS.begin,0);
						//ｱﾄﾞﾚｽ(LSB)
		}
	}
	else					//再生中断のとき
	{
		voiceS.no=0;			//再生終了にする
		spi_reset();			//SPIをﾘｾｯﾄする
	}
//DBG_D(&voiceS,sizeof(voiceS));
}


//==============================================
//音声S再生処理
//==============================================
static void voiceS_exe(void)
{

//DBG_C('\n');
//DBG_C('p');
	voiceS.pcm=(short)spi_trans(0,0)-128;	//音声ﾃﾞｰﾀを取出して､
						//　8ﾋﾞｯﾄPCM形式をsignedに変換
//DBG_S(voiceS.pcm);
	voiceS.pcm=(long)voiceS.pcm*((long)VOICES_VOL*PWM_STEP/100)/128;
						//音量配分を掛ける
//DBG_S(voiceS.pcm);
	if(++voiceS.begin==voiceS.end)		//音声ﾃﾞｰﾀが最後のとき
	{
//DBG_C('e');
		voiceS.no=0;			//再生終了にする
		spi_reset();			//SPIをﾘｾｯﾄする
		CB_VOICES_END();		//音声再生終了処理(ｺｰﾙﾊﾞｯｸ関数)を呼出す
	}
}
#endif


//==============================================
//ﾊﾞｯﾌｧへ詰める
//ﾊﾞｯﾌｧﾌﾙの場合は待合せる
//==============================================
static void put_buf(
	short pcm)				//PCMﾃﾞｰﾀ
{
	unsigned char n;

//DBG_C('\n');
//DBG_C('-');
//DBG_S(pcm);
	n=buf_write;				//書込みﾎﾟｲﾝﾀを取得する
	if(++n==OUT_BUF_N) n=0;			//書込み位置を仮に進める
//DBS_H;
	while(n==buf_read);			//ﾊﾞｯﾌｧが空くのを待つ
//DBS_L;
	buf[buf_write]=pcm;			//ﾃﾞｰﾀをﾊﾞｯﾌｧに書込む
	buf_write=n;				//書込みﾎﾟｲﾝﾀを更新する
}


//==============================================
//ﾒｲﾝ処理
//==============================================
int main(void)
{
#if VOICE_C>0					//SDを使うとき
	unsigned char n;
#endif

	wait_ms(10);				//電圧安定時間
	CB_INIT();				//ﾃﾞﾊﾞｲｽの初期設定

#if VOICE_C>0					//SDを使うとき
//DBG_C('+');
	do
	{
		n=mmsd_init();			//SDCを初期化する
//DBG_B(n);
	}
	while(n);
#endif


//==============================================
//ﾒｲﾝﾙｰﾌﾟ
//==============================================
	while(1)
	{
//DBG_C('\n');
//DBG_C('m');


//==============================================
//固有処理
//==============================================
//DBG_C('k');
//DBG_S(kyotuu.ps);
		if(!(kyotuu.ps--))		//固有処理のﾀｲﾐﾝｸﾞになったら
		{
			kyotuu.ps=(unsigned long)KOYUU_PR*1000/PWM_PR-1;
						//固有処理ﾌﾟﾘｽｹｰﾗを初期化
			CB_KOYUU();		//固有処理(ｺｰﾙﾊﾞｯｸ関数)を呼出す
		}


//==============================================
//出力事前処理
//==============================================
		kyotuu.pcm=0;			//PCM合算値をｸﾘｱしておく


#if PART_N>0
//==============================================
//ｵﾙｺﾞｰﾙ演奏処理
//==============================================
//DBG_C('o');
		if(song.no)			//演奏中のとき
		{
//DBG_C('\n');
//DBG_B(song.song_ps);
			if(!(song.song_ps--))	//演奏処理のﾀｲﾐﾝｸﾞになったら
			{
				song.song_ps=SONG_PS-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				song_exe();	//演奏処理を実行する
			}
			kyotuu.pcm+=song.pcm;	//PCM値を反映する
		}
#endif


#if VOICE_N>0
//DBG_C('n');
//==============================================
//音声0再生処理
//==============================================
		if(voiceN[0].no)		//再生中のとき
		{
			if(!(voiceN[0].ps--))	//再生処理のﾀｲﾐﾝｸﾞになったら
			{
				voiceN[0].ps=voiceN[0].psn-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				voiceN_exe(0);	//演奏処理を実行する
			}
			kyotuu.pcm+=voiceN[0].pcm;
						//PCM値を反映する
		}
#endif


#if VOICE_N>1
//==============================================
//音声1再生処理
//==============================================
		if(voiceN[1].no)		//再生中のとき
		{
			if(!(voiceN[1].ps--))	//再生処理のﾀｲﾐﾝｸﾞになったら
			{
				voiceN[1].ps=voiceN[1].psn-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				voiceN_exe(1);	//演奏処理を実行する
			}
			kyotuu.pcm+=voiceN[1].pcm;
						//PCM値を反映する
		}
#endif


#if VOICE_N>2
//==============================================
//音声2再生処理
//==============================================
		if(voiceN[2].no)		//再生中のとき
		{
			if(!(voiceN[2].ps--))	//再生処理のﾀｲﾐﾝｸﾞになったら
			{
				voiceN[2].ps=voiceN[2].psn-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				voiceN_exe(2);	//演奏処理を実行する
			}
			kyotuu.pcm+=voiceN[2].pcm;
						//PCM値を反映する
		}
#endif


#if VOICE_I>0
//==============================================
//音声I再生処理
//==============================================
//DBG_C('i');
		if(voiceI.no)			//再生中のとき
		{
			if(!(voiceI.ps--))	//再生処理のﾀｲﾐﾝｸﾞになったら
			{
				voiceI.ps=voiceI.psn-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				voiceI_exe();	//演奏処理を実行する
			}
			kyotuu.pcm+=voiceI.pcm;	//PCM値を反映する
		}
#endif


#if VOICE_C>0
//==============================================
//音声C再生処理
//==============================================
//DBG_C('c');
		if(voiceC.no)			//再生中のとき
		{
			if(!(voiceC.ps--))	//再生処理のﾀｲﾐﾝｸﾞになったら
			{
				voiceC.ps=voiceC.psn-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				voiceC_exe();	//演奏処理を実行する
			}
			kyotuu.pcm+=voiceC.pcm;	//PCM値を反映する
		}
#endif


#if VOICE_S>0
//==============================================
//音声S再生処理
//==============================================
//DBG_C('s');
		if(voiceS.no)			//再生中のとき
		{
			if(!(voiceS.ps--))	//再生処理のﾀｲﾐﾝｸﾞになったら
			{
				voiceS.ps=voiceS.psn-1;
						//演奏処理ﾌﾟﾘｽｹｰﾗを初期化
				voiceS_exe();	//演奏処理を実行する
			}
			kyotuu.pcm+=voiceS.pcm;	//PCM値を反映する
		}
#endif


//==============================================
//ﾊﾞｯﾌｧ書出し
//==============================================
//DBG_C('b');
//DBG_S(kyotuu.pcm);
		if(kyotuu.pcm>=(PWM_STEP+1)/2) kyotuu.pcm=(PWM_STEP+1)/2-1;
						//有効な範囲に規制する
		else if(kyotuu.pcm<=-PWM_STEP/2) kyotuu.pcm=-PWM_STEP/2+1;
		put_buf(kyotuu.pcm);		//PCM形式でﾊﾞｯﾌｧに出力する
	}
}
