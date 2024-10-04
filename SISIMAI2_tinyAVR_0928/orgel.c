//CH32V003�d�q�ٺް�Ver1_2�̴ݼ�ݕ�
//���������������ް��̐݌v�͢�h�L�������g\CH32V003�d�q�I���S�[��.xls����Q��
//�����ް��Ƌ��ް��̘g�g�݂�orgel.h���Q��
//�ݸޥ�����ް��̘g�g�݂�orgel.inc���Q��
//�߰Ċ����Ĥ���ݸސݒ�͌ŗL���������Q��


//==============================================
//I2C������ϸے�`
//==============================================
#define	I2C_SCL_PU	((PORT_tn *)&I2C_SCL_PORT)->PINnCTRL[I2C_SCL_BIT]=0b00001000;
#define	I2C_SCL_H	I2C_SCL_PORT.DIRCLR=1<<I2C_SCL_BIT
#define	I2C_SCL_L	I2C_SCL_PORT.DIRSET=1<<I2C_SCL_BIT
#define	I2C_SDA_PU	((PORT_tn *)&I2C_SDA_PORT)->PINnCTRL[I2C_SDA_BIT]=0b00001000;
#define	I2C_SDA_H	I2C_SDA_PORT.DIRCLR=1<<I2C_SDA_BIT
#define	I2C_SDA_L	I2C_SDA_PORT.DIRSET=1<<I2C_SDA_BIT
#define	I2C_SDA		(I2C_SDA_PORT.IN&1<<I2C_SDA_BIT)


//==============================================
//SPI������ϸے�`
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
//����N����ð���
//==============================================
static const unsigned short voiceN_vol[]={
	(unsigned long)VOICE0_VOL*PWM_STEP/100,
	(unsigned long)VOICE1_VOL*PWM_STEP/100,
	(unsigned long)VOICE2_VOL*PWM_STEP/100
};


//==============================================
//����ð���(�������ނ���ؽ��ْl�ɕϊ�����)
//==============================================
static const unsigned char onka_tbl[]={
	2,	//1=32��3�A��		=kR32
	4,	//2=16��3�A��		=kR16
	6,	//3=32������		=kK32
	8,	//4=8��3�A��		=kR8
	9,	//5=�t�_32������	=kP32
	12,	//6=16������		=kK16
	16,	//7=4��3�A��		=kR4
	18,	//8=�t�_16������	=kP16
	24,	//9=8������		=kK8
	32,	//10=2��3�A��		=kR2
	36,	//11=�t�_8������	=kP8
	48,	//12=4������		=kK4
	64,	//13=�S3�A��		=kR1
	72,	//14=�t�_4������	=kP4
	96,	//15=2������		=kK2
	144,	//16=�t�_2������	=kP2
	192,	//17=�S����		=kK1
	80,	//18=kW80		=kW80
	84,	//19=kW84		=kW84
	168,	//20=kW168		=kW168
	255,	//21=kW255		=kW255
};


//==============================================
//�������ނ����ޥ�����ɕϊ�����ð���
//�@�������:�����ޔԍ�(0�N�Z)(�����ް���̵����ޔԍ��Ƃ͋t���ɂȂ��Ă��邱�Ƃɗ��ӂ��邱��)
//�@��������:�����ԍ�(0�N�Z)(�����ް���̉����ԍ��Ƃ͋��E���قȂ邱�Ƃɗ��ӂ��邱��)
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
//����ð���
//==============================================
#define	smp_mac(fff)	((unsigned long)fff*256/10*256/25*PWM_PR/10*SONG_PS/4000+5)/10
						//fff=���g��[0.01Hz]
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
//����ð���
//==============================================
static struct KYOTUU kyotuu;			//���ʐ���ð���
#if	PART_N>0
static struct SONG song;			//���t����ð���
static struct PART part[PART_N];		//�߰Đ���ð���
#endif
#if	VOICE_N>0
static struct VOICEN voiceN[VOICE_N];		//����N�Đ�����ð���
#endif
#if	VOICE_I>0
static struct VOICEI voiceI;			//����I�Đ�����ð���
#endif
#if	VOICE_C>0
static struct VOICEC voiceC;			//����C�Đ�����ð���
#endif
#if	VOICE_S>0
static struct VOICES voiceS;			//����S�Đ�����ð���
#endif


//==============================================
//PWM�o���ޯ̧
//==============================================
static volatile short buf[OUT_BUF_N];		//�ޯ̧
static volatile unsigned char buf_write,buf_read;
						//�ޯ̧�̏����ݤ�Ǎ��݈ʒu


//==============================================
//Э�Đݒ菈��
//==============================================
//������


#if PART_N>0
//==============================================
//���ް�����������
//==============================================
static void song_init(void)
{
	struct PART *part_pt;
	unsigned char m,*q;

//DBG_C('\n');
	if((song.part_su=song.song_hdr->part_su)>PART_N) song.part_su=PART_N;
						//�ݸ��ް��̎����߰Đ����ݼ�ݑ���
						//�@�ő��߰Đ��𒴂��Ă�����
						//�@�ݼ�ݑ��̍ő��߰Đ��ɐ�������
//DBG_B(song.part_su);
	song.key=song.song_hdr->key;		//�ڒ��x���捞��
//DBG_B(song.key);
	song.onka_psn=song.song_hdr->onka_psn;	//������ؽ��ْl���捞��
//DBG_S(song.onka_psn);
	song.song_ps=0;				//���t��ؽ��ׂ�ر
	song.onka_ps=0;				//������ؽ��ׂ�ر
//DBG_D(&song,sizeof(song));
	for(m=0,q=(unsigned char *)part;m<sizeof(part);m++,q++) *q=0;
						//�߰Čʐ���ð��ق�ر
	for(m=0,part_pt=part;m<song.part_su;m++,part_pt++)
						//�߰Čʐ���ð��ق̏����ݒ�
	{
//DBG_C('\n');
//DBG_C('m');
//DBG_B(m);
//DBG_S(part_pt);
		part_pt->song_part=&(song.song_hdr->part[m]);
						//�߰ď��ւ��߲�����擾����
//DBG_S(part_pt->song_part);
		part_pt->onpu=(unsigned short *)part_pt->song_part->onpu;
						//�����g�`�ւ��߲�����擾����
//DBG_S(part_pt->ongen);
		part_pt->ongen=(struct WAVE_HDR *)part_pt->song_part->ongen;
						//�����g�`�ւ��߲�����擾����
//DBG_S(part_pt->ongen);
		part_pt->enve=(struct ENVE_HDR *)part_pt->song_part->enve;
						//����۰�ߔg�`�ւ��߲�����擾����
//DBG_S(part_pt->enve);
		part_pt->pitch=(struct PITCH_HDR *)part_pt->song_part->pitch;
						//�߯�����ޔg�`�ւ��߲�����擾����
//DBG_S(part_pt->pitch);
//DBG_D(&part[m],sizeof(part[m]));
	}
}


