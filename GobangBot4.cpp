
// ��ͥ���ṩ�������ο����벻Ҫ��Ϯ��ת��
#define  _CRT_SECURE_NO_WARNINGS 1
#define _BOTZONE_ONLINE
#include <vector>
#include <tuple>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string.h>
#include <unordered_map>
#include<unordered_set>
#include<algorithm>
#include <chrono>
#include <iomanip> 
#include <ctime>

using namespace std; 

#ifndef _BOTZONE_ONLINE
std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::high_resolution_clock::now();
std::chrono::milliseconds max_search_time = std::chrono::milliseconds(static_cast<long long>(0.95 * 1000)); // 0.95��

#endif // !_BOTZONE_ONLINE
int new_x, new_y;
int cutting_cnt = 0;
const int boardSIZE = 15;
int blackScores[15][15] = { 0 };
int whiteScores[15][15] = { 0 };
//vector<pair<int, int>> history;
const int pos_inf = 0x3f3f3f3f;//������
const int neg_inf = -0x3f3f3f3f;//������//������ƴ����� �ҿ���

int depth = 1;//���������ĵݹ����
int countLimit = 10;//ÿ���ڵ�����Ƶ�����ӽڵ���
int allStepsCnt = 0;//��ǰ������������

//shape����
int shapeCache[3][4][15][15] = { 0 };//0 ��ʾ�����ӣ�1��ʾ�ҷ���2��ʾ�з� 

static int board[15][15] = { 0 };//1�����ҷ���2����з���0 ��ʾ��λ��
//�Ե�ǰ���͵Ĺ�ֵ
const int FIVE_SCORE = 10000000;
const int BLOCK_FIVE_SCORE = FIVE_SCORE;
const int FOUR_SCORE = 100000;
const int FOUR_FOUR_SCORE = FOUR_SCORE; // ˫����
const int FOUR_THREE_SCORE = FOUR_SCORE; // ���Ļ���
const int THREE_THREE_SCORE = FOUR_SCORE / 2; // ˫��
const int BLOCK_FOUR_SCORE = 1500;
const int THREE_SCORE = 1000;
const int BLOCK_THREE_SCORE = 150;
const int TWO_TWO_SCORE = 200; // ˫���
const int TWO_SCORE = 100;
const int BLOCK_TWO_SCORE = 15;
const int ONE_SCORE = 10;
const int BLOCK_ONE_SCORE = 1;

enum Shape {//���ӵ���״
    FIVE = 5,
    BLOCK_FIVE = 50,
    FOUR = 4,
    FOUR_FOUR = 44,
    FOUR_THREE = 43,
    THREE_THREE = 33,
    BLOCK_FOUR = 40,
    THREE = 3,
    BLOCK_THREE = 30,
    TWO_TWO = 22,
    BLOCK_TWO = 20,
    TWO = 2,
    ONE = 1,
    NONE = 0
};

void printBoard() {
    /*
    // ��ӡ�к�
    std::cout << "    ";
    for (int i = 0; i < 15; i++) {
        std::cout << std::setw(3) << i; // ���ÿ��Ϊ3
    }
    std::cout << std::endl;

    // ��ӡ�кź�����
    for (int i = 0; i < 15; i++) {
        // ��ӡ�к�
        std::cout << std::setw(3) << i; // ���ÿ��Ϊ3

        // ��ӡ����
        for (int j = 0; j < 15; j++) {
            if (board[i][j] == 0) {
                std::cout << std::setw(3) << "0"; // ���ÿ��Ϊ3����ӡ�հ�
            }
            else if (board[i][j] == 1) {
                std::cout << std::setw(3) << "1"; // ���ÿ��Ϊ3
            }
            else if (board[i][j] == 2) {
                std::cout << std::setw(3) << "2"; // ���ÿ��Ϊ3
            }
        }
        std::cout << std::endl;
    }
    */
}

// ��״ת��������ע������ķ����ǵ�ǰλ�û�û�����ӵķ���
int getRealShapeScore(int shape) {
    switch (shape) {
    case FIVE:
        return FIVE_SCORE;
    case BLOCK_FIVE://����
        return FIVE_SCORE;
    case FOUR://����
        return FOUR_SCORE;
    case FOUR_FOUR://˫����
        return FOUR_SCORE;
    case FOUR_THREE://��������
        return FOUR_SCORE;
    case BLOCK_FOUR://����
        return BLOCK_FOUR_SCORE;
    case THREE://����
        return BLOCK_FOUR_SCORE;
    case THREE_THREE:
        return THREE_THREE_SCORE;
    case BLOCK_THREE://����
        return BLOCK_THREE_SCORE;
    case TWO:
        return TWO_SCORE;
    case TWO_TWO:
        return TWO_TWO_SCORE;
    default:
        return 0;
    }
}

