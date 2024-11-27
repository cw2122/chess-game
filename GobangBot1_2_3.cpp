#include <vector>
#include <algorithm>
using namespace std;

#define GRIDSIZE 15
#define grid_black 1
#define grid_white -1
#define grid_blank 0

static int currBotColor;          // Bot所执棋子颜色


/*********************************************************************************************/
// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition(int gridlnfo[15][15]);
// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate();

// 一号Bot函数定义
const int my_score_of_road1[6] = { 0, 1, 5, 10, 50, 200 }, enemy_score_of_road1[6] = { 0, 1, 5, 25, 100, 200 };
int my_road1[6], enemy_road1[6];  // 统计有效路的数组

// 电脑一号， 一步贪心
void Bot1(int gridlnfo[15][15], int Rounds, int chessColor, int& X, int& Y) {
	currBotColor = chessColor;
	if (Rounds <= 2) {
		if (Rounds == 1) {
			X = 7; Y = 7;
		}
		else {
			if (gridlnfo[7][7] == 0) {
				X = 7; Y = 7;
			}
			else {
				X = 8; Y = 6;
			}
		}
		return;
	}
	vector<vector<int>>	points;
	for (int i = 0; i < GRIDSIZE; i++)  // 把可下的点放入容器中
		for (int j = 0; j < GRIDSIZE; j++) {
			if (gridlnfo[i][j] == grid_blank) {
				points.push_back({ i, j });
			}
		}
	int maxscore = INT_MIN;
	for (auto point : points) {
		gridlnfo[point[0]][point[1]] = currBotColor;
		Recognition(gridlnfo);
		gridlnfo[point[0]][point[1]] = grid_blank;
		int score = Evaluate();
		if (score > maxscore) {
			maxscore = score;
			X = point[1];
			Y = point[0];
		}
	}
	return;
}

// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition(int gridlnfo[15][15]) {
	for (int i = 0; i < 6; i++) {
		my_road1[i] = enemy_road1[i] = 0;
	}
	//统计横向的有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road1[mynum]++;
				enemy_road1[enemynum]++;
			}
		}
	}

	//统计竖向有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road1[mynum]++;
				enemy_road1[enemynum]++;
			}
		}
	}

	//统计左斜方向有效路
	for (int i = 0; i < GRIDSIZE - 4; i++) {
		for (int j = 4; j < GRIDSIZE; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road1[mynum]++;
				enemy_road1[enemynum]++;
			}
		}
	}

	//统计右斜方向有效路
	for (int i = 0; i < GRIDSIZE - 4; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road1[mynum]++;
				enemy_road1[enemynum]++;
			}
		}
	}
}

// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate() {
	int Score = 0;
	for (int i = 0; i < 6; i++) {
		Score += (my_road1[i] * my_score_of_road1[i] - enemy_road1[i] * enemy_score_of_road1[i]);
	}
	return Score; //返回对当前棋局状态的评估
}
/*********************************************************************************************/

/*********************************************************************************************/
// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition2(int gridlnfo[15][15]);
// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate2();

// 二号Bot函数定义
const int my_score_of_road2[6] = { 0, 1, 5, 20, 80, 500 }, enemy_score_of_road2[6] = { 0, 1, 5, 20, 80, 500 };
int my_road2[6], enemy_road2[6];  // 统计有效路的数组

// 电脑二号
void Bot2(int gridlnfo[15][15], int Rounds, int chessColor, int& X, int& Y) {
	currBotColor = chessColor;
	if (Rounds <= 2) {
		if (Rounds == 1) {
			X = 7; Y = 7;
		}
		else {
			if (gridlnfo[7][7] == 0) {
				X = 7; Y = 7;
			}
			else {
				X = 8; Y = 6;
			}
		}
		return;
	}
	vector<vector<int>>	points;
	for (int i = 0; i < GRIDSIZE; i++)  // 把可下的点放入容器中
		for (int j = 0; j < GRIDSIZE; j++) {
			if (gridlnfo[i][j] == grid_blank) {
				points.push_back({ i, j });
			}
		}
	int maxscore = INT_MIN;
	for (auto point1 : points) {
		gridlnfo[point1[0]][point1[1]] = currBotColor;
		int minscore = INT_MAX;
		for (auto point2 : points) {
			if (gridlnfo[point2[0]][point2[1]] != 0)
				continue;
			gridlnfo[point2[0]][point2[1]] = -currBotColor;
			Recognition2(gridlnfo);
			gridlnfo[point2[0]][point2[1]] = grid_blank;
			int score = Evaluate2();
			if (score < minscore) {
				minscore = score;
			}
		}
		gridlnfo[point1[0]][point1[1]] = grid_blank;
		if (minscore >= maxscore) {
			if (minscore == maxscore) {
				if ((point1[0] - 7) * (point1[0] - 7) + (point1[1] - 7) * (point1[1] - 7) >= (Y - 7) * (Y - 7) + (X - 7) * (X - 7)) {
					continue;
				}
			}
			maxscore = minscore;
			X = point1[1];
			Y = point1[0];
		}
	}
	return;
}

// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition2(int gridlnfo[15][15]) {
	for (int i = 0; i < 6; i++) {
		my_road2[i] = enemy_road2[i] = 0;
	}
	//统计横向的有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road2[mynum]++;
				enemy_road2[enemynum]++;
			}
		}
	}

	//统计竖向有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road2[mynum]++;
				enemy_road2[enemynum]++;
			}
		}
	}

	//统计左斜方向有效路
	for (int i = 0; i < GRIDSIZE - 4; i++) {
		for (int j = 4; j < GRIDSIZE; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road2[mynum]++;
				enemy_road2[enemynum]++;
			}
		}
	}

	//统计右斜方向有效路
	for (int i = 0; i < GRIDSIZE - 4; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road2[mynum]++;
				enemy_road2[enemynum]++;
			}
		}
	}
}

// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate2() {
	int Score = 0;
	for (int i = 0; i < 6; i++) {
		Score += (my_road2[i] * my_score_of_road2[i] - enemy_road2[i] * enemy_score_of_road2[i]);
	}
	return Score; //返回对当前棋局状态的评估
}
/*********************************************************************************************/

/*********************************************************************************************/
// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition3(int gridlnfo[15][15]);
// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate3();
// 局部识别+评分函数
int localEvaluate3(int gridlnfo[15][15], int x, int y, int score, int color);

// 三号Bot函数定义
const int my_score_of_road3[6] = { 0, 1, 5, 20, 100, 1000 }, enemy_score_of_road3[6] = { 0, 1, 5, 20, 100, 1000 };
int my_road3[6], enemy_road3[6];  // 统计有效路的数组
const int search_width = 20;   // 搜索宽度

