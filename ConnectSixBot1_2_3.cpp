#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

#define GRIDSIZE 15
#define grid_black 1
#define grid_white -1
#define grid_blank 0

static int currBotColor;          // Bot所执棋子颜色

/*********************************************************************************************/

static int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // 先x后y，记录棋盘状
static int search_width = 3;
const static int MAX = 1e7;

// 判断是否在棋盘内
inline bool inMap(int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}

// 检查落子是否合法
bool Check(int x, int y) {
	if (!inMap(x, y))
		return false;
	if (gridInfo[x][y] != grid_blank)
		return false;
	return true;
}

// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition(int gridlnfo[GRIDSIZE][GRIDSIZE], int my_road[], int enemy_road[]) {
	//统计横向的有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 5; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 6; k++) {
				if (gridlnfo[i][j + k] == grid_blank) // 该点是空白位，考察横向下一个邻接点
					continue;
				if (gridlnfo[i][j + k] == currBotColor) { // 该点是我方棋子
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
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 5; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 6; k++) {
				if (gridlnfo[j + k][i] == grid_blank) // 该点是空白位，考察竖向下一个邻接点
					continue;
				if (gridlnfo[j + k][i] == currBotColor) { // 该点是我方棋子
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
	for (int i = 0; i < GRIDSIZE - 5; i++) {
		for (int j = 5; j < GRIDSIZE; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 6; k++) {
				if (gridlnfo[i + k][j - k] == grid_blank) // 该点是空白位，考察左斜方向下一个邻接点
					continue;
				if (gridlnfo[i + k][j - k] == currBotColor) { // 该点是我方棋子
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
	for (int i = 0; i < GRIDSIZE - 5; i++) {
		for (int j = 0; j < GRIDSIZE - 5; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 6; k++) {
				if (gridlnfo[i + k][j + k] == grid_blank) // 该点是空白位，考察右斜方向下一个邻接点
					continue;
				if (gridlnfo[i + k][j + k] == currBotColor) { // 该点是我方棋子
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
}

// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate(int my_road[], int enemy_road[], int my_score_of_road[], int enemy_score_of_road[]) {
	int Score = 0;
	for (int i = 0; i < 7; i++) {
		Score += (my_road[i] * my_score_of_road[i] - enemy_road[i] * enemy_score_of_road[i]);
	}
	return Score; //返回对当前棋局状态的评估
}

// 遗传算法Bot1，计算score_of_road分量数组
void Heredity1(int my_score_of_road[], int enemy_score_of_road[], int turnID) {
	int test1[7] = { 0, 17, 78, 141, 788, 1030, WINT_MAX / 3 }, test2[7] = { 0, 17, 78, 141, 10000, 10700, WINT_MAX / 3 };; //经验赋值，也可以遗传算法科学赋值
	int T1[7] = { 0, 17, 80, 50, 30, 30, WINT_MAX / 3 }, T2[7] = { 0, 17, 80, 50, 30, 30, WINT_MAX / 3 };
	if (turnID == 2) {
		for (int i = 0; i < 7; i++) {
			my_score_of_road[i] = T1[i];
			enemy_score_of_road[i] = T2[i];
		}
	}
	else {
		for (int i = 0; i < 7; i++) {
			my_score_of_road[i] = test1[i];
			enemy_score_of_road[i] = test2[i];
		}
	}
	return;
}

// 遗传算法Bot2，计算score_of_road分量数组
void Heredity2(int my_score_of_road[], int enemy_score_of_road[], int e, int turnID) {
	int test1[7] = { 0, 17, 78, 141, 788, 1030, MAX }, test2[7] = { 0, 17, 78, 141, 10000, 10700, MAX }; //经验赋值，也可以遗传算法科学赋值
	int defend1[7] = { 0, 1, 15, 20, 80, 70, MAX }, defend2[7] = { 0, 5, 30, 70, 1000, 1000 , MAX };
	if (turnID < 7) {
		if (!e) {
			for (int i = 0; i < 7; i++) {
				my_score_of_road[i] = defend1[i];
				enemy_score_of_road[i] = defend2[i];
			}
		}
		else {
			for (int i = 0; i < 7; i++) {
				my_score_of_road[i] = test2[i];
				enemy_score_of_road[i] = test1[i];
			}
		}
	}
	else {
		if (!e) {
			for (int i = 0; i < 7; i++) {
				my_score_of_road[i] = test1[i];
				enemy_score_of_road[i] = test2[i];
			}
		}
		else {
			for (int i = 0; i < 7; i++) {
				my_score_of_road[i] = test2[i];
				enemy_score_of_road[i] = test1[i];
			}
		}
	}
	return;
}

// 评估总函数，结合识别和评估两个函数
int FinalEvaluate(int gridlnfo[GRIDSIZE][GRIDSIZE], int e, int turnID, int sigh) {
	int my_road[7] = { 0 }, enemy_road[7] = { 0 };
	int my_score_of_road[7] = { 0 }, enemy_score_of_road[7] = { 0 };
	switch (sigh) {
	case 1:
		Heredity1(my_score_of_road, enemy_score_of_road, turnID);
		break;
	case 2:
		Heredity2(my_score_of_road, enemy_score_of_road, e, turnID);
		break;
	case 3:
		break;
	default: break;
	}
	Recognition(gridlnfo, my_road, enemy_road);
	return Evaluate(my_road, enemy_road, my_score_of_road, enemy_score_of_road);
}

// 开局黑棋阻断
bool Hinder(int gridlnfo[GRIDSIZE][GRIDSIZE], int& x1, int& y1) {
	int x_white[2] = { 0 }, y_white[2] = { 0 };
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++) {
			if (gridlnfo[i][j] == grid_white) {
				if (x_white[0] == 0 && y_white[0] == 0)
					x_white[0] = i, y_white[0] = j;
				else
					x_white[1] = i, y_white[1] = j;
			}
		}
	double k = (x_white[0] - x_white[1]) * (x_white[0] - x_white[1]) + (y_white[0] - y_white[1]) * (y_white[0] - y_white[1]);
	if (sqrt(k) > 5.0)
		return false;
	else {
		if (sqrt(k) < 2.0) {
			if (Check(x_white[0] * 2 - x_white[1], y_white[0] * 2 - y_white[1])) {
				x1 = x_white[0] * 2 - x_white[1], y1 = y_white[0] * 2 - y_white[1];
				return true;
			}
			if (Check(x_white[1] * 2 - x_white[0], y_white[1] * 2 - y_white[0])) {
				x1 = x_white[1] * 2 - x_white[0], y1 = y_white[1] * 2 - y_white[0];
				return true;
			}
			return false;
		}
		else {
			x1 = int((x_white[0] + x_white[1]) / 2);
			y1 = int((y_white[0] + y_white[1]) / 2);
			return Check(x1, y1);
		}
	}
}

void Increase(int gridlnfo[GRIDSIZE][GRIDSIZE], int n, int& x1, int& y1, int& x2, int& y2) {
	int x_black = 0, y_black = 0;
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			if (gridlnfo[i][j] == grid_black)
				x_black = i, y_black = j;
	int a = Check(x_black - 1, y_black + 1), b = Check(x_black + 1, y_black - 1);
	int c = Check(x_black - 1, y_black - 1), d = Check(x_black + 1, y_black + 1);
	if (n == 1) {
		if (a)
			x2 = x_black - 1, y2 = y_black + 1;
		else if (d)
			x2 = x_black + 1, y2 = y_black + 1;
		else if (b)
			x2 = x_black + 1, y2 = y_black - 1;
		else if (c)
			x2 = x_black - 1, y2 = y_black - 1;
		return;
	}
	if (n == 2) {
		if (a && b) {
			x1 = x_black - 1, y1 = y_black + 1;
			x2 = x_black + 1, y2 = y_black - 1;
		}
		else if (c && d) {
			x1 = x_black - 1, y1 = y_black - 1;
			x2 = x_black + 1, y2 = y_black + 1;
		}
		else if (a && c) {
			x1 = x_black - 1, y1 = y_black + 1;
			x2 = x_black - 1, y1 = y_black - 1;
		}
		else if (a && d) {
			x1 = x_black - 1, y1 = y_black + 1;
			x2 = x_black + 1, y2 = y_black + 1;
		}
		else if (b && c) {
			x1 = x_black + 1, y2 = y_black - 1;
			x2 = x_black - 1, y1 = y_black - 1;
		}
		else {
			x1 = x_black + 1, y2 = y_black - 1;
			x2 = x_black + 1, y2 = y_black + 1;
		}
	}
}

double distance(int x1, int y1, int x2, int y2) {
	double dx = (x1 - x2) * (x1 - x2);
	double dy = (y1 - y2) * (y1 - y2);
	return sqrt((dx + dy));
}

// 开局库。增加随机性。
void opening(int gridlnfo[GRIDSIZE][GRIDSIZE], int& x1, int& y1, int& x2, int& y2, int turn) {
	if (currBotColor == grid_black) {
		if (turn == 1) {
			srand((unsigned)time(NULL));
			int d_x = rand() % 1;
			srand((unsigned)time(NULL));
			int d_y = rand() % 1;
			x1 = 6 + d_x;
			y1 = 6 + d_y;
			x2 = -1; y2 = -1;
			return;
		}
		if (turn == 3) {
			if (Hinder(gridlnfo, x1, y1))
				Increase(gridlnfo, 1, x1, y1, x2, y2);
			else
				Increase(gridlnfo, 2, x1, y1, x2, y2);
			return;
		}
	}
	else {
		if (turn == 2) {
			int x_black = 0, y_black = 0;
			for (int i = 0; i < GRIDSIZE; i++)
				for (int j = 0; j < GRIDSIZE; j++)
					if (gridlnfo[i][j] == grid_black) {
						x_black = i; y_black = j;
					}
			double maxnum1 = 10000; double dis;	double maxnum2 = 10000;
			int d_x[4] = { 0, 1, 0, -1 }, d_y[4] = { -1, 0, 1, 0 };
			for (int i = 0; i < 4; i++) {
				if (Check(x_black + d_x[i], y_black + d_y[i])) {
					dis = distance(x_black + d_x[i], y_black + d_y[i], 7, 7);
					if (dis < maxnum1) {
						x1 = x_black + d_x[i]; y1 = y_black + d_y[i];
						maxnum1 = dis;
					}
				}
			}
			gridlnfo[x1][y1] = currBotColor;
			for (int i = 0; i < 4; i++) {
				if (Check(x_black + d_x[i], y_black + d_y[i])) {
					dis = distance(x_black + d_x[i], y_black + d_y[i], 7, 7);
					if (dis < maxnum2) {
						x2 = x_black + d_x[i]; y2 = y_black + d_y[i];
						maxnum2 = dis;
					}
				}
			}
			gridlnfo[x1][y1] = grid_blank;
		}
		if (turn == 4) {
			int x_white[2] = { 0 }, y_white[2] = { 0 };
			for (int i = 0; i < GRIDSIZE; i++)
				for (int j = 0; j < GRIDSIZE; j++) {
					if (gridlnfo[i][j] == grid_white) {
						if (x_white[0] == 0 && y_white[0] == 0)
							x_white[0] = i, y_white[0] = j;
						else
							x_white[1] = i, y_white[1] = j;
					}
				}
			int dx[4] = { -2, 0, 2, 0 }, dy[4] = { 0, 2, 0, -2 };
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 4; j++) {
					if (Check(x_white[i] + dx[j], y_white[i] + dy[j])) {
						if (x1 == 0 && y1 == 0) {
							x1 = x_white[i] + dx[j]; y1 = y_white[i] + dy[j];
						}
						else {
							x2 = x_white[i] + dx[j]; y2 = y_white[i] + dy[j];
							return;
						}
					}

				}
		}
	}
}

// 搜索算法，无博弈
void Search(int gridlnfo[GRIDSIZE][GRIDSIZE], int& x1, int& y1, int& x2, int& y2, int turnID) {
	int max_score = INT16_MIN;
	vector<vector<int>>	points;
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++) {
			if (Check(i, j)) {
				points.push_back({ i, j });
			}
		}
	int size = points.size();
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++) {
			gridlnfo[points[i][0]][points[i][1]] = currBotColor;
			gridlnfo[points[j][0]][points[j][1]] = currBotColor;
			int temp_score = FinalEvaluate(gridInfo, 0, turnID, 1);
			//cout << temp_score << endl;
			if (temp_score > max_score) {
				max_score = temp_score;
				y1 = points[i][0]; x1 = points[i][1];
				y2 = points[j][0]; x2 = points[j][1];
			}
			gridlnfo[points[i][0]][points[i][1]] = grid_blank;
			gridlnfo[points[j][0]][points[j][1]] = grid_blank;
		}
	return;
}

// 博弈搜索
void GameTreeSearch(int gridInfo[GRIDSIZE][GRIDSIZE], int& x1, int& y1, int& x2, int& y2, int turnID) {
	int threshold = 0.98 * (double)CLOCKS_PER_SEC;
	int start_time, current_time;
	start_time = current_time = clock();
	//尝试下一步，进入第一层
	vector<vector<int>>	points;
	for (int i = 0; i < GRIDSIZE; i++)  // 把可下的点放入容器中
		for (int j = 0; j < GRIDSIZE; j++) {
			if (Check(i, j)) {
				points.push_back({ i, j });
			}
		}
	int size = points.size();
	if (size == 2) {
		y1 = points[0][0], x1 = points[0][1];
		y2 = points[1][0], x2 = points[1][1];
		return;
	}
	vector<vector<int>> Temp, rest;
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++) {
			gridInfo[points[i][0]][points[i][1]] = currBotColor;
			gridInfo[points[j][0]][points[j][1]] = currBotColor;
			int temp_score = FinalEvaluate(gridInfo, 0, turnID, 2);
			if (temp_score > 200000) {
				y1 = points[i][0], x1 = points[i][1];
				y2 = points[j][0], x2 = points[j][1];
				gridInfo[points[i][0]][points[i][1]] = grid_blank;
				gridInfo[points[j][0]][points[j][1]] = grid_blank;
				return;
			}
			Temp.push_back({ temp_score, 1, points[i][0], points[i][1], points[j][0], points[j][1] });
			gridInfo[points[i][0]][points[i][1]] = grid_blank;
			gridInfo[points[j][0]][points[j][1]] = grid_blank;
		}
	sort(Temp.begin(), Temp.end(), greater<vector<int>>()); // 对rest中局面进行降序排列
	int Temp_size = Temp.size();
	for (int i = 0; i < Temp_size && i < search_width; i++) {
		//cout << Temp[i][0] << ' ' << Temp[i][2] << ' ' << Temp[i][3] << ' ' << Temp[i][4] << ' ' << Temp[i][5] << endl;
		rest.push_back(Temp[i]);
	}
	int rest_size = rest.size();
	//取前50个评分局面进行对方模拟下(最优下法)
	for (int i = 0; i < rest_size && i < search_width; i++) {
		gridInfo[rest[i][2]][rest[i][3]] = currBotColor;
		gridInfo[rest[i][4]][rest[i][5]] = currBotColor;
		int max_score = INT16_MIN;
		int m1, n1, m2, n2;
		for (int m = 0; m < size; m++) {
			if (gridInfo[points[m][0]][points[m][1]] != grid_blank)
				continue;
			for (int n = m + 1; n < size; n++) {
				if (gridInfo[points[n][0]][points[n][1]] != grid_blank)
					continue;
				gridInfo[points[m][0]][points[m][1]] = -1 * currBotColor;
				gridInfo[points[n][0]][points[n][1]] = -1 * currBotColor;
				int temp_score = -1 * FinalEvaluate(gridInfo, 1, turnID, 2);
				if (temp_score > max_score) {
					m1 = points[m][0], n1 = points[m][1];
					m2 = points[n][0], n2 = points[n][1];
					max_score = temp_score;
				}
				gridInfo[points[m][0]][points[m][1]] = grid_blank;
				gridInfo[points[n][0]][points[n][1]] = grid_blank;
			}
		}
		if (max_score > 20000) {
			rest[i][1] = 0;
			rest[i][0] = INT16_MIN;
		}
		else {
			rest[i].push_back(m1); rest[i].push_back(n1); rest[i].push_back(m2); rest[i].push_back(n2);
		}
		gridInfo[rest[i][2]][rest[i][3]] = grid_blank;
		gridInfo[rest[i][4]][rest[i][5]] = grid_blank;
	}
	// 在筛出的部分，模拟我方下棋，取分数最大的(第三层了)
	for (int i = 0; i < rest_size && i < search_width; i++) {
		if (rest[i][1] == 0)
			continue;
		gridInfo[rest[i][2]][rest[i][3]] = currBotColor;
		gridInfo[rest[i][4]][rest[i][5]] = currBotColor;
		gridInfo[rest[i][6]][rest[i][7]] = -1 * currBotColor;
		gridInfo[rest[i][8]][rest[i][9]] = -1 * currBotColor;
		int max_score = INT16_MIN;
		for (int m = 0; m < size; m++) {
			if (gridInfo[points[m][0]][points[m][1]] != grid_blank)
				continue;
			for (int n = m + 1; n < size; n++) {
				if (gridInfo[points[n][0]][points[n][1]] != grid_blank)
					continue;
				gridInfo[points[m][0]][points[m][1]] = currBotColor;
				gridInfo[points[n][0]][points[n][1]] = currBotColor;
				int temp_score = FinalEvaluate(gridInfo, 0, turnID, 2);
				// 判断是否超时
				current_time = clock();
				if (current_time - start_time >= threshold) {
					for (int k = 0; k < rest_size; k++) {
						if (rest[k][1] == 1) {
							y1 = rest[k][2], x1 = rest[k][3];
							y2 = rest[k][4], x2 = rest[k][5];
							return;
						}
					}
					y1 = rest[0][2], x1 = rest[0][3];
					y2 = rest[0][4], x2 = rest[0][5];
					return;
				}
				if (temp_score > max_score) {
					max_score = temp_score;
				}
				gridInfo[points[m][0]][points[m][1]] = grid_blank;
				gridInfo[points[n][0]][points[n][1]] = grid_blank;
			}
		}
		rest[i][0] = max_score;
		gridInfo[rest[i][2]][rest[i][3]] = grid_blank;
		gridInfo[rest[i][4]][rest[i][5]] = grid_blank;
		gridInfo[rest[i][6]][rest[i][7]] = grid_blank;
		gridInfo[rest[i][8]][rest[i][9]] = grid_blank;
	}
	sort(rest.begin(), rest.end(), greater<vector<int>>());
	y1 = rest[0][2], x1 = rest[0][3];
	y2 = rest[0][4], x2 = rest[0][5];
	return;
}


/*********************************************************************************************/

// 一号Bot(简单)
void Bot1(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2) {
	currBotColor = chessColor;
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			gridInfo[i][j] = gridlnfo[i][j];
	if (Rounds <= 2) {
		opening(gridInfo, Y1, X1, Y2, X2, Rounds);
	}
	else
		Search(gridInfo, X1, Y1, X2, Y2, Rounds);
	return;
}

// 二号Bot(中等)
void Bot2(int gridlnfo[15][15], int Rounds, int chessColor, int& X1, int& Y1, int& X2, int& Y2) {
	currBotColor = chessColor;
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			gridInfo[i][j] = gridlnfo[i][j];
	if (Rounds <= 2) {
		opening(gridInfo, Y1, X1, Y2, X2, Rounds);
	}
	else
		GameTreeSearch(gridInfo, X1, Y1, X2, Y2, Rounds);
	return;
}