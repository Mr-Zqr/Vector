#pragma once
#pragma warning(disable:4996)

#include <graphics.h>      // 引用图形库头文件
#include <ctime>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <direct.h>
#include <Windows.h>
#include <mmsystem.h>		// 播放 MP3 所需
#pragma comment(lib,"Winmm.lib")

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define RADIAN(angle) 3.14159*angle/180   //定义宏实现角度转换成弧度

using namespace std;

#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define CMD_FLASH		512
#define CMD_ATTACK		1024
//#define CMD_MAGNET		2048
#define	sCMD_UP			16
#define	sCMD_DOWN		32
#define	sCMD_LEFT		64
#define	sCMD_RIGHT		128
#define sCMD_FLASH		4096
#define sCMD_ATTACK		8192
//#define sCMD_MAGNET		16384
#define	CMD_PAUSE		256
#define PI				3.1415926
#define WIDE 1280
#define HEIGHT 720

extern MOUSEMSG KaiShi;			//鼠标变量定义
extern MOUSEMSG XuanZeDiTu1;
extern MOUSEMSG ZanTingCaiDan;
extern MOUSEMSG help;
extern MOUSEMSG Jinggao;
extern MOUSEMSG Shengli;

extern int gid;				//主菜单选择变量
extern int map;				//图片选择函数

extern int Cspeed;				// 速度Cspeed为玩家2，Pspeed为玩家1
extern int Pspeed;
extern double PForward;		// 方向
extern double CForward;
extern double PForward0;		//用新的变量存储角度，实现碰撞时车子图像的后退
extern double CForward0;
extern double Mx1, My1;			//实时位置更新
extern double Mx2, My2;
extern int Px,Py;					//初始位置
extern int Cx, Cy;
extern int Rota;				// 转动速度的 -1 次方，用于调整小车转弯速度
extern int MaxSpeed;			//最大速度
extern int SpeedAdd;			// 加速度
extern int SpeedChange;		//不同地形的摩擦力
extern int Finroad;
extern int Finsand;
extern int player;				//判断游戏模式
extern bool flag;				//小车碰撞标志

extern float Time;					//指示用时
extern clock_t Menutime;
extern clock_t PauseTime;
extern char t[50];					//计时器文本
extern int R;

//判定小车位置
extern bool inRoad;
extern bool inSand;
extern bool inWall;
extern bool inSline1;		//判断是否位于起点
extern bool inSline2;		//判断是否抄近路
extern bool inBoost;
extern bool Birth1;
extern bool Birth2;
extern bool is_paused;

extern char Name1[50];
extern char Name2[50];
extern char Name3[50];
extern char Name4[50];
extern char Name5[50];

extern float lap1;
extern float lap2;
extern float lap3;
extern float lap4;
extern float lap5;

extern char Lap1[50];
extern char Lap2[50];
extern char Lap3[50];
extern char Lap4[50];
extern char Lap5[50];

extern FILE *Rank1;
extern FILE *Rank2;
extern FILE *Rank3;
extern FILE *Rank4;
extern FILE *Rank5;

extern clock_t Start;			//关于时间的变量定义
extern clock_t Now;
extern clock_t Pause;
extern clock_t Restart;
extern clock_t MeumUsed;

extern IMAGE Menu;					//相关图像定义
extern IMAGE car1, car2;
extern IMAGE Player1, Player2;
extern IMAGE Racing;
extern IMAGE pengzhuang;
extern IMAGE SaiDaoXuanZe;
extern IMAGE zanting;
extern IMAGE Help;
extern IMAGE JingGao;
extern IMAGE flash;
extern IMAGE attack;
extern IMAGE magnet;
extern IMAGE energy;
extern IMAGE Victory1;
extern IMAGE LIST1,LIST2;
extern IMAGE Fail1;
extern IMAGE Fail2;

// 计时器
extern class timer
{
	private:
		bool is_start = false;
		clock_t start;
	public:
		bool WaitFor(clock_t s)
		{
			if (is_start)
			{
				if ((start + s) <= clock())
				{
					is_start = false;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				start = clock();
				is_start = true;
				return false;
			}
		}
};

void gaming(int player);
void Init();
void PauseMenu();
void time();
void ShowHelp();
void ChooseMap();

bool MouseTouch1(double upbound, double lowbound, int slot, int boundary, MOUSEMSG m);
bool MouseTouch2(int left, int top, int right, int buttom, MOUSEMSG m);
void POnLeft();
void POnRight();
void POnUp();
void POnDown();
void COnLeft();
void COnRight();
void COnUp();
void COnDown();
int GetCommand();
void DispatchCommand(int _cmd);

int PointTsm(int x, int y, int wide, int high);

void CollisionBetweenCircles(float c1, float c2);
void MoveCheck(int Vx, int Vy, double VForward, int WanJia);
void Position();
void birth();
void initdata();
void MoShi();
void Victory();

void meansure(int Px, int Py, int Cx, int Cy);
void CCCCCattack();
void CCCCCflash();
void PPPPPattack();
void PPPPPflash();
void random();
void set();

void Sorry();
int Rank(double Time);
void WriteAll1();
void WriteAll2();
void ReadAll1();
void ReadAll2();
void LapChange1(int i);
void LapChange2(int i);
void LapShow(int i);