//==============================================
//�ȑI������(API�֐�)
//==============================================
static void SONG_SEL(
	unsigned char no)			//�Ȕԍ�(0�͉��t���~)
{

//DBG_C('\n');
//DBG_C('s');
//DBG_B(no);
//DBG_S(song_idx);
	song_idx=(struct SONG_IDX *)((unsigned short)song_idx|0x8000);
						//��۸����ׯ���ֈʒu�t����
//DBG_S(song_idx);
//DBG_D(song_idx,16);
//DBG_C('\n');
//DBG_B(song.no);
	if(no)					//���t�J�n�̂Ƃ�
	{
//DBG_B(song_idx->no);
		if(song.no==no) return;		//���t���̋Ȑ��ԍ��Ɠ����Ƃ��͖߂�
		if(no>song_idx->no) return;	//�������𒴂��Ă���Ƃ��͖߂�
		song.no=no;			//�Ȕԍ����L��
//DBG_B(song.no);
//DBG_S(song_idx->song_hdr[song.no-1]);
		song.song_hdr=(struct SONG_HDR *)song_idx->song_hdr[song.no-1];
						//��ͯ�ނւ��߲�����擾
//DBG_S(song.song_hdr);
//DBG_D(song.song_hdr,64);
		song_init();			//���ް���������
	}
	else					//���t���~�̂Ƃ�
	{
		song.no=0;			//���t�I���ɂ���
		song.pcm=0;			//�S�߰ĕ���PWM�ޭ�è�l��
						//�@�ر���Ă���
	}
//DBG_C('>');
}


