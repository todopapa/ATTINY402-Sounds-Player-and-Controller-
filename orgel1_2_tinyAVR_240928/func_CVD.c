//CVD��]������@�\Ӽޭ��
//
//CVD�������ٱ��߂���ƌ��m���x���Ⴂ�̂Ť100k���O����ٱ��߂𐄏�����
//���̏ꍇ�� CVD_EXPU ��錾����
//
//CVD�̍\�������L�̗�ɕ���Ĥ�ďo�����ɂĒ�`���Ă������ơ
//
//CVD�͕����������\�CVD�����߰�ڼ޽�������Ă��悢�
//
//CVD�̵݂Ƃͤ���������ԡ
//CVD�̵̂Ƃͤ������Ȃ���ԡ
//
//CVD�̕]���͈ȉ���2��Ӱ�ނ�����
//�Eر�Ӱ��
//�@�K����ԓ������·�͖�������
//�@��Ԃ��ω������Ƃ��ɕω��̏󋵂�Ԃ��
//�@�߂�l�ͤ0=�ω��̌��m�Ȃ��1=�̂���݂ւ̕ω������m�2=�݂���̂ւ̕ω������m�
//�E��ϰӰ��
//�@�݂̌p�����Ԃ��Z��臒l�ɂȂ�����Z�݈�v�Ƃ���
//�@�݂̌p�����Ԃ�����臒l�ɂȂ����璷�݈�v�Ƃ���
//�@�݂���̂֕ω������Ƃ��ɤ�ݏ�Ԃł��������Ԃ��Z��臒l�����̂Ƃ��͒Z�݌��m�Ƃ���
//�@�߂�l�ͤ0=���m�Ȃ��1=�Z�݌��m�2=���݈�v�3=�Z�݈�v�
//ر�Ӱ�ނ���ϰӰ�ނ͔r���I�Ť1��CVD�ɑ΂��Ăǂ��炩1��Ӱ�ނ��w��ł���
//
//CVD��]������ꍇ�ͤ����Ӽޭ�ق�#include����
//ر�Ӱ�ނŕ]������Ƃ��ͤCVD_REAL��錾����
//��ϰӰ�ނŕ]������Ƃ��ͤCVD_TIMER��錾����
//Sleep�֘A�̏����ɂ���Ӽޭ�ق͊֗^���Ȃ��


//==============================================
//CVD�\���̒�`��
//==============================================
//#define	CVD_REAL			//CVDر�Ӱ�ނ���������Ƃ��ɐ錾����
//#define	CVD_TIMER			//CVD��ϰӰ�ނ���������Ƃ��ɐ錾����

//CVD�̍\��--------------------------------------
//static const struct CVD_CNF
//{
//	PORT_t *port;				//PORT���ڽ
//	unsigned char mode;			//b7:SW��Ӱ��
//						//�@0=ر�Ӱ�ޤ1=��ϰӰ��
//						//b2-0:�ޯĔԍ�
//	unsigned char ain;			//AIN�ԍ�
//} cvd_cnf[]=
//{
//CVD0�̍\��-------------------------------------
//	{GPIOA,0x000000f0,0x02,1,0x80},		//PA1�A1���ϰӰ��
//CVD1�̍\��-------------------------------------
//	{GPIOD,0x0f000000,0x40,6,0x00},		//PD6�A6�ر�Ӱ��
//CVD2�̍\��-------------------------------------
//	{GPIOD,0x00f00000,0x20,5,0x00},		//PD5�A5�ر�Ӱ��
//CVD3�̍\��-------------------------------------
//	{GPIOD,0x000f0000,0x10,7,0x00},		//PD4�A7�ر�Ӱ��
//};

#define	CVD_SU	(sizeof(cvd_cnf)/sizeof(cvd_cnf[0]))
						//CVD�̎�����

//==============================================
//CVD�]����臒l��
//==============================================
#ifdef	CVD_EXPU			//CVD���O����ٱ��߂���Ƃ�
#ifndef	CVD_CNT				//�]���̉񐔐錾����Ă��Ȃ��Ƃ�
#define	CVD_CNT		8			//�@�]���̉񐔂�錾����
#endif
#ifndef	CVD_THR1			//�]����臒l1���錾����Ă��Ȃ��Ƃ�
#define	CVD_THR1	10			//�@臒l1��錾����
#endif
#ifndef	CVD_THR2			//�]����臒l2���錾����Ă��Ȃ��Ƃ�
#define	CVD_THR2	20			//�@臒l2��錾����
#endif
#ifndef	CVD_INC				//�ړ����όv�Z�̑����l���錾����Ă��Ȃ��Ƃ�
#define	CVD_INC		1			//�@�����l��錾����
#endif
#ifndef	CVD_WAIT			//�����ݸޑ҂����Ԃ��錾����Ă��Ȃ��Ƃ�
#define	CVD_WAIT	3	//100k���z��	//�@�����ݸޑ҂����Ԃ�錾����
#endif
#else					//CVD�������ٱ��߂���Ƃ�
#ifndef	CVD_CNT				//�]���̉񐔐錾����Ă��Ȃ��Ƃ�
#define	CVD_CNT		8			//�@�]���̉񐔂�錾����
#endif
#ifndef	CVD_THR1			//�]����臒l1���錾����Ă��Ȃ��Ƃ�
#define	CVD_THR1	10			//�@臒l1��錾����
#endif
#ifndef	CVD_THR2			//�]����臒l2���錾����Ă��Ȃ��Ƃ�
#define	CVD_THR2	20			//�@臒l2��錾����
#endif
#ifndef	CVD_INC				//�ړ����όv�Z�̑����l���錾����Ă��Ȃ��Ƃ�
#define	CVD_INC		3			//�@�����l��錾����
#endif
#ifndef	CVD_WAIT			//A�����ݸޑ҂����Ԃ��錾����Ă��Ȃ��Ƃ�
#define	CVD_WAIT	0			//�@�����ݸޑ҂����Ԃ�錾����
#endif
#endif

