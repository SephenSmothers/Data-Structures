/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A binary search tree
Notes:			Property of Full Sail University 2305
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

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
#define LAB_7	1

// Individual unit test toggles
#define BST_CTOR								1
#define BST_NODE_CTOR							1 
#define BST_PUSH_EMPTY							1
#define BST_PUSH_LEFT							1
#define BST_PUSH_RIGHT							1
#define BST_CLEAR								1
#define BST_DTOR								1
#define BST_CONTAINS_FOUND						1
#define BST_CONTAINS_NOTFOUND					1
#define BST_REMOVE_CASE0_ROOT					1
#define BST_REMOVE_CASE0_LEFT					1
#define BST_REMOVE_CASE0_RIGHT					1
#define BST_REMOVE_CASE1_ROOT_LEFT				1
#define BST_REMOVE_CASE1_ROOT_RIGHT				1
#define BST_REMOVE_CASE1_LEFT_LEFT				1
#define BST_REMOVE_CASE1_LEFT_RIGHT				1
#define BST_REMOVE_CASE1_RIGHT_LEFT				1
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1
#define BST_REMOVE_CASE2_CASE0					1
#define BST_REMOVE_CASE2_CASE1					1
#define BST_REMOVE_CASE0						1
#define BST_REMOVE_CASE1						1
#define BST_REMOVE_CASE2						1
#define BST_REMOVE_NOT_FOUND					1
#define BST_IN_ORDER_TRAVERSAL					1
#define BST_ASSIGNMENT_OP						1
#define BST_COPY_CTOR							1


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node {
		Type data;					// The value being stored
		Node* left, * right;		// The left and right nodes
		Node* parent;				// The parent node

		// Constructor
		//		Always creates a leaf node
		//
		// In:	_data		The value to store in this node
		//		_parent		The parent pointer (optional)
		Node(const Type& _data, Node* _parent = nullptr) {
			// TODO: Implement this method
			data = _data;
			left = nullptr;
			right = nullptr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	// The top-most Node in the tree

public:

	// Default constructor
	//			Always creates an empty tree
	BST() {
		// TODO: Implement this method
		mRoot = nullptr;
	}

	// Destructor
	//			Clear all dynamic memory
	~BST() {
		// TODO: Implement this method
		Clear();
	}

	// Copy constructor
		//			Used to initialize one object to another
		//
		// In:	_copy		The object to copy from
	BST(const BST& _copy) {
		// TODO: Implement this method

		this->mRoot = nullptr;
		Copy(_copy.mRoot);
	}

	// Assignment operator
	//			Used to assign one object to another
	//
	// In:	_assign		The object to assign from
	//
	// Return:	The invoking object (by reference)
	//		This allows us to daisy-chain
	BST& operator=(const BST& _assign) {
		// TODO: Implement this method

		if (this != &_assign)
		{
			Clear();
			Copy(_assign.mRoot);
		}

		return *this;
	}

private:
	// Recursive helper method for use with Rule of 3
	// 
	// In:	_curr		The current Node to copy
	//
	// NOTE:	Use pre-order traversal
	void Copy(const Node* _curr) {
		// TODO: Implement this method

		if (_curr == nullptr)
		{
			return;
		}

		Push(_curr->data);

		Copy(_curr->left);
		Copy(_curr->right);
	}

public:

	// Clears out the tree and readies it for re-use
	void Clear() {
		// TODO: Implement this method
		Clear(mRoot);
		mRoot = nullptr;
	}

private:

	// Recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	//
	// NOTE:	Use post-order traversal
	void Clear(Node* _curr) {
		// TODO: Implement this method

		if (_curr == nullptr)
		{
			return;
		}

		Clear(_curr->left);
		Clear(_curr->right);

		delete _curr;
	}

public:

	// Add a value into the tree
	//
	// In:	_val			The value to add
	void Push(const Type& _val) {
		// TODO: Implement this method
		Push(_val, mRoot);
	}

private:

	// Optional recursive helper method for use with Push
	//
	// In:	_val		The value to add
	//		_curr		The current Node being looked at
	void Push(const Type& _val, Node* _curr) {

		if (mRoot == nullptr)
		{
			mRoot = new Node(_val);
			mRoot->parent = nullptr;
			mRoot->left = nullptr;
			mRoot->right = nullptr;
		}
		else
		{
			if (_val < _curr->data)
			{
				if (_curr->left == nullptr)
				{
					Node* nodePtrL = new Node(_val);
					nodePtrL->left = nullptr;
					nodePtrL->right = nullptr;
					nodePtrL->parent = _curr;
					_curr->left = nodePtrL;
				}
				else
				{
					Push(_val, _curr->left);
				}
			}
			else
			{
				if (_curr->right == nullptr)
				{
					Node* nodePtrR = new Node(_val);
					nodePtrR->left = nullptr;
					nodePtrR->right = nullptr;
					nodePtrR->parent = _curr;
					_curr->right = nodePtrR;
				}
				else
				{
					Push(_val, _curr->right);
				}
			}
		}
	}

public:

	// Checks to see if a value is in the tree
	//
	// In:	_val		The value to search for
	//
	// Return:	True, if found
	bool Contains(const Type& _val) {
		// TODO: Implement this method

		Node* findNode = FindNode(_val);
		bool result = false;

		if (findNode != nullptr)
		{
			result = true;
		}
		return result;
	}

private:

	// Optional helper method for use with Contains and Remove methods
	//
	// In:	_val		The value to search for
	//
	// Return: The node containing _val (or nullptr if not found)
	Node* FindNode(const Type& _val) {
		Node* tempNode = mRoot;

		while (tempNode != nullptr)
		{
			if (_val == tempNode->data)
			{
				break;
			}
			else if (_val < tempNode->data)
			{
				tempNode = tempNode->left;
			}
			else
			{
				tempNode = tempNode->right;
			}
		}
		return tempNode;
	}

	// Remove a leaf node from the tree
	//		Case 0
	// 	   
	// In:	_node		The node to remove
	void RemoveCase0(Node* _node) {
		// TODO: Implement this method


		if (_node == mRoot)
		{
			delete _node;
			mRoot = nullptr;
		}
		else if (_node == _node->parent->left)
		{
			_node->parent->left = nullptr;
			delete _node;
		}
		else
		{
			_node->parent->right = nullptr;
			delete _node;
		}

	}

	// Remove a node from the tree that has only one child
	//		Case 1
	//
	// In:	_node		The node to remove
	void RemoveCase1(Node* _node) {
		// TODO: Implement this method

		if (_node == mRoot)
		{
			if (_node->left != nullptr && _node->right == nullptr)
			{
				mRoot = mRoot->left;
				mRoot->parent = nullptr;
				delete _node;
			}
			else if (_node->right != nullptr && _node->left == nullptr)
			{
				mRoot = mRoot->right;
				mRoot->parent = nullptr;
				delete _node;
			}
		}
		else if (_node == _node->parent->left)
		{
			if (_node->left != nullptr && _node->right == nullptr)
			{
				_node->parent->left = _node->left;
				_node->left->parent = _node->parent;
				delete _node;
			}
			else if (_node->right != nullptr && _node->left == nullptr)
			{
				_node->parent->left = _node->right;
				_node->right->parent = _node->parent;
				delete _node;
			}
		}
		else if (_node == _node->parent->right)
		{
			if (_node->left != nullptr && _node->right == nullptr)
			{
				_node->parent->right = _node->left;
				_node->left->parent = _node->parent;
				delete _node;
			}
			else if (_node->right != nullptr && _node->left == nullptr)
			{
				_node->parent->right = _node->right;
				_node->right->parent = _node->parent;
				delete _node;
			}
		}
	}

	// Remove a node from the tree that has both children
	//		Case 2
	//
	// In:	_node		The node to remove
	void RemoveCase2(Node* _node) {
		// TODO: Implement this method
		Node* min = _node;

		if (_node == mRoot)
		{
			min = _node->right;

			while (min->left != nullptr)
			{
				min = min->left;
			}

			_node->data = min->data;

			if (min->left == nullptr && min->right == nullptr)
			{
				RemoveCase0(min);
			}
			else
			{
				RemoveCase1(min);
			}
		}
		else
		{
			min = _node->right;

			while (min->left != nullptr)
			{
				min = min->left;
			}

			_node->data = min->data;

			if (min->left == nullptr && min->right == nullptr)
			{
				RemoveCase0(min);
			}
			else
			{
				RemoveCase1(min);
			}
		}
	}

public:

	// Removes a value from tree (first instance only)
	//
	// In:	_val			The value to search for
	//
	// Return:	True, if a Node was removed
	// NOTE:	Keep in mind the three cases
	//			A) 2 children ("fix" tree)
	//			B) 0 children
	//			C) 1 child
	bool Remove(const Type& _val) {
		// TODO: Implement this method

		bool isRemoved = false;
		Node* nodeToRemove = FindNode(_val);

		if (nodeToRemove == nullptr)
		{
			isRemoved = false;
		}
		else if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr)
		{
			isRemoved = true;
			RemoveCase0(nodeToRemove);
		}
		else if ((nodeToRemove->left != nullptr && nodeToRemove->right == nullptr) || (nodeToRemove->left == nullptr && nodeToRemove->right != nullptr))
		{
			isRemoved = true;
			RemoveCase1(nodeToRemove);
		}
		else
		{
			isRemoved = true;
			RemoveCase2(nodeToRemove);
		}

		return isRemoved;
	}

	// Returns a space-delimited string of the tree in order
	/*
	 Example:
			 24
			/ \
		   10  48
			\   \
			12   50

	 Should return: "10 12 24 48 50"
	*/

	std::string InOrder() {
		// TODO: Implement this method

		std::string theOrder = "";
		InOrder(mRoot, theOrder);
		theOrder.pop_back();
		return theOrder;
	}

private:

	// Recursive helper method to help with InOrder
	//
	// In:	_curr		The current Node being looked at
	//		_str		The string to add to
	//
	// NOTE:	Use in-order traversal
	// NOTE:	Use to_string to convert an int to its string equivelent
	void InOrder(Node* _curr, std::string& _str) {
		// TODO: Implement this method
		if (_curr == nullptr)
		{
			return;
		}

		InOrder(_curr->left, _str);

		_str += std::to_string(_curr->data);
		_str += " ";

		InOrder(_curr->right, _str);
	}
};

