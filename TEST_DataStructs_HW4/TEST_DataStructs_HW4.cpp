#include "pch.h"
#include "CppUnitTest.h"
#include "../DataStructs_HW4/HashOneD.h" //import shit
#include "../DataStructs_HW4/HashOneD.cpp"
#include "../DataStructs_HW4/HashTwoD.h"
#include "../DataStructs_HW4/HashTwoD.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TEST_HashOneD
{
	TEST_CLASS(TEST_Insert)
	{
	public:
		
		//add to beginning
		TEST_METHOD(beginning)
		{
			HashOneD t;
			t.Insert(0);
			Assert::AreEqual(0, t.GetVal(0));
		}

		//add to middle
		TEST_METHOD(middle) 
		{
			HashOneD t;
			t.Insert(223);
			Assert::AreEqual(223, t.GetVal(223));
		}
		
		//add to end
		TEST_METHOD(end)
		{
			HashOneD t;
			t.Insert(499);
			Assert::AreEqual(499, t.GetVal(499));
		}

		//add same value multiple times
		TEST_METHOD(same_mult)
		{
			HashOneD t;
			t.Insert(501);
			t.Insert(501);
			t.Insert(501);
			Assert::AreEqual(501, t.GetVal(1));
			Assert::AreEqual(501, t.GetVal(2));
			Assert::AreEqual(501, t.GetVal(3));
		}
		
		//add diff values same has multiple times
		TEST_METHOD(diff_but_same_mult)
		{
			HashOneD t;
			t.Insert(501);
			t.Insert(1001);
			t.Insert(1501);
			Assert::AreEqual(501, t.GetVal(1));
			Assert::AreEqual(1001, t.GetVal(2));
			Assert::AreEqual(1501, t.GetVal(3));
		}
		
		//add same values multiple times, and add a value that would be in a spot thats overflowed
		TEST_METHOD(same_mult_and_overflow)
		{
			HashOneD t;
			t.Insert(513);
			t.Insert(513);
			t.Insert(513);
			t.Insert(514);

			Assert::AreEqual(513, t.GetVal(13));
			Assert::AreEqual(513, t.GetVal(14));
			Assert::AreEqual(513, t.GetVal(15));
			Assert::AreEqual(514, t.GetVal(16));
		}
		
		//add two values next to each other, and insert first value again
		TEST_METHOD(two_diff_then_first)
		{
			HashOneD t;
			t.Insert(1004);
			t.Insert(1005);
			t.Insert(1004);

			Assert::AreEqual(1004, t.GetVal(4));
			Assert::AreEqual(1005, t.GetVal(5));
			Assert::AreEqual(1004, t.GetVal(6));
		}
		
		// make sure it properly returns collisions
		TEST_METHOD(colls) 
		{
			HashOneD t;
			t.Insert(345);
			t.Insert(345);
			t.Insert(345);
			t.Insert(345);
			t.Insert(345);
			Assert::AreEqual(6, t.Insert(345));
		}
		
		//make sure invals wrap around properly
		TEST_METHOD(wrap_around) {
			HashOneD t;
			t.Insert(498);
			t.Insert(498);
			t.Insert(498);
			t.Insert(498);
			t.Insert(498);
			Assert::AreEqual(498, t.GetVal(0));
		}

	}; // TEST_Insert

	TEST_CLASS(TEST_Find)
	{
	public:

		// add integer, find it
		TEST_METHOD(one_int)
		{
			HashOneD t;
			t.Insert(375);
			Assert::AreEqual(1, t.Find(375));
		}

		// add integer mult times, find it
		TEST_METHOD(mult_ints) 
		{
			HashOneD t;
			t.Insert(373);
			t.Insert(373);
			t.Insert(374);
			Assert::AreEqual(2, t.Find(374));
		}

		// try to find a val thats not there
		TEST_METHOD(not_there) 
		{
			HashOneD t;
			t.Insert(473);
			t.Insert(473);
			Assert::AreEqual(2, t.Find(474));
		}

		// find - insert thing that loops over, remove all that are at end, find thing that wrapped around
		TEST_METHOD(wrap_around) 
		{
			HashOneD t;
			Assert::AreEqual(1, t.Insert(998));
			Assert::AreEqual(2, t.Insert(998));
			Assert::AreEqual(3, t.Insert(998));

			Assert::AreEqual(998, t.GetVal(0));

			Assert::AreEqual(1, t.Remove(998));
			Assert::AreEqual(2, t.Remove(998));

			Assert::AreEqual(3, t.Find(998));
		}

		// add something remove it, try to find it, should return 2 cols
		TEST_METHOD(remove_find)
		{
			HashOneD t;
			t.Insert(594);
			t.Remove(594);
			Assert::AreEqual(2, t.Find(594));
		}
		
		
		// add ints mult, remove 1+ , try to find remaining one
		TEST_METHOD(remov_find_mult) {
			HashOneD t;
			t.Insert(482);
			t.Insert(482);
			t.Insert(482);
			
			t.Remove(482);
			t.Remove(482);
			Assert::AreEqual(3, t.Find(482));
		}

	}; // TEST_Find



	TEST_CLASS(TEST_Remove) {
		//insert val, remove that val
		TEST_METHOD(insert_remove) 
		{
			HashOneD t;
			t.Insert(547);
			Assert::AreEqual(1, t.Remove(547));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(47));
		}
		
		//insert mult vals, remove one, it's gone
		TEST_METHOD(insert_mult_rem_one) 
		{
			HashOneD t;
			t.Insert(576);
			t.Insert(576);
			t.Insert(576);
			Assert::AreEqual(1, t.Remove(576));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(76));
		}

		// insert mult vals, remove all, they all gone
		TEST_METHOD(insert_mult_rem_all) 
		{
			HashOneD t;
			t.Insert(586);
			t.Insert(586);
			t.Insert(586);
			Assert::AreEqual(586, t.GetVal(86));
			Assert::AreEqual(586, t.GetVal(87));
			Assert::AreEqual(586, t.GetVal(88));

			Assert::AreEqual(1, t.Remove(586));
			Assert::AreEqual(2, t.Remove(586));
			Assert::AreEqual(3, t.Remove(586));

			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(86));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(87));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(87));
		}

		// insert val, remove, insert again, it's that val
		TEST_METHOD(insert_rem_ins) 
		{
			HashOneD t;
			t.Insert(681);
			Assert::AreEqual(1, t.Remove(681));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(181));
			
			//for testing
			int a = t.GetVal(181);
			bool b = t.GetFlag(181);
			
			t.Insert(681);
			Assert::AreEqual(681, t.GetVal(181));
		}

		// insert mult of another val, then one of a higher val, remove higher val
		TEST_METHOD(rem_higher) 
		{
			HashOneD t;
			t.Insert(584);
			t.Insert(584);
			t.Insert(584);
			t.Insert(585);
			t.Print();
			std::cout << "\n\n\n";
			Assert::AreEqual(3, t.Remove(585));
			t.Print();
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(87));
		}

		// insert things that loop over and remove them all
		TEST_METHOD(wrap_around) {
			HashOneD t;
			Assert::AreEqual(1, t.Insert(498));
			Assert::AreEqual(2, t.Insert(498));
			Assert::AreEqual(3, t.Insert(498));
			Assert::AreEqual(498, t.GetVal(0)); //ensure it wrapped around properly
			
			Assert::AreEqual(1, t.Remove(498));
			Assert::AreEqual(2, t.Remove(498));
			Assert::AreEqual(3, t.Remove(498));

			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(0));
		}
	}; // TEST_Remove
}



