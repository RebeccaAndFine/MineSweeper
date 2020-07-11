#include <graphics.h>
#include <stdio.h>
#include <Gdiplus.h>

int SHOW[10][10] = { 0 };
int MINE[10][10] = { 0 };
int STEP = 0;//�㿪������
int FLAG = 0;
int COUNT = 0;
int CMINE = 0;
int ROW = 0;
int COL = 0;

void Print();
void Menu();//�˵�����
void Open();//�㿪���ӻ����
void Display(int x, int y);//
void drawNumber(int x,int y,int count);
void Answer();//��Ϸʧ�ܺ��֪�û�����λ��
int Number(int x, int y);
void Random();
void Safe(int x, int y);

void Safe(int x, int y)
{
	int i = 0, j = 0;
	if (MINE[x][y] == 1) {
		MINE[x][y] = 0;
		while (1) {
			i = rand() % (ROW + 1); //��0��ROW-1�ķ�Χ�ڳ�ȡ�����
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
		x = rand() % (ROW + 1); //��0��ROW-1�ķ�Χ�ڳ�ȡ�����
		y = rand() % (COL + 1);
		if (MINE[x][y] == 0) { //����Ƿ�������Ƿ���֮ǰ��ͬ�����������������Ϊ0����ô���֮ǰ���ظ�
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
	if (x >= 0 && y >= 0 && x < ROW && y < COL) { //����Ϸ�
		if (SHOW[x][y] == 0) { //δչ����
			count = Number(x, y);
			if (MINE[x][y] != 1) { //��������û����
				if (count == 0) { //���������Ϊ�㣬չ���հ�
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
				else { //�����������Ϊ��
					drawNumber(x, y, count);
				}
			}
			else { //������������
				Answer();
				exit(0);
			}
		}
	}
}

void Answer()//��Ϸʧ�ܺ��֪�û�����λ��
{
	int i, j;
	IMAGE mine;
	loadimage(&mine, L"mine.png", 30, 30);//����ͼƬ
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
	setlinecolor(LIGHTGRAY);//���ӱ߿�Ϊ��ɫ
	rectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);
	setfillcolor(RGB(220, 220, 220));//������ɫ
	fillrectangle(x * 30, 50 + y * 30, 30 + x * 30, 50 + 30 + y * 30);//����λ��
	switch (count)
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

void Open()
{
	int point_x;//���������
	int point_y;//����������
	IMAGE flag,lattice;
	loadimage(&flag, L"flag.png", 30, 30);//����ͼƬ
	loadimage(&lattice, L"lattice.png", 30, 30);//����ͼƬ

	MOUSEMSG m;//�����Ŀ���
	while (1)
	{
		m = GetMouseMsg();//���λ��
		if (m.uMsg == WM_LBUTTONDOWN)//���
		{
			//����ѡ���ѶȽ���
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
				else if (SHOW[point_y][point_x]==0)//�ô���δ�㿪�ĸ���
					Display(point_y, point_x);
			}
		}
		if (m.uMsg == WM_RBUTTONDOWN)//�Ҽ�
		{
			point_x = m.x / 30;
			point_y = (m.y - 50) / 30;
			if (FLAG > 0 && SHOW[point_y][point_x] == 0)//����
			{
				putimage(point_x * 30, 50 + point_y * 30, &flag);
				FLAG--;
				SHOW[point_y][point_x] = 2;
			}
			else if (SHOW[point_y][point_x] == 2)//����
			{
				putimage(point_x * 30, 50 + point_y * 30, &lattice);
				FLAG++;
				SHOW[point_y][point_x] = 0;
			}
			//��ʾ���Ӳ���
		}
	}
}

void Print()
{
	//char s[5];//�������飬��������ַ���
	//TCHAR s[5];
	int i,j;

	initgraph(ROW * 30, 50 + COL * 30);//�����С
	setbkcolor(RGB(220, 220, 220));//������ɫ
	cleardevice();   //���֮ǰͼƬ
	IMAGE lattice,back;
	loadimage(&lattice, L"lattice.png", 30, 30);//����ͼƬ
	loadimage(&back, L"back.jpg", 70, 30);//����ѡ���ѶȽ���
	
	putimage((ROW * 30)/2-35, 10, &back);

	//settextcolor(RED);//���ֺ�ɫ
	//settextstyle(30, 0, 0);//���ִ�С
	//sprintf(s, "%d", flag);//������flagת�����ַ���
	//outtextxy(40, 10, L"10");

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
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
				FLAG = 10;
				CMINE = 10;
				ROW = 10, COL = 10;
				Random();
				Print();//��������
				Open();
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 125 && m.y <= 175)
		{
			setlinecolor(LIGHTGRAY);//�����߿�Ϊ��ɫ
			rectangle(95, 120, 205, 180);
			if (m.uMsg == WM_LBUTTONDOWN)//�������������Ϸ��ʼ
			{
				FLAG = 50;
				CMINE = 50;
				ROW = 20, COL = 20;
				Random();
				Print();//�м�����
				Open();
				break;
			}
		}
		else if (m.x >= 100 && m.x <= 200 && m.y >= 200 && m.y <= 250)
		{
			setlinecolor(LIGHTGRAY);//�����߿�Ϊ��ɫ
			rectangle(95, 195, 205, 255);
			if (m.uMsg == WM_LBUTTONDOWN)//�������������Ϸ��ʼ
			{
				FLAG = 100;
				CMINE = 100;
				ROW = 30, COL = 20;
				Random();
				Print();//�߼�����
				Open();
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