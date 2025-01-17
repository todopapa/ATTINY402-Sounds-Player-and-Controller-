# ATTINY402_Sounds_Player for toy
This is a new AVR ATTINY 402/202 series Sounds Player w/Piezo mic input and Motor controller  
for toy gadgets PCBs replacement or a amusement

<img src="https://github.com/user-attachments/assets/67f2f646-dc5e-4c46-ae4f-5d6ad38f57b6" width="480">
<!-- ![TINY202_IR_REMOTE 2024-05-02 233458](https://github.com/todopapa/TINY202_IR_REMOTE_ISR/assets/16860878/7a59901e-49d1-468d-9323-dc31d36176b7)　-->

## はじめに
### つつじが丘おもちゃ病院 大泉さんのtinyAVRオルゴール基板プロジェクト　　
[名張市つつじが丘おもちゃ病院](http://tutujith.blog.fc2.com/)では、故障したおもちゃの修理用に、換装用のマイコン基板とソフトを開発されています。  

最近のおもちゃは基板に黒いCOBのカスタムICを乗せて音を出したり演奏したり、動かすものが多くなってますが、  
このCOBは中身がブラックボックスのため、一旦壊れるとおもちゃの修理に手の出しようがなくて困っています。   

つつじが丘おもちゃ病院では、その対応策として安価に購入できるPIC等のCPUを使った基板を作って換装することを    
他のおもちゃ病院のドクターさん達に提案されています。   

**以下、大泉さんの開発者コメントを引用します。**   
マイコン制御のおもちゃで、マイコンが故障しているとマイコンを換装しなければならない。その場合、 おもちゃの   
要件に合わせて  ファームウェアを開発する必要があるが、ゼロからファームウェアを開発すると大変なので、   
既存のファームウェアをベースにカスタマイズを行うと楽だ。 

以下に、つつじが丘おもちゃ病院で開発してきたファームウェアの代表事例を紹介する。  

・これらのファームウェアは自由にダウンロードして使うことができる。  
・ソースコードやデータ、設計資料も公開しているので、カスタマイズが遣り易い。  
・複製、改変、再配布を自由にやってよい。おもちゃ病院業界の皆で改善を施して共有して行きたい。  
・リンク先は１例のみを示しているので、その他の応用は「ブログ内検索」で検索するか、メールにて  
　 問い合わせいただきたい。    
**引用はここまで**  

## プロジェクトの内容
### ATTINY402 Sound Player基板の概要
今回は、つつじが丘おもちゃ病院で開発してきたファームウェアの代表事例のうち、tinyAVRプロジェクト    
に注目し、new ATTINY402  を使って基板を起こしましたので、その内容を公開したいと思います。   

他のおもちゃ病院のドクターさんに参考になれば幸いです。    
[ｔｉｎｙＡＶＲ電子オルゴールVer1_2（ｔｉｎｙ４０２をサポート）](http://tutujith.blog.fc2.com/blog-entry-741.html)  

この基板の概略仕様は下記になります。  
1.new ATTINY CPUのうち、小型化のため8ピンとピンが少ないATTINY402を採用する　　

2.ピンが少ないので、音楽再生を制御するSWは1個のみ。SWを押すたびにフラッシュメモリICの曲を   
　　ラウンドロビンで順に再生する  

3.長押しで停止する。停止時はSleep待機に入り待機時の消費電流はは1uA以下になる   
  SWを押すと割り込みで起動する   

4.piezoマイクに対応したファームを書き込むと、おもちゃを叩いたり、大きな音に反応して  
　おもちゃが動く仕様となる    
  演奏中にLEDが点灯する信号を使って、おもちゃを動かす外部モータを駆動する回路も付けている      
  
5.トリガ起動がピエゾマイクの場合は、振動で次の曲に移動しないようにトリガ信号無効にする。   
   停止時も4秒の待ち時間を設ける   

6.フラッシュメモリICに書き込んだ音声データを再生する以外に、マイコン内のメモリに書き込んだ  
  音符データでオルゴールを再生することもできる。TINY402はメモリが4kBしかなく、1曲程度しか   
  記憶できない。数曲以上のオルゴールに対応するには14ピンで内部メモリが16kBのATTINY1614を使用する。   
  こちらは今回の基板では対応していない。（別の大サイズ基板 V3で対応）   
  
5.基板の大きさは35ｍｍｘ50ｍｍ(TINY1614版のV3は50ｍｍｘ60ｍｍ)、単三電池2個で3Ｖで動作することを想定    
  動作時の電流は最大50~100ｍＡ、待機時は1uA以下（ピエゾアンプ実装時は3uA程度）  
  
## **ハードウェア説明**
### ATTINY402 Sound Player基板の基本設計
今回の基板のＣＰＵはATTINY402、音声データを入れるフラッシュメモリICはWinBondのW25Q64(64Mbit)を使います    
フラッシュICとTINY402の間の接続図は下記になります    

・入力は、SW0 タクトスイッチ 1個をPA0に、ピエゾマイクのアンプ出力をPA2に入力し、2種の音声のトリガ入力にします   

・出力は、PA6をモータ駆動信号に、PA3を音声のPWM正相出力に設定します  

・フラッシュICは、/CSをPA1、CLKをPA2 (ピエゾ入力と併用）、DIをPA7、DOは10kΩを介してPA7を併用します   
   フラッシュICとの接続は、/CS、CLK、PA7ピンのMOSI/MISOを使った3線SPIになります  
   
・プログラムはPA0 UPDI端子をSW0タクトSWと併用します。あらかじめFUSEbitでUPDIからGPIOに変更します    
　  (プログラム時はHVP（高電圧)プログラマーが必要になります）   
 
 <img src="https://github.com/user-attachments/assets/13a25016-7da2-4704-89ea-2c94c9342ec7" width="480">    

 PA3からの音声PWM信号は、16KHzの場合は約31uS周期になります。 16MHzクロックで496ステップにしているからです。    
 プログラムの中のorgel_conf.h に下記の記述があります。  （31uS ≒ 32kHz）   
 #define PWM_STEP 496	//PWMｽﾃｯﾌﾟ数(PWM周期=496/16MHz=31us)  
 
 元の回路では、PWM正相出力と逆相出力をHブリッジICに入れてスピーカを駆動していますが、今回はモータ駆動するピンで   
 TINY402のピンを使ったので、PWM正相のみを出力して一般的なAB級アンプICを使った回路にしました。  
 高周波のPWM信号をそのまま入れるとICを壊す恐れがありますので、アンプの入力にCRローパスフィルタと音量調整のため   
 半固定ボリュームを入れました。  
 
 AB級アンプとしては、ISSIのIS31AP4991Aというスマホ用のものを使います。  
 一般的なTI LM4891MXというICもあります。どちらもSOP8でピン配も同じなのですが、Sleepさせる論理が逆なので要注意です。  
 IS31AP4991Aの場合は、SDBにモータ駆動信号 MOT_ONを接続します。LM4891MXを実装する場合は/CS信号を接続します。

 <img src="https://github.com/user-attachments/assets/844ad3c4-5525-4207-8fd6-67c08ce1b76e" width="400">    

 **ピエゾマイク回路**
 先頭の写真に銀色の円盤が写っていますが、これがピエゾマイクです。  
 圧電効果で、音や振動を拾って電圧に変換します。  
 そのピエゾアンプの元回路は下記になります。 自己バイアス回路で増幅率は100程度だと思います。  
 これに保護用のダイオードを付けて（落とすと高電圧でTRを壊す恐れあり）待機電流を減らすために 470k → 1M にします。  
 
<img src="https://github.com/user-attachments/assets/6ce74da2-f343-4ae3-ac8b-c14457e50024" width="180">    

**Sound Player アンプ部**   　　  

### 回路図
<img src="https://github.com/user-attachments/assets/d24ee328-6231-4893-ae8d-fd2b4a33f62f" width="640">   
  
**ATTINY402 Sound Player基板V2.1　回路図**

回路は前に説明した通りです。UPDIプログラミングのため、UPDI/3V/GNDの3ピンのコネクタを付けました。  
また、演奏中はモータ駆動信号をONして、トランジスタQ1 SS8050でON/OFFしJ2に出力します。  
モータ駆動信号がON時は、LED D2をONします。 LEDは1608～2012サイズであれば何でもかまいません  
抵抗・コンデンサは2012のパッドですが、1608サイズも実装可能です。      
U3 フラッシュメモリIC W25Q64はDIPだと高いので、SOP8サイズを購入し、DIP変換基板に載せてします。  
演奏する音楽や音声を変えるたびにデータを書き換える必要があるので、8ピンのICソケットを実装しています。  
J1～J5までXH、PHコネクタで設計してますが、J4 UPDIの3P ピンヘッダ以外は半田付けPADとして使用します。  
   
## **ソフト説明**
### **orgel1_2_tinyAVR_240928**
は、AVRマイコン ATTNY402 のSound Player基板制御用のファームウェアです。 　 
* ATTINY402（202） 8pin SOP対応  　
* ATMEL STUDIO（現Microchip Studio）対応  　
* 書き込みは UPDIを使用するが、PA0 UPDIピンをGPIOで使用するためHVP対応のプログラマーが必要（下記を参考に）
　　 [ATTINY202/402のFUSEビットをAVRDUDESSを使って書く方法](https://ameblo.jp/powpher/entry-12863906067.html)   
  UPDIを使用するがATMEL Studioはserial UPDIライタに対応していないので、AVR DUDESSを使ってオフラインで書き込みを行う

### orgel_SW_402プロジェクトファイル　　
orgel1_2_tinyAVR_240928フォルダの下のorgel_SW_402を開いて、頭のorgel_SW_402.atsln がプロジェクト   
ファイルです。orgel_SW_402フォルダ内には、その階層の中には    
* main.c : メインプログラム   
* song_idx.s : 今回は使いませんが、オルゴールを実装するときに曲のインデックスが入ってます   

  Dependencies内に入っているファイル（上の階層orgel1_2_tinyAVR_240928に入ってます）  
* orgel_conf.h : 各種設定値が入っています。音声再生とオルゴール再生もここで選択します     
* apl_SW.c : 音声を起動するトリガーとなる、スイッチ、静電スイッチ、CDS等を選択します  
　獅子舞タイプの時は、apl_SISIMAI.c になり、ピエゾ素子をトリガに使う専用ソフトになります   
* orgel.c : オルゴール・音声再生のメインエンジン部
* dev_xxx.c  : PWM周期ではいる割り込み処理。 PWM波形を生成する   
以上、変更が必要になる部分、重要な部分のみ説明しています。

###プログラムの説明と変更点
### main.c の変更点 （ポート割当て変更と曲インデックス変更）
**ATTINY402のポート割り当て**
```
tiny402のﾎﾟｰﾄの割当て(3線SPI)
1:VDD
2:(PA6)MOTOR_ON信号/(TxD)ﾃﾞﾊﾞｸﾞ情報
3:(PA7)MOSI出力(M25QのDIに繋ぐ)/MISO(10kΩ介してM25QのDOに繋ぐ)
4:(PA1)SS出力(M25QのCSに繋ぐ)
5:(PA2)SCK出力(M25QのCLKに繋ぐ)/SW2入力（ピエゾ信号）
6:(PA0)SW0入力/UPDIプログラム信号入出力
7:(PA3)/(WO0)正相出力
8:GND
```
**プログラムでPWMのポート設定**
```
//PWMのﾎﾟｰﾄ定義
#define	PWM_F_PORT	PORTA			//PWM正相のﾎﾟｰﾄ
#define	PWM_F_BIT	3			//PWM正相のﾋﾞｯﾄ
```
**3線SPIのポート設定**  
```
//SPIのﾎﾟｰﾄ定義
#define	SPI_SOFT				//SPIをｿﾌﾄ実装する
#define SPI_SCK_PORT	PORTA			//SPI_SCKのﾎﾟｰﾄ
#define SPI_SCK_BIT	2			//SPI_SCKのﾋﾞｯﾄ
#define SPI_MOSI_PORT	PORTA			//SPI_MOSIのﾎﾟｰﾄ
#define SPI_MOSI_BIT	7			//SPI_MOSIのﾋﾞｯﾄ
~
#else					//3線SPIのとき
#ifdef	SPI3					//3線SPIで接続する
#define SPI_SS_PORT	PORTA			//SPI_SSのﾎﾟｰﾄ
#define SPI_SS_BIT	1			//SPI_SSのﾋﾞｯﾄ
#endif
#define SPI_MISO_PORT	PORTA			//SPI_MISOのﾎﾟｰﾄ
#define SPI_MISO_BIT	7			//SPI_MISOのﾋﾞｯﾄ
```

**SW0の入力のポート定義**
```
//ﾄﾘｶﾞ入力のﾎﾟｰﾄ定義
#define	SW0_PORT	PORTA			//SW0のﾎﾟｰﾄ
#define	SW0_BIT		0			//SW0のﾋﾞｯﾄ
#define	SW0_INV					//SW0入力は負論理
					//以下のﾀｲﾏｰﾓｰﾄﾞとﾘｱﾙﾓｰﾄﾞは択一
#define SW0_TIMER				//SW0はﾀｲﾏｰﾓｰﾄﾞ
//#define	SW0_REAL			//SW0はﾘｱﾙﾓｰﾄﾞ		//ﾄﾘｶﾞのﾋﾞｯﾄ（PA0 UPDI)
```
SW1等も追加するなら、定義を増やします。  　

**モータ制御のポート定義**
```
//モータ制御追加　24/05/23　YM
#if BTL==0				//ｼﾝｸﾞﾙ出力のとき
//ﾓｰﾀｰ制御のﾎﾟｰﾄ定義
#define	MTR_PORT	PORTA			//ﾓｰﾀｰのﾎﾟｰﾄ
#define	MTR_BIT		6			//ﾓｰﾀｰのﾋﾞｯﾄ PA1→PA6
```
で定義を変更しています。

**音声再生時のインデックス変更**  
フラッシュメモリに書き込んだ曲のインデックスは、main.cに記述する必要があります。    
350行付近の不要な曲のインデックスをコメントアウトして、vos_mac.txtを貼り付けます。  
（今回はクリスマスソング）  
```
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
};
```
### orgel_conf.h の変更点 （PWMシングル出力と外部フラッシュIC音声再生を選択）
#define	BTL 		0	を選択します。（PWMシングル出力（正出力のみ））    
#define	VOICE_S		1	を選択します。（他は0にする）   
```
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
```

### apl_SW.c の変更点 （各機能の宣言 SW_ENコメントアウトを外す）  
```
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
```

## 音声データの作成方法
再生したい音声のファイルをMP3からWAV 8KHz 8bit（または16bit)のデータに変換します。
そのために使うアプリは、iTunesかAudicityです。
Audicityをつかってフォーマット変換する方法については、ブログに記載しています。
[【Part1】Sound Player基板V2の音声データの作成方法と特性検討](https://ameblo.jp/powpher/entry-12868881833.html)  
大泉さんのWAV2HEXでも、WAVファイルのサンプル周波数変換と変換bit 8bit化の機能はありますが、  
16kHzの倍数以外だと、変換誤差がでますので、注意してください。事前に変換することをお勧めします。

## デバイスへのプログラム書き込み方法   
今回のプロジェクトは、ATMEL STUDIO 7.0で作成されています。  
アプリをインストールしたら、プロジェクトファイルはmy Document下に作られると思います。  
my Document → ATMEL STUDIO → 7.0 → プロジェクトファイルをコピーします。  
プロジェクトファイルの中にあるorgel_SW_402を開いて、orgel_SW_402.atslnをダブルクリックして起動します。  
起動したら、右のSolution Explorerからmain.cをダブルクリックして開きます。  
 <img src="https://github.com/user-attachments/assets/4b8ee2ba-8c93-4c72-b56a-01a4cae7deb3" width="640">   

他のファイルは、Solution ExplorerのDependenciesに入ってます。▽をポチッとして開いてください。   
orgel_conf.h に各種設定がありますので、自分の環境に合わせてここでパラメータを設定してください。   
 <img src="https://github.com/user-attachments/assets/824d828f-191e-4464-af83-77f35efcd514" width="640">     

変更したら、上のBuild タブで Rebuild Solution を選んでください。エラーが出なければコンパイル完了です。  
プロジェクトのフォルダ内のDebugフォルダの中にhexファイルが生成されるので、AVRDUDEかAVRDUDESSで書き込みます。  

演奏する音声データを変更してプログラムを書き換える方法についても、ブログに記載していますので、参照してください。   
[【Part2】Sound Player基板V2の音声データの作成方法と特性検討](https://ameblo.jp/powpher/entry-12868913563.html)   

## 基板説明
基板の端子は下記に示しています。  
 <img src="https://github.com/user-attachments/assets/4ae1b704-3ac1-4445-b284-655c75480fdc" width="480">       
基板左下から、ピエゾ入力端子（GND Sig)、電源端子（GND 3V)、半固定ボリューム   
右上から、UPDIコネクタ（UPDI 3V GND)、  スピーカ端子（+　-）   
基板左上から、演奏中LED、操作スイッチ、フラッシュメモリICソケットになります。     

## 使い方  
⓵ 電源コネクタに単三電池 2本等で3V電源を接続し、スピーカ端子に8Ωスピーカを接続します。  
⓶ フラッシュメモリICソケットには、プログラムのインデックスで指定した音声を書き込んでおきます。  
⓷ 操作スイッチを押すとプログラムが起動し、LEDが点灯し音声（音楽の曲）を演奏します。  
⓸ 演奏の途中で、スイッチを押すとラウンドロビンで次の曲になります。長押しすると停止します。  
⓹ 曲の演奏中（LEDが点灯中）はモータ端子もONになり、接続したモータが回転し、おもちゃが動きます。  
⓺ 演奏を停止するとCPUはスリープになり、待機電流は1uA以下になります。  　


## 獅子舞タイプの使い方  
獅子舞タイプのプログラム書き込みの場合は、起動はスイッチではなく、ピエゾマイクで行います。   
⓵ ピエゾマイクを叩くか、音を入れると起動します。
⓶ 曲の演奏中は、誤動作を防ぐためピエゾマイクの入力は受け付けません。  
⓷ 曲が終わると数秒後にスリープに入り、次のピエゾマイクの入力を受け付けます。  
⓸ ピエゾマイクのアンプ回路を実装している場合、待機中の消費電流は3～4uAくらいになります。  

## 他のATTINY402開発参考資料
New ATTINY コード記述方法　Direct Port Manipulation  
https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/Ref_DirectPortManipulation.md  

Microchip  Getting Started with GPIO TB3229  
https://www.microchip.com/en-us/application-notes/tb3229  

ATTINY202/402/802 datasheet  
https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/ATtiny202-204-402-404-406-DataSheet-DS40002318A.pdf  

