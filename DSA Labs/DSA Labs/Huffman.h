/*
File:			Huffman.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A class to wrap up Huffman compression algorithm
Notes:			Property of Full Sail University 2305
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <queue>
#include "BitStream.h"
#include <fstream>

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
#define LAB_8	1

// Individual unit test toggles
#define HUFFMAN_CTOR					1
#define HUFFMAN_GENERATE_FREQUENCY		1
#define HUFFMAN_GENERATE_LEAFLIST		1
#define HUFFMAN_GENERATE_TREE			1
#define HUFFMAN_CLEAR_TREE				1
#define HUFFMAN_DTOR					1
#define HUFFMAN_GENERATE_ENCODING		1
#define HUFFMAN_COMPRESS				1
#define HUFFMAN_DECOMPRESS				1

// Wraps up Huffman compression algorithm
class Huffman {

	friend class UnitTests_Lab8; // Giving access to test code

	// A node for a a Huffman tree
	struct HuffNode {
		short value;		// The value to store (-1 if not a leaf node, 0-255 for the ascii value)
		unsigned int freq;	// The frequency of the node
		HuffNode* left;		// Left child
		HuffNode* right;	// Right child
		HuffNode* parent;	// Parent node

		// Constructor
		// 
		// In:	_value		The value of the node
		//		_freq		The frequency of the node
		//		_left		The node's left child (OPTIONAL)
		//		_right		The node's right child (OPTIONAL)
		//		_parent		The parent node (OPTIONAL)
		HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
			: value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
		}

		// Copy constructor
		//
		// In:	_hnode		The node to copy from
		HuffNode(const HuffNode& _hnode)
			: value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
		}
	};

	// A binary predicate used to compare HuffNodes
	//		This is used in the GenerateTree method
	struct HuffCompare {
		// Compare the frequency of two nodes
		// 
		// In:	_a		The first node
		//		_b		The second node
		//
		// Return: True, if _a's freq is greater than _b's freq
		bool operator() (const HuffNode* _a, const HuffNode* _b) {
			return(_a->freq > _b->freq);
		}
	};


	// Data members
	// NOTE: Values set to 1/-1 for unit test purposes
	std::string mFileName = "-1";						// The name of the file to open for read/write
	unsigned int mFrequencyTable[256] = { 1 };			// The frequency of each character in the file (the index in the array is the char's ASCII value)
	std::vector<HuffNode*> mLeafList;						// Contains all of the dynamically allocated leaf nodes
	HuffNode* mRoot = reinterpret_cast<HuffNode*>(-1);	// The root of the huffman tree (set in GenerateTree)
	std::vector<bool> mEncodingTable[256];					// Contains all of the bit-codes used to compress/decompress a file

	// Default constructor
	//
	// In:	_fileName		The name of the file to open
	Huffman(const std::string& _fileName) {
		// TODO:
		// 1. Assign the data members the values from the parameters

		// 2. Zero out the frequency table

		// 3. Set the root to null
		mFileName = _fileName;

		for (size_t i = 0; i < 256; i++)
		{
			mFrequencyTable[i] = 0;
		}
		mRoot = nullptr;
	}

	// Destructor
	//		Needs to clean up any left-over dynamic memory in tree
	~Huffman() {
		// TODO:
		// 1. Clear out the tree
		ClearTree();
	}


	// Generate the frequency table for the Huffman algorithm (WRITING ONLY)
	//
	// NOTE:	mFrequencyTable is an array of 256 unsigned ints representing the 
	//			count of each character in the file (the index in the array is the char's ASCII value)
	//				Example:  'A' is ASCII 65, so if A is the character being checked, [65] of your array would get incremented
	void GenerateFrequencyTable() {
		// TODO:
		// 1. Open the file in binary mode (using a standard ifstream)

		// 2. Read the file one byte at a time, and increment the corresponding index

		// 3. Close the file when complete

		unsigned char currIndex = 0;

		std::ifstream fIn(mFileName, std::ios::binary);

		while (true) {
			fIn.read((char*)&currIndex, sizeof(unsigned char));

			if (fIn.eof())
				break;

			mFrequencyTable[currIndex] = mFrequencyTable[currIndex] + 1;
		}

		fIn.close();
	}

	// Generate the leaf list for the Huffman algorithm (used in READ AND WRITE)
	//
	// Note:	Will cause leaks until ClearTree is implemented
	void GenerateLeafList() {
		// TODO:
		// 1. Iterate through the frequency table and dynamically create a leaf node for each non-0
		//		frequency. Add it to the mLeafList vector.

		for (int i = 0; i < 256; i++)
		{
			if (mFrequencyTable[i] != 0)
			{
				HuffNode* newNode = new HuffNode(i, mFrequencyTable[i]);
				mLeafList.push_back(newNode);
			}
		}
	}

	// Generate a Huffman tree
	void GenerateTree() {
		// TODO:
		// 1. Create the priority queue
		//              This will be storing HuffNode*'s
		//              in a vector, and will be using the HuffCompare for comparison

		// 2. Add in all data from your leaf list

		// 3. Enter the tree generation algorithm
		//              While the queue has more than 1 node
		//                      Store the top two nodes into some temporary pointers and pop them
		//                      Create a new parent node /w 1st node as left, and 2nd as right
		//                      Set the parent value to -1, and frequency to the sum of its children
		//                      Set the 1st and 2nd node's parent to the new node you created
		//                      Insert new node into queue

		// 4. Set the root of the tree (this will be the only node in the queue)

		std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffCompare> HuffPriority;

		for (int i = 0; i < mLeafList.size(); ++i) {
			HuffPriority.push(mLeafList[i]);
		}

		while (HuffPriority.size() > 1)
		{
			HuffNode* tempNode1 = HuffPriority.top();
			HuffPriority.pop();

			HuffNode* tempNode2 = HuffPriority.top();
			HuffPriority.pop();

			HuffNode* parentNode = new HuffNode(-1, tempNode1->freq + tempNode2->freq, tempNode1, tempNode2);
			tempNode1->parent = parentNode;
			tempNode2->parent = parentNode;

			HuffPriority.push(parentNode);
		}

		mRoot = HuffPriority.top();
	}

	// Generating the encoding table for the Huffman algorithm
	//
	//				Each vector will contain the bit-code corresponding to that index in the frequency table
	void GenerateEncodingTable() {
		// TODO:
		// 1. Go through all of the leaf nodes and generate the bit codes
		//		You will do this by traversing up the tree from the leaf node
		//			As you move up, push a 0 to the vector if you passed through a left child connection
		//			and a 1 if you passed through a right
		//			Once you hit the root node, reverse the values in the vector


		for (int i = 0; i < mLeafList.size(); i++)
		{
			HuffNode* tempNode = mLeafList[i];
			while (tempNode->parent != nullptr)
			{
				if (tempNode == tempNode->parent->left)
				{
					tempNode = tempNode->parent;
					mEncodingTable[mLeafList[i]->value].push_back(false);
				}
				else if (tempNode == tempNode->parent->right)
				{
					tempNode = tempNode->parent;
					mEncodingTable[mLeafList[i]->value].push_back(true);
				}
			}
		}

		for (int i = 0; i < 256; i++)
		{
			std::reverse(mEncodingTable[i].begin(), mEncodingTable[i].end());
		}


	}

	// Clear the tree of all dynamic memory (by using the helper function)
	void ClearTree() {
		// TODO:
		// 1. Call the helper function with the root and then set it back to null

		ClearTree(mRoot);
		mRoot = nullptr;
	}

	// Clear the tree of all dynamic memory (recursive helper function)
	// 
	// In:	_curr		The current node to clean up
	//
	// Note:	This will be a recursive function that does a post-order deletion
	void ClearTree(HuffNode* _curr) {
		// TODO:
		// 1. Implement this method

		if (_curr == nullptr)
		{
			return;
		}

		ClearTree(_curr->left);
		ClearTree(_curr->right);

		delete _curr;
	}

	// Write a Huffman compressed file to disk
	//
	// In:	_outputFile			Where to write the compressed data to
	//
	// Note: You will use most of your other functionality to complete this function
	void Compress(const char* _outputFile) {
		// TODO:
		// 1. Create the frequency table, leaf list, tree, and encoding table (in this order)

		// 2. Create a BitOfStream and supply it the huffman header

		// 3. Open the input file in binary mode with a standard ifstream

		// 4. Start the compression process.   (You can read the whole file into a buffer first if you want)
		//		For each byte in the original file, write out the bit-code from the encoding table

		GenerateFrequencyTable();
		GenerateLeafList();
		GenerateTree();
		GenerateEncodingTable();

		BitOfstream bitOut(_outputFile, (const char*)mFrequencyTable, sizeof(unsigned int) * 256);
		std::ifstream fIn(mFileName, std::ios::binary);

		size_t sizeOfFile = 0;

		fIn.seekg(0, std::ios::end);
		sizeOfFile = fIn.tellg();
		fIn.seekg(0, std::ios::beg);
		unsigned char* buffer = new unsigned char[sizeOfFile];
		fIn.read((char*)buffer, sizeOfFile);

		for (int i = 0; i < sizeOfFile; i++)
		{
			bitOut << mEncodingTable[(unsigned int)buffer[i]];
		}

		bitOut.Close();
		fIn.close();
		delete[] buffer;
	}

	// Decompress a huffman-compressed file
	//
	// In:	_outputFile		Where to write the uncompressed data to
	//
	// Note: The mFileName will be the compressed file
	void Decompress(const char* _outputFile) {
		// TODO:
		// 1. Create a BitIfStream and read the frequency table

		// 2. Create the leaf list and tree (in this order)

		// 3. Create a standard ofstream for output (binary mode)

		// 4. Create a bool to use for traversing down the list, and a char to store the character for writing

		// 5. Create a node pointer for use in traversing the list (start it at the top)

		// 6. Go through the compressed file one bit at a time, traversing through the tree
		//		When you get to a leaf node, write out the value, and go back to the root
		//	Note: Remember, there may be trailing 0's at the end of the file, so only loop the total frequency number of times

		// 7. Close the streams

		// 8. Clean up the dynamic memory by clearing the tree

		BitIfstream bitIn(mFileName.c_str(), (char*)mFrequencyTable, sizeof(unsigned int) * 256);
		std::ofstream fOut(_outputFile, std::ios::binary);
		int fileSize = 0;
		size_t encodeVecSize = 0;
		bool travelRoute = false;
		char currChar = ' ';
		
		GenerateLeafList();
		GenerateTree();

		HuffNode* startingNode = mRoot;

		for (int i = 0; i < 256; i++)
		{
			fileSize += mFrequencyTable[i];
		}


		for (int i = 0; i < fileSize; i++)
		{
			while (startingNode->left != nullptr && startingNode->right != nullptr)
			{
				bitIn >> travelRoute;

				if (travelRoute)
				{
					startingNode = startingNode->right;
				}
				else
				{
					startingNode = startingNode->left;
				}
			}

			currChar = startingNode->value;
			startingNode = mRoot;
			fOut << currChar;
		}


		bitIn.Close();
		fOut.close();
	}
};

