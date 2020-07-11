#include <graphics.h>
#include <stdio.h>
#include <Gdiplus.h>

int a[10][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				  { 1, 0, 0, 0, 0, 0, 0, 0, 4, 1 },
				  { 1, 2, 0, 3, 3, 3, 0, 0, 4, 1 },
				  { 1, 0, 0, 0, 0, 0, 0, 0, 4, 1 },
				  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
int STEP = 0;//点开格子数
void Print(int x, int y);
void Menu();//菜单界面
void Open(int x,int y);//点开格子或插旗
int Display(int x, int y);//
void drawNumber(int x,int y,int a);

void drawNumber(int x, int y, int a)
{
	setlinecolor(LIGHTGRAY);//格子边框为灰色
	rectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);
	setfillcolor(RGB(220, 220, 220));//方框颜色
	fillrectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);//方框位置
	switch (a)
	{
	case 0:
		break;
	case 1:
		settextcolor(BLUE);//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"1");
		break;
	case 2:
		settextcolor(GREEN);//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"2");
		break;
	case 3:
		settextcolor(RED);//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"3");
		break;
	case 4:
		settextcolor(RGB(255, 140, 0));//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"4");
		break;
	case 5:
		settextcolor(RGB(255, 192, 203));//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"5");
		break;
	case 6:
		settextcolor(YELLOW);//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"6");
		break;
	case 7:
		settextcolor(RGB(160, 32, 240));//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"7");
		break;
	case 8:
		settextcolor(BLACK);//数字颜色
		settextstyle(25, 0, 0);//数字大小
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"8");
		break;
	default:
		break;
	}
}

void Open(int x, int y)
{
	int row = x;
	int column = y;
	int point_x;//数组横坐标
	int point_y;//数组纵坐标

	MOUSEMSG m;//对鼠标的控制
	while (1)
	{
		m = GetMouseMsg();//鼠标位置
		if (m.uMsg == WM_LBUTTONDOWN)//左键
		{
			//返回选择难度界面
			if (m.x >= ((row * 30) / 2 - 15) && m.x <= ((row * 30) / 2 + 15) && m.y >= 10 && m.y <= 40)
			{
				Menu();
				break;
			}
			if (m.y > 50)
			{
				point_x = m.x / 30;
				point_y = (m.y - 50) / 30;
				STEP++;
				if (STEP==1)
				{

				}
				else
				{
					drawNumber(point_x, point_y, Display(point_x, point_y));
				}
			}
		}

	}
}

void Print(int x,int y)
{
	int row = x;
	int column = y;
	//char s[5];//声明数组，用来存放字符串
	//TCHAR s[5];
	int i,j;

	initgraph(row * 30, 50 + column * 30);//界面大小
	setbkcolor(RGB(220, 220, 220));//背景颜色
	cleardevice();   //清空之前图片
	IMAGE lattice,back,mine,flag;
	loadimage(&lattice, L"lattice.png", 30, 30);//方格图片
	loadimage(&back, L"back.jpg", 30, 30);//返回选择难度界面
	loadimage(&mine, L"mine.png", 30, 30);//地雷图片
	loadimage(&flag, L"flag.png", 30, 30);//旗帜图片
	putimage((row * 30)/2-15, 10, &back);

	//settextcolor(RED);//文字红色
	//settextstyle(30, 0, 0);//文字大小
	//sprintf(s, "%d", flag);//将整型flag转换成字符串
	//outtextxy(40, 10, L"10");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			putimage(i * 30, 50 + j * 30, &lattice);
		}
	}
}

void Menu()//菜单界面
{
	initgraph(300, 300);//界面大小
	setbkcolor(RGB(220, 220, 220));//背景颜色
	cleardevice();
	setfillcolor(RGB(100, 149, 237));//方框颜色
	fillrectangle(100, 50, 200, 100);//方框位置
	fillrectangle(100, 125, 200, 175);
	fillrectangle(100, 200, 200, 250);
	setlinecolor(WHITE);//按键边框为白色
	rectangle(95, 45, 205, 105);
	rectangle(95, 120, 205, 180);
	rectangle(95, 195, 205, 255);
	
	settextstyle(25, 0, L"楷体");
	setbkmode(TRANSPARENT);//文字背景为透明
	settextcolor(WHITE);//文字白色
	settextstyle(30, 0, 0);//文字大小
	outtextxy(120, 60, L"初级");
	outtextxy(120, 135, L"中级");
	outtextxy(120, 210, L"高级");

	MOUSEMSG m;//对鼠标的控制
	
	while (1)
	{
		m = GetMouseMsg();//鼠标位置
		if (m.x >= 100 && m.x <= 200 && m.y >= 50 && m.y <= 100)
		{
			setlinecolor(LIGHTGRAY);//按键边框为灰色
			rectangle(95, 45, 205, 105);
			if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键点击，游戏开始
			{
				Print(10,10);//初级界面
				Open(10, 10);
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 125 && m.y <= 175)
		{
			setlinecolor(LIGHTGRAY);//按键边框为灰色
			rectangle(95, 120, 205, 180);
			if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键点击，游戏开始
			{
				Print(20, 20);//中级界面
				Open(20, 20);
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 200 && m.y <= 250)
		{
			setlinecolor(LIGHTGRAY);//按键边框为灰色
			rectangle(95, 195, 205, 255);
			if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键点击，游戏开始
			{
				Print(30, 20);//高级界面
				Open(30, 20);
				break;
			}
		}
		else
		{
			//按键边框为白色
			setlinecolor(WHITE);
			rectangle(95, 45, 205, 105);
			rectangle(95, 120, 205, 180);
			rectangle(95, 195, 205, 255);
		}
		
	}
}


int main()
{
	Menu();//打印菜单
	//Print(10, 10);
	
	getchar();//回车退出
}