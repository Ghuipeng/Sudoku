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

void setNull(int** sudo, int* place, int place_length) {    //�����ڿ��վ֣��õ�����
	for (int postion = 0; postion < place_length; postion++) {
		sudo[place[postion] / length][place[postion] % length] = 0;
	}
}

void Generate(int num, bool oneSolution, int diffcult, int low, int high) {
	int num_now = 0;
	int size = 2;   //������2����
	int size_per_sudo = 1;
	list<int**> valid_sudo_list;
	extern char* Final_path;
	ifstream read;
	read.open(Final_path);
	int** onesudo = RequestMemory(0);
	int** copy_sudo = RequestMemory(0);
	while (num > num_now) {
		if (read_from_text(onesudo, read))   //ÿ�ζ�ȡһ���վֵ�onesudo
		{
			for (int i = 0; i < size_per_sudo; i++)    //ÿ���վֿ��Ի�ü�������������Ŀ�Ļ���
			{
				int place[high_limit] = { 0 };
				copy_sudo = RequestMemory(onesudo);   //��Ϊһ���վ�onesudo�ж�λ��ᣬ��Ҫ����������ʹ��copy_sudo
				int place_length = GetBlankPlace(place, diffcult, low, high);
				int real_diffcult = GetDiffcult(place, place_length);   //Ӧ�õ���diffcult
				setNull(copy_sudo, place, place_length);    //���ɵõ�����copy_sudo
				if (oneSolution)
				{
					list<int**> sudo_list;
					GetAnswer(copy_sudo, size, &sudo_list);
					if (sudo_list.size() == 0) {  //�����޽�
						cout << "���ɵ������޽�" << endl;
						break;
					}
					if (sudo_list.size() != 1) {  //���(2)
						cout << "���ɵ��������" << endl;
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
	srand(time(NULL)); // ��ʼ�����������

	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		std::swap(array[i], array[j]);
	}
}

// ��0-80֮�����ȡn����������place
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
	//���ѶȺ��ڿ����ƻ���ڿյ�λ��
	//����ֵ��place�ĳ���
	//place����һ��ָ��
	//��������ɵõ�һ��place���飬���ж��Ƿ�����Ѷ�
	//place��һ��һά���飬����0��2��3��ʾ��0��2��3λ���ڿգ�����õ��ڶ�ά�����е�λ��
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

//������ڿ����õ����Ѷ�
float GetNumDiff(int length) {
	if (length <= low_limit)
		length = low_limit + 1;
	if (length > high_limit)
		length = high_limit;
	return float(length - low_limit) / float(high_limit - low_limit);
}


//�����ά����Ϊ����������
//��������ɶȵõ����Ѷ�
//���Ż����ӿ��ά��,ÿ�����ÿ��еĿհ������ཻ�����еĿհ���
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


