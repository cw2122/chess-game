#include <vector>
#include <graphics.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Gobang.h"
using namespace std;

// ��ʼpk����
void Gobang::PK() {
	w_id = 0;
	createOneWindows();
	messageControl();
	closegraph();
}

// һ�����洴������
void Gobang::createOneWindows() {
	w_id = 0;
	wHandle = initgraph(wWidth[0], wHeight[0], EW_SHOWCONSOLE);
	// ���ô�������
	SetWindowText(wHandle, "��������Ϸ");
	// ���ô��ڱ���
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	// ��ͼ
	IMAGE img;
	loadimage(&img, "..\\ͼƬ��Դ\\Snipaste_2024-07-04_10-51-23.png", wWidth[0], wHeight[0]);
	putimage(0, 0, &img);
	// ���ô��ڰ�ť
	setOneButton();
}

// �������洴������
void Gobang::createTwoWindows(int windowsId) {
	w_id = windowsId;
	wHandle = initgraph(wWidth[1], wHeight[1], EW_SHOWCONSOLE);
	// ���ô�������
	SetWindowText(wHandle, "��������Ϸ");
	// ���ô��ڱ���
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	if (windowsId < 4) {
		gridOriginal(); // ���̳�ʼ��
		// ��������
		drawBoard();
	}
	// ���ô��ڰ�ť
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

// һ�Ŵ��ڰ�ť����
void Gobang::setOneButton() {
	// ͼ�����

	// ��ť����
	int buttonWidth = wWidth[w_id] / 3, buttonHeight = wHeight[w_id] / 5 * 2 / 4 / 2;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(250, 165, 118));
	setfillstyle(BS_SOLID);
	settextcolor(BLACK);
	settextstyle(buttonHeight / 2, 0, "����", 0, 0, 1000, false, false, false);
	startx = (wWidth[w_id] - buttonWidth) / 2; starty = wHeight[w_id] / 5 * 3 + buttonHeight / 2;
	for (int i = 0; i < 4; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// ���水ťi����ֹ������
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i]);
		tHeight = textheight(buttonName[i]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i]);
		starty += (buttonHeight * 2);
	}
	// ���ذ�ť
	startx += (buttonWidth + 10);
	starty -= (buttonHeight * 2);
	fillroundrect(startx, starty, startx + buttonWidth / 2, starty + buttonHeight, 10, 6);
	wButton[w_id][4][0] = startx; wButton[w_id][4][1] = starty; wButton[w_id][4][2] = startx + buttonWidth / 2; wButton[w_id][4][3] = starty + buttonHeight;
	tWidth = textwidth("����");
	tHeight = textheight("����");
	t_startx = startx + (buttonWidth / 2 - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
	outtextxy(t_startx, t_starty, "����");
}

// ���Ŵ��ڰ�ť����
void Gobang::setTwoButton() {
	// ͼ�����

	// ��ť����(Ŀǰ�ĸ�)
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "����", 0, 0, 1000, false, false, false);
	startx = gridWidth / 16; starty = 50 + gridWidth + 40;
	for (int i = 0; i < 4; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// ���水ťi����ֹ������
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 4]);
		tHeight = textheight(buttonName[i + 4]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 4]);
		startx += (buttonWidth * 2);
	}
}

// ���Ŵ��ڰ�ť����
void Gobang::setThreeButton() {
	// ͼ�����

	// ��ť����(Ŀǰ����)
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "����", 0, 0, 1000, false, false, false);
	startx = gridWidth / 16; starty = 50 + gridWidth + 40;
	for (int i = 0; i < 4; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// ���水ťi����ֹ������
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

	// botId��ʾ��ʼ��
	settextcolor(BLACK);
	settextstyle(20, 0, "����", 0, 0, 1000, false, false, false);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(wButton[2][5][0] - 20, wButton[2][5][3] + 15, "����:");
	outtextxy(wButton[2][5][0] - 20 + textwidth("����:"), wButton[2][5][3] + 15, botName[botId]);
}

