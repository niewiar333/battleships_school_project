#ifndef SHIP_H
#define SHIP_H

class Ship {
private:
    int size;
    int hits;

public:
    Ship(int shipSize);
    void hit();
    bool isSunk() const;
};

#endif // SHIP_H
