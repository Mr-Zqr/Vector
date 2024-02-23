#include"NieR.h"
/****************由 杜鎔杰 于2019年3月17日 编辑 全部道具的出现及拾取及释放**********/
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


//测距函数 杜
void meansure(int Px, int Py, int Cx, int Cy)//赛车和道具距离
{

	Pprop.radius = (Px - isset.pos[0] + 25)*(Px - isset.pos[0] + 25) + (Py - isset.pos[1] + 25)*(Py - isset.pos[1] + 25);
	Cprop.radius = (Cx - isset.pos[0] + 25)*(Cx - isset.pos[0] + 25) + (Cy - isset.pos[1] + 25)*(Cy - isset.pos[1] + 25);
}

//随机函数，随机出道具数据
void random()
{
	isset.type = rand() % 2;//道具类型判断
	if (map == 1)
	{
		isset.pos[0] = rand() % 500 + 400;//道具位置判断
		isset.pos[1] = rand() % 200 + 300;
	}
	if (map == 2)
	{
		isset.pos[0] = 400 + isset.type * 470;
		isset.pos[1] = 360;
	}
}
//道具放置函数
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
		if (Cprop.radius < 1000)//下面是道具拾取函数，捡到同类型道具加一，距离小于根号1000判断为获取
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

//玩家1的闪现技能
void PPPPPflash()					
{
	if (Pprop.flash > 0)
	{
		Px += 80 * cos(PForward);	//向前闪现70
		Py += 80 * sin(PForward);
		Pprop.flash -= 1;
	}
}

//玩家1的攻击技能
void PPPPPattack()					
{
	if (Pprop.attack > 0)
	{
		Cx -= 50 * cos(CForward);	//使玩家2后退30
		Cy -= 50 * sin(CForward);
		Pprop.attack -= 1;
	}
}

//同上
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

//判断赛车位置的重要函数
void PutImgWithout(IMAGE &obj, int px, int py, COLORREF withouter = WHITE, DWORD* pbWnd = GetImageBuffer(), int wX = getwidth(), int wY = getheight(), DWORD bitsub = 0x00FFFFFF)   //reference code 中的一段函数，用于避免小车旋转时出现的黑色边框
{
	DWORD* pbImg = GetImageBuffer(&obj);
	int iX = obj.getwidth();
	int iY = obj.getheight();
	for (int i1 = 0; i1 < iX; i1++)
	{
		for (int i2 = 0; i2 < iY; i2++)
		{
			if (PointTsm(i1 + px, i2 + py, wX, wY) == -1)continue;						 // 检测是否越界
			if ((pbImg[PointTsm(i1, i2, iX, iY)] & bitsub) == BGR(withouter))continue;	 // 检测是否要排除该颜色
			pbWnd[PointTsm(i1 + px, i2 + py, wX, wY)] = pbImg[PointTsm(i1, i2, iX, iY)]; // 操作显存
		}
	}
}

//游戏主循环  
/**************************************************由 陆星存 于3月2日更新*****************************************************/
void gaming(int player)
{
	timer a;
	ChooseMap();							//选择不同地图
	initdata();								//每次进行游戏前的初始化
	cleardevice();
	Start = clock();//开始计时（为了暂停留的）
	//单人模式
	if (!player)
	{
		BeginBatchDraw();												//与”FlushBatchDraw“”EndBatchDraw"一同使用用于消除小车运动时的闪烁问题
		while (true)													//死循环
		{
			if (Birth1)
			{
				birth();												//根据赛道上的起跑线位置确定出生点，运行结束后布尔变量Birth1变为false。
			}
			if (a.WaitFor(30))											//等25毫秒
			{
				DispatchCommand(GetCommand());							//GetCommand获得键盘操作，之后的操作请看DispatchCommand。
				Position();
				time();										//位置判断，用类似积分的原理得出小车位置
			}
			//cleardevice();
			settextcolor(WHITE);

			rotateimage(&Player1, &car1, -PForward, WHITE, true, false);//旋转小车图片，实现“开起来”的效果。
			putimage(0, 0, &Racing);									//放置赛道图片
			PutImgWithout(Player1, Px, Py);								//PutImgWithout是我们引用的reference code 的一段函数，相比直接putimage(),它可以消除小车旋转后留下的黑边。
			//FlushBatchDraw();
		}
		//EndBatchDraw();
	}
	else//对于第二辆小车的操作，原理同上。
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
			//双人模式下的简易碰撞算法
			else
			{
				//mciSendString(_TEXT("open 文件\\撞车.mp3 alias music3"), NULL, 0, NULL);
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