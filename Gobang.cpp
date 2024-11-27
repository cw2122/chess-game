#include <vector>
#include <graphics.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Gobang.h"
using namespace std;

// 开始pk函数
void Gobang::PK() {
	w_id = 0;
	createOneWindows();
	messageControl();
	closegraph();
}

// 一级界面创建函数
void Gobang::createOneWindows() {
	w_id = 0;
	wHandle = initgraph(wWidth[0], wHeight[0], EW_SHOWCONSOLE);
	// 设置窗口名称
	SetWindowText(wHandle, "五子棋游戏");
	// 设置窗口背景
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	// 贴图
	IMAGE img;
	loadimage(&img, "..\\图片资源\\Snipaste_2024-07-04_10-51-23.png", wWidth[0], wHeight[0]);
	putimage(0, 0, &img);
	// 设置窗口按钮
	setOneButton();
}

// 二级界面创建函数
void Gobang::createTwoWindows(int windowsId) {
	w_id = windowsId;
	wHandle = initgraph(wWidth[1], wHeight[1], EW_SHOWCONSOLE);
	// 设置窗口名称
	SetWindowText(wHandle, "五子棋游戏");
	// 设置窗口背景
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	if (windowsId < 4) {
		gridOriginal(); // 棋盘初始化
		// 绘制棋盘
		drawBoard();
	}
	// 设置窗口按钮
	switch (windowsId)
	{
	case 1:
		setTwoButton(); break;
	case 2:
		setThreeButton(); break;
	case 3:
		setFourButton(); break;
	case 4:
		setFiveButton(); break;
	default:
		break;
	}
}

// 一号窗口按钮设置
void Gobang::setOneButton() {
	// 图像放置

	// 按钮设置
	int buttonWidth = wWidth[w_id] / 3, buttonHeight = wHeight[w_id] / 5 * 2 / 4 / 2;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(250, 165, 118));
	setfillstyle(BS_SOLID);
	settextcolor(BLACK);
	settextstyle(buttonHeight / 2, 0, "楷体", 0, 0, 1000, false, false, false);
	startx = (wWidth[w_id] - buttonWidth) / 2; starty = wHeight[w_id] / 5 * 3 + buttonHeight / 2;
	for (int i = 0; i < 4; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// 保存按钮i的起止点坐标
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i]);
		tHeight = textheight(buttonName[i]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i]);
		starty += (buttonHeight * 2);
	}
	// 返回按钮
	startx += (buttonWidth + 10);
	starty -= (buttonHeight * 2);
	fillroundrect(startx, starty, startx + buttonWidth / 2, starty + buttonHeight, 10, 6);
	wButton[w_id][4][0] = startx; wButton[w_id][4][1] = starty; wButton[w_id][4][2] = startx + buttonWidth / 2; wButton[w_id][4][3] = starty + buttonHeight;
	tWidth = textwidth("返回");
	tHeight = textheight("返回");
	t_startx = startx + (buttonWidth / 2 - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
	outtextxy(t_startx, t_starty, "返回");
}

// 二号窗口按钮设置
void Gobang::setTwoButton() {
	// 图像放置

	// 按钮设置(目前四个)
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "楷体", 0, 0, 1000, false, false, false);
	startx = gridWidth / 16; starty = 50 + gridWidth + 40;
	for (int i = 0; i < 4; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// 保存按钮i的起止点坐标
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 4]);
		tHeight = textheight(buttonName[i + 4]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 4]);
		startx += (buttonWidth * 2);
	}
}

// 三号窗口按钮设置
void Gobang::setThreeButton() {
	// 图像放置

	// 按钮设置(目前六个)
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "楷体", 0, 0, 1000, false, false, false);
	startx = gridWidth / 16; starty = 50 + gridWidth + 40;
	for (int i = 0; i < 4; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// 保存按钮i的起止点坐标
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 4]);
		tHeight = textheight(buttonName[i + 4]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 4]);
		startx += (buttonWidth * 2);
	}
	startx = 800 + (200 - buttonWidth) / 2; starty = 50;
	for (int i = 0; i < 2; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		wButton[w_id][i + 4][0] = startx; wButton[w_id][i + 4][1] = starty; wButton[w_id][i + 4][2] = startx + buttonWidth; wButton[w_id][i + 4][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 8]);
		tHeight = textheight(buttonName[i + 8]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 8]);
		starty += (buttonHeight * 2);
	}

	// botId显示初始化
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体", 0, 0, 1000, false, false, false);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(wButton[2][5][0] - 20, wButton[2][5][3] + 15, "电脑:");
	outtextxy(wButton[2][5][0] - 20 + textwidth("电脑:"), wButton[2][5][3] + 15, botName[botId]);
}

