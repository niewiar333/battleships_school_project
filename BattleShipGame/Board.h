#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

struct Cell {
    bool hasShip;
    bool isHit;

    Cell() : hasShip(false), isHit(false) {}
};

class Board {
private:
    std::vector<std::vector<Cell>> grid;
    int shipsRemaining;

public:
    Board();

    bool placeShip(int x, int y, int size, char orientation);
    bool attack(int x, int y);
    bool hasShipsLeft() const;
    bool isShipSunk(int x, int y) const;
    void display(bool showShips) const;
};

#endif // BOARD_H
