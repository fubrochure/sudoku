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
	char* getData();
private:
	char * cache;
	int * data;
	int map[9][9] = { 0 };
	const static int nodeNum = 9 * 9 * 4 + 9 * 9 * 9 * 4 + 1;
	const static int colNum = 9 * 9 * 4;
	int *left;
	int *right;
	int *up;
	int *down;
	int *colValue;
	int *rowValue;
	int *fillValue;
	int *targetCol;
	int *number;
	int dealFile(std::string);
	void solveUnit(int&);
	//void initial();
	void initialA(int&);
	void initialB(int*, int&);
	//void createNode(int row, int clo, int value);
	void createNodeA(int row, int col, int value, int&);
	void update(int row, int clo, int value, bool* criterion);
	void removeA(int* criterion, int row, int clo, int value);
	void recoverA(int* criterion, int row, int clo, int value);
	//bool dealing();
	bool dealingA();
	bool dealingB(int*);
	bool fill(int row, int clo, int value, int* criterion);
	//void remove(node* p);
	void remove(int p);
	
	//void recover(node* p);
	void recover(int p);
	
	//void clear();
	void toCache(int , int&);
	void rewrite(std::string);
	//node * head;


};