// �ĺŴ��ڰ�ť����
void Gobang::setFourButton() {
	// ͼ�����

	// ��ť����(Ŀǰ����)
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "����", 0, 0, 1000, false, false, false);
	startx = gridWidth / 16; starty = 50 + gridWidth + 40;
	for (int i = 0; i < 3; i++) {
		fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
		// ���水ťi����ֹ������
		wButton[w_id][i][0] = startx; wButton[w_id][i][1] = starty; wButton[w_id][i][2] = startx + buttonWidth; wButton[w_id][i][3] = starty + buttonHeight;
		tWidth = textwidth(buttonName[i + 4]);
		tHeight = textheight(buttonName[i + 4]);
		t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
		outtextxy(t_startx, t_starty, buttonName[i + 4]);
		startx += (buttonWidth * 2);
	}
	fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
	// ���水ťi����ֹ������
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

	// botId_1, botId_2��ʾ��ʼ��
	settextcolor(BLACK);
	settextstyle(20, 0, "����", 0, 0, 1000, false, false, false);
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 20, "�׷�:");
	outtextxy(wButton[3][6][0] - 20 + textwidth("�׷�:"), wButton[3][6][3] + 20, botName[botId_1]);
	outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 60, "�ҷ�:");
	outtextxy(wButton[3][6][0] - 20 + textwidth("�ҷ�:"), wButton[3][6][3] + 60, botName[botId_2]);
}

// ��Ŵ��ڰ�ť����
void Gobang::setFiveButton() {
	// �����ĵ�
	settextcolor(BLACK);
	settextstyle(100, 0, "����", 0, 0, 1000, false, false, false);
	outtextxy((wWidth[1] - textwidth("ʲô��û���ˣ�����")) / 2, (wHeight[1] - textheight("ʲô��û���ˣ�����")) / 2, "ʲô��û���ˣ�����");
	// ���ذ�ť
	int buttonWidth = wWidth[1] / 4 / 2, buttonHeight = 40;
	int tWidth, tHeight;
	int startx, starty, t_startx, t_starty;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	settextcolor(WHITE);
	settextstyle(buttonHeight / 2, 0, "����", 0, 0, 1000, false, false, false);
	startx = (wWidth[1] - buttonWidth) / 2; starty = 50 + gridWidth + 40;
	fillroundrect(startx, starty, startx + buttonWidth, starty + buttonHeight, 10, 6);
	// ���水ťi����ֹ������
	wButton[w_id][0][0] = startx; wButton[w_id][0][1] = starty; wButton[w_id][0][2] = startx + buttonWidth; wButton[w_id][0][3] = starty + buttonHeight;
	tWidth = textwidth("����");
	tHeight = textheight("����");
	t_startx = startx + (buttonWidth - tWidth) / 2; t_starty = starty + (buttonHeight - tHeight) / 2;
	outtextxy(t_startx, t_starty, "����");
}

// һ�Ŵ�����Ϣִ�к���
void Gobang::msgExecuteOne() {
	switch (msg.message)
	{  // ��Ϣ���ַ�����
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[0][0][0] && msg.y > wButton[0][0][1] && msg.x < wButton[0][0][2] && msg.y < wButton[0][0][3]) {
			changeWindows(1);  // ���˶��ˡ���ť���л�����
		}
		else if (msg.x > wButton[0][1][0] && msg.y > wButton[0][1][1] && msg.x < wButton[0][1][2] && msg.y < wButton[0][1][3]) {
			changeWindows(2);  // ���˶Ե��ԡ���ť���л�����
		}
		else if (msg.x > wButton[0][2][0] && msg.y > wButton[0][2][1] && msg.x < wButton[0][2][2] && msg.y < wButton[0][2][3]) {
			changeWindows(3);  // �����ԶԵ��ԡ���ť���л�����
		}
		else if (msg.x > wButton[0][3][0] && msg.y > wButton[0][3][1] && msg.x < wButton[0][3][2] && msg.y < wButton[0][3][3]) {
			changeWindows(4);  // ����������ť���л�����
		}
		else if (msg.x > wButton[0][4][0] && msg.y > wButton[0][4][1] && msg.x < wButton[0][4][2] && msg.y < wButton[0][4][3]) {
			gameState = 0;	   // �����ء���ť�� �л�������
		}
		break;
	default:
		break;
	}
}