//ر�Ӱ�ނ̐ݒ�l
#ifndef	CVD_HST_BIT			//���·��������[�]������](1�`7�͈̔�)��
					//�@�錾����Ă��Ȃ��Ƃ�
#define	CVD_HST_BIT	3			//�@���·�������Ԃ�錾����
#endif
#define	CVD_HST_MSK	((1<<(CVD_HST_BIT+1))-1)//���𔻒��ޯ�Ͻ�
#define	CVD_HST_ON	((1<<CVD_HST_BIT)-1)	//����ݕω�����l
#define	CVD_HST_OFF	((1<<(CVD_HST_BIT+1))-2)//����̕ω�����l

//��ϰӰ�ނ̐ݒ�l
#ifndef	CVD_SHORT			//�Z�ݎ���臒l[ms]���錾����Ă��Ȃ��Ƃ�
#define	CVD_SHORT	100			//��̫�Ēl[ms]��ݒ肷��
#endif
#ifndef	CVD_LONG			//���ݎ���臒l[ms]���錾����Ă��Ȃ��Ƃ�
#define	CVD_LONG	1000			//��̫�Ēl[ms]��ݒ肷��
#endif


//==============================================
//��ƈ�
//==============================================
static struct HIST				//�������
{
	unsigned char cvd_hst;			//CVD�̌�������(�L�^)
						//ر�Ӱ�ނł͵�/�̏�ԗ���(0=�̤1=��)
						//�@b0���ŐV��Ԃŕ]���������ɍ����
						//��ϰӰ�ނł͵ݏ�Ԍo�ߎ���[�]������]
	unsigned short cvd_ave;			//ADC�ړ�����(�L�^)
}cvd_hist[CVD_SU]={0};