//==============================================
//�ٺްى��t����
//==============================================
static void song_exe(void)
{
	struct PART *part_pt;			//�߰Čʐ���ð����߲��
	unsigned char n,m,c;
	short j;
	union					//8�ޯļ�ĉ��Z�̌�����
	{
		unsigned short sss;
		unsigned char bbb[2];
	} sssbbb;

//DBG_C('<');
	//������
	song.pcm=0;				//�S�߰ĕ���PWM�l��0�ɂ��Ă���
	m=0;					//���t�����߰Đ���ر���Ă���

	//������ؽ��ׂ��X�V
//DBG_S(song.onka_ps);
	if(song.onka_ps) song.onka_ps--;	//������ؽ��ׂ��c���Ă�����޸�
	else song.onka_ps=song.onka_psn;	//�������Ă����珉��������

	//�߰ĉ��t����
	for(n=0,part_pt=part;n<song.part_su;n++,part_pt++)
						//�����߰Đ������J�Ԃ�
	{
//DBG_B(n);
		if(!part_pt->song_part) continue;
						//���t���I�����Ă����߰Ă͔�΂�
		m++;				//���t�����߰Đ���ݸ�

		//��������o��
//DBG_C('t');
		while(!part_pt->onka_zan)	//�����c�������Ȃ����玟�̉����֐i��
						//�@�ʏ퉹��������邩������I���܂ŌJ�Ԃ�
						//�@�܂褐��䉹���͈�C�ɏ�������
		{
//DBG_C('\n');
//DBG_C('>');
//DBG_B(n);
//DBG_C('+');
//DBG_S(part_pt->song_part->onpu);
//DBG_S(part_pt->onpu_of);
			if(part_pt->onpu_of==0xffff)
						//KB���t�̂Ƃ���
			{
//DBG_C('b');
				part_pt->onpu_cd=part_pt->onpu_kb;
						//KB���t�p�ޯ̧���特�����ނ���o��
				part_pt->onpu_kb=0;
						//KB���t�p�ޯ̧��ر���Ă���
			}
			else			//�ٺްى��t�̂Ƃ���
				part_pt->onpu_cd=*(part_pt->onpu+part_pt->onpu_of++);
						//�������ނ��擾��������ï�߂�i�߂Ă���
//DBG_S(part_pt->onpu_cd);
			if(part_pt->onpu_cd&0x2000)//�@�\����2�̂Ƃ�
			{
				if(part_pt->onpu_cd&0x1000)
						//��߰ĕ���ȊO�̂Ƃ�
				{
					if(part_pt->onpu_cd&0x0800)
							//�g�`�؊����̂Ƃ�
					{
//DBG_C('w');
						switch(part_pt->onpu_cd&0x0700)
						{
						case 0x0000:	//�����g�`�̂Ƃ�
//DBG_C('o');
							part_pt->ongen=
								(struct WAVE_HDR *)
								*(part_pt->onpu+
								part_pt->onpu_of++);
								//�����g�`���ڽ���擾���
								//�@�����ï�߂�i�߂Ă���
//DBG_S(part_pt->ongen);
							break;
						case 0x0100:	//����۰�ߔg�`�̂Ƃ�
//DBG_C('e');
							part_pt->enve=
								(struct ENVE_HDR *)
								*(part_pt->onpu+
								part_pt->onpu_of++);
								//����۰�ߔg�`���ڽ���擾���
								//�@�����ï�߂�i�߂Ă���
//DBG_S(part_pt->enve);
							break;
						case 0x0200:	//�߯�����ޔg�`�̂Ƃ�
//DBG_C('p');
							part_pt->pitch=
								(struct PITCH_HDR *)
								*(part_pt->onpu+
								part_pt->onpu_of++);
								//�߯�����ޔg�`���ڽ���擾���
								//�@�����ï�߂�i�߂Ă���
//DBG_S(part_pt->pitch);
							break;
						}
					}
					else if(part_pt->onpu_cd&0x0400)
							//�e��l�ݒ�̂Ƃ�
					{
//DBG_C('k');
						switch(part_pt->onpu_cd&0x0300)
						{
						case 0x0000:	//��ۼè�ݒ�̂Ƃ�
//DBG_C('v');
							part_pt->velo=
								((unsigned long)
								(part_pt->onpu_cd&0x00ff)*
								PWM_STEP)/256;
//DBG_S(part_pt->velo);
							break;
						case 0x0100:	//����۰����ѐݒ�̂Ƃ�
//DBG_C('e');
							part_pt->enve_psn=
								part_pt->song_part->enve_psn*
								(part_pt->onpu_cd&0x00ff);
//DBG_S(part_pt->enve_psn);
							break;
						case 0x0200:	//���ߐݒ�̂Ƃ�
//DBG_C('t');

							song.onka_psn=
								(song.song_hdr->onka_psn*
								(part_pt->onpu_cd&0x00ff))>>7;
//DBG_S(song.onka_psn);
							break;
						case 0x0300:	//�߯��������ѐݒ�̂Ƃ�
//DBG_C('p');

							part_pt->pitch_psn=
								part_pt->song_part->pitch_psn*
								(part_pt->onpu_cd&0x00ff);
//DBG_S(part_pt->pitch);
							break;
						}

					}
					else		//����������̂Ƃ�
					{
//DBG_C('j');
						part_pt->onpu_of=part_pt->onpu_cd&0x03ff;
							//������ݒ肷��
//DBG_S(part_pt->onpu_of);
					}
				}
				else		//��߰ĕ���̂Ƃ�
				{
//DBG_C('r');
					c=(part_pt->onpu_cd&0x0c00)>>10;
							//��߰Ĕԍ��𓾂�
//DBG_B(c);
//DBG_B(part_pt->rpt[c]);
					if(part_pt->rpt[c])
							//��߰ĉ񐔎c������Ƃ�
					{
//DBG_C('z');
						part_pt->rpt[c]--;
							//��߰ĉ񐔎c���޸؂���
//DBG_B(part_pt->rpt[c]);
						part_pt->onpu_of=part_pt->onpu_cd&0x03ff;
							//������ݒ肷��
//DBG_S(part_pt->onpu_of);
					}
				}
			}
			else if(part_pt->onpu_cd&0x1f00)
						//���t�����̂Ƃ�
			{
//DBG_C('\n');
//DBG_C('u');
				sssbbb.sss=part_pt->onpu_cd;
						//�����̉������ނ��特���c��ݒ�
				part_pt->onka_zan=onka_tbl[((sssbbb.bbb[1]&0x1f)-1)];
//DBG_B(part_pt->onka_zan);
				if(part_pt->onpu_cd&0x007f)
						//���������̂Ƃ�
				{
//DBG_C('\n');
//DBG_C('h');
//DBG_B(song.key);
					c=((part_pt->onpu_cd&0x003f)+song.key)&0x3f;
						//�����Ɉڒ��x���������Ĥ�͈͓��ɋK������
//DBG_B(c);
					c=onkou_mei_tbl[c];
						//�����ޔԍ��Ɖ������ނ𓾂�
//DBG_B(c);
					part_pt->ongen_tobi=onkou_tbl[c&0x0f];
						//�����̻���ٔ�ѐ��𓾂�
//DBG_S(part_pt->ongen_tobi);
					if(c>>=4) part_pt->ongen_tobi>>=c;
						//�����ޔԍ��ż�Ă���
//DBG_S(part_pt->ongen_tobi);
				}
				else part_pt->ongen_tobi=0;
						//�x���̂Ƃ��ͻ���ٔ�ѐ���0�ɂ���
//DBG_S(part_pt->ongen_tobi);
				if(!(part_pt->onpu_cd&0x0080))
						//����װ�łȂ��Ƃ�
				{
//DBG_C('c');
					part_pt->enve_of=0;
						//����۰�ߔg�`ð��ٵ̾�Ă�ر
					part_pt->enve_ps=0;
						//����۰�ߏ����Ή�����ؽ��ׂ�������
					part_pt->pitch_of=0;
						//�߯�����ޔg�`ð��ٵ̾�Ă�ر
					part_pt->pitch_ps=0;
						//�߯�����ޏ����Ή�����ؽ��ׂ�������
				}
			}
			else if(part_pt->onpu_cd&0x0040)
						//��߰ĉ񐔐ݒ�̂Ƃ�
			{
//DBG_C('r');
				c=(part_pt->onpu_cd&0x0030)>>4;
						//��߰Ĕԍ��𓾂�
//DBG_B(c);
				part_pt->rpt[c]=part_pt->onpu_cd&0x000f;
//DBG_B(part_pt->rpt[c]);
			}
			else if(part_pt->onpu_cd&0x0020)
						//�]���ݒ�̂Ƃ�
			{
//DBG_C('i');
				if((c=part_pt->onpu_cd&0x001f)==0)
					song.key=song.song_hdr->key;
							//�����l��0�̂Ƃ���
							//�@�ݸ�ͯ�ނ̷��ɖ߂�
				else
				{			//�����l��0�łȂ����
					song.key+=c;	//���Ă̷����瑝������
					if(c>15) song.key-=32;
							//�����̂Ƃ��ɐ�������
				}
//DBG_B(song.key);
			}
			else if(part_pt->onpu_cd&0x0010)
			{
						//KB���t�ڍs�̂Ƃ�
				part_pt->onpu_of=0xffff;//KB���t�ɂ���
//DBG_S(part_pt->onpu_of);
			}
			else break;		//���t�I���̂Ƃ�
		}

		//�����̔���
//DBG_C('h');
//DBG_B(part_pt->onka_zan);
		if(part_pt->onka_zan)		//�����c�������(�����I���łȂ����)
						//�@���t���������s����
		{

			//�������X�V
//DBG_C('a');
//DBG_S(song.onka_ps);
			if(!song.onka_ps)	//������ؽ��ׂ��������Ă�����
				part_pt->onka_zan--;
						//�����c���޸؂���
//DBG_B(part_pt->onka_zan);

			//��������
//DBG_B(part_pt->ongen_tobi);
			if(part_pt->ongen_tobi)	//���������̂Ƃ�
			{

				//����۰�ߏ���
//DBG_C('\n');
//DBG_C('e');
//DBG_S(part_pt->enve_psn);
				if(part_pt->enve_psn)
						//����۰�߂��ݒ肳��Ă���Ƃ���
						//�@����۰�ߏ������s��
				{
//DBG_C('s');
//DBG_S(part_pt->enve_ps);
					if(!part_pt->enve_ps)
						//����۰�ߏ��������ݸނ̂Ƃ�
					{
//DBG_C('t');
//DBG_S(part_pt->velo);
//DBG_B(part_pt->enve_of);
//DBG_B(part_pt->enve->data[part_pt->enve_of]);
						part_pt->velo_enve=((unsigned long)
							part_pt->velo*
							part_pt->enve->
							data[part_pt->enve_of])/256;
						//����۰�ߏ��������ۼè�l�����߂�
//DBG_S(part_pt->velo_enve);

//DBG_B(part_pt->enve->smp);
						//����ٵ̾�Ă�i�߂�
						if(part_pt->enve_of<
							part_pt->enve->smp)
							part_pt->enve_of++;
							//����ٵ̾�Ă�i�߂Ĥ�Ō�ɋK������
//DBG_B(part_pt->enve_of);
					}
					if(part_pt->enve_ps++>part_pt->enve_psn)
					{
						//����۰�߂���ؽ��ׂ�ݸ؂��Ė���������
						part_pt->enve_ps=0;
							//����۰�߂���ؽ��ׂ�ر
					}
				}
				else		//����۰�߂��ݒ肳��Ă��Ȃ��Ƃ���
				{
					part_pt->velo_enve=part_pt->velo;
						//�@��ۼè�ݒ�l�����̂܂܎g��
				}
//DBG_S(part_pt->velo_enve);

				//��������ْl�𓾂�
//DBG_C('\n');
//DBG_C('w');
//DBG_S(part_pt->ongen_of);
				sssbbb.sss=part_pt->ongen_of;
//DBG_B(sssbbb.bbb[1]);
				j=(short)(part_pt->ongen->data[sssbbb.bbb[1]])-128;
						//��������ْl�𓾂�
//DBG_S(j);
				j=((long)part_pt->velo_enve*j)/256;
						//��ۼè����������
//DBG_S(j);
				song.pcm+=j;	//�S�߰ĕ���PWM�ޭ�è�l�ɤ
						//�@�����߰ĕ������Z����
//DBG_S(song.pcm);

				//��������ٵ̾�Ă�i�߂�
//DBG_C('o');
//DBG_S(part_pt->ongen_of);
//DBG_S(part_pt->ongen_tobi);
				part_pt->ongen_of+=part_pt->ongen_tobi;
						//�g�`�ް��̵̾�Ă�i�߂Ĥ
						//�@����ِ���256�Œ�̂���
						//�@�����۰�͖�������
//DBG_S(part_pt->ongen_of);

				//�߯�����ޏ���
//DBG_C('\n');
//DBG_C('p');
				if(part_pt->pitch_psn)
						//�߯�����ނ��ݒ肳��Ă���Ƃ���
						//�@�߯�����ޏ������s��
				{
//DBG_C('\n');
//DBG_S(part_pt->pitch_ps);
					if(!part_pt->pitch_ps)
						//�߯�����ޏ��������ݸނ̂Ƃ�
					{

						//�߯�����޻���ْl�𓾂�
						j=part_pt->pitch->data
							[part_pt->pitch_of];
							//�߯�����޻���ْl�𓾂�
//DBG_S(j);
//DBG_S(part_pt->ongen_tobi);
						part_pt->ongen_tobi=
							part_pt->ongen_tobi+j-128;
							//��������ٔ�ѐ��𑝌�����

						//�߯�����޻���ٵ̾�Ă�i�߂�
//DBG_S(part_pt->ongen_tobi);
						if(part_pt->pitch_of<
							part_pt->pitch->smp)
							part_pt->pitch_of++;
							//����ٵ̾�Ă�i�߂Ĥ�Ō�ɋK������
//DBG_B(part_pt->pitch_of);
					}
					if(part_pt->pitch_ps++>part_pt->pitch_psn)
					{
						//�߯�����ނ���ؽ��ׂ�ݸ؂��Ė���������
						part_pt->pitch_ps=0;
							//�߯�����ނ���ؽ��ׂ�ر
//DBG_S(part_pt->pitch_ps);
					}
				}
			}
		}

		else				//�����I���̂Ƃ�
		{
			//�߰ďI������
//DBG_C('t');
			if(part_pt->onpu_of!=0xffff)
						//�ٺްى��t�̂Ƃ���
				part_pt->song_part=0;
						//�߰ĉ��t�I����\������
		}
//DBG_C('r');
	}
//DBG_B(m);
	if(!m)					//�S�߰Ă��I��������
	{
//DBG_S(song.song_hdr->next);
		if(song.song_hdr->next)		//�A�����t����Ƃ�
		{
			song.song_hdr=(struct SONG_HDR *)song.song_hdr->next;
						//��ͯ�ނւ��߲�����擾
//DBG_S(song.song_hdr);
//DBG_D(song.song_hdr,64);
			song_init();		//���ް���������
		}
		else				//�P�ȉ��t�̂Ƃ�
		{
			song.no=0;		//�ȉ��t�I���̕\��
			CB_SONG_END();		//���t�I��������ޯ��֐����Ă�
		}
	}
//DBG_C('>');
}
#endif


