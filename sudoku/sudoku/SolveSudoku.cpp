#include "stdafx.h"
#include "SolveSudoku.h"

const int encode[9] = { 1,2,4,8,16,32,64,128,256 };

int getblock(int row, int col)
{
	return (row - 1) / 3 * 3 + (col + 2) / 3;
}

SolveSudoku::SolveSudoku()
{
	cache = NULL;
	data = NULL;
}

SolveSudoku::~SolveSudoku()
{
	delete[] cache;
	delete[] data;
}

void SolveSudoku::startSolve(std::string adress)    //��ʼ�����������Ϊpublic�����ⲿ����
{
	int i = 0;
	int goalNumber, nowNumber, result,index;
	std::string path;
	path = adress;
	goalNumber = dealFile(path);
	index = 0;
	result = 0;
	for (nowNumber = 0; nowNumber < goalNumber; nowNumber++) {
		solveUnit(index);
		toCache(nowNumber, result);
	}
	cache[result++] = '\0';
	rewrite(path);
}

int SolveSudoku::dealFile(std::string path)    //��ȡ�ļ��е�����
{
	int i, j;
	int len;
	int number = 0;
	std::ifstream file;
	file.open(path,std::ios::in);
	file.seekg(0, std::ios::end);
	len = int(file.tellg());
	int temp = (int)len + 1;
	cache = new char[temp];
	file.seekg(0, std::ios::beg);
	file.read(cache, len);
	for (i = 0; i < temp; i++) {
		if (cache[i] >= '0'&&cache[i] <= '9') {
			number++;
		}
	}
	data = new int[number];
	for (i = 0, j = 0; i < temp; i++) {
		if (cache[i] >= '0'&&cache[i] <= '9') {
			data[j++] = cache[i] - '0';
		}
	}
	number /= 81;
	return number;
}

void SolveSudoku::solveUnit(int& index)           //��������ʼ�������
{
	int criterion[27];
	initialB(criterion, index);
	dealingB(criterion, 0, 0);
	return;
}

void SolveSudoku::initialB(int *criterion, int& index)   //��ʼ������������ص����ݽṹ
{
	int i, j;
	for (i = 0; i < 27; i++) {
		criterion[i] = 511;
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			map[i][j] = data[index++];
			if (map[i][j] != 0) {
				removeA(criterion, i + 1, j + 1, map[i][j]);
			}
		}
	}
}

void SolveSudoku::removeA(int * criterion, int row, int clo, int value) //����������жϱ�׼�Ƴ�          //����������������������и���
{
	criterion[0 + row - 1] = criterion[row - 1] & (~encode[value - 1]);
	criterion[9 + clo - 1] = criterion[9 + clo - 1] & (~encode[value - 1]);
	criterion[18 + (getblock(row, clo) - 1)] = criterion[18 + (getblock(row, clo) - 1)] & (~encode[value - 1]);
}  

void SolveSudoku::recoverA(int * criterion, int row, int clo, int value)          //�ָ���������
{
	criterion[0 + row - 1] = criterion[row - 1] | (encode[value - 1]);
	criterion[9 + clo - 1] = criterion[9 + clo - 1] | (encode[value - 1]);
	criterion[18 + (getblock(row, clo) - 1)] = criterion[18 + (getblock(row, clo) - 1)] | (encode[value - 1]);
}    

bool SolveSudoku::dealingB(int* criterion, int i, int j)       //�������Ļ��ݺ���
{
	int k;
	bool state = false;
	for (; i < 9; i++) {
		for (; j < 9; j++) {
			if (map[i][j] == 0) {
				state = true;
				break;
			}
		}
		if (state) {
			break;
		}
		j = 0;
	}
	if (!state) {
		return true;
	}
	int value;
	state = false;
	for (k = 0; k < 9; k++) {
		value = k + 1;
		if (!fill(i + 1, j + 1, value, criterion)) {
			continue;
		}
		map[i][j] = value;
		removeA(criterion, i + 1, j + 1, value);
		state = dealingB(criterion, i, j);
		if (state) {
			break;
		}
		recoverA(criterion, i + 1, j + 1, value);
		map[i][j] = 0;
	}
	return state;
}

bool SolveSudoku::fill(int row, int clo, int value, int* criterion)  //�ж��Ƿ�������ĳ����             //�ж�����ĳ��λ���Ƿ��ܹ���д����
{
	int temp = criterion[row - 1] & criterion[9 + clo - 1] & criterion[18 + (getblock(row, clo) - 1)] & encode[value - 1];
	if (temp != 0) {
		return true;
	}
	return false;
}

void SolveSudoku::toCache(int nowNumber, int &result)     //������д��char*������
{
	int i, j;
	if (nowNumber != 0) {
		cache[result++] = '\n';
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (j != 0) {
				cache[result++] = ' ';
			}
			cache[result++] = map[i][j] + '0';
		}
		cache[result++] = '\n';
	}
	return;
}

void SolveSudoku::rewrite(std::string path)   //���
{
	
	std::ofstream file;
	file.open(".\\sudoku.txt", std::ios::trunc | std::ios::out);
	file << cache;
	file.close();
	return;
}

char * SolveSudoku::getData()   //��Ԫ������
{
	return cache;
}
