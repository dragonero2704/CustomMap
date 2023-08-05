#pragma once
#include <iostream>
#include "CustomNode.h"
#include "macros.h"
using namespace std;


template <class Key, class Value>
class CustomMap
{
	template <class A, class B>
	friend class Node;
private:
	Node<Key, Value>* root;
	unsigned int _size;

	void realInsert(Node<Key, Value>* node) {
		
		if (this->root == nullptr) {
			this->root = node;
			this->root->color = BLACK;
		}
		else
		{
			// inserimento
			Node<Key, Value>* tmp = this->root;
			Node<Key, Value>* tmpParent = tmp->parent;


			while (tmp != nullptr) {
				if (node->key == tmp->key) 
				{
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
			//uso tmpParent
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
			this->_size++;
			//RB balacing cases
			case1(node);
		}
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
			/* Here, n == n->parent->right && n->parent == grandparent(n)->right */
			rotateLeft(node->parent);
		}
	};
	void recDelete(Node<Key, Value>* node) {
		if (node->left != nullptr) this->recDelete(node->left);
		if (node->right != nullptr) this->recDelete(node->right);
		delete node;
	};
	// not working needs fixing: does not change this->root
	void rotateLeft(Node<Key, Value>* pivot) {
		Node<Key, Value>* root = pivot->parent;
		Node<Key, Value>* oldLeft = pivot->left;
		Node<Key, Value>* grandParent = pivot->parent->parent;
		bool left;
		if (grandParent != nullptr) left = root->isLeftSon();
		//pivot diventa la nuova root
		pivot->left = root;
		root->parent = pivot;

		//oldLeft diventa root->right (prima root->right era pivot)
		root->right = oldLeft;
		if(oldLeft != nullptr) oldLeft->parent = root;

		//ora bisogna occuparsi di collegare il grandparent a pivot
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
			//pivot è la nuova root
			this->root = pivot;
		}
		
	}
	// not working needs fixing: does not change this->root
	void rotateRight(Node<Key, Value>* pivot) {
		Node<Key, Value>* root = pivot->parent;
		Node<Key, Value>* oldRight = pivot->right;
		Node<Key, Value>* grandParent = pivot->parent->parent;
		bool left;
		if (grandParent != nullptr) left = root->isLeftSon();
		//pivot diventa la nuova root
		pivot->right = root;
		root->parent = pivot;

		//oldLeft diventa root->right (prima root->right era pivot)
		root->left = oldRight;
		if (oldRight != nullptr)oldRight->parent = root;

		//ora bisogna occuparsi di collegare il grandparent a pivot
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
			//pivot è la nuova root
			this->root = pivot;
		}
	}

public:
	CustomMap(void) {
		this->root = nullptr;
		this->_size = 0;
	};
	CustomMap(Key key, Value value) {
		this->root = new Node<Key, Value>(key, value);
		this->root->color = BLACK;
		this->_size = 1;
	};
	~CustomMap() {
		if (this->root != nullptr) this->recDelete(this->root);
	};

	bool isempty(void) {
		return this->_size == 0;
	};
	unsigned int size(void) {
		return this->_size;
	};

	void insert(Key key, Value value) {
		Node<Key, Value>* node = new Node<Key, Value>(key, value);
		this->realInsert(node);
	};
	void insert(Node<Key, Value> node) {
		this->realInsert(&node);
	};

	Value find(Key k) {
		Node<Key, Value>* tmp = this->root;
		if (tmp->key == k) return tmp->value;

		while (tmp->key != k) {

			if (k > tmp->key) {
				// go right
				tmp = tmp->right;
			}
			else {
				// go left
				tmp = tmp->left;
			}
			if (tmp == nullptr) return Value();
		}
		return tmp->value;
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
				//definisco il nuovo elemento
				Node<Key, Value>* node = new Node<Key, Value>(key, Value());
				this->insert(*node);
				return node->value;
			}
		}
		return tmp->value;
	};
};





