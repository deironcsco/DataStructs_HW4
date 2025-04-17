
#include "HashExceptions.h"
#include "HashOneD.h"
#include <iostream>
#include <limits>

/*
constructor
initializes all values in table to 0, and all bools in is_empty_f to true
(meaning they are empty)
*/
HashOneD::HashOneD() {
  for (int i{0}; i < SIZE; i++) {
    table[i] = std::numeric_limits<int>::min();
    is_empty_f[i] = true;
  }
}

/*
destructor
doesn't really need to do anything special since we don't utilize pointers
*/
HashOneD::~HashOneD() = default;

/*
hashing function - get index for where to insert inval into table
*/
int HashOneD::Hash(int inval) { return inval % SIZE; }

/*
return true if table is full, false otherwise
*/
bool HashOneD::IsFull() {
  for (int i{0}; i < SIZE; i++) {
    if (is_empty_f[i]) { // returns false if at least one of the entries is
                         // empty
      return false;
    }
  }
  return true;
}

/*
Insert – accepts a value (integer), runs a hash function on the integer, and
places it in the hash table. This function should return the number of spots it
checks before inserting the item in the hash table so if it has no collisions,
it should return 1 and if it has 3 collisions and then finds a spot on the 4th
try, it return 4

input
        an integer to put into the table
process
        uses Hash() to find wehre to put integer, if collision it goes to the
next index until its empty...
        ...counts number of collisions (# spots moved)
output
        # collisions

cases
        add to beginning
        add to middle
        add to end
        add same value multiple times
        add diff values same has multiple times
        add same values multiple times, and add a value that would be in a spot
thats overflowed add two values next to each other, and insert first value again
*/
int HashOneD::Insert(int inval) {
  // check if table is full first
  if (IsFull()) {
    throw FullTableException();
  }

  int index{Hash(inval)}; // index of where to insert into array
  int num_coll{1}; // # collisions (initialized to 1 per lab instructions)

  // increment index (linear probing)
  while (table[index] != std::numeric_limits<int>::min()) {
    index = (index + 1) % SIZE;
    num_coll++;
  }

  // insert and change is_empty_f
  table[index] = inval;
  is_empty_f[index] = false;

  // return num collisions
  return num_coll;
}

/*
Find – accepts a value (integer), locates the value in the hash table and
returns the number of spots it checked to find the item or determine it is not
in the hash table. This uses the same procedure as Insert to determine number of
spots checked

input
        an integer
process
        loop through table until encounter true or value equivalent to inval
output
        # collisions

cases
        add integer, find it
        add integerx2, find it
        add integerx2, remove first, find it
*/
int HashOneD::Find(int inval) {
  // find index
  int index{Hash(inval)};
  int coll{1};

  // increment linearly
  while (table[index] != inval && is_empty_f[index] == false) {
    index = (index + 1) % SIZE;
    coll++;
  }

  // return collision
  return coll;
}

/*
Remove – accepts a value (integer), locates the value in the hash table and
removes it from the hash table. It returns the number of spots it checked to
find the item or determine it is not in the hash table. This uses the same
procedure as Insert to determine number of spots checked.

input
        int to remove
process
        loops through table until encounters input or encounters empty spot
output
        num collisions

cases
        insert val, remove that val
        insert mult vals, remove one, it's gone
        insert mult vals, remove all, they all gone
        insert val, remove, insert again, it's that val
        that's all i can come up with rn
*/
int HashOneD::Remove(int inval) {
  // get index
  int index{Hash(inval)};
  int colls{1}; // initialized to 1 per instructions

  // loop until find/not find
  // loop until it finds it or is empty f is true (meaning no values were added)
  while (!(table[index] == inval || is_empty_f[index] == true)) {
    index = (index + 1) % SIZE;
    colls++;
  }

  // if it's there, removes it
  if (table[index] == inval) {
    table[index] =
        std::numeric_limits<int>::min(); // some val that's pretty unlikely
  }
  // does not change is_empty_f because dupe values could still be after removed
  // value

  // return colls
  return colls;
}

/*
Print – prints all items in the hash table including an indication of which
spots are not occupied
*/
void HashOneD::Print() {
  for (int i{0}; i < SIZE; i++) {
    if (is_empty_f[i] != true) {
      std::cout << i << "-" << table[i] << " ";
    } else {
      std::cout << i << "-" << '.' << " ";
    }
    if (i % 20 == 0 && i != 0) {
      std::cout << '\n';
    }
  }
  std::cout << "\n";
}

// get table[inval]
int HashOneD::GetVal(int inval) { return table[inval]; }

// get is_empty_f[inval]
bool HashOneD::GetFlag(int inval) { return is_empty_f[inval]; }
