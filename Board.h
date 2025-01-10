#pragma once
#include <vector>
class Board
{
private:
    std::vector<std::vector<char>> grid;
    int size;

public:
    Board(int n) : size(n), grid(n, std::vector<char>(n, ' ')) {}

    void display() const;

    bool makeMove(int row, int col, char symbol);

    bool checkWin(int row, int col, char symbol) const;

    bool isFull() const;
};

