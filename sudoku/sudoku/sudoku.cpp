// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"SolveSudoku.h"
#include"SolveSudoku.h"
#include"CreateSudoku.h"
#include"Check.h"
#include"time.h"

const int keynumber = 4;

int main(int argc, char** argv)
{
	clock_t start, end;
	start = clock();
	CheckParameter *check = new CheckParameter(argc, argv);
	CreateSudoku create;
	SolveSudoku solve;
	switch (check->check())
	{
	case 1:
		create.stratCreate(check->getCreateNumber());
		break;
	case 2:
		solve.startSolve(check->getpath());
		break;
	default:
		break;
	}
	end = clock();
	std::cout << "time " << ((double)end - (double)start)/CLOCKS_PER_SEC << "\n";
	return 0;
}


