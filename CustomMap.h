#pragma once
#ifndef NODE_INCLUDE
#define NODE_INCLUDE
#include "CustomNode.h"
#endif
/*
#include "macros.h"
#include <iostream>
using namespace std;
*/

template <class Key, class Value>
class CustomMap
{
private:
	Node<Key, Value>* root;
	size_t _size;

	// in this function the node is inserted and then the balancing operations are executed based on the position of the new node
	void realInsert(Node<Key, Value>* node) {
		if (this->root == nullptr) {
			this->root = node;
		}
		else
		{
			Node<Key, Value>* tmp = this->root;
			Node<Key, Value>* tmpParent = tmp->parent;
			this->_size++;
			while (tmp != nullptr) {
				// if a node is found with the same key, the value of the already existing node is modified
				if (node->key == tmp->key) 
				{
					this->_size--;
					tmp->value = node->value;
					return;
				} 
				if (node->key > tmp->key) {
					//go right
					tmpParent = tmp;
					tmp = tmp->right;
				}
				else
				{
					// go left
					tmpParent = tmp;
					tmp = tmp->left;
				}
			}
			if (node->key > tmpParent->key) {
				//right
				node->parent = tmpParent;
				tmpParent->right = node;
			}
			else {
				//left
				node->parent = tmpParent;
				tmpParent->left = node;
			}
			//correctly inserted
		}
		//RB balacing cases
		case1(node);
	};

	void case1(Node<Key, Value>* node) {
		// info("Case 1");
		if (node->parent == nullptr)
			node->color = BLACK;
		else
			case2(node);
	};
	void case2(Node<Key, Value>* node) {
		// info("Case 2");
		if (node->parent->color == BLACK) return;
		else case3(node);
	};
	void case3(Node<Key, Value>* node) {
		// info("Case 3");
		if (node->uncle() != nullptr && node->uncle()->color == RED) {
			node->parent->color = BLACK;
			node->uncle()->color = BLACK;
			node->grandparent()->color = RED;
			case1(node->grandparent());
		}
		else case4(node);
	};
	void case4(Node<Key, Value>* node) {
		//info("Case 4");
		if (node == node->parent->right && node->parent == node->grandparent()->left) {
			rotateLeft(node);
			node = node->left;
		}
		else if (node == node->parent->left && node->parent == node->grandparent()->right) {
			rotateRight(node);
			node = node->right;
		}
		case5(node);
	};
	void case5(Node<Key, Value>* node) {
		// info("Case 5");
		node->parent->color = BLACK;
		node->grandparent()->color = RED;
		if (node == node->parent->left && node->parent == node->grandparent()->left) {
			rotateRight(node->parent);
		}
		else {
			rotateLeft(node->parent);
		}
	};

	// tree left rotation
	void rotateLeft(Node<Key, Value>* pivot) {
		Node<Key, Value>* root = pivot->parent;
		Node<Key, Value>* oldLeft = pivot->left;
		Node<Key, Value>* grandParent = pivot->parent->parent;

		// this piece of code determines if the root has a parent, it is a right son or a left son
		bool left = grandParent != nullptr ? root->isLeftSon() : 0;
		
		// pivot becomes the new root
		pivot->left = root;
		root->parent = pivot;

		//oldLeft becomes root->right (before root->right was pivot)
		root->right = oldLeft;
		if(oldLeft != nullptr) oldLeft->parent = root;

		// now we need to link pivot->parent with grandParent
		pivot->parent = grandParent;
		if (grandParent != nullptr) {
			if (left) {
				grandParent->left = pivot;
			}
			else {
				grandParent->right = pivot;
			}
		}
		else {
			// if grandParent is nullptr, then pivot is the new main root of the tree
			this->root = pivot;
		}
		
	}

	// tree right rotation
	void rotateRight(Node<Key, Value>* pivot) {
		Node<Key, Value>* root = pivot->parent;
		Node<Key, Value>* oldRight = pivot->right;
		Node<Key, Value>* grandParent = pivot->parent->parent;
		
		bool left = grandParent != nullptr ? root->isLeftSon() : 0;
		
		// pivot becomes the new root
		pivot->right = root;
		root->parent = pivot;

		//oldRight becomes root->right (before root->right was pivot)
		root->left = oldRight;
		if (oldRight != nullptr)oldRight->parent = root;

		// now we need to link pivot->parent with grandParent
		pivot->parent = grandParent;
		if (grandParent != nullptr) {
			if (left) {
				grandParent->left = pivot;
			}
			else {
				grandParent->right = pivot;
			}
		}
		else {
			// if grandParent is nullptr, then pivot is the new main root of the tree
			this->root = pivot;
		}
	}

