#include "AVLTree.h"

#include <cassert>
#include <stdlib.h>
#include <map>
#include <time.h>
#include <cstring>


void test1();
void test2();
void test3();
void test4();
void test5();

int main() {
	try {
		test1();
		test2();
		test3();
		test4();
		test5();
	}
	catch (int e) {
		switch (e) {
			case 1: {
				std::cout << "Function KEY() FOR NULL" << std::endl;
				return -1;
			}
			case 2: {
				std::cout << "Function VALUE() FOR NULL" << std::endl;
				return -1;
			}
			case 3: {
				std::cout << "Function SORT()" << std::endl;
				return -1;
			}
			case 4: {
				std::cout << "Function [] " << std::endl;
				return -1;
			}
			case 5: {
				std::cout << "Function DELETE" << std::endl;
				return -1;
			}
			case 6: {
				std::cout << "Function PRINT FOR EMPTY" << std::endl;
				return -1;
			}
			default: {
				return 0;
			}
		}
	}
	return 0;
}

void test1() {
	AVLTree<std::string, int> Tree;
	Tree.insert("first", 1);
	Tree.insert("second", 2);
	Tree.insert("third", 3);
	Tree.insert("fourth", 4);
	Tree.insert("fivth", 5);
	Tree.insert("sixth", 6);
	Tree.insert("seventh", 7);
	Tree.insert("eighth", 8);
	Tree.insert("nineth", 9);
	Tree.insert("tenth", 10);
	Tree.AVLPrint();
	assert(Tree.find("first") && Tree.find("second") && Tree.find("fivth") && Tree.find("sixth"));
}


void test2() {
	std::cout << "TEST 2, INSERT" << std::endl;
	AVLTree<std::string, int> Tree;
	Tree.insert("first", 1);
	Tree.insert("second", 2);
	Tree.insert("third", 3);
	Tree.insert("fourth", 4);
	Tree.insert("fivth", 5);
	std::cout << "\n                          Tree 1 = {1, 2, 3, 4, 5}\n" << std::endl;
	Tree.AVLPrint();
	Tree.insert("sixth", 6);
	Tree.insert("seventh", 7);
	Tree.insert("eighth", 8);
	Tree.insert("nineth", 9);
	Tree.insert("tenth", 10);
	std::cout << "\n                            Tree 2 = Tree1 + {6, 7, 8, 9, 10}\n" << std::endl;
	Tree.AVLPrint();
}
void test3() {
	std::cout << "\nTEST 3 , DELETE\n" << std::endl;
	AVLTree<std::string, int> Tree;
	Tree.insert("first", 1);
	Tree.insert("second", 2);
	Tree.insert("third", 3);
	Tree.insert("fourth", 4);
	Tree.insert("fivth", 5);
	Tree.insert("sixth", 6);
	Tree.insert("seventh", 7);
	Tree.insert("eighth", 8);
	Tree.insert("nineth", 9);
	Tree.insert("tenth", 10);
	std::cout << "Tree {1,2,3,4,5,6,7,8,9,10} before del\n" << std::endl;
	Tree.AVLPrint();
	Tree.DeleteVertex("first");
	Tree.DeleteVertex("fivth");
	std::cout << "                       Tree - {1, 5}\n" << std::endl;
	Tree.AVLPrint();
	Tree.DeleteVertex("second");
	std::cout << "\n                  Tree - {2}\n" << std::endl;
	Tree.AVLPrint();
	Tree.DeleteVertex("third");
	Tree.DeleteVertex("fourth");
	Tree.DeleteVertex("sixth");
	std::cout << "\n                     Tree - {3,4,6}\n" << std::endl;
	Tree.AVLPrint();
}

void test4() {
	std::cout << "\nTEST 4 iterators\n" << std::endl;
	AVLTree<std::string, int> Tree;
	Tree.insert("first", 1);
	Tree.insert("second", 2);
	Tree.insert("third", 3);
	Tree.insert("fourth", 4);
	Tree.insert("fivth", 5);
	Tree.insert("sixth", 6);
	Tree.AVLPrint();
	AVLTree<std::string, int>::AVL_iterator it(Tree);
	for (it = Tree.GetMin(); it != Tree.GetMax(); ++it)
		std::cout << "(" << it.key() << ", " << it.value() << ")" << std::endl;
	std::cout << "(" << it.key() << ", " << it.value() << ")" << std::endl;
}

void test5() {
	std::cout << "\nTEST 5, =\n" << std::endl;
	AVLTree<std::string, int> Tree;
	Tree.insert("first", 1);
	Tree.insert("second", 2);
	Tree.insert("third", 3);
	Tree.insert("fourth", 4);
	Tree.insert("fivth", 5);
	std::cout << "\n                          Tree 1 = {1, 2, 3, 4, 5}\n" << std::endl;
	Tree.AVLPrint();
	AVLTree<std::string, int> Tree_copy;
	Tree_copy = Tree;
	std::cout << '\n';
	std::cout << "\nCopy Tree\n" << std::endl;
	Tree_copy.AVLPrint();
}
