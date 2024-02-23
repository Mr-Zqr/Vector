#include "Nier.h"
/**********************由 陆星存 于2019年3月17、18日编辑*************/
void ReadAll1()
{

	Rank1 = fopen("文件\\排行榜\\1\\Rank1.txt", "r+");
	if (Rank1 != NULL)
	{
		fread(Name1, sizeof(Name1), 1, Rank1);
		fread(Lap1, sizeof(Lap1), 1, Rank1);
		fclose(Rank1);
		lap1 = atof(Lap1);
	}

	Rank2 = fopen("文件\\排行榜\\1\\Rank2.txt", "r+");
	if (Rank2 != NULL)
	{
		fread(Name2, sizeof(Name2), 1, Rank2);
		fread(Lap2, sizeof(Lap2), 1, Rank2);
		fclose(Rank2);
		lap2 = atof(Lap2);
	}

	Rank3 = fopen("文件\\排行榜\\1\\Rank3.txt", "r+");
	if (Rank3 != NULL)
	{
		fread(Name3, sizeof(Name3), 1, Rank3);
		fread(Lap3, sizeof(Lap3), 1, Rank3);
		fclose(Rank3);
		lap3 = atof(Lap3);
	}

	Rank4 = fopen("文件\\排行榜\\1\\Rank4.txt", "r+");
	if (Rank4 != NULL)
	{
		fread(Name4, sizeof(Name4), 1, Rank4);
		fread(Lap4, sizeof(Lap4), 1, Rank4);
		fclose(Rank4);
		lap4 = atof(Lap4);
	}

	Rank5 = fopen("文件\\排行榜\\1\\Rank5.txt", "r+");
	if (Rank5 != NULL)
	{
		fread(Name5, sizeof(Name5), 1, Rank5);
		fread(Lap5, sizeof(Lap5), 1, Rank5);
		fclose(Rank5);
		lap5 = atof(Lap5);
	}
}

void ReadAll2()
{

	Rank1 = fopen("文件\\排行榜\\2\\Rank1.txt", "r+");
	if (Rank1 != NULL)
	{
		fread(Name1, sizeof(Name1), 1, Rank1);
		fread(Lap1, sizeof(Lap1), 1, Rank1);
		fclose(Rank1);
		lap1 = atof(Lap1);
	}

	Rank2 = fopen("文件\\排行榜\\2\\Rank2.txt", "r+");
	if (Rank2 != NULL)
	{
		fread(Name2, sizeof(Name2), 1, Rank2);
		fread(Lap2, sizeof(Lap2), 1, Rank2);
		fclose(Rank2);
		lap2 = atof(Lap2);
	}

	Rank3 = fopen("文件\\排行榜\\2\\Rank3.txt", "r+");
	if (Rank3 != NULL)
	{
		fread(Name3, sizeof(Name3), 1, Rank3);
		fread(Lap3, sizeof(Lap3), 1, Rank3);
		fclose(Rank3);
		lap3 = atof(Lap3);
	}

	Rank4 = fopen("文件\\排行榜\\2\\Rank4.txt", "r+");
	if (Rank4 != NULL)
	{
		fread(Name4, sizeof(Name4), 1, Rank4);
		fread(Lap4, sizeof(Lap4), 1, Rank4);
		fclose(Rank4);
		lap4 = atof(Lap4);
	}

	Rank5 = fopen("文件\\排行榜\\2\\Rank5.txt", "r+");
	if (Rank5 != NULL)
	{
		fread(Name5, sizeof(Name5), 1, Rank5);
		fread(Lap5, sizeof(Lap5), 1, Rank5);
		fclose(Rank5);
		lap5 = atof(Lap5);
	}
}


