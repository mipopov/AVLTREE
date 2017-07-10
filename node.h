#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>

template<class U, class T>
class AVLNode {
public:
	AVLNode();

	AVLNode(const U &key, const T &value);

	AVLNode<U, T> *LeftRotate();

	AVLNode<U, T> *RightRotate();

	AVLNode<U, T> *Balance();

	AVLNode<U, T> *findMin();

	AVLNode<U, T> *deleteMin();

	int BalanceFactor();

	void FixHeight();

	U _key;
	T _value;
	AVLNode<U, T> *_left;
	AVLNode<U, T> *_right;
	size_t _height;
};

template<class U, class T>
AVLNode<U, T>::AVLNode() {
	_left = NULL;
	_right = NULL;
	_height = 0;
}
template<class U, class T>
AVLNode<U, T>::AVLNode(const U &key, const T &value) {
	_key = key;
	_value = value;
	_height = 1;
	_left = NULL;
	_right = NULL;
}
template<class U, class T>
void AVLNode<U, T>::FixHeight() {
	size_t H_l = _left ? _left->_height : 0;
	size_t H_r = _right ? _right->_height : 0;
	_height = (H_l > H_r ? H_l : H_r) + 1;
}

template<class U, class T>
AVLNode<U, T> *AVLNode<U, T>::RightRotate() {
	AVLNode<U, T> *L = _left;
	_left = L->_right;
	L->_right = this;
	FixHeight();
	L->FixHeight();
	return L;
}

template<class U, class T>
AVLNode<U, T> *AVLNode<U, T>::LeftRotate() {
	AVLNode<U, T> *R = _right;
	_right = R->_left;
	R->_left = this;
	FixHeight();
	R->FixHeight();
	return R;
}

template<class U, class T>
AVLNode<U, T> *AVLNode<U, T>::Balance() {
	FixHeight();
	switch (BalanceFactor()) {
		case 2:
			if (_right->BalanceFactor() < 0)
				_right = _right->RightRotate();
			return LeftRotate();
		case -2:
			if (_left->BalanceFactor() > 0)
				_left = _left->LeftRotate();
			return RightRotate();
		default:
			return this;
	}
}

template<class U, class T>
int AVLNode<U, T>::BalanceFactor() {
	if (this == NULL)
		return 0;
	int r_height = _right ? _right->_height : 0;
	int l_height = _left ? _left->_height : 0;
	return r_height - l_height;
}

template<class U, class T>
AVLNode<U, T> *AVLNode<U, T>::findMin() {
	return _left ? _left->findMin() : this;
}

template<class U, class T>
AVLNode<U, T> *AVLNode<U, T>::deleteMin() {
	if (_left == NULL)
		return _right;
	_left = _left->deleteMin();
	return Balance();
}

#endif
