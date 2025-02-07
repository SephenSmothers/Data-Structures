/*
File:			DList.h\
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A doubly-linked list (similar to std::list)
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
#define LAB_3	1

// Individual unit test toggles			
#define LAB3_CTOR						1
#define LAB3_NODE_CTOR_DEFAULT			1
#define LAB3_NODE_CTOR					1
#define LAB3_ADDHEAD_EMPTY				1
#define LAB3_ADDHEAD					1
#define LAB3_ADDTAIL_EMPTY				1
#define LAB3_ADDTAIL					1
#define LAB3_CLEAR						1
#define LAB3_DTOR						1
#define LAB3_ITER_BEGIN					1
#define LAB3_ITER_END					1
#define LAB3_ITER_INCREMENT_PRE			1
#define LAB3_ITER_INCREMENT_POST		1
#define LAB3_ITER_DECREMENT_PRE			1
#define LAB3_ITER_DECREMENT_POST		1
#define LAB3_ITER_DEREFERENCE			1
#define LAB3_INSERT_EMPTY				1
#define LAB3_INSERT_HEAD				1
#define LAB3_INSERT_MIDDLE				1
#define LAB3_ERASE_EMPTY				1
#define LAB3_ERASE_HEAD					1
#define LAB3_ERASE_TAIL					1
#define LAB3_ERASE_MIDDLE				1
#define LAB3_ASSIGNMENT_OP				1
#define LAB3_COPY_CTOR					1

template<typename Type>
class DList {

	friend class UnitTests_Lab3;	// Giving access to test code

	struct Node {
		// NOTE: Values set to -1 for unit test purposes
		Type data;
		Node* next = reinterpret_cast<Node*>(-1);
		Node* prev = reinterpret_cast<Node*>(-1);

		// Constructor
		//		Creates and fills out a node
		//
		// In:	_data	The value to store
		//		_next	The address of the next node
		//		_prev	The address of the prev node
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) {
			// TODO: Implement this method
			data = _data;
			next = _next;
			prev = _prev;
		}
	};

public:

	class Iterator {
	public:

		Node* mCurr = reinterpret_cast<Node*>(-1);

		// Pre-fix increment operator
		//
		// Return: Invoking object with curr pointing to next node
		// 
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
							I
							R
		*/
		Iterator& operator++() {
			// TODO: Implement this method
			this->mCurr = this->mCurr->next;

			return *this;
		}

		// Post-fix increment operator
		//
		// In:	(unused)		Post-fix operators take in an unused int, so that the compiler can differentiate
		//
		// Return:	An iterator that has its curr pointing to the "old" curr
		// NOTE:	Will need a temporary iterator 
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
					  R		I

		*/
		Iterator operator++(int) {
			// TODO: Implement this method
			Iterator temp;
			temp.mCurr = mCurr;
			mCurr = mCurr->next;
			return temp;
		}

		// Pre-fix decrement operator
		//
		// Return: Invoking object with curr pointing to previous node
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
				I
				R
		*/
		Iterator& operator--() {
			// TODO: Implement this method
			this->mCurr = this->mCurr->prev;

			return *this;
		}

		// Post-fix decrement operator
		//
		// In:	(unused)		Post-fix operators take in an unused int, so that the compiler can differentiate
		//
		// Return:	An iterator that has its curr pointing to the "old" curr
		// NOTE:	Will need a temporary iterator 
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
				I	  R

		*/
		Iterator operator--(int) {
			// TODO: Implement this method
			Iterator temp;
			temp.mCurr = mCurr;
			mCurr = mCurr->prev;
			return temp;
		}

		// Dereference operator
		//
		// Return: The data the curr is pointing to
		Type& operator*() {
			// TODO: Implement this method
			return this->mCurr->data;
		}

		// Not-equal operator (used for testing)
		// 
		// In:	_iter		The iterator to compare against
		//
		// Return: True, if the iterators are not pointing to the same node
		bool operator != (const Iterator& _iter) const {
			return mCurr != _iter.mCurr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mHead = reinterpret_cast<Node*>(-1);
	Node* mTail = reinterpret_cast<Node*>(-1);
	size_t mSize = -1;

public:

	// Default constructor
	//		Creates a new empty linked list
	DList() {
		// TODO: Implement this method
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
	}

	// Destructor
	//		Cleans up all dynamically allocated memory
	~DList() {
		// TODO: Implement this method
		Clear();
	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_copy			The object to copy from
	DList(const DList& _copy)  {
		// TODO: Implement this method

		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;

		AddHead(_copy.mHead->data);
		Iterator iter;
		iter.mCurr = _copy.mHead;

		for (int i = 0; i < _copy.mSize - 1; i++)
		{
			iter++;
			AddTail(iter.mCurr->data);
		}

		//* this = _copy;
	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_assign			The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	DList& operator=(const DList& _assign) {
		// TODO: Implement this method

		if (this != &_assign)
		{
			Clear();
			AddHead(_assign.mHead->data);
			Iterator iter;
			iter.mCurr = _assign.mHead;

			for ( int i = 0; i < _assign.mSize - 1; i++)
			{
				iter++;
				AddTail(iter.mCurr->data);
			}
		}

		return *this;
	}

private:
	// Optional recursive helper method for use with Rule of 3
	//
	// In:	_curr		The current Node to copy
	void RecursiveCopy(const Node* _curr) {
		// TODO (optional): Implement this method

	}

public:
	// Add a piece of data to the front of the list
	//
	// In:	_data			The object to add to the list
	void AddHead(const Type& _data) {
		// TODO: Implement this method
		Node* newHead = new Node(_data);

		if (mHead == nullptr)
		{
			mHead = newHead;
			mTail = newHead;
			++mSize;
		}
		else //if (mHead != nullptr)
		{
			newHead->next = mHead;
			mHead->prev = newHead;
			mHead = newHead;
			++mSize;
		}
		
	}

	// Add a piece of data to the end of the list
	//
	// In:	_data			The object to add to the list
	void AddTail(const Type& _data) {
		// TODO: Implement this method

		Node* newTail = new Node(_data);
		
		if (mTail == nullptr)
		{
			mHead = newTail;
			mTail = newTail;
			++mSize;
		}
		else //if (mHead != nullptr)
		{
			newTail->prev = mTail;
			mTail->next = newTail;
			mTail = newTail;

			++mSize;
		}
	}

	// Clear the list of all dynamic memory
	//			Resets the list to its default state
	void Clear() {
		// TODO: Implement this method

		if (mHead != nullptr)
		{
			while (mHead != nullptr)
			{
				Node* temp = mHead;
				mHead = mHead->next;
				delete temp;
			}
		}

		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
	}

private:
	// Optional recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	void RecursiveClear(const Node* _curr) {
		// TODO (Optional): Implement this method

	}

public:

	// Insert a piece of data *before* the passed-in iterator
	//
	// In:	_iter		The iterator
	//		_data		The value to add
	//
	// Example:
	/*
		Before

			0<-[4]<->[5]<->[6]->0
					  I

		After

			0<-[4]<->[9]<->[5]<->[6]->0
					  I
	*/
	// Return:	The iterator
	// SPECIAL CASE:	Inserting at head or empty list
	// NOTE:	The iterator should now be pointing to the new node created
	Iterator Insert(Iterator& _iter, const Type& _data) {
		// Implement this method
		
		if (mHead == nullptr || _iter.mCurr->prev == nullptr)
		{
			AddHead(_data);
			_iter.mCurr = mHead;
		}
		else
		{
			Node* node = new Node(_data);

			_iter.mCurr->prev->next = node;
			node->prev = _iter.mCurr->prev;
			node->next = _iter.mCurr;
			_iter.mCurr->prev = node;
			_iter.mCurr = node;

			mSize++;
		}

		return _iter;
	}

	// Erase a Node from the list
	//
	// In:	_iter		The iterator
	//
	// Example
	/*

		Before

			0<-[4]<->[5]<->[6]->0
					  I

		After

			0<-[4]<->[6]->0
					  I
	*/
	// Return:	The iterator
	// SPECIAL CASE:	Erasing head or tail
	// NOTE:	The iterator should now be pointing at the node after the one erased
	Iterator Erase(Iterator& _iter) {
		// TODO: Implement this method
		
		if (mHead == nullptr)
		{
			return _iter;
		}
		else if (_iter.mCurr->prev == nullptr)
		{
			_iter.mCurr = mHead->next;
			_iter.mCurr->next = mHead->next->next;
			_iter.mCurr->next->prev = _iter.mCurr;
			delete mHead;
			mHead = _iter.mCurr;
			mHead->next = _iter.mCurr->next;
			mHead->prev = nullptr;
			mSize--;
		}
		else if (_iter.mCurr->next == nullptr)
		{
			_iter.mCurr = mTail->prev;
			_iter.mCurr->prev = mTail->prev->prev;
			_iter.mCurr->prev->next = _iter.mCurr;
			delete mTail;
			mTail = _iter.mCurr;
			mTail->next = nullptr;
			mTail->prev = _iter.mCurr->prev;
			_iter.mCurr = nullptr;
			mSize--;
		}
		else
		{
			Node* tempNode = _iter.mCurr;

			_iter.mCurr->prev->next = _iter.mCurr->next;
			_iter.mCurr->next->prev = _iter.mCurr->prev;
			_iter.mCurr = _iter.mCurr->next;

			delete tempNode;
			

			mSize--;
		}

		return _iter;
	}

	// Set an Iterator at the front of the list
	// 
	// Return: An iterator that has its curr pointing to the list's head
	Iterator Begin() const {
		// TODO: Implement this method
		Iterator begin;
		begin.mCurr = mHead;
		return begin;
	}

	// Set an Iterator pointing to the end of the list
	// 
	// Return: An iterator that has its curr pointing to a null pointer
	Iterator End() const {
		// TODO: Implement this method
		Iterator end;
		end.mCurr = nullptr;
		return end;
	}
};