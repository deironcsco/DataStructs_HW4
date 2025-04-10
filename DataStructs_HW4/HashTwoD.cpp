
#include "HashTwoD.h"
#include "iostream"
#include "HashExceptions.h"

// constructor
// initialize table
HashTwoD::HashTwoD() {
	for (int i{ 0 }; i < SIZE_2D; i++) {
		for (int j{ 0 }; j < DEPTH; j++) {
			table[i][j] = std::numeric_limits<int>::min();
		}
	}
}

// destructor
// can be default because we don't really mess with pointers
HashTwoD::~HashTwoD() = default;


// hash func
// returns hash value of input
int HashTwoD::Hash(int inval) {
	return inval % SIZE_2D;
}

// full column
// helper func, true if column is full at an index at table
bool HashTwoD::FullColumn(int index) {

	for (int i{ 0 }; i < DEPTH; i++) {
		//if at least one entry is min, return false
		if (table[index][i] == std::numeric_limits<int>::min()) {
			return false;
		}
	}
	return true;
}

/*
insert value into hash table
if there's a val there already, go down a row and add it there

input
	int
process
	if full column throw FullColumnException
	otherwise loop through column to insert (incrementing colls in the process)
output
	# collisions

cases
	testing the exception
	bunch of inserts that should have same index
	same testing as for insert in hashoned
*/
int HashTwoD::Insert(int inval) {
	// get index
	int index{ Hash(inval) };
	
	// if column is full, throw exception
	if (FullColumn(index)) {
		throw FullColumnException();
	}
	 
	// loop through depth while there's something there, get collisions
	int colls{ 1 };
	int curr_depth{ 0 };
	// keep incrementing while the cell is not 'empty'
	while (table[index][curr_depth] != std::numeric_limits<int>::min()) {
		curr_depth++;
		colls++;
	}

	// insert
	table[index][curr_depth] = inval;

	// return collisions
	return colls;
}

/*
find func, finds a value but returns collisions

inputs
	an integer
process
	just loops through column until it finds or or depth reaches 5
outputs
	# collisions

cases
	find first val
	find a val that's deeper into column
	find a val that's not there
	find a val that's in an empty table
*/
int HashTwoD::Find(int inval) {

	// set index
	int index{ Hash(inval) };
	int colls{ 1 };

	// loop through column until encounter inval or depth > 5 or encounter min
	int curr_depth{ 0 };
	while ((table[index][curr_depth] != inval) && 
		(table[index][curr_depth] != std::numeric_limits<int>::min()) && (curr_depth < DEPTH)) {
		curr_depth++;
		colls++;
	}

	// return collisions
	return colls;
}

/*
remove a value from the table
(first occurence of that value)

input
	an integer
process
	loops through column to see if integer if there
	if its there it replaces it with lowest int, moves bottom entries up
	else it ignores it
output
	returns col

cases
	insert then remove
	insert mult then remove one
	insert mult diff then remove a bottom one 
	insert mult, remove middle, find one after
	insert, remove, insert again
	insert all, remove all (bottom up?)
*/
int HashTwoD::Remove(int inval) {
	// find index
	int index{ Hash(inval) };
	int colls{ 1 };

	// find the value
	// loop through the column until encounter it, encounter a min, or curr depth >= DEPTH
	int curr_depth{ 0 };
	while (table[index][curr_depth] != inval && 
		table[index][curr_depth] != std::numeric_limits<int>::min() && curr_depth < DEPTH) {

		curr_depth++;
		colls++;
	}

	// if curr is the value we're looking for, then move all entries below it up
	if (table[index][curr_depth] == inval) {
		// while next depth isn't the end and next entry is filled
		while ((curr_depth + 1 < DEPTH) && (table[index][curr_depth] != std::numeric_limits<int>::min())) {
			// replace curr with curr+1 and increment curr
			table[index][curr_depth] = table[index][curr_depth + 1];
			curr_depth++;
		}
		// replace bottom value with min
		table[index][curr_depth] = std::numeric_limits<int>::min();
	}

	// return colls
	return colls;
}

// print func
// just prints the table to the console
void HashTwoD::Print() {
	for (int i{ 0 }; i < SIZE_2D; i++) {
		std::cout << i << "\t";
		for (int j{ 0 }; j < DEPTH; j++) {
			if (table[i][j] != std::numeric_limits<int>::min()) {
				std::cout << j << "-" << table[i][j] << "\t";
			}
			else {
				std::cout << j << "-.\t";
			}
		}
		std::cout << "\n";
	}
}

// get val func
// for testing, just returns an item in the table
int HashTwoD::GetVal(int index, int depth) {
	return table[index][depth];
}