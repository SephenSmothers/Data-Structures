/*
File:			UnitTestHelper.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		08.15.2021
Last Modified:	10.20.2021
Purpose:		Declarations of global functions used in all unit tests
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

/************/
/* Includes */
/************/
#include <iostream>
#include <fstream>
#include <chrono>
#include "Console.h"
#include "UnitTestHelper.h"

// Random number generator
extern std::mt19937 rng((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());

// Generate a random int type value
int RandomInt(int _min, int _max) {
	return std::uniform_int_distribution<int>(_min, _max)(rng);
}

// Generate a random float type value
float RandomFloat(float _min, float _max) {
	return std::uniform_real_distribution<float>(_min, _max)(rng);
}

// Creates a dynamic array of random values
// 
// In:	_numElements		The number of elements to allocate
//		_min				Minimum value for element
//		_max				Maximum value for element
//
// Return: A dynamically allocated array
int* CreateRandomArray(size_t _numElements, int _min, int _max) {
	int* randomVals = new int[_numElements];
	for (size_t i = 0; i < _numElements; ++i)
		randomVals[i] = std::uniform_int<>(_min, _max)(rng);

	return randomVals;
}

// Create a duplicate of a file
//		Used so that the original file does not get corrupted
//
// In:	_srcFile		The file to duplicate
//		_dstFileName	The name for the duplicated file
void CreateDuplicateFile(const char* _srcFile, const char* _dstFileName) {
	std::ifstream ifl(_srcFile, std::ios::binary);
	std::ofstream ofl(_dstFileName, std::ios::binary);

	if (!ifl.is_open())
		std::cout << _srcFile << " did not open correctly\n";

	ofl << ifl.rdbuf();

	ifl.close();
	ofl.close();
}

// Remove whitepspace from a string (in-place)
// In:	_str			String to remove whitespace from
void RemoveWhiteSpace(std::string& _str) {
	_str.erase(std::remove(_str.begin(), _str.end(), ' '), _str.end());
	_str.erase(std::remove(_str.begin(), _str.end(), '\t'), _str.end());

}


// Check to see if a file contains a particular line of code
//
// In:	_srcFile		The file to open
//		_searchStart	The area of the file to start searching from
//		_searchStop		The area of the file to stop searching
//		_searchCriteria	The code to search for
//
// Return: True, if the searchCriteria is found
bool SearchFile(const char* _srcFile, const std::string& _searchStart,
	const std::string& _searchStop, const std::string& _searchCriteria) {
	std::ifstream ifl(_srcFile);
	
	std::string currLine;
	std::string searchCriteria = _searchCriteria;
	std::string searchStart = _searchStart;
	std::string searchStop = _searchStop;
	// Remove all whitespace from search criteria
	RemoveWhiteSpace(searchCriteria);
	RemoveWhiteSpace(searchStart);
	RemoveWhiteSpace(searchStop);

	

	bool criteriaFound = false;
	bool multiLineComment = false;

	// Read and ignore until searchStart
	for (;;) {
		std::getline(ifl, currLine);
		RemoveWhiteSpace(currLine);
		if (currLine.find(searchStart) != std::string::npos)
			break;
	}

	// In search area now, so look for criteria
	for (;;) {
		std::getline(ifl, currLine);
		// Remove all whitespace from line
		RemoveWhiteSpace(currLine);

		// Checking to see if line is comment and ignoring
		if (currLine.find("//") == 0)
			continue;

		if (currLine.find("/*") != std::string::npos) {
			multiLineComment = true;
			continue;
		}

		if (currLine.find("*/") != std::string::npos) {
			multiLineComment = false;
			continue;
		}

		if (multiLineComment)
			continue;

		if (currLine.find(searchCriteria) != std::string::npos) {
			criteriaFound = true;
			break;
		}
		if (ifl.eof() || currLine.find(searchStop) != std::string::npos)
			break;
	}
	ifl.close();

	return criteriaFound;
}


// Used to print out PASS/FAIL messages
//
// In:	_msg		The string to print (reason for failure)
//		_success	Deteremines the PASS/FAIL result
//		_deduction	The points deducted for failing this test
void PrintMessage(const char* _msg, int _deduction) {

#ifdef _WIN32
	System::Console::ForegroundColor(System::ConsoleColor::Red);
	std::cout << "FAIL";
	System::Console::ForegroundColor(System::ConsoleColor::Gray);
#else
	std::cout << "FAIL";
#endif
	std::cout << " - " << _msg << " (-" << _deduction << ")\n";
}

void PrintMessage() {
#ifdef _WIN32
	System::Console::ForegroundColor(System::ConsoleColor::Green);
	std::cout << "PASS\n";
	System::Console::ForegroundColor(System::ConsoleColor::Gray);
#else
	std::cout << "PASS";
#endif
}

// Print out UNKNOWN error message for neither pass or fail
void PrintUnknownMessage() {
#ifdef _WIN32
	System::Console::ForegroundColor(System::ConsoleColor::Yellow);
	std::cout << "UNKNOWN";
	System::Console::ForegroundColor(System::ConsoleColor::Gray);
#else
	std::cout << "UNKNOWN";
#endif
	std::cout << " - " << "Double-check method and contact instructor\n";
}

// Print out score for lab
void PrintTotalScore(int _totalScore) {
	std::cout << "\nTotal score (not counting deductions for warnings): " << _totalScore << "/100\n";
}

// Calculate the score for a single unit test (caps at 0)
// In:	_maxPoints	Maximum amount of points
//		_deductions	Points lost due to failing tests
//
// Return: The total score for the test
int CalculatePointsForTest(int _maxPoints, int _deductions) {
	int total = _maxPoints - _deductions;
	if (total < 0)
		total = 0;

	return total;
}

// Perform a battery of unit tests
//
// In:	_msg		The message to display (the name of the unit test)
//		_maxPoints	The maximum amount of points achievable for the test
//		_failTests	vector containing all of the subtests for failure
//		_passTests	vector containing all of the subtests for passing
// 
// Return: The total deductions of all fails
int UnitTestBattery(const char* _msg, int _maxPoints, FailVector& _failTests, PassVector& _passTests) {
	std::cout << _msg << " (" << _maxPoints << " points)\n";

	bool fail = false;

	FailResult result;
	int totalDeductions = 0;

	// Run all the fails first
	for (auto test : _failTests) {
		result = test();
		if (!fail && FAIL == result.check)
			fail = true;
		if (result.check) {
			PrintMessage(result.msg.c_str(), result.deduction);
			totalDeductions += result.deduction;
		}
	}

	// Only check pass tests if no failures
	int numPass = 0;
	if (!fail) {
		for (auto test : _passTests) {
			if (PASS == test())
				numPass++;
		}
	}

	if (_passTests.size() == numPass)
		PrintMessage();
	else if (_passTests.size() != numPass && !fail) {
		PrintUnknownMessage();
		totalDeductions = _maxPoints;
	}

	return totalDeductions;
}