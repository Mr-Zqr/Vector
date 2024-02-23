#include "Nier.h"

//���п��ƺ���
/*************�� ½�Ǵ� ��2019��3��2�ձ༭ ***********/
void POnLeft()
{
	PForward -= PI / Rota;
}

void POnRight()
{
	PForward += PI / Rota;
}

void POnUp()
{
	Pspeed += SpeedAdd;
	if (Pspeed > MaxSpeed)
	{
		Pspeed = MaxSpeed;
	}
}

void POnDown()
{
	Pspeed -= SpeedAdd;
	if (Pspeed < -MaxSpeed)
	{
		Pspeed = -MaxSpeed;
	}
}

void COnLeft()
{
	if (player)		CForward -= PI / Rota;
}

void COnRight()
{
	if (player)		CForward += PI / Rota;
}

void COnUp()
{
	if (player)
	{
		Cspeed += SpeedAdd;
		if (Cspeed > MaxSpeed)
		{
			Cspeed = MaxSpeed;
		}
	}
}

void COnDown()
{
	if (player)
	{
		Cspeed -= SpeedAdd;
		if (Cspeed < -MaxSpeed)
		{
			Cspeed = -MaxSpeed;
		}
	}
}

/******************************�� ���g�� ��3��6�ո���****************************/
//��������ж�	
//��������б���������ж�
bool MouseTouch1(double upbound, double lowbound, int slot, int boundary, MOUSEMSG m)
{
	double verdict;
	bool second = 0;
	verdict = 0.147*(m.x - slot) + m.y;
	if (m.x < slot)
		return false;
	if (verdict >= lowbound && verdict <= upbound)
	{
		if (m.y < boundary&&m.x <= 700)
			return true;
		else if (m.x < 550)
			return true;
		else
			return false;
	}
	else
		return false;
}

//��ȡ�û�����
int GetCommand()
{
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
		//mciSendString(_TEXT("open �ļ�\\��ʻ1.mp3 alias music1"), NULL, 0, NULL);
		//mciSendString(_TEXT("play music1 "), NULL, 0, NULL);
		c |= CMD_UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		//mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
		//mciSendString(_TEXT("open �ļ�\\ɲ��.mp3 alias music2"), NULL, 0, NULL);
		//mciSendString(_TEXT("play music2"), NULL, 0, NULL);
		c |= CMD_DOWN;
	}
	if (GetAsyncKeyState('N') & 0x8000)		c |= CMD_FLASH;
	if (GetAsyncKeyState('M') & 0x8000)		c |= CMD_ATTACK;
	//if (GetAsyncKeyState('M') & 0x8000)		c |= CMD_MAGNET;

	if (player)
	{
		if (GetAsyncKeyState('A') & 0x8000)		c |= sCMD_LEFT;
		if (GetAsyncKeyState('D') & 0x8000)		c |= sCMD_RIGHT;
		if (GetAsyncKeyState('W') & 0x8000)		c |= sCMD_UP;
		if (GetAsyncKeyState('S') & 0x8000)		c |= sCMD_DOWN;
		if (GetAsyncKeyState('F') & 0x8000)	c |= sCMD_FLASH;
		if (GetAsyncKeyState('G') & 0x8000)		c |= sCMD_ATTACK;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)		c |= CMD_PAUSE;
	return c;
}

//�����û������޸��ٶȺͷ���
//���GetCommand�ķ���ֵ��������С���ٶȸ��Ļ�Ƕȱ仯�Ĳ�����
void DispatchCommand(int _cmd)
{
	if (_cmd & CMD_UP)
	{
		POnUp();
		//mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
	}//Pspeed(ָС���ٶ�) ����ٶ���ӣ����ﵽ����ٶ��򱣳֡�
	if (_cmd & CMD_DOWN)
	{
		POnDown();
		//mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
	}//Pspeed(ָС���ٶ�) ����ٶ���������ﵽ����ٶȵ��෴���򱣳֡�
	if (_cmd & CMD_LEFT)
	{
		POnLeft();
		//mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
		//mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
	}//PForward��С��ÿ�μ�СPI/64 
	if (_cmd & CMD_RIGHT)
	{
		POnRight();
		//mciSendString(_TEXT("stop music1"), NULL, 0, NULL);
		//mciSendString(_TEXT("stop music2"), NULL, 0, NULL);
	}//PForward����ÿ������PI/64 
	if (_cmd & CMD_FLASH)		PPPPPflash();					//����
	if (_cmd & CMD_ATTACK)		PPPPPattack();
	//if (_cmd & CMD_MAGNET)		PPPPPmagnet();

	if (player)//���Ƶڶ���ң�ԭ��ͬ�ϡ�
	{
		if (_cmd & sCMD_UP)			COnUp();
		if (_cmd & sCMD_DOWN)		COnDown();
		if (_cmd & sCMD_LEFT)		COnLeft();
		if (_cmd & sCMD_RIGHT)		COnRight();
		if (_cmd & sCMD_FLASH)		CCCCCflash();					//����
		if (_cmd & sCMD_ATTACK)		CCCCCattack();
		//if (_cmd & sCMD_MAGNET)		CCCCCmagnet();
	}
	if (_cmd&CMD_PAUSE)
	{
		is_paused = true;
		PauseMenu();
	}
}