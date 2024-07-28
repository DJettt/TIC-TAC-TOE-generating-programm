#pragma once
#include "Node.h"
class bin_node {						//node of binary tree
public:
	int hash;							//hash in node of binary tree
	std::shared_ptr<bin_node>left;		//smart pointer to left bin_node
	std::shared_ptr<bin_node>right;		//smart pointer to right bin_node
	std::shared_ptr<Node>link;			//smart pointer to node


	bin_node();							//constructor
	bin_node(int a);					//constructor by hash
	~bin_node();						//destructor
};