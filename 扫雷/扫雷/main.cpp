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
int STEP = 0;//�㿪������
void Print(int x, int y);
void Menu();//�˵�����
void Open(int x,int y);//�㿪���ӻ����
int Display(int x, int y);//
void drawNumber(int x,int y,int a);

void drawNumber(int x, int y, int a)
{
	setlinecolor(LIGHTGRAY);//���ӱ߿�Ϊ��ɫ
	rectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);
	setfillcolor(RGB(220, 220, 220));//������ɫ
	fillrectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);//����λ��
	switch (a)
	{
	case 0:
		break;
	case 1:
		settextcolor(BLUE);//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"1");
		break;
	case 2:
		settextcolor(GREEN);//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"2");
		break;
	case 3:
		settextcolor(RED);//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"3");
		break;
	case 4:
		settextcolor(RGB(255, 140, 0));//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"4");
		break;
	case 5:
		settextcolor(RGB(255, 192, 203));//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"5");
		break;
	case 6:
		settextcolor(YELLOW);//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"6");
		break;
	case 7:
		settextcolor(RGB(160, 32, 240));//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
		outtextxy(x * 30 + 10, 50 + y * 30 + 5, L"7");
		break;
	case 8:
		settextcolor(BLACK);//������ɫ
		settextstyle(25, 0, 0);//���ִ�С
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
	int point_x;//���������
	int point_y;//����������

	MOUSEMSG m;//�����Ŀ���
	while (1)
	{
		m = GetMouseMsg();//���λ��
		if (m.uMsg == WM_LBUTTONDOWN)//���
		{
			//����ѡ���ѶȽ���
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
	//char s[5];//�������飬��������ַ���
	//TCHAR s[5];
	int i,j;

	initgraph(row * 30, 50 + column * 30);//�����С
	setbkcolor(RGB(220, 220, 220));//������ɫ
	cleardevice();   //���֮ǰͼƬ
	IMAGE lattice,back,mine,flag;
	loadimage(&lattice, L"lattice.png", 30, 30);//����ͼƬ
	loadimage(&back, L"back.jpg", 30, 30);//����ѡ���ѶȽ���
	loadimage(&mine, L"mine.png", 30, 30);//����ͼƬ
	loadimage(&flag, L"flag.png", 30, 30);//����ͼƬ
	putimage((row * 30)/2-15, 10, &back);

	//settextcolor(RED);//���ֺ�ɫ
	//settextstyle(30, 0, 0);//���ִ�С
	//sprintf(s, "%d", flag);//������flagת�����ַ���
	//outtextxy(40, 10, L"10");

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			putimage(i * 30, 50 + j * 30, &lattice);
		}
	}
}

void Menu()//�˵�����
{
	initgraph(300, 300);//�����С
	setbkcolor(RGB(220, 220, 220));//������ɫ
	cleardevice();
	setfillcolor(RGB(100, 149, 237));//������ɫ
	fillrectangle(100, 50, 200, 100);//����λ��
	fillrectangle(100, 125, 200, 175);
	fillrectangle(100, 200, 200, 250);
	setlinecolor(WHITE);//�����߿�Ϊ��ɫ
	rectangle(95, 45, 205, 105);
	rectangle(95, 120, 205, 180);
	rectangle(95, 195, 205, 255);
	
	settextstyle(25, 0, L"����");
	setbkmode(TRANSPARENT);//���ֱ���Ϊ͸��
	settextcolor(WHITE);//���ְ�ɫ
	settextstyle(30, 0, 0);//���ִ�С
	outtextxy(120, 60, L"����");
	outtextxy(120, 135, L"�м�");
	outtextxy(120, 210, L"�߼�");

	MOUSEMSG m;//�����Ŀ���
	
	while (1)
	{
		m = GetMouseMsg();//���λ��
		if (m.x >= 100 && m.x <= 200 && m.y >= 50 && m.y <= 100)
		{
			setlinecolor(LIGHTGRAY);//�����߿�Ϊ��ɫ
			rectangle(95, 45, 205, 105);
			if (m.uMsg == WM_LBUTTONDOWN)//�������������Ϸ��ʼ
			{
				Print(10,10);//��������
				Open(10, 10);
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 125 && m.y <= 175)
		{
			setlinecolor(LIGHTGRAY);//�����߿�Ϊ��ɫ
			rectangle(95, 120, 205, 180);
			if (m.uMsg == WM_LBUTTONDOWN)//�������������Ϸ��ʼ
			{
				Print(20, 20);//�м�����
				Open(20, 20);
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 200 && m.y <= 250)
		{
			setlinecolor(LIGHTGRAY);//�����߿�Ϊ��ɫ
			rectangle(95, 195, 205, 255);
			if (m.uMsg == WM_LBUTTONDOWN)//�������������Ϸ��ʼ
			{
				Print(30, 20);//�߼�����
				Open(30, 20);
				break;
			}
		}
		else
		{
			//�����߿�Ϊ��ɫ
			setlinecolor(WHITE);
			rectangle(95, 45, 205, 105);
			rectangle(95, 120, 205, 180);
			rectangle(95, 195, 205, 255);
		}
		
	}
}


int main()
{
	Menu();//��ӡ�˵�
	//Print(10, 10);
	
	getchar();//�س��˳�
}