namespace TEST_HashTwoD
{
	TEST_CLASS(TEST_Insert) {
		
		// testing the full column exception
		// kinda included a bunch of other tests in here. this is all we need pretty much, right?
		TEST_METHOD(full_col)
		{
			HashTwoD t;

			Assert::AreEqual(1, t.Insert(101));
			Assert::AreEqual(2, t.Insert(201));
			Assert::AreEqual(3, t.Insert(301));
			Assert::AreEqual(4, t.Insert(401));
			Assert::AreEqual(5, t.Insert(501));

			//ensure those ^^^ spots have the right values
			Assert::AreEqual(101, t.GetVal(1, 0));
			Assert::AreEqual(201, t.GetVal(1, 1));
			Assert::AreEqual(301, t.GetVal(1, 2));
			Assert::AreEqual(401, t.GetVal(1, 3));
			Assert::AreEqual(501, t.GetVal(1, 4));

			int a{ 0 };
			try {
				t.Insert(601);
			}
			catch (FullColumnException) {
				a = 1;
			}
			Assert::AreEqual(1, a);
		}

	}; // TEST_Insert

	TEST_CLASS(TEST_Find) {
		
		//find first val
		TEST_METHOD(find_val) {
			HashTwoD t;
			t.Insert(432);
			Assert::AreEqual(1, t.Find(432));
		}

		//find a val that's deeper into column
		TEST_METHOD(find_val_mult) {
			HashTwoD t;
			t.Insert(543);
			t.Insert(743);
			t.Insert(643);
			t.Insert(343);
			Assert::AreEqual(4, t.Find(343));
		}

		//find a val that's not there
		TEST_METHOD(find_val_gone) {
			HashTwoD t;
			t.Insert(823);
			t.Insert(523);
			t.Insert(623);
			t.Insert(223);
			t.Insert(623);
			Assert::AreEqual(6, t.Find(23));
		}
		
		//find a val that's in an empty table
		TEST_METHOD(empty) {
			HashTwoD t;
			Assert::AreEqual(1, t.Find(4));
		}
	}; // TEST_Find

