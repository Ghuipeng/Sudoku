#include "GetAnswer.h"
#include "Util.h"
int GetNextBlank(int** sudoku, int begin) {
	for (int i = begin; i < length * length; i++) {
		if (sudoku[i / length][i % length] == 0)
			return i;
	}
	return -1;
}
bool CheckRow(int** sudoku, int num, int x) {
	//return true;

	for (int i = 0; i < length; i++) {
		if (sudoku[x][i] == num)
			return false;
	}
	return true;
}
bool CheckCol(int** sudoku, int num, int y) {
	//return true;
	for (int i = 0; i < length; i++) {
		if (sudoku[i][y] == num)
			return false;
	}
	return true;
}
bool CheckBlock(int** sudoku, int num, int x, int y) {
	//return true;
	int block_num = (x / block_size) * block_size + y / block_size;
	int x_start = (block_num / block_size) * block_size;
	int y_start = (block_num % block_size) * block_size;
	for (int i = x_start; i < x_start + block_size; i++) {
		for (int j = y_start; j < y_start + block_size; j++) {
			if (sudoku[i][j] == num)
				return false;
		}
	}
	return true;

}

bool IsCorrect(int** sudoku, int num, int x, int y) {

	if (CheckRow(sudoku, num, x) && CheckCol(sudoku, num, y) && CheckBlock(sudoku, num, x, y))
		return true;
	return false;
}

void GetAnswer(int** sudoku, int& size, list<int**>* all_sudo, int begin) {
	int blank = GetNextBlank(sudoku, begin);
	if (blank == -1) {	//全都不为0
		if (size != 0 && size <= all_sudo->size()) {
			cout << "已经得到足够的数独答案，停止获取";
			return;
		}
		int** new_sudoku = RequestMemory(sudoku);
		if (new_sudoku == NULL) {
			cout << "内存已经不足，停止获取";
			size = all_sudo->size();
			return;
		}
		all_sudo->push_back(new_sudoku);
		return;
	}
	for (int i = 1; i <= 9; i++) {
		if (IsCorrect(sudoku, i, blank / 9, blank % 9)) {
			sudoku[blank / length][blank % length] = i;
			GetAnswer(sudoku, size, all_sudo, blank + 1);
			if (size <= all_sudo->size()) break;
		}
	}
	sudoku[blank / length][blank % length] = 0;
	return;
}