// 电脑三号
void Bot3(int gridlnfo[15][15], int Rounds, int chessColor, int& X, int& Y) {
	currBotColor = chessColor;
	if (Rounds <= 2) {
		if (Rounds == 1) {
			X = 7; Y = 7;
		}
		else {
			if (gridlnfo[7][7] == 0) {
				X = 7; Y = 7;
			}
			else {
				X = 8; Y = 6;
			}
		}
		return;
	}
	vector<vector<int>>	points;
	for (int i = 0; i < GRIDSIZE; i++)  // 把可下的点放入容器中
		for (int j = 0; j < GRIDSIZE; j++) {
			if (gridlnfo[i][j] == grid_blank) {
				points.push_back({ i, j });
			}
		}
	// 识别初始局面， 获得初始评分
	Recognition3(gridlnfo);
	int original_score = Evaluate3();
	// 第一层筛选评分前search_width的点
	vector<vector<int>> One;
	for (auto i : points) {
		gridlnfo[i[0]][i[1]] = currBotColor;
		int temp_score = localEvaluate3(gridlnfo, i[0], i[1], original_score, currBotColor);
		gridlnfo[i[0]][i[1]] = grid_blank;
		One.push_back({ temp_score, i[0], i[1] });
	}
	sort(One.begin(), One.end(), greater<vector<int>>());
	int maxscore = INT_MIN;
	for (int i = 0; i < search_width && i < One.size(); i++) {
		gridlnfo[One[i][1]][One[i][2]] = currBotColor;
		vector<vector<int>> Two;
		for (auto point2 : points) {
			if (gridlnfo[point2[0]][point2[1]] != 0)
				continue;
			gridlnfo[point2[0]][point2[1]] = -currBotColor;
			int temp1_score = localEvaluate3(gridlnfo, point2[0], point2[1], One[i][0], -currBotColor);
			gridlnfo[point2[0]][point2[1]] = grid_blank;
			Two.push_back({ temp1_score, point2[0], point2[1] });
		}
		sort(Two.begin(), Two.end());
		int minscore = INT_MAX;
		for (int j = 0; j < search_width && j < Two.size(); j++) {
			gridlnfo[Two[j][1]][Two[j][2]] = -currBotColor;
			vector<vector<int>> Three;
			for (auto point3 : points) {
				if (gridlnfo[point3[0]][point3[1]] != 0)
					continue;
				gridlnfo[point3[0]][point3[1]] = currBotColor;
				int temp2_score = localEvaluate3(gridlnfo, point3[0], point3[1], Two[j][0], currBotColor);
				gridlnfo[point3[0]][point3[1]] = grid_blank;
				Three.push_back({ temp2_score, point3[0], point3[1] });
			}
			sort(Three.begin(), Three.end(), greater<vector<int>>());
			int max2score = INT_MIN;
			for (int k = 0; k < search_width && Three.size(); k++) {
				gridlnfo[Three[k][1]][Three[k][2]] = currBotColor;
				int min2score = INT_MAX;
				for (auto point4 : points) {
					if (gridlnfo[point4[0]][point4[1]] != 0)
						continue;
					gridlnfo[point4[0]][point4[1]] = -currBotColor;
					int temp3_score = localEvaluate3(gridlnfo, point4[0], point4[1], Three[k][0], -currBotColor);
					gridlnfo[point4[0]][point4[1]] = grid_blank;
					if (temp3_score < min2score)
						min2score = temp3_score;
				}
				if (min2score >= max2score)
					max2score = min2score;
				gridlnfo[Three[k][1]][Three[k][2]] = grid_blank;
			}
			if (max2score < minscore)
				minscore = max2score;
			gridlnfo[Two[j][1]][Two[j][2]] = grid_blank;
		}
		if (minscore >= maxscore) {
			if (minscore == maxscore) {
				if ((One[i][1] - 7) * (One[i][1] - 7) + (One[i][2] - 7) * (One[i][2] - 7) >= (Y - 7) * (Y - 7) + (X - 7) * (X - 7)) {
					continue;
				}
			}
			maxscore = minscore;
			X = One[i][2];
			Y = One[i][1];
		}
		gridlnfo[One[i][1]][One[i][2]] = grid_blank;
	}
	return;
}

// 识别函数，获取棋盘信息，统计我方和对方的“有效”路。
void Recognition3(int gridlnfo[15][15]) {
	for (int i = 0; i < 6; i++) {
		my_road3[i] = enemy_road3[i] = 0;
	}
	//统计横向的有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road3[mynum]++;
				enemy_road3[enemynum]++;
			}
		}
	}

	//统计竖向有效路
	for (int i = 0; i < GRIDSIZE; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road3[mynum]++;
				enemy_road3[enemynum]++;
			}
		}
	}

	//统计左斜方向有效路
	for (int i = 0; i < GRIDSIZE - 4; i++) {
		for (int j = 4; j < GRIDSIZE; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road3[mynum]++;
				enemy_road3[enemynum]++;
			}
		}
	}

	//统计右斜方向有效路
	for (int i = 0; i < GRIDSIZE - 4; i++) {
		for (int j = 0; j < GRIDSIZE - 4; j++) {
			int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
			for (int k = 0; k < 5; k++) {
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
				my_road3[mynum]++;
				enemy_road3[enemynum]++;
			}
		}
	}
}

// 评估函数，利用获取的有效路信息和遗传算法计算的分量值，给当前局面算一个分数。
int Evaluate3() {
	int Score = 0;
	for (int i = 0; i < 6; i++) {
		Score += (my_road3[i] * my_score_of_road3[i] - enemy_road3[i] * enemy_score_of_road3[i]);
	}
	return Score; //返回对当前棋局状态的评估
}

