#include <iostream>
#include "node.hpp"
#include "tree_iterator.hpp"
#include "search_tree.hpp"

int main() {

	Search_Tree::Red_Black_tree<int, std::less<int>> test;
	
	test.unbalanced_insertion(50);
	test.unbalanced_insertion(47);
	test.unbalanced_insertion(55);
	test.unbalanced_insertion(10);
	test.unbalanced_insertion(48);
	test.unbalanced_insertion(60);

	Search_Tree::Red_Black_tree<int, std::less<int>>::iterator it = test.end();
	--it;
	Search_Tree::Red_Black_tree<int, std::less<int>>::iterator it_beg = test.begin();
	for(it, it_beg; it != it_beg; --it) {
		std::cout << *it << std::endl;
	}
	--it;
	std::cout << *it << std::endl;

	return 0;
}
