//==============================================
//�������ޯ��(VOICE_N�p)����ϸ�
//�@�����Đ�����������PWM�����ɑ΂�����ؽ��ْl�𐶐�����
//�@�����ް��̱��ڽ����۸�����؂��޲ı��ڽ���w�肷�邱��
//aaa:�����ް��̱��ڽ[�޲�]�bbb:����[�޲�]�sss:�����ݸ�ڰ�[sps]
//==============================================
#define	von_mac(aaa,bbb,sss)	{aaa,bbb,((unsigned long)100000/PWM_PR*100/sss+5)/10},


//==============================================
//�������ޯ��(VOICE_I�p)����ϸ�
//�@�����Đ�����������PWM�����ɑ΂�����ؽ��ْl�𐶐�����
//�@�����ް��̱��ڽ��I2C�ׯ������޲ı��ڽ���w�肷�邱��
//�@�ڰ�ޱ��ڽ��I2C�ڰ�ޱ��ڽ(���۰ٺ���+R�ޯĕt��)(��.0xa0)���w�肷�邱��
//aaa:�����ް��̱��ڽ[�޲�]�bbb:����[�޲�]�sss:�����ݸ�ڰ�[sps]�ccc:�ڰ�ޱ��ڽ
//==============================================
#define	voi_mac(aaa,bbb,sss,ccc)	{aaa,bbb,((unsigned long)100000/PWM_PR*100/sss+5)/10,ccc},


//==============================================
//�������ޯ��(VOICE_C�p)����ϸ�
//�@�����Đ�����������PWM�����ɑ΂�����ؽ��ْl�𐶐�����
//�@�����ް��̱��ڽ��SD���ޏ���߰�ޱ��ڽ���w�肷�邱��
//�@�����ް��̒�����SD���ޏ���߰�ސ����w�肷�邱��
//aaa:�����ް��̱��ڽ[�߰��]�bbb:����[�߰��]�sss:�����ݸ�ڰ�[sps]
//==============================================
#define	voc_mac(aaa,ppp,sss)	{aaa,ppp,((unsigned long)100000/PWM_PR*100/sss+5)/10},


//==============================================
//�������ޯ��(VOICE_S�p)����ϸ�
//�@�����Đ�����������PWM�����ɑ΂�����ؽ��ْl�𐶐�����
//�@�����ް��̱��ڽ��SPI�ׯ������޲ı��ڽ���w�肷�邱��
//aaa:�����ް��̱��ڽ[�޲�]�bbb:����[�޲�]�sss:�����ݸ�ڰ�[sps]
//==============================================
#define	vos_mac(aaa,bbb,sss)	{aaa,bbb,((unsigned long)100000/PWM_PR*100/sss+5)/10},


//==============================================
//�����g�`�ް��̘g�g��(wave_�ɓK�p����)
//==============================================
struct WAVE_HDR					//�����g�`�ް���ͯ��
{
	unsigned char data[256];		//�g�`�ް�(�v�f����256�Œ�)
};


//==============================================
//����۰�ߔg�`�ް��̘g�g��(enve_�ɓK�p����)
//==============================================
struct ENVE_HDR					//����۰�ߔg�`�ް���ͯ��
{
	unsigned char smp;			//�g�`�ް�����ِ�-1
	unsigned char data[1];			//�g�`�ް�(�v�f����smp+1)
};


//==============================================
//�߯�����ޔg�`�ް��̘g�g��(pitch_�ɓK�p����)
//==============================================
struct PITCH_HDR				//�߯�����ޔg�`�ް���ͯ��
{
	unsigned char smp;			//�g�`�ް�����ِ�-1
	unsigned char data[1];			//�g�`�ް�(�v�f����smp+1)
};


//==============================================
//�Ȳ��ޯ���̘g�g��
//==============================================
struct SONG_IDX
{
	unsigned char no;			//�Ȑ�
	unsigned char dmy;
	struct SONG_HDR *song_hdr[1];		//��ͯ�ނւ��߲��
};


//==============================================
//���߰Ă̘g�g��
//==============================================
struct SONG_PART				//�߰ď��
{
	unsigned short onpu;			//�����ް��ւ��߲��
	unsigned short ongen;			//�����ް��ւ��߲��
	unsigned short enve_psn;		//����۰�ߏ�����ؽ��ْl
	unsigned short enve;			//����۰�ߔg�`ͯ�ނւ��߲��
	unsigned short pitch_psn;		//�߯�����ޏ�����ؽ��ْl
	unsigned short pitch;			//�߯�����ޔg�`ͯ�ނւ��߲��
};


//==============================================
//��ͯ�ނ̘g�g��
//==============================================
struct SONG_HDR					//��ͯ��
{
	unsigned short next;			//���̋�ͯ�ނւ��߲��
						//�@�P�Ȃł�NULL
	unsigned short onka_psn;		//������ؽ��ْl
	char key;				//�ڒ��x
	unsigned char part_su;			//�����߰Đ�
	struct SONG_PART part[1];		//�߰ď��
};


