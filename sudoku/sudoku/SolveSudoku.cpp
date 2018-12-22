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
	/*left = new int[nodeNum];
	right = new int[nodeNum];
	up = new int[nodeNum];
	down = new int[nodeNum];
	colValue = new int[nodeNum];
	rowValue = new int[nodeNum];
	fillValue = new int[nodeNum];
	targetCol = new int[nodeNum];*/
	//number = new int[colNum + 1];
}

SolveSudoku::~SolveSudoku()
{
	delete[] cache;
	delete[] data;
	//delete[] left;
	//delete[] right;
	//delete[] up;
	//delete[] down;
	//delete[] colValue;
	//delete[] rowValue;
	//delete[] fillValue;
	//delete[] targetCol;
	//delete[] number;
}

void SolveSudoku::startSolve(std::string adress)    //开始求解数独，作为public方法外部调用
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
		//std::cout << "finish one\n";
	}
	cache[result++] = '\0';
	rewrite(path);
}

int SolveSudoku::dealFile(std::string path)    //读取文件中的数独
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

void SolveSudoku::solveUnit(int& index)           //对数独开始进行求解
{
	//int i, j;
	int criterion[27];
	//initial();
	//initialA(index);
	initialB(criterion, index);
	//back = dealing();
	//dealingA();
	dealingB(criterion, 0, 0);
	//clear();
	return;
}

//void SolveSudoku::initialA(int &index)
//{
//	int i, j;
//	int useNum=0;
//	bool col[9][9];
//	bool row[9][9];
//	bool block[9][9];
//	for (i = 0; i < 9; i++) {              //判定标准初始化
//		for (j = 0; j < 9; j++) {
//			col[i][j] = true;
//			row[i][j] = true;
//			block[i][j] = true;
//		}
//	}
//	for (i = 0; i < 9; i++) {               //数独map初始化，对空格取值加入限制
//		for (j = 0; j < 9; j++) {
//			map[i][j] = data[index++];
//			//std::cout << ' ' << map[i][j];
//			if (map[i][j] > 0) {
//				row[i][map[i][j] - 1] = false;
//				col[j][map[i][j] - 1] = false;
//				block[getblock(i + 1, j + 1) - 1][map[i][j] - 1] = false;
//			}
//		}
//		//std::cout << '\n';
//	}
//	useNum = 0;           //头指针
//	left[0] = 0;
//	right[0] = 0;
//	up[0] = 0;
//	down[0] = 0;
//	useNum++;
//	for (i = 1; i <= colNum; i++) {  //辅助元素
//		left[i] = i - 1;
//		right[i] = i + 1;
//		down[i] = i;
//		up[i] = i;
//		number[i] = 0;
//	}
//	right[0] = 1;
//	left[0] = colNum;
//	right[colNum] = 0;
//	useNum += colNum;
//	for (i = 0; i < 9; i++) {
//		for (j = 0; j < 9; j++) {
//			if (map[i][j] != 0) {
//				createNodeA(i + 1, j + 1, map[i][j], useNum);
//			}
//			else{
//				for (int k = 1; k <= 9; k++) {
//					if (row[i][k-1] && col[j][k-1] && block[getblock(i + 1, j + 1) - 1][k-1]) {
//						createNodeA(i + 1, j + 1, k, useNum);
//					}
//				}
//			}
//		}
//	}
//}

void SolveSudoku::initialB(int *criterion, int& index)   //初始化数独求解的相关的数据结构
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

//void SolveSudoku::createNodeA(int row, int col, int value, int&useNum)
//{
//	int i, j, temp;
//	for (i = 0; i < 4; i++) {
//		temp = useNum + i;
//		left[temp] = useNum + (i - 1 + 4) % 4;
//		right[temp] = useNum + (i + 1) % 4;
//		if (i == 0) {
//			j = 1 + (row - 1) * 9 + (col - 1);
//		}
//		else if (i == 1) {
//			j = 82 + (row - 1) * 9 + (value - 1);
//		}
//		else if (i == 2) {
//			j = 163 + (col - 1) * 9 + (value - 1);
//		}
//		else
//		{
//			j = 244 + (getblock(row, col) - 1) * 9 + (value - 1);
//		}
//		up[temp] = j;
//		down[temp] = down[j];
//		up[down[j]] = temp;
//		down[j] = temp;
//		colValue[temp] = col;
//		rowValue[temp] = row;
//		fillValue[temp] = value;
//		targetCol[temp] = j;
//		number[j]++;
//	}
//	useNum += 4;
//	//std::cout << row << ' ' << col << ' ' << value<<'\n';
//	return;
//}