const vector<pair<int, int>> allDirections = {
  {0, 1},  // Horizontal
  {1, 0},  // Vertical
  {1, 1},
  {1, -1}  // Diagonal /
};

//��ά����ת��Ϊһά���   ��Ҫ��shapeCache�е�
int direction2index(int ox, int oy) {
    if (ox == 0) return 0; // |
    if (oy == 0) return 1; // -
    if (ox == oy) return 2;
    if (ox != oy) return 3; // /
}

bool isValid(int x, int y) {
    return x >= 0 && x < boardSIZE && y >= 0 && y < boardSIZE;
}
//һάλ�ñ��ת��Ϊ��ά����
std::vector<int> position2Coordinate(int position, int size) {
    return { position / size, position % size };
}

//��ά����ת��Ϊһάλ�ñ��
int coordinate2Position(int x, int y, int size) {
    return x * size + y;
}

struct ShapeInfo {
    int selfCount;//�Լ�������
    int totalLength;//��ǰ�������ɵ��ܳ���
    int noEmptySelfCount;//û�п�λ�������ӵ�����
    int OneEmptySelfCount;//ֻ��һ����λ��ǰ���ӵ�����
    int innerEmptyCount;//�ڲ���λ��
    int sideEmptyCount;//���������λ��
};

ShapeInfo countShape(int x, int y, int offsetX, int offsetY, int role) {
    int opponent = 3 - role;

    int innerEmptyCount = 0;
    int tempEmptyCount = 0;
    int selfCount = 0;
    int totalLength = 0;
    int sideEmptyCount = 0;
    int noEmptySelfCount = 0, OneEmptySelfCount = 0;

    for (int i = 1; i <= 5; i++) {
        int nx = x + i * offsetX;
        int ny = y + i * offsetY;

        if (!isValid(nx, ny) || board[nx][ny] == opponent) break;
        int currentRole = board[nx][ny];
        if (currentRole == role) {
            selfCount++;
            sideEmptyCount = 0;
            if (tempEmptyCount) {
                innerEmptyCount += tempEmptyCount;
                tempEmptyCount = 0;
            }
            if (innerEmptyCount == 0) {
                noEmptySelfCount++;
                OneEmptySelfCount++;
            }
            else if (innerEmptyCount == 1) {
                OneEmptySelfCount++;
            }
        }
        totalLength++;
        if (currentRole == 0) {
            tempEmptyCount++;
            sideEmptyCount++;
        }
        if (sideEmptyCount >= 2) {
            break;
        }
    }
    if (!innerEmptyCount) OneEmptySelfCount = 0;
    //printf("�������ӵ�����Ϊ��");
    //printf("%d %d %d %d %d %d\n", selfCount, totalLength, noEmptySelfCount, OneEmptySelfCount, innerEmptyCount, sideEmptyCount);
    return { selfCount, totalLength, noEmptySelfCount, OneEmptySelfCount, innerEmptyCount, sideEmptyCount };
}

