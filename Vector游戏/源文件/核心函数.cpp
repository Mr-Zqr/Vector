#include"NieR.h"

/********************************�� ������ ��3��7�ո���********************************/
/***********************�� ������ ��3��10�ո��£�����·���ص����жϣ�******************/
//�ж���������λ�ã�����Ħ����	
/*********������ 3��15�յ����������˲�������ʹ���ܿ����������*************/
void MoveCheck(int Vx, int Vy, double VForward, int WanJia)
{
	int iX;
	int iY;
	iX = Player1.getwidth();										//��ȡС��ͼƬ�ĳߴ�
	iY = Player1.getheight();
	DWORD* pbtch = GetImageBuffer(&pengzhuang);						//��һ��ʹ��GetImageBuffer������GetImageBuffer���㣡
	int a[2];
	a[0] = Vx + (int)ceil(((double)iX / 2)*cos(VForward));			//��ȡ��ͷ���꣬��ȷ����ͷ�м���Ǹ����ص�λ�ã����ֱ��ʹ��Vx��Vy�Ļ��ᵼ�µ�����ʻ���ٶ�Ϊ�������ʱ���������������
	a[1] = Vy + (int)ceil(((double)iY / 2)*sin(VForward));
	DWORD c = pbtch[PointTsm(a[0] + 30, a[1] + 20, WIDE, HEIGHT)];  //��С����ͷ���ڵ����ص����ɫ��Ϣ��ֵ��c����Ϊ����ԭ����ײͼ������ͼ��Щ��λ�������в����ܿ������������30��20�����в�����
	if (c == BGR(BLACK))
	{
		SpeedChange = Finroad;
	}
	if (c == BGR(0x0000FF))
	{
		if (WanJia == 1)
		{
			Pspeed = 0; return;
		}
		if (WanJia == 2)
		{
			Cspeed = 0; return;
		}
	}
	if (c == BGR(0x00FFFF))
	{
		SpeedChange = Finsand;
	}
	if (c == BGR(0xFFFFFF))						//��������ɫ��ǳ�������м��ٵ�Ч�������ǻ���ѿ��ơ�
	{
		MaxSpeed = 10;
	}
	if (c == BGR(0x00FF00))						//�����Ҫ�������ж��Ƿ���ߺ��Ƿ񳭽�·Υ�档
	{
		inSline1 = true;
	}
	if (c == BGR(0xFFFF00))						//�������ж���
	{
		inSline2 = true;
	}
	if (!player)
	{
		if (inSline1)							//������������յ㣬�ж��Ƿ񳭽��������������¿�ʼ����������ɱ�������ʾ��ʱ�����ȴ������ʱ����
		{
			if (inSline1&&inSline2)
			{
				loadimage(&Victory1,_T("�ļ�\\Victory.jpg"));
				Victory();
			}
			else if (Pspeed > 0)
			{
				putimage(0, 0, &JingGao);
				mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
				mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
				BeginBatchDraw();
				while (true)
				{

					FlushBatchDraw();
					FlushMouseMsgBuffer();					 //�����껺��
					Jinggao = GetMouseMsg();
					if (Jinggao.mkLButton)
					{
						if (MouseTouch2(990, 640, 1110, 660, Jinggao))
						{
							gaming(player);
						}
					}
				}
				EndBatchDraw();
			}
			return;
		}
	}
	else  //˫��ģʽ�ж�ʤ��
	{
		if (inSline1&&WanJia == 1)
		{
			loadimage(&Victory1, _T("�ļ�\\Victory2.jpg"));
			Victory();
		}
		if (inSline1&&WanJia == 2)
		{
			loadimage(&Victory1, _T("�ļ�\\Victory1.jpg"));
			Victory();
		}
	}
}

