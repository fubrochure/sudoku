// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define keynumber 4

int checkParameter(int argc, char ** argv);
int stringToInt(char* target);
class SudokuMap
{
public:
	SudokuMap();
	SudokuMap(int type, int number);
	SudokuMap(int type, char* path);
	~SudokuMap();

private:
	int modle;
	int number;
	char *path;
};

int main(int argc, char** argv)
{
	int model;
	SudokuMap sudoku;
	model = checkParameter(argc, argv);
	if (-1==model) {
		
	}
	else if(1==model){
		
		sudoku = SudokuMap(1, stringToInt(argv[2]));
	}
	else {
		sudoku = SudokuMap(2, argv[2]);
	}
	return 0;
}

int checkParameter(int argc, char ** argv)
{
	int i;
	if (argc != 3) {
		std::cout << "wrong number of patermeter!\n";
		return -1;
	}
	/*for (i = 0; i < argc; i++) {
	std::cout << argv[i];
	}*/
	std::string order = argv[1];
	if (order == "-c") {
		for (i = 0; i < strlen(argv[2]); i++) {
			if (argv[2][i] > '9' || argv[2][i] < '0') {
				std::cout << "the second parameter should be a interger.\n";
				return -1;
			}
		}
		return 1;
	}
	else if (order == "-s") {

		return 2;
	}
	else {
		std::cout << "the first parameter is wrong\n";
		return -1;
	}
}

int stringToInt(char* target)
{
	int i, temp;
	temp = 0;
	for (i = 0; i < strlen(target); i++) {
		temp = temp * 10 + target[i] - '0';
	}
	return temp;
}



SudokuMap::SudokuMap()
{

}

SudokuMap::SudokuMap(int type, int number) 
{
	this->modle = type;
	this->number = number;
	std::cout << "model: creat, goal: " << number << "\n";
}

SudokuMap::SudokuMap(int type, char* path)
{
	this->modle = type;
	this->path = path;
	std::cout << "model: solve, path: " << path << "\n";
}

SudokuMap::~SudokuMap()
{

}