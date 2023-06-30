#include <list>
#include<fstream>
using namespace std;
extern char* Final_path;
//输出终局，包括输出到文件
void output(int**);
//输出终局列表，包括输出到文件
void output(list<int**>);
//输出到屏幕
void output_to_screen(int**);
//把一个二维数组写到文件终
void output_to_text(int** sudo, ofstream& write);

bool read_from_text(int** sudo, ifstream& read);

//注意在使用前先用RequestMemory获得一个sudo，在函数中只能对它进行赋值
bool read_final(int** sudo, ifstream& read);


void output_game(int**);
void output_game(list<int**>);
void output_result(int**);
void output_result(list<int**>);