#include "Ship.h"

Ship::Ship(int shipSize) : size(shipSize), hits(0) {}

void Ship::hit() {
    if (hits < size) {
        hits++;
    }
}

bool Ship::isSunk() const {
    return hits >= size;
}
