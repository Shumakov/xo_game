#pragma once
#include <string>
class Player
{
private:
    char symbol;
    std::string name;

public:
    Player(char sym, const std::string& n) : symbol(sym), name(n) {}

    char getSymbol() const { return symbol; }
    std::string getName() const { return name; }
};

