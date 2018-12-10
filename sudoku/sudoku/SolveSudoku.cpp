#include "stdafx.h"
#include "SolveSudoku.h"

int getblock(int row, int col)
{
	if (row <= 3) {
		if (col <= 3) {
			return 1;
		}
		else if (col <= 6)
		{
			return 2;
		}
		else {
			return 3;
		}
	}
	else if (row <= 6) {
		if (col <= 3) {
			return 4;
		}
		else if (col <= 6)
		{
			return 5;
		}
		else {
			return 6;
		}
	}
	else {
		if (col <= 3) {
			return 7;
		}
		else if (col <= 6)
		{
			return 8;
		}
		else {
			return 9;
		}
	}
}

SolveSudoku::SolveSudoku()
{
	path = "";
	cache = NULL;
	data = NULL;
	index = 0;
	goalNumber = 0;
	nowNumber = 0;
	result = 0;
	left = new int[nodeNum];
	right = new int[nodeNum];
	up = new int[nodeNum];
	down = new int[nodeNum];
	colValue = new int[nodeNum];
	rowValue = new int[nodeNum];
	fillValue = new int[nodeNum];
	targetCol = new int[nodeNum];
}

SolveSudoku::~SolveSudoku()
{
	delete[] cache;
	delete[] data;
	delete[] left;
	delete[] right;
	delete[] up;
	delete[] down;
	delete[] colValue;
	delete[] rowValue;
	delete[] fillValue;
	delete[] targetCol;
}

void SolveSudoku::startSolve(std::string adress)
{
	int i = 0;
	this->path = adress;
	dealFile();
	index = 0;
	result = 0;
	for (nowNumber = 0; nowNumber < goalNumber; nowNumber++) {
		solveUnit();
		toCache();
	}
	cache[result++] = '\0';
	rewrite();
}

void SolveSudoku::dealFile()
{
	int i, j;
	int len;
	file.open(path,std::ios::in);
	file.seekg(0, std::ios::end);
	len = file.tellg();
	cache = new char[len+1];
	file.seekg(0, std::ios::beg);
	file.read(cache, len);
	for (i = 0; i < len + 1; i++) {
		if (cache[i] >= '0'&&cache[i] <= '9') {
			goalNumber++;
		}
	}
	data = new int[goalNumber];
	for (i = 0, j = 0; i < len + 1; i++) {
		if (cache[i] >= '0'&&cache[i] <= '9') {
			data[j++] = cache[i] - '0';
		}
	}
	goalNumber /= 81;
	//std::cout << goalNumber<<'\n';
	return;
}

void SolveSudoku::solveUnit()
{
	//int i, j;
	bool back;
	//initial();
	initialA();
	//back = dealing();
	back = dealingA();
	//clear();
	return;
}

void SolveSudoku::initialA()
{
	int i, j;
	for (i = 0; i < 9; i++) {              //�ж���׼��ʼ��
		for (j = 0; j < 9; j++) {
			col[i][j] = true;
			row[i][j] = true;
			block[i][j] = true;
		}
	}
	for (i = 0; i < 9; i++) {               //����map��ʼ�����Կո�ȡֵ��������
		for (j = 0; j < 9; j++) {
			map[i][j] = data[index++];
			//std::cout << ' ' << map[i][j];
			if (map[i][j] > 0) {
				row[i][map[i][j] - 1] = false;
				col[j][map[i][j] - 1] = false;
				block[getblock(i + 1, j + 1) - 1][map[i][j] - 1] = false;
			}
		}
		//std::cout << '\n';
	}
	useNum = 0;           //ͷָ��
	left[0] = 0;
	right[0] = 0;
	up[0] = 0;
	down[0] = 0;
	useNum++;
	for (i = 1; i <= colNum; i++) {  //����Ԫ��
		left[i] = i - 1;
		right[i] = i + 1;
		down[i] = i;
		up[i] = i;
	}
	right[0] = 1;
	left[0] = colNum;
	right[colNum] = 0;
	useNum += colNum;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (map[i][j] != 0) {
				createNodeA(i + 1, j + 1, map[i][j]);
			}
			else{
				for (int k = 1; k <= 9; k++) {
					if (row[i][k-1] && col[j][k-1] && block[getblock(i + 1, j + 1) - 1][k-1]) {
						createNodeA(i + 1, j + 1, k);
					}
				}
			}
		}
	}
}