void WriteAll1()
{

	Rank1 = fopen("文件\\排行榜\\1\\Rank1.txt", "w+");
	if (Rank1 != NULL)
	{
		sprintf_s(Lap1, "%.3f s", lap1);
		fwrite(Name1, sizeof(Name1), 1, Rank1);
		fwrite(Lap1, sizeof(Lap1), 1, Rank1);
		fclose(Rank1);
	}

	Rank2 = fopen("文件\\排行榜\\1\\Rank2.txt", "w+");
	if (Rank2 != NULL)
	{
		sprintf_s(Lap2, "%.3f s", lap2);
		fwrite(Name2, sizeof(Name2), 1, Rank2);
		fwrite(Lap2, sizeof(Lap2), 1, Rank2);
		fclose(Rank2);
	}

	Rank3 = fopen("文件\\排行榜\\1\\Rank3.txt", "w+");
	if (Rank3 != NULL)
	{
		sprintf_s(Lap3, "%.3f s", lap3);
		fwrite(Name3, sizeof(Name3), 1, Rank3);
		fwrite(Lap3, sizeof(Lap3), 1, Rank3);
		fclose(Rank3);
	}

	Rank4 = fopen("文件\\排行榜\\1\\Rank4.txt", "w+");
	if (Rank5 != NULL)
	{
		sprintf_s(Lap4, "%.3f s", lap4);
		fwrite(Name4, sizeof(Name4), 1, Rank4);
		fwrite(Lap4, sizeof(Lap4), 1, Rank4);
		fclose(Rank4);
	}

	Rank5 = fopen("文件\\排行榜\\1\\Rank5.txt", "w+");
	if (Rank5 != NULL)
	{
		sprintf_s(Lap5, "%.3f s", lap5);
		fwrite(Name5, sizeof(Name5), 1, Rank5);
		fwrite(Lap5, sizeof(Lap5), 1, Rank5);
		fclose(Rank5);
	}
}

void WriteAll2()
{

	Rank1 = fopen("文件\\排行榜\\2\\Rank1.txt", "w+");
	if (Rank1 != NULL)
	{
		sprintf_s(Lap1, "%.3f s", lap1);
		fwrite(Name1, sizeof(Name1), 1, Rank1);
		fwrite(Lap1, sizeof(Lap1), 1, Rank1);
		fclose(Rank1);
	}

	Rank2 = fopen("文件\\排行榜\\2\\Rank2.txt", "w+");
	if (Rank2 != NULL)
	{
		sprintf_s(Lap2, "%.3f s", lap2);
		fwrite(Name2, sizeof(Name2), 1, Rank2);
		fwrite(Lap2, sizeof(Lap2), 1, Rank2);
		fclose(Rank2);
	}

	Rank3 = fopen("文件\\排行榜\\2\\Rank3.txt", "w+");
	if (Rank3 != NULL)
	{
		sprintf_s(Lap3, "%.3f s", lap3);
		fwrite(Name3, sizeof(Name3), 1, Rank3);
		fwrite(Lap3, sizeof(Lap3), 1, Rank3);
		fclose(Rank3);
	}

	Rank4 = fopen("文件\\排行榜\\2\\Rank4.txt", "w+");
	if (Rank5 != NULL)
	{
		sprintf_s(Lap4, "%.3f s", lap4);
		fwrite(Name4, sizeof(Name4), 1, Rank4);
		fwrite(Lap4, sizeof(Lap4), 1, Rank4);
		fclose(Rank4);
	}

	Rank5 = fopen("文件\\排行榜\\2\\Rank5.txt", "w+");
	if (Rank5 != NULL)
	{
		sprintf_s(Lap5, "%.3f s", lap5);
		fwrite(Name5, sizeof(Name5), 1, Rank5);
		fwrite(Lap5, sizeof(Lap5), 1, Rank5);
		fclose(Rank5);
	}
}

void Sorry()
{
	loadimage(&Fail1, _T("文件\\排行榜\\1\\失败1.jpg"));
	if (map == 1)
	{
		cleardevice();
		BeginBatchDraw();
		while (true)
		{			
			putimage(0, 0, &Fail1);
			FlushBatchDraw();
			FlushMouseMsgBuffer();  //清空鼠标缓存
			ZanTingCaiDan = GetMouseMsg();
			if (ZanTingCaiDan.mkLButton)
				if (MouseTouch2(954, 640, 1110, 670, ZanTingCaiDan))
				{
					flag = 2;
					Init();
					MoShi();
					break;
				}
		}
		EndBatchDraw();
	}

	loadimage(&Fail2, _T("文件\\排行榜\\2\\失败2.jpg"));
	if (map == 2)
	{
		cleardevice();
		BeginBatchDraw();
		while (true)
		{
			putimage(0, 0, &Fail2);
			FlushBatchDraw();
			FlushMouseMsgBuffer();  //清空鼠标缓存
			ZanTingCaiDan = GetMouseMsg();
			if (ZanTingCaiDan.mkLButton)
				if (MouseTouch2(954, 640, 1110, 670,  ZanTingCaiDan))
				{
					flag = 2;
					Init();
					MoShi();
					break;
				}
		}
		EndBatchDraw();
	}
}