//==============================================
//����Nͯ�ނ̘g�g��
//==============================================
struct VOICEN_HDR
{
	const unsigned char *adr;		//�����ް��̱��ڽ[�޲�]
	unsigned short len;			//�����ް��̒���[�޲�]
	unsigned char psn;			//�Đ�������ؽ��ْl
};


//==============================================
//����Iͯ�ނ̘g�g��
//==============================================
struct VOICEI_HDR
{
	unsigned short adr;			//�����ް��̱��ڽ[�޲�]
	unsigned short len;			//�����ް��̒���[�޲�]
	unsigned char psn;			//�Đ�������ؽ��ْl
	unsigned char sla;			//I2C�ڰ�ޱ��ڽ
};


//==============================================
//����Cͯ�ނ̘g�g��
//==============================================
struct VOICEC_HDR
{
	unsigned long adr;			//�����ް����߰�ޱ��ڽ
	unsigned long len;			//�����ް����߰�ސ�
	unsigned char psn;			//�Đ�������ؽ��ْl
};


//==============================================
//����Sͯ�ނ̘g�g��
//==============================================
struct VOICES_HDR
{
	unsigned long adr;			//�����ް��̱��ڽ[�޲�]
	unsigned long len;			//�����ް��̒���[�޲�]
	unsigned char psn;			//�Đ�������ؽ��ْl
};


//==============================================
//���ʐ���ð��ق̘g�g��
//==============================================
struct KYOTUU					//���ʐ���ð���
{
	unsigned short ps;			//�ŗL��������ޯ�������ؽ���
	short pcm;				//�o��PCM�l
};


//==============================================
//���t����ð��ق̘g�g��
//==============================================
struct SONG					//���t����ð���
{
	const struct SONG_HDR *song_hdr;	//��ͯ�ނւ��߲��
	unsigned short onka_psn;		//������ؽ��ْl(�����l�Ϳݸ�ͯ�ނ���ݒ�)
	unsigned short onka_ps;			//������ؽ���
	short pcm;				//�S�߰ĕ���PCM�l
	unsigned char no;			//�Ȕԍ�(1�N�Z�0�͉��t�I��)
	unsigned char part_su;			//�����߰Đ�
	char key;				//���ݒ�l(�����l�Ϳݸ�ͯ�ނ���ݒ�)
	unsigned char song_ps;			//���t��ؽ���
};


//==============================================
//�߰Čʐ���ð��ق̘g�g��
//==============================================
struct PART					//�߰Đ���ð���
{
	const struct SONG_PART *song_part;	//�߰ď��ւ��߲��(NULL�͉��t�I��)
	const unsigned short *onpu;		//�����ް��ւ��߲��
	const struct WAVE_HDR *ongen;		//�����ް��ւ��߲��
	const struct ENVE_HDR *enve;		//����۰�ߔg�`ͯ�ނւ��߲��
	const struct PITCH_HDR *pitch;		//�߯�����ޔg�`ͯ�ނւ��߲��
	unsigned short onpu_cd;			//��������
	unsigned short onpu_kb;			//��������(KB���t�p)
	unsigned short onpu_of;			//����ð��ٵ̾��
						//�@(0xffff�̂Ƃ��ͷ��ް�ޓ���ƂȂ�)
	unsigned short ongen_of;		//�����g�`����ٵ̾��
						//�@[1/256](������8�ޯ�+�[����8�ޯ�)
	unsigned short ongen_tobi;		//�����g�`����ٔ�ѐ�/
						//�@(PWM����*���s��ؽ��ْl)[1/256]
						//�@(������8�ޯ�+�[����8�ޯ�)
	unsigned short port_tobi_gl;		//�����g�`����ٔ�ѐ��ް�/
						//�@(PWM����*���s��ؽ��ْl)[1/256]
						//�@(������8�ޯ�+�[����8�ޯ�)
	unsigned short port_tobi_ps;		//�����g�`����ٔ�ѐ�������/��ؽ���/
						//�@(PWM����*���s��ؽ��ْl)[1/256]
						//�@(������8�ޯ�+�[����8�ޯ�)
	unsigned short velo;			//��ۼè�l
						//�@�����ް��̎w��l��PWM_PR�𔽉f���Đݒ�
						//�@�����ް��ɂ�ORGEL_VOL�����f����Ă���
	unsigned short velo_enve;		//�����-�ߏ������f�����ۼè�l
						//�@PWM_PR�𔽉f����
	unsigned short enve_psn;		//����۰�ߏ������s����ؽ��ْl
						//�@�ݸ�ͯ�ނƉ����ް��̐ς�ݒ�
						//�@(0�̂Ƃ�������װ���t)
	unsigned short enve_ps;			//����۰�ߏ������s����ؽ���
	unsigned short pitch_psn;		//�߯�����ޏ������s����ؽ��ْl
						//�@�ݸ�ͯ�ނƉ����ް��̐ς�ݒ�
						//�@(0�̂Ƃ����߯�����ނ��Ȃ�)
	unsigned short pitch_ps;		//�߯�����ޏ������s����ؽ���
	unsigned char onka_zan;			//�������Ďc
	unsigned char enve_of;			//����۰�ߔg�`����ٵ̾��
	unsigned char pitch_of;			//�߯�����ޔg�`����ٵ̾��
	unsigned char rpt[4];			//��߰Ķ���
};


