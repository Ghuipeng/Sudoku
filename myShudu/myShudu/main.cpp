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
				cout << produce_num << "�������վ�������" << endl;
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

					auto it_1 = sudo_list.begin();
					while (it_1 != sudo_list.end()) {
						output_result(*it_1);
						it_1++;
					}
					DeleteMemory(sudo_list);
					i++;
					if (i == 6)
						break;
				}
				cout << "game������" << endl;
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
					ProucedByPermutationTrans(num);		//����num���վ֣���֤�㹻���ɣ�
					Generate(num, false, 0, 20, 55);	//�����ɵ��վ��еõ�num������game������game.txt
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
					cout << "param argv[3] error!";

				if (num >= 1 && num <= 10000) {
					ProucedByPermutationTrans(10*num);		//����10*num���վ֣���֤�㹻���ɣ�
					Generate(num, oneSolution, 0, 20, 55);	//�����ɵ��վ��еõ�num������game������game.txt
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
						ProucedByPermutationTrans(num);		//����num���վ�
						Generate(num, false, diff, 20, 55);	//�����ɵ��վ��еõ�num������game������game.txt
					}
					else {
						cout << "params error!" << endl;
						return 0;
					}
				}
				else {
					int num = atoi(argv[2]);
					int low = 20, high = 55;
					std::string range = argv[4]; // �������в����л�ȡ "20~55" �ַ���
					size_t tildeIndex = range.find("~");

					if (tildeIndex != std::string::npos) {
						std::string strA = range.substr(0, tildeIndex); // ��ȡ "~" ǰ��������ַ���
						std::string strB = range.substr(tildeIndex + 1); // ��ȡ "~" ����������ַ���

						low = std::stoi(strA); // ���ַ���ת��Ϊ����
						high = std::stoi(strB); // ���ַ���ת��Ϊ����

						cout << "low: " << low << "    " << "high: " << high << endl;
					}
					else {
						std::cout << "argv[4] has no '~' symbol!" << std::endl;
					}

					if (num >= 1 && num <= 10000 && low >= 20 && high <= 55) {
						ProucedByPermutationTrans(num);		//����num���վ�
						Generate(num, false, 0, low, high);	//�����ɵ��վ��еõ�num������game������game.txt
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