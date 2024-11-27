#pragma once
#include <vector>
#include <graphics.h>
#include <stack>
using namespace std;

class ConnectSix {  // ��������Ϸ
private:
	HWND wHandle;	// ���ھ��
	int w_id;		// ����㼶ID
	int wWidth[2], wHeight[2]; // ÿ�����ڵĴ�С
	bool gameState;   // ��Ϸ����״̬��1��ʾ����Ϸ�������У� 0��ʾ��������Ϸ���������˳��� 
	int timeDelay = 1000;  // bot��bot�Ծ�֮����ӳ�(1000ms)
	vector<vector<vector<int>>> wButton;  // ÿ�����ڵİ�ť��Ϣ
	ExMessage msg;      // ��Ϣ����
	char buttonName[14][17] = { "�˶���", "�˶Ե���", "���ԶԵ���", "����", "��������", "��ʼ�Ծ�", "����", "����һ��", "�ҷ�����", "�����Ѷ�", "��ֹ�Ծ�", "�׷�����", "���Լ��Ѷ�", "�������Ѷ�" };
	int botId = 1;   // bot��ѡ��Ĭ��Ϊbot1(��)
	int botId_1 = 1, botId_2 = 1;  // botId_1�Ǽ׷�bot, botId_2���ҷ�bot, ��ʼĬ��2��bot
	char botName[10][16] = { "", "Bot1(��)", "Bot2(�е�)", "Bot3(����)" }; // Bot������
	// ��������
	const int gridWidth = 600;			 // ���̳ߴ�
	const int linenumber = 15;			 // ����������
	const int GRIDSIZE = linenumber - 1; // ���̸�����
	const int xstart = 200, ystart = 50; // ���̵���ʼ������xstart, ystart
	int gridState = 0;					 // ����״̬, 0-������1-���š�2-��ֹ
	const int lattic = gridWidth / (linenumber - 1); // ���ߴ�
	const int R = lattic / 2 / 4 * 3;			 // ���Ӱ뾶
	int grid[15][15] = { 0 };			 // ���� 
	bool ourBackupTeam = false;          // �ҷ��Ƿ����
	const int grid_blank = 0;            // ���̿���λ
	const int grid_white = -1;           // ����
	const int grid_black = 1;            // ����
	int chesscolor = grid_black;		 // ��ǰִ����ɫ
	int Rounds = 1;                      // �غ���
	bool hasPawn = false;             // �Ƿ�����һ����
	stack<vector<int>> gridBackUp;    // ��ּ�¼
public:
	// ���캯��, ��ʼ����������
	ConnectSix(int onewidth, int oneheight, int twowidth, int twoheight) : wButton(5, vector<vector<int>>(10, vector<int>(4))), gameState(1) {
		wWidth[0] = onewidth; wHeight[0] = oneheight; wWidth[1] = twowidth; wHeight[1] = twoheight;
	};
	// ��ʼpk����
	void PK();
private:
	// �����л�����
	void changeWindows(int dstWindowsId);
	// ��Ϣ����ͷַ�����
	void messageControl();
	// һ�����洴������
	void createOneWindows();
	// �������洴������
	void createTwoWindows(int windowsId);
	// һ�Ŵ��ڰ�ť����
	void setOneButton();
	// ���Ŵ��ڰ�ť����
	void setTwoButton();
	// ���Ŵ��ڰ�ť����
	void setThreeButton();
	// �ĺŴ��ڰ�ť����
	void setFourButton();
	// ��Ŵ��ڰ�ť����
	void setFiveButton();
	// һ�Ŵ�����Ϣִ�к���
	void msgExecuteOne();
	// ���Ŵ�����Ϣִ�к���
	void msgExecuteTwo();
	// ���Ŵ�����Ϣִ�к���
	void msgExecuteThree();
	// �ĺŴ�����Ϣִ�к���
	void msgExecuteFour();
	// ��Ŵ�����Ϣִ�к���
	void msgExecuteFive();
	// ��������
	void drawBoard();
	// �ڲ����̳�ʼ��
	void gridOriginal();
	// ָ��λ������
	bool playChess(int x, int y);
	// �ж�����Ƿ����
	bool isEnd();
	// ���е��Ը����������Ƿ���ȷ
	bool isFair(int X1, int Y1, int X2, int Y2);
	// �������̸���
	void copy(int gridtemp[15][15]);
	//������һ������ť������һ����
	void GridBack();
	// bot֮��PK����
	void Bot_PK_Bot();
	// ��������תchar*
	void to_Chars(int x, char s[]);
	// char*ת����
	int to_Int(char s[]);
	// ת�����
	void createx_y(char x_y[], vector<int>& point);
};


//  ����bot����
/*********************************************************************************************/

// һ��Bot��������
void Bot1(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2);

// ����Bot��������
void Bot2(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2);

/*
// ����Bot��������, ��������������(δ��ʵ��)
void Bot3(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2);
*/