//==============================================
//����N�Đ�����ð��ق̘g�g��
//==============================================
struct VOICEN					//����N�Đ�����ð���
{
	const unsigned char *begin;		//�����ް��̊J�n���ڽ
	const unsigned char *end;		//�����ް��̏I�����ڽ
	unsigned char no;			//�����ԍ�(0�͍Đ��I��)
	short pcm;				//PCM�l
						//�@PWM_PR�𔽉f����
	unsigned char psn;			//�Đ�������ؽ��ْl
	unsigned char ps;			//�Đ�������ؽ���
};


//==============================================
//����I�Đ�����ð��ق̘g�g��
//==============================================
struct VOICEI					//����I�Đ�����ð���
{
	unsigned short begin;			//�����ް��̊J�n���ڽ
	unsigned short end;			//�����ް��̏I�����ڽ
	unsigned char no;			//�����ԍ�(0�͍Đ��I��)
	short pcm;				//PCM�l
						//�@PWM_PR�𔽉f����
	unsigned char sla;			//I2C�ڰ�ޱ��ڽ
	unsigned char psn;			//�Đ�������ؽ��ْl
	unsigned char ps;			//�Đ�������ؽ���
};


//==============================================
//����C�Đ�����ð��ق̘g�g��
//==============================================
struct VOICEC					//����C�Đ�����ð���
{
	unsigned long begin;			//�����ް��̊J�n�߰�ޱ��ڽ(1�߰�ނ�256�޲�)
	unsigned long end;			//�����ް��̏I�����ڽ(1�߰�ނ�256�޲�)
	unsigned short no;			//�����ԍ�(0�͍Đ��I��)
	short pcm;				//PCM�l
						//�@PWM_PR�𔽉f����
	unsigned short bct;			//��ۯ����޲ı��ڽ(1��ۯ���512�޲�)
	unsigned char psn;			//�Đ�������ؽ��ْl
	unsigned char ps;			//�Đ�������ؽ���
};


//==============================================
//����S�Đ�����ð��ق̘g�g��
//==============================================
struct VOICES					//����S�Đ�����ð���
{
	unsigned long begin;			//�����ް��̊J�n���ڽ
	unsigned long end;			//�����ް��̏I�����ڽ
	unsigned short no;			//�����ԍ�(0�͍Đ��I���0xffff�͍Đ��I����)
	short pcm;				//PCM�l
						//�@PWM_PR�𔽉f����
	unsigned char psn;			//�Đ�������ؽ��ْl
	unsigned char ps;			//�Đ�������ؽ���
};


//==============================================
//����ޯ��֐������������ߐ錾
//==============================================
static void CB_INIT(void);			//�ŗL�̏����ݒ�
static void CB_KOYUU(void);			//�ŗL�̏���
#if PART_N>0				//�ٺްى��t����������Ƃ�
static void CB_SONG_END(void);			//���t�I�����̏���
#endif
#if VOICE_N>0				//����N�Đ�����������Ƃ�
static void CB_VOICEN_END(			//����N�Đ��I�����̏���
	unsigned char);				//�@ch�ԍ�
#endif
#if VOICE_I>0				//����I�Đ�����������Ƃ�
static void CB_VOICEI_END(void);		//����I�Đ��I�����̏���
#endif
#if VOICE_C>0				//����C�Đ�����������Ƃ�
static void CB_VOICEC_END(void);		//����C�Đ��I�����̏���
#endif
#if VOICE_S>0				//����S�Đ�����������Ƃ�
static void CB_VOICES_END(void);		//����S�Đ��I�����̏���
#endif
static void apl_init(void);			//���ع���݂̏���������


//==============================================
//W25Q�ذ�ފ֘A�萔
//==============================================
#define	W25_ReadData	0x03			//ReadData�����
#define	W25_PwrDwn	0xb9			//PowerDown�����
#define	W25_Re_PwrDwn	0xab			//ReleasePowerDown�����


//==============================================
//SD���̪���֘A�萔
//==============================================
#define	CMD0		0x40			//ؾ��
#define	CMD0CRC		0x95			//CMD0��CRC
#define	CMD1		0x41			//MMC�����������߰�ݸ�
#define	CMD1CRC		0x87			//CMD1��CRC
#define	CMD8		0x48			//����d���̊m�F��SDC���ް�ޮ�����
#define	CMD12		0x4C			//�ް��Ǎ��݂��~����������
#define	CMD13		0x4D			//�����݂̏�Ԃ�₢���킹������
#define	CMD16		0x50			//��ۯ����ސݒ�
#define	CMD17		0x51			//�ݸ����ۯ��Ǎ��ݗv��
#define	CMD24		0x58			//�ݸ����ۯ������ݗv��
#define	ACMD41		0x69			//SD�̏����������߰�ݸ�
#define	CMD55		0x77			//ACMD41/ACMD23�ƾ�ĂŎg�p��������
#define	CMD58		0x7A			//OCR�̓Ǐo��

