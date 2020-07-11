#include <stdio.h>
#include <graphics.h>
#define ROW 3
#define COL 3
#define CMINE 1
int SHOW[ROW][COL] = { 0 };
int MINE[ROW][COL] = { 0 };
int COUNT = 0;
int FLAG = 0;
int Number(int x, int y,int row, int col);
void Answer();
void drawNumber(int x, int y, int a);

void Display(int x,int y,int row,int col) {
	int count = 0;
	if (x >= 0 && y >= 0 && x < row && y < col) { //����Ϸ�
		if (SHOW[x][y] == 0) { //δչ����
			count=Number(x, y, row, col);
			if (MINE[x][y] != 1) { //��������û����
				if (count == 0) { //���������Ϊ�㣬չ���հ�
					SHOW[x][y] = 1;
					if (x > 1 && y > 1) {
						Display(x - 1, y - 1, row, col);
					}
					if (x > 1) {
						Display(x - 1, y, row, col);
					}
					if (x > 1 && y < col-1) {
						Display(x - 1, y + 1, row, col);
					}
					if (y > 1) {
						Display(x, y - 1, row, col);
					}
					if (y < col-1) {
						Display(x, y + 1, row, col);
					}
					if (x < row-1 && y>1) {
						Display(x + 1, y - 1, row, col);
					}
					if (x < row - 1) {
						Display(x + 1, y, row, col);
					}
					if (x < row - 1 && y < col - 1) {
						Display(x + 1, y + 1, row, col);
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

//A B C
//D X E
//F G H

int Number(int x, int y,int row, int col) {
	int count = 0;
	//H
	if (x + 1 < row && y + 1 < col) {
		if (MINE[x+1][y+1] == 1) {
			count++;
		}
	}
	//G
	if (x + 1 < row) {
		if (MINE[x+1][y] == 1) {
			count++;
		}
	}
	//F
	if (x + 1 < row && y - 1 >= 0) {
		if (MINE[x + 1][y - 1] == 1) {
			count++;
		}
	}
	//E
	if (y + 1 < col) {
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
	if (x - 1 >= 0 && y + 1 < col) {
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

void Random(int row, int col) {
	int x = 0, y = 0;
	for (int i = 0; i < CMINE; i++) {
		x = rand() % (row + 1); //��0��ROW-1�ķ�Χ�ڳ�ȡ�����
		y = rand() % (col + 1);
		if (MINE[x][y] == 0) { //����Ƿ�������Ƿ���֮ǰ��ͬ�����������������Ϊ0����ô���֮ǰ���ظ�
			MINE[x][y] = 1;
		}
		else {
			i--;
		}
	}
}

void Safe(int x, int y, int row, int col) {
	int i = 0, j = 0;
	if (MINE[x][y] == 1) {
		MINE[x][y] = 0;
		while (1) {
			i = rand() % (row + 1); //��0��ROW-1�ķ�Χ�ڳ�ȡ�����
			j = rand() % (col + 1);
			if (MINE[i][j] == 0) {
				MINE[i][j] = 1;
				break;
			}
		}
	}
}

int Result(int row, int col) {
	int correct = 0;
	if (FLAG == 0) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (SHOW[i][j] == 2) {
					if (MINE[i][j] == 1) {
						correct++;
					}
				}
			}
		}
		if (correct == CMINE) {
			return 1;
		}
		else if (COUNT == CMINE) {
			return 1;
		}
		else return 0;
	}
}

