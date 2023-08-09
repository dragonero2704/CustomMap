#pragma once

#define BLACK 0 //false
#define RED 1 //true


template <class Key, class Value>
class Node
{
	// this way the CustomMap class can access private attributes and methods
	template <class Key, class Value>
	friend class CustomMap;
private:
	// key of the Node, used to build the binary tree
	Key key;
	// value of each node
	Value value;

	Node<Key, Value>* parent;
	Node<Key, Value>* left;
	Node<Key, Value>* right;

	// used for RB balancing of the binary tree
	bool color;

	// Helper function for bilancing the binary tree
	Node<Key, Value>* uncle() 
	{
		Node<Key, Value>* grandparent = this->grandparent();

		if (grandparent != nullptr) {
			Node<Key, Value>* parent = this->parent;
			if (grandparent->right == this->parent) return grandparent->left;
			else return grandparent->right;
		}

		return nullptr;
	};

	Node<Key, Value>* grandparent() {
		if (this->parent != nullptr) {
			if (this->parent->parent != nullptr) {
				return this->parent->parent;
			}
		}
		return nullptr;
	};

	Node<Key, Value>* sibling() {
		if (this->parent != nullptr) 
		return this->parent->left == this ? this->parent->right : this->parent->left;
		return nullptr;
	};

	bool isLeftSon() {
		return this->parent->left == this;
	}
	bool isRightSon() {
		return this->parent->right == this;
	}

public:
	// const reference to key
	const Key& first = this->key;
	// reference to value
	Value& second = this->value;

	// constructors definitions
	Node(void) {
		this->key = Key();
		this->value = Value();
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->color = RED;
	};
	Node(Key key, Value value) {
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->color = RED;
	};

	// empty destructor
	~Node(void) {};

	// operators definitions
	bool operator!=(Node<Key, Value>& other) const {
		return this->key != other->key;
	}
	bool operator==(Node<Key, Value>& other) const {
		return this->key == other->key;
	}

	Node<Key,Value>* operator*() {
		return this;
	}

	Node<Key, Value>* operator->() {
		return this;
	}
};