// 局部识别+评分函数
int localEvaluate3(int gridlnfo[15][15], int x, int y, int score, int color) {
	for (int i = 0; i < 6; i++) {
		my_road3[i] = enemy_road3[i] = 0;
	}
	gridlnfo[x][y] = grid_blank;
	int startx, starty, endx, endy;
	// 横向区域局部有效路
	starty = (y - 4 >= 0) ? (y - 4) : 0;
	endy = (y + 4 < GRIDSIZE) ? y : (y - (y + 4 - (GRIDSIZE - 1)));
	for (int j = starty; j <= endy; j++) {
		int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
		for (int k = 0; k < 5; k++) {
			if (gridlnfo[x][j + k] == grid_blank) // 该点是空白位，考察横向下一个邻接点
				continue;
			if (gridlnfo[x][j + k] == currBotColor) { // 该点是我方棋子
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
			my_road3[mynum]++;
			enemy_road3[enemynum]++;
		}
	}

	// 纵向区域局部有效路
	startx = (x - 4 >= 0) ? (x - 4) : 0;
	endx = (x + 4 < GRIDSIZE) ? x : (x - (x + 4 - (GRIDSIZE - 1)));
	for (int j = startx; j <= endx; j++) {
		int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
		for (int k = 0; k < 5; k++) {
			if (gridlnfo[j + k][y] == grid_blank) // 该点是空白位，考察竖向下一个邻接点
				continue;
			if (gridlnfo[j + k][y] == currBotColor) { // 该点是我方棋子
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
			my_road3[mynum]++;
			enemy_road3[enemynum]++;
		}
	}

	// 左斜区域局部有效路
	if (x - 4 >= 0 && y + 4 < GRIDSIZE) {
		startx = x - 4; starty = y + 4;
	}
	else {
		int dx = x, dy = (GRIDSIZE - 1) - y;
		startx = (dx < dy) ? (x - dx) : (x - dy);
		starty = (dx < dy) ? (y + dx) : (y + dy);
	}
	if (x + 4 < GRIDSIZE && y - 4 >= 0) {
		endx = x; endy = y;
	}
	else {
		int dx = (x + 4 - (GRIDSIZE - 1)), dy = 4 - y;
		endx = (dx > dy) ? (x - dx) : (x - dy);
		endy = (dx > dy) ? (y + dx) : (y + dy);
	}
	while (startx <= endx && starty >= endy) {
		int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
		for (int k = 0; k < 5; k++) {
			if (gridlnfo[startx + k][starty - k] == grid_blank) // 该点是空白位，考察左斜方向下一个邻接点
				continue;
			if (gridlnfo[startx + k][starty - k] == currBotColor) { // 该点是我方棋子
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
			my_road3[mynum]++;
			enemy_road3[enemynum]++;
		}
		startx++;
		starty--;
	}

	// 右斜区域局部有效路
	if (x - 4 >= 0 && y - 4 >= 0) {
		startx = x - 4; starty = y - 4;
	}
	else {
		int dx = x, dy = y;
		startx = (dx < dy) ? (x - dx) : (x - dy);
		starty = (dx < dy) ? (y - dx) : (y - dy);
	}
	if (x + 4 < GRIDSIZE && y + 4 < GRIDSIZE) {
		endx = x; endy = y;
	}
	else {
		int dx = (x + 4 - (GRIDSIZE - 1)), dy = (y + 4 - (GRIDSIZE - 1));
		endx = (dx > dy) ? (x - dx) : (x - dy);
		endy = (dx > dy) ? (y - dx) : (y - dy);
	}
	while (startx <= endx && starty <= endy) {
		int mynum = 0, enemynum = 0, e = 1; //mynum,enemynum该路上我方和对方的棋子数，e表示该路是否有效
		for (int k = 0; k < 5; k++) {
			if (gridlnfo[startx + k][starty + k] == grid_blank) // 该点是空白位，考察右斜方向下一个邻接点
				continue;
			if (gridlnfo[startx + k][starty + k] == currBotColor) { // 该点是我方棋子
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
			my_road3[mynum]++;
			enemy_road3[enemynum]++;
		}
		startx++;
		starty++;
	}
	int oldscore = Evaluate3();
	if (color == currBotColor) {
		for (int i = 4; i >= 0; i--)
			my_road3[i + 1] = my_road3[i];
		my_road3[0] = 0;
		for (int i = 0; i < 6; i++)
			enemy_road3[i] = 0;
	}
	else {
		for (int i = 4; i >= 0; i--)
			enemy_road3[i + 1] = enemy_road3[i];
		enemy_road3[0] = 0;
		for (int i = 0; i < 6; i++)
			my_road3[i] = 0;
	}
	int newscore = Evaluate3();
	gridlnfo[x][y] = color;
	return score - oldscore + newscore;
}
/*********************************************************************************************/