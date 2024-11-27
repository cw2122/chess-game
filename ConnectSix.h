#pragma once
#include <vector>
#include <graphics.h>
#include <stack>
using namespace std;

class ConnectSix {  // 六子棋游戏
private:
	HWND wHandle;	// 窗口句柄
	int w_id;		// 界面层级ID
	int wWidth[2], wHeight[2]; // 每级窗口的大小
	bool gameState;   // 游戏对象状态，1表示该游戏正常运行， 0表示结束该游戏对象（析构退出） 
	int timeDelay = 1000;  // bot与bot对决之间的延迟(1000ms)
	vector<vector<vector<int>>> wButton;  // 每级窗口的按钮信息
	ExMessage msg;      // 消息对象
	char buttonName[14][17] = { "人对人", "人对电脑", "电脑对电脑", "帮助", "重置棋盘", "开始对局", "返回", "悔棋一步", "我方后手", "电脑难度", "终止对局", "甲方后手", "电脑甲难度", "电脑乙难度" };
	int botId = 1;   // bot的选择，默认为bot1(简单)
	int botId_1 = 1, botId_2 = 1;  // botId_1是甲方bot, botId_2是乙方bot, 初始默认2号bot
	char botName[10][16] = { "", "Bot1(简单)", "Bot2(中等)", "Bot3(困难)" }; // Bot的名称
	// 棋盘属性
	const int gridWidth = 600;			 // 棋盘尺寸
	const int linenumber = 15;			 // 棋盘线条数
	const int GRIDSIZE = linenumber - 1; // 棋盘格子数
	const int xstart = 200, ystart = 50; // 棋盘的起始点坐标xstart, ystart
	int gridState = 0;					 // 棋盘状态, 0-锁定、1-开放、2-终止
	const int lattic = gridWidth / (linenumber - 1); // 棋格尺寸
	const int R = lattic / 2 / 4 * 3;			 // 棋子半径
	int grid[15][15] = { 0 };			 // 棋盘 
	bool ourBackupTeam = false;          // 我方是否后手
	const int grid_blank = 0;            // 棋盘空闲位
	const int grid_white = -1;           // 白棋
	const int grid_black = 1;            // 黑棋
	int chesscolor = grid_black;		 // 当前执棋颜色
	int Rounds = 1;                      // 回合数
	bool hasPawn = false;             // 是否已下一棋子
	stack<vector<int>> gridBackUp;    // 棋局记录
public:
	// 构造函数, 初始化操作界面
	ConnectSix(int onewidth, int oneheight, int twowidth, int twoheight) : wButton(5, vector<vector<int>>(10, vector<int>(4))), gameState(1) {
		wWidth[0] = onewidth; wHeight[0] = oneheight; wWidth[1] = twowidth; wHeight[1] = twoheight;
	};
	// 开始pk函数
	void PK();
private:
	// 界面切换函数
	void changeWindows(int dstWindowsId);
	// 消息捕获和分发函数
	void messageControl();
	// 一级界面创建函数
	void createOneWindows();
	// 二级界面创建函数
	void createTwoWindows(int windowsId);
	// 一号窗口按钮设置
	void setOneButton();
	// 二号窗口按钮设置
	void setTwoButton();
	// 三号窗口按钮设置
	void setThreeButton();
	// 四号窗口按钮设置
	void setFourButton();
	// 五号窗口按钮设置
	void setFiveButton();
	// 一号窗口消息执行函数
	void msgExecuteOne();
	// 二号窗口消息执行函数
	void msgExecuteTwo();
	// 三号窗口消息执行函数
	void msgExecuteThree();
	// 四号窗口消息执行函数
	void msgExecuteFour();
	// 五号窗口消息执行函数
	void msgExecuteFive();
	// 绘制棋盘
	void drawBoard();
	// 内部棋盘初始化
	void gridOriginal();
	// 指定位置下棋
	bool playChess(int x, int y);
	// 判断棋局是否结束
	bool isEnd();
	// 评判电脑给出的坐标是否正确
	bool isFair(int X1, int Y1, int X2, int Y2);
	// 拷贝棋盘副本
	void copy(int gridtemp[15][15]);
	//“悔棋一步”按钮，倒回一步棋
	void GridBack();
	// bot之间PK函数
	void Bot_PK_Bot();
	// 整型数字转char*
	void to_Chars(int x, char s[]);
	// char*转整型
	int to_Int(char s[]);
	// 转换输出
	void createx_y(char x_y[], vector<int>& point);
};


//  电脑bot声明
/*********************************************************************************************/

// 一号Bot函数声明
void Bot1(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2);

// 二号Bot函数声明
void Bot2(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2);

/*
// 三号Bot函数声明, 本作者能力有限(未能实现)
void Bot3(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2);
*/
