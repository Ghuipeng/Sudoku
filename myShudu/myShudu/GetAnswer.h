#include <list>
using namespace std;
void GetAnswer(int** sudoku, int& size, list<int**>* all_sudo, int begin = 0);
//或许可以从GetNextBlank优化
//在获取所有的情况下，是不会有区别的，有区别的是在约定size的情况下
//在获取特定数目解的情况下，如果选取的是更快得到有可行解的位置你们整体速度会变快，
//但是如果要所有解，那么所有的情况都会遍历不会有区别
int GetNextBlank(int** sudoku, int begin);
//IsCorrect可以获得速度上的优化
//准确的来说是替换，一次性获得所有本处空白的可行解，只需要遍历四遍，比遍历九遍快
bool IsCorrect(int** sudoku, int num, int x, int y);
int** RequestMemory(int** sudoku);
//将一个值拷贝给一个二维数组
int** RequestMemory(int num);
bool CheckRow(int** sudoku, int num, int x);
bool CheckCol(int** sudoku, int num, int y);
bool CheckBlock(int** sudoku, int num, int x, int y);