// 四号窗口按钮设置
void Gobang::setFourButton() {
	// 图像放置

	// 按钮设置(目前六个)
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "楷体", 0, 0, 1000, false, false, false);
	startx = gridWidth / 16; starty = 50 + gridWidth + 40;
	for (int i = 0; i < 3; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// 保存按钮i的起止点坐标
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 4]);
		tHeight = textheight(buttonName[i + 4]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 4]);
		startx += (buttonWidth * 2);
	}
	fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
	// 保存按钮i的起止点坐标
	wButton[w_id][3][0] = startx; wButton[w_id][3][1] = starty; wButton[w_id][3][2] = startx + buttonWidth; wButton[w_id][3][3] = starty + buttonHeight;
	tWidth = textwidth(buttonName[10]);
	tHeight = textheight(buttonName[10]);
	t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
	outtextxy(t_startx, t_starty, buttonName[10]);

	startx = 800 + (200 - buttonWidth) / 2; starty = 50;
	for (int i = 0; i < 3; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		wButton[w_id][i + 4][0] = startx; wButton[w_id][i + 4][1] = starty; wButton[w_id][i + 4][2] = startx + buttonWidth; wButton[w_id][i + 4][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 11]);
		tHeight = textheight(buttonName[i + 11]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 11]);
		starty += (buttonHeight * 2);
	}

	// botId_1, botId_2显示初始化
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体", 0, 0, 1000, false, false, false);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 20, "甲方:");
	outtextxy(wButton[3][6][0] - 20 + textwidth("甲方:"), wButton[3][6][3] + 20, botName[botId_1]);
	outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 60, "乙方:");
	outtextxy(wButton[3][6][0] - 20 + textwidth("乙方:"), wButton[3][6][3] + 60, botName[botId_2]);
}

// 五号窗口按钮设置
void Gobang::setFiveButton() {
	// 帮助文档
	settextcolor(BLACK);
	settextstyle(100, 0, "楷体", 0, 0, 1000, false, false, false);
	outtextxy((wWidth[1] - textwidth("什么都没有了，哈哈")) / 2, (wHeight[1] - textheight("什么都没有了，哈哈")) / 2, "什么都没有了，哈哈");
	// 返回按钮
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "楷体", 0, 0, 1000, false, false, false);
	startx = (wWidth[1] - buttonWidth) / 2; starty = 50 + gridWidth + 40;
	fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
	// 保存按钮i的起止点坐标
	wButton[w_id][0][0] = startx; wButton[w_id][0][1] = starty; wButton[w_id][0][2] = startx + buttonWidth; wButton[w_id][0][3] = starty + buttonHeight;
	tWidth = textwidth("返回");
	tHeight = textheight("返回");
	t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
	outtextxy(t_startx, t_starty, "返回");
}

// 一号窗口消息执行函数
void Gobang::msgExecuteOne() {
	switch (msg.message)
	{  // 消息类别分发处理
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[0][0][0] && msg.y > wButton[0][0][1] && msg.x < wButton[0][0][2] && msg.y < wButton[0][0][3]) {
			changeWindows(1);  // “人对人”按钮，切换界面
		}
		else if (msg.x > wButton[0][1][0] && msg.y > wButton[0][1][1] && msg.x < wButton[0][1][2] && msg.y < wButton[0][1][3]) {
			changeWindows(2);  // “人对电脑”按钮，切换界面
		}
		else if (msg.x > wButton[0][2][0] && msg.y > wButton[0][2][1] && msg.x < wButton[0][2][2] && msg.y < wButton[0][2][3]) {
			changeWindows(3);  // “电脑对电脑”按钮，切换界面
		}
		else if (msg.x > wButton[0][3][0] && msg.y > wButton[0][3][1] && msg.x < wButton[0][3][2] && msg.y < wButton[0][3][3]) {
			changeWindows(4);  // “帮助”按钮，切换界面
		}
		else if (msg.x > wButton[0][4][0] && msg.y > wButton[0][4][1] && msg.x < wButton[0][4][2] && msg.y < wButton[0][4][3]) {
			gameState = 0;	   // “返回”按钮， 切回主界面
		}
		break;
	default:
		break;
	}
}

