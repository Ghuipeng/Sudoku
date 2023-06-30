#include "GenerateSuodekuFromFinal.h"
#include "Util.h"
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "Read_Write_File.h"
#include "GetAnswer.h"
#include <iostream>
using namespace std;

void setNull(int** sudo, int* place, int place_length) {    //用于挖空终局，得到数独
	for (int postion = 0; postion < place_length; postion++) {
		sudo[place[postion] / length][place[postion] % length] = 0;
	}
}

void Generate(int num, bool oneSolution, int diffcult, int low, int high) {
	int num_now = 0;
	int size = 2;   //至多求2个解
	int size_per_sudo = 1;
	list<int**> valid_sudo_list;
	extern char* Final_path;
	ifstream read;
	read.open(Final_path);
	int** onesudo = RequestMemory(0);
	int** copy_sudo = RequestMemory(0);
	while (num > num_now) {
		if (read_from_text(onesudo, read))   //每次读取一个终局到onesudo
		{
			for (int i = 0; i < size_per_sudo; i++)    //每个终局可以获得几次生成数独题目的机会
			{
				int place[high_limit] = { 0 };
				copy_sudo = RequestMemory(onesudo);   //因为一个终局onesudo有多次机会，需要保留，我们使用copy_sudo
				int place_length = GetBlankPlace(place, diffcult, low, high);
				int real_diffcult = GetDiffcult(place, place_length);   //应该等于diffcult
				setNull(copy_sudo, place, place_length);    //生成得到数独copy_sudo
				if (oneSolution)
				{
					list<int**> sudo_list;
					GetAnswer(copy_sudo, size, &sudo_list);
					if (sudo_list.size() == 0) {  //数独无解
						cout << "生成的数独无解" << endl;
						break;
					}
					if (sudo_list.size() != 1) {  //多解(2)
						cout << "生成的数独多解" << endl;
						break;
					}
					num_now++;
					valid_sudo_list.push_back(copy_sudo);
					DeleteMemory(sudo_list);
				}
				else {
					num_now++;
					valid_sudo_list.push_back(copy_sudo);
				}
				if (num_now >= num)
					break;
			}
		}
	}
	cout<<valid_sudo_list.size()<<endl;
	output_game(valid_sudo_list);
	DeleteMemory(valid_sudo_list);
	DeleteMemory(onesudo);
	DeleteMemory(copy_sudo);
}

void ShuffleArray(int* array, int size) {
	srand(time(NULL)); // 初始化随机数种子

	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		std::swap(array[i], array[j]);
	}
}

// 在0-80之间随机取n个数，放入place
void GetRandomNumbers(int* place, int n) {
	int numbers[81];
	for (int i = 0; i < 81; i++) {
		numbers[i] = i;
	}

	ShuffleArray(numbers, 81);

	for (int i = 0; i < n; i++) {
		place[i] = numbers[i];
	}
}

int getRandomNumber(int low, int high) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(low, high);
	return distribution(gen);
}

int GetBlankPlace(int* place, int diffcult, int low, int high) {
	//从难度和挖空限制获得挖空的位置
	//返回值是place的长度
	//place输入一个指针
	//用随机生成得到一个place数组，再判断是否符合难度
	//place是一个一维数组，形如0，2，3表示在0，2，3位置挖空，计算得到在二维数组中的位置
	int randomNumber;
	if (diffcult == 0){
		randomNumber = getRandomNumber(low, high);
		cout << "randomNumber: " << randomNumber << endl;
		GetRandomNumbers(place, randomNumber);
	}
	else{
		do
		{
			randomNumber = getRandomNumber(low, high);
			cout << "randomNumber: " << randomNumber << endl;
			GetRandomNumbers(place, randomNumber);
		} while (GetDiffcult(place, randomNumber) != diffcult);
	}

	return randomNumber;
}


int GetDiffcult(int* place, int place_length) {
	float numdiff = GetNumDiff(place_length);
	int** two_dim_place = RequestMemory(1);
	setNull(two_dim_place, place, place_length);
	float freediff = GetFreeDiff(two_dim_place);
	float rate = 0.8;
	DeleteMemory(two_dim_place);
	return ceil(3 * (rate * numdiff + (1 - rate) * freediff));
}

//获得因挖空数得到的难度
float GetNumDiff(int length) {
	if (length <= low_limit)
		length = low_limit + 1;
	if (length > high_limit)
		length = high_limit;
	return float(length - low_limit) / float(high_limit - low_limit);
}


//输入二维，因为这样更方便
//获得因自由度得到的难度
//可优化，从块的维度,每个块获得块中的空白数与相交的行列的空白数
int GetFree(int** place, int x, int y) {
	if (place[x][y])
		return 0;
	int freedom = 0;
	for (int i = 0; i < length; i++) {
		if (place[i][y]) continue;
		freedom += 1;
	}
	for (int j = 0; j < length; j++) {
		if (place[x][j]) continue;
		freedom += 1;
	}
	freedom -= 2;
	int block_num = (x / block_size) * block_size + y / block_size;
	int x_start = (block_num / block_size) * block_size;
	int y_start = (block_num % block_size) * block_size;
	for (int i = x_start; i < x_start + block_size; i++) {
		for (int j = y_start; j < y_start + block_size; j++) {
			if (place[i][j]) continue;
			if (i == x || j == y) continue;
			freedom += 1;
		}
	}
	return freedom;
}
float  GetFreeDiff(int** place) {
	int freedom = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			freedom += GetFree(place, i, j);
		}
	}
	if (freedom <= low_freedom)
		freedom = low_freedom + 1;
	if (freedom > high_freedom)
		freedom = high_freedom;
	return float(freedom - low_freedom) / float(high_freedom - low_freedom);
}


