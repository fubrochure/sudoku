#pragma once

class CheckParameter
{
public:
	CheckParameter();
	CheckParameter(int argc, char** argv);
	~CheckParameter();
	int getCreateNumber();
	int check();
private:
	const int createOrder = 1;
	const int solveOrder = 2;
	const int wrongOrder = -1;
	int argc;
	char** argv;
	int create_num;
	std::string adress;
	int stringToInt(char* target);
};