	// recursive delete function
	void recDelete(Node<Key, Value>* node) {
		if (node->left != nullptr) this->recDelete(node->left);
		if (node->right != nullptr) this->recDelete(node->right);
		delete node;
	};

public:
	//costructors definitions
	CustomMap(void) {
		this->root = nullptr;
		this->_size = 0;
	};
	CustomMap(Key key, Value value) {
		this->root = new Node<Key, Value>(key, value);
		this->root->color = BLACK;
		this->_size = 1;
	};

	// recursive deletion function
	~CustomMap() {
		if (this->root != nullptr) this->recDelete(this->root);
	};

	bool isempty(void) {
		return this->_size == 0;
	};

	size_t size(void) {
		return this->_size;
	};

	// insertion function if key and value are supplied 
	void insert(Key key, Value value) {
		Node<Key, Value>* node = new Node<Key, Value>(key, value);
		this->realInsert(node);
	};

	// insertion function if a Node is supplied 
	void insert(Node<Key, Value> node) {
		this->realInsert(&node);
	};

	Value& operator[](Key key) {
		if (this->root == nullptr) {
			this->root = new Node<Key, Value>(key, Value());
			return this->root->value;
		}

		Node<Key, Value>* tmp = this->root;
		if (tmp->key == key) return tmp->value;

		while (tmp->key != key) {
			if (key > tmp->key) {
				// go right
				tmp = tmp->right;
			}
			else {
				// go left
				tmp = tmp->left;
			}
			if (tmp == nullptr)
			{
				// if the element is not found, a new node is inserted in the tree with defualt value and the key supplied
				// then a reference to the node->value is returned so it can be changed in the code
				Node<Key, Value>* node = new Node<Key, Value>(key, Value());
				this->realInsert(node);
				return node->value;
			}
		}
		return tmp->value;
	};
	void empty() {
		if(this->root!=nullptr) this->recDelete(this->root);
		this->_size = 0;
	}

	// iterator class definition
	class Iterator {
	private:
		Node<Key, Value>* ptr;
	public:
		// constructor definitions
		Iterator() {
			this->ptr = nullptr;
		};
		Iterator(Node<Key, Value>* node) {
			this->ptr = node;
		};

		//empty destructor
		~Iterator() {};

		// operators definitions
		void operator++(int) {
			if (this->ptr == nullptr) return;
			Node<Key, Value>* nodocorr = this->ptr;

			Key key = this->ptr->key;
			if (nodocorr->right != nullptr)
			{
				nodocorr = nodocorr->right;

				// controllo se ci sono rami minori
				while (nodocorr->left != nullptr && key < nodocorr->left->key)
				{
					nodocorr = nodocorr->left;
				}
				this->ptr = nodocorr;
				return;
			}
			else
			{
				if (nodocorr->parent != nullptr)
				{
					nodocorr = nodocorr->parent;
					while (nodocorr->key < key)
					{
						if (nodocorr->parent == nullptr)
						{
							this->ptr = nullptr;
							return;
						}
						nodocorr = nodocorr->parent;
					}

					while (nodocorr->left != nullptr && key < nodocorr->left->key)
					{
						nodocorr = nodocorr->left;
					}
					this->ptr = nodocorr;
					return;
				}
			}
		}

		void operator--(int) {
			if (this->ptr == nullptr) return;
			Node<Key, Value>* nodocorr = this->ptr;
			Key key = ptr->key;
			if (nodocorr->left != nullptr)
			{
				nodocorr = nodocorr->left;
				while (nodocorr->right != nullptr && nodocorr->right->key < key)
				{
					nodocorr = nodocorr->right;
				}
				this->ptr = nodocorr;
				return;
			}
			else
			{
				if (nodocorr->parent != nullptr)
				{
					nodocorr = nodocorr->parent;
					while (nodocorr->key > key)
					{
						if (nodocorr->parent == nullptr)
						{
							// I have reached back way to the root, it means there are no valid nodes
							// set this->ptr to nullptr and return
							this->ptr = nullptr;
							return;
						}

						nodocorr = nodocorr->parent;

					}

					this->ptr = nodocorr;
					return;
				}
				this->ptr = nullptr;
			}
		}

		Iterator& operator+(const int& value) const {
			for (int i = 0; i < value; i++) {
				this->operator++();
			}
		}
		Iterator& operator-(const int& value) const {
			for (int i = 0; i < value; i++) {
				this->operator--();
			}
		}

