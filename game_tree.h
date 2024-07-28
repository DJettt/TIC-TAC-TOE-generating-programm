#pragma once
#include "bin_tree.h"
struct XON {															//Support structure. Due to it, the probability will be calculated.
	int frist;															//the number of 1st player wins under the Node
	int second;															//the number of 2nd player wins under the Node
	int no_one;															//the number os draws under this Node
};
class game_tree {														//the tree of Tic-tac-toe
public:
	std::shared_ptr<Node> root;											//root of the game (empty board)

	game_tree();														//constructor
	~game_tree();														//destructor

	void generation(std::string& s, bin_tree& hash_array);				//RECURSIVELY generating new Nodes and connecting them with fathers
	XON harvester(std::shared_ptr<Node> a);								//RECURSIVELY harvesting all XON from down to up inside the tree
	void fill();														//creating the game tree and calling the generation function
	void save(const std::string& filename);								//RECURSIVELY uploading all information to txt file
	void save_nodes(std::shared_ptr<Node> node, std::ofstream& file);	//RECURSIVELY saving all Nodes to txt file
	bool file_empty(const std::string &filename);						//checking is txt file empty
};