//void SolveSudoku::update(int row, int clo, int value, bool * criterion)
//{
//	criterion[row * 9 + map[row][clo] - 1] = false;
//	criterion[81 + clo * 9 + map[row][clo] - 1] = false;
//	criterion[162 + (getblock(row + 1, clo + 1) - 1) * 9 + map[row][clo] - 1] = false;
//}

void SolveSudoku::removeA(int * criterion, int row, int clo, int value)           //填入数独后对限制条件进行更新
{
	criterion[0 + row - 1] = criterion[row - 1] & (~encode[value - 1]);
	criterion[9 + clo - 1] = criterion[9 + clo - 1] & (~encode[value - 1]);
	criterion[18 + (getblock(row, clo) - 1)] = criterion[18 + (getblock(row, clo) - 1)] & (~encode[value - 1]);
}  

void SolveSudoku::recoverA(int * criterion, int row, int clo, int value)          //恢复限制条件
{
	criterion[0 + row - 1] = criterion[row - 1] | (encode[value - 1]);
	criterion[9 + clo - 1] = criterion[9 + clo - 1] | (encode[value - 1]);
	criterion[18 + (getblock(row, clo) - 1)] = criterion[18 + (getblock(row, clo) - 1)] | (encode[value - 1]);
}    

//bool SolveSudoku::dealingA()
//{
//	//std::cout << ++pile << '\n';
//	int i, minValue, minPos;
//	bool state = false;
//	if (right[0] == 0) {
//		return true;
//	}
//	minValue = number[right[0]];
//	minPos = right[0];
//	for (i = right[0]; i != 0; i = right[i]) {
//		if (number[i] < minValue) {
//			minValue = number[i];
//			minPos = i;
//		}
//	}
//	//std::cout << "finish\n";
//	for (i = down[minPos]; i != minPos; i = down[i]) {
//		remove(i);
//		map[rowValue[i] - 1][colValue[i] - 1] = fillValue[i];
//		//std::cout << rowValue[i] << ' ' << colValue[i] << ' ' << fillValue[i] << '\n';
//		state = dealingA();
//		if (state) break;
//		recover(i);
//	}
//	return state;
//}

bool SolveSudoku::dealingB(int* criterion, int i, int j)       //数独求解的回溯函数
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

bool SolveSudoku::fill(int row, int clo, int value, int* criterion)               //判断数独某个位置是否能够填写数字
{
	int temp = criterion[row - 1] & criterion[9 + clo - 1] & criterion[18 + (getblock(row, clo) - 1)] & encode[value - 1];
	if (temp != 0) {
		return true;
	}
	return false;
}

//void SolveSudoku::remove(int p)
//{
//	int row, col, temp;
//	col = p;
//	do {
//		left[right[targetCol[col]]] = left[targetCol[col]];
//		right[left[targetCol[col]]] = right[targetCol[col]];
//		row = down[col];
//		while (row != col)
//		{
//			if (row != targetCol[col]) {
//				temp = right[row];
//				while (temp != row) {
//					down[up[temp]] = down[temp];
//					up[down[temp]] = up[temp];
//					number[targetCol[temp]]--;
//					temp = right[temp];
//				}
//			}
//			row = down[row];
//		}
//		col = right[col];
//	} while (col != p);
//	return;
//}
//
//void SolveSudoku::recover(int p)
//{
//	int row, col, temp;
//	col = p;
//	do {
//		left[right[targetCol[col]]] = targetCol[col];
//		right[left[targetCol[col]]] = targetCol[col];
//		row = down[col];
//		while (row != col)
//		{
//			if (row != targetCol[col]) {
//				temp = right[row];
//				while (temp != row) {
//					down[up[temp]] = temp;
//					up[down[temp]] = temp;
//					number[targetCol[temp]]++;
//					temp = right[temp];
//				}
//			}
//			row = down[row];
//		}
//		col = right[col];
//	} while (col != p);
//	return;
//}

void SolveSudoku::toCache(int nowNumber, int &result)     //将数独写入char*最后输出
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

void SolveSudoku::rewrite(std::string path)   //输出
{
	
	std::ofstream file;
	file.open(".\\sudoku.txt", std::ios::trunc | std::ios::out);
	file << cache;
	file.close();
	return;
}

char * SolveSudoku::getData()   //单元测试用
{
	return cache;
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
//	for (i = 0; i < 9; i++) {              //判定标准初始化
//		for (j = 0; j < 9; j++) {
//			col[i][j] = true;
//			row[i][j] = true;
//			block[i][j] = true;
//		}
//	}
//	for (i = 0; i < 9; i++) {               //数独map初始化，对空格取值加入限制
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
//	for (i = 324; i >= 1; i--) { //dancing link 辅助元素初始化完成
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
//	for (i = 0; i < 9; i++) {         //dancing link 构建
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

//void SolveSudoku::createNode(int row, int col, int value)     //行列从1开始的实际值
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