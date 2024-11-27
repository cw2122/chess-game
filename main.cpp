#include <iostream>
#include <graphics.h>
#include <vector>
#include "Gobang.h"
#include "ConnectSix.h"
using namespace std;

const int wWidth = 1000, wHeight = 700;  // 主界面宽度和高度
const int gameNums = 3;		// 当前游戏数量
const int gWidth = wWidth / 10, gHeight = wHeight / 6;
const char gameNames[gameNums][15] = { "五子棋", "六子棋", "引力四子棋"};
const char gameImageLoad[gameNums][100] = { "..\\图片资源\\Snipaste_2024-07-04_10-51-23.png", "..\\图片资源\\Snipaste_2024-07-04_11-12-38.png" };
vector<vector<int>> buttonNatures(gameNums, vector<int>(4));   // 主界面按钮属性
HWND wHandle;    // 主界面的窗口句柄


// 绘制主界面
void InterfaceDraws();
// 绘制按钮
void ButtonDraws(int x, int y);
// 消息捕获及分发
void MessCapture();

int main(void) {
	InterfaceDraws();		// 绘制主界面
	MessCapture();  // 消息捕获及分发

	return 0;
}

// 绘制主界面
void InterfaceDraws() {
	wHandle = initgraph(wWidth, wHeight, EX_SHOWCONSOLE);  // 绘制主界面
	setbkcolor(WHITE);  // 设置当前绘图设备背景色
	cleardevice();

	ButtonDraws(wWidth / 20, wHeight / 12); // 绘制按钮
}

// 绘制按钮
void ButtonDraws(int x, int y) {
	int startx = x, starty = y;
	setbkmode(TRANSPARENT);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID);
	settextcolor(BLACK);
	settextstyle(18, 0, "楷体");
	IMAGE img;
	for (int i = 0; i < gameNums; i++) {  // 按钮绘制
		if (i % 5 == 0) {
			startx = x; starty = y + (i / 5) * (2 * gHeight);
		}
		loadimage(&img, gameImageLoad[i], gWidth, gHeight);
		// fillroundrect(startx, starty, startx + gWidth, starty + gHeight, 5, 1);
		buttonNatures[i][0] = startx; buttonNatures[i][1] = starty; buttonNatures[i][2] = startx + gWidth; buttonNatures[i][3] = starty + gHeight;
		outtextxy(startx + (gWidth - textwidth(gameNames[i])) / 2, starty + gHeight, gameNames[i]);
		putimage(startx, starty, &img);
		startx += (2 * gWidth);
	}
}


// 消息捕获及分发
void MessCapture() {
	ExMessage msg;
	while (1) {
		getmessage(&msg, EX_MOUSE);
		switch (msg.message) {
		case WM_LBUTTONUP:
			if (msg.x > buttonNatures[0][0] && msg.y > buttonNatures[0][1] && msg.x < buttonNatures[0][2] && msg.y < buttonNatures[0][3]) {
				flushmessage(); // 清空消息缓冲区
				closegraph();   // 关闭主界面
				Gobang gamex(500, 800, 1000, 800);	// 五子棋游戏启动
				gamex.PK();
				InterfaceDraws();
			}
			else if (msg.x > buttonNatures[1][0] && msg.y > buttonNatures[1][1] && msg.x < buttonNatures[1][2] && msg.y < buttonNatures[1][3]) {
				flushmessage(); // 清空消息缓冲区
				closegraph();   // 关闭主界面
				ConnectSix gamex(500, 800, 1000, 800);		// 六子棋游戏启动
				gamex.PK();
				InterfaceDraws();
			}
			else if (msg.x > buttonNatures[2][0] && msg.y > buttonNatures[2][1] && msg.x < buttonNatures[2][2] && msg.y < buttonNatures[2][3]) {
				flushmessage(); // 清空消息缓冲区
				closegraph();   // 关闭主界面
								// 引力四子棋游戏启动
				InterfaceDraws();
			}
			break;
		default: break;
		}
		flushmessage();   // 从游戏里退出后清空消息缓冲区
	}
}