		Node<Key, Value>* operator->()
		{
			return this->ptr;
		}
		Node<Key, Value>* operator*()
		{
			return this->ptr;
		}

		bool operator!=(Iterator other) const {
			return *other != this->ptr;
		}
		bool operator==(Iterator other) const  {
			return *other == this->ptr;
		}
	};

	// returns an iterator to the smallest key
	Iterator begin() {
		if (this->root == nullptr) return Iterator();
		Node<Key, Value>* tmp = this->root;
		while (tmp->left != nullptr) {
			tmp = tmp->left;
		}
		return Iterator(tmp);
		
	}

	// returns an iterator with its ptr property = nullptr
	Iterator end(){
		return Iterator();
	}

	Iterator find(Key k) {
		Node<Key, Value>* tmp = this->root;
		
		while (tmp->key != k) {

			if (k > tmp->key) {
				// go right
				tmp = tmp->right;
			}
			else {
				// go left
				tmp = tmp->left;
			}
			if (tmp == nullptr) return this->end();
		}
		return Iterator(tmp);
	};

	// ReverseIterator class definition
	class ReverseIterator {
	private:
		Node<Key, Value>* ptr;
	public:
		// constructors defintions
		ReverseIterator() {
			this->ptr = nullptr;
		};
		ReverseIterator(Node<Key, Value>* node) {
			this->ptr = node;
		};
		// empty destuctor
		~ReverseIterator() {};

		// operators definitions
		void operator++(int) {
			if (this->ptr == nullptr) return;
			Node<Key, Value>* nodocorr = this->ptr;
			Key key = ptr->key;
			if (nodocorr->left != nullptr)
			{
				nodocorr = nodocorr->left;
				while (nodocorr->right != nullptr && nodocorr->right->key < key)
				{
					nodocorr = nodocorr->right;
				}
				this->ptr = nodocorr;
				return;
			}
			else
			{
				if (nodocorr->parent != nullptr)
				{
					nodocorr = nodocorr->parent;
					while (nodocorr->key > key)
					{
						if (nodocorr->parent == nullptr)
						{
							// I have reached back way to the root, it means there are no valid nodes
							// set this->ptr to nullptr and return
							this->ptr = nullptr;
							return;
						}
						
						nodocorr = nodocorr->parent;
						
					}
				
					this->ptr = nodocorr;
					return;
				}
				this->ptr = nullptr;
			}
		};
		
		void operator--(int) {
			if (this->ptr == nullptr) return;
			Node<Key, Value>* nodocorr = this->ptr;

			Key key = this->ptr->key;
			if (nodocorr->right != nullptr)
			{
				nodocorr = nodocorr->right;

				// controllo se ci sono rami minori
				while (nodocorr->left != nullptr && key < nodocorr->left->key)
				{
					nodocorr = nodocorr->left;
				}
				this->ptr = nodocorr;
				return;
			}
			else
			{
				if (nodocorr->parent != nullptr)
				{
					nodocorr = nodocorr->parent;
					while (nodocorr->key < key)
					{
						if (nodocorr->parent == nullptr)
						{
							this->ptr = nullptr;
							return;
						}
						nodocorr = nodocorr->parent;
					}

					while (nodocorr->left != nullptr && key < nodocorr->left->key)
					{
						nodocorr = nodocorr->left;
					}
					 
					this->ptr = nodocorr;
					return;
				}
			}
		};

		ReverseIterator& operator+(const int& value) const {
			for (int i = 0; i < value; i++) {
				this->operator++();
			}
		}

		ReverseIterator& operator-(const int& value) const {
			for (int i = 0; i < value; i++) {
				this->operator--();
			}
		}

		Node<Key, Value>* operator->()
		{
			return this->ptr;
		}
		Node<Key, Value>* operator*()
		{
			return this->ptr;
		}

		bool operator!=(ReverseIterator other) const {
			return *other != this->ptr;
		}
		bool operator==(ReverseIterator other) const {
			return *other == this->ptr;
		}
		
	};

	// returns an iterator to the largest key in the tree
	ReverseIterator rbegin() {
		Node<Key, Value>* tmp = this->root;
		if (tmp == nullptr) return ReverseIterator();

		while (tmp->right != nullptr) {
			tmp = tmp->right;
		}
		return ReverseIterator(tmp);
	}

	ReverseIterator rend() {
		return ReverseIterator();
	}
};