#include"NieR.h"
/****************�� ���g�� ��2019��3��17�� �༭ ȫ�����ߵĳ��ּ�ʰȡ���ͷ�**********/
struct prop
{
	int	radius;
	int	circletime;
	int circlepos[2];
	bool	drawcircle;
	int flash;
	int attack;
	int magnet;
	int energy;
};
struct prop Pprop = { 5000,100,0,0,false,0,0,0,0 }, Cprop = { 5000,100,0,0,false,0,0,0,0 };

struct setprop
{
	int istime;
	int interval;
	int type;
	int pos[2];
	int flag;
};
struct setprop isset = { 0,2000,0,0,0,0 };

struct ifget
{
	bool ifflash;
	bool ifattack;
	bool ifmagnet;
	bool ifenergy;
};
struct ifget ifopen = { false,false,false,false };


//��ຯ�� ��
void meansure(int Px, int Py, int Cx, int Cy)//�����͵��߾���
{

	Pprop.radius = (Px - isset.pos[0] + 25)*(Px - isset.pos[0] + 25) + (Py - isset.pos[1] + 25)*(Py - isset.pos[1] + 25);
	Cprop.radius = (Cx - isset.pos[0] + 25)*(Cx - isset.pos[0] + 25) + (Cy - isset.pos[1] + 25)*(Cy - isset.pos[1] + 25);
}

//����������������������
void random()
{
	isset.type = rand() % 2;//���������ж�
	if (map == 1)
	{
		isset.pos[0] = rand() % 500 + 400;//����λ���ж�
		isset.pos[1] = rand() % 200 + 300;
	}
	if (map == 2)
	{
		isset.pos[0] = 400 + isset.type * 470;
		isset.pos[1] = 360;
	}
}
//���߷��ú���
void set()
{
	isset.flag = isset.istime % isset.interval;
	if (isset.istime >= isset.interval)
	{
		switch (isset.type)
		{
		case 0:putimage(isset.pos[0] - flash.getwidth(), isset.pos[1] - flash.getheight(), &attack); ifopen.ifattack = true; break;
		case 1:putimage(isset.pos[0] - flash.getwidth(), isset.pos[1] - flash.getheight(), &flash); ifopen.ifflash = true; break;
		

		default:
			break;
			if (isset.istime >= 2 * isset.interval)
				isset.istime = isset.interval + 1;
		}
		if (isset.flag == 0)
		{
			random();

		}
		if (Cprop.radius < 1000)//�����ǵ���ʰȡ��������ͬ���͵��߼�һ������С�ڸ���1000�ж�Ϊ��ȡ
		{
			isset.pos[0] = 1350;
			isset.pos[1] = 800;
			if (ifopen.ifflash)
			{
				Cprop.flash += 1;
				ifopen.ifflash = false;
				ifopen.ifattack = false;
			}
			if (ifopen.ifattack)
			{
				Cprop.attack+=1;
				ifopen.ifattack = false;
				ifopen.ifflash = false;
			}
			/*if (ifopen.ifmagnet)
			{
				Cprop.magnet++;
				ifopen.ifmagnet = false;
			}*/
			/*if (ifopen.ifenergy)
			{
				Cprop.energy++;
				ifopen.ifenergy = false;
			}*/
		}
		if (Pprop.radius < 1000)
		{
			isset.pos[0] = 1350;
			isset.pos[1] = 800;
			if (ifopen.ifflash)
			{
				Pprop.flash+=1;
				ifopen.ifflash = false;
				ifopen.ifattack = false;
			}
			if (ifopen.ifattack)
			{
				Pprop.attack+=1;
				ifopen.ifattack = false;
				ifopen.ifflash = false;
			}
		}
	}
}

//���1�����ּ���
void PPPPPflash()					
{
	if (Pprop.flash > 0)
	{
		Px += 80 * cos(PForward);	//��ǰ����70
		Py += 80 * sin(PForward);
		Pprop.flash -= 1;
	}
}

//���1�Ĺ�������
void PPPPPattack()					
{
	if (Pprop.attack > 0)
	{
		Cx -= 50 * cos(CForward);	//ʹ���2����30
		Cy -= 50 * sin(CForward);
		Pprop.attack -= 1;
	}
}

//ͬ��
void CCCCCflash()				
{
	if (player && (Cprop.flash > 0))
	{
		Cx += 80 * cos(CForward);
		Cy += 80 * sin(CForward);
		Cprop.flash -= 1;
	}
}
void CCCCCattack()
{
	if (player && (Cprop.attack > 0))
	{
		Px -= 50 * cos(PForward);
		Py -= 50 * sin(PForward);
		Cprop.attack -= 1;
	}
}

