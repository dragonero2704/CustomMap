#pragma once
#include "CustomMap.h"

template <class Key, class Value>
class Node
{
	template <class A, class B>
	friend class CustomMap;
private:
	Key key;
	Value value;
	Node<Key, Value>* parent;
	Node<Key, Value>* left;
	Node<Key, Value>* right;

	Node<Key, Value>* uncle();
	Node<Key, Value>* grandparent();

public:
	Node();
	Node(Key key, Value value);
	~Node();
	Key getKey();
	Value getValue();
	
};