std::tuple<Shape, int> getShapeFast(int x, int y, int offsetX, int offsetY, int role) {
    if (isValid(x + offsetX, y + offsetY) && board[x + offsetX][y + offsetY] == 0
        && isValid(x - offsetX, y - offsetY) && board[x - offsetX][y - offsetY] == 0
        && isValid(x + 2 * offsetX, y + 2 * offsetY) && board[x + 2 * offsetX][y + 2 * offsetY] == 0
        && isValid(x - 2 * offsetX, y - 2 * offsetY) && board[x - 2 * offsetX][y - 2 * offsetY] == 0
        ) {
        return { Shape::NONE, 1 };
    }

    auto left = countShape(x, y, -offsetX, -offsetY, role);
    auto right = countShape(x, y, offsetX, offsetY, role);

    int selfCount = left.selfCount + right.selfCount + 1;
    int totalLength = left.totalLength + right.totalLength + 1;
    int noEmptySelfCount = left.noEmptySelfCount + right.noEmptySelfCount + 1;
    int OneEmptySelfCount = std::max(left.OneEmptySelfCount + right.noEmptySelfCount, left.noEmptySelfCount + right.OneEmptySelfCount) + 1;
    int rightEmpty = right.sideEmptyCount;
    int leftEmpty = left.sideEmptyCount;


    if (totalLength < 5) return { Shape::NONE, selfCount };
    if (noEmptySelfCount >= 5) {
        if (rightEmpty > 0 && leftEmpty > 0) {
            return { Shape::FIVE, selfCount };
        }
        else {
            return { Shape::BLOCK_FIVE, selfCount };
        }
    }
    if (noEmptySelfCount == 4) {
        if ((rightEmpty >= 1 || right.OneEmptySelfCount > right.noEmptySelfCount) && (leftEmpty >= 1 || left.OneEmptySelfCount > left.noEmptySelfCount)) {
            return { Shape::FOUR, selfCount };
        }
        else if (!(rightEmpty == 0 && leftEmpty == 0)) {
            return { Shape::BLOCK_FOUR, selfCount };
        }
    }
    if (OneEmptySelfCount == 4) {
        return { Shape::BLOCK_FOUR, selfCount };
    }
    if (noEmptySelfCount == 3) {
        if ((rightEmpty >= 2 && leftEmpty >= 1) || (rightEmpty >= 1 && leftEmpty >= 2)) {
            return { Shape::THREE, selfCount };
        }
        else {
            return { Shape::BLOCK_THREE, selfCount };
        }
    }
    if (OneEmptySelfCount == 3) {//������
        if ((rightEmpty >= 1 && leftEmpty >= 1)) {
            return { Shape::THREE, selfCount };
        }
        else {
            return { Shape::BLOCK_THREE, selfCount };
        }
    }
    if ((noEmptySelfCount == 2 || OneEmptySelfCount == 2) && totalLength > 5) {
        return { Shape::TWO, selfCount };
    }
    return { Shape::NONE, selfCount };
}

//���µ�ǰ��ĸ�������ĵ÷�

int updateSinglePoint(int x, int y, int role, int direction) {
    if (board[x][y] != 0 || !isValid(x, y)) return 0;  // ���ǿ�λ

    // ��ʱ��������
    board[x][y] = role;

    vector<pair<int, int>> directions;

    if (direction != -1) {
        directions.push_back(allDirections[direction]);
    }
    else {
        directions.insert(directions.end(), allDirections.begin(), allDirections.end());
    }

    auto& temp_shapeCache = shapeCache[role];

    // �����������  ��ǰ���ӵ��ĸ��������״ȫ�����
    for (auto& dir : directions) {
        temp_shapeCache[direction2index(dir.first, dir.second)][x][y] = NONE;
    }

    int score = 0;
    int blockfourCount = 0;
    int threeCount = 0;
    int twoCount = 0;
    // �������е÷�
    for (int intDirection = 0; intDirection < 4; intDirection++) {
        auto shape = shapeCache[role][intDirection][x][y];
        if (shape > NONE) {
            score += getRealShapeScore(shape);
            if (shape == BLOCK_FOUR) blockfourCount++;
            if (shape == THREE) threeCount++;
            if (shape == TWO) twoCount++;
        }
    }
    for (auto& dir : directions) {
        int intDirection = direction2index(dir.first, dir.second);

        std::tuple<Shape, int> result = getShapeFast(x, y, dir.first, dir.second, role);
        Shape shape = std::get<0>(result);


        int selfCount = std::get<1>(result);
        if (!shape) continue;
        if (shape) {
            temp_shapeCache[intDirection][x][y] = shape;
            if (shape == BLOCK_FOUR) blockfourCount++;
            if (shape == Shape::THREE) threeCount++;
            if (shape == Shape::TWO) twoCount++;
            if (blockfourCount >= 2) {
                shape = Shape::FOUR_FOUR;
            }
            else if (blockfourCount && threeCount) {
                shape = Shape::FOUR_THREE;
            }
            else if (threeCount >= 2) {
                shape = Shape::THREE_THREE;
            }
            else if (twoCount >= 2) {
                shape = Shape::TWO_TWO;
            }
            score += getRealShapeScore(shape);
        }
    }

    board[x][y] = 0;  // �Ƴ���ʱ����

    if (role == 1) {
        blackScores[x][y] = score;
    }
    else {
        whiteScores[x][y] = score;
    }
    return score;
}