#if VOICE_N>0
//==============================================
//����N�I������(API�֐�)
//==============================================
static void VOICEN_SEL(				//�߂�l����
	unsigned char ch,			//ch�ԍ�
	unsigned char no)			//�����ԍ�(0�͍Đ����~)
{
	struct VOICEN *voiceN_pt;		//����N�Đ�����ð����߲��

//DBG_C('\n');
//DBG_C('s');
//DBG_B(ch);
//DBG_B(no);
//DBG_D(voiceN_idx,sizeof(voiceN_idx));
//DBG_C('i');
	voiceN_pt=voiceN+ch;			//����N�Đ�����ð����߲����ݒ�
	if(no)					//�Đ��J�n�̂Ƃ�
	{
		if(no>sizeof(voiceN_idx)/sizeof(voiceN_idx[0])) return;
						//�������𒴂��Ă���Ƃ��͖߂�
		if(voiceN_pt->no!=no)		//�������̉����ԍ��ƈقȂ�Ƃ��̂�
						//�@������؂�ւ���
		{
			voiceN_pt->no=no--;	//�����ԍ���ݒ�
			voiceN_pt->begin=voiceN_idx[no].adr;
						//�����ް��̊J�n���ڽ��ݒ�
//DBG_S(voiceN_pt->begin);
			voiceN_pt->end=voiceN_pt->begin+voiceN_idx[no].len;
						//�����ް��̏I�����ڽ��ݒ�
//DBG_S(voiceN_pt->end);
			voiceN_pt->psn=voiceN_idx[no].psn;
						//�Đ�������ؽ��ْl��ݒ�
//DBG_B(voiceN_pt->psn);
			voiceN_pt->pcm=0;	//PCM�l��������
//DBG_B(voiceN_pt->pcm);
		}
	}
	else					//�Đ����f�̂Ƃ�
	{
		voiceN_pt->no=0;		//�Đ��I���ɂ���
	}
//DBG_D(voiceN_pt,sizeof(voiceN[0]));
}


//==============================================
//����N�Đ�����
//==============================================
static void voiceN_exe(
	unsigned char ch)			//ch�ԍ�
{
	struct VOICEN *voiceN_pt;		//����N�Đ�����ð����߲��

//DBG_C('\n');
//DBG_C('p');
//DBG_B(ch);
	voiceN_pt=voiceN+ch;			//����N�Đ�����ð����߲����ݒ肷��
	voiceN_pt->pcm=*voiceN_pt->begin++-128;//�����ް�����o��o���Ĥ
						//�@8�ޯ�PCM�`����signed�ɕϊ�
//DBG_S(voiceN_pt->pcm);
//DBG_S(voiceN_vol[ch]);
	voiceN_pt->pcm=(long)voiceN_pt->pcm*voiceN_vol[ch]/128;
						//���ʔz�����|����
//DBG_S(voiceN_pt->pcm);
	if(voiceN_pt->begin==voiceN_pt->end)	//�����ް����Ō�̂Ƃ�
	{
//DBG_C('e');
		voiceN_pt->no=0;		//�Đ��I���ɂ���
		CB_VOICEN_END(ch);		//�����Đ��I������(����ޯ��֐�)���ďo��
	}
}
#endif


#if VOICE_I>0				//I2C��؂��g���Ƃ�
#ifdef I2C_SOFT				//I2C���Ď�������Ƃ�
//==============================================
//I2C���ĺ��ި���
//==============================================
static void i2c_start(void)
{

//DBG_C('s');
	I2C_SCL_H;				//SCL��H(High-Z)
	wait_1us();
	I2C_SDA_L;				//SCL��H�̂܂�SDA��L
	wait_1us();
	I2C_SCL_L;				//SCL��L
	wait_1us();
	I2C_SDA_H;				//SDA��H(High-Z)
	wait_1us();
}


//==============================================
//I2C�į�ߺ��ި���
//==============================================
static void i2c_stop(void)
{

//DBG_C('p');
	I2C_SDA_L;				//SDA��L
	wait_1us();
	I2C_SCL_H;				//SCL��H(High-Z)
	wait_1us();
	I2C_SDA_H;				//SCL��H�̂܂�SDA��H(High-Z)
	wait_1us();
}


//==============================================
//I2C���M
//==============================================
static void i2c_send(
	unsigned char data)			//���M�ް�
{
	unsigned char n=8;

//DBG_C('d');
	while(n--)				//8�ޯĕ��J�Ԃ�
	{
		if(data&0x80) I2C_SDA_H;	//���M�ޯĂ�ݒ肷��
		else I2C_SDA_L;
		data<<=1;			//�ޯĂ�i�߂�
		wait_1us();
		I2C_SCL_H;			//SCL��H(High-Z)
		wait_1us();
		I2C_SCL_L;			//SCL��L
		wait_1us();
	}
	I2C_SDA_H;				//SDA��High-Z(ACK��M)
	wait_1us();
	I2C_SCL_H;				//SCL��H(High-Z)
	wait_1us();
	I2C_SCL_L;				//SCL��L
	wait_1us();
}


//==============================================
//I2C��M+ACK����
//==============================================
static unsigned char i2c_recv_ack(void)		//��M�ް���Ԃ�
{
	unsigned char n=8,data=0;

//DBG_C('k');
	while(n--)				//8�ޯĕ��J�Ԃ�
	{
		I2C_SCL_H;			//SCL��H(High-Z)
		wait_1us();
		data<<=1;			//�ޯĂ�i�߂�
		if(I2C_SDA) data|=1;		//��M�ޯĂ��捞��
		I2C_SCL_L;			//SCL��L
		wait_1us();
	}
	I2C_SDA_L;				//SDA��L(ACK)
	wait_1us();
	I2C_SCL_H;				//SCL��H(High-Z)
	wait_1us();
	I2C_SCL_L;				//SCL��L
	I2C_SDA_H;				//SDA��H(High-Z)
	wait_1us();
	return(data);				//��M�ް���Ԃ�
}


//==============================================
//I2C��M+NOACK����
//==============================================
static unsigned char i2c_recv_noack(void)	//��M�ް���Ԃ�
{
	unsigned char n=8,data=0;

//DBG_C('n');
	while(n--)				//8�ޯĕ��J�Ԃ�
	{
		I2C_SCL_H;			//SCL��H(High-Z)
		wait_1us();
		data<<=1;			//�ޯĂ�i�߂�
		if(I2C_SDA) data|=1;		//��M�ޯĂ��捞��
		I2C_SCL_L;			//SCL��L
		wait_1us();
	}
	I2C_SDA_H;				//SDA��H(High-Z)(NOACK)
	wait_1us();
	I2C_SCL_H;				//SCL��H(High-Z)
	wait_1us();
	I2C_SCL_L;				//SCL��L
	wait_1us();
	return(data);				//��M�ް���Ԃ�
}


