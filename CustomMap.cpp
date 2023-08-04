#include "CustomMap.h"
#include "CustomNode.h"

template<class Key, class Value>
CustomMap<Key, Value>::CustomMap() {
	this->root = nullptr;
	this->_size = 0;
}

template<class Key, class Value>
CustomMap<Key, Value>::CustomMap(Key key, Value value)
{
	this->root = new Node<Key, Value>(key, value);
}

template<class Key, class Value>
CustomMap<Key, Value>::~CustomMap()
{
	if (this->root != nullptr) this->recDelete(this->root);
	else delete this->root;
}

template<class Key, class Value>
void CustomMap<Key, Value>::recDelete(Node<Key, Value>* node)
{
	if (node->left != nullptr) this->recDelete(node->left);
	if (node->right != nullptr) this->recDelete(node->right);

	if(node !=nullptr) delete node;
	return;
}

template<class Key, class Value>
bool CustomMap<Key, Value>::isempty()
{
	return this->_size == 0;
}

template<class Key, class Value>
unsigned int CustomMap<Key, Value>::size()
{
	return this->_size;
}
