#include "game_tree.h"
#include <fstream>
game_tree::game_tree() {	//constructor
	if (file_empty("game_tree.txt") == true) {
		fill();
	}
};

game_tree::~game_tree() {	//destructor

}

void game_tree::generation(std::string& s, bin_tree& hash_tree) {	//RECURSIVELY generating new Nodes and connecting them with fathers
	int countOne = 0, countTwo = 0;
	char next;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '1') countOne++;
		if (s[i] == '2') countTwo++;
	}
	if (countOne > countTwo) next = '2';
	else next = '1';
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '.') {
			std::string a = s;
			a[i] = next;
			std::shared_ptr<Node> nodeA = hash_tree.get_link(a);
			std::shared_ptr<Node> nodeS = hash_tree.get_link(s);
			nodeS->push_son(nodeA);
			if (nodeA->situation == 'N' && !nodeA->sons_created) {
				nodeA->sons_created = true;
				generation(a, hash_tree);
			}
		}
	}
}

XON game_tree::harvester(std::shared_ptr<Node> a) {	//RECURSIVELY harvesting all XON from down to up inside the tree
	char w = a->situation;
	if (w == '1') {
		a->Moves = { 0, 20, 20 };
		return { 1,0,0 };
	}
	else if (w == '2') {
		a->Moves = { 20, 0, 20 };
		return { 0,1,0 };
	}
	else if (w == 'S') {
		a->Moves = { 20, 20, 0 };
		return { 0,0,1 };
	}
	else if (!(a->win_first == 0 && a->win_second == 0 && a->win_no_one == 0))
		return { a->win_first, a->win_second, a->win_no_one };
	for (size_t i = 0; i < 9; i++) {
		if (a->game_sons[i] == nullptr)
			break;
		XON helper = harvester(a->game_sons[i]);
		a->win_first += helper.frist;
		a->win_second += helper.second;
		a->win_no_one += helper.no_one;
		a->Moves.Move0 = std::min(a->Moves.Move0, a->game_sons[i]->Moves.Move0 + 1);				
		a->Moves.Move1 = std::min(a->Moves.Move1, a->game_sons[i]->Moves.Move1 + 1);
		a->Moves.Move2 = std::min(a->Moves.Move2, a->game_sons[i]->Moves.Move2 + 1);
	}
	a->get_next_hashes();
	return { a->win_first, a->win_second, a->win_no_one };
}
void game_tree::fill() {	//creating the game tree and calling the generation function
	bin_tree hash_tree;
	std::string s = ".........";
	root = hash_tree.get_link(s);
	generation(s, hash_tree);
	XON check = harvester(root);
	save("game_tree.txt");
	return;
}

void game_tree::save(const std::string& filename) {	//RECURSIVELY uploading all information to txt file
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cout<< "не удалось открыть файл" << std::endl;
		return;
	}
	save_nodes(root, file);
	file.close();
}

void game_tree::save_nodes(std::shared_ptr<Node> node, std::ofstream& file) {	//RECURSIVELY saving all Nodes to txt file
	file << node->hash << ":  " << node->next_hashes.hash1 << " " << node->next_hashes.hash2 << " " << node->next_hashes.hash0 << '\n';
	for (int i = 0; i < 9; i++) {
		if (node->game_sons[i] != nullptr && node->game_sons[i]->soon_save == false) save_nodes(node->game_sons[i], file);
	}
	node->soon_save = true;
}
bool game_tree::file_empty(const std::string& filename) {	//checking is txt file empty
	std::ifstream file(filename);
	if (!file.good()) {
		std::ofstream new_file(filename);
		return true; //the file created
	}
	// checking is the file empty
	return file.peek() == std::ifstream::traits_type::eof();
}