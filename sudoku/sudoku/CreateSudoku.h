#pragma once
class CreateSudoku
{
public:
	CreateSudoku();
	~CreateSudoku();
	bool stratCreate(int goalNumber);
	char* getOuput();
private:
	const int keynumber = 4;
	int goalNumber;
	int nowNumber;
	int seed[9] = { 4,1,2,3,5,6,7,8,9 };
	int sudoku[9][9] = {0};
	int result[9][9] = {0};
	int Index[18] = { 0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8 };
	//std::string output;
	//std::ofstream file;
	char *output;
	int target;
	bool createSeed(int cursor);
	bool createMap();
	void changeMap();
	void swap(int *goalArray,int a, int b);
	void changePartly(int* a, int start, int end);
	void getResult();
	void outputResult();
	void stringToFile();
	
};

