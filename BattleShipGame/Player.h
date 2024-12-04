#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>

class Player {
private:
    std::string name;
    int hitsCount; // Counter for successful hits

public:
    Player(const std::string& playerName);
    Board board;
    void placeShips();
    bool attack(Player& opponent, int x, int y);
    bool hasShipsLeft() const;
    void displayBoard(bool showShips) const;
    const std::string& getName() const;
    int getHitsCount() const;

    const Board& getBoard() const; // Function to access the board
};

#endif // PLAYER_H
