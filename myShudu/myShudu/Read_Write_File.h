#include <list>
#include<fstream>
using namespace std;
extern char* Final_path;
//����վ֣�����������ļ�
void output(int**);
//����վ��б�����������ļ�
void output(list<int**>);
//�������Ļ
void output_to_screen(int**);
//��һ����ά����д���ļ���
void output_to_text(int** sudo, ofstream& write);

bool read_from_text(int** sudo, ifstream& read);

//ע����ʹ��ǰ����RequestMemory���һ��sudo���ں�����ֻ�ܶ������и�ֵ
bool read_final(int** sudo, ifstream& read);


void output_game(int**);
void output_game(list<int**>);
void output_result(int**);
void output_result(list<int**>);