#else					//����I2CӼޭ�ق��g���Ƃ�
//==============================================
//I2C���ĺ��ި���
//==============================================
static void i2c_start(
	unsigned char slave)			//�ڰ�ޱ��ڽ
{
	unsigned char w;

//DBG_C('s');
//DBG_B(slave);
	//���ĺ��ި��݌�ɽڰ�ޱ��ڽ�𑗐M
//DBG_B(TWI0.MSTATUS);
	TWI0.MADDR=slave;			//�ڰ�ޱ��ڽ���
//DBG_B(TWI0.MSTATUS);

	//ACK��҂�
	w=0;
	while(!(TWI0.MSTATUS&TWI_RIF_bm)&&!(TWI0.MSTATUS&TWI_WIF_bm))
						//����M������҂�
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm);	//����M������ر����
//DBG_B(TWI0.MSTATUS);
}


//==============================================
//I2C��߰Ľ��ĺ��ި���
//==============================================
static void i2c_rep_start(
	unsigned char slave)			//�ڰ�ޱ��ڽ
{

//DBG_C('e');
	//���ĺ��ި��݌�ɽڰ�ޱ��ڽ�𑗐M
//DBG_B(TWI0.MSTATUS);
	TWI0.MADDR=slave;			//�ڰ�ޱ��ڽ���
//DBG_B(TWI0.MSTATUS);
}


//==============================================
//I2C�į�ߺ��ި���
//==============================================
static void i2c_stop(void)
{

//DBG_C('p');
	TWI0.MCTRLB|=TWI_MCMD_STOP_gc;		//�į�ߺ��ި���
//DBG_B(TWI0.MSTATUS);
}


//==============================================
//I2C�ް����M
//==============================================
static void i2c_send(
	unsigned char data)
{
	unsigned char w;

//DBG_C('d');
//DBG_B(data);
	//�ް��𑗐M
//DBG_B(TWI0.MSTATUS);
	TWI0.MDATA=data;			//���M�ް����
//DBG_B(TWI0.MSTATUS);

	//���M������҂�
	w=0;
	while(!(TWI0.MSTATUS&TWI_WIF_bm))	//���M������҂� 
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
}


//==============================================
//I2C��M+ACK����
//==============================================
static unsigned char i2c_recv_ack(void)
{
	unsigned char data;
	unsigned char w;

//DBG_C('a');
	//��M��҂�
	w=0;
	while(!(TWI0.MSTATUS&TWI_RIF_bm))	//��M������҂�
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm);	//����M��ر����
//DBG_B(TWI0.MSTATUS);
	TWI0.MCTRLB&=~(1<<TWI_ACKACT_bp);	//ACK������Ă���
//DBG_B(TWI0.MCTRLB);
	data=TWI0.MDATA;			//��M�ް�����o��
//DBG_B(data);
	TWI0.MCTRLB|=TWI_MCMD_RECVTRANS_gc;	//ACK��������
//DBG_B(TWI0.MCTRLB);
	return(data);					
}


//==============================================
//I2C��M+NOACK����
//==============================================
static unsigned char i2c_recv_noack(void)
{
	unsigned char data;
	unsigned char w;

//DBG_C('n');
	//��M��҂�
	w=0;
	while(!(TWI0.MSTATUS&TWI_RIF_bm))	//��M������҂�
	{
//DBG_B(TWI0.MSTATUS);
		if(w++>50) break;
		wait_1us();
	}
	TWI0.MSTATUS|=(TWI_RIF_bm|TWI_WIF_bm);	//����M��ر����
//DBG_B(TWI0.MSTATUS);
	TWI0.MCTRLB|=TWI_ACKACT_NACK_gc;	//NACK������Ă���
//DBG_B(TWI0.MCTRLB);
	data=TWI0.MDATA;			//��M�ް�����o��
//DBG_B(data);
	return(data);					
}
#endif


//==============================================
//����I�I������(API�֐�)
//==============================================
static void VOICEI_SEL(				//�߂�l����
	unsigned short no)			//�����ԍ�(0�͍Đ����~)
{


//I2C�]����
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
	if(voiceI.no!=no)			//�������̉����ԍ��ƈقȂ�Ƃ���
	{
		if(voiceI.no)			//�Đ����̂Ƃ���
		{
			wait_us(50);		//���܂��Ȃ�(�ʏ�ٰĂ̓]���I����҂�)
						//�@400kbps�ł̓K���l
			i2c_recv_noack();	//��M+NOACK����
			i2c_stop();		//I2C�į�ߺ��ި���
			voiceI.no=0;		//�Đ���~�ɂ���
			voiceI.pcm=0;		//PCM�l��������
//DBG_B(voiceI.pcm);
		}
	}

	if(no)					//�Đ��J�n�̂Ƃ�
	{
		if(no>sizeof(voiceI_idx)/sizeof(voiceI_idx[0])) return;
						//�������𒴂��Ă���Ƃ��͖߂�
		voiceI.no=no--;			//�����ԍ���ݒ肵�Ĥ�ԍ���0�N�Z�ɂ���
		voiceI.begin=voiceI_idx[no].adr;//�����ް��̊J�n���ڽ��ݒ�
//DBG_S(voiceI.begin);
		voiceI.end=voiceI.begin+voiceI_idx[no].len;
						//�����ް��̏I�����ڽ��ݒ�
//DBG_S(voiceI.end);
		voiceI.psn=voiceI_idx[no].psn;	//�Đ�������ؽ��ْl��ݒ�
//DBG_B(voiceI.psn);
		voiceI.sla=voiceI_idx[no].sla;	//I2C�ڰ�ޱ��ڽ��ݒ�
//DBG_B(voiceI.sla);
#ifdef I2C_SOFT				//I2C���Ď�������Ƃ�
		i2c_start();			//I2C���ĺ��ި���
		i2c_send(voiceI.sla);		//�ڰ�ޱ��ڽ(W)���M
#else					//����I2CӼޭ�ق��g���Ƃ�
		i2c_start(voiceI.sla);		//I2C���ĺ��ި��ݤ�ڰ�ޱ��ڽ(W)���M
#endif
		i2c_send(voiceI.begin>>8);	//���ڽ��ʑ��M
		i2c_send(voiceI.begin);		//���ڽ���ʑ��M
#ifdef I2C_SOFT				//I2C���Ď�������Ƃ�
		i2c_start();			//I2C���ĺ��ި���
		i2c_send(voiceI.sla|1);		//�ڰ�ޱ��ڽ+�Ǎ��ݎw�著�M
#else					//����I2CӼޭ�ق��g���Ƃ�
		i2c_rep_start(voiceI.sla|1);	//I2C��߰Ľ��ĺ��ި��ݤ�ڰ�ޱ��ڽ(R)���M
#endif
	}
//DBG_D(&voiceI,sizeof(voiceI));
}