// 二号窗口消息执行函数
void Gobang::msgExecuteTwo() {
	switch (msg.message)
	{  // 消息类别分发处理
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[1][0][0] && msg.y > wButton[1][0][1] && msg.x < wButton[1][0][2] && msg.y < wButton[1][0][3]) {
			setbkcolor(WHITE);
			cleardevice();  // “重置棋盘”按钮，复原棋盘
			drawBoard();
			setTwoButton();
			gridOriginal();
		}
		else if (msg.x > wButton[1][1][0] && msg.y > wButton[1][1][1] && msg.x < wButton[1][1][2] && msg.y < wButton[1][1][3]) {
			if (gridState == 0)
				gridState = 1;	// “开始对局”按钮，开始对局
		}
		else if (msg.x > wButton[1][2][0] && msg.y > wButton[1][2][1] && msg.x < wButton[1][2][2] && msg.y < wButton[1][2][3]) {
			gridOriginal();
			changeWindows(0);  // “返回”按钮，返回上一级界面
		}
		else if (msg.x > wButton[1][3][0] && msg.y > wButton[1][3][1] && msg.x < wButton[1][3][2] && msg.y < wButton[1][3][3]) {
			if (gridState) {
				GridBack();// 悔棋一步
			}
		}
		else if (msg.x > xstart - lattic / 2 && msg.x < xstart + 14 * lattic + lattic / 2 && msg.y > ystart - lattic / 2 && msg.y < ystart + 14 * lattic + lattic / 2) {
			if (gridState == 1) {
				if (!playChess(msg.x - (xstart - lattic / 2), msg.y - (ystart - lattic / 2)))
					break;
				if (isEnd()) {
					gridState = 2;
				}
				flushmessage();
			}
		}
		break;
	default:
		break;
	}
}