//�������������λ�õĵ÷�
void updatePoint(int x, int y) {
    //auto start = std::chrono::steady_clock::now();
    //printf("update Point*****\n");
    updateSinglePoint(x, y, 1, -1);
    updateSinglePoint(x, y, 2, -1);
    //printf("update Point*****\n");

    for (const auto& direction : allDirections) {
        int ox = direction.first;
        int oy = direction.second;
        for (int sign : {1, -1}) { // -1 for negative direction, 1 for positive direction
            //int emptyCount = 0;
            for (int step = 1; step <= 5; step++) {
                bool reachEdge = false;
                for (int role : {1, 2}) {
                    int nx = x + sign * step * ox;
                    int ny = y + sign * step * oy; // +1 to adjust for wall
                    // ����߽�ֹͣ
                    if (!isValid(nx, ny)) {
                        // Stop if wall or opponent's piece is found
                        reachEdge = true;
                        break;
                    }
                    else if (board[nx][ny] == 3 - role) { // �ﵽ�Է����ӣ���ת����ɫ
                        continue;
                    }
                    else if (board[nx][ny] == 0) {
                        updateSinglePoint(nx, ny, role, direction2index(sign * ox, sign * oy));  // -1 to adjust back from wall
                        // ���ﲻ�����������ܻ��ڻ���ʱ©��һЩ�����µĵ�λ
                        //emptyCount++;
                        //if (emptyCount >= 3) {
                        //    // Stop if more than 2 empty spaces
                        //    break;
                        //}
                    }
                }
                if (reachEdge) break;
            }
        }
    }
    //performance.updateTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
}
//*******************************************************************
int evaluate(int role) {
    int blackScore = 0, whiteScore = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            blackScore += blackScores[i][j];
        }
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            whiteScore += whiteScores[i][j];
        }
    }
    int score = role == 1 ? blackScore - whiteScore : whiteScore - blackScore;
    return score;
}
void putMove(int x, int y, int role) {//��������
    if (!isValid(x, y)) return;

    for (int i = 0; i < 4; i++) {
        shapeCache[role][i][x][y] = 0;
        shapeCache[3 - role][i][x][y] = 0;
    }

    //���º������ĵ÷�
    blackScores[x][y] = 0;
    whiteScores[x][y] = 0;
    board[x][y] = role;
    allStepsCnt++;
    updatePoint(x, y);
}

void undo(int x, int y) {//��������
    if (!isValid(x, y)) return;
    board[x][y] = 0;
    allStepsCnt--;
    updatePoint(x, y);
}

bool hasNeighbor(int x, int y, int dx, int dy) {
    for (int i = -dx; i <= dx; i++) {
        for (int j = -dy; j <= dy; j++) {
            int sx = x + i, sy = y + j;
            if (sx == x && sy == y) continue;
            if (!isValid(sx, sy)) continue;
            if (board[sx][sy]) return true;
        }
    }
    return false;
}

int getWinner() {
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} }; // ˮƽ����ֱ���Խ���
    for (int i = 0; i < boardSIZE; i++) {
        for (int j = 0; j < boardSIZE; j++) {
            if (board[i][j] == 0) continue;
            for (auto direction : directions) {
                int leftcount = 0, rightcount = 0;
                int dx = i, dy = j;
                while (isValid(dx - direction[0], dy - direction[1]) && board[dx - direction[0]][dy - direction[1]] == board[i][j]) {
                    dx -= direction[0];
                    dy -= direction[1];
                    leftcount++;
                }
                dx = i;
                dy = j;
                while (isValid(dx + direction[0], dy + direction[1]) && board[dx + direction[0]][dy + direction[1]] == board[i][j]) {
                    dx += direction[0];
                    dy += direction[1];
                    rightcount++;
                }
                int count = leftcount + rightcount;
                if (count >= 4) return board[i][j]; // �����Ϊ >= 4����Ϊ�������ߵı߽粻Ӧ����
            }
        }
    }
    return 0;
}

bool scoreCmp(int a, int b) {
    int ax = a / boardSIZE;
    int ay = a % boardSIZE;
    int bx = b / boardSIZE;
    int by = b % boardSIZE;
    //int scoreA =role==1? 2 * blackScores[ax][ay] + whiteScores[ax][ay]: blackScores[ax][ay] + 2*whiteScores[ax][ay];
    //int scoreB =role==1? 2 * blackScores[bx][by] + whiteScores[bx][by]: blackScores[bx][by] + 2*whiteScores[bx][by];
    int scoreB = blackScores[bx][by] + whiteScores[bx][by];
    int scoreA = blackScores[ax][ay] + whiteScores[ax][ay];
    return scoreA > scoreB;
}