// ���Ŵ�����Ϣִ�к���
void Gobang::msgExecuteTwo() {
	switch (msg.message)
	{  // ��Ϣ���ַ�����
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[1][0][0] && msg.y > wButton[1][0][1] && msg.x < wButton[1][0][2] && msg.y < wButton[1][0][3]) {
			setbkcolor(WHITE);
			cleardevice();  // ���������̡���ť����ԭ����
			drawBoard();
			setTwoButton();
			gridOriginal();
		}
		else if (msg.x > wButton[1][1][0] && msg.y > wButton[1][1][1] && msg.x < wButton[1][1][2] && msg.y < wButton[1][1][3]) {
			if (gridState == 0)
				gridState = 1;	// ����ʼ�Ծ֡���ť����ʼ�Ծ�
		}
		else if (msg.x > wButton[1][2][0] && msg.y > wButton[1][2][1] && msg.x < wButton[1][2][2] && msg.y < wButton[1][2][3]) {
			gridOriginal();
			changeWindows(0);  // �����ء���ť��������һ������
		}
		else if (msg.x > wButton[1][3][0] && msg.y > wButton[1][3][1] && msg.x < wButton[1][3][2] && msg.y < wButton[1][3][3]) {
			if (gridState) {
				GridBack();// ����һ��
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

// ���Ŵ�����Ϣִ�к���
void Gobang::msgExecuteThree() {
	switch (msg.message)
	{  // ��Ϣ���ַ�����
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[2][0][0] && msg.y > wButton[2][0][1] && msg.x < wButton[2][0][2] && msg.y < wButton[2][0][3]) {
			setbkcolor(WHITE);
			cleardevice();  // ���������̡���ť����ԭ����
			drawBoard();
			setThreeButton();
			gridOriginal();
		}
		else if (msg.x > wButton[2][1][0] && msg.y > wButton[2][1][1] && msg.x < wButton[2][1][2] && msg.y < wButton[2][1][3]) {
			if (gridState == 0) {
				gridState = 1;	// ����ʼ�Ծ֡���ť����ʼ�Ծ�
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
			changeWindows(0);  // �����ء���ť��������һ������
		}
		else if (msg.x > wButton[2][3][0] && msg.y > wButton[2][3][1] && msg.x < wButton[2][3][2] && msg.y < wButton[2][3][3]) {
			if (gridState == 1) {
				GridBack();// ������һ������ť
				GridBack();// �ٻ���һ��
			}
		}
		else if (msg.x > wButton[2][4][0] && msg.y > wButton[2][4][1] && msg.x < wButton[2][4][2] && msg.y < wButton[2][4][3]) {
			ourBackupTeam = true; // ���ҷ����֡���ť
		}
		else if (msg.x > wButton[2][5][0] && msg.y > wButton[2][5][1] && msg.x < wButton[2][5][2] && msg.y < wButton[2][5][3]) {
			char inPut[4] = { 0 };  // �������Ѷȡ���ť��Botѡ��δʵװ��
			bool e = InputBox(inPut, 4, "1---Bot1(��)  2---Bot2(�е�)  3---Bot3(����)\n\n4---Bot4(��ͥ��)  5---Bot5(������)", "������Botѡ��", "1", 0, 0, false);
			if (e) {
				int botnumber = to_Int(inPut);
				if (botnumber >= 1 && botnumber <= 5) {
					botId = botnumber;
					settextcolor(BLACK);
					settextstyle(20, 0, "����", 0, 0, 1000, false, false, false);
					setbkcolor(WHITE);
					setbkmode(TRANSPARENT);
					clearrectangle(wButton[2][5][0] - 20, wButton[2][5][3] + 15, wButton[2][5][0] + 200, wButton[2][5][3] + 35);
					outtextxy(wButton[2][5][0] - 20, wButton[2][5][3] + 15, "����:");
					outtextxy(wButton[2][5][0] - 20 + textwidth("����:"), wButton[2][5][3] + 15, botName[botId]);
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

// �ĺŴ�����Ϣִ�к���, bot��bot
void Gobang::msgExecuteFour() {
	switch (msg.message)
	{  // ��Ϣ���ַ�����
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[3][0][0] && msg.y > wButton[3][0][1] && msg.x < wButton[3][0][2] && msg.y < wButton[3][0][3]) {
			setbkcolor(WHITE);
			cleardevice();  // ���������̡���ť����ԭ����
			drawBoard();
			setFourButton();
			gridOriginal();
		}
		else if (msg.x > wButton[3][1][0] && msg.y > wButton[3][1][1] && msg.x < wButton[3][1][2] && msg.y < wButton[3][1][3]) {
			if (gridState == 0) {
				gridState = 1;	// ����ʼ�Ծ֡���ť����ʼ�Ծ�
				Bot_PK_Bot();
			}
		}
		else if (msg.x > wButton[3][2][0] && msg.y > wButton[3][2][1] && msg.x < wButton[3][2][2] && msg.y < wButton[3][2][3]) {
			botId_1 = 1; botId_2 = 1;
			gridOriginal();
			changeWindows(0);  // �����ء���ť��������һ������
		}
		else if (msg.x > wButton[3][3][0] && msg.y > wButton[3][3][1] && msg.x < wButton[3][3][2] && msg.y < wButton[3][3][3]) {
			// ��ֹ�Ծְ�ť����ǰ��ֹ�Ծ�
		}
		else if (msg.x > wButton[3][4][0] && msg.y > wButton[3][4][1] && msg.x < wButton[3][4][2] && msg.y < wButton[3][4][3]) {
			ourBackupTeam = true; // ���׷����֡���ť
		}
		else if (msg.x > wButton[3][5][0] && msg.y > wButton[3][5][1] && msg.x < wButton[3][5][2] && msg.y < wButton[3][5][3]) {
			char inPut[4] = { 0 };  // �����Լ��Ѷȡ���ť��Botѡ��δʵװ��
			bool e = InputBox(inPut, 4, "1---Bot1(��)  2---Bot2(�е�)  3---Bot3(����)\n\n4---Bot4(��ͥ��)  5---Bot5(������)", "������׷�botѡ��", "1", 0, 0, false);
			if (e) {
				int botnumber = to_Int(inPut);
				if (botnumber >= 1 && botnumber <= 5) {
					botId_1 = botnumber;
					settextcolor(BLACK);
					settextstyle(20, 0, "����", 0, 0, 1000, false, false, false);
					setbkcolor(WHITE);
					setbkmode(TRANSPARENT);
					clearrectangle(wButton[3][6][0] - 20, wButton[3][6][3] + 20, wButton[3][6][0] + 200, wButton[3][6][3] + 40);
					outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 20, "�׷�:");
					outtextxy(wButton[3][6][0] - 20 + textwidth("�׷�:"), wButton[3][6][3] + 20, botName[botId_1]);
				}
			}
		}
		else if (msg.x > wButton[3][6][0] && msg.y > wButton[3][6][1] && msg.x < wButton[3][6][2] && msg.y < wButton[3][6][3]) {
			char inPut[4] = { 0 };  // ���������Ѷȡ���ť��Botѡ��δʵװ��
			bool e = InputBox(inPut, 4, "1---Bot1(��)  2---Bot2(�е�)  3---Bot3(����)\n\n4---Bot4(��ͥ��)  5---Bot5(������)", "�������ҷ�botѡ��", "1", 0, 0, false);
			if (e) {
				int botnumber = to_Int(inPut);
				if (botnumber >= 1 && botnumber <= 5) {
					botId_2 = botnumber;
					settextcolor(BLACK);
					settextstyle(20, 0, "����", 0, 0, 1000, false, false, false);
					setbkcolor(WHITE);
					setbkmode(TRANSPARENT);
					clearrectangle(wButton[3][6][0] - 20, wButton[3][6][3] + 60, wButton[3][6][0] + 200, wButton[3][6][3] + 80);
					outtextxy(wButton[3][6][0] - 20, wButton[3][6][3] + 60, "�ҷ�:");
					outtextxy(wButton[3][6][0] - 20 + textwidth("�ҷ�:"), wButton[3][6][3] + 60, botName[botId_2]);
				}
			}
		}
		break;
	default:
		break;
	}
}

// ��Ŵ�����Ϣִ�к���
void Gobang::msgExecuteFive() {
	switch (msg.message)
	{  // ��Ϣ���ַ�����
	case WM_LBUTTONDOWN:
		if (msg.x > wButton[4][0][0] && msg.y > wButton[4][0][1] && msg.x < wButton[4][0][2] && msg.y < wButton[4][0][3]) {
			changeWindows(0);  // �����ء���ť��������һ������
		}
		break;
	default:
		break;
	}
}

// �����л�����
void Gobang::changeWindows(int dstWindowsId) {
	// �رյ�ǰ����
	closegraph();

	//���ݲ�������ָ����ʶ���½���
	if (dstWindowsId == 0)
		createOneWindows();
	else
		createTwoWindows(dstWindowsId);
}

// ��Ϣ����ͷַ�����
void Gobang::messageControl() {
	while (gameState) {
		getmessage(&msg, EX_MOUSE);
		switch (w_id)
		{	// ���ݵ�ǰ����ַ���Ϣ
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
		// �����Ϣ������
		flushmessage();
	}
}

// ��������
void Gobang::drawBoard() {
	// ���̱�������
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	setfillcolor(RGB(250, 165, 118));
	setfillstyle(BS_SOLID);
	fillroundrect(xstart - 25, ystart - 25, xstart + gridWidth + 13, ystart + gridWidth + 13, 10, 5);
	
	// ������������
	int dx = 0, dy = 0;
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	// ������
	dy = 0;
	for (int i = 1; i <= linenumber; i++) {
		line(xstart, ystart + dy, xstart + gridWidth - 12, ystart + dy);
		dy += lattic;
	}
	// ������
	dx = 0;
	for (int i = 1; i <= linenumber; i++) {
		line(xstart + dx, ystart, xstart + dx, ystart + gridWidth - 12);
		dx += lattic;
	}


	// �淶������, ��������
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	solidrectangle(xstart + 3 * lattic - 5, ystart + 3 * lattic - 5, xstart + 3 * lattic + 5, ystart + 3 * lattic + 5);
	solidrectangle(xstart + 11 * lattic - 5, ystart + 3 * lattic - 5, xstart + 11 * lattic + 5, ystart + 3 * lattic + 5);
	solidrectangle(xstart + 3 * lattic - 5, ystart + 11 * lattic - 5, xstart + 3 * lattic + 5, ystart + 11 * lattic + 5);
	solidrectangle(xstart + 11 * lattic - 5, ystart + 11 * lattic - 5, xstart + 11 * lattic + 5, ystart + 11 * lattic + 5);
	solidrectangle(xstart + 7 * lattic - 5, ystart + 7 * lattic - 5, xstart + 7 * lattic + 5, ystart + 7 * lattic + 5);
}

// �ڲ����̳�ʼ��
void Gobang::gridOriginal() {
	// ��ʼ������
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

// ��ָ��λ����������
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
		gridBackUp.push({ chesscolor, Rounds, gridx, gridy});  // ��¼ÿһ������
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		if (chesscolor == grid_black)
			setfillcolor(BLACK);
		else
			setfillcolor(WHITE);
		setfillstyle(BS_SOLID);
		fillcircle(xstart + gridx * lattic, ystart + gridy * lattic, R);  // �����ⲿ��������
		grid[gridy][gridx] = chesscolor;		// �ڲ���������
		Rounds++;								// ��ֻغ�����һ
		chesscolor = -chesscolor;				// ������ɫ��ת���ױ�ڣ� �ڱ�ף�

		// ����������ʾ
		setlinecolor(RED);
		setlinestyle(PS_SOLID, 3);
		line(xstart + gridx * lattic - R * 2 / 3, ystart + gridy * lattic, xstart + gridx * lattic + R * 2 / 3, ystart + gridy * lattic);
		line(xstart + gridx * lattic, ystart + gridy * lattic - R * 2 / 3, xstart + gridx * lattic, ystart + gridy * lattic + R * 2 / 3);
		return true;
	}
}

// �ж�����Ƿ����
bool Gobang::isEnd() {
	int my_road[6] = { 0 }, enemy_road[6] = { 0 };
	bool gridfull = true;
	//ͳ�ƺ���
	for (int i = 0; i <= GRIDSIZE; i++) {
		for (int j = 0; j <= GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum��·���ҷ��ͶԷ�����������e��ʾ��·�Ƿ���Ч
			for (int k = 0; k < 5; k++) {
				if (grid[i][j + k] == 0) { // �õ��ǿհ�λ�����������һ���ڽӵ�
					gridfull = false;
					continue;
				}
				if (grid[i][j + k] == 1) { // �õ����ҷ�����
					if (enemynum == 0)	//�з�������Ϊ�㣬��·����Ч
						mynum++;
					else {	//��·�Ѿ���Ч��������һ��·
						e = 0;   //��Ч·
						break;
					}
				}
				else {	//�õ��ǶԷ�����
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//��Ч·�����, my_road��enemy_roadҪôȫΪ�㣬Ҫôֻ��һ��Ϊ�㣬Ϊ����±����ֵĬ��Ϊ��
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	//ͳ��������Ч·
	for (int i = 0; i <= GRIDSIZE; i++) {
		for (int j = 0; j <= GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum��·���ҷ��ͶԷ�����������e��ʾ��·�Ƿ���Ч
			for (int k = 0; k < 5; k++) {
				if (grid[j + k][i] == 0) { // �õ��ǿհ�λ������������һ���ڽӵ�
					gridfull = false;
					continue;
				}
				if (grid[j + k][i] == 1) { // �õ����ҷ�����
					if (enemynum == 0)	//�з�������Ϊ�㣬��·����Ч
						mynum++;
					else {	//��·�Ѿ���Ч��������һ��·
						e = 0;   //��Ч·
						break;
					}
				}
				else {	//�õ��ǶԷ�����
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//��Ч·�����, my_road��enemy_roadҪôȫΪ�㣬Ҫôֻ��һ��Ϊ�㣬Ϊ����±����ֵĬ��Ϊ��
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	//ͳ����б������Ч·
	for (int i = 0; i <= GRIDSIZE - 4; i++) {
		for (int j = 4; j <= GRIDSIZE; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum��·���ҷ��ͶԷ�����������e��ʾ��·�Ƿ���Ч
			for (int k = 0; k < 5; k++) {
				if (grid[i + k][j - k] == 0) { // �õ��ǿհ�λ��������б������һ���ڽӵ�
					gridfull = false;
					continue;
				}
				if (grid[i + k][j - k] == 1) { // �õ����ҷ�����
					if (enemynum == 0)	//�з�������Ϊ�㣬��·����Ч
						mynum++;
					else {	//��·�Ѿ���Ч��������һ��·
						e = 0;   //��Ч·
						break;
					}
				}
				else {	//�õ��ǶԷ�����
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//��Ч·�����, my_road��enemy_roadҪôȫΪ�㣬Ҫôֻ��һ��Ϊ�㣬Ϊ����±����ֵĬ��Ϊ��
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	//ͳ����б������Ч·
	for (int i = 0; i <= GRIDSIZE - 4; i++) {
		for (int j = 0; j <= GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum��·���ҷ��ͶԷ�����������e��ʾ��·�Ƿ���Ч
			for (int k = 0; k < 5; k++) {
				if (grid[i + k][j + k] == 0) { // �õ��ǿհ�λ��������б������һ���ڽӵ�
					gridfull = false;
					continue;
				}
				if (grid[i + k][j + k] == 1) { // �õ����ҷ�����
					if (enemynum == 0)	//�з�������Ϊ�㣬��·����Ч
						mynum++;
					else {	//��·�Ѿ���Ч��������һ��·
						e = 0;   //��Ч·
						break;
					}
				}
				else {	//�õ��ǶԷ�����
					if (mynum == 0)
						enemynum++;
					else {
						e = 0;
						break;
					}
				}
			}
			if (e == 1) {	//��Ч·�����, my_road��enemy_roadҪôȫΪ�㣬Ҫôֻ��һ��Ϊ�㣬Ϊ����±����ֵĬ��Ϊ��
				my_road[mynum]++;
				enemy_road[enemynum]++;
			}
		}
	}

	// ��ִ洢
	if (my_road[5] > 0 || enemy_road[5] > 0 || gridfull) { // �Ծ־�������洢���ļ���
		stack<vector<int>> T;
		vector<int> point;
		IMAGE img;
		settextstyle(R, 0, "����", 0, 0, 1000, false, false, false);
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
		saveimage("..\\�Ծ����\\������\\�Ծ����.bmp", &img);

		fstream file;
		file.open("..\\�Ծ����\\������\\�Ծּ�¼.txt", ios::app);
		file.write("�Ծ�����", sizeof("�Ծ����꣺"));
		if (my_road[5] > 0)
			file.write("(����ʤ)��", sizeof("(����ʤ)��"));
		else if (enemy_road[5] > 0)
			file.write("(����ʤ)��", sizeof("(����ʤ)��"));
		else file.write("(ƽ��)��", sizeof("(ƽ��)��"));
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

	// ��ʤ��
	settextcolor(RED);
	settextstyle(80, 0, "����", 0, 0, 1000, false, false, false);
	if (my_road[5] > 0) {
		outtextxy(xstart + (lattic * 14 - textwidth("�����ʤ")) / 2, ystart + (lattic * 14 - textheight("�����ʤ")) / 2, "�����ʤ");
		return true;
	}
	if (enemy_road[5] > 0) {
		outtextxy(xstart + (lattic * 14 - textwidth("�����ʤ")) / 2, ystart + (lattic * 14 - textheight("�����ʤ")) / 2, "�����ʤ");
		return true;
	}
	if (gridfull) {
		outtextxy(xstart + (lattic * 14 - textwidth("ƽ��")) / 2, ystart + (lattic * 14 - textheight("ƽ��")) / 2, "ƽ��");
		return true;
	}
	return false;
}

// ���е��Ը����������Ƿ���ȷ
bool Gobang::isFair(int X, int Y) {
	int i = Y, j = X;
	if (i < 0 || i > GRIDSIZE || j < 0 || j > GRIDSIZE) {
		cout << "Bot���������" << "(" << X << "," << Y << ")" << "δ��������" << endl;
		gridState = 2;
		return false;
	}
	if (grid[i][j] != 0) {
		cout << "Bot���������" << "(" << X << "," << Y << ")" << "��������" << endl;
		gridState = 2;
		return false;
	}
	playChess(X * lattic, Y * lattic);
	return true;
}

// �������̸���
void Gobang::copy(int gridtemp[15][15]) {
	for (int i = 0; i <= GRIDSIZE; i++) {
		for (int j = 0; j <= GRIDSIZE; j++) {
			gridtemp[i][j] = grid[i][j];
		}
	}
}

// ����һ��
void Gobang::GridBack() {
	if (gridBackUp.empty()) {
		// cout << "ջ���ˣ� �˳�";
		return;
	}
	vector<int> point = gridBackUp.top();
	gridBackUp.pop();
	// �޸��ڲ���������
	Rounds--;
	chesscolor = -chesscolor;
	grid[point[3]][point[2]] = grid_blank;

	// �޸������ⲿ����
	int x = point[2] * lattic + xstart, y = point[3] * lattic + ystart;
	setbkcolor(RGB(250, 165, 118));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	clearcircle(x, y, R + 1);
	line(x - R - 1, y, x + R + 1, y);
	line(x, y - R - 1, x, y + R + 1);

	// ����㴦��
	if (((point[2] == 3 || point[2] == 11) && (point[3] == 3 || point[3] == 11)) || (point[2] == 7 && point[3] == 7)) {
		setfillcolor(BLACK);
		setfillstyle(BS_SOLID);
		solidrectangle(xstart + point[2] * lattic - 5, ystart + point[3] * lattic - 5, xstart + point[2] * lattic + 5, ystart + point[3] * lattic + 5);
	}

	// ��ʾ���Ļ���
	if (gridBackUp.empty())
		return;
	point = gridBackUp.top();
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	line(xstart + point[2] * lattic - R * 2 / 3, ystart + point[3] * lattic, xstart + point[2] * lattic + R * 2 / 3, ystart + point[3] * lattic);
	line(xstart + point[2] * lattic, ystart + point[3] * lattic - R * 2 / 3, xstart + point[2] * lattic, ystart + point[3] * lattic + R * 2 / 3);
}

// bot֮���PK
void Gobang::Bot_PK_Bot() {
	int X = -1, Y = -1;
	int gridtemp[15][15] = { 0 };
	if (ourBackupTeam) {  // ����׷�bot���֣��ȵ���һ���ҷ�bot
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
		Sleep(timeDelay); // �ӳ�1000ms
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
		Sleep(timeDelay); // �ӳ�1000ms
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

// ��������תchar*
void Gobang::to_Chars(int x, char s[]) {
	string str = to_string(x);
	for (int i = 0; i < str.length(); i++)
		s[i] = str[i];
	return;
}

// char*ת����
int Gobang::to_Int(char s[]) {  // �ǹ淶����char*������-1
	int i = 0;
	int num = 0;
	bool posNum = true;   // Ĭ��������
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

// ת�����
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