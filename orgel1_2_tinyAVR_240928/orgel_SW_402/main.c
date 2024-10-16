//#define	SHDBG		//ﾃﾞﾊﾞｸﾞ情報を出力するときに宣言する
//#define	SHDBG_SOFT	//ﾃﾞﾊﾞｸﾞ情報出力のUARTをｿﾌﾄ実装するときに宣言する
//#define	SHDBG_BPS	115200	//内蔵UARTのときﾃﾞﾊﾞｸﾞ情報のﾎﾞｰﾚｰﾄを宣言する
				//　(ﾃﾞﾌｫﾙﾄ値は38400bps)
//#define	SHDBS		//ﾃﾞﾊﾞｸﾞ信号を出力するときに宣言する

//#define	SPI2		//2線SPIのときに宣言する
				//　宣言しないときは3線SPIとなる
#define		SLEEP_EN	//Sleep機能を実装するときに宣言する
//#define	SHAUTO			//自動開始するときに宣言する
//#define	KYOKU_RAND	//曲番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIN_RAND	//音声N番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEII_RAND	//音声I番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIC_RAND	//音声C番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
//#define	ONSEIS_RAND	//音声S番号をﾗﾝﾀﾞﾏｲｽﾞするときに宣言する
#define	SW_EN		//SWを実装するときに宣言する
//#define	TRG_EN			 //トリガ入力を実装するときに宣言する
//#define	CdS_EN		//CdSを実装するときに宣言する
//#define	CVD_EN		//CVDを実装するときに宣言する
//#define	CVD_EXPU	//CVDを外部ﾌﾟﾙｱｯﾌﾟ(100kΩ推奨)するときに宣言する


//ｵﾙｺﾞｰﾙ箱への応用では以下を宣言しておくこと
//#define	CdS_FUTA	//蓋を開ける(明)とｵﾝ判定する
//#define	CdS_THR	100	//判定閾値を固定の宣言値にする


