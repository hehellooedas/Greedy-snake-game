//贪吃蛇
#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h> 
#include <math.h>

#pragma comment (lib,"winmm.lib") //库文件
//mciSendString("open D:\\文件\\音乐\\大鱼.mp3 alias a",0,0,0);
//mciSendString("close a",0,0,0);
//srand(time(NULL));

#define SNAKE_NUM 500 //蛇的最大节数
//srand((unsigned)GetTickCount());
enum DIR //表示蛇的方向
{
	UP,DOWN,LEFT,RIGHT
};

struct Food //食物的结构
{
	int x, y,r; //食物的坐标和半径
	bool flag; //标记食物是否被吃
	DWORD color; //食物颜色
}food;

struct Snake //蛇的结构
{
	int size; //蛇的节数
	int dir = RIGHT; //蛇的方向,默认向右走
	int speed; //蛇的移动速度
	POINT coor[SNAKE_NUM]; //已经定义好的结构体
}snake;  //snake就是全局变量了

void GameInit()
{
	//初始化蛇
	initgraph(640, 480/*, SHOWCONSOLE*/); //初始化graph图形窗口
	snake.size = 3;
	snake.speed = 10;
	snake.dir;
	for (int i = 0; i < snake.size ; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
		//printf("?%d %d", snake.coor[i].x, snake.coor[i].y);
	}
	//初始化食物
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

void GameDraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119)); //设置背景颜色
	cleardevice(); //清除设备
	solidcircle(snake.coor[0].x,snake.coor[0].y,5);
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	// 绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

void snakeMove()
{
	//移动蛇
	for (int i = snake.size-1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}

	//snake.coor[0].x++; //蛇头位置自增
		//判断蛇应该移动的方向
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
	//通过键盘输入，改变贪吃蛇移动的方向
	// 判断键盘有没有按键
	if (_kbhit())  //如果有按键就返回真
	{
		//72 80 75 77上下左右键值
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
			//游戏暂停
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
	// 重新生成食物
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