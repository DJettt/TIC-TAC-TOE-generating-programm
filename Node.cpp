#include "Node.h"
Node::Node() { //constructor
	board = "";
	hash = -1;
	situation = 'N';
	next_step = find_next_step();
	for (int i = 0; i < 9; i++)
		game_sons[i] = NULL;
}
Node::Node(std::string s) { //constructor by a string
	board = s;
	hash = find_hash(s);
	situation = current_situation();
	next_step = find_next_step();
	for (int i = 0; i < 9; i++)
		game_sons[i] = NULL;
}
Node::Node(int a) { //constructor by a hash
	hash = a;
	board = find_board(a);
	next_step = find_next_step();
	situation = current_situation();
	for (int i = 0; i < 9; i++)
		game_sons[i] = NULL;
}
Node::~Node() {
	for (size_t i = 0; i < 9; i++) {
		if (game_sons[i] != nullptr) {
			game_sons[i].reset(); //deleting smart pointer and cleaning of memory
		}
		else break;
	}
}
void Node::push_son(std::shared_ptr<Node> a) { //adding a son
	for (int i = 0; i < 9; i++) {
		if (game_sons[i] == a)
			return;
		if (game_sons[i] == nullptr) {
			game_sons[i] = a;
			return;
		}
	}
}
char Node::current_situation() { //check for current situation
	/*
		X - 1st player won
		O - 2nd player won
		N - the game didn't end
		S - draw
	*/
	/*
	*	012345678
	*	012
	*	345
	*	678
	*/
	if (board.empty()) return 'S';
	if (board[0] == board[1] && board[1] == board[2])
		if (board[0] == '1') return '1';
		else if (board[0] == '2') return '2';
	if (board[3] == board[4] && board[3] == board[5])
		if (board[3] == '1') return '1';
		else if (board[3] == '2') return '2';
	if (board[6] == board[7] && board[6] == board[8])
		if (board[6] == '1') return '1';
		else if (board[6] == '2') return '2';
	if (board[0] == board[3] && board[0] == board[6])
		if (board[0] == '1') return '1';
		else if (board[0] == '2') return '2';
	if (board[1] == board[4] && board[1] == board[7])
		if (board[1] == '1') return '1';
		else if (board[1] == '2') return '2';
	if (board[2] == board[5] && board[2] == board[8])
		if (board[2] == '1') return '1';
		else if (board[2] == '2') return '2';
	if (board[0] == board[4] && board[0] == board[8])
		if (board[0] == '1') return '1';
		else if (board[0] == '2') return '2';
	if (board[2] == board[4] && board[2] == board[6])
		if (board[2] == '1') return '1';
		else if (board[2] == '2') return '2';
	for (size_t i = 0; i < board.size(); i++) {		//check for empty cells
		if (board[i] == '.')
			return 'N';
	}
	return 'S';
}
char Node::find_next_step() { //returns who must go next by the string
	if (board.empty()) return '1';
	int countX = 0, countO = 0;
	for (int i = 0; i < board.size(); i++) {
		if (board[i] == '1') countX++;
		if (board[i] == '2') countO++;
	}
	if (countX == countO) return '1';
	else return '2';
}
std::string Node::get_board() { return board; }
void Node::show_board(char first_simbol, char second_symbol) { //show the board in console
	for (int i = 0; i < board.size(); i++) {
		if (i == 3 || i == 6 || i == 9) std::cout << '\n';
		if (board[i] == '1') std::cout << first_simbol << ' ';
		if (board[i] == '2') std::cout << second_symbol << ' ';
		if (board[i] == '.') std::cout << board[i] << ' ';
	}
	std::cout << "\n";
	return;
}
bool Node::double_win(std::shared_ptr<Node> &a) {		//returns does 1st player have a forced win strategy
	for (std::shared_ptr<Node>& A : a->game_sons) {		// for (int i = 0; i < 9; i++)
		if (A != nullptr && a->next_hashes.hash1 == A->hash) {
			for (std::shared_ptr<Node>& B : A->game_sons) {
				if (B != nullptr && A->next_hashes.hash2 == B->hash) {
					for (std::shared_ptr<Node>& C : B->game_sons) {
						if (C != nullptr && B->next_hashes.hash1 == C->hash) {
							return C->situation == '1';
						}
					}
				}
			}
		}
	}
	return false;
}
void Node::get_next_hashes() {		//creating of profitable hashes
	double prob1 = -1., prob2 = -1., prob0 = -1.;
	for (int i = 0; i < 9; i++) {
		if (game_sons[i] != nullptr) {
			double all = game_sons[i]->win_first + game_sons[i]->win_second + game_sons[i]->win_no_one;
			if (all != 0.) {
				double prob_son_first = (double)game_sons[i]->win_first / all;
				double prob_son_second = (double)game_sons[i]->win_second / all;
				double prob_son_no_one = (double)game_sons[i]->win_no_one / all;
				if (prob_son_first > prob1 && game_sons[i]->Moves.Move2 != 1) {
					prob1 = prob_son_first;
					next_hashes.hash1 = game_sons[i]->hash;
				}
				if (prob_son_second > prob2 && game_sons[i]->Moves.Move1 != 1) {
					if (Moves.Move1 == 4) { //next_step == '2'
						if (!double_win(game_sons[i])) {
							prob2 = prob_son_second;
							next_hashes.hash2 = game_sons[i]->hash;
						}
					}
					else {
						prob2 = prob_son_second;
						next_hashes.hash2 = game_sons[i]->hash;
					}
				}
				if (prob_son_no_one > prob0) {
					if (next_step == '1' && game_sons[i]->Moves.Move2 != 1) {
						prob0 = prob_son_no_one;
						next_hashes.hash0 = game_sons[i]->hash;
					}
					else if (next_step == '2' && game_sons[i]->Moves.Move1 != 1) {
						prob0 = prob_son_no_one;
						next_hashes.hash0 = game_sons[i]->hash;
					}
				}
			}
			else {
				if (game_sons[i]->situation == '1') {
					prob1 = 1.;
					next_hashes.hash1 = game_sons[i]->hash;
				}
				else if (game_sons[i]->situation == '2') {
					prob2 = 1.;
					next_hashes.hash2 = game_sons[i]->hash;
				}
				else if (game_sons[i]->situation == 'S') {
					prob0 = 1.;
					next_hashes.hash0 = game_sons[i]->hash;
				}
				else std::cout << "Error: Node.cpp line:175 ";
			}
		}
		else {
			if (next_hashes.hash0 == -1 && next_hashes.hash1 == -1 && next_hashes.hash2 != -1) { //last move situation
				next_hashes.hash0 = next_hashes.hash2;
				next_hashes.hash1 = next_hashes.hash2;
			}
			if (next_hashes.hash1 == -1 && next_hashes.hash2 == -1 && next_hashes.hash0 != -1) {
				next_hashes.hash1 = next_hashes.hash0;
				next_hashes.hash2 = next_hashes.hash0;
			}
			if (next_hashes.hash0 == -1 && next_hashes.hash2 == -1 && next_hashes.hash1 != -1) {
				next_hashes.hash0 = next_hashes.hash1;
				next_hashes.hash2 = next_hashes.hash1;
			}
			if (next_step == '1' && next_hashes.hash0 == -1)
				next_hashes.hash0 = next_hashes.hash1;
			if (next_step == '2' && next_hashes.hash0 == -1)
				next_hashes.hash0 = next_hashes.hash2;
			return;
		}
	}
	return;
}