/*
tinyAVR電子ｵﾙｺﾞｰﾙ演奏+音声再生ver1_2
これは根のｿｰｽｺｰﾄﾞ

・ﾀｰｹﾞｯﾄはtiny402(内部16MHzｸﾛｯｸ)

・SWとCVDを合わせて3個まで実装可能だが､このｱﾌﾟﾘｹｰｼｮﾝではそれぞれ1個を
　使っている｡

・SWはﾎﾟｰﾄ-GND間に設置し､負論理(導通=L)で入力する｡
・SWの短ｵﾝでﾗｳﾝﾄﾞﾛﾋﾞﾝに曲を演奏開始､音声を再生開始する｡
・SWの長ｵﾝで演奏中断､再生中断する｡

・CVDはCVDﾊﾟｯﾄﾞﾎﾟｰﾄから10kΩの抵抗を介してﾎﾟｰﾄに入力する｡
　10kΩはﾎﾟｰﾄ保護のためであり､必須ではない｡
・CVDの短CVDでﾗｳﾝﾄﾞﾛﾋﾞﾝに曲を演奏開始､音声を再生開始する｡
・CVDの長CVDで演奏中断､再生中断する｡

・CdSは1個のみ実装している｡
・CdSはﾎﾟｰﾄ-GND間に設置し､正論理(暗=H)で入力する｡
・CdSの短ｵﾝでﾗｳﾝﾄﾞﾛﾋﾞﾝに曲を演奏開始､音声を再生開始する｡
・CdSの長ｵﾝで演奏中断､再生中断する｡

・SHAUTOを宣言することで､自動的に曲を演奏開始､及び音声を再生開始する｡
・音声ﾃﾞｰﾀはﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ､I2Cﾌﾗｯｼｭ､SDｶｰﾄﾞ､SPIﾌﾗｯｼｭの何れかに格納しておく｡


//==============================================
//外部のﾒﾓﾘを使わないとき
//==============================================
tiny402のﾎﾟｰﾄの割当て
1:VDD
2:(PA6)SW1/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(AIN6)CdS/(AIN6)CVD0/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)SW2/(AIN7)CVD1
4:(PA1)/(WO1)逆相出力
5:(PA2)SW3/(AIN2)CVD2
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)正相出力
8:GND


//==============================================
//I2Cﾌﾗｯｼｭﾒﾓﾘを使うとき
//==============================================
24FCのﾋﾟﾝ接
ﾋﾟﾝ1:A0(Vssに繋ぐ)
ﾋﾟﾝ2:A1(Vssに繋ぐ)
ﾋﾟﾝ3:A2(Vssに繋ぐ)
ﾋﾟﾝ4:Vss
ﾋﾟﾝ5:SDA(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
ﾋﾟﾝ6:SCL(1.5kで外部ﾌﾟﾙｱｯﾌﾟ)
ﾋﾟﾝ7:WP(Vccに繋ぐ)
ﾋﾟﾝ8:Vcc

tiny402のﾎﾟｰﾄの割当て
1:VDD
2:(PA6)SW1/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(AIN6)CdS/(AIN6)CVD0/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)SDA
4:(PA1)/(WO1)逆相出力
5:(PA2)SCL
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)正相出力
8:GND


//==============================================
//SDｶｰﾄﾞを使うとき
//==============================================
SDｶｰﾄﾞｽﾛｯﾄのﾋﾟﾝ接(SPIﾓｰﾄﾞ)
9:空き(不使用)
1:CS(2線SPIでは時定数回路を介してCLKに繋ぐ)
2:DI
3:Vss1
4:Vdd
5:CLK
6:Vss2
7:DO(抵抗を介してDIに繋ぐ)
8:IRQ(不使用)

tiny402のﾎﾟｰﾄの割当て(3線SPI)
1:VDD
2:(PA6)SW1/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(AIN6)CdS/(AIN6)CVD0/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)MOSI(SDCのDIに繋ぐ)
4:(PA1)SS(SDCのCSに繋ぐ)/(WO1)逆相出力
5:(PA2)SCK(SDCのCLKに繋ぐ)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)正相出力
8:GND

tiny402のﾎﾟｰﾄの割当て(2線SPI)
1:VDD
2:(PA6)SW1/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(AIN6)CdS/(AIN6)CVD0/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)MOSI(SDCのDIに繋ぐ)
4:(PA1)/(WO1)逆相出力
5:(PA2)SCK(SDCのCLKに繋ぐ)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)正相出力
8:GND


//==============================================
//SPIﾌﾗｯｼｭﾒﾓﾘを使うとき
//==============================================
W25Qのﾋﾟﾝ接(標準SPIﾓｰﾄﾞ)
1:CS(2線SPIでは時定数回路を介してCLKに繋ぐ)
2:DO(2線SPI･3線SPIでは抵抗を介してDIに繋ぐ)
3:WP(GNDに接続)
4:GND
5:DI
6:CLK
7:HOLD(Vccに接続)
8:Vcc

tiny402のﾎﾟｰﾄの割当て(3線SPI)
1:VDD
2:(PA6)SW1/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(AIN6)CdS/(AIN6)CVD0/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)MOSI(M25QのDIに繋ぐ)
4:(PA1)SS(M25QのCSに繋ぐ)/(WO1)逆相出力
5:(PA2)SCK(M25QのCLKに繋ぐ)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)正相出力
8:GND

tiny402のﾎﾟｰﾄの割当て(2線SPI)
1:VDD
2:(PA6)SW1/ﾃﾞﾊﾞｸﾞ情報/ﾃﾞﾊﾞｸﾞ信号/(AIN6)CdS/(AIN6)CVD0/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)MOSI(M25QのDIに繋ぐ)
4:(PA1)/(WO1)逆相出力
5:(PA2)SCK(M25QのCLKに繋ぐ)
6:(PA0)SW0/(AIN0)CVD1/UPDI
7:(PA3)/(WO0)正相出力
8:GND

tiny402のﾎﾟｰﾄの割当て(3線SPI) 240928 YM
1:VDD
2:(PA6)MOTOR_ON信号/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)MOSI出力(M25QのDIに繋ぐ)/MISO(10kΩ介してM25QのDOに繋ぐ)
4:(PA1)SS出力(M25QのCSに繋ぐ)
5:(PA2)SCK出力(M25QのCLKに繋ぐ)/SW2入力（ピエゾ信号）
6:(PA0)SW0入力/UPDIプログラム信号入出力
7:(PA3)/(WO0)正相出力 PWM_P
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
#define	DBS_BIT		6			//ﾃﾞﾊﾞｸﾞ信号のﾋﾞｯﾄ

//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ定義
#define	DBG_PORT	PORTA			//ﾃﾞﾊﾞｸﾞ情報のﾎﾟｰﾄ
#define	DBG_BIT		6			//ﾃﾞﾊﾞｸﾞ情報のﾋﾞｯﾄ

//PWMのﾎﾟｰﾄ定義
#define	PWM_F_PORT	PORTA			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	3			//PWM正相のﾋﾞｯﾄ
#define	PWM_R_PORT	PORTA			//PWM逆相のﾎﾟｰﾄ
#define	PWM_R_BIT	1			//PWM逆相のﾋﾞｯﾄ

//I2Cのﾎﾟｰﾄ定義
#define	I2C_SOFT			//I2Cをｿﾌﾄ実装する
#define I2C_SCL_PORT	PORTA			//I2C_SCLのﾎﾟｰﾄ
#define I2C_SCL_BIT	2			//I2C_SCLのﾋﾞｯﾄ
#define I2C_SDA_PORT	PORTA			//I2C_SDAのﾎﾟｰﾄ
#define I2C_SDA_BIT	7			//I2C_SDAのﾋﾞｯﾄ

//SPIのﾎﾟｰﾄ定義
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define SPI_SCK_PORT	PORTA			//SPI_SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	2			//SPI_SCKのﾋﾞｯﾄ
#define SPI_MOSI_PORT	PORTA			//SPI_MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	7			//SPI_MOSIのﾋﾞｯﾄ
#ifdef SPI2				//2線SPIのとき
#define	SS_WAIT_TIME	50			//SSﾈｹﾞｰﾄ待ち時間[us]
#define SPI_SS_PORT	PORTA			//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	2			//SPI_SSのﾋﾞｯﾄ
#else					//3線SPIのとき
#define	SPI3					//3線SPIで接続する
#define SPI_SS_PORT	PORTA			//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	1			//SPI_SSのﾋﾞｯﾄ
#endif
#define SPI_MISO_PORT	PORTA			//SPI_MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	7			//SPI_MISOのﾋﾞｯﾄ

//LEDのﾎﾟｰﾄ定義
#if(0)
#ifndef RFID_EN				//RFIDを実装しないとき
#define	LED0_PORT	PORTC			//LED0のﾎﾟｰﾄ
#define	LED0_BIT	0			//LED0のﾋﾞｯﾄ
#define	LED1_PORT	PORTD			//LED1のﾎﾟｰﾄ
#define	LED1_BIT	2			//LED1のﾋﾞｯﾄ
#define	LED2_PORT	PORTD			//LED2のﾎﾟｰﾄ
#define	LED2_BIT	3			//LED2のﾋﾞｯﾄ
#define	LED3_PORT	PORTC			//LED3のﾎﾟｰﾄ
#define	LED3_BIT	2			//LED3のﾋﾞｯﾄ
#endif
#endif

//SWのﾎﾟｰﾄ定義
#define	SW0_PORT	PORTA		//SW0のﾎﾟｰﾄ
#define	SW0_BIT		0			//SW0のﾋﾞｯﾄ（PA0 UPDI)
#define	SW0_INV					//SW0入力は負論理
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW0_TIMER				//SW0はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW0_REAL			//SW0はﾘｱﾙﾓｰﾄﾞ

//ﾄﾘｶﾞ入力のﾎﾟｰﾄ定義
#define	TRG_PORT	PORTA		//ﾄﾘｶﾞのﾎﾟｰﾄ
#define	TRG_BIT		0			//ﾄﾘｶﾞのﾋﾞｯﾄ（PA0 UPDI)

//CdSのﾎﾟｰﾄ定義
#define	CdS_PORT	PORTA			//CdSのﾎﾟｰﾄ
#define	CdS_BIT		6			//CdSのﾋﾞｯﾄ
#define	CdS_AIN		6			//CdSのAIN
//#define	CdS_INV				//CdS入力は負論理(暗=L)
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CdS_TIMER				//CdSはﾀｲﾏｰﾓｰﾄﾞ
//#define	CdS_REAL			//CdSはﾘｱﾙﾓｰﾄﾞ
//#define	CdS_THR		100		//CdS評価の固定閾値[1/256]
//#define	CdS_FUTA			//CdS判定反転(明=ｵﾝ)

//CVDのﾎﾟｰﾄ定義
#define	CVD0_PORT	PORTA			//CVD0のﾎﾟｰﾄ
#define	CVD0_BIT	6			//CVD0のﾋﾞｯﾄ
#define	CVD0_AIN	6			//CVD0のAIN
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define CVD0_TIMER				//CVD0はﾀｲﾏｰﾓｰﾄﾞ
//#define	CVD0_REAL			//CVD0はﾘｱﾙﾓｰﾄﾞ

//MFRCのﾎﾟｰﾄ定義
#define MFRC_RST_PORT		PORTD		//RC522_RSTのﾎﾟｰﾄ
#define MFRC_RST_BIT		7		//RC522_RSTのﾋﾞｯﾄ
#define MFRC_SCK_PORT		PORTC		//RC522_SCKのﾎﾟｰﾄ
#define MFRC_SCK_BIT		0		//RC522_SCKのﾋﾞｯﾄ
#define MFRC_NSS_PORT		PORTC		//RC522_NSSのﾎﾟｰﾄ
#define MFRC_NSS_BIT		2		//RC522_NSSのﾋﾞｯﾄ
#define MFRC_MOSI_PORT		PORTD		//RC522_MOSIのﾎﾟｰﾄ
#define MFRC_MOSI_BIT		2		//RC522_MOSIのﾋﾞｯﾄ
#define MFRC_MISO_PORT		PORTD		//RC522_MISOのﾎﾟｰﾄ
#define MFRC_MISO_BIT		3		//RC522_MISOのﾋﾞｯﾄ


//モータ制御追加　24/05/23　YM
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//ﾓｰﾀｰ制御のﾎﾟｰﾄ定義
#define	MTR_PORT	PORTA			//ﾓｰﾀｰのﾎﾟｰﾄ
#define	MTR_BIT		6			//ﾓｰﾀｰのﾋﾞｯﾄ PA1→PA6
#else					//ｺﾝﾌﾟﾘ･ﾌﾞﾘｯｼﾞ･ﾌﾞﾚｰｷ出力のとき
#if VOICE_S==0				//SPIを実装しないとき
#define	MTR_PORT	PORTA			//ﾓｰﾀｰのﾎﾟｰﾄ
#define	MTR_BIT		7			//ﾓｰﾀｰのﾋﾞｯﾄ （SPIのMOMIbitに設定）
#endif
#endif


#if	PART_N>0
//==============================================
//ｿﾝｸﾞﾃﾞｰﾀのｲﾝﾃﾞｯｸｽ
//==============================================
extern struct SONG_IDX SONG_IDX;		//曲ｲﾝﾃﾞｯｸｽ実体
static struct SONG_IDX *song_idx=&SONG_IDX;	//曲ｲﾝﾃﾞｯｸｽへのﾎﾟｲﾝﾀ
#endif


#if	VOICE_N>0
//==============================================
//音声ﾃﾞｰﾀ
//==============================================
#include	"../voice_WAN.c"
#include	"../voice_DAME.c"
//#include	"../voice_CHIKO.c"


//==============================================
//音声ﾃﾞｰﾀ(ﾌﾟﾛｸﾞﾗﾑﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEN_HDR voiceN_idx[]=
{
	von_mac(voice_WAN,sizeof(voice_WAN),8000)
	von_mac(voice_DAME,sizeof(voice_DAME),8000)
//	von_mac(voice_CHIKO,sizeof(voice_CHIKO),8000)
};
#define VOICEN_SU	(sizeof(voiceN_idx)/sizeof(voiceN_idx[0]))
#endif


#if	VOICE_I>0
//==============================================
//音声ﾃﾞｰﾀ(I2Cﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEI_HDR voiceI_idx[]=
{

	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(Mirrorna_24FC512.XのMirrorna_24FC512.X)を使う
	voi_mac(0x0000,0x4B88,8000,0xa0)	//KIRAKIRAOMEME
	voi_mac(0x4B88,0x1B8A,8000,0xa0)	//AIDORUMITAI
	voi_mac(0x6712,0x30B0,8000,0xa0)	//KYOUNOOSHARE
	voi_mac(0x97C2,0x2076,8000,0xa0)	//EGAOGASUTEKI
	voi_mac(0xB838,0x3626,8000,0xa0)	//KIRARIN

};
#define VOICEI_SU	(sizeof(voiceI_idx)/sizeof(voiceI_idx[0]))
#endif


#if	VOICE_C>0
//==============================================
//音声ﾃﾞｰﾀ(SDｶｰﾄﾞ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICEC_HDR voiceC_idx[]=
{

	//｢ｱﾝﾊﾟﾝﾏﾝｼｮｰ｣の音声ﾃﾞｰﾀ(SDのANPANMAN.wav)を使う
	voc_mac(0x00029e,0x00e367,8000)		//anpan
	voc_mac(0x002000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)
	voc_mac(0x004000,0x000080,8000)		//anpanの一部(ﾃｽﾄ用)

};
#define VOICEC_SU	(sizeof(voiceC_idx)/sizeof(voiceC_idx[0]))
#endif


#if	VOICE_S>0
//==============================================
//音声ﾃﾞｰﾀ(SPIﾌﾗｯｼｭ)のｲﾝﾃﾞｯｸｽ
//==============================================
static const struct VOICES_HDR voiceS_idx[]=
{
	//voice_ToyStory\W25Q16_12ksps8bit.hexを使う
//	vos_mac(0x000000,0x0afc83,12000)	//ToyStory_12ksps8bit
/*　いちおうコメントアウトしておく
	//｢ｷﾃｨﾐﾗｰﾅ｣の音声ﾃﾞｰﾀ(voice_Mirrorna\W25Q16.hex)を使う
	vos_mac(0x000000,0x002401,8000)		//sharin.wav
	vos_mac(0x002401,0x004575,8000)		//kirakiraomeme.wav
	vos_mac(0x006976,0x001956,8000)		//aidorumitai.wav
	vos_mac(0x0082cc,0x002b18,8000)		//kyounooshare.wav
	vos_mac(0x00ade4,0x001d61,8000)		//egaogasuteki.wav
	vos_mac(0x00cb45,0x0033a5,8000)		//kirarin.wav
*/
//　クリスマスソング（フリー音源を使う 16kbps）
vos_mac(0x000000,0x0e2835,16000)	//Silent_Night_cover.wav
vos_mac(0x0e2835,0x2ae280,16000)	//gingle_hade.wav
vos_mac(0x390ab5,0x1396e5,16000)	//morobito-cover-.wav

