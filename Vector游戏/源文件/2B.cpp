/******����ģ�黯�� ½�Ǵ� ��2019��3Լ18�� ʵ��*******/
#include "NieR.h"

extern struct prop Pprop, Cprop;
extern struct ifget ifopen;
extern struct setprop isset;

MOUSEMSG KaiShi;			//����������
MOUSEMSG XuanZeDiTu1;
MOUSEMSG ZanTingCaiDan;
MOUSEMSG help;
MOUSEMSG Jinggao;
MOUSEMSG Shengli;

int gid = 0;				//���˵�ѡ�����
int map = 0;				//ͼƬѡ����

int Cspeed = 0;				// �ٶ�CspeedΪ���2��PspeedΪ���1
int Pspeed = 0;
double PForward = 0;		// ����
double CForward = 0;
double PForward0 = 0;		//���µı����洢�Ƕȣ�ʵ����ײʱ����ͼ��ĺ���
double CForward0 = 0;
double Mx1, My1;			//ʵʱλ�ø���
double Mx2, My2;
int Px, Py;					//��ʼλ��
int Cx = 120, Cy = 100;
int Rota = 23;				// ת���ٶȵ� -1 �η������ڵ���С��ת���ٶ�
int MaxSpeed = 14;			//����ٶ�
int SpeedAdd = 2;			// ���ٶ�
int SpeedChange = 0;		//��ͬ���ε�Ħ����
int Finroad = 1;
int Finsand = 3;
int player = 1;				//�ж���Ϸģʽ
bool flag = 0;				//С����ײ��־
int mapo = 0;
float Time;					//ָʾ��ʱ
clock_t Menutime;
clock_t PauseTime = 0;
char t[50] = { 0 };					//��ʱ���ı�
int R;

//�ж�С��λ��
bool inRoad;
bool inSand;
bool inWall;
bool inSline1 = false;		//�ж��Ƿ�λ�����
bool inSline2 = false;		//�ж��Ƿ񳭽�·
bool inBoost;
bool Birth1 = true;
bool Birth2 = false;
bool is_paused = false;

char Name1[50] = "Player1";
char Name2[50] = "Player2";
char Name3[50] = "Player3";
char Name4[50] = "Player4";
char Name5[50] = "Player5";

float lap1 = 28.00;
float lap2 = 30.00;
float lap3 = 32.00;
float lap4 = 34.00;
float lap5 = 36.00;

char Lap1[50] = { 0 };
char Lap2[50] = { 0 };
char Lap3[50] = { 0 };
char Lap4[50] = { 0 };
char Lap5[50] = { 0 };

FILE *Rank1 = NULL;
FILE *Rank2 = NULL;
FILE *Rank3 = NULL;
FILE *Rank4 = NULL;
FILE *Rank5 = NULL;

clock_t Start = 0;			//����ʱ��ı�������
clock_t Now = 0;
clock_t Pause = 0;
clock_t Restart = 0;
clock_t MeumUsed = 0;

IMAGE Menu;					//���ͼ����
IMAGE car1, car2;
IMAGE Player1, Player2;
IMAGE Racing;
IMAGE pengzhuang;
IMAGE SaiDaoXuanZe;
IMAGE zanting;
IMAGE Help;
IMAGE JingGao;
IMAGE flash;
IMAGE attack;
IMAGE magnet;
IMAGE energy;
IMAGE Victory1;
IMAGE LIST1, LIST2;
IMAGE Fail1;
IMAGE Fail2;

/**************�� ������ ��2019��3��13�ձ�д   ��2019��3��17�� ��Ӽ�ʱ��****/
void PauseMenu()
{
	mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
	mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
	mciSendString(_TEXT("stop music3"), NULL, 0, NULL);
	cleardevice();
	int flag;//����ֲ���־����
	Pause =clock();//ȡ�ô�ʱ����Ϸʱ��
	BeginBatchDraw();
	while (true)
	{
		putimage(0, 0, &zanting);//���ر���ͼ�������黯��
		FlushBatchDraw();
		FlushMouseMsgBuffer();  //�����껺��
		ZanTingCaiDan = GetMouseMsg();
		if (ZanTingCaiDan.mkLButton)
		{
			if (MouseTouch2(500, 280, 770, 350, ZanTingCaiDan))
			{
				flag = 1;
				Restart = clock();//ȡ�ð��¡�������Ϸ����ťʱ��ʱ��
				Menutime = Restart - Pause;//���ʱ���
				break;
			}
			if (MouseTouch2(470, 460, 810, 530, ZanTingCaiDan))
			{
				flag = 2;
				Init();
				MoShi();
				break;
			}
			EndBatchDraw();
		}
	}
}

