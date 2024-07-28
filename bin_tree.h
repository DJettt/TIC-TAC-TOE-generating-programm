#pragma once
#include "bin_node.h"
class bin_tree {
public:
	std::shared_ptr<bin_node> head;					//the root of binary tree

	bin_tree();										//constructor
	~bin_tree();									//destructor

	void push(int a);								//adding new bin_node by hash
	void push(std::string s);						//adding new bin_node by string
	std::shared_ptr<Node> get_link(int a);			//get the link to a Node by hash
	std::shared_ptr<Node> get_link(std::string s);	//get the link to a Node by string
};