#include "bin_tree.h"
bin_tree::bin_tree() {
	head = std::make_shared<bin_node>(9960);	
	// The large number of pushes in the constructor is because
	// we are balancing the binary tree to a state where
	// search operations take logarithmic time (approximately 13).
	// The hashes are always generated the same, so
	// we can push the same values once,
	// which were found separately, outside of this program.
	push(4516);									
	push(2028);		
	push(998);
	push(487);
	push(212);
	push(105);
	push(52);
	push(21);
	push(11);
	push(5);
	push(2);
	push(1);
	push(14602);
	push(16941);
	push(18021);
	push(18609);
	push(18883);
	push(19224);
	push(19348);
	push(19471);
	push(19533);
	push(19557);
	push(19562);
	push(19570);
}
bin_tree::~bin_tree() {				//destructor hehe

}
void bin_tree::push(int a) {		//adding new bin_node by hash
	std::shared_ptr<bin_node> temp = head;
	while (true) {
		int hash = temp->link->hash;
		if (a < hash) {
			if (temp->left == nullptr) {
				temp->left = std::make_shared<bin_node>(a);
				return;
			}
			else temp = temp->left;
		}
		else if (a > hash) {
			if (temp->right == nullptr) {
				temp->right = std::make_shared<bin_node>(a);
				return;
			}
			else temp = temp->right;
		}
		else return;
	}
}
void bin_tree::push(std::string s) {	//adding new bin_node by string
	int a = find_hash(s);
	std::shared_ptr<bin_node> temp = head;
	while (true) {
		if (a < temp->link->hash) {
			if (temp->left == nullptr) {
				temp->left = std::make_shared<bin_node>(a);
				return;
			}
			else temp = temp->left;
		}
		else if (a > temp->link->hash) {
			if (temp->right == nullptr) {
				temp->right = std::make_shared<bin_node>(a);
				return;
			}
			else temp = temp->right;
		}
		else return;
	}
}
std::shared_ptr<Node> bin_tree::get_link(int a) {	//adding new bin_node by hash
	std::shared_ptr<bin_node> temp = head;
	while (true) {
		if (a < temp->link->hash) {
			if (temp->left == nullptr) {
				temp->left = std::make_shared<bin_node>(a);
				return temp->left->link;
			}
			else temp = temp->left;
		}
		else if (a > temp->link->hash) {
			if (temp->right == nullptr) {
				temp->right = std::make_shared<bin_node>(a);
				return temp->right->link;
			}
			else temp = temp->right;
		}
		else {
			return temp->link;
		}
	}
}
std::shared_ptr<Node> bin_tree::get_link(std::string s) {	//get a link to a Node by string
	int a = find_hash(s);
	std::shared_ptr<bin_node> temp = head;
	while (true) {
		if (a < temp->link->hash) {
			if (temp->left == nullptr) {
				temp->left = std::make_shared<bin_node>(a);
				return temp->left->link;
			}
			else temp = temp->left;
		}
		else if (a > temp->link->hash) {
			if (temp->right == nullptr) {
				temp->right = std::make_shared<bin_node>(a);
				return temp->right->link;
			}
			else temp = temp->right;
		}
		else {
			return temp->link;
		}
	}
}