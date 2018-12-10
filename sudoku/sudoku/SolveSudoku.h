#pragma once

struct node {
	struct node* up;
	struct node* down;
	struct node* left;
	struct node* right;
	struct node* col;
	struct node* next;
	int No;
	int row;
	int value;
};

class SolveSudoku
{
public:
	SolveSudoku();
	~SolveSudoku();
	void startSolve(std::string);
private:
	std::string path;
	std::ifstream file;
	char * cache;
	int * data;
	int goalNumber;
	int nowNumber;
	int index;
	int result;
	int map[9][9] = { 0 };
	bool col[9][9] = {true};
	bool row[9][9] = {true};
	bool block[9][9] = {true};
	const static int nodeNum = 9 * 9 * 4 + 9 * 9 * 9 * 4 + 1;
	const static int colNum = 9 * 9 * 4;
	int pile = 0;
	int *left;
	int *right;
	int *up;
	int *down;
	int *colValue;
	int *rowValue;
	int *fillValue;
	int *targetCol;
	int *number;
	int useNum;
	void dealFile();
	void solveUnit();
	//void initial();
	void initialA();
	//void createNode(int row, int clo, int value);
	void createNodeA(int row, int col, int value);
	//bool dealing();
	bool dealingA();
	//void remove(node* p);
	void remove(int p);
	//void recover(node* p);
	void recover(int p);
	//void clear();
	void toCache();
	void rewrite();
	//node * head;
};





