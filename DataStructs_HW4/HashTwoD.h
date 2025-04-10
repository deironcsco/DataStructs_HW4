#pragma once

const int SIZE_2D = 100;
const int DEPTH = 5;

class HashTwoD {
private:
	int table[SIZE_2D][DEPTH];
	int Hash(int);
	bool FullColumn(int);
public:
	HashTwoD();
	~HashTwoD();
	int Insert(int);
	int Find(int);
	int Remove(int);
	
	//helper/testing funcs
	void Print();
	int GetVal(int, int);
};