//��ʱ������
/*****************************�� ����� �����˺ܾ�************************************/
/*****************************�� ������ �����˰���************************************/
/***********�� ������ ��3��13�ո���(��ֻ�ǰѺ����Ϲ����ˣ�Ȼ��Ͳ�����)  ��3��17��ʵ����������***************/
void time()
{
	BeginBatchDraw();
	Now = clock();
	if (is_paused)
	{	
		PauseTime = PauseTime + Menutime;//��ͣʱ���ۼ�
		Pause = 0;
		Restart = 0;
		is_paused = false;
	}
	Time =((double)(Now-Start-PauseTime)) / CLOCKS_PER_SEC;//clock()��õ��Ǵӳ���ʼ����������CPUʱ�䣬��˷ֱ�����start, now, pause, restart����������ȡʱ�䣬Ȼ�������Ϸʱ�䡣
	outtextxy(1100, 50, ("��ǰ��ʱ��"));
	sprintf_s(t, "%.3f s\n", Time);
	outtextxy(1170, 50,t);
	FlushBatchDraw();
	//EndBatchDraw();
}


//�淨����
/**********������ 3��16�� �༭ ���ͼ��Ͱ�ť************/
void ShowHelp()
{
	putimage(0, 0, &Help);
	while (true)
	{
		
		FlushMouseMsgBuffer();
		help = GetMouseMsg();
		if (help.mkLButton)
		{
			if (MouseTouch2(1100, 670, 1230, 700, help))
			{
				Init();
				MoShi();
			}
		}
	}
	return;
}

