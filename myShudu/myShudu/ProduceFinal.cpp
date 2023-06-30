#include "ProduceFinal.h"
#include "Util.h"
#include "Read_Write_File.h"
#include "GetAnswer.h"
#include <ctime>
#include <random>
#include <math.h>
#include <algorithm>

using namespace std;

int* init(int n) {
	int* firsrrow = new int[length];
	for (int i = 0; i < length; i++) {
		firsrrow[i] = i + n;
	}
	return firsrrow;
}
int** ProuceOneByFirstRow(int* firstrow) {
	int** onesudo = RequestMemory(0);
	int shift[9] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };
	//memcpy(onesudo[0], firstrow, sizeof(int) * (length));
	for (int i = 0; i < length; i++) {
		memcpy(onesudo[i], firstrow + shift[i], sizeof(int) * (length - shift[i]));
		memcpy(onesudo[i] + length - shift[i], firstrow, sizeof(int) * (shift[i]));
	}
	return onesudo;
}
int** TransRow(int** sudo, int* row) {
	int** onesudo = RequestMemory(0);
	for (int i = 0; i < length; i++) {
		memcpy(onesudo[i], sudo[row[i]], sizeof(int) * (length));
	}
	return onesudo;
}
void ProucedByPermutationTrans(int produce_num) {
	int num = 0;
	int* firsrrow = init(1);
	int* rowtrans = init(0);
	do {
		int** onesudo = ProuceOneByFirstRow(firsrrow);
		do
		{
			do
			{
				do
				{
					if (num >= produce_num)
						return;
					int** transsudo = TransRow(onesudo, rowtrans);
					output(transsudo);
					DeleteMemory(transsudo);
					transsudo = NULL;
					num++;
				} while (next_permutation(rowtrans + 6, rowtrans + 9));
			} while (next_permutation(rowtrans + 3, rowtrans + 6));
		} while (next_permutation(rowtrans + 1, rowtrans + 3));
		DeleteMemory(onesudo);
		onesudo = NULL;
	} while (next_permutation(firsrrow, firsrrow + length));
	free(firsrrow); free(rowtrans);
}


void ProucedByRandom(int produce_num, int random_num) {
	int num_now_produce = 0;
	int num_now_random = 0;
	int size = ceil(sqrt(produce_num));
	while (num_now_produce < produce_num)
	{
		int** onesudo = RequestMemory(0);
		num_now_random = 0;
		while (num_now_random < random_num) {
			//真随机获得的话会花费很长时间找到一个能够满足Correct的情况
			srand((unsigned)time(NULL));
			int x = rand() % length;
			int y = rand() % length;
			int num = (rand() % length) + 1;
			//cout << x << endl;
			//cout << y << endl;
			//cout << num << endl;
			if (IsCorrect(onesudo, num, x, y)) {
				onesudo[x][y] = num;
				num_now_random++;
			}
		}
		list<int**> sudo_list;
		GetAnswer(onesudo, size, &sudo_list);
		num_now_produce += sudo_list.size();
		output(sudo_list);
		DeleteMemory(onesudo);
		onesudo = NULL;
	}
}