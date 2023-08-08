#pragma once

#define BLACK 0 //false
#define RED 1 //true


template <class Key, class Value>
class Node
{
	template <class Key, class Value>
	friend class CustomMap;
	template <class Key, class Value>
	friend class DisplayNode;
private:
	Key key;
	Value value;
	Node<Key, Value>* parent;
	Node<Key, Value>* left;
	Node<Key, Value>* right;
	bool color;

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
	// const reference to value
	const Value& second = this->value;

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
	~Node(void) {};
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