void LapShow(int i)
{
	cleardevice();
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	if (map == 1)
	{
			putimage(0, 0, &LIST1);
			switch (i)
			{
			case 1:
				settextcolor(RED);
				outtextxy(470, 170, Name1);
				outtextxy(720, 170, Lap1);
				settextcolor(BLACK);
				outtextxy(470, 270, Name2);
				outtextxy(720, 270, Lap2);
				outtextxy(470, 370, Name3);
				outtextxy(720, 370, Lap3);
				outtextxy(470, 470, Name4);
				outtextxy(720, 470, Lap4);
				outtextxy(470, 570, Name5);
				outtextxy(720, 570, Lap5);
				break;
			case 2:
				settextcolor(RED);
				outtextxy(470, 270, Name2);
				outtextxy(720, 270, Lap2);
				settextcolor(BLACK);
				outtextxy(470, 170, Name1);
				outtextxy(720, 170, Lap1);
				outtextxy(470, 370, Name3);
				outtextxy(720, 370, Lap3);
				outtextxy(470, 470, Name4);
				outtextxy(720, 470, Lap4);
				outtextxy(470, 570, Name5);
				outtextxy(720, 570, Lap5);
				break;
			case 3:
				settextcolor(RED);
				outtextxy(470, 370, Name3);
				outtextxy(720, 370, Lap3);
				settextcolor(BLACK);
				outtextxy(470, 170, Name1);
				outtextxy(720, 170, Lap1);
				outtextxy(470, 270, Name2);
				outtextxy(720, 270, Lap2);
				outtextxy(470, 470, Name4);
				outtextxy(720, 470, Lap4);
				outtextxy(470, 570, Name5);
				outtextxy(720, 570, Lap5);
				break;
			case 4:
				settextcolor(RED);
				outtextxy(470, 470, Name4);
				outtextxy(720, 470, Lap4);
				settextcolor(BLACK);
				outtextxy(470, 170, Name1);
				outtextxy(720, 170, Lap1);
				outtextxy(470, 370, Name3);
				outtextxy(720, 370, Lap3);
				outtextxy(470, 270, Name2);
				outtextxy(720, 270, Lap2);
				outtextxy(470, 570, Name5);
				outtextxy(720, 570, Lap5);
				break;
			case 5:
				settextcolor(RED);
				outtextxy(470, 570, Name5);
				outtextxy(720, 570, Lap5);
				settextcolor(BLACK);
				outtextxy(470, 170, Name1);
				outtextxy(720, 170, Lap1);
				outtextxy(470, 370, Name3);
				outtextxy(720, 370, Lap3);
				outtextxy(470, 270, Name2);
				outtextxy(720, 270, Lap2);
				outtextxy(470, 470, Name4);
				outtextxy(720, 470, Lap4);
				break;
			}
			FlushBatchDraw();
			while (true)
			{
			FlushMouseMsgBuffer();  //清空鼠标缓存
			ZanTingCaiDan = GetMouseMsg();
			if (ZanTingCaiDan.mkLButton)
				if (MouseTouch2(954, 640, 1110, 670, ZanTingCaiDan))
				{
					flag = 2;
					Init();
					MoShi();
					break;
				}
			}
	}
	if (map == 2)
	{
		putimage(0, 0, &LIST2);
		switch (i)
		{
		case 1:
			settextcolor(RED);
			outtextxy(470, 170, Name1);
			outtextxy(720, 170, Lap1);
			settextcolor(WHITE);
			outtextxy(470, 270, Name2);
			outtextxy(720, 270, Lap2);
			outtextxy(470, 370, Name3);
			outtextxy(720, 370, Lap3);
			outtextxy(470, 470, Name4);
			outtextxy(720, 470, Lap4);
			outtextxy(470, 570, Name5);
			outtextxy(720, 570, Lap5);
			break;
		case 2:
			settextcolor(RED);
			outtextxy(470, 270, Name2);
			outtextxy(720, 270, Lap2);
			settextcolor(WHITE);
			outtextxy(470, 170, Name1);
			outtextxy(720, 170, Lap1);
			outtextxy(470, 370, Name3);
			outtextxy(720, 370, Lap3);
			outtextxy(470, 470, Name4);
			outtextxy(720, 470, Lap4);
			outtextxy(470, 570, Name5);
			outtextxy(720, 570, Lap5);
			break;
		case 3:
			settextcolor(RED);
			outtextxy(470, 370, Name3);
			outtextxy(720, 370, Lap3);
			settextcolor(WHITE);
			outtextxy(470, 170, Name1);
			outtextxy(720, 170, Lap1);
			outtextxy(470, 270, Name2);
			outtextxy(720, 270, Lap2);
			outtextxy(470, 470, Name4);
			outtextxy(720, 470, Lap4);
			outtextxy(470, 570, Name5);
			outtextxy(720, 570, Lap5);
			break;
		case 4:
			settextcolor(RED);
			outtextxy(470, 470, Name4);
			outtextxy(720, 470, Lap4);
			settextcolor(WHITE);
			outtextxy(470, 170, Name1);
			outtextxy(720, 170, Lap1);
			outtextxy(470, 370, Name3);
			outtextxy(720, 370, Lap3);
			outtextxy(470, 270, Name2);
			outtextxy(720, 270, Lap2);
			outtextxy(470, 570, Name5);
			outtextxy(720, 570, Lap5);
			break;
		case 5:
			settextcolor(RED);
			outtextxy(470, 570, Name5);
			outtextxy(720, 570, Lap5);
			settextcolor(WHITE);
			outtextxy(470, 170, Name1);
			outtextxy(720, 170, Lap1);
			outtextxy(470, 370, Name3);
			outtextxy(720, 370, Lap3);
			outtextxy(470, 270, Name2);
			outtextxy(720, 270, Lap2);
			outtextxy(470, 470, Name4);
			outtextxy(720, 470, Lap4);
			break;
		}
		FlushBatchDraw();
		while (true)
		{
			FlushMouseMsgBuffer();  //清空鼠标缓存
			ZanTingCaiDan = GetMouseMsg();
			if (ZanTingCaiDan.mkLButton)
				if (MouseTouch2(954, 640, 1110, 670, ZanTingCaiDan))
				{
					flag = 2;
					Init();
					MoShi();
					break;
				}
		}
	}
	//EndBatchDraw();
}

