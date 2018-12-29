#include "stdafx.h"
#include "CreateSudoku.h"

CreateSudoku::CreateSudoku()      //��ʼ��
{
	this->goalNumber = 0;
	nowNumber = 0;
	target = 0;
}

CreateSudoku::~CreateSudoku()
{
	delete[] output;
}

bool CreateSudoku::stratCreate(int goalNumber)    //�ⲿ���ú���
{
	this->goalNumber = goalNumber;
	int temp = ((int)163 * goalNumber) + 100;
	output = new char[temp];
	createSeed(1);
	stringToFile();
	return true;
}

char * CreateSudoku::getOuput()    //��Ԫ����ʹ��
{
	return output;
}

bool CreateSudoku::createSeed(int cursor)      //��seed����ȫ����
{
	int i;
	if (cursor == 8) {
		createMap();
	}
	else {
		for (i = cursor; i <= 8; i++) {
			swap(seed,cursor,i);
			createSeed(cursor + 1);
			if (nowNumber == goalNumber) break;
			swap(seed, cursor, i);
			
		}
	}
	return true;
}

bool CreateSudoku::createMap()                 //seed���ɺ�����ƽ����������
{
	int i, j, k, l, m;
	for (i = 0, k = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sudoku[i][j] = seed[k++];
			for (l = 0; l < 3; l++) {
				for (m = 0; m < 3; m++) {
					sudoku[(i + m) % 3 + 3 * l][(j + l) % 3 + m * 3] = sudoku[i][j];
				}
			}
		}	
	}
	changeMap();
	return true;
}

void CreateSudoku::changeMap()               //��map���±����ȫ���У��൱�ڽ������б任
{
	changePartly(Index, 3, 5);
	return;
}

void CreateSudoku::swap(int* goalArray,int a, int b)     //ȫ���еĽ�������
{
	int temp;
	temp = goalArray[a];
	goalArray[a] = goalArray[b];
	goalArray[b] = temp;
}

void CreateSudoku::changePartly(int * a, int start, int end)   //�����λ�ý���ȫ����
{
	int i;
	if (start == end) {
		if (end == 5) {
			changePartly(a, 6, 8);
		}
		else if (end == 8) {
			changePartly(a, 12, 14);
		}
		else if (end == 14) {
			changePartly(a, 15, 17);
		}
		else {
			outputResult();
		}
	}
	else {
		for (i = start; i <= end; i++) {
			swap(a, start, i);
			changePartly(a, start + 1, end);
			if (nowNumber == goalNumber) break;
			swap(a, start, i);
			
		}
	}
	return;
}

void CreateSudoku::outputResult()           //���д��char*
{
	int i, j;
	if (nowNumber > 0) {
		output[target++] = '\n';
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (j == 0) {
				output[target++] = sudoku[Index[i]][Index[j + 9]] +'0';
			}
			else {
				output[target++] = ' ';
				output[target++] = sudoku[Index[i]][Index[j + 9]] +'0';
			}
		}
		output[target++] = '\n';	
	}
	nowNumber++;
	return;
}

void CreateSudoku::stringToFile()//д���ļ�
{
	output[target++] = '\0';
	std::ofstream file;
	file.open(".\\sudoku.txt", std::ios::out | std::ios::trunc);
	file << output;
	file.close();
	return ;
}

