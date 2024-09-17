#include "game.h"

game::game() {
	start_board = std::make_shared<Node>(".........");
}

game::~game() {
	//start_board->~Node();
}

void game::start_game() {
	std::cout << "Добро пожаловать в tic-tak-toe.\n";
	char flag;
	while (true) {
		std::cout << "Выберите режим этой игры\n 1 - игрок/игрок\n 2 - игрок/ИИ\n 3 - ИИ/ИИ\n";
		std::cin >> flag;
		if (flag == '1') game_player_player();
		if (flag == '2') game_AI_player();
		if (flag == '3') game_AI_AI();
		std::cout << "Хотите ли продолжить играть?\n 1 - да\n 0 - нет\n";
		std::cin >> flag;
		if (flag == '0') break;
        start_board->board = ".........";
        start_board->next_step = start_board->find_next_step();
	}
	return;
}

void game::game_player_player() {
	char first_symbol;
	char second_symbol;
	int position;
	std::cout << "Введите какими символами будут играть 1 и 2 игроки:";
	std::cin >> first_symbol >> second_symbol;
	for (int i = 0; i < 9; i++) {
		start_board->show_board(first_symbol, second_symbol);
		while (true) {
			std::cout << "0 1 2\n3 4 5\n6 7 8\nИгрок" << start_board->next_step << " ведите номер клетки, в которую хотите вствить символ : ";
			std::cin >> position;
			if ( position > 8 || position < 0 || start_board->board[position] != '.') {
				std::cout << "эта клетка занята или не корректна, попробуйте еще раз\n";
			}
			else break;
		}
		start_board->board[position] = start_board->next_step;
		if (start_board->current_situation() == '1'|| start_board->current_situation() == '2') {
			std::cout << "Игрок " << start_board->next_step << " победил!\n";
            start_board->show_board(first_symbol, second_symbol);
			break;
		}
		start_board->next_step = start_board->find_next_step();
	}
    if (start_board->current_situation() == 'S') {
        std::cout << "У вас ничья.\n";
        start_board->show_board(first_symbol, second_symbol);
    }
}
void game::game_AI_player() {
    char complexity;
    char first_symbol, second_symbol;
    int position;
    int AI_flag;

    std::cout << "Выберите сложность режима\n 1 - hard\n 2 - middle\n 3 - easy\n 4 - random\n";
    std::cin >> complexity;
    std::cin.ignore(); // Очищаем буфер ввода

    std::cout << "Вы хотите чтобы ИИ играл 1-ым\n 1 - да\n 0 - нет\n";
    std::cin >> AI_flag;

    if (AI_flag == 0) {
        if (complexity == '1') complexity = '3';
        else if (complexity == '3') complexity = '1';
    }
    AI player("game_tree.txt", "Frank", complexity);

    std::cout << "Введите какими символами будут играть 1 и 2 игроки:";
    std::cin >> first_symbol >> second_symbol;
    std::cin.ignore(); // Очищаем буфер ввода

    for (int i = 0; i < 9; i++) {
        start_board->show_board(first_symbol, second_symbol);
        if (AI_flag == 0) {

            while (true) {
                std::cout << "\n0 1 2\n3 4 5\n6 7 8\nИгрок" << start_board->next_step << " ведите номер клетки, в которую хотите вствить символ : ";
                std::cin >> position;
                std::cin.clear(); // Очищаем флаги ошибок
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
                if (position > 8 || position < 0 || start_board->board[position] != '.') {
                    std::cout << "эта клетка занята или не корректна, попробуйте еще раз\n";
                }
                else {
                    break;
                }
            }

            start_board->board[position] = start_board->next_step;
            AI_flag = 1;
        }
        else {
            if (AI_flag == 1 && start_board->current_situation() == 'N') {
                start_board->board = find_board(player.AI_move(start_board->board));
                std::cout << "Игрок "<< player.GetName() <<" сделал свой ход\n";
                AI_flag = 0;
            }
        }
        if (start_board->current_situation() == '1' || start_board->current_situation() == '2') {
            std::cout << "Игрок " << start_board->next_step << " победил!\n";
            start_board->show_board(first_symbol, second_symbol);
            break;
        }
        start_board->next_step = start_board->find_next_step();
    }
    if (start_board->current_situation() == 'S') {                                           
        std::cout << "У вас ничья.\n";
        start_board->show_board(first_symbol, second_symbol);
    }
}
void game::game_AI_AI() {
    char complexity1, complexity2;
    bool AI_flag = true;
    char first_symbol, second_symbol;
    std::cout << "Выберите сложность режима 1 ИИ\n 1 - hard\n 2 - middle\n 3 - easy\n 4 - random\n";
    std::cin >> complexity1;
    std::cin.ignore(); // Очищаем буфер ввода
    std::cout << "Выберите сложность режима 2 ИИ\n 1 - hard\n 2 - middle\n 3 - easy\n 4 - random\n";
    std::cin >> complexity2;
    std::cin.ignore(); 

    if (complexity2 == '1') complexity2 = '3';                                               
    else if (complexity2 == '3') complexity2 = '1';

    AI player1("game_tree.txt","Frank", complexity1);
    AI player2("game_tree.txt","Bob",  complexity2);

    std::cout << "Введите какими символами будут играть 1 и 2 игроки:";
    std::cin >> first_symbol >> second_symbol;
    std::cin.ignore(); // Очищаем буфер ввода

    for (int i = 0; i < 9; i++) {
        if (AI_flag == true) {
            start_board->show_board(first_symbol, second_symbol);
            if ( start_board->current_situation() != 'N') {
                break;
            }
            start_board->board = find_board(player1.AI_move(start_board->board));
            std::cout << "Игрок " << player1.GetName() << " сделал свой ход\n";
            AI_flag = false;
        }
        else {
            if (start_board->current_situation() != 'N' ) {
                break;
            }
            start_board->show_board(first_symbol, second_symbol);
            start_board->board = find_board(player2.AI_move(start_board->board));
            std::cout << "Игрок "<< player2.GetName() <<" сделал свой ход\n";
            AI_flag = true;
        }

        start_board->next_step = start_board->find_next_step();
    }
    if (start_board->current_situation() == '2') {
        std::cout << "Игрок " << player2.GetName() << " победил!\n";
        start_board->show_board(first_symbol, second_symbol);
    }
    if (start_board->current_situation() == '1') {
        std::cout << "Игрок " << player1.GetName() << " победил!\n";
        start_board->show_board(first_symbol, second_symbol);
    }
    if (start_board->current_situation() == 'S') {                   
        std::cout << "У вас ничья.\n";
        start_board->show_board(first_symbol, second_symbol);
    }
}