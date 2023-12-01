#include <iostream>
#include "node.hpp"
#include "tree_iterator.hpp"
#include "search_tree.hpp"

int main() {

	Search_Tree::Red_Black_tree<int> test;
	
	test.insert(50);
	std::cout << "norv";
	test.insert(47);
	test.insert(55);
	test.insert(10);
	test.insert(48);
	test.insert(60);

	Search_Tree::Red_Black_tree<int>::iterator it = test.find(48);
	std::cout << *it << std::endl;
	

	return 0;
}
