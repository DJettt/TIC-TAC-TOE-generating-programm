#pragma once
#include <string>
#include <iostream>
#include <memory>											//smart pointer's library

int power(int a, int b);									//exponentiation
int find_hash(std::string s);								//string -> hash
std::string find_board(int a);								//hash -> string

struct main_hashes {
	int hash1 = -1;
	int hash2 = -1;
	int hash0 = -1;
};

struct Move_end {
	int Move1 = 9;
	int Move2 = 9;
	int Move0 = 9;
};
class Node {  
public:
	int hash;												//hash of current position
	std::string board;										//current position
	char next_step;											//who's moving next
	char situation;											//current situation (is the game over) X - 1st player won, O - 2nd player won, N - the game didn't end, S - draw
	int win_first = 0;										//the number of wins of the 1st player under this node
	int win_second = 0;										//the number of wins of the 2snd player under this node
	int win_no_one = 0;										//the number of draws under this node
	bool sons_created = false;								//the flag on the created sons under this node
	bool soon_save = false;									//flag whether we have already saved this node in txt
	main_hashes next_hashes;								//hashes of profitable moves
	Move_end Moves;											//how many moves are left before the victory of the 1st, 2nd or draw (it is necessary for additional calculation of profitable hashes)
	std::shared_ptr<Node> game_sons[9];						//links to next nodes of moves


	Node();													//constructor
	Node(std::string s);									//constructor by string
	Node(int a);											//constructor by hash
	~Node();												//destructor

	void push_son(std::shared_ptr<Node> a);					//adding a son
	char find_next_step();									//returns who must go next
	char current_situation();								//check current situation
	std::string get_board();								//return the string of current board situation
	void show_board(char first_simbol, char second_symbol);	//show the board in console
	bool double_win(std::shared_ptr<Node> &a);				//returns does 1st player have a forced win strategy( true - yes, false - no)
	void get_next_hashes();									//creating of profitable hashes
};