void SolveSudoku::createNodeA(int row, int col, int value)
{
	int i, j, temp;
	for (i = 0; i < 4; i++) {
		temp = useNum + i;
		left[temp] = useNum + (i - 1 + 4) % 4;
		right[temp] = useNum + (i + 1) % 4;
		if (i == 0) {
			j = 1 + (row - 1) * 9 + (col - 1);
		}
		else if (i == 1) {
			j = 82 + (row - 1) * 9 + (value - 1);
		}
		else if (i == 2) {
			j = 163 + (col - 1) * 9 + (value - 1);
		}
		else
		{
			j = 244 + (getblock(row, col) - 1) * 9 + (value - 1);
		}
		up[temp] = j;
		down[temp] = down[j];
		up[down[j]] = temp;
		down[j] = temp;
		colValue[temp] = col;
		rowValue[temp] = row;
		fillValue[temp] = value;
		targetCol[temp] = j;
	}
	useNum += 4;
	//std::cout << row << ' ' << col << ' ' << value<<'\n';
	return;
}

bool SolveSudoku::dealingA()
{
	//std::cout << ++pile << '\n';
	int i;
	bool state = false;
	if (right[0] == 0) {
		pile--;
		return true;
	}
   	i = right[0];
	for (i = down[right[0]]; i != right[0]; i = down[i]) {
		remove(i);
		map[rowValue[i] - 1][colValue[i] - 1] = fillValue[i];
		//std::cout << rowValue[i] << ' ' << colValue[i] << ' ' << fillValue[i] << '\n';
		state = dealingA();
		if (state) break;
		recover(i);
	}
	pile--;
	return state;
}

void SolveSudoku::remove(int p)
{
	int row, col, temp;
	col = p;
	do {
		left[right[targetCol[col]]] = left[targetCol[col]];
		right[left[targetCol[col]]] = right[targetCol[col]];
		row = down[col];
		while (row != col)
		{
			if (row != targetCol[col]) {
				temp = right[row];
				while (temp != row) {
					down[up[temp]] = down[temp];
					up[down[temp]] = up[temp];
					temp = right[temp];
				}
			}
			row = down[row];
		}
		col = right[col];
	} while (col != p);
	return;
}

void SolveSudoku::recover(int p)
{
	int row, col, temp;
	col = p;
	do {
		left[right[targetCol[col]]] = targetCol[col];
		right[left[targetCol[col]]] = targetCol[col];
		row = down[col];
		while (row != col)
		{
			if (row != targetCol[col]) {
				temp = right[row];
				while (temp != row) {
					down[up[temp]] = temp;
					up[down[temp]] = temp;
					temp = right[temp];
				}
			}
			row = down[row];
		}
		col = right[col];
	} while (col != p);
	return;
}

void SolveSudoku::toCache()
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

void SolveSudoku::rewrite()
{
	std::ofstream file;
	file.open(path, std::ios::trunc | std::ios::out);
	file << cache;
	file.close();
	return;
}

//void SolveSudoku::clear()
//{
//	node* temp;
//	while (top != NULL) {
//		temp = top;
//		top = top->next;
//		delete temp;
//	}
//	return;
//}
//