//λ�ø���
/*******************************�� ½�Ǵ� ��3��2�ո���*********************************/
void Position()
{
	MoveCheck(Px, Py, PForward, 1);								//�����ײ
	Mx1 = Pspeed * cos(1 * PForward) + Px;			//�������ƻ��ֵķ�ʽ���С�����н�·���Ի�á�����������Ч����Mx1,My1�����ݴ�Ϊλ����Ϣ
	My1 = Pspeed * sin(1 * PForward) + Py;
	Px = (int)ceil(Mx1);							//��λ�����ݸ�ֵ��Px��Py��ceil()�������Ƿ��ز����ڸ����������
	Py = (int)ceil(My1);

	//���һ���ٶȿ���
	if (SpeedChange < abs(Pspeed))							//���ڵ����Ħ����С���ٶȵľ���ֵ
	{
		if (Pspeed < 0)		Pspeed = Pspeed + SpeedChange;  //ʹС������ֹͣ�������ɿ��ϼ����¼���ֹͣ��
		if (Pspeed > 0)		Pspeed = Pspeed - SpeedChange;
	}
	else
		Pspeed = 0;

	//��Ҷ��Ŀ��ƣ�ԭ��ͬ�ϡ������淨��ͬ���ڻ��д���޸ġ�
	if (player)
	{
		MoveCheck(Cx, Cy, CForward, 2);
		Mx2 = Cspeed * cos(CForward) + Cx;
		My2 = Cspeed * sin(CForward) + Cy;
		Cx = Mx2;
		Cy = My2;

		//��ֹ������ײ���������ֻ���ڲ�����ײ�������ż���Ƿ���ײ
		//if (flag == 0)
		{
			CollisionBetweenCircles(15, 15);
		}

		//���ڵ����Ħ����С���ٶȵľ���ֵ
		if (SpeedChange < abs(Cspeed))
		{
			if (Cspeed < 0)		Cspeed = Cspeed + SpeedChange;
			if (Cspeed > 0)		Cspeed = Cspeed - SpeedChange;
		}
		else
			Cspeed = 0;
	}
}

/************************************�� ������ ��3��10�ո���***********************************/
//�������ж�
void birth()
{
	int a1;
	int a2;
	DWORD* kaishi = GetImageBuffer(&pengzhuang); //����kaishi��ΪGetImageBufferָ�룬��ȡͼƬ�������ɫ��Ϣ��
	int QiPao;
	for (a1 = 1; a1 < HEIGHT - 10; a1++)			//����ѭ������kaishiָ��ɨ��ͼƬ����������Ѱ�������ߣ�����Ϊ��ɫ��
	{
		for (a2 = 1; a2 < WIDE - 10; a2++)
		{
			int i = WIDE * a1 + a2;
			QiPao = kaishi[i];					//��kaishi[i]�е���ɫ���ݸ�ֵ��QiPao
			if (QiPao == BGR(0x00FF00))			//�Ƚ�QiPao�����ݺ���ɫ�������ͬ����ȷ��������λ�����꣬��a2 a1�ֱ𸳸�Px Py����gaming�����н�����ͼƬ������Ӧ��λ�á�
			{
				Px = a2 - 40;
				Py = a1 + 30;
				goto aa;						//����goto�������ѭ������������� ��aa��
			}
		}
	}
aa:Birth1 = false;								//����Birth1��ֵΪfalse����֮�����Ϸ�����в��ٽ���birth()������
}

//ÿ����Ϸǰ���г�ʼ��
void initdata()
{									
	cleardevice();
	if (!player)
	{
		Pspeed = 0;
		Birth1 = true;
		PForward = 0;
		inSline1 = false;
		inSline2 = false;
		PauseTime = 0;
		Menutime = 0;
	}
	if (player)
	{
		inSline1 = false;
		Rota = 5;
		MaxSpeed = 10;
		Player1 = car1;
		Player2 = car2;
		Pspeed = 0;
		Cspeed = 0;
		Px = 200; Py = 360; PForward = 0;
		Cx = 1080; Cy = 360; CForward = -PI;
	}
}

//��ײ��⺯����Ĭ��ͼƬԲ��
void CollisionBetweenCircles(float c1, float c2)
{
	int m;									//���������õ���ʱ����
	float n;
	float distanceOfCenter = sqrt(pow((Px - Cx), 2) + pow((Py - Cy), 2));
	float distanceOfRadius = c1 + c2;

	PForward0 = PForward;					//���µı����洢�Ƕȣ�ʵ����ײʱ����ͼ��ĺ���
	CForward0 = CForward;

	//��⵽��ײ��˫�������ٶȣ�flag��1
	if (distanceOfCenter <= distanceOfRadius)
	{
		flag = 1;
		m = Pspeed;
		Pspeed = Cspeed;
		Cspeed = m;
		n = PForward0;
		PForward0 = CForward0;
		CForward0 = n;
		mciSendString(_TEXT("resume music3"), NULL, 0, NULL);
		mciSendString(_TEXT("open �ļ�\\ײ��.mp3 alias music3"), NULL, 0, NULL);
		mciSendString(_TEXT("play music3 repeat "), NULL, 0, NULL);
		return;
	}
	//û����ײ��flag����
	else
	{
		mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
		mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
		mciSendString(_TEXT("stop music3"), NULL, 0, NULL);
		flag = 0;
		return;
	}
}