int bestMoveIndex = 0;
//generate������Ȼ��Ҫ�Ż�
vector<int> generate(int role, bool onlythrees, bool onlyfours) {//onlythrees Ϊ1��ʾֻ���ػ������ϵĵ�
    std::vector<int> fives;
    std::vector<int> comfives;
    std::vector<int> humfives;
    std::vector<int> comfours;
    std::vector<int> humfours;
    std::vector<int> comblockedfours;
    std::vector<int> humblockedfours;
    std::vector<int> comtwothrees;
    std::vector<int> humtwothrees;
    std::vector<int> comthrees;
    std::vector<int> humthrees;
    std::vector<int> comtwos;
    std::vector<int> humtwos;
    std::vector<int> neighbors;//�ھӽڵ�

    for (int i = 0; i < boardSIZE; i++) {
        for (int j = 0; j < boardSIZE; j++) {
            if (board[i][j] != 0) continue;
            int neigbourX = 2, neigbourY = 2;
            if (allStepsCnt < 10)neigbourX = 1, neigbourY = 1;
            if (!hasNeighbor(i, j, neigbourX, neigbourY)) continue;
            //�ҷ��������
            int comFIVE_CNT = 0;//����
            int comBLOCK_FIVE_CNT = 0;

            int comFOUR_CNT = 0;//����
            int comBLOCK_FOUR_CNT = 0;//����
            int comFOUR_THREE = 0;//��������
            int comFOUR_FOUR = 0;//˫����
            int comTHREE_CNT = 0;//����
            int comBLOCK_THREE_CNT = 0;//����
            int comTHREE_THREE_CNT = 0;//˫����
            int comTWO_CNT = 0;//���
            int comTWO_TWO_CNT = 0;//˫���
            //�Է��������
            int humFIVE_CNT = 0;//����
            int humBLOCK_FIVE_CNT = 0;
            int humFOUR_CNT = 0;//����
            int humBLOCK_FOUR_CNT = 0;//����
            int humFOUR_THREE = 0;//��������
            int humFOUR_FOUR = 0;//˫����
            int humTHREE_CNT = 0;//����
            int humBLOCK_THREE_CNT = 0;//����
            int humTHREE_THREE_CNT = 0;//˫����
            int humTWO_CNT = 0;//���
            int humTWO_TWO_CNT = 0;//˫���
            for (int r : {role, 3 - role}) {//shapeCache��  1��ʾ�ҷ��� 2��ʾ�з�
                for (int d = 0; d < 4; d++) {
                    int tmp_shape = shapeCache[r][d][i][j];
                    if (tmp_shape == NONE) continue;
                    if (tmp_shape == FIVE || tmp_shape == BLOCK_FIVE) {
                        if (r == 1) comFIVE_CNT++;
                        else humFIVE_CNT++;
                    }
                    else if (tmp_shape == FOUR) {
                        if (r == 1)comFOUR_CNT++;
                        else humFOUR_CNT++;
                    }
                    else if (tmp_shape == BLOCK_FOUR) {
                        if (r == 1) comBLOCK_FOUR_CNT++;
                        else humBLOCK_FOUR_CNT++;
                    }
                    else if (tmp_shape == THREE) {
                        if (r == 1) comTHREE_CNT++;
                        else humTHREE_CNT++;
                    }
                    else if (tmp_shape == BLOCK_THREE) {
                        if (r == 1) comBLOCK_THREE_CNT++;
                        else humBLOCK_THREE_CNT++;
                    }
                    else if (tmp_shape == TWO) {
                        if (r == 1) comTWO_CNT++;
                        else humTWO_CNT++;
                    }
                }
            }
#ifndef _BOTZONE_ONLINE
            if (i == 8 && j == 7) {
                printf("humfour=%d\n", humFOUR_CNT);
                printf("com_blockfour=%d\n", comBLOCK_FOUR_CNT);
                printf("****\n");

            }
#endif // !_BOTZONE_ONLINE
            //printf("��ʼ�γ�vector\n");
            //if (comFIVE_CNT > 0 || humFIVE_CNT > 0) fives.push_back(coordinate2Position(i, j, boardSIZE));
            if (comFIVE_CNT > 0) comfives.push_back(coordinate2Position(i, j, boardSIZE));
            if (humFIVE_CNT > 0) humfives.push_back(coordinate2Position(i, j, boardSIZE));
            //���ģ�˫���ģ����Ļ���
            if (comFOUR_CNT > 0 || comBLOCK_FOUR_CNT >= 2 || (comBLOCK_FOUR_CNT >= 1 && comTHREE_CNT > 0)) comfours.push_back(coordinate2Position(i, j, boardSIZE));
            if (humFOUR_CNT > 0 || humBLOCK_FOUR_CNT >= 2 || (humBLOCK_FOUR_CNT >= 1 && humTHREE_CNT > 0)) humfours.push_back(coordinate2Position(i, j, boardSIZE));
            //���� ˫��
            if (comBLOCK_FOUR_CNT > 0)comblockedfours.push_back(coordinate2Position(i, j, boardSIZE));
            if (humBLOCK_FOUR_CNT > 0)humblockedfours.push_back(coordinate2Position(i, j, boardSIZE));

            //˫����
            if (comTHREE_CNT >= 2) comtwothrees.push_back(coordinate2Position(i, j, boardSIZE));
            if (humTHREE_CNT >= 2) humtwothrees.push_back(coordinate2Position(i, j, boardSIZE));
            //����
            if (comTHREE_CNT > 0)comthrees.push_back(coordinate2Position(i, j, boardSIZE));
            if (humTHREE_CNT > 0)humthrees.push_back(coordinate2Position(i, j, boardSIZE));

            // ���
            if (comTWO_CNT > 0) comtwos.push_back(coordinate2Position(i, j, boardSIZE));
            if (humTWO_CNT > 0)humtwos.push_back(coordinate2Position(i, j, boardSIZE));
            else neighbors.push_back(coordinate2Position(i, j, boardSIZE));
        }
    }
#ifndef _BOTZONE_ONLINE
    //printf("");

#endif // !_BOTZONE_ONLINE
    //������壬ֱ�ӷ��س���
    if (role == 1 && comfives.size()) return comfives;
    else if (role == 1 && !comfives.size() && humfives.size()) return humfives;
    if (role == 2 && humfives.size()) return humfives;
    else if (role == 2 && !humfives.size() && comfives.size()) return comfives;
    //printf("five over\n");
    //����Լ����Ի��ģ�ֱ�ӷ��ػ���
    if (role == 1 && comfours.size()) {
        //std::sort(comfours.begin(), comfours.end(), scoreCmp);
        return comfours;
    }
    if (role == 2 && humfours.size()) {
        //std::sort(humfours.begin(), humfours.end(), scoreCmp);
        return humfours;
    }
    ////����ҷ���˫���������ȿ����ҷ�˫����
    //if (role == 1 && comtwothrees.size()) return comtwothrees;
    //if (role == 2 && humtwothrees.size()) return humtwothrees;


    //����ҷ��г��ģ����ȿ��ǳ��ģ�ʹ�ø��߹�����
    //��һ���൱���Ƿϵģ���Ϊ�����ˣ��Է���Ȼ����㣬����ûʲô���壬����ͻ���һ���
    /*if (role == 1 && comblockedfours.size()) return comblockedfours;
    if (role == 2 && humblockedfours.size()) return humblockedfours;*/

    //�����л��ģ��Լ����Ķ�û�У����ȿ��Ƕ���Ļ���
    if (role == 1 && humfours.size()) return humfours;
    if (role == 2 && comfours.size()) return comfours;
    //����ҷ���˫���������ȿ����ҷ�˫����
    if (role == 1 && comtwothrees.size()) return comtwothrees;
    if (role == 2 && humtwothrees.size()) return humtwothrees;
    //����ҷ�û��˫���������ȿ��ǶԷ�˫����
    if (role == 1 && !comtwothrees.size() && humtwothrees.size()) return humtwothrees;
    if (role == 2 && !humtwothrees.size() && comtwothrees.size()) return comtwothrees;

    if (onlyfours) {
        if (role == 1) {
            return comfours;
        }
        else return humfours;
    }

    //����ҷ��л��������ȿ����ҷ�����
    if (role == 1 && comthrees.size()) {
        comthrees.insert(comthrees.end(), comblockedfours.begin(), comblockedfours.end());
        //sort(comthrees.begin(), comthrees.end(), scoreCmp);
        return comthrees;
    }
    if (role == 2 && humthrees.size()) {
        humthrees.insert(humthrees.end(), humblockedfours.begin(), humblockedfours.end());
        //sort(humthrees.begin(), humthrees.end(), scoreCmp);
        return humthrees;
    }
    if (onlythrees) {
        if (role == 1) {
            comtwothrees.insert(comtwothrees.end(), comthrees.begin(), comthrees.end());
            //sort(comtwothrees.begin(), comtwothrees.end(), scoreCmp);
            return comtwothrees;
        }
        else {
            humtwothrees.insert(humtwothrees.end(), humthrees.begin(), humthrees.end());
            //humtwothrees.insert(humtwothrees.end(), humblockedfours.begin(), humblockedfours.end());
            sort(humtwothrees.begin(), humtwothrees.end(), scoreCmp);
            return humtwothrees;
        }
    }




    vector<int> res;
    if (role == 1) {
        res.insert(res.end(), comtwothrees.begin(), comtwothrees.end());
        res.insert(res.end(), humtwothrees.begin(), humtwothrees.end());
        res.insert(res.end(), comblockedfours.begin(), comblockedfours.end());
        res.insert(res.end(), humblockedfours.begin(), humblockedfours.end());
        res.insert(res.end(), comthrees.begin(), comthrees.end());
        res.insert(res.end(), humthrees.begin(), humthrees.end());
    }
    else {
        res.insert(res.end(), humtwothrees.begin(), humtwothrees.end());
        res.insert(res.end(), comtwothrees.begin(), comtwothrees.end());
        res.insert(res.end(), humblockedfours.begin(), humblockedfours.end());
        res.insert(res.end(), comblockedfours.begin(), comblockedfours.end());
        res.insert(res.end(), humthrees.begin(), humthrees.end());
        res.insert(res.end(), comthrees.begin(), comthrees.end());
    }
    sort(res.begin(), res.end(), scoreCmp);

    //if (comtwothrees.size() || humtwothrees.size()) return res;
    //if (onlythrees) return res;
    vector<int> twos;
    if (role == 1) {
        twos.insert(twos.end(), comtwos.begin(), comtwos.end());
        //twos.insert(twos.end(), humtwos.begin(), humtwos.end());
    }
    else {
        twos.insert(twos.end(), humtwos.begin(), humtwos.end());
        //twos.insert(twos.end(), comtwos.begin(), comtwos.end());
    }
    std::sort(twos.begin(), twos.end(), scoreCmp);

    if (twos.size()) {
        res.insert(res.end(), twos.begin(), twos.end());
    }
    else {
        res.insert(res.end(), neighbors.begin(), neighbors.end());
    }
    sort(res.begin(), res.end(), scoreCmp);
    if (res.size() > countLimit) res.resize(countLimit);
    return res;
}

