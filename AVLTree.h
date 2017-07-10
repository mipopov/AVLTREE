#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "node.h"
#include <exception>
#include <cmath>

template<class U, class T>
AVLNode<U, T> *Next(AVLNode<U, T> *root, const U &str);

template <class U, class T>
class AVLTree {
public:
	class AVL_iterator {
	public:
		AVL_iterator(const AVLTree<U, T> &other) : node_(NULL), root_(other._root) {}

		AVL_iterator() : node_(NULL), root_(NULL) {}

		AVL_iterator(const AVLTree<U, T> &Tr, AVLNode<U, T> *node) : root_(Tr._root), node_(node) {}

		AVL_iterator(const AVL_iterator &other) : node_(other.node_), root_(other.root_) {}

		AVL_iterator(AVLNode<U, T> *other) : node_(other) {}

		AVLNode<U, T> operator*() { return *node_; }

		AVL_iterator GetLeft() {
			return node_->_left ? AVL_iterator(node_->_left) : AVL_iterator(NULL);
		}

		AVL_iterator GetRight() {
			return node_->_right ? AVL_iterator(node_->_right) : AVL_iterator(NULL);
		}

		bool operator==(const AVL_iterator &other) {
			return node_ == other.node_;
		}

		bool operator<(const AVL_iterator &other) {
			return node_ < other.node_;
		}

		bool operator!=(const AVL_iterator &other) {
			return node_ != other.node_;
		}

		AVL_iterator &operator=(const AVL_iterator &other) {
			node_ = other.node_;;
			return *this;
		}

		AVL_iterator &operator++() {
			node_ = Next(root_, node_->_key);
			return *this;
		}

		AVL_iterator operator--() {
			node_ = Prev(root_, node_->_key);
			return *this;
		}

		U key() const {
			if (node_ != NULL)
				return node_->_key;
			throw 1;
		}

		T value() const {
			if (node_ != NULL)
				return node_->_value;
			throw 2;
		}

		AVLNode<U, T> *node_;
		AVLNode<U, T> *root_;
	};

	AVLTree() : _root(NULL), _size(0) {}

	AVLTree(const AVLTree<U, T> &other);

	~AVLTree();

	size_t Height() { return _root->_height; }

	AVLNode<U, T> **insert_(AVLNode<U, T> **node, const U &key, const T &value);

	void insert(const U &key, const T &value);

	T &operator[](const U &str);

	AVLTree<U, T> &operator=(const AVLTree<U, T> &other);

	void AVLSort();

	void DeleteVertex(const U &str);

	AVLNode<U, T> **DeleteVertex_(AVLNode<U, T> **node, const U &str);

	AVLNode<U, T> *find_(AVLNode<U, T> *node, const U &str);

	bool find(const U &str);

	AVLNode<U, T> *GetMin_(AVLNode<U, T> *other) const;

	AVLNode<U, T> *GetMax_(AVLNode<U, T> *other) const;

	AVL_iterator GetMin() const { return AVL_iterator(GetMin_(_root)); }

	AVL_iterator GetMax() const { return AVL_iterator(GetMax_(_root)); }

	AVL_iterator GetRoot() const { return AVL_iterator(_root); }

	AVL_iterator GetNext(const AVL_iterator &it) const { return AVL_iterator(next(it.key())); }

	AVL_iterator GetPrev(const AVL_iterator &it) const { return AVL_iterator(prev(it.key())); }

	AVLNode<U, T> *next(const U &str) const;

	AVLNode<U, T> *prev(const U &str) const;

	void Destruct(AVLNode<U, T> **node);

	int TheoryHeight() { return (2.14 * log(_size)); }

	AVL_iterator Find_(AVL_iterator node, const U &str) {
		if (str < node.key())
			Find_(node.GetLeft(), str);
		else if (str > node.key())
			Find_(node.GetRight(), str);
		else
			return node;
	}

	AVL_iterator Find(const U &str) {
		if (!find())
			AVL_iterator(NULL);
		else
			return Find_(_root, str);
	}

	size_t size() { return _size; }

	void print_(AVLNode<U, T> *node, int lvl, T value, char c) const;

	void AVLPrint() const;

private:
	AVLNode<U, T> *_root;
	size_t _size;
};


template<class U, class T>
AVLNode<U, T> *AVLTree<U, T>::prev(const U& str) const {
	AVLNode<U, T> *cur = _root;
	AVLNode<U, T> *suc = NULL;
	while (cur != NULL) {
		if (cur->_key < str) {
			suc = cur;
			cur = cur->_right;
		} else
			cur = cur->_left;
	}
	return suc;
}

