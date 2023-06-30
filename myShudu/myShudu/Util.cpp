#include "Util.h"
#include <list>
int** RequestMemory(int** sudoku) {
	int** new_sudoku = (int**)malloc(sizeof(int*) * length);
	if (new_sudoku == NULL)
		return NULL;
	for (int i = 0; i < length; i++)
	{
		new_sudoku[i] = (int*)malloc(sizeof(int) * (length));
		if (new_sudoku[i] == NULL)
			return NULL;
		memcpy(new_sudoku[i], sudoku[i], sizeof(int) * (length));

	}
	return new_sudoku;
}
int** RequestMemory(int num) {
	int** new_sudoku = (int**)malloc(sizeof(int*) * length);
	if (new_sudoku == NULL)
		return NULL;
	for (int i = 0; i < length; i++)
	{
		new_sudoku[i] = (int*)malloc(sizeof(int) * (length));
		if (new_sudoku[i] == NULL)
			return NULL;
		memset(new_sudoku[i], num, sizeof(int) * (length));

	}
	return new_sudoku;
}

//使用引用能把指针指向NULL
//可以防止多次释放的错误
//在该函数还也可以任意指定释放掉的指针为NULL，不受影响
void DeleteMemory(int** &sudo) {
	for (int i = 0; i < length; i++)
	{
		if (sudo[i] != NULL)
			free(sudo[i]);
		sudo[i] = NULL;
	}
	if (sudo != NULL)
		free(sudo);
	sudo = NULL;
}
//使用引用保证指针最后可以指向NULL，防止多次释放
void DeleteMemory(list<int**> &sudo_list) {
	list<int**>::iterator it_1 = sudo_list.begin();

	while (it_1 != sudo_list.end()) {
		int** element = *it_1;
		DeleteMemory(element);
		*it_1 = NULL;
		it_1++;
	}
}
