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
        players.emplace_back('X', "Игрок 1");
        players.emplace_back('O', "Игрок 2");
    }

    void play() {
        // Основной игровой цикл
    }
};

