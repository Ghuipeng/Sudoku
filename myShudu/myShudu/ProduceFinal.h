//生成固定数目的
//由第一行全排列
//之后的按行号的不超出各自范围的排列
//的转换生成的终局
void ProucedByPermutationTrans(int produce_num);
//使用第一行按照shift数组移动生成整个数独
int** ProuceOneByFirstRow(int* firstrow);
//初始化一个由n开始的长为length的数组
int* init(int n);
//将一个数独按照行号的排列生成终局
int** TransRow(int**, int*);
//
//
//
//

//由n个随机数初始化生成终盘
//n建议不超过18
void ProucedByRandom(int produce_num, int random_num);

