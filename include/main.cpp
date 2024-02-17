#include <iostream>
#include "node.hpp"
#include "tree_iterator.hpp"
#include "search_tree.hpp"

int main() {

	Search_Tree::Red_Black_tree<int> test;
	
	test.insert(156);
	test.insert(131);
	test.insert(171);
	test.insert(190);
	test.insert(140);
	test.insert(90);
	test.insert(70);
	test.insert(160);
	test.insert(165);
	test.insert(163);
	test.insert(166);

	return 0;
}