pair<int, int> MinMax_with_abPuring(int alpha, int beta, int player, int cur_depth) {
    //alpha��ʼ��Ϊ������³�ʼ��Ϊ������
#ifndef _BOTZONE_ONLINE
    printf("���ڵִ�������current depth=%d\n", cur_depth);
#endif // !_BOTZONE_ONLINE

    if (getWinner() == 1) return { pos_inf + 1,cur_depth };
    else if (getWinner() == 2) return { neg_inf - 1,cur_depth };

    if (cur_depth == depth) {
        return { evaluate(1),cur_depth };
    }
    int bestMoveIndex = -1;

    //����������ʲô���ֻҪ������ʲô���ֻҪ���� �����ܵĵݹ�������


    bool onlythrees = cur_depth >= 5 ? true : false;
    bool onlyfours = cur_depth >= 9 ? true : false;

    //**********


    vector<int> child = generate(player, onlythrees, onlyfours);


    //��û�п��ߵĽڵ�ʱ�ͷ��أ���ǰ���������
    if (!child.size()) return { evaluate(1),cur_depth };

#ifndef _BOTZONE_ONLINE
    printf("��ǰ������%d�����еĲ���\n", child.size());
    for (auto it : child) {
        printf("(%d %d)", it / 15, it % 15);
    }
    printf("\n");
#endif // !_BOTZONE_ONLINE

    int bestVal;
    int bestDepth = 12;
    //����С����+ab��֦
    if (player == 1) {//�ҷ�
        bestVal = neg_inf;
        int num = 0;
        for (int num = 0; num < child.size(); num++) {
            int x = child[num] / boardSIZE, y = child[num] % boardSIZE;
#ifndef _BOTZONE_ONLINE

            printf("��ǰ׼��Ҫ�µ����ӣ�x=%d y=%d\n", x, y);

#endif // !_BOTZONE_ONLINE

            putMove(x, y, player);
            //printf("��������ѭ��\n");
            auto it = MinMax_with_abPuring(alpha, beta, 3 - player, cur_depth + 1);
            undo(x, y);
            int val = it.first;
            //bestVal = max(bestVal, val);
            if (val > bestVal) {
                new_x = x, new_y = y;
                bestVal = val;
                bestMoveIndex = num;
                bestDepth = it.second;
            }
            else if (val == bestVal && bestDepth > it.second) {
                bestMoveIndex = num;
                bestDepth = it.second;
            }
            alpha = max(alpha, bestVal);
            if (alpha >= beta) {
                cutting_cnt++;
                break;
            }
        }
    }
    else {//�з�
        bestVal = pos_inf;

        for (int num = 0; num < child.size(); num++) {
            int x = child[num] / boardSIZE, y = child[num] % boardSIZE;

            putMove(x, y, player);
            auto it = MinMax_with_abPuring(alpha, beta, 3 - player, cur_depth + 1);
            undo(x, y);
            int val = it.first;
            if (val < bestVal) {
                new_x = x, new_y = y;
                bestVal = val;
                bestMoveIndex = num;
                bestDepth = it.second;
            }
            else if (val == bestVal && bestDepth > it.second) {
                bestMoveIndex = num;
                bestDepth = it.second;
            }
            beta = min(beta, bestVal);
            if (alpha >= beta) {
                cutting_cnt++;
                break;
            }
        }
    }
    //��֤�˸��ڵ���ӽڵ���˳�����ظ��ڵ�
    if (cur_depth == 0 && bestMoveIndex != -1) {
        new_x = child[bestMoveIndex] / boardSIZE;
        new_y = child[bestMoveIndex] % boardSIZE;
    }
    else if (cur_depth == 0 && bestMoveIndex == -1 && child.size() == 1) {
        new_x = child[0] / boardSIZE;
        new_y = child[0] % boardSIZE;
    }
    return { bestVal,bestDepth };
}

