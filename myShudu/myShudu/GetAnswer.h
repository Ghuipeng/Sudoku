#include <list>
using namespace std;
void GetAnswer(int** sudoku, int& size, list<int**>* all_sudo, int begin = 0);
//������Դ�GetNextBlank�Ż�
//�ڻ�ȡ���е�����£��ǲ���������ģ������������Լ��size�������
//�ڻ�ȡ�ض���Ŀ�������£����ѡȡ���Ǹ���õ��п��н��λ�����������ٶȻ��죬
//�������Ҫ���н⣬��ô���е���������������������
int GetNextBlank(int** sudoku, int begin);
//IsCorrect���Ի���ٶ��ϵ��Ż�
//׼ȷ����˵���滻��һ���Ի�����б����հ׵Ŀ��н⣬ֻ��Ҫ�����ı飬�ȱ����ű��
bool IsCorrect(int** sudoku, int num, int x, int y);
int** RequestMemory(int** sudoku);
//��һ��ֵ������һ����ά����
int** RequestMemory(int num);
bool CheckRow(int** sudoku, int num, int x);
bool CheckCol(int** sudoku, int num, int y);
bool CheckBlock(int** sudoku, int num, int x, int y);
