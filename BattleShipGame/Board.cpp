#include "Board.h"

using namespace std;

Board::Board() : shipsRemaining(10), grid(10, vector<Cell>(10)) {}

bool Board::placeShip(int x, int y, int size, char orientation) {
    if (orientation == 'H') {
        if (x < 0 || x >= 10 || y < 0 || (y + size) > 10) return false;

        for (int i = 0; i < size; ++i) {
            if (grid[x][y + i].hasShip) return false;
        }
        for (int i = -1; i <= size; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + j, ny = y + i;
                if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && grid[nx][ny].hasShip) return false;
            }
        }

        for (int i = 0; i < size; ++i) {
            grid[x][y + i].hasShip = true;
        }
    } else if (orientation == 'V') {
        if (x < 0 || (x + size) > 10 || y < 0 || y >= 10) return false;

        for (int i = 0; i < size; ++i) {
            if (grid[x + i][y].hasShip) return false;
        }
        for (int i = -1; i <= size; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + i, ny = y + j;
                if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && grid[nx][ny].hasShip) return false;
            }
        }

        for (int i = 0; i < size; ++i) {
            grid[x + i][y].hasShip = true;
        }
    } else {
        return false;
    }

    return true;
}

bool Board::attack(int x, int y) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
    if (grid[x][y].isHit) return false;

    grid[x][y].isHit = true;
    if (grid[x][y].hasShip) {
        --shipsRemaining;
        return true;
    }
    return false;
}

bool Board::hasShipsLeft() const {
    return shipsRemaining > 0;
}

bool Board::isShipSunk(int x, int y) const {
    if (!grid[x][y].hasShip) return false;

    for (int i = x; i >= 0 && grid[i][y].hasShip; --i) {
        if (!grid[i][y].isHit) return false;
    }
    for (int i = x + 1; i < 10 && grid[i][y].hasShip; ++i) {
        if (!grid[i][y].isHit) return false;
    }

    for (int j = y; j >= 0 && grid[x][j].hasShip; --j) {
        if (!grid[x][j].isHit) return false;
    }
    for (int j = y + 1; j < 10 && grid[x][j].hasShip; ++j) {
        if (!grid[x][j].isHit) return false;
    }

    return true;
}

void Board::display(bool showShips) const {
    cout << "   ";
    for (int j = 0; j < 10; ++j) {
        cout << j << " ";
    }
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        cout << i << "  ";
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j].isHit) {
                cout << (grid[i][j].hasShip ? "X " : "O ");
            } else if (showShips && grid[i][j].hasShip) {
                cout << "S ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}
