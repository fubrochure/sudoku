#include "stdafx.h"
#include "Check.h"


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
}


CheckParameter::~CheckParameter()
{

}

int CheckParameter::check()
{
	int i;
	if (argc != 3) {
		std::cout << "wrong number of patermeter!\n";
		return this->wrongOrder;
	}
	std::string order = argv[1];
	if (order == "-c") {
		for (i = 0; i < strlen(argv[2]); i++) {
			if (argv[2][i] > '9' || argv[2][i] < '0') {
				std::cout << "the second parameter should be a interger.\n";
				return this->wrongOrder;
			}
		}
		this->create_num = stringToInt(argv[2]);
		return this->createOrder;
	}
	else if (order == "-s") {
		adress = argv[2];
		return this->solveOrder;
	}
	else {
		std::cout << "the first parameter is wrong\n";
		return this->wrongOrder;
	}
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
