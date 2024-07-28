#include "bin_node.h"
bin_node::bin_node() {					//constructor
	hash = -1;
	left = nullptr;
	right = nullptr;
	link = std::make_shared<Node>();	//constructor by hash
}
bin_node::bin_node(int a) {
	hash = a;
	left = nullptr;
	right = nullptr;
	link = std::make_shared<Node>(a);	//destructor
}
bin_node::~bin_node() {
	left = nullptr;
	right = nullptr;
}
