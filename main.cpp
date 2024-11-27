#include <iostream>
#include <graphics.h>
#include <vector>
#include "Gobang.h"
#include "ConnectSix.h"
using namespace std;

const int wWidth = 1000, wHeight = 700;  // �������Ⱥ͸߶�
const int gameNums = 3;		// ��ǰ��Ϸ����
const int gWidth = wWidth / 10, gHeight = wHeight / 6;
const char gameNames[gameNums][15] = { "������", "������", "����������"};
const char gameImageLoad[gameNums][100] = { "..\\ͼƬ��Դ\\Snipaste_2024-07-04_10-51-23.png", "..\\ͼƬ��Դ\\Snipaste_2024-07-04_11-12-38.png" };
vector<vector<int>> buttonNatures(gameNums, vector<int>(4));   // �����水ť����
HWND wHandle;    // ������Ĵ��ھ��


// ����������
void InterfaceDraws();
// ���ư�ť
void ButtonDraws(int x, int y);
// ��Ϣ���񼰷ַ�
void MessCapture();

int main(void) {
	InterfaceDraws();		// ����������
	MessCapture();  // ��Ϣ���񼰷ַ�

	return 0;
}

// ����������
void InterfaceDraws() {
	wHandle = initgraph(wWidth, wHeight, EX_SHOWCONSOLE);  // ����������
	setbkcolor(WHITE);  // ���õ�ǰ��ͼ�豸����ɫ
	cleardevice();

	ButtonDraws(wWidth / 20, wHeight / 12); // ���ư�ť
}

// ���ư�ť
void ButtonDraws(int x, int y) {
	int startx = x, starty = y;
	setbkmode(TRANSPARENT);
	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID);
	settextcolor(BLACK);
	settextstyle(18, 0, "����");
	IMAGE img;
	for (int i = 0; i < gameNums; i++) {  // ��ť����
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


// ��Ϣ���񼰷ַ�
void MessCapture() {
	ExMessage msg;
	while (1) {
		getmessage(&msg, EX_MOUSE);
		switch (msg.message) {
		case WM_LBUTTONUP:
			if (msg.x > buttonNatures[0][0] && msg.y > buttonNatures[0][1] && msg.x < buttonNatures[0][2] && msg.y < buttonNatures[0][3]) {
				flushmessage(); // �����Ϣ������
				closegraph();   // �ر�������
				Gobang gamex(500, 800, 1000, 800);	// ��������Ϸ����
				gamex.PK();
				InterfaceDraws();
			}
			else if (msg.x > buttonNatures[1][0] && msg.y > buttonNatures[1][1] && msg.x < buttonNatures[1][2] && msg.y < buttonNatures[1][3]) {
				flushmessage(); // �����Ϣ������
				closegraph();   // �ر�������
				ConnectSix gamex(500, 800, 1000, 800);		// ��������Ϸ����
				gamex.PK();
				InterfaceDraws();
			}
			else if (msg.x > buttonNatures[2][0] && msg.y > buttonNatures[2][1] && msg.x < buttonNatures[2][2] && msg.y < buttonNatures[2][3]) {
				flushmessage(); // �����Ϣ������
				closegraph();   // �ر�������
								// ������������Ϸ����
				InterfaceDraws();
			}
			break;
		default: break;
		}
		flushmessage();   // ����Ϸ���˳��������Ϣ������
	}
}