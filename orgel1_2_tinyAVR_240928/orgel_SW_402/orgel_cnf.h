//==============================================
//構成情報(ｵﾙｺﾞｰﾙ演奏+音声再生処理に関わるもの)
//==============================================
#define	BTL 		0			//BTL出力指定
						//　0=ｼﾝｸﾞﾙ出力
						//　1=ｺﾝﾌﾟﾘ出力
						//　2=ﾌﾞﾘｯｼﾞ出力
						//　3=ﾌﾞﾚｰｷ出力
#define	PWM_STEP	496			//PWMｽﾃｯﾌﾟ数(PWM周期=496/16MHz=31us)
#define	PWM_DB		10			//PWMﾃﾞｯﾄﾞﾊﾞﾝﾄﾞ(ﾌﾞﾘｯｼﾞ出力時)[0.021us]
#define	OUT_BUF_N	20			//出力ﾊﾞｯﾌｧｻｲｽﾞ

#define	PWM_PR		31			//PWM周期[1us]
#define	SONG_PS		2			//演奏処理ﾌﾟﾘｽｹｰﾙ値
						//　演奏処理周期=PWM_PR*SONG_PS
#define	KOYUU_PR	32			//固有処理のｺｰﾙﾊﾞｯｸ周期[ms]
#define	VOICE0_VOL	100			//音声0のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICE1_VOL	100			//音声1のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICE2_VOL	100			//音声2のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICEI_VOL	100			//音声Iのﾎﾞﾘｭｰﾑ配分[%]
#define	VOICEC_VOL	100			//音声Cのﾎﾞﾘｭｰﾑ配分[%]
#define	VOICES_VOL	100			//音声Sのﾎﾞﾘｭｰﾑ配分[%]
#define	ORGEL_VOL	100			//ｵﾙｺﾞｰﾙ演奏のﾎﾞﾘｭｰﾑ配分[%]
#define	VOICE_N		0			//音声N発声数の最大値(最大値3､
						//　0のときは
						//　音声再生機能を実装しない)
#define	VOICE_I		0			//音声I発声数の最大値(最大値1､
						//　0のときは
						//　音声再生機能を実装しない)
#define	VOICE_C		0			//音声C発声数の最大値(最大値1､
						//　0のときは
						//　音声再生機能を実装しない)
#define	VOICE_S		1			//音声S発声数の最大値(最大値1､
						//　0のときは
						//　音声再生機能を実装しない)
#define	PART_N		0			//演奏ﾊﾟｰﾄ数の最大値(最大値4､
						//　0のときはｵﾙｺﾞｰﾙ演奏機能を
						//　実装しない)
#define	PITCH_N		PART_N			//ﾋﾟｯﾁﾍﾞﾝﾄﾞ有効ﾊﾟｰﾄ数の最大値(最大値はPART_N､
						//　0のときはﾋﾟｯﾁﾍﾞﾝﾄﾞ機能を実装しない)
#define	KB_N		0			//KB演奏有効ﾊﾟｰﾄ数の最大値
						//　(0のときはKB演奏機能を実装しない)
