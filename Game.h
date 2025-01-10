#pragma once
#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"

class Game
{
	std::string name;
	Board board;
	std::vector<Player> players;
	int currentPlayerIndex;

public:
    Game(int size) : board(size), currentPlayerIndex(0) {
        players.emplace_back('X', "����� 1");
        players.emplace_back('O', "����� 2");
    }

    void play() {
        // �������� ������� ����
    }
};

