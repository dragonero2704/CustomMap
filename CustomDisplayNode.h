#pragma once
#ifndef NODE_INCLUDE
#define NODE_INCLUDE
#include "CustomNode.h"
#endif
template <class Key, class Value>
class DisplayNode {
	template<class Key, class Value>
	friend class Node;
private:
	Node<Key, Value>* reference;
	void updateReference(Node<Key, Value>* newReference) {
		this->reference = newReference;
		this->first = newReference->key;
		this->second = newReference->value;
	}
public:
	Key first;
	Value second;
	DisplayNode(Node<Key, Value>* node) {
		this->reference = node;
		this->first = node->key;
		this->second = node->value;
	}

	// this one is going to be rarely used
	DisplayNode(void) {
		this->first = Key();
		this->second = Value();
	}

	

};
