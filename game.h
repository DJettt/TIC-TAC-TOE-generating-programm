#pragma once
#include "AI.h"
class game {
private:
	std::shared_ptr<Node> start_board;	
public:
	game();							
	~game();							
	void start_game();					
	void game_player_player();			
	void game_AI_player();				
	void game_AI_AI();					
};