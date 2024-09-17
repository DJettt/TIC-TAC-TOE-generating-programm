#include "AI.h"
#include <fstream>
#include <random>

AI::AI(std::string filename,std::string name,  char complexity): filename(filename), name(name),  complexity(complexity){}

int AI::AI_move(std::string game_board) {

    int hash = find_hash(game_board);
    int hashf;
    int pos1;
    std::string line;
    std::ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            pos1 = line.find(':');
            hashf = stoi(line.substr(0, pos1));
            if (hash == hashf) {
                break;
            }
        }
        int hash_1;
        int hash_0;
        int hash_2;
        int pos2 = line.find(' ', pos1 + 3);
        hash_1 = stoi(line.substr(pos1 + 3, pos2 - pos1 - 2));
        int pos3 = line.find(' ', pos2 + 1);
        hash_2 = stoi(line.substr(pos2, pos3 - pos2));
        hash_0 = stoi(line.substr(pos3 + 1));
        switch (complexity)
        {
        case '1':
            return hash_1;
            break;
        case '2':
            return hash_0;
            break;
        case '3':
            return hash_2;
            break;
        case '4':
            std::string s = find_board(hash);
            int count1 = 0, count2 = 0;
            char w;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '1') count1++;
                if (s[i] == '2') count2++;
            }
            if (count1 == count2) w = '1';
            else w = '2';
            int count = 0;
            for (size_t i = 0; i < s.size(); i++) {
                if (s[i] == '.') count++;
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, count-1);
            int random = dist(gen);
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '.')
                    if (random == 0) {
                        s[i] = w;
                        break;
                    }
                    else random--;
            }
            return find_hash(s);
            break;
        }
    }
}