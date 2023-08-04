#include <iostream>
#include "CustomNode.h"

using namespace std;

template<class Key, class Value>
Node<Key, Value>* Node<Key, Value>::uncle()
{
	Node<Key, Value>* grandparent = this->grandparent();

	if (grandparent != nullptr) {
		Node<Key, Value>* parent = this->parent;
		if (grandparent->right == this->parent) return grandparent->left;
		else return grandparent->right;
	}
	
	return nullptr;
}

template<class Key, class Value>
Node<Key, Value>* Node<Key, Value>::grandparent()
{
	if (this->parent != nullptr) {	
		if (this->parent->parent != nullptr) {
			return this->parent->parent;
		}
	}
	return nullptr;
}

template<class Key, class Value>
Node<Key, Value>::Node() {
	this->key = Key();
	this->value = Value();
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

template<class Key, class Value>
Node<Key, Value>::Node(Key key, Value value) {
	this->key = key;
	this->value = value;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

template<class Key, class Value>
Node<Key, Value>::~Node()
{
}

template<class Key, class Value>
Key Node<Key, Value>::getKey()
{
	return this->key;
}

template<class Key, class Value>
Value Node<Key, Value>::getValue()
{
	return this->value;
}