//�ж�����λ�õ���Ҫ����
void PutImgWithout(IMAGE &obj, int px, int py, COLORREF withouter = WHITE, DWORD* pbWnd = GetImageBuffer(), int wX = getwidth(), int wY = getheight(), DWORD bitsub = 0x00FFFFFF)   //reference code �е�һ�κ��������ڱ���С����תʱ���ֵĺ�ɫ�߿�
{
	DWORD* pbImg = GetImageBuffer(&obj);
	int iX = obj.getwidth();
	int iY = obj.getheight();
	for (int i1 = 0; i1 < iX; i1++)
	{
		for (int i2 = 0; i2 < iY; i2++)
		{
			if (PointTsm(i1 + px, i2 + py, wX, wY) == -1)continue;						 // ����Ƿ�Խ��
			if ((pbImg[PointTsm(i1, i2, iX, iY)] & bitsub) == BGR(withouter))continue;	 // ����Ƿ�Ҫ�ų�����ɫ
			pbWnd[PointTsm(i1 + px, i2 + py, wX, wY)] = pbImg[PointTsm(i1, i2, iX, iY)]; // �����Դ�
		}
	}
}

//��Ϸ��ѭ��  
/**************************************************�� ½�Ǵ� ��3��2�ո���*****************************************************/
void gaming(int player)
{
	timer a;
	ChooseMap();							//ѡ��ͬ��ͼ
	initdata();								//ÿ�ν�����Ϸǰ�ĳ�ʼ��
	cleardevice();
	Start = clock();//��ʼ��ʱ��Ϊ����ͣ���ģ�
	//����ģʽ
	if (!player)
	{
		BeginBatchDraw();												//�롱FlushBatchDraw����EndBatchDraw"һͬʹ����������С���˶�ʱ����˸����
		while (true)													//��ѭ��
		{
			if (Birth1)
			{
				birth();												//���������ϵ�������λ��ȷ�������㣬���н����󲼶�����Birth1��Ϊfalse��
			}
			if (a.WaitFor(30))											//��25����
			{
				DispatchCommand(GetCommand());							//GetCommand��ü��̲�����֮��Ĳ����뿴DispatchCommand��
				Position();
				time();										//λ���жϣ������ƻ��ֵ�ԭ��ó�С��λ��
			}
			//cleardevice();
			settextcolor(WHITE);

			rotateimage(&Player1, &car1, -PForward, WHITE, true, false);//��תС��ͼƬ��ʵ�֡�����������Ч����
			putimage(0, 0, &Racing);									//��������ͼƬ
			PutImgWithout(Player1, Px, Py);								//PutImgWithout���������õ�reference code ��һ�κ��������ֱ��putimage(),����������С����ת�����µĺڱߡ�
			//FlushBatchDraw();
		}
		//EndBatchDraw();
	}
	else//���ڵڶ���С���Ĳ�����ԭ��ͬ�ϡ�
	{
		int count = 0;
		MaxSpeed = 15;
		Rota = 17;
		BeginBatchDraw();
		while (true)
		{
			isset.istime++;
			//Now = clock();
			meansure(Px, Py, Cx, Cy);
			if (flag == 0)
			{
				if (a.WaitFor(25))
				{

					DispatchCommand(GetCommand());
					Position();
				}
			}
			//˫��ģʽ�µļ�����ײ�㷨
			else
			{
				//mciSendString(_TEXT("open �ļ�\\ײ��.mp3 alias music3"), NULL, 0, NULL);
				//mciSendString(_TEXT("play music3 repeat "), NULL, 0, NULL);
				count++;
				Mx1 = Pspeed * cos(1 * PForward0) + Px;
				My1 = Pspeed * sin(1 * PForward0) + Py;
				Px = (int)ceil(Mx1);
				Py = (int)ceil(My1);
				Mx2 = Cspeed * cos(CForward0) + Cx;
				My2 = Cspeed * sin(CForward0) + Cy;
				Cx = (int)ceil(Mx2);
				Cy = (int)ceil(My2);
				if (count >= 10)
				{
					count = 0;
					flag = 0;
				}
			}
			cleardevice();
			settextcolor(WHITE);

			putimage(0, 0, &Racing);
			set();
			rotateimage(&Player1, &car1, -PForward, WHITE, true, false);
			PutImgWithout(Player1, Px, Py);
			rotateimage(&Player2, &car2, -CForward, WHITE, true, false);
			PutImgWithout(Player2, Cx, Cy);

			FlushBatchDraw();
		}
		EndBatchDraw();
	}
}