// 各周波数のサイン波の音声データ
/*
		vos_mac(0x000000,0x075300,16000)	//wav\1_1khz-0db-30sec#.wav
		vos_mac(0x075300,0x075300,16000)	//wav\2_400hz-0db-30sec#.wav
		vos_mac(0x0ea600,0x04e200,16000)	//wav\3_100hz-6db-20sec#.wav
		vos_mac(0x138800,0x04e200,16000)	//wav\4_400hz-6db-20sec#.wav
		vos_mac(0x186a00,0x04e200,16000)	//wav\5_1khz-6db-20sec#.wav
		vos_mac(0x1d4c00,0x04e200,16000)	//wav\6_2khz-6db-20sec#.wav
		vos_mac(0x222e00,0x04e200,16000)	//wav\7_5khz-6db-20sec#.wav
*/
//　アンパンマンキーボードの音声データ（デモ音源を使う 8kbps）
/*
	vos_mac(0x000000,0x14d32a,8000)	//wav\demo_all_1.wav
	vos_mac(0x14d32a,0x14c802,8000)	//wav\demo_all_2.wav
	vos_mac(0x299b2c,0x1030e2,8000)	//wav\demo_all_3.wav
	vos_mac(0x39cc0e,0x03d18e,8000)	//wav\demo_all_4.wav
	vos_mac(0x3d9d9c,0x07d1d2,8000)	//wav\demo_all_5.wav
*/
// TRUTHで音質のテスト
 //   vos_mac	(0x000000,0x3d9f28,16000)  //TRUTH.wav
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
#include "../apl_SW.c"
