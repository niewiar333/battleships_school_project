#include "Player.h"
#include <iostream>
#include <limits>

using namespace std;

Player::Player(const string& playerName) : name(playerName), board(), hitsCount(0) {}

void Player::placeShips() {
    cout << "\n" << name << ", it's your turn to place your ships.\n";
    cout << "Here is your empty board:\n";
    board.display(true); // Display empty board before placing any ships

    int shipSizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for (int size : shipSizes) {
        bool placed = false;
        while (!placed) {
            cout << "\n" << name << ", please place a ship of size " << size 
                      << " (format: x y orientation [H/V]): ";
            int x, y;
            char orientation;

            if (!(cin >> x >> y >> orientation)) {
                cout << "Invalid input. Please enter numbers for coordinates and H/V for orientation.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (orientation != 'H' && orientation != 'V') {
                cout << "Invalid orientation. Please use 'H' for horizontal or 'V' for vertical.\n";
                continue;
            }

            placed = board.placeShip(x, y, size, orientation);
            if (!placed) {
                cout << "Invalid placement. Make sure the ship fits and does not touch other ships. Try again.\n";
            } else {
                cout << "\nHere's your current board after placing the ship:\n";
                board.display(true); // Display board with the new ship
            }
        }
    }
    cout << "\n" << name << ", you have placed all your ships!\n";
}

bool Player::attack(Player& opponent, int x, int y) {
    bool hit = opponent.board.attack(x, y);
    if (hit) {
        cout << "You hit an enemy ship at (" << x << ", " << y << ")!\n";
        hitsCount++;

        if (opponent.board.isShipSunk(x, y)) {
            cout << "You sunk an enemy ship!\n";
        }
    } else {
        cout << "Missed at (" << x << ", " << y << ").\n";
    }

    return hit;
}

bool Player::hasShipsLeft() const {
    return board.hasShipsLeft();
}

void Player::displayBoard(bool showShips) const {
    board.display(showShips);
}

const string& Player::getName() const {
    return name;
}

int Player::getHitsCount() const {
    return hitsCount;
}

const Board& Player::getBoard() const {
    return board; // Provide access to the private board
}
