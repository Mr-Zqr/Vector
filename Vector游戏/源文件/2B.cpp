/******程序模块化由 陆星存 于2019年3约18日 实现*******/
#include "NieR.h"

extern struct prop Pprop, Cprop;
extern struct ifget ifopen;
extern struct setprop isset;

MOUSEMSG KaiShi;			//鼠标变量定义
MOUSEMSG XuanZeDiTu1;
MOUSEMSG ZanTingCaiDan;
MOUSEMSG help;
MOUSEMSG Jinggao;
MOUSEMSG Shengli;

int gid = 0;				//主菜单选择变量
int map = 0;				//图片选择函数

int Cspeed = 0;				// 速度Cspeed为玩家2，Pspeed为玩家1
int Pspeed = 0;
double PForward = 0;		// 方向
double CForward = 0;
double PForward0 = 0;		//用新的变量存储角度，实现碰撞时车子图像的后退
double CForward0 = 0;
double Mx1, My1;			//实时位置更新
double Mx2, My2;
int Px, Py;					//初始位置
int Cx = 120, Cy = 100;
int Rota = 23;				// 转动速度的 -1 次方，用于调整小车转弯速度
int MaxSpeed = 14;			//最大速度
int SpeedAdd = 2;			// 加速度
int SpeedChange = 0;		//不同地形的摩擦力
int Finroad = 1;
int Finsand = 3;
int player = 1;				//判断游戏模式
bool flag = 0;				//小车碰撞标志
int mapo = 0;
float Time;					//指示用时
clock_t Menutime;
clock_t PauseTime = 0;
char t[50] = { 0 };					//计时器文本
int R;

//判定小车位置
bool inRoad;
bool inSand;
bool inWall;
bool inSline1 = false;		//判断是否位于起点
bool inSline2 = false;		//判断是否抄近路
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

clock_t Start = 0;			//关于时间的变量定义
clock_t Now = 0;
clock_t Pause = 0;
clock_t Restart = 0;
clock_t MeumUsed = 0;

IMAGE Menu;					//相关图像定义
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