//==============================================
//CVD��]������
//���Ұ�:�]���Ώۂ�CVD�ԍ�[0�N�Z]
//�߂�l
//�@ر�Ӱ�ނ̂Ƃ� W:�]������(0=�ω��Ȃ��1=�̂���݂֕ω����m�2=�݂���̂֕ω����m)
//�@��ϰӰ�ނ̂Ƃ� W:�]������(0=���m�Ȃ��1=�Z�݌��m�2=���݌��m)
//==============================================
unsigned char cvd_read(				//����]�����ʂ�Ԃ�
	unsigned char no)			//�]���Ώۂ�CVD�ԍ�(0�N�Z)
{
	unsigned short value;			//CVD��ADC�l
	unsigned char res;			//CVD�]���߂�l
	const struct CVD_CNF *p;		//CVD�\���\�ւ��߲��
	struct HIST *q;				//�������ւ��߲�
	static unsigned char init_tmr;		//��������ϰ
	unsigned char n,m;

	//��퓮��҂�
	if(init_tmr<1500/KOYUU_PR)		//��������ϰ���������̂Ƃ���
	{
		init_tmr++;			//��������ϰ��ݸ؂���
		return(0);			//���������߂�
	}

	//�����ݸޑ҂����Ԑݒ�
	ADC0.CTRLD=CVD_WAIT;			//�����ݸޑ҂�

//DBG_C('\n');
//DBG_C('v');
//DBG_B(no);
	//�\���\�ւ��߲����ݒ�
	if(no>=CVD_SU) return(0);		//�������𒴂��Ă�����߂�
	p=cvd_cnf+no;				//�\���\�̴��؂𓾂�
	m=1<<(p->mode&0x07);			//�ޯ�Ͻ��𓾂�
//DBG_S(p);
//DBG_D(p,12);

	//�������ւ��߲��
	q=cvd_hist+no;				//�������ւ��߲���𓾂�
//DBG_S(q);
//DBG_D(q,4);

	//CVD��ADC
	value=0;
	for(n=0;n<CVD_CNT;n++)
	{
		p->port->OUTCLR=m;		//�߰Ă�L
		p->port->DIRSET=m;		//�߰Ă��o��Ӱ��
		ADC0.MUXPOS=p->ain;		//ADC������݂�ݒ肷��
		cli();				//�����݋֎~
		p->port->DIRCLR=m;		//�߰Ă����Ӱ��
		ADC0.COMMAND=0b00000001;	//�ϊ��J�n
		sei();				//�����݋���
		while(ADC0.COMMAND);		//�ϊ�������҂�
//DBG_C('+');
//DBG_S(0x3ff-ADC0.RES);
		value+=(0x3ff-ADC0.RES);	//�ϊ����ʂ��捞��
	}
//DBG_C('=');
//DBG_S(value);

	//�ړ�����
	if(q->cvd_ave)				//��퓮��̂Ƃ�
	{
		if(value>q->cvd_ave) q->cvd_ave+=CVD_INC;
						//ADC���ʂ��ړ����ς𒴂�����
						//�@�ړ����ς𑝉�������
		else q->cvd_ave=value;		//�����ĂȂ����
						//�@ADC���ʂ��ړ����ςƂ���
	}
	else					//���񓮍�̂Ƃ�
	{
		q->cvd_ave=value;		//�ړ����ς�����������
	}
//DBG_C('-');
//DBG_S(q->cvd_ave);

	//��ϰӰ�ނ̏���
	if(p->mode&0x80)			//��ϰӰ�ނ̂Ƃ�
	{
#ifdef CVD_TIMER			//��ϰӰ�ނ���������Ƃ�
//DBG_C('t');

		//���Ēl�𔻒�
//DBG_B(q->cvd_hst);
		res=0;				//���ɵ̔���ɂ��Ă���
		if(q->cvd_hst)			//�O�񂪵ݔ��肾�����Ƃ�
		{
			if(value>q->cvd_ave+CVD_THR1*CVD_CNT) res=1;
						//���Ēl>(�ړ����ϒl+臒l1)�̂Ƃ��ݔ���
		}
		else				//�O�񂪵̔��肾�����Ƃ�
		{
			if(value>q->cvd_ave+CVD_THR2*CVD_CNT) res=1;
						//���Ēl>(�ړ����ϒl+臒l2)�̂Ƃ��ݔ���
		}
//DBG_B(res);

		//������]��
		if(res)				//�ݔ���̂Ƃ�
		{
//DBG_C('+');
			if((++(q->cvd_hst)==0)) q->cvd_hst--;
						//�݌p�����Ԃ�ݸ؂���
						//�@�����۰������߂�
//DBG_B(q->cvd_hst);
			if(q->cvd_hst==CVD_LONG/KOYUU_PR) res=2;
						//����臒l�Ɉ�v������2���Ԃ�
			else if(q->cvd_hst==CVD_SHORT/KOYUU_PR) res=3;
						//�Z��臒l�Ɉ�v������3���Ԃ�
			else res=0;
		}
		else				//�̔���̂Ƃ�
		{
//DBG_C('-');
//DBG_B(q->cvd_hst);
			if(q->cvd_hst>CVD_LONG/KOYUU_PR) res=0;
						//����臒l�𒴂��Ă�����0���Ԃ�
			else if(q->cvd_hst>CVD_SHORT/KOYUU_PR) res=1;
						//�Z��臒l�𒴂��Ă�����1���Ԃ�
			else res=0;		//���̑��͢0���Ԃ�
			q->cvd_hst=0;		//������ر����
		}

//DBG_B(res);
#else					//��ϰӰ�ނ��������Ȃ��Ƃ�
		return(0);
#endif
	}

	//ر�Ӱ�ނ̏���
	else
	{
#ifdef CVD_REAL				//ر�Ӱ�ނ���������Ƃ�
//DBG_C('r');
		q->cvd_hst<<=1;			//�������Ă��Ă���
//DBG_B(q->cvd_hst);
//DBG_B(value);
		if(q->cvd_hst&0x02)		//�O�񂪵ݔ��肾�����Ƃ�
		{
			if(value>(short)q->cvd_ave+CVD_THR1*CVD_CNT) cvd_hst|=1;
						//���Ēl>(�ړ����ϒl+臒l1)�̂Ƃ��ݔ���
		}
		else				//�O�񂪵̔��肾�����Ƃ�
		{
			if(value>(short)q->cvd_ave+CVD_THR2*CVD_CNT) cvd_hst|=1;
						//���Ēl>(�ړ����ϒl+臒l1)�̂Ƃ��ݔ���
		}
//DBG_B(q->cvd_hst);
		switch(cvd_hst&CVD_HST_MSK)	//�����Ŕ��肷��
		{
		case CVD_HST_ON:		//�ݔ�������݂̂Ƃ���
			res=1;			//�@�1���Ԃ�
			break;
		case CVD_HST_OFF:		//�̔�������݂̂Ƃ���
			res=2;			//�@�2���Ԃ�
			break;
		default:
			res=0;			//���̑��͢0���Ԃ�
		}
//DBG_B(res);
#else					//ر�Ӱ�ނ��������Ȃ��Ƃ�
		return(0);
#endif
	}

//DBG_B(res);
	return(res);				//�]�����ʂ�Ԃ�
}
