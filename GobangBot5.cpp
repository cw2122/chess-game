#include <iostream>

using namespace std;

const int SIZE = 15;
static int board[SIZE][SIZE] = { 0 };

const int FIVE = 100000;
const int LIVE_FOUR = 10000;
const int DEAD_FOUR = 10000;
const int LIVE_THREE = 700;
const int SLEEP_THREE = 500;
const int LIVE_TWO = 60;
const int SLEEP_TWO = 40;
const int LIVE_ONE = 30;
const int SLEEP_ONE = 15;
const int JUMP_THREE = 1000;
const int JUMP_FOUR = 8000; // 跳活四
const int DOUBLE_THREE = 5000; // 双三
const int DOUBLE_FOUR = 20000; // 双四
// 检查在一个方向上的棋型
int evaluateDirection(int x, int y, int dx, int dy, int player) {
    int max_line = 0;
    int left_space = 0, right_space = 0;
    bool left_blocked = false, right_blocked = false;

    // 向右检查
    for (int i = 1; i < 5 && x + i * dx < SIZE && x + i * dx >= 0 && y + i * dy < SIZE && y + i * dy >= 0; ++i) {
        if (board[x + i * dx][y + i * dy] == player) {
            max_line++;
        }
        else {
            if (board[x + i * dx][y + i * dy] == 0) {
                if (i < 4 && board[x + (i + 1) * dx][y + (i + 1) * dy] == player) {
                    max_line++;
                    right_space = 1;
                }
            }
            else {
                right_blocked = true;
            }
            break;
        }
    }

    // 向左检查
    for (int i = 1; i < 5 && x - i * dx < SIZE && x - i * dx >= 0 && y - i * dy < SIZE && y - i * dy >= 0; ++i) {
        if (board[x - i * dx][y - i * dy] == player) {
            max_line++;
        }
        else {
            if (board[x - i * dx][y - i * dy] == 0) left_space = 1;
            else left_blocked = true;
            break;
        }
    }

    // 根据不同棋型评分
    if (max_line >= 4) return FIVE;
    if (max_line == 3) {
        if (!left_blocked && !right_blocked && (left_space || right_space)) return JUMP_FOUR;  // 跳活四
        if (!left_blocked && !right_blocked) return LIVE_FOUR;
        if (left_blocked != right_blocked) return DEAD_FOUR;
    }
    if (max_line == 2) {
        if (!left_blocked && !right_blocked && (left_space || right_space)) return JUMP_THREE;  // 跳活三
        if (!left_blocked && !right_blocked) return LIVE_THREE;
        if (left_blocked != right_blocked) return SLEEP_THREE;
    }
    if (max_line == 1) {
        if (!left_blocked && !right_blocked) return LIVE_TWO;
        if (left_blocked != right_blocked) return SLEEP_TWO;
    }
    if (max_line == 0) {
        if (!left_blocked && !right_blocked) return LIVE_ONE;
        if (left_blocked != right_blocked) return SLEEP_ONE;
    }
    return 0;
}

// 总的评估函数，累积四个方向的得分
int evaluate(int x, int y, int player) {
    if (board[x][y] != 0) return 0;  // 确保评估空位

    board[x][y] = player;  // 假设在这里下了一个棋子
    int score = 0;
    int live_three_count = 0;  // 记录活三的数量
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
    for (int i = 0; i < 4; ++i) {
        int temp_score = evaluateDirection(x, y, directions[i][0], directions[i][1], player);
        score += temp_score;
        if (temp_score == LIVE_THREE) live_three_count++;
    }
    board[x][y] = 0;  // 恢复空位

    if (live_three_count == 1) score += LIVE_THREE;  // 如果只有一个活三，加上单活三的分数
    if (live_three_count >= 2) score += DOUBLE_THREE;  // 如果有两个或更多活三，加上双活三的分数

    return score;
}

void Bot5(int gridlnfo[15][15], int Rounds, int chessColor, int& X, int& Y) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chessColor == 1) {
                board[j][i] = gridlnfo[i][j];
            }
            else {
                board[j][i] = -1 * gridlnfo[i][j];
            }
        }
    }
    int new_x = -1, new_y = -1;
    if (Rounds <= 2) {
        if (Rounds == 1) {
            new_x = 7; new_y = 7;
        }
        else {
            if (gridlnfo[7][7] == 0) {
                new_x = 7; new_y = 7;
            }
            else {
                new_x = 8; new_y = 6;
            }
        }
    }
    else {
        int max_score = -1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    int score = evaluate(i, j, 1) + evaluate(i, j, -1); // 我方和对方得分
                    if (score > max_score) {
                        max_score = score;
                        new_x = i;
                        new_y = j;
                    }
                }
            }
        }
    }

    X = new_x; Y = new_y; // 输出最终选择的坐标
    return;
}