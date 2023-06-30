#include <list>
const int length = 9;
const int block_size = 3;
using namespace std;
#include <iostream>
int** RequestMemory(int** sudoku);
//将一个值拷贝给一个二维数组
int** RequestMemory(int num);
void DeleteMemory(int** &);
void DeleteMemory(list<int**>& );