/********�� ��˼�� ������ ��3��13�� ��д  ���ͼƬ����ť********/
//��ͬģʽ�µ�ͼƬѡ��
void ChooseMap()
{
	//cleardevice();
	if (!player)
	{
		loadimage(&SaiDaoXuanZe, _T("�ļ�\\ѡ������ 1.jpg"));
		BeginBatchDraw();
		while (true)
		{
			putimage(0, 0, &SaiDaoXuanZe);
			FlushBatchDraw();
			FlushMouseMsgBuffer();
			XuanZeDiTu1 = GetMouseMsg();
			if (XuanZeDiTu1.mkLButton)
			{
				if (MouseTouch2(353, 232, 927, 360, XuanZeDiTu1))
				{
					loadimage(&Racing, _T("�ļ�\\��������1\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("�ļ�\\��������1\\pengzhuang.gif"));
					loadimage(&zanting, _T("�ļ�\\��������1\\zanting.jpg"));
					loadimage(&JingGao, _T("�ļ�\\��������1\\jinggao.jpg"));
					map = 1;
					ReadAll1();
					return;
				}
				if (MouseTouch2(353, 422, 927, 548, XuanZeDiTu1))
				{
					loadimage(&Racing, _T("�ļ�\\��������2\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("�ļ�\\��������2\\pengzhuang.gif"));
					loadimage(&zanting, _T("�ļ�\\��������2\\zanting.jpg"));
					loadimage(&JingGao, _T("�ļ�\\��������2\\jinggao.jpg"));
					map = 2;
					ReadAll2();
					return;
				}
				if (MouseTouch2(1100, 670, 1230, 700, XuanZeDiTu1))
				{
					Init();
					MoShi();
				}
			}
		}
		EndBatchDraw();
	}
	else
	{
		loadimage(&SaiDaoXuanZe, _T("�ļ�\\ѡ������ 2.jpg"), WIDE, HEIGHT);
		BeginBatchDraw();
		while (true)
		{
			putimage(0, 0, &SaiDaoXuanZe);
			FlushBatchDraw();
			FlushMouseMsgBuffer();
			XuanZeDiTu1 = GetMouseMsg();
			if (XuanZeDiTu1.mkLButton)
			{
				if (MouseTouch2(353, 232, 927, 360, XuanZeDiTu1))
				{
					loadimage(&Racing, _T("�ļ�\\˫������1\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("�ļ�\\˫������1\\pengzhuang.gif"));
					loadimage(&zanting, _T("�ļ�\\˫������1\\zanting.jpg"));
					map = 1;
					return;
				}
				if (MouseTouch2(353, 422, 927, 548, XuanZeDiTu1))
				{
					loadimage(&Racing, _T("�ļ�\\˫������2\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("�ļ�\\˫������2\\pengzhuang.gif"));
					loadimage(&zanting, _T("�ļ�\\˫������2\\zanting.jpg"));
					map = 2;
					return;
				}
				if (MouseTouch2(1100, 670, 1230, 700, XuanZeDiTu1))
				{
					Init();
					MoShi();
				}
			}
		}
		EndBatchDraw();
	}
}

/***�� ½�Ǵ� ��2019��3��2�� ��д ���ڼ�������λ��*/
//���ڻ�֪С������λ�õ���������λ��
int PointTsm(int x, int y, int wide, int high)
{
	if (x < 0)return x = 0;
	if (x >= wide)return x = wide;
	if (y < 0)return y = 0;
	if (y >= high)return y = high;

	return wide * y + x;
}

/*******************�� ������ ��2019��3��3�ձ༭ ���ڼ����굥������************/
bool MouseTouch2(int left, int top, int right, int buttom, MOUSEMSG m)
{
	if (m.x > left&&m.x<right&&m.y>top&&m.y < buttom)
		return true;
	else
		return false;
}

/*******************�� ����� ��2019��3 ��13�ձ༭*******/
void Victory()
{
	//loadimage(&Victory1, _T("�ļ�\\Vicyory.jpg"));//����ʤ��ͼƬ
	mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
	mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
	mciSendString(_TEXT("stop music3"), NULL, 0, NULL);
	if (map == 1)
	{
		ReadAll1();
	}
	if (map == 2)
	{
		ReadAll2();
	}
	R = Rank(Time);
	BeginBatchDraw();//������Ϸ����Ļ���
	while (true)
	{
		putimage(0, 0, &Victory1);
		FlushBatchDraw();
		FlushMouseMsgBuffer();  //�����껺��
		Shengli = GetMouseMsg();
		//��������˶�ʱ����
		if (Shengli.mkLButton)
		{
			if (gid == 1)
			{
				if (MouseTouch2(1089, 605, 1234, 652, Shengli))//ȱ��Ȧ�ٰ���ʾ
				{
					if (R)
					{
						LapChange1(R);
						LapShow(R);
					}
					else if (R == 0)
					{
						Sorry();
					}
				}
			}
				if (MouseTouch2(1089, 655, 1234, 702, Shengli))
				{
					Init();
					MoShi();							//�˳���ť
				}
		}
	}
	EndBatchDraw();
}

/**************************�� ½�Ǵ� ��3��2�ո���*****************************/
//������ĳ�ʼ������
//��ȡͼ�����ɳ�ʼ�����棬������ģʽѡ��		
void Init()
{
	loadimage(&flash, _T("�ļ�\\����\\flash.bmp"));
	loadimage(&attack, _T("�ļ�\\����\\attack.bmp"));
	loadimage(&magnet, _T("�ļ�\\����\\magnet.bmp"));
	loadimage(&energy, _T("�ļ�\\����\\energy.bmp"));
	loadimage(&Menu, _T("�ļ�\\menu.jpg"));					//ʹ�����λ�ü����й�ͼ��
	loadimage(&car1, _T("�ļ�\\car.gif"));					
	loadimage(&car2, _T("�ļ�\\car2.gif"));			
	loadimage(&Help, _T("�ļ�\\help.jpg"));
	loadimage(&LIST1, _T("�ļ�\\Ȧ�ٰ�1.jpg"));
	loadimage(&LIST2, _T("�ļ�\\Ȧ�ٰ�2.jpg"));
	Player1=car1;											//Ԥ��һ��һ����ͼ�Σ��Ա��ں���rotateimage�ĺ�����ʹ��
	initgraph(WIDE, HEIGHT);
	player = 0;
	gid = 0;

	ReadAll1();												//����Ȧ�ٰ�
	PlaySound(TEXT("�ļ�\\����.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC | SND_NOSTOP);
	//ģʽ��ѡ��
	BeginBatchDraw();
	while (true)
	{
		putimage(0, 0, &Menu);
		FlushBatchDraw();
		EndBatchDraw();
		FlushMouseMsgBuffer();								//�����껺��
		KaiShi = GetMouseMsg();								//��ȡ�����Ϣ
		if (KaiShi.mkLButton)
		{
			if (MouseTouch1(200, 100, 130, 210, KaiShi))
			{
				gid = 1;									//����ģʽ
				break;
			}
			if (MouseTouch1(400, 300, 130, 210, KaiShi))
			{
				gid = 2;									//˫��ģʽ
				break;
			}
			if (MouseTouch2(1230, 480 ,1260, 610, KaiShi))
			{
				gid = 3;									//�����˵�
				break;
			}
			if (MouseTouch2(1089, 655, 1234, 702, KaiShi))
			{
				gid = 4;									//�˳���ť
				break;										
			}
		}
	}
}

/************************�� ½�Ǵ� ��3��2�ո���************************/
/***************�� ������ ��2019��3��13�ո��� ���ģ�黯�̶� ��ģʽѡ�������MoShi()����**********/
//������		
int main()
{
	Init();											//������Ϸʱ�Ŀ�ʼ����
	//cleardevice();//����
	MoShi();
	closegraph();
}


void MoShi()
{
	if (gid == 1)
	{
		player = 0;									//ʹ��player������ǵ�˫��ģʽ
		gaming(player);
	}
	if (gid == 2)
	{
		player = 1;
		Px = 200; Py = 360;
		Cx = 1080; Cy = 360;
		gaming(player);
	}
	if (gid == 3)
	{
		ShowHelp();
	}
	if (gid == 4)
	{
		closegraph();
	}
}