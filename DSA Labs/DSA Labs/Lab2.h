/*
File:			Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::vector class
Notes:			Property of Full Sail University 2305
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/

// Main toggle
#define LAB_2	1

// Individual unit test toggles
#define LAB2_PALINDROME_NUMBER		1
#define LAB2_FILL_FILE				1
#define LAB2_FILL_ARRAY				1
#define LAB2_CLEAR					1
#define LAB2_SORT_ASCENDING			1
#define LAB2_SORT_DESCENDING		1
#define LAB2_BRACKETS				1
#define LAB2_CONTAINS_TRUE			1
#define LAB2_CONTAINS_FALSE			1
#define LAB2_MOVE_PALINDROMES		1

/************/
/* Includes */
/************/
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

// Checks to see if a number is a palindrome (reads the same forwards and backwards)
//		An example of a palindrome word would be "racecar"
//
// In: _num			The number to check
//
// Return: True, if the number is a palindrome number
inline bool IsPalindromeNumber(unsigned int _num) {
	// TODO: Implement this function	

	bool palindrome;
	std::string charNumber;
	charNumber = std::to_string(_num);
	std::reverse(charNumber.begin(), charNumber.end());

	if (std::stoi(charNumber) == _num)
	{
		palindrome = true;
	}
	else
	{
		palindrome = false;
	}

	return palindrome;
}

class DSA_Lab2
{
	friend class UnitTests_Lab2;	// Giving access to test code

private:

	std::vector<int> mValues;		// contains all of the values
	std::vector<int> mPalindromes;	// contains just the numbers that are palindromes (only used in MovePalindromes method)

public:

	// Fill out the mValues vector with the contents of the binary file
	//		First four bytes of the file are the number of ints in the file
	//
	// In:	_input		Name of the file to open
	void Fill(const char* _input) {
		// TODO: Implement this method

		std::ifstream fIn(_input, std::ios::binary);
		int currentValue = 0;
		int numOfInts = 0;

		fIn.read((char*)&numOfInts, sizeof(int));

		while (true) {
			fIn.read((char*)&currentValue, sizeof(int));

			if (fIn.eof())
				break;

			mValues.push_back(currentValue);
		}

		fIn.close();
	}

	// Fill out the mValues vector with the contents of an array
	//
	// In:	_arr			The array of values
	//		_size			The number of elements in the array
	void Fill(const int* _arr, size_t _size) {
		// TODO: Implement this method

		for (size_t i = 0; i < _size; i++)
		{
			mValues.push_back(_arr[i]);
		}
	}

	// Remove all elements from vector and decrease capacity to 0
	void Clear() {
		// TODO: Implement this method

		mValues.clear();
		mValues.shrink_to_fit();
	}

	// Sort the vector 
	//
	// In:	_ascending		To sort in ascending order or not
	//
	// NOTE: Use the std::sort method in this implementation
	void Sort(bool _ascending) {
		// TODO: Implement this method

		if (_ascending)
		{
			std::sort(mValues.begin(), mValues.end());
		}
		else
		{
			std::sort(mValues.begin(), mValues.end(), std::greater<int>());
		}
	}

	// Get an individual element from the mValues vector
	int operator[](int _index) {
		// TODO: Implement this method
		return mValues[_index];
	}

	// Determine if a value is present in the vector
	// 
	// In:	_val		The value to find
	//
	// Return: True, if the value is present
	bool Contains(int _val) const {
		// TODO: Implement this method
		bool contains = false;

		for (int i = 0; i < mValues.size(); i++)
		{
			if (mValues[i] == _val)
			{
				contains = true;
				break;
			}
			else
			{
				contains = false;
			}
		}

		return contains;
	}

	// Move all palindrome numbers from mValues vector to mPalindromes vector
	//
	// Pseudocode:
	//		iterate through the main values vector
	//			if the value is a palindrome
	//				add it to the palindrome vector
	//				remove it from the values vector
	void MovePalindromes() {
		// TODO: Implement this method

		for (std::vector<int>::iterator iter = mValues.begin(); iter != mValues.end(); ) {
			if (IsPalindromeNumber(*iter))
			{
				mPalindromes.push_back(*iter);
				iter = mValues.erase(iter);
			}
			else 
			{
				iter++;
			}
		}
	}
};