//void SolveSudoku::initial()
//{
//	int i, j;
//	head = new node;
//	head->No = 0;
//	head->up = head;
//	head->left = head;
//	head->down = head;
//	head->right = head;
//	head->col = NULL;
//	head->row = 0;
//	head->next = NULL;
//	top = head;
//	for (i = 0; i < 9; i++) {              //�ж���׼��ʼ��
//		for (j = 0; j < 9; j++) {
//			col[i][j] = true;
//			row[i][j] = true;
//			block[i][j] = true;
//		}
//	}
//	for (i = 0; i < 9; i++) {               //����map��ʼ�����Կո�ȡֵ��������
//		for (j = 0; j < 9; j++) {
//			map[i][j] = data[index++];
//			if (map[i][j] > 0) {
//				row[i][map[i][j] - 1] = false;
//				col[j][map[i][j] - 1] = false;
//				block[getblock(i+1,j+1)-1][map[i][j] - 1] = false;
//			}
//		}
//	}
//	node *temp;
//	for (i = 324; i >= 1; i--) { //dancing link ����Ԫ�س�ʼ�����
//		temp = new node;
//		temp->next = top;
//		top = temp;
//		temp->up = temp;
//		temp->down = temp;
//		temp->left = temp;
//		temp->right = temp;
//		temp->col = NULL;
//		temp->No = i;
//		temp->left = head;
//		temp->right = head->right;
//		head->right->left = temp;
//		head->right = temp;
//	}
//	for (i = 0; i < 9; i++) {         //dancing link ����
//		for (j = 0; j < 9; j++) {
//			if (map[i][j] > 0) {
//				createNode(i + 1, j + 1, map[i][j]);
//			}
//			else {
//				for (int k = 0; k < 9; k++) {
//					if (row[i][map[i][j] - 1] && col[j][map[i][j] - 1] && block[getblock(i + 1, j + 1) - 1][map[i][j] - 1]) {
//						createNode(i + 1, j + 1, map[i][j]);
//					}
//				}
//			}
//		}
//	}
//	return;
//}

//void SolveSudoku::recover(node * p)
//{
//	node* temp = p;
//	node* row, *q;
//	do {
//		temp->col->right->left = temp->col;
//		temp->col->left->right = temp->col;
//		row = temp->down;
//		while (row != temp)
//		{
//			if (row != temp->col) {
//				q = row->right;
//				while (q != row)
//				{
//					q->up->down = q;
//					q->down->up = q;
//					q = q->right;
//				}
//			}
//			row = row->down;
//		}
//		temp = temp->right;
//	} while (temp != p);
//	return;
//}

//void SolveSudoku::remove(node * p)
//{
//	node* temp = p;
//	node* row, *q;
//	do {
//		temp->col->right->left = temp->col->left;
//		temp->col->left->right = temp->col->right;
//		row = temp->down;
//		while (row!=temp)
//		{
//			if (row != temp->col) {
//				q = row->right;
//				while (q!=row)
//				{
//					q->up->down = q->down;
//					q->down->up = q->up;
//				}
//			}
//			row = row->down;
//		}
//		temp = temp->right;
//	} while (temp!=p);
//	return ;
//}

//void SolveSudoku::createNode(int row, int col, int value)     //���д�1��ʼ��ʵ��ֵ
//{
//	node *temp[4], *target;
//	int i, j;
//	target = head;
//	for (i = 0; i < 4; i++) {
//		temp[i] = new node;
//		temp[i]->next = top;
//		top = temp[i];
//		if (i == 0) {
//			j = 1 + (row - 1) * 9 + (col - 1);
//			while (target->No != j ) {
//				target = target->right;
//			}
//		}
//		else if (i == 1) {
//			j = 82 + (row - 1) * 9 + (value - 1);
//			while (target->No != j) {
//				target = target->right;
//			}
//		}
//		else if (i == 2) {
//			j = 163 + (col - 1) * 9 + (value - 1);
//			while (target->No !=j ){
//				target = target->right;
//			}
//		}
//		else
//		{
//			j = 244 + (getblock(row, col) - 1) * 9 + (value - 1);
//			while (target->No != j)
//			{
//				target = target->right;
//			}
//		}
//		temp[i]->col = target;
//		temp[i]->No = col;
//		temp[i]->value = value;
//		temp[i]->row = row;
//		temp[i]->up = target;
//		temp[i]->down = target->down;
//		target->down->up = temp[i];
//		target->down = temp[i];
//	}
//	for (i = 0; i < 4; i++) {
//		temp[i]->right = temp[(i + 1) % 4];
//		temp[i]->left = temp[(i - 1 + 4) % 4];
//	}
//	return;
//}

//bool SolveSudoku::dealing()
//{
//	bool state=false;
//	if (head->right == head) {
//		return true;
//	}
//	node *col, *temp;
//	for (col = head->right->down; col != head->right; col = col->right) {
//		remove(col);
//		map[col->row-1][col->No-1] = col->value;
//		state = dealing();
//		recover(col);
//		if (state) {
//			std::cout << col->row << ' ' << col->No << ' ' << col->value << '\n';
//			break;
//		}
//	}
//	return state;
//}