/**************由 赵清锐 于2019年3月13日编写   于2019年3月17日 添加计时器****/
void PauseMenu()
{
	mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
	mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
	mciSendString(_TEXT("stop music3"), NULL, 0, NULL);
	cleardevice();
	int flag;//定义局部标志变量
	Pause =clock();//取得此时的游戏时间
	BeginBatchDraw();
	while (true)
	{
		putimage(0, 0, &zanting);//加载背景图（后期虚化）
		FlushBatchDraw();
		FlushMouseMsgBuffer();  //清空鼠标缓存
		ZanTingCaiDan = GetMouseMsg();
		if (ZanTingCaiDan.mkLButton)
		{
			if (MouseTouch2(500, 280, 770, 350, ZanTingCaiDan))
			{
				flag = 1;
				Restart = clock();//取得按下“继续游戏”按钮时的时间
				Menutime = Restart - Pause;//算出时间差
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

//计时器函数
/*****************************由 郭泓灏 更新了很久************************************/
/*****************************由 李子明 更新了半天************************************/
/***********由 赵清锐 于3月13日更新(他只是把函数拖过来了，然后就不会了)  于3月17日实现完整功能***************/
void time()
{
	BeginBatchDraw();
	Now = clock();
	if (is_paused)
	{	
		PauseTime = PauseTime + Menutime;//暂停时间累加
		Pause = 0;
		Restart = 0;
		is_paused = false;
	}
	Time =((double)(Now-Start-PauseTime)) / CLOCKS_PER_SEC;//clock()获得的是从程序开始运行以来的CPU时间，因此分别设置start, now, pause, restart，等用来获取时间，然后求出游戏时间。
	outtextxy(1100, 50, ("当前用时："));
	sprintf_s(t, "%.3f s\n", Time);
	outtextxy(1170, 50,t);
	FlushBatchDraw();
	//EndBatchDraw();
}


//玩法帮助
/**********赵清锐 3月16日 编辑 添加图像和按钮************/
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

/********由 刘思语 赵清锐 于3月13日 编写  添加图片、按钮********/
//不同模式下的图片选择
void ChooseMap()
{
	//cleardevice();
	if (!player)
	{
		loadimage(&SaiDaoXuanZe, _T("文件\\选择赛道 1.jpg"));
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
					loadimage(&Racing, _T("文件\\单人赛道1\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("文件\\单人赛道1\\pengzhuang.gif"));
					loadimage(&zanting, _T("文件\\单人赛道1\\zanting.jpg"));
					loadimage(&JingGao, _T("文件\\单人赛道1\\jinggao.jpg"));
					map = 1;
					ReadAll1();
					return;
				}
				if (MouseTouch2(353, 422, 927, 548, XuanZeDiTu1))
				{
					loadimage(&Racing, _T("文件\\单人赛道2\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("文件\\单人赛道2\\pengzhuang.gif"));
					loadimage(&zanting, _T("文件\\单人赛道2\\zanting.jpg"));
					loadimage(&JingGao, _T("文件\\单人赛道2\\jinggao.jpg"));
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
		loadimage(&SaiDaoXuanZe, _T("文件\\选择赛道 2.jpg"), WIDE, HEIGHT);
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
					loadimage(&Racing, _T("文件\\双人赛道1\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("文件\\双人赛道1\\pengzhuang.gif"));
					loadimage(&zanting, _T("文件\\双人赛道1\\zanting.jpg"));
					map = 1;
					return;
				}
				if (MouseTouch2(353, 422, 927, 548, XuanZeDiTu1))
				{
					loadimage(&Racing, _T("文件\\双人赛道2\\Racing.jpg"), WIDE, HEIGHT);
					loadimage(&pengzhuang, _T("文件\\双人赛道2\\pengzhuang.gif"));
					loadimage(&zanting, _T("文件\\双人赛道2\\zanting.jpg"));
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

/***由 陆星存 于2019年3月2日 编写 用于计算数组位置*/
//用于获知小车所在位置的像素数组位置
int PointTsm(int x, int y, int wide, int high)
{
	if (x < 0)return x = 0;
	if (x >= wide)return x = wide;
	if (y < 0)return y = 0;
	if (y >= high)return y = high;

	return wide * y + x;
}

/*******************由 赵清锐 于2019年3月3日编辑 用于检测鼠标单击区域************/
bool MouseTouch2(int left, int top, int right, int buttom, MOUSEMSG m)
{
	if (m.x > left&&m.x<right&&m.y>top&&m.y < buttom)
		return true;
	else
		return false;
}

/*******************由 郭泓灏 于2019年3 月13日编辑*******/
void Victory()
{
	//loadimage(&Victory1, _T("文件\\Vicyory.jpg"));//加载胜利图片
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
	BeginBatchDraw();//结束游戏界面的绘制
	while (true)
	{
		putimage(0, 0, &Victory1);
		FlushBatchDraw();
		FlushMouseMsgBuffer();  //清空鼠标缓存
		Shengli = GetMouseMsg();
		//这里鼠标运动时会闪
		if (Shengli.mkLButton)
		{
			if (gid == 1)
			{
				if (MouseTouch2(1089, 605, 1234, 652, Shengli))//缺少圈速榜显示
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
					MoShi();							//退出按钮
				}
		}
	}
	EndBatchDraw();
}

/**************************由 陆星存 于3月2日更新*****************************/
//主程序的初始化函数
//读取图像，生成初始化界面，并进行模式选择		
void Init()
{
	loadimage(&flash, _T("文件\\道具\\flash.bmp"));
	loadimage(&attack, _T("文件\\道具\\attack.bmp"));
	loadimage(&magnet, _T("文件\\道具\\magnet.bmp"));
	loadimage(&energy, _T("文件\\道具\\energy.bmp"));
	loadimage(&Menu, _T("文件\\menu.jpg"));					//使用相对位置加载有关图像
	loadimage(&car1, _T("文件\\car.gif"));					
	loadimage(&car2, _T("文件\\car2.gif"));			
	loadimage(&Help, _T("文件\\help.jpg"));
	loadimage(&LIST1, _T("文件\\圈速榜1.jpg"));
	loadimage(&LIST2, _T("文件\\圈速榜2.jpg"));
	Player1=car1;											//预存一个一样的图形，以便在后面rotateimage的函数中使用
	initgraph(WIDE, HEIGHT);
	player = 0;
	gid = 0;

	ReadAll1();												//读出圈速榜
	PlaySound(TEXT("文件\\背景.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC | SND_NOSTOP);
	//模式的选择
	BeginBatchDraw();
	while (true)
	{
		putimage(0, 0, &Menu);
		FlushBatchDraw();
		EndBatchDraw();
		FlushMouseMsgBuffer();								//清空鼠标缓存
		KaiShi = GetMouseMsg();								//获取鼠标信息
		if (KaiShi.mkLButton)
		{
			if (MouseTouch1(200, 100, 130, 210, KaiShi))
			{
				gid = 1;									//单人模式
				break;
			}
			if (MouseTouch1(400, 300, 130, 210, KaiShi))
			{
				gid = 2;									//双人模式
				break;
			}
			if (MouseTouch2(1230, 480 ,1260, 610, KaiShi))
			{
				gid = 3;									//帮助菜单
				break;
			}
			if (MouseTouch2(1089, 655, 1234, 702, KaiShi))
			{
				gid = 4;									//退出按钮
				break;										
			}
		}
	}
}

/************************由 陆星存 于3月2日更新************************/
/***************由 赵清锐 于2019年3月13日更新 提高模块化程度 将模式选择独立到MoShi()函数**********/
//主函数		
int main()
{
	Init();											//进入游戏时的开始界面
	//cleardevice();//清屏
	MoShi();
	closegraph();
}


void MoShi()
{
	if (gid == 1)
	{
		player = 0;									//使用player变量标记单双人模式
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