// �����ĺŽӿ�
void Bot4(int gridlnfo[15][15], int Rounds, int chessColor, int& X, int& Y) {
#ifndef _BOTZONE_ONLINE
    freopen("input1.txt", "r", stdin);

#endif // !_BOTZONE_ONLINE
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chessColor == 1) {
                board[j][i] = (gridlnfo[i][j] == -1) ? 2 : gridlnfo[i][j];
            }
            else {
                if (gridlnfo[i][j] == 1)
                    board[j][i] = 2;
                else if (gridlnfo[i][j] == -1)
                    board[j][i] = 1;
                else
                    board[j][i] = 0;
            }
        }
    }
    allStepsCnt = Rounds - 1;
#ifndef _BOTZONE_ONLINE
    printf("%d\n", allStepsCnt);
    printBoard();
#endif // !_BOTZONE_ONLINE

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            updatePoint(i, j);
        }
    }
#ifndef _BOTZONE_ONLINE

#endif // !_BOTZONE_ONLINE
    //�Ż����ԣ����Ƿ�����������Сʱ ̰�Ĳ����������ھ����� ����������С��10��ʱ�����ý�ǳ�ĵݹ��������������������
    if (allStepsCnt <= 6) depth = 1;
    else if (allStepsCnt <= 15) depth = 4;
    else if (allStepsCnt <= 25) depth = 7;
    else depth = 10;
    // �����������ܵĵݹ���ȣ��������� ���Գ��Ե������ 8��9��10��11��12
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
        MinMax_with_abPuring(neg_inf, pos_inf, 1, 0);
    }
#ifndef _BOTZONE_ONLINE
    printf("black score 7 10=%d\n", blackScores[7][10]);
    printf("white score 7 10=%d\n", whiteScores[7][10]);
    printf("black score 10 7=%d\n", blackScores[10][7]);
    printf("white score 10 7=%d\n", whiteScores[10][7]);
    for (int i = 0; i < 4; i++) {
        printf("my=%d\n", shapeCache[1][i][8][7]);
        printf("op=%d\n", shapeCache[2][i][8][7]);
    }


#endif // !_BOTZONE_ONLINE

#ifndef _BOTZONE_ONLINE
    std::chrono::milliseconds current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time);
    std::cout << "�Ѿ���ȥ��ʱ��: " << current_time.count() << " ����" << std::endl;

#endif // !_BOTZONE_ONLINE 
    // ��ƽ̨������߽��
#ifndef _BOTZONE_ONLINE
    board[new_x][new_y] = 1;
    printBoard();
    printf("��֦����Ϊ��%d\n", cutting_cnt);
    printf("\n");
#endif // !_BOTZONE_ONLINE
    X = new_x; Y = new_y;
    return;
}