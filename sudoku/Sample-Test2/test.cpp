#include "pch.h"
#include "../sudoku/Check.h"
#include"../sudoku/Check.cpp"
#include"../sudoku/CreateSudoku.h"
#include"../sudoku/CreateSudoku.cpp"
#include"../sudoku/SolveSudoku.h"
#include"../sudoku/SolveSudoku.cpp"

bool checkCreate(char* result, int num);
bool compare(int** a, int** b);
bool checkSolution(char *data, int num);
bool fill(int row, int clo, int value, int* criterion);

TEST(Check, CheckRightCreate)
{
	char** parameters = new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "-c\0");
	strcpy(parameters[2], "10000\0");
	CheckParameter check(3, parameters);
	EXPECT_EQ(1, check.check());
}

TEST(Check, WrongNumOfParameter)
{
	char** parameters = new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "-c\0");
	strcpy(parameters[2], "10000\0");
	CheckParameter check(2, parameters);
	EXPECT_EQ(-1, check.check());
}

TEST(Check, WrongParameter)
{
	char** parameters = new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "fsdsf\0");
	strcpy(parameters[2], "10000\0");
	CheckParameter check(2, parameters);
	EXPECT_EQ(-1, check.check());
}

TEST(Check, CheckWrongCreate)
{
	char** parameters = new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "-c\0");
	strcpy(parameters[2], "1ad00\0");
	CheckParameter check(3, parameters);
	EXPECT_EQ(-1, check.check());
}

TEST(Check, TooManyCreateCases)
{
	char** parameters = new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "-c\0");
	strcpy(parameters[2], "10000000\0");
	CheckParameter check(3, parameters);
	EXPECT_EQ(-1, check.check());
}

TEST(Check, CheckRightSolve)
{
	char** parameters=new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "-s\0");
	strcpy(parameters[2], "G:\\github\\sudoku\\sudoku\\Debug\\p.txt\0");
	CheckParameter check(3, parameters);
	EXPECT_EQ(2, check.check());
}

TEST(Check, CheckWrongSolve)
{
	char** parameters = new char*[3];
	parameters[0] = new char[1];
	parameters[1] = new char[100];
	parameters[2] = new char[100];
	strcpy(parameters[1], "-s\0");
	strcpy(parameters[2], "1ad00\0");
	CheckParameter check(3, parameters);
	EXPECT_EQ(-1, check.check());
}

TEST(Create, MinCase)
{
	int num = 1;
	CreateSudoku create;
	create.stratCreate(num);
	char* result = create.getOuput();
	EXPECT_TRUE(true);
}

TEST(Create, MaxCase)
{
	int num = 1000000;
	CreateSudoku create;
	create.stratCreate(num);
	char* result = create.getOuput();
	EXPECT_TRUE(true);
}

TEST(Create, SameResult)
{
	int num = 10000;
	CreateSudoku create;
	create.stratCreate(num);
	char* result = create.getOuput();
	EXPECT_TRUE(checkCreate(result, num));
}

TEST(Solve, RightSolution) 
{
	SolveSudoku soluve;
	std::string adress = "G:\\github\\sudoku\\sudoku\\Debug\\p.txt";
	soluve.startSolve(adress);
	char* data = soluve.getData();
	EXPECT_TRUE(checkSolution(data, 20));
}

TEST(Solve, PlentyOfCases) 
{
	SolveSudoku soluve;
	std::string adress = "G:\\github\\sudoku\\sudoku\\x64\\Debug\\1000000.txt\0";
	soluve.startSolve(adress);
	char* data = soluve.getData();
	EXPECT_TRUE(checkSolution(data, 1000000));
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

bool checkCreate(char * result, int num)
{
	int*** map = new int**[num];
	int i, j, k;
	int len = strlen(result);
	int index = 0;
	for (i = 0; i < num; i++) {
		map[i] = new int*[9];
		for (j = 0; j < 9; j++) {
			map[i][j] = new int[9];
			for (k = 0; k < 9; k++) {
				while (result[index]<'1' || result[index]>'9')
				{
					index++;
				}
				map[i][j][k] = result[index++];
			}
		}
	}
	bool flag;
	flag = true;
	for (i = 0; i < num-1; i++) {
		for (j = i + 1; j < num; j++) {
			if (!compare(map[i], map[j])) {
				flag = false;
				break;
			}
			//std::cout << "compare:" << i << " & " << j << std::endl;
		}
		if (i % 9999 == 0) {
			std::cout << "compare:" << i << std::endl;
		}
		if (!flag) {
			break;
		}
	}
	for (i = 0; i < num; i++) {
		for (j = 0; j < 9; j++) {
			delete[] map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
	return flag;
}

bool compare(int ** a, int ** b)
{
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (a[i][j] != b[i][j]) {
				return true;
			}
		}
	}
	return false;
}

bool checkSolution(char * data, int num)
{
	int i, j, k;
	int index;
	index = 0;
	int criterion[27];
	int temp;
	for (i = 0; i < num; i++) {
		for (j = 0; j < 27; j++) {
			criterion[j] = 511;
		}
		for (j = 0; j < 9; j++) {
			for (k = 0; k < 9; k++) {
				while (data[index]>'9' || data[index]<'1')
				{
					index++;
				}
				temp = data[index++]-'0';
				if (!fill(j + 1, k + 1, temp, criterion)) {
					std::cout << "map:" << i + 1 << " row:" << j + 1 << " clo:" << k + 1 << " value:" << temp << std::endl;
					return false;
				}
			}
		}
	}
	return true;
}

bool fill(int row, int clo, int value, int* criterion)
{
	int flag = criterion[row - 1] & criterion[9 + clo - 1] & criterion[18 + (getblock(row, clo) - 1)] & encode[value - 1];
	if (flag != 0) {
		
		criterion[0 + row - 1] = criterion[row - 1] & (~encode[value - 1]);
		criterion[9 + clo - 1] = criterion[9 + clo - 1] & (~encode[value - 1]);
		criterion[18 + (getblock(row, clo) - 1)] = criterion[18 + (getblock(row, clo) - 1)] & (~encode[value - 1]);
		return true;
	}
	return false;
}