	TEST_CLASS(TEST_Remove)
	{
		//insert then remove
		TEST_METHOD(insert_remove)
		{
			HashTwoD t;
			t.Insert(543);
			Assert::AreEqual(1, t.Remove(543));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(43, 0));
		}

		//insert mult then remove one
		TEST_METHOD(insert_mult_remove)
		{
			HashTwoD t;
			t.Insert(634);
			t.Insert(634);
			t.Insert(634);

			//remove, test colls
			Assert::AreEqual(1, t.Remove(634));
			
			//test vals after
			Assert::AreEqual(634, t.GetVal(34, 0));
			Assert::AreEqual(634, t.GetVal(34, 1));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(34, 2));
		}

		//insert mult diff then remove a bottom one
		TEST_METHOD(insert_mult_remove_bottom)
		{
			HashTwoD t;

			t.Insert(463);
			t.Insert(563);
			t.Insert(763);
			t.Insert(863);
			t.Insert(263);

			Assert::AreEqual(5, t.Remove(263));

			//test make sure col isn't affected 
			Assert::AreEqual(463, t.GetVal(63, 0));
			Assert::AreEqual(563, t.GetVal(63, 1));
			Assert::AreEqual(763, t.GetVal(63, 2));
			Assert::AreEqual(863, t.GetVal(63, 3));
		}
		
		//insert mult diff, remove top
		TEST_METHOD(insert_mult_remove_top)
		{
			HashTwoD t;

			t.Insert(463);
			t.Insert(563);
			t.Insert(763);
			t.Insert(863);
			t.Insert(263);

			Assert::AreEqual(1, t.Remove(463));

			//test make sure col isn't affected 
			Assert::AreEqual(563, t.GetVal(63, 0));
			Assert::AreEqual(763, t.GetVal(63, 1));
			Assert::AreEqual(863, t.GetVal(63, 2));
			Assert::AreEqual(263, t.GetVal(63, 3));
		}

		//insert mult, remove middle, find one after
		
		TEST_METHOD(insert_rem_middle_find)
		{
			HashTwoD t;

			t.Insert(432);
			t.Insert(632);
			t.Insert(932);
			t.Insert(4332);

			//remove
			Assert::AreEqual(3, t.Remove(932));

			//make sure col moves up properly
			Assert::AreEqual(432, t.GetVal(32, 0));
			Assert::AreEqual(632, t.GetVal(32, 1));
			Assert::AreEqual(4332, t.GetVal(32, 2));

			//find
			Assert::AreEqual(3, t.Find(4332));
		}

		//insert, remove, insert again
		TEST_METHOD(insert_rem_insert)
		{
			HashTwoD t;

			t.Insert(842);
			
			//remove
			Assert::AreEqual(1, t.Remove(842));

			//check deleted
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(42, 0));

			//insert again
			t.Insert(942);

			//make sure it inserted properly
			Assert::AreEqual(942, t.GetVal(42, 0));

		}

		//insert all, remove all 
		TEST_METHOD(insert_all_rem_all)
		{
			HashTwoD t;

			t.Insert(523);
			t.Insert(823);
			t.Insert(223);
			t.Insert(423);
			t.Insert(1923);

			//remove
			Assert::AreEqual(1, t.Remove(523));
			Assert::AreEqual(1, t.Remove(823));
			Assert::AreEqual(1, t.Remove(223));
			Assert::AreEqual(1, t.Remove(423));
			Assert::AreEqual(1, t.Remove(1923));

			//ensure all are empty
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(23, 0));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(23, 1));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(23, 2));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(23, 3));
			Assert::AreEqual(std::numeric_limits<int>::min(), t.GetVal(23, 4));
		}
	}; //TEST_Remove

} //TEST_HashTwoD