#pragma once
#include "game_tree.h"
class AI {
private:
	std::string name;				
	std::string filename;			
	char complexity;				
	
public:
	std::string GetName() { return name; };					
	AI(std::string filename, std::string name, char complexity);
	int AI_move(std::string game_board);							
};