template<class U, class T>
T &AVLTree<U, T>::operator[](const U &str) {
	if (!find(str))
		throw 4;
	AVL_iterator it = Find(str);
	return it.value();
}
template<class U, class T>
AVLTree<U, T>::AVLTree(const AVLTree<U, T> &other) {
	_root = NULL;
	_size = 0;
	*this = other;
}
template<class U, class T>
AVLTree<U, T> &AVLTree<U, T>::operator=(const AVLTree<U, T> &other) {
	if (_size > 0)
		Destruct(&_root);
	_root = NULL;
	AVLNode<U, T> *Cur = other._root;
	AVLNode<U, T> *right = other._root;
	while (Cur->_left != NULL)
		Cur = Cur->_left;
	while (right->_right != NULL)
		right = right->_right;
	while (Cur != right) {
		insert(Cur->_key, Cur->_value);
		Cur = other.next(Cur->_key);
	}
	insert(right->_key, right->_value);
	return *this;
}
template<class U, class T>
AVLNode<U, T> *Next(AVLNode<U, T> *root, const U &str) {
	AVLNode<U, T> *cur = root;
	AVLNode<U, T> *suc = NULL;
	while (cur != NULL) {
		if (cur->_key > str) {
			suc = cur;
			cur = cur->_left;
		} else
			cur = cur->_right;
	}
	return suc;
}
template<class U, class T>
AVLNode<U, T> *Prev(AVLNode<U, T> *root, const U &str) {
	AVLNode<U, T> *cur = root;
	AVLNode<U, T> *suc = NULL;
	while (cur != NULL) {
		if (cur->_key < str) {
			suc = cur;
			cur = cur->_right;
		} else
			cur = cur->_left;
	}
	return suc;
}
template<class U, class T>
AVLNode<U, T> *AVLTree<U, T>::next(const U &str) const {
	AVLNode<U, T> *cur = _root;
	AVLNode<U, T> *suc = NULL;
	while (cur != NULL) {
		if (cur->_key > str) {
			suc = cur;
			cur = cur->_left;
		} else
			cur = cur->_right;
	}
	return suc;
}
template<class U, class T>
AVLNode<U, T> *AVLTree<U, T>::GetMin_(AVLNode<U, T> *other) const {
	if (other->_left == NULL)
		return other;
	return GetMin_(other->_left);
}
template<class U, class T>
AVLNode<U, T> *AVLTree<U, T>::GetMax_(AVLNode<U, T> *other) const {
	if (other->_right == NULL)
		return other;
	return GetMax_(other->_right);
}

template<class U, class T>
void AVLTree<U, T>::Destruct(AVLNode<U, T> **node) {
	if (*node != NULL) {
		Destruct(&((*node)->_left));
		Destruct(&((*node)->_right));
		delete *node;
		--_size;
	}
}

template<class U, class T>
AVLTree<U, T>::~AVLTree() {
	Destruct(&_root);
}

template<class U, class T>
AVLNode<U, T> *AVLTree<U, T>::find_(AVLNode<U, T> *node, const U &str) {
	if (node == NULL)
		return NULL;
	if (str < node->_key) {
		find_(node->_left, str);
		return node;
	} else if (str > node->_key) {
		find_(node->_right, str);
		return node;
	} else
		return node;
}

template<class U, class T>
bool AVLTree<U, T>::find(const U &str) {
	AVLNode<U, T> *r = _root;
	while (r != NULL) {
		if (str < r->_key)
			r = r->_left;
		else if (str > r->_key)
			r = r->_right;
		else
			return true;
	}
	return false;
}
template<class U, class T>
AVLNode<U, T> **AVLTree<U, T>::insert_(AVLNode<U, T> **node, const U &key, const T &value) {
	if (*node == NULL) {
		*node = new AVLNode<U, T>(key, value);
		return node;
	} else {
		if (key < (*node)->_key)
			(*node)->_left = *(insert_(&((*node)->_left), key, value));
		else
			(*node)->_right = *(insert_(&((*node)->_right), key, value));
		*node = (*node)->Balance();
		return node;
	}
}
template<class U, class T>
void AVLTree<U, T>::insert(const U &key,const T &value) {
	if (!find(key)) {
		insert_(&_root, key, value);
		++_size;
	}
}

template<class U, class T>
AVLNode<U, T> **AVLTree<U, T>::DeleteVertex_(AVLNode<U, T> **node, const U &str) {
	if (str < (*node)->_key)
		(*node)->_left = *(DeleteVertex_(&((*node)->_left), str));
	else if (str > (*node)->_key)
		(*node)->_right = *(DeleteVertex_(&((*node)->_right), str));
	else {
		AVLNode<U, T> **l = &((*node)->_left);
		AVLNode<U, T> *_l = (*node)->_left;
		AVLNode<U, T> *r = ((*node)->_right);
		delete *node;
		*l = _l;
		if (r == NULL)
			return l;
		AVLNode<U, T> *min = (r)->findMin();
		min->_right = (r)->deleteMin();
		min->_left = *l;
		*node = (min->Balance());
		return node;
	}
	*node = (*node)->Balance();
	return node;
}

template<class U, class T>
void AVLTree<U, T>::DeleteVertex(const U &str) {
	if (find(str)) {
		DeleteVertex_(&_root, str);
		--_size;
	} else
		throw 5;
}

template<class U, class T>
void AVLTree<U, T>::print_(AVLNode<U, T> *node, int lvl, T value, char c) const {
	if (node == NULL)
		return;
	for (int i = 0; i < lvl; i++)
		std::cout << "     ";
	std::cout << "|"
			  << node->BalanceFactor()
			  << ", " << value
			  << ", " << c
			  << "|" << "("
			  << node->_key
			  << ", " << node->_value << ")" << "\n";
	print_(node->_left, lvl - 2, node->_value, 'L');
	print_(node->_right, lvl + 2, node->_value, 'R');
}

template<class U, class T>
void AVLTree<U, T>::AVLPrint() const {
	if (_size == 0)
		throw 6;
	print_(_root, _size, 0, '0');
}

#endif
