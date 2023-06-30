#include "Read_Write_File.h"
#include "Util.h"
#pragma warning(disable : 4996)
char* Final_path = (char*)("./sudoku_final.txt");
char* Game_path = (char*)("./game.txt");
char* Result_path = (char*)("./sudoku.txt");


void output_to_text(int** sudo, ofstream& write) {
	char sudo_char[length * (length + 1) + 1];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++) {
			sudo_char[i * (length + 1) + j] = '0' + sudo[i][j];
		}
		sudo_char[(i) * (length + 1) + length] = '\n';
	}
	sudo_char[length * (length + 1)] = '\n';
	write.write(sudo_char, sizeof(sudo_char));
	write.flush();
}
bool read_from_text(int** sudo, ifstream& read) {
	if (read.eof() && read)
		return false;
	char sudo_char[length * (length + 1) + 1];
	read.read(sudo_char, sizeof(sudo_char));
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++) {
			sudo[i][j] = sudo_char[i * (length + 1) + j] - '0';
		}
	}
	return true;
}
void output_to_screen(int** sudo) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cout << sudo[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void output(int** sudo) {
	output_to_screen(sudo);
	ofstream write;
	write.open(Final_path, ios::app);
	output_to_text(sudo, write);
	write.close();
}
void output(list<int**> sudo_list) {
	list<int** >::iterator it;
	for (it = sudo_list.begin(); it != sudo_list.end(); it++) {
		output(*it);
	}
}



void output_game(int** sudo) {
	output_to_screen(sudo);
	ofstream write;
	write.open(Game_path, ios::app);
	output_to_text(sudo, write);
	write.close();
}
void output_game(list<int**> sudo_list) {
	list<int** >::iterator it;
	for (it = sudo_list.begin(); it != sudo_list.end(); it++) {
		output_game(*it);
	}
}
void output_result(int** sudo) {
	output_to_screen(sudo);
	ofstream write;
	write.open(Result_path, ios::app);
	output_to_text(sudo, write);
	write.close();
}
void output_result(list<int**> sudo_list) {
	list<int** >::iterator it;
	for (it = sudo_list.begin(); it != sudo_list.end(); it++) {
		output_result(*it);
	}
}