#pragma once
#pragma warning(disable:4996)

#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
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
#include <mmsystem.h>		// ���� MP3 ����
#pragma comment(lib,"Winmm.lib")

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define RADIAN(angle) 3.14159*angle/180   //�����ʵ�ֽǶ�ת���ɻ���

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

extern MOUSEMSG KaiShi;			//����������
extern MOUSEMSG XuanZeDiTu1;
extern MOUSEMSG ZanTingCaiDan;
extern MOUSEMSG help;
extern MOUSEMSG Jinggao;
extern MOUSEMSG Shengli;

extern int gid;				//���˵�ѡ�����
extern int map;				//ͼƬѡ����

extern int Cspeed;				// �ٶ�CspeedΪ���2��PspeedΪ���1
extern int Pspeed;
extern double PForward;		// ����
extern double CForward;
extern double PForward0;		//���µı����洢�Ƕȣ�ʵ����ײʱ����ͼ��ĺ���
extern double CForward0;
extern double Mx1, My1;			//ʵʱλ�ø���
extern double Mx2, My2;
extern int Px,Py;					//��ʼλ��
extern int Cx, Cy;
extern int Rota;				// ת���ٶȵ� -1 �η������ڵ���С��ת���ٶ�
extern int MaxSpeed;			//����ٶ�
extern int SpeedAdd;			// ���ٶ�
extern int SpeedChange;		//��ͬ���ε�Ħ����
extern int Finroad;
extern int Finsand;
extern int player;				//�ж���Ϸģʽ
extern bool flag;				//С����ײ��־

extern float Time;					//ָʾ��ʱ
extern clock_t Menutime;
extern clock_t PauseTime;
extern char t[50];					//��ʱ���ı�
extern int R;

//�ж�С��λ��
extern bool inRoad;
extern bool inSand;
extern bool inWall;
extern bool inSline1;		//�ж��Ƿ�λ�����
extern bool inSline2;		//�ж��Ƿ񳭽�·
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

extern clock_t Start;			//����ʱ��ı�������
extern clock_t Now;
extern clock_t Pause;
extern clock_t Restart;
extern clock_t MeumUsed;

extern IMAGE Menu;					//���ͼ����
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

// ��ʱ��
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

