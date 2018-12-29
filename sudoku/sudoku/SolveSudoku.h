#pragma once

class SolveSudoku
{
public:
	SolveSudoku();
	~SolveSudoku();
	void startSolve(std::string);
	char* getData();
private:
	char * cache;
	int * data;
	int map[9][9] = { 0 };
	const static int nodeNum = 9 * 9 * 4 + 9 * 9 * 9 * 4 + 1;
	const static int colNum = 9 * 9 * 4;
	int dealFile(std::string);
	void solveUnit(int&);
	void initialB(int*, int&);
	void removeA(int* criterion, int row, int clo, int value);
	void recoverA(int* criterion, int row, int clo, int value);
	bool dealingB(int*, int i, int j);
	bool fill(int row, int clo, int value, int* criterion);
	void toCache(int , int&);
	void rewrite(std::string);
};