//==============================================
//����I�Đ�����
//==============================================
static void voiceI_exe(void)
{
	unsigned char data;

//DBG_C('\n');
//DBG_C('p');
//DBS_H;
	if(++voiceI.begin==voiceI.end)		//�����ް����Ō�̂Ƃ�
	{
		data=i2c_recv_noack();		//��M+NOACK����
	}
	else					//�����ް����r���̂Ƃ�
	{
		data=i2c_recv_ack();		//��M+ACK����
	}
//DBS_L;
//DBG_B(data);
	voiceI.pcm=(short)data-128;		//�����ް���signed�ɕϊ�
//DBG_S(voiceI.pcm);
	voiceI.pcm=(long)voiceI.pcm*((long)VOICEI_VOL*PWM_STEP/100)/128;
						//���ʔz�����|����
//DBG_S(voiceI.pcm);
	if(voiceI.begin==voiceI.end)		//�����ް����Ō�̂Ƃ�
	{
//DBG_C('e');
		voiceI.no=0;			//�Đ��I���ɂ���
		i2c_stop();			//I2C�į�ߺ��ި���
		voiceI.pcm=0;			//PCM�l��������
		CB_VOICEI_END();		//�����Đ��I������(����ޯ��֐�)���ďo��
	}
}
#endif


#if (VOICE_C+VOICE_S)>0			//SD�܂���SPI��؂��g���Ƃ�
#ifdef SPI_SOFT				//SPI���Ď�������Ƃ�
//==============================================
//SS��ȹްđ҂�
//==============================================
#ifdef	SS_WAIT_TIME			//SS�҂����Ԃ���`����Ă���Ƃ�
#define	SPI_SS_WAIT()	wait_us(SS_WAIT_TIME);	//SS��ȹްĂ���܂ő҂�
#else					//SS�҂����Ԃ���`����Ă��Ȃ��Ƃ�
#define	SPI_SS_WAIT()				//SSȹްđ҂������Ȃ�
#endif


//==============================================
//SPI����M
//==============================================
static unsigned char spi_trans(			//��M�����ް���Ԃ�
	unsigned char data,			//���M�����ް�
	unsigned char sck_h)			//�ŏI�ޯĂ�SCK�̈���
						//�@(2��SPI������ܰ�޳݂̂���)
						//�@0=L�ɂ���1=H��ێ�����
{
	unsigned char c=8;

//DBS_H;
//DBG_C('(');
//DBG_B(data);
	while(c--)
	{
		if(data&0x80) SPI_MOSI_H;	//�ް��ޯĂ�
		else SPI_MOSI_L;		//�@MOSI�ɏ悹��
#if defined(SPI2)||defined(SPI3)	//2��SPI�܂���3��SPI�̂Ƃ�
		SPI_MOSI_OUT;			//MOSI���o��Ӱ��
#endif
#ifdef SPI2 				//2��SPI�̂Ƃ�
		__disable_irq();		//�����݋֎~
#endif
		SPI_SCK_H;			//SCK��H
#if defined(SPI2)||defined(SPI3)	//2��SPI�܂���3��SPI�̂Ƃ�
		SPI_MISO_IN;			//MISO�����Ӱ��
		wait_1us();
#endif
		data<<=1;			//�ް������ɐi�߂�
		if(SPI_MISO) data++;		//MISO���ް��Ɏ捞��
		if(c||(!sck_h))			//�ŏI�ޯĈȊO����ܰ�޳݈ȊO��
		{
			SPI_SCK_L;		//SCK��L
		}
#ifdef SPI2 				//2��SPI�̂Ƃ�
		__enable_irq();			//�����݋���
#endif
	};
//DBG_B(data);
//DBG_C(')');
//DBS_L;
	return(data);				//��M�����ް���Ԃ�
}


//==============================================
//SPIؾ��
//==============================================
static void spi_reset(void)
{

	SPI_SS_H;				//SS��ȹްĂ���
	SPI_SS_WAIT();				//SSȹްĎ��Ԃ�҂�
}


#else					//����SPIӼޭ�ق��g���Ƃ�
//==============================================
//����SPIӼޭ�ق��g���Ƃ���ϸےu����
//==============================================
#define	SPI_SS_WAIT()				//SSȹްđ҂������Ȃ�
#define spi_trans(x,y) spi_trans_(x)		//�ŏI�ޯĂ�SCK�����𖳎�����


//==============================================
//SPI����M
//==============================================
static unsigned char spi_trans_(		//��M�����ް���Ԃ�
	unsigned char data)			//���M�����ް�
{

//DBS_H;
//DBG_C('(');
//DBG_B(data);
	SPI0.DATA=data;				//����M�J�n
	while(!(SPI0.INTFLAGS&0x80));		//����M������҂�
//DBG_B(data);
//DBG_C(')');
//DBS_L;
	return(SPI0.DATA);			//��M�����ް���Ԃ�
}


//==============================================
//SPIؾ��
//==============================================
static void spi_reset(void)
{

	SPI_SS_H;				//SS��ȹްĂ���
}
#endif
#endif


#if VOICE_C>0				//SD���g���Ƃ�
//==============================================
//SD��������ڽ��ݽ����M����
//==============================================
static unsigned char mmsd_resp(void)		//ڽ��ݽ��Ԃ�(0=OK�0x11=��ѱ��)
{
	unsigned char n=255,res;

//DBG_C('!');
	while(n--)
	{
		res=spi_trans(0xff,0);
//DBG_B(res);
		if((res&0x80)==0) break;	//b7��0�̂Ƃ��͔�����
	}
	return(res);				//ڽ��ݽ��Ԃ�
}


//==============================================
//SD����������������
//==============================================
static unsigned char mmsd_init(void)		//ڽ��ݽ��Ԃ�(0=OK�0x11=��ѱ�Ĥ���̑��װ)
{
	unsigned char n,res;

	//SD���I���ɂ���
//DBG_C('\n');
//DBG_C('u');
	spi_reset();				//SPI��ؾ�Ă���

	//��а�ۯ��𑗐M����
//DBG_C('d');
	for(n=0;n<10;n++)			//74�ȏ�(80)��
	{
		spi_trans(0xff,0);		//��а�ۯ��𑗐M����
	}

	//SD��I������
//DBG_C('s');
	SPI_SS_L;				//���߾ڸ�
	wait_us(10);
	spi_trans(0xff,0);			//��а�ۯ��𑗐M����

//DBG_C('r');
	spi_trans(CMD0,0);			//CMD0�𑗐M����
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(CMD0CRC,0);
	res=mmsd_resp();			//ڽ��ݽ�𓾂�
//DBG_B(res);
	if(res&0x80) return(0x11);		//ڽ��ݽ��MSB��1�̂Ƃ�����ѱ�Ă�Ԃ�
	if(res!=0x01) return(0x12);		//����قłȂ�������װ��Ԃ�

	//�������̊�����҂�
//DBG_C('i');
	do
	{
		spi_trans(0xff,0);		//��а�]�����Ȃ���CMD1��0x05�ɂȂ�
		spi_trans(CMD1,0);		//CMD1�𑗐M����
		spi_trans(0,0);
		spi_trans(0,0);
		spi_trans(0,0);
		spi_trans(0,0);
		spi_trans(1,0);
		res=mmsd_resp();		//ڽ��ݽ�𓾂�
//DBG_B(res);
		if(res&0x80) return(0x13);	//ڽ��ݽ��MSB��1�̂Ƃ�����ѱ�Ă�Ԃ�
	}
	while(res==0x01);			//����ق̂Ƃ��͌J�Ԃ�
	if(res) return(0x14);			//ڽ��ݽ��0�łȂ�������װ��Ԃ�

	//��ۯ���(512[�޲�]�ݒ�)�𑗐M����
//DBG_C('l');
	
	spi_trans(0xff,0);			//��а�]�����Ȃ���CMD16��0x01�ɂȂ�
	spi_trans(CMD16,0);			//CMD16�𑗐M����
	spi_trans(0,0);
	spi_trans(0,0);
	spi_trans(2,0);
	spi_trans(0,0);
	spi_trans(1,0);
	res=mmsd_resp();			//ڽ��ݽ�𓾂�
//DBG_B(res);
	if(res&0x80) return(0x15);		//ڽ��ݽ��MSB��1�̂Ƃ�����ѱ�Ă�Ԃ�
	if(res) return(0x16);			//ڽ��ݽ��0�łȂ�������װ��Ԃ�
	return(0);
}


