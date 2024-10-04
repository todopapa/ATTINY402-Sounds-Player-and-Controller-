// 24/07/24 トリガ入力をUPDIポートでUPDIプログラム書けない不具合発生したので
//トリガ入力をUPDIポート（PA0）から、SCLKポート（PA2)と共用に変更する。

//#define	SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHDBG_SOFT	//ﾃﾞﾊﾞｸﾞ情報出力のUARTをｿﾌﾄ実装するときに宣言する
//#define	SHDBG_BPS	115200	//内蔵UARTのときﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する
				//　(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する

#define		SLEEP_EN	//Sleep機能を実装するときに宣言する


/*
tinyAVR電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_2
これは根のｿｰｽｺｰﾄﾞ

・ﾀｰｹﾞｯﾄはtiny402(内部16MHzｸﾛｯｸ)


//==============================================
//ﾋﾟﾝ割当て
//==============================================
W25Qのﾋﾟﾝ接(標準SPIﾓｰﾄﾞ)
1:CS
2:DO
3:WP(GNDに接続)
4:GND
5:DI
6:CLK
7:HOLD(Vccに接続)
8:Vcc

tiny402のﾎﾟｰﾄの割当て(3線SPI) 変更前オリジナル
1:VDD
2:(PA6)SCK(M25QのCLKに繋ぐ)/ﾄﾘｶﾞ入力
3:(PA7)SS(M25QのCSに繋ぐ)
4:(PA1)ﾓｰﾀｰ制御出力(正論理)/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(WO1)逆相出力/(TxD)ﾃﾞﾊﾞｸﾞ情報
5:(PA2)MOSI(M25QのDIに繋ぐ)･MISO(抵抗を介してM25QのDOに繋ぐ)
6:(PA0)/UPDI
7:(PA3)/(WO0)正相出力
8:GND

tiny402のﾎﾟｰﾄの割当て(3線SPI) YM変更後
1:VDD
2:(PA2)SCK(M25QのCLKに繋ぐ)  /ﾄﾘｶﾞ入力を共用（10kΩを経由して接続すること ）
3:(PA1)SS(M25QのCSに繋ぐ)
4:(PA6)ﾓｰﾀｰ制御出力(正論理)/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(WO1)逆相出力/(TxD)ﾃﾞﾊﾞｸﾞ情報
5:(PA7)MOSI(M25QのDIに繋ぐ)･MISO(抵抗を介してM25QのDOに繋ぐ)
6:(PA0)/UPDI_SW1入力 
7:(PA3)/(WO0)正相出力（変更なし）
8:GND
*/


//==============================================
//ﾍｯﾀﾞﾌｧｲﾙの呼込み
//==============================================
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "../port_tn.h"				//I/Oportの勝手なstruct定義
#include "orgel_cnf.h"				//ｵﾙｺﾞｰﾙ演奏処理と音声再生の構成を呼込む
#include "../orgel.h"				//ｱﾌﾟﾘのﾍｯﾀﾞﾌｧｲﾙ


//==============================================
//構成情報(ｱﾌﾟﾘｹｰｼｮﾝとﾀｰｹﾞｯﾄﾃﾞﾊﾞｲｽに関わるもの)
//==============================================
//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ定義
#define	DBS_PORT	PORTA			//ﾃﾞﾊﾞｸﾞ信号のﾎﾟｰﾄ
#define	DBS_BIT		1			//ﾃﾞﾊﾞｸﾞ信号のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	DBG_PORT	PORTA			//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ
#define	DBG_BIT		1			//ﾃﾞﾊﾞｸﾞ情報のﾋﾞｯﾄ

//PWMのﾎﾟｰﾄ定義
#define	PWM_F_PORT	PORTA			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	3			//PWM正相のﾋﾞｯﾄ
#if BTL>0				//ｺﾝﾌﾟﾘ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#define	PWM_R_PORT	PORTA			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	1			//PWM逆相のﾋﾞｯﾄ
#endif

//SPIのﾎﾟｰﾄ定義
// TINY orgel1_2_0520　と同じピン配にする 変更 by YM
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define SPI3					//3線SPIで接続する
#define SPI_SCK_PORT	PORTA			//SPI_SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	2			//SPI_SCKのﾋﾞｯﾄ　6→2
#define SPI_MOSI_PORT	PORTA			//SPI_MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	7			//SPI_MOSIのﾋﾞｯﾄ 2→7
#define SPI_SS_PORT	PORTA			//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	1			//SPI_SSのﾋﾞｯﾄ　2→1
#define SPI_MISO_PORT	PORTA			//SPI_MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	7			//SPI_MISOのﾋﾞｯﾄ 2→7

#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//ﾓｰﾀｰ制御のﾎﾟｰﾄ定義 変更 by YM
#define	MTR_PORT	PORTA			//ﾓｰﾀｰのﾎﾟｰﾄ
#define	MTR_BIT		6			//ﾓｰﾀｰのﾋﾞｯﾄ　1→6
#else					//ｺﾝﾌﾟﾘ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#if VOICE_S==0				//SPIを実装しないとき
#define	MTR_PORT	PORTA			//ﾓｰﾀｰのﾎﾟｰﾄ
#define	MTR_BIT		6			//ﾓｰﾀｰのﾋﾞｯﾄ　7→6
#endif

#endif

//ﾄﾘｶﾞ入力のﾎﾟｰﾄ定義 変更 by YM
#define	TRG_PORT	PORTA			//ﾄﾘｶﾞのﾎﾟｰﾄ
//#define	TRG_BIT		0			//ﾄﾘｶﾞのﾋﾞｯﾄ　6→0 （UPDIと共用）
#define	TRG_BIT		2			//ﾄﾘｶﾞのﾋﾞｯﾄ　0→2 （SCLKと共用）に変更 240724

#if	PART_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
static struct SONG_IDX *song_idx=&SONG_IDX;	//曲ｲﾝﾃﾞｯｸｽへのﾎﾟｲﾝﾀ
#endif


#if	VOICE_S>0
//==============================================
//音声ﾃﾞｰﾀ(SPIﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{

#if(1)	//本番用
	//voice_SISIMAI\W25Q16.hexを使う
//	vos_mac(0x000000,0x04879a,8000)		//sisimai1ch8bit8ksps.wav
//　//　クリスマスソング（フリー音源を使う 16kbps）0817 ジングルベル先頭に順番を変えた
	vos_mac(0x000000,0x2ae280,16000)	//gingle_hade.wav
	vos_mac(0x2ae280,0x0e2835,16000)	//Silent_Night_cover.wav
	vos_mac(0x390ab5,0x1396e5,16000)	//morobito-cover-.wav


#else	//ﾃｽﾄ用
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q16.hex)を使う
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav
#endif
};
#define VOICES_SU	(sizeof(voiceS_idx)/sizeof(voiceS_idx[0]))
#endif


//==============================================
//共通ｺｰﾄﾞの呼込み
//==============================================
#include "../common.c"				//共通ｺｰﾄﾞを呼込む
#include "../orgel.c"				//orgelｴﾝｼﾞﾝを呼込む


//==============================================
//ﾃﾞﾊﾞｲｽ依存部の呼込み
//==============================================
#include "../dev_xxx.c"				//tinyAVR


//==============================================
//ｱﾌﾟﾘｹｰｼｮﾝ依存部の呼込み
//==============================================
#include "../apl_SISIMAI.c"
