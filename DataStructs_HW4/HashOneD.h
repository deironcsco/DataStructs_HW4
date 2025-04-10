#pragma once


const int SIZE = 500; // size of table

/*
* One dimensional hash table class
* utilizes linear probing when encountering collisions
* designed around testing collisions performance (most funcs return # of collisions)
*/

class HashOneD {
private:
	int table[SIZE]; // contains data
	bool is_empty_f[SIZE]; // indicates whether an entry in. true if empty, false if filled

	int Hash(int); // hashing function
	bool IsFull(); // to determine if table is full before we insert something
public:
	HashOneD(); // constructor
	~HashOneD(); // destructor
	int Insert(int); // insert, returns # collisions
	int Find(int); // find a value, returns # collisions
	int Remove(int); // remove a value, return # collisions
	void Print(); // prints all items, indicating which spots are emptyint 
	int GetVal(int); // for testing - gets value at given index
	bool GetFlag(int); // for testing - get is_empty_f value at given index
};


