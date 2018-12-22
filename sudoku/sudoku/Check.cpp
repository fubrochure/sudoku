#include "stdafx.h"
#include "Check.h"

void help();

CheckParameter::CheckParameter()
{
	this->argc = 0;
	this->argv = NULL;
	this->create_num = 0;
	this->adress = "";
}

CheckParameter::CheckParameter(int argc, char** argv)
{
	this->argc = argc;
	this->argv = argv;
	create_num = 0;
	adress = "";
}


CheckParameter::~CheckParameter()
{

}

int CheckParameter::getCreateNumber()
{
	return create_num;
}

int CheckParameter::check()
{
	int i;
	if (argc != 3) {
		std::cout << "wrong number of patermeter!\n";
		help();
		return this->wrongOrder;
	}
	std::string order = argv[1];
	if (order == "-c") {
		for (i = 0; i < strlen(argv[2]); i++) {
			if (argv[2][i] > '9' || argv[2][i] < '0') {
				std::cout << "the second parameter should be a interger.\n";
				help();
				return this->wrongOrder;
			}
		}
		this->create_num = stringToInt(argv[2]);
		if (create_num > 1000000 || create_num < 0) {
			std::cout << "Too Many Cases\n";
			help();
			return wrongOrder;
		}
		return this->createOrder;
	}
	else if (order == "-s") {
		std::ifstream file;
		file.open(argv[2], std::ios::in);
		if (!file.is_open()) {
			std::cout << "can't open file" << argv[2]<<"\n";
			help();
			return wrongOrder;
		}
		else
		{
			adress = argv[2];
			//std::cout << adress;
			return this->solveOrder;
		}
	}
	else {
		std::cout << "the first parameter is wrong\n";
		help();
		return this->wrongOrder;
	}
}

std::string CheckParameter::getpath()
{
	return adress;
}

int CheckParameter::stringToInt(char * target)
{
	int i, temp;
	temp = 0;
	for (i = 0; i < strlen(target); i++) {
		temp = temp * 10 + target[i] - '0';
	}
	return temp;
}

void help()
{
	std::cout << "to create sudoku:\n\
sudoku.exe -c n (0<=n<=1000000)\n\
to solve sudoku:\n\
sudoku.exe -s absolutepath\n";
}