// 三号窗口消息执行函数
void Gobang::msgExecuteThree() {
	switch (msg.message)
	{  // 消息类别分发处理
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[2][0][0] && msg.y > wButton[2][0][1] && msg.x < wButton[2][0][2] && msg.y < wButton[2][0][3]) {
			setbkcolor(WHITE);
			cleardevice();  // “重置棋盘”按钮，复原棋盘
			drawBoard();
			setThreeButton();
			gridOriginal();
		}
		else if (msg.x > wButton[2][1][0] && msg.y > wButton[2][1][1] && msg.x < wButton[2][1][2] && msg.y < wButton[2][1][3]) {
			if (gridState == 0) {
				gridState = 1;	// “开始对局”按钮，开始对局
				if (ourBackupTeam) {
					int X = -1, Y = -1;
					int gridtemp[15][15] = { 0 };
					copy(gridtemp);
					switch (botId) {
					case 1: Bot1(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 2: Bot2(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 3: Bot3(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 4: Bot4(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 5: Bot5(gridtemp, Rounds, chesscolor, X, Y);
						break;
					}
					if (!isFair(X, Y))
						break;
				}
			}
		}
		else if (msg.x > wButton[2][2][0] && msg.y > wButton[2][2][1] && msg.x < wButton[2][2][2] && msg.y < wButton[2][2][3]) {
			botId = 1;
			gridOriginal();
			changeWindows(0);  // “返回”按钮，返回上一级界面
		}
		else if (msg.x > wButton[2][3][0] && msg.y > wButton[2][3][1] && msg.x < wButton[2][3][2] && msg.y < wButton[2][3][3]) {
			if (gridState == 1) {
				GridBack();// “悔棋一步”按钮
				GridBack();// 再悔棋一步
			}
		}
		else if (msg.x > wButton[2][4][0] && msg.y > wButton[2][4][1] && msg.x < wButton[2][4][2] && msg.y < wButton[2][4][3]) {
			ourBackupTeam = true; // “我方后手”按钮
		}
		else if (msg.x > wButton[2][5][0] && msg.y > wButton[2][5][1] && msg.x < wButton[2][5][2] && msg.y < wButton[2][5][3]) {
			char inPut[4] = { 0 };  // “电脑难度”按钮，Bot选择（未实装）
			bool e = InputBox(inPut, 4, "1---Bot1(简单)  2---Bot2(中等)  3---Bot3(困难)\n\n4---Bot4(孙庭宣)  5---Bot5(徐郁博)", "五子棋Bot选择", "1", 0, 0, false);
			if (e) {
				int botnumber = to_Int(inPut);
				if (botnumber >= 1 && botnumber <= 5) {
					botId = botnumber;
					settextcolor(BLACK);
					settextstyle(20, 0, "楷体", 0, 0, 1000, false, false, false);
					setbkcolor(WHITE);
					setbkmode(TRANSPARENT);
					clearrectangle(wButton[2][5][0] - 20, wButton[2][5][3] + 15, wButton[2][5][0] + 200, wButton[2][5][3] + 35);
					outtextxy(wButton[2][5][0] - 20, wButton[2][5][3] + 15, "电脑:");
					outtextxy(wButton[2][5][0] - 20 + textwidth("电脑:"), wButton[2][5][3] + 15, botName[botId]);
				}
			}
		}
		else if (msg.x > xstart - lattic / 2 && msg.x < xstart + 14 * lattic + lattic / 2 && msg.y > ystart - lattic / 2 && msg.y < ystart + 14 * lattic + lattic / 2) {
			if (gridState == 1) {
				if (!playChess(msg.x - (xstart - lattic / 2), msg.y - (ystart - lattic / 2)))
					break;
				if (isEnd()) {
					gridState = 2;
				}
				else {
					int X = -1, Y = -1;
					int gridtemp[15][15] = { 0 };
					copy(gridtemp);
					switch (botId) {
					case 1: Bot1(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 2: Bot2(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 3: Bot3(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 4: Bot4(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 5: Bot5(gridtemp, Rounds, chesscolor, X, Y);
						break;
					case 6:
						break;
					case 7:
						break;
					}
					if (!isFair(X, Y))
						break;
					if (isEnd())
						gridState = 2;
				}
				flushmessage();
			}
		}
		break;
	default:
		break;
	}
}

// 四号窗口消息执行函数, bot对bot
void Gobang::msgExecuteFour() {
	switch (msg.message)
	{  // 消息类别分发处理
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[3][0][0] && msg.y > wButton[3][0][1] && msg.x < wButton[3][0][2] && msg.y < wButton[3][0][3]) {
			setbkcolor(WHITE);
			cleardevice();  // “重置棋盘”按钮，复原棋盘
			drawBoard();
			setFourButton();
			gridOriginal();
		}
		else if (msg.x > wButton[3][1][0] && msg.y > wButton[3][1][1] && msg.x < wButton[3][1][2] && msg.y < wButton[3][1][3]) {
			if (gridState == 0) {
				gridState = 1;	// “开始对局”按钮，开始对局
				Bot_PK_Bot();
			}
		}
		else if (msg.x > wButton[3][2][0] && msg.y > wButton[3][2][1] && msg.x < wButton[3][2][2] && msg.y < wButton[3][2][3]) {
			botId_1 = 1; botId_2 = 1;
			gridOriginal();
			changeWindows(0);  // “返回”按钮，返回上一级界面
		}
		else if (msg.x > wButton[3][3][0] && msg.y > wButton[3][3][1] && msg.x < wButton[3][3][2] && msg.y < wButton[3][3][3]) {
			// 终止对局按钮，提前终止对局
		}
		else if (msg.x > wButton[3][4][0] && msg.y > wButton[3][4][1] && msg.x < wButton[3][4][2] && msg.y < wButton[3][4][3]) {
			ourBackupTeam = true; // “甲方后手”按钮
		}
		else if (msg.x > wButton[3][5][0] && msg.y > wButton[3][5][1] && msg.x < wButton[3][5][2] && msg.y < wButton[3][5][3]) {
			char inPut[4] = { 0 };  // “电脑甲难度”按钮，Bot选择（未实装）
			bool e = InputBox(inPut, 4, "1---Bot1(简单)  2---Bot2(中等)  3---Bot3(困难)\n\n4---Bot4(孙庭宣)  5---Bot5(徐郁博)", "五子棋甲方bot选择", "1", 0, 0, false);
			if (e) {
				int botnumber = to_Int(inPut);
				if (botnumber >= 1 && botnumber <= 5) {
					botId_1 = botnumber;
					settextcolor(BLACK);
					settextstyle(20, 0, "楷体", 0, 0, 1000, false, false, false);
					setbkcolor(WHITE);
					setbkmode(TRANSPARENT);
					clearrectangle(wButton[3][6][0] - 20, wButton[3][6][3] + 20, wButton[3][6][0] + 200, wButton[3][6][3] + 40);
					outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 20, "甲方:");
					outtextxy(wButton[3][6][0] - 20 + textwidth("甲方:"), wButton[3][6][3] + 20, botName[botId_1]);
				}
			}
		}
		else if (msg.x > wButton[3][6][0] && msg.y > wButton[3][6][1] && msg.x < wButton[3][6][2] && msg.y < wButton[3][6][3]) {
			char inPut[4] = { 0 };  // “电脑乙难度”按钮，Bot选择（未实装）
			bool e = InputBox(inPut, 4, "1---Bot1(简单)  2---Bot2(中等)  3---Bot3(困难)\n\n4---Bot4(孙庭宣)  5---Bot5(徐郁博)", "五子棋乙方bot选择", "1", 0, 0, false);
			if (e) {
				int botnumber = to_Int(inPut);
				if (botnumber >= 1 && botnumber <= 5) {
					botId_2 = botnumber;
					settextcolor(BLACK);
					settextstyle(20, 0, "楷体", 0, 0, 1000, false, false, false);
					setbkcolor(WHITE);
					setbkmode(TRANSPARENT);
					clearrectangle(wButton[3][6][0] - 20, wButton[3][6][3] + 60, wButton[3][6][0] + 200, wButton[3][6][3] + 80);
					outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 60, "乙方:");
					outtextxy(wButton[3][6][0] - 20 + textwidth("乙方:"), wButton[3][6][3] + 60, botName[botId_2]);
				}
			}
		}
		break;
	default:
		break;
	}
}

// 五号窗口消息执行函数
void Gobang::msgExecuteFive() {
	switch (msg.message)
	{  // 消息类别分发处理
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[4][0][0] && msg.y > wButton[4][0][1] && msg.x < wButton[4][0][2] && msg.y < wButton[4][0][3]) {
			changeWindows(0);  // “返回”按钮，返回上一级界面
		}
		break;
	default:
		break;
	}
}

// 界面切换函数
void Gobang::changeWindows(int dstWindowsId) {
	// 关闭当前界面
	closegraph();

	//根据参数创建指定标识的新界面
	if (dstWindowsId == 0)
		createOneWindows();
	else
		createTwoWindows(dstWindowsId);
}

// 消息捕获和分发函数
void Gobang::messageControl() {
	while (gameState) {
		getmessage(&msg, EX_MOUSE);
		switch (w_id)
		{	// 根据当前界面分发消息
		case 0:
			msgExecuteOne();
			break;
		case 1:
			msgExecuteTwo();
			break;
		case 2:
			msgExecuteThree();
			break;
		case 3:
			msgExecuteFour();
			break;
		case 4:
			msgExecuteFive();
			break;
		default:
			break;
		}
		// 清空消息缓冲区
		flushmessage();
	}
}

// 绘制棋盘
void Gobang::drawBoard() {
	// 棋盘背景属性
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	setfillcolor(RGB(250, 165, 118));
	setfillstyle(BS_SOLID);
	fillroundrect(xstart - 25, ystart - 25, xstart + gridWidth + 13, ystart + gridWidth + 13, 10, 5);
	
	// 设置线条属性
	int dx = 0, dy = 0;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	// 画横线
	dy = 0;
	for (int i = 1; i <= linenumber; i++) {
		line(xstart, ystart + dy, xstart + gridWidth - 12, ystart + dy);
		dy += lattic;
	}
	// 画竖线
	dx = 0;
	for (int i = 1; i <= linenumber; i++) {
		line(xstart + dx, ystart, xstart + dx, ystart + gridWidth - 12);
		dx += lattic;
	}


	// 规范化棋盘, 特殊点绘制
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	solidrectangle(xstart + 3 * lattic - 5, ystart + 3 * lattic - 5, xstart + 3 * lattic + 5, ystart + 3 * lattic + 5);
	solidrectangle(xstart + 11 * lattic - 5, ystart + 3 * lattic - 5, xstart + 11 * lattic + 5, ystart + 3 * lattic + 5);
	solidrectangle(xstart + 3 * lattic - 5, ystart + 11 * lattic - 5, xstart + 3 * lattic + 5, ystart + 11 * lattic + 5);
	solidrectangle(xstart + 11 * lattic - 5, ystart + 11 * lattic - 5, xstart + 11 * lattic + 5, ystart + 11 * lattic + 5);
	solidrectangle(xstart + 7 * lattic - 5, ystart + 7 * lattic - 5, xstart + 7 * lattic + 5, ystart + 7 * lattic + 5);
}

// 内部棋盘初始化
void Gobang::gridOriginal() {
	// 初始化棋盘
	chesscolor = grid_black;
	Rounds = 1;
	gridState = 0;
	ourBackupTeam = false;
	for (int i = 0; i <= GRIDSIZE; i++)
		for (int j = 0; j <= GRIDSIZE; j++)
			grid[i][j] = 0;
	while (!gridBackUp.empty())
		gridBackUp.pop();
}

// 在指定位置生成棋子
bool Gobang::playChess(int x, int y) {
	int gridx = x / lattic, gridy = y / lattic;
	if (grid[gridy][gridx] != 0)
		return false;
	else {
		if (!gridBackUp.empty()) {
			vector<int> point = gridBackUp.top();
			if (point[0] == grid_black)
				setfillcolor(BLACK);
			else
				setfillcolor(WHITE);
			setfillstyle(BS_SOLID);
			solidcircle(xstart + point[2] * lattic, ystart + point[3] * lattic, R - 1);
		}
		gridBackUp.push({ chesscolor, Rounds, gridx, gridy});  // 记录每一步走棋
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		if (chesscolor == grid_black)
			setfillcolor(BLACK);
		else
			setfillcolor(WHITE);
		setfillstyle(BS_SOLID);
		fillcircle(xstart + gridx * lattic, ystart + gridy * lattic, R);  // 绘制外部棋盘棋子
		grid[gridy][gridx] = chesscolor;		// 内部棋盘落子
		Rounds++;								// 棋局回合数加一
		chesscolor = -chesscolor;				// 棋子颜色翻转（白变黑， 黑变白）

		// 绘制落子提示
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 3);
		line(xstart + gridx * lattic - R * 2 / 3, ystart + gridy * lattic, xstart + gridx * lattic + R * 2 / 3, ystart + gridy * lattic);
		line(xstart + gridx * lattic, ystart + gridy * lattic - R * 2 / 3, xstart + gridx * lattic, ystart + gridy * lattic + R * 2 / 3);
		return true;
	}
}

// 判断棋局是否结束
bool Gobang::isEnd() {
	int my_road[6] = { 0 }, enemy_road[6] = { 0 };
	bool gridfull = true;
	//统计横向
	for (int i = 0; i <= GRIDSIZE; i++) {
		for (int j = 0; j <= GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
				if (grid[i][j + k] == 0) { // 该点是空白位，考察横向下一个邻接点
					gridfull = false;
					continue;
				}
				if (grid[i][j + k] == 1) { // 该点是我方棋子
					if (enemynum == 0)	//敌方棋子数为零，该路还有效
						mynum++;
					else {	//该路已经无效，考察下一条路
						e = 0;   //无效路
						break;
					}
				}
				else {	//该点是对方棋子
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//有效路情况下, my_road和enemy_road要么全为零，要么只有一个为零，为零的下标分量值默认为零
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	//统计竖向有效路
	for (int i = 0; i <= GRIDSIZE; i++) {
		for (int j = 0; j <= GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
				if (grid[j + k][i] == 0) { // 该点是空白位，考察竖向下一个邻接点
					gridfull = false;
					continue;
				}
				if (grid[j + k][i] == 1) { // 该点是我方棋子
					if (enemynum == 0)	//敌方棋子数为零，该路还有效
						mynum++;
					else {	//该路已经无效，考察下一条路
						e = 0;   //无效路
						break;
					}
				}
				else {	//该点是对方棋子
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//有效路情况下, my_road和enemy_road要么全为零，要么只有一个为零，为零的下标分量值默认为零
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	//统计左斜方向有效路
	for (int i = 0; i <= GRIDSIZE - 4; i++) {
		for (int j = 4; j <= GRIDSIZE; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
				if (grid[i + k][j - k] == 0) { // 该点是空白位，考察左斜方向下一个邻接点
					gridfull = false;
					continue;
				}
				if (grid[i + k][j - k] == 1) { // 该点是我方棋子
					if (enemynum == 0)	//敌方棋子数为零，该路还有效
						mynum++;
					else {	//该路已经无效，考察下一条路
						e = 0;   //无效路
						break;
					}
				}
				else {	//该点是对方棋子
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//有效路情况下, my_road和enemy_road要么全为零，要么只有一个为零，为零的下标分量值默认为零
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	//统计右斜方向有效路
	for (int i = 0; i <= GRIDSIZE - 4; i++) {
		for (int j = 0; j <= GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
				if (grid[i + k][j + k] == 0) { // 该点是空白位，考察右斜方向下一个邻接点
					gridfull = false;
					continue;
				}
				if (grid[i + k][j + k] == 1) { // 该点是我方棋子
					if (enemynum == 0)	//敌方棋子数为零，该路还有效
						mynum++;
					else {	//该路已经无效，考察下一条路
						e = 0;   //无效路
						break;
					}
				}
				else {	//该点是对方棋子
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//有效路情况下, my_road和enemy_road要么全为零，要么只有一个为零，为零的下标分量值默认为零
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	// 棋局存储
	if (my_road[5] > 0 || enemy_road[5] > 0 || gridfull) { // 对局具体情况存储到文件里
		stack<vector<int>> T;
		vector<int> point;
		IMAGE img;
		settextstyle(R, 0, "楷体", 0, 0, 1000, false, false, false);
		while (!gridBackUp.empty()) {
			char s[5] = { '\0' };
			point = gridBackUp.top();
			gridBackUp.pop();
			T.push(point);
			to_Chars(point[1], s);
			if (point[0] == grid_black)
				settextcolor(WHITE);
			else
				settextcolor(BLACK);
			outtextxy(xstart + point[2] * lattic - textwidth(s) / 2, ystart + point[3] * lattic - textheight(s) / 2, s);
		}
		getimage(&img, xstart - 25, ystart - 25, gridWidth + 40, gridWidth + 40);
		saveimage("..\\对局情况\\五子棋\\对局情况.bmp", &img);

		fstream file;
		file.open("..\\对局情况\\五子棋\\对局记录.txt", ios::app);
		file.write("对局坐标", sizeof("对局坐标："));
		if (my_road[5] > 0)
			file.write("(黑棋胜)：", sizeof("(黑棋胜)："));
		else if (enemy_road[5] > 0)
			file.write("(白棋胜)：", sizeof("(白棋胜)："));
		else file.write("(平局)：", sizeof("(平局)："));
		while (!T.empty()) {
			char x_y[7] = { 0 };
			point = T.top();
			T.pop();
			createx_y(x_y, point);
			file.write(x_y, strlen(x_y));
			if (point[0] == grid_black)
				setfillcolor(BLACK);
			else
				setfillcolor(WHITE);
			setfillstyle(BS_SOLID);
			solidcircle(xstart + point[2] * lattic, ystart + point[3] * lattic, R - 1);
		}
		file.write("\n", 2);
		file.close();
	}

	// 判胜负
	settextcolor(RED);
	settextstyle(80, 0, "楷体", 0, 0, 1000, false, false, false);
	if (my_road[5] > 0) {
		outtextxy(xstart + (lattic * 14 - textwidth("黑棋获胜")) / 2, ystart + (lattic * 14 - textheight("黑棋获胜")) / 2, "黑棋获胜");
		return true;
	}
	if (enemy_road[5] > 0) {
		outtextxy(xstart + (lattic * 14 - textwidth("白棋获胜")) / 2, ystart + (lattic * 14 - textheight("白棋获胜")) / 2, "白棋获胜");
		return true;
	}
	if (gridfull) {
		outtextxy(xstart + (lattic * 14 - textwidth("平局")) / 2, ystart + (lattic * 14 - textheight("平局")) / 2, "平局");
		return true;
	}
	return false;
}

// 评判电脑给出的坐标是否正确
bool Gobang::isFair(int X, int Y) {
	int i = Y, j = X;
	if (i < 0 || i > GRIDSIZE || j < 0 || j > GRIDSIZE) {
		cout << "Bot的输出坐标" << "(" << X << "," << Y << ")" << "未在棋盘内" << endl;
		gridState = 2;
		return false;
	}
	if (grid[i][j] != 0) {
		cout << "Bot的输出坐标" << "(" << X << "," << Y << ")" << "已有棋子" << endl;
		gridState = 2;
		return false;
	}
	playChess(X * lattic, Y * lattic);
	return true;
}

// 拷贝棋盘副本
void Gobang::copy(int gridtemp[15][15]) {
	for (int i = 0; i <= GRIDSIZE; i++) {
		for (int j = 0; j <= GRIDSIZE; j++) {
			gridtemp[i][j] = grid[i][j];
		}
	}
}

// 悔棋一步
void Gobang::GridBack() {
	if (gridBackUp.empty()) {
		// cout << "栈空了， 退出";
		return;
	}
	vector<int> point = gridBackUp.top();
	gridBackUp.pop();
	// 修改内部棋盘数据
	Rounds--;
	chesscolor = -chesscolor;
	grid[point[3]][point[2]] = grid_blank;

	// 修改棋盘外部表现
	int x = point[2] * lattic + xstart, y = point[3] * lattic + ystart;
	setbkcolor(RGB(250, 165, 118));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	clearcircle(x, y, R + 1);
	line(x - R - 1, y, x + R + 1, y);
	line(x, y - R - 1, x, y + R + 1);

	// 特殊点处理
	if (((point[2] == 3 || point[2] == 11) && (point[3] == 3 || point[3] == 11)) || (point[2] == 7 && point[3] == 7)) {
		setfillcolor(BLACK);
		setfillstyle(BS_SOLID);
		solidrectangle(xstart + point[2] * lattic - 5, ystart + point[3] * lattic - 5, xstart + point[2] * lattic + 5, ystart + point[3] * lattic + 5);
	}

	// 提示符的回退
	if (gridBackUp.empty())
		return;
	point = gridBackUp.top();
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	line(xstart + point[2] * lattic - R * 2 / 3, ystart + point[3] * lattic, xstart + point[2] * lattic + R * 2 / 3, ystart + point[3] * lattic);
	line(xstart + point[2] * lattic, ystart + point[3] * lattic - R * 2 / 3, xstart + point[2] * lattic, ystart + point[3] * lattic + R * 2 / 3);
}

// bot之间的PK
void Gobang::Bot_PK_Bot() {
	int X = -1, Y = -1;
	int gridtemp[15][15] = { 0 };
	if (ourBackupTeam) {  // 如果甲方bot后手，先调用一次乙方bot
		copy(gridtemp);
		switch (botId_2) {
		case 1: Bot1(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 2: Bot2(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 3: Bot3(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 4: Bot4(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 5: Bot5(gridtemp, Rounds, chesscolor, X, Y);
			break;
		}
		if (!isFair(X, Y))
			return;
	}
	while (1) {
		Sleep(timeDelay); // 延迟1000ms
		copy(gridtemp);
		switch (botId_1) {
		case 1: Bot1(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 2: Bot2(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 3: Bot3(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 4: Bot4(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 5: Bot5(gridtemp, Rounds, chesscolor, X, Y);
			break;
		}
		if (!isFair(X, Y))
			return;
		if (isEnd()) {
			gridState = 2;
			return;
		}
		Sleep(timeDelay); // 延迟1000ms
		/*
		if (peekmessage(&msg, EX_MOUSE, true) && (msg.x > wButton[3][3][0] && msg.y > wButton[3][3][1] && msg.x < wButton[3][3][2] && msg.y < wButton[3][3][3])) {
			gridState = 2;
			return;
		}
		*/
		copy(gridtemp);
		switch (botId_2) {
		case 1: Bot1(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 2: Bot2(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 3: Bot3(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 4: Bot4(gridtemp, Rounds, chesscolor, X, Y);
			break;
		case 5: Bot5(gridtemp, Rounds, chesscolor, X, Y);
			break;
		}
		if (!isFair(X, Y))
			return;
		if (isEnd()) {
			gridState = 2;
			return;
		}
	}
}

// 整型数字转char*
void Gobang::to_Chars(int x, char s[]) {
	string str = to_string(x);
	for (int i = 0; i < str.length(); i++)
		s[i] = str[i];
	return;
}

// char*转整型
int Gobang::to_Int(char s[]) {  // 非规范数字char*，返回-1
	int i = 0;
	int num = 0;
	bool posNum = true;   // 默认是正数
	while (s[i] != '\0') {
		if (s[i] == '-')
			posNum = false;
		else if (s[i] >= '0' && s[i] <= '9') {
			num *= 10;
			num += (s[i] - '0');
		}
		else return -1;
		i++;
	}
	return (posNum) ? num : -num;
}

// 转换输出
void Gobang::createx_y(char x_y[], vector<int>& point) {
	string x = to_string(point[2]);
	string y = to_string(point[3]);
	int i = 0, j = 0;
	while (i < x.length()) {
		x_y[i] = x[i];
		i++;
	}
	x_y[i] = ' ';
	i++;
	while (j < y.length()) {
		x_y[i] = y[j];
		i++; j++;
	}
	x_y[i] = ' ';
	i++;
	x_y[i] = '\0';
}