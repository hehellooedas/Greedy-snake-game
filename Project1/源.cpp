//̰����
#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h> 
#include <math.h>

#pragma comment (lib,"winmm.lib") //���ļ�
//mciSendString("open D:\\�ļ�\\����\\����.mp3 alias a",0,0,0);
//mciSendString("close a",0,0,0);
//srand(time(NULL));

#define SNAKE_NUM 500 //�ߵ�������
//srand((unsigned)GetTickCount());
enum DIR //��ʾ�ߵķ���
{
	UP,DOWN,LEFT,RIGHT
};

struct Food //ʳ��Ľṹ
{
	int x, y,r; //ʳ�������Ͱ뾶
	bool flag; //���ʳ���Ƿ񱻳�
	DWORD color; //ʳ����ɫ
}food;

struct Snake //�ߵĽṹ
{
	int size; //�ߵĽ���
	int dir = RIGHT; //�ߵķ���,Ĭ��������
	int speed; //�ߵ��ƶ��ٶ�
	POINT coor[SNAKE_NUM]; //�Ѿ�����õĽṹ��
}snake;  //snake����ȫ�ֱ�����

void GameInit()
{
	//��ʼ����
	initgraph(640, 480/*, SHOWCONSOLE*/); //��ʼ��graphͼ�δ���
	snake.size = 3;
	snake.speed = 10;
	snake.dir;
	for (int i = 0; i < snake.size ; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
		//printf("?%d %d", snake.coor[i].x, snake.coor[i].y);
	}
	//��ʼ��ʳ��
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

void GameDraw()
{
	//˫�����ͼ
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119)); //���ñ�����ɫ
	cleardevice(); //����豸
	solidcircle(snake.coor[0].x,snake.coor[0].y,5);
	//������
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	// ����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

void snakeMove()
{
	//�ƶ���
	for (int i = snake.size-1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}

	//snake.coor[0].x++; //��ͷλ������
		//�ж���Ӧ���ƶ��ķ���
	switch (snake.dir)
	{
	case UP: 
		snake.coor[0].y-= snake.speed;
		if (snake.coor[0].y+10 <= 0) snake.coor[0].y = 480;
		break;
	case DOWN: 
		snake.coor[0].y+= snake.speed;
		if (snake.coor[0].y - 10 >= 480) snake.coor[0].y=0;
		break;
	case LEFT: 
		snake.coor[0].x-= snake.speed;
		if (snake.coor[0].x + 10 <= 0) snake.coor[0].x = 640;
		break;
	case RIGHT:
		snake.coor[0].x+= snake.speed;
		if (snake.coor[0].x - 10 >= 640) snake.coor[0].x = 0;
		break;
	}
}

void keyControl()
{
	//ͨ���������룬�ı�̰�����ƶ��ķ���
	// �жϼ�����û�а���
	if (_kbhit())  //����а����ͷ�����
	{
		//72 80 75 77�������Ҽ�ֵ
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN) { snake.dir = UP; break; }
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP) { snake.dir = DOWN; break; }
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT) { snake.dir = LEFT; break; }
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT) { snake.dir = RIGHT; break; }
		case ' ':
			//��Ϸ��ͣ
			while (1)
			{
				if (_getch() == ' ') return;
			}
		}
	}
}

void EatFood()
{
	if (food.flag&&hypot(snake.coor[0].x-food.x,snake.coor[0].y-food.y) <= food.r + 1)
	{
		food.flag = false;
		snake.size++;
	}
	// ��������ʳ��
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}

int main(void)
{
	GameInit();
	while (1)
	{
		GameDraw();
		snakeMove();
		keyControl();
		EatFood();
		Sleep(50);
	}
	system("pause");
	return 0;
}