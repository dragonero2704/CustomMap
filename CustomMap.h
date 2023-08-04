#pragma once
#include <iostream>
#include "CustomNode.h"
using namespace std;


template <class Key, class Value>
class CustomMap
{
	template <class A, class B>
	friend class Node;
private:
	Node<Key, Value>* root;
	unsigned int _size;

public:
	CustomMap();
	CustomMap(Key key, Value value);
	~CustomMap();
	void recDelete(Node<Key, Value>*);

	bool isempty();
	unsigned int size();
};




