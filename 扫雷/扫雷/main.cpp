#include <graphics.h>
#include <stdio.h>
#include <Gdiplus.h>

int SHOW[10][10] = { 0 };
int MINE[10][10] = { 0 };
int STEP = 0;//点开格子数
int FLAG = 0;
int COUNT = 0;
int CMINE = 0;
int ROW = 0;
int COL = 0;

void Print();
void Menu();//菜单界面
void Open();//点开格子或插旗
void Display(int x, int y);//
void drawNumber(int x,int y,int count);
void Answer();//游戏失败后告知用户地雷位置
int Number(int x, int y);
void Random();
void Safe(int x, int y);

void Safe(int x, int y)
{
	int i = 0, j = 0;
	if (MINE[x][y] == 1) {
		MINE[x][y] = 0;
		while (1) {
			i = rand() % (ROW + 1); //在0到ROW-1的范围内抽取随机数
			j = rand() % (COL + 1);
			if (MINE[i][j] == 0) {
				MINE[i][j] = 1;
				break;
			}
		}
	}
}

void Random() {
	int x = 0, y = 0;
	for (int i = 0; i < CMINE; i++) {
		x = rand() % (ROW + 1); //在0到ROW-1的范围内抽取随机数
		y = rand() % (COL + 1);
		if (MINE[x][y] == 0) { //检查是否随机数是否与之前相同，若随机数抽中坐标为0，则该处与之前不重复
			MINE[x][y] = 1;
		}
		else {
			i--;
		}
	}
}
//A B C
//D X E
//F G H
int Number(int x, int y)
{
	int count = 0;
	//H
	if (x + 1 < ROW && y + 1 < COL) {
		if (MINE[x + 1][y + 1] == 1) {
			count++;
		}
	}
	//G
	if (x + 1 < ROW) {
		if (MINE[x + 1][y] == 1) {
			count++;
		}
	}
	//F
	if (x + 1 < ROW && y - 1 >= 0) {
		if (MINE[x + 1][y - 1] == 1) {
			count++;
		}
	}
	//E
	if (y + 1 < COL) {
		if (MINE[x][y + 1] == 1) {
			count++;
		}
	}
	//D
	if (y - 1 >= 0) {
		if (MINE[x][y - 1] == 1) {
			count++;
		}
	}
	//C
	if (x - 1 >= 0 && y + 1 < COL) {
		if (MINE[x - 1][y + 1] == 1) {
			count++;
		}
	}
	//B
	if (x - 1 >= 0) {
		if (MINE[x - 1][y] == 1) {
			count++;
		}
	}
	//A
	if (x - 1 >= 0 && y - 1 >= 0) {
		if (MINE[x - 1][y - 1] == 1) {
			count++;
		}
	}
	return count;
}

void Display(int x, int y)
{
	int count = 0;
	if (x >= 0 && y >= 0 && x < ROW && y < COL) { //坐标合法
		if (SHOW[x][y] == 0) { //未展开过
			count = Number(x, y);
			if (MINE[x][y] != 1) { //该坐标下没有雷
				if (count == 0) { //方阵地雷数为零，展开空白
					SHOW[x][y] = 1;
					drawNumber(x, y, count);
					if (x > 0 && y > 0) {
						Display(x - 1, y - 1);
					}
					if (x > 0) {
						Display(x - 1, y);
					}
					if (x > 0 && y < COL - 1) {
						Display(x - 1, y + 1);
					}
					if (y > 0) {
						Display(x, y - 1);
					}
					if (y < COL - 1) {
						Display(x, y + 1);
					}
					if (x < ROW - 1 && y>0) {
						Display(x + 1, y - 1);
					}
					if (x < ROW - 1) {
						Display(x + 1, y);
					}
					if (x < ROW - 1 && y < COL - 1) {
						Display(x + 1, y + 1);
					}
				}
				else { //方阵地雷数不为零
					drawNumber(x, y, count);
				}
			}
			else { //该坐标下有雷
				Answer();
				exit(0);
			}
		}
	}
}

void Answer()//游戏失败后告知用户地雷位置
{
	int i, j;
	IMAGE mine;
	loadimage(&mine, L"mine.png", 30, 30);//地雷图片
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (MINE[i][j] == 1)
				putimage(i * 30, 50 + j * 30, &mine);
		}
	}
}

void drawNumber(int x, int y, int count)
{
	setlinecolor(LIGHTGRAY);//格子边框为灰色
	rectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);
	setfillcolor(RGB(220, 220, 220));//方框颜色
	fillrectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);//方框位置
	switch (count)
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

void Open()
{
	int point_x;//数组横坐标
	int point_y;//数组纵坐标
	IMAGE flag,lattice;
	loadimage(&flag, L"flag.png", 30, 30);//旗帜图片
	loadimage(&lattice, L"lattice.png", 30, 30);//方格图片

	MOUSEMSG m;//对鼠标的控制
	while (1)
	{
		m = GetMouseMsg();//鼠标位置
		if (m.uMsg == WM_LBUTTONDOWN)//左键
		{
			//返回选择难度界面
			if (m.x >= ((ROW * 30) / 2 - 35) && m.x <= ((ROW * 30) / 2 + 35) && m.y >= 10 && m.y <= 40)
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
					Safe(point_y,point_x);
					Display(point_y, point_x);
				}
				else if (SHOW[point_y][point_x]==0)//该处是未点开的格子
					Display(point_y, point_x);
			}
		}
		if (m.uMsg == WM_RBUTTONDOWN)//右键
		{
			point_x = m.x / 30;
			point_y = (m.y - 50) / 30;
			if (FLAG > 0 && SHOW[point_y][point_x] == 0)//插旗
			{
				putimage(point_x * 30, 50 + point_y * 30, &flag);
				FLAG--;
				SHOW[point_y][point_x] = 2;
			}
			else if (SHOW[point_y][point_x] == 2)//拔旗
			{
				putimage(point_x * 30, 50 + point_y * 30, &lattice);
				FLAG++;
				SHOW[point_y][point_x] = 0;
			}
			//提示旗子插完
		}
	}
}

void Print()
{
	//char s[5];//声明数组，用来存放字符串
	//TCHAR s[5];
	int i,j;

	initgraph(ROW * 30, 50 + COL * 30);//界面大小
	setbkcolor(RGB(220, 220, 220));//背景颜色
	cleardevice();   //清空之前图片
	IMAGE lattice,back;
	loadimage(&lattice, L"lattice.png", 30, 30);//方格图片
	loadimage(&back, L"back.jpg", 70, 30);//返回选择难度界面
	
	putimage((ROW * 30)/2-35, 10, &back);

	//settextcolor(RED);//文字红色
	//settextstyle(30, 0, 0);//文字大小
	//sprintf(s, "%d", flag);//将整型flag转换成字符串
	//outtextxy(40, 10, L"10");

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
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
				FLAG = 10;
				CMINE = 10;
				ROW = 10, COL = 10;
				Random();
				Print();//初级界面
				Open();
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 125 && m.y <= 175)
		{
			setlinecolor(LIGHTGRAY);//按键边框为灰色
			rectangle(95, 120, 205, 180);
			if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键点击，游戏开始
			{
				FLAG = 50;
				CMINE = 50;
				ROW = 20, COL = 20;
				Random();
				Print();//中级界面
				Open();
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 200 && m.y <= 250)
		{
			setlinecolor(LIGHTGRAY);//按键边框为灰色
			rectangle(95, 195, 205, 255);
			if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键点击，游戏开始
			{
				FLAG = 100;
				CMINE = 100;
				ROW = 30, COL = 20;
				Random();
				Print();//高级界面
				Open();
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