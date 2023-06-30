#include "GetAnswer.h"
#include "Util.h"
#include "ProduceFinal.h"
#include "GenerateSuodekuFromFinal.h"
#include "Read_Write_File.h"
#include <string>
#pragma warning(disable : 4996)

int main(int argc, char** argv) {
	if (argc == 1) {
		cout << "please input command in cmd line" << endl;
		return 0;
	}
	else {
		if (!strcmp(argv[1], "-c")) {
			int produce_num = atoi(argv[2]);
			if (produce_num >= 1 && produce_num <= 1000000) {
				int produce_num = atoi(argv[2]);
				ProucedByPermutationTrans(produce_num);
				cout << produce_num << "个数独终局已生成" << endl;
			}
			else {
				cout << "input param after '-c' error!" << endl;
				return 0;
			}
		}
		else if (!strcmp(argv[1], "-s")) {
			char* gamePath = argv[2];

			if (gamePath != NULL) {
				int size = 1;
				ifstream read;
				read.open(gamePath);
				int** sudo = RequestMemory(0);
				int i = 0;
				while (read_from_text(sudo, read)) 
				{
					list<int**> sudo_list;
					GetAnswer(sudo, size, &sudo_list);

					list<int**>::iterator it_1 = sudo_list.begin();
					while (it_1 != sudo_list.end()) {
						output_result(*it_1);
						it_1++;
					}

					i++;
					if (i == 6)
						break;
				}
				cout << "game求解完毕" << endl;
				DeleteMemory(sudo);
			}
			else {
				cout << "please input something after -s" << endl;
				return 0;
			}
		}
		else if (!strcmp(argv[1], "-n")) {
			if (argc == 3) {
				int num = atoi(argv[2]);
				if (num >= 1 && num <= 10000) {
					ProucedByPermutationTrans(num);		//生成num个终局（保证足够即可）
					Generate(num, false, 0, 20, 55);	//从生成的终局中得到num个数独game，存入game.txt
				}
				else {
					cout << "input param after '-n' error!" << endl;
					return 0;
				}
			}
			else if (argc == 4) {
				int num = atoi(argv[2]);
				bool oneSolution = false;
				if (!strcmp(argv[3], "-u"))
					oneSolution = true;
				else
				{
					cout << "param argv[3] error!";
					return 0;
				}

				if (num >= 1 && num <= 10000) {
					ProucedByPermutationTrans(10*num);		//生成10*num个终局（保证足够即可）
					Generate(num, oneSolution, 0, 20, 55);	//从生成的终局中得到num个数独game，存入game.txt
				}
				else {
					cout << "input param after '-n' error!" << endl;
					return 0;
				}
			}
			else if (argc == 5) {
				if (!strcmp(argv[3], "-m")) {
					int num = atoi(argv[2]);
					int diff = atoi(argv[4]);

					if (num >= 1 && num <= 10000 && diff >= 1 && diff <= 3) {
						ProucedByPermutationTrans(num);		//生成num个终局
						Generate(num, false, diff, 20, 55);	//从生成的终局中得到num个数独game，存入game.txt
					}
					else {
						cout << "params error!" << endl;
						return 0;
					}
				}
				else {
					int num = atoi(argv[2]);
					int low = 20, high = 55;
					std::string range = argv[4]; // 从命令行参数中获取 "20~55" 字符串
					size_t tildeIndex = range.find("~");

					if (tildeIndex != std::string::npos) {
						std::string strA = range.substr(0, tildeIndex); // 提取 "~" 前面的数字字符串
						std::string strB = range.substr(tildeIndex + 1); // 提取 "~" 后面的数字字符串

						low = std::stoi(strA); // 将字符串转换为整数
						high = std::stoi(strB); // 将字符串转换为整数

						cout << "low: " << low << "    " << "high: " << high << endl;
					}
					else {
						std::cout << "argv[4] has no '~' symbol!" << std::endl;
						return 0;
					}

					if (num >= 1 && num <= 10000 && low >= 20 && high <= 55) {
						ProucedByPermutationTrans(num);		//生成num个终局
						Generate(num, false, 0, low, high);	//从生成的终局中得到num个数独game，存入game.txt
					}
					else {
						cout << "params error!" << endl;
						return 0;
					}
				}
			}
			else {
				cout << "too many params!" << endl;
				return 0;
			}
		}
		else {
			cout << "input cmd error!" << endl;
			return 0;
		}
	}
}