//==============================================
//SD�Ǎ��݊J�n
//==============================================
static void mmsd_read(void)
{

	//��ި����
//DBG_C('\n');
//DBG_C('r');
//DBG_L(voiceC.begin);
	do
	{
		while(spi_trans(0xff,0)!=0xff){};
						//0xff���Ԃ�܂���а�ް��𑗂�

	//�ݸ����ۯ�ذ�ސݒ�
//DBG_C('b');
		spi_trans(CMD17,0);		//CMD17�𑗐M����
		spi_trans(voiceC.begin>>16,0);	//SD���ނ̱��ڽ(MSB)
		spi_trans(voiceC.begin>>8,0);	//SD���ނ̱��ڽ
		spi_trans(voiceC.begin,0);	//SD���ނ̱��ڽ
		spi_trans(0,0);			//SD���ނ̱��ڽ(LSB)
		spi_trans(1,0);			//CRC
	}
	while(mmsd_resp());			//ڽ��ݽ��0�ɂȂ�܂ŌJ�Ԃ�

	//�ް�İ�݊J�n�҂�
//DBG_C('t');
	while(spi_trans(0xff,0)!=0xfe){};	//�ް���M�J�n�܂ŌJ�Ԃ�
//DBG_C('o');
}


//==============================================
//����C�I������(API�֐�)
//==============================================
static void VOICEC_SEL(				//�߂�l����
	unsigned short no)			//�����ԍ�(0�͍Đ����~)
{

//DBG_C('\n');
//DBG_C('s');
//DBG_S(no);
//DBG_D(voiceC_idx,40);
//DBG_C('i');
	if(no)					//�Đ��J�n�̂Ƃ�
	{
		if(no>sizeof(voiceC_idx)/sizeof(voiceC_idx[0])) return;
						//�������𒴂��Ă���Ƃ��͖߂�
		if(voiceC.no!=no)		//�������̉����ԍ��ƈقȂ�Ƃ��̂�
						//�@������؂�ւ���
		{
			voiceC.no=no--;		//�����ԍ���ݒ�
			voiceC.begin=voiceC_idx[no].adr;
						//�����ް��̊J�n���ڽ��ݒ�
//DBG_L(voiceC.begin);
			voiceC.end=voiceC.begin+voiceC_idx[no].len*2;
						//�����ް��̏I�����ڽ��ݒ�
//DBG_L(voiceC.end);
			voiceC.psn=voiceC_idx[no].psn;
						//�Đ�������ؽ��ْl��ݒ�
//DBG_B(voiceC.psn);
			voiceC.pcm=0;		//PCM�l��������
//DBG_B(voiceC.pcm);
			voiceC.bct=0;		//��ۯ����޲ı��ڽ��������
//DBG_S(voiceC.bct);
		}
	}
	else					//�Đ����f�̂Ƃ�
	{
		if(voiceC.no)			//�Đ����������Ƃ�
		{
			voiceC.begin=voiceC.end-2;
						//�ŏI�߰�ނɂ��Ă���
			voiceC.no=0xffff;	//�Đ��I�����ɂ���
		}
	}
//DBG_D(&voiceC,sizeof(voiceC));
}


//==============================================
//����C�Đ�����
//==============================================
static void voiceC_exe(void)
{
//	short pcm;

//DBG_C('\n');
//DBG_C('p');
//DBG_S(voiceC.bct);
	if(!(voiceC.bct++))			//�߰�ސ擪�̂Ƃ�
	{
//DBG_C('r');
		mmsd_read();			//SD�Ǎ��݊J�n��ݒ肷��
	}
	voiceC.pcm=(short)spi_trans(0xff,0)-128;//�����ް�����o���Ĥ
						//�@8�ޯ�PCM�`����signed�ɕϊ�
//DBG_S(voiceC.pcm);
	voiceC.pcm=(long)voiceC.pcm*((long)VOICEC_VOL*PWM_STEP/100)/128;
						//���ʔz�����|����
//DBG_S(voiceC.pcm);
	if(voiceC.bct==512)			//��ۯ��̍Ō�ɂȂ�����
	{
		voiceC.bct=0;			//��ۯ����޲ı��ڽ��ر����
		if((voiceC.begin+=2)==voiceC.end)
						//�����ް��̍Ō�ɂȂ�����
		{
//DBG_C('e');
//DBG_S(voiceC.no);
			if(voiceC.no!=0xffff)
			{
				voiceC.no=0;	//�Đ��I���ɂ���
				CB_VOICEC_END();//�����Đ��I������(����ޯ��֐�)���ďo��
			}
			voiceC.no=0;		//�Đ��I���ɂ���
		}
	}
}
#endif


#if VOICE_S>0				//SPI��؂��g���Ƃ�
//==============================================
//W25����ܰ�޳�(API�֐�)
//==============================================
static void W25_PWR_DOWN(void)
{

	voiceS.no=0;				//�����Đ��I���ɂ���
	spi_reset();				//SPI��ؾ�Ă���
	SPI_SS_L;				//���߾ڸ�
#ifdef SPI2				//2��SPI�̂Ƃ�
	spi_trans(W25_PwrDwn,1);		//��ܰ�޳ݺ����
#else					//2��SPI�łȂ��Ƃ�
	spi_trans(W25_PwrDwn,0);		//��ܰ�޳ݺ����
#endif
	spi_reset();				//SPI��ؾ�Ă���
}


//==============================================
//W25����ܰ����(API�֐�)
//==============================================
static void W25_PWR_UP(void)
{

	spi_reset();				//SPI��ؾ�Ă���
	wait_us(10);
	SPI_SS_L;				//���߾ڸ�
#ifdef SPI2				//2��SPI�̂Ƃ�
	spi_trans(W25_Re_PwrDwn,1);		//��ܰ�޳݉��������
#else					//2��SPI�łȂ��Ƃ�
	spi_trans(W25_Re_PwrDwn,0);		//��ܰ�޳݉��������
#endif
	spi_reset();				//SPI��ؾ�Ă���
}


//==============================================
//����S�I������(API�֐�)
//==============================================
static void VOICES_SEL(				//�߂�l����
	unsigned short no)			//�����ԍ�(0�͍Đ����~)
{

//DBG_C('\n');
//DBG_C('s');
//DBG_S(no);
//DBG_C('i');
	if(no)					//�Đ��J�n�̂Ƃ�
	{
		if(no>sizeof(voiceS_idx)/sizeof(voiceS_idx[0])) return;
						//�������𒴂��Ă���Ƃ��͖߂�
		if(voiceS.no!=no)		//�������̉����ԍ��ƈقȂ�Ƃ��̂�
						//�@������؂�ւ���
		{
			voiceS.no=no--;		//�����ԍ���ݒ�
			voiceS.begin=voiceS_idx[no].adr;
						//�����ް��̊J�n���ڽ��ݒ�
//DBG_L(voiceS.begin);
			voiceS.end=voiceS.begin+voiceS_idx[no].len;
						//�����ް��̏I�����ڽ��ݒ�
//DBG_L(voiceS.end);
			voiceS.ps=voiceS.psn=voiceS_idx[no].psn;
						//�Đ�������ؽ��ْl��ݒ�
//DBG_B(voiceS.psn);
			voiceS.pcm=0;		//PCM�l��������
//DBG_S(voiceS.pcm);
			spi_reset();		//SPI��ؾ�Ă���
			SPI_SS_L;		//���߾ڸ�
			spi_trans(W25_ReadData,0);
						//ReadData�����
			spi_trans(voiceS.begin>>16,0);
						//���ڽ(MSB)
			spi_trans(voiceS.begin>>8,0);
						//���ڽ
			spi_trans(voiceS.begin,0);
						//���ڽ(LSB)
		}
	}
	else					//�Đ����f�̂Ƃ�
	{
		voiceS.no=0;			//�Đ��I���ɂ���
		spi_reset();			//SPI��ؾ�Ă���
	}
//DBG_D(&voiceS,sizeof(voiceS));
}


