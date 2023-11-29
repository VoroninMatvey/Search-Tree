#include <iostream>
#include "node.hpp"
#include "tree_iterator.hpp"
#include "search_tree.hpp"

int main() {

	Search_Tree::Red_Black_tree<int, std::less<int>> test;
	for(int i = 1; i <= 100; ++i) {
		test.unbalanced_insertion(i);
	}

	std::cout << "Success" << 1 << std::endl;

	Search_Tree::Red_Black_tree<int, std::less<int>>::iterator it1 = test.begin();
	std::cout << "Success" << 2 << std::endl;
	Search_Tree::Red_Black_tree<int, std::less<int>>::iterator it2 = test.end();
	std::cout << "Success" << 3 << std::endl;
	while(it1 != it2) {
		std::cout << *it1 << std::endl;
		++it1;
	}
	return 0;

}
