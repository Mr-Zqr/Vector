#include"NieR.h"

/********************************由 赵清锐 于3月7日更新********************************/
/***********************由 赵清锐 于3月10日更新（抄近路和重点线判断）******************/
//判断赛车所在位置，调整摩擦力	
/*********赵清锐 3月15日调整，更改了参数数量使其能控制两个玩家*************/
void MoveCheck(int Vx, int Vy, double VForward, int WanJia)
{
	int iX;
	int iY;
	iX = Player1.getwidth();										//获取小车图片的尺寸
	iY = Player1.getheight();
	DWORD* pbtch = GetImageBuffer(&pengzhuang);						//再一次使用GetImageBuffer函数，GetImageBuffer真香！
	int a[2];
	a[0] = Vx + (int)ceil(((double)iX / 2)*cos(VForward));			//获取车头坐标，精确到车头中间的那个像素的位置，如果直接使用Vx，Vy的话会导致当车辆驶入速度为零的区域时卡在里面出不来。
	a[1] = Vy + (int)ceil(((double)iY / 2)*sin(VForward));
	DWORD c = pbtch[PointTsm(a[0] + 30, a[1] + 20, WIDE, HEIGHT)];  //将小车车头所在的像素点的颜色信息赋值给c。因为不明原因碰撞图和赛场图有些错位（电脑中并不能看出来）因此用30和20来进行补偿。
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
	if (c == BGR(0xFFFFFF))						//赛道上颜色较浅的区域有加速的效果，但是会很难控制。
	{
		MaxSpeed = 10;
	}
	if (c == BGR(0x00FF00))						//这个得要，用于判断是否冲线和是否抄近路违规。
	{
		inSline1 = true;
	}
	if (c == BGR(0xFFFF00))						//抄近道判定线
	{
		inSline2 = true;
	}
	if (!player)
	{
		if (inSline1)							//如果赛车到达终点，判断是否抄近道并决定是重新开始比赛还是完成比赛并显示用时。（等待接入计时器）
		{
			if (inSline1&&inSline2)
			{
				loadimage(&Victory1,_T("文件\\Victory.jpg"));
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
					FlushMouseMsgBuffer();					 //清空鼠标缓存
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
	else  //双人模式判断胜利
	{
		if (inSline1&&WanJia == 1)
		{
			loadimage(&Victory1, _T("文件\\Victory2.jpg"));
			Victory();
		}
		if (inSline1&&WanJia == 2)
		{
			loadimage(&Victory1, _T("文件\\Victory1.jpg"));
			Victory();
		}
	}
}

//位置更新
/*******************************由 陆星存 于3月2日更新*********************************/
void Position()
{
	MoveCheck(Px, Py, PForward, 1);								//检测碰撞
	Mx1 = Pspeed * cos(1 * PForward) + Px;			//利用类似积分的方式算出小车的行进路线以获得“开”起来的效果。Mx1,My1用于暂存为位置信息
	My1 = Pspeed * sin(1 * PForward) + Py;
	Px = (int)ceil(Mx1);							//将位置数据赋值给Px，Py，ceil()的作用是返回不大于该数最大整数
	Py = (int)ceil(My1);

	//玩家一的速度控制
	if (SpeedChange < abs(Pspeed))							//所在地面的摩擦力小于速度的绝对值
	{
		if (Pspeed < 0)		Pspeed = Pspeed + SpeedChange;  //使小车缓慢停止而不是松开上键或下键就停止。
		if (Pspeed > 0)		Pspeed = Pspeed - SpeedChange;
	}
	else
		Pspeed = 0;

	//玩家二的控制，原理同上。但因玩法不同后期会有大的修改。
	if (player)
	{
		MoveCheck(Cx, Cy, CForward, 2);
		Mx2 = Cspeed * cos(CForward) + Cx;
		My2 = Cspeed * sin(CForward) + Cy;
		Cx = Mx2;
		Cy = My2;

		//防止卡在碰撞里出不来，只有在不是碰撞的情况里才检测是否碰撞
		//if (flag == 0)
		{
			CollisionBetweenCircles(15, 15);
		}

		//所在地面的摩擦力小于速度的绝对值
		if (SpeedChange < abs(Cspeed))
		{
			if (Cspeed < 0)		Cspeed = Cspeed + SpeedChange;
			if (Cspeed > 0)		Cspeed = Cspeed - SpeedChange;
		}
		else
			Cspeed = 0;
	}
}

/************************************由 赵清锐 于3月10日更新***********************************/
//出生点判断
void birth()
{
	int a1;
	int a2;
	DWORD* kaishi = GetImageBuffer(&pengzhuang); //设置kaishi作为GetImageBuffer指针，获取图片数组的颜色信息。
	int QiPao;
	for (a1 = 1; a1 < HEIGHT - 10; a1++)			//利用循环控制kaishi指针扫过图片的整个像素寻找起跑线（被画为绿色）
	{
		for (a2 = 1; a2 < WIDE - 10; a2++)
		{
			int i = WIDE * a1 + a2;
			QiPao = kaishi[i];					//将kaishi[i]中的颜色数据赋值给QiPao
			if (QiPao == BGR(0x00FF00))			//比较QiPao的数据和绿色，如果相同，即确定起跑线位置坐标，将a2 a1分别赋给Px Py，在gaming函数中将赛车图片放入相应的位置。
			{
				Px = a2 - 40;
				Py = a1 + 30;
				goto aa;						//利用goto语句跳出循环，跳至标记行 “aa”
			}
		}
	}
aa:Birth1 = false;								//调整Birth1的值为false，在之后的游戏运行中不再进入birth()函数。
}

//每次游戏前进行初始化
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

//碰撞检测函数，默认图片圆形
void CollisionBetweenCircles(float c1, float c2)
{
	int m;									//交换数据用的临时变量
	float n;
	float distanceOfCenter = sqrt(pow((Px - Cx), 2) + pow((Py - Cy), 2));
	float distanceOfRadius = c1 + c2;

	PForward0 = PForward;					//用新的变量存储角度，实现碰撞时车子图像的后退
	CForward0 = CForward;

	//检测到碰撞，双方交换速度，flag置1
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
		mciSendString(_TEXT("open 文件\\撞车.mp3 alias music3"), NULL, 0, NULL);
		mciSendString(_TEXT("play music3 repeat "), NULL, 0, NULL);
		return;
	}
	//没有碰撞，flag回零
	else
	{
		mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
		mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
		mciSendString(_TEXT("stop music3"), NULL, 0, NULL);
		flag = 0;
		return;
	}
}