//==============================================
//����S�Đ�����
//==============================================
static void voiceS_exe(void)
{

//DBG_C('\n');
//DBG_C('p');
	voiceS.pcm=(short)spi_trans(0,0)-128;	//�����ް�����o���Ĥ
						//�@8�ޯ�PCM�`����signed�ɕϊ�
//DBG_S(voiceS.pcm);
	voiceS.pcm=(long)voiceS.pcm*((long)VOICES_VOL*PWM_STEP/100)/128;
						//���ʔz�����|����
//DBG_S(voiceS.pcm);
	if(++voiceS.begin==voiceS.end)		//�����ް����Ō�̂Ƃ�
	{
//DBG_C('e');
		voiceS.no=0;			//�Đ��I���ɂ���
		spi_reset();			//SPI��ؾ�Ă���
		CB_VOICES_END();		//�����Đ��I������(����ޯ��֐�)���ďo��
	}
}
#endif


//==============================================
//�ޯ̧�֋l�߂�
//�ޯ̧�ق̏ꍇ�͑ҍ�����
//==============================================
static void put_buf(
	short pcm)				//PCM�ް�
{
	unsigned char n;

//DBG_C('\n');
//DBG_C('-');
//DBG_S(pcm);
	n=buf_write;				//�������߲�����擾����
	if(++n==OUT_BUF_N) n=0;			//�����݈ʒu�����ɐi�߂�
//DBS_H;
	while(n==buf_read);			//�ޯ̧���󂭂̂�҂�
//DBS_L;
	buf[buf_write]=pcm;			//�ް����ޯ̧�ɏ�����
	buf_write=n;				//�������߲�����X�V����
}


//==============================================
//Ҳݏ���
//==============================================
int main(void)
{
#if VOICE_C>0					//SD���g���Ƃ�
	unsigned char n;
#endif

	wait_ms(10);				//�d�����莞��
	CB_INIT();				//���޲��̏����ݒ�

#if VOICE_C>0					//SD���g���Ƃ�
//DBG_C('+');
	do
	{
		n=mmsd_init();			//SDC������������
//DBG_B(n);
	}
	while(n);
#endif


//==============================================
//Ҳ�ٰ��
//==============================================
	while(1)
	{
//DBG_C('\n');
//DBG_C('m');


//==============================================
//�ŗL����
//==============================================
//DBG_C('k');
//DBG_S(kyotuu.ps);
		if(!(kyotuu.ps--))		//�ŗL���������ݸނɂȂ�����
		{
			kyotuu.ps=(unsigned long)KOYUU_PR*1000/PWM_PR-1;
						//�ŗL������ؽ��ׂ�������
			CB_KOYUU();		//�ŗL����(����ޯ��֐�)���ďo��
		}


//==============================================
//�o�͎��O����
//==============================================
		kyotuu.pcm=0;			//PCM���Z�l��ر���Ă���


#if PART_N>0
//==============================================
//�ٺްى��t����
//==============================================
//DBG_C('o');
		if(song.no)			//���t���̂Ƃ�
		{
//DBG_C('\n');
//DBG_B(song.song_ps);
			if(!(song.song_ps--))	//���t���������ݸނɂȂ�����
			{
				song.song_ps=SONG_PS-1;
						//���t������ؽ��ׂ�������
				song_exe();	//���t���������s����
			}
			kyotuu.pcm+=song.pcm;	//PCM�l�𔽉f����
		}
#endif


#if VOICE_N>0
//DBG_C('n');
//==============================================
//����0�Đ�����
//==============================================
		if(voiceN[0].no)		//�Đ����̂Ƃ�
		{
			if(!(voiceN[0].ps--))	//�Đ����������ݸނɂȂ�����
			{
				voiceN[0].ps=voiceN[0].psn-1;
						//���t������ؽ��ׂ�������
				voiceN_exe(0);	//���t���������s����
			}
			kyotuu.pcm+=voiceN[0].pcm;
						//PCM�l�𔽉f����
		}
#endif


#if VOICE_N>1
//==============================================
//����1�Đ�����
//==============================================
		if(voiceN[1].no)		//�Đ����̂Ƃ�
		{
			if(!(voiceN[1].ps--))	//�Đ����������ݸނɂȂ�����
			{
				voiceN[1].ps=voiceN[1].psn-1;
						//���t������ؽ��ׂ�������
				voiceN_exe(1);	//���t���������s����
			}
			kyotuu.pcm+=voiceN[1].pcm;
						//PCM�l�𔽉f����
		}
#endif


#if VOICE_N>2
//==============================================
//����2�Đ�����
//==============================================
		if(voiceN[2].no)		//�Đ����̂Ƃ�
		{
			if(!(voiceN[2].ps--))	//�Đ����������ݸނɂȂ�����
			{
				voiceN[2].ps=voiceN[2].psn-1;
						//���t������ؽ��ׂ�������
				voiceN_exe(2);	//���t���������s����
			}
			kyotuu.pcm+=voiceN[2].pcm;
						//PCM�l�𔽉f����
		}
#endif


#if VOICE_I>0
//==============================================
//����I�Đ�����
//==============================================
//DBG_C('i');
		if(voiceI.no)			//�Đ����̂Ƃ�
		{
			if(!(voiceI.ps--))	//�Đ����������ݸނɂȂ�����
			{
				voiceI.ps=voiceI.psn-1;
						//���t������ؽ��ׂ�������
				voiceI_exe();	//���t���������s����
			}
			kyotuu.pcm+=voiceI.pcm;	//PCM�l�𔽉f����
		}
#endif


#if VOICE_C>0
//==============================================
//����C�Đ�����
//==============================================
//DBG_C('c');
		if(voiceC.no)			//�Đ����̂Ƃ�
		{
			if(!(voiceC.ps--))	//�Đ����������ݸނɂȂ�����
			{
				voiceC.ps=voiceC.psn-1;
						//���t������ؽ��ׂ�������
				voiceC_exe();	//���t���������s����
			}
			kyotuu.pcm+=voiceC.pcm;	//PCM�l�𔽉f����
		}
#endif


#if VOICE_S>0
//==============================================
//����S�Đ�����
//==============================================
//DBG_C('s');
		if(voiceS.no)			//�Đ����̂Ƃ�
		{
			if(!(voiceS.ps--))	//�Đ����������ݸނɂȂ�����
			{
				voiceS.ps=voiceS.psn-1;
						//���t������ؽ��ׂ�������
				voiceS_exe();	//���t���������s����
			}
			kyotuu.pcm+=voiceS.pcm;	//PCM�l�𔽉f����
		}
#endif


//==============================================
//�ޯ̧���o��
//==============================================
//DBG_C('b');
//DBG_S(kyotuu.pcm);
		if(kyotuu.pcm>=(PWM_STEP+1)/2) kyotuu.pcm=(PWM_STEP+1)/2-1;
						//�L���Ȕ͈͂ɋK������
		else if(kyotuu.pcm<=-PWM_STEP/2) kyotuu.pcm=-PWM_STEP/2+1;
		put_buf(kyotuu.pcm);		//PCM�`�����ޯ̧�ɏo�͂���
	}
}