void LapChange1(int i)
{
	char name[50] = { 0 };
	InputBox(name, 10, "请输入您的名字：", "恭喜您进入圈速榜前五");
	if (i == 1)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, Name3);
		strcpy(Name3, Name2);
		strcpy(Name2, Name1);
		strcpy(Name1, name);
		lap5 = lap4;
		lap4 = lap3;
		lap3 = lap2;
		lap2 = lap1;
		lap1 = Time;
		WriteAll1();
	}
	if (i == 2)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, Name3);
		strcpy(Name3, Name2);
		strcpy(Name2, name);
		lap5 = lap4;
		lap4 = lap3;
		lap3 = lap2;
		lap2 = Time;
		WriteAll1();
	}
	if (i == 3)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, Name3);
		strcpy(Name3, name);
		lap5 = lap4;
		lap4 = lap3;
		lap3 = Time;
		WriteAll1();
	}
	if (i == 4)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, name);
		lap5 = lap4;
		lap4 = Time;
		WriteAll1();
	}
	if (i == 5)
	{
		strcpy(Name5, name);
		lap5 = Time;
		WriteAll1();
	}
	ReadAll1();
}

void LapChange2(int i)
{
	char name[50] = { 0 };
	InputBox(name, 10, "请输入您的名字：", "恭喜您进入圈速榜前五");
	if (i == 1)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, Name3);
		strcpy(Name3, Name2);
		strcpy(Name2, Name1);
		strcpy(Name1, name);
		lap5 = lap4;
		lap4 = lap3;
		lap3 = lap2;
		lap2 = lap1;
		lap1 = Time;
		WriteAll2();
	}
	if (i == 2)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, Name3);
		strcpy(Name3, Name2);
		strcpy(Name2, name);
		lap5 = lap4;
		lap4 = lap3;
		lap3 = lap2;
		lap2 = Time;
		WriteAll2();
	}
	if (i == 3)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, Name3);
		strcpy(Name3, name);
		lap5 = lap4;
		lap4 = lap3;
		lap3 = Time;
		WriteAll2();
	}
	if (i == 4)
	{
		strcpy(Name5, Name4);
		strcpy(Name4, name);
		lap5 = lap4;
		lap4 = Time;
		WriteAll2();
	}
	if (i == 5)
	{
		strcpy(Name5, name);
		lap5 = Time;
		WriteAll2();
	}
	ReadAll2();
}
int Rank(double Time)
{
	if (Time < lap1)
	{
		return 1;
	}
	else if (Time < lap2)
	{
		return 2;
	}
	else if (Time < lap3)
	{
		return 3;
	}
	else if (Time < lap4)
	{
		return 4;
	}
	else if (Time < lap5)
	{
		return 5;
	}
	else
	{
		return 0;
	}
}