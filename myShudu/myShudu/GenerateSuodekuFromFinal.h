//从几个终局中获取数独
//num表示获取的数独的数量
//oneSolution表示是否获取只有一个解的数独
//diffcult 表示难度，难度来自两个方面，一是挖空的数目，一个是每个空白的自由度
//low与high是限定的挖空的数量。全部设置0表示由我们人为限定
const int low_limit = 20;
const int high_limit = 55;
const int low_freedom = 400;
const int high_freedom = 1100;
void Generate(int num, bool oneSolution = false, int diffcult = 0, int low = 20, int high = 55);

//从难度和挖空限制获得挖空的位置
//返回值是place的长度
//place输入一个指针
//用随机生成得到一个place数组，再判断是否符合难度
//place是一个一维数组，形如0，2，3表示在0，2，3位置挖空，计算得到在二维数组中的位置
int GetBlankPlace(int* place, int diffcult = 0, int low = 20, int high = 55);

//获得plcae的难度
int GetDiffcult(int* place, int length);

//获得因挖空数得到的难度
float GetNumDiff(int length);

//输入二维，因为这样更方便
//获得因自由度得到的难度
float GetFreeDiff(int** place);
int GetFree(int** place, int x, int y);