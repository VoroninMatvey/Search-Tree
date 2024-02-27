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
	test.insert(168);
	test.insert(167);

	Search_Tree::Red_Black_tree<int>::iterator it1 = test.begin();
	Search_Tree::Red_Black_tree<int>::iterator it2 = test.end();
	int i = 1;
	while(it1 != it2) {
		std::cout<<i<<")number: "<<*it1<<" ;sum: "<<test.car(it1)<<std::endl<<std::endl;
		++it1;
		++i;
	}

	/*int j = 130;
	std::cout<<std::endl<<std::endl<<"input number: "<<j<<std::endl;
	std::cout<<test.output_lower(test.lower_bound(j));
	std::cout<<std::endl<<std::endl;*/

	/*int k = 400;
	std::cout<<std::endl<<std::endl<<"input number: "<<k<<std::endl;
	std::cout<<test.output_upper(test.upper_bound(k));
	std::cout<<std::endl<<std::endl;*/

	/*std::cout<<std::endl<<std::endl<<"out:"<<std::endl;
	std::cout<<test.left_subtree_more_than_key(test.find(131))<<std::endl;
	std::cout<<test.right_subtree_less_than_key(test.find(160))<<std::endl;
	std::cout<<test.left_subtree_less_than_key(test.find(140))<<std::endl;
	std::cout<<test.right_subtree_more_than_key(test.find(190))<<std::endl;*/
	/*int i = 0;
	while(i < 200) {
		test.insert(i);
		++i;
	}*/
	std::cout<<test.range_query(70,1000)<<std::endl;
	//std::cout<<test.right_subtree_less_than_key(test.find(171))<<std::endl;
	//std::cout<<test.mydistance(test.find(156), test.find(156))<<std::endl;
}
