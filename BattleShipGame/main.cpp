#include "Player.h"
#include <iostream>
#include <limits> // for cin.ignore

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayLegend() {
    cout << "Legend:\n";
    cout << "  . - Empty cell\n";
    cout << "  S - Ship (only visible on your board)\n";
    cout << "  X - Hit ship\n";
    cout << "  O - Missed shot\n";
    cout << "\n";
}

void waitForNextTurn() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter
}

void endGame(const string& winnerName) {
    clearScreen();
    cout << "Congratulations, " << winnerName << "! You win the game!\n";
    cout << "Press Enter to end the game...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    cout << "Welcome to Battleship!\n";

    cout << "Enter Player 1 name: ";
    string player1Name;
    cin >> player1Name;

    cout << "Enter Player 2 name: ";
    string player2Name;
    cin >> player2Name;

    Player player1(player1Name);
    Player player2(player2Name);

    cout << player1Name << ", place your ships.\n";
    player1.placeShips();

    clearScreen();
    cout << player2Name << ", place your ships.\n";
    player2.placeShips();

    clearScreen();
    cout << "The ships are placed! Let's start the game.\n";

    bool gameRunning = true;
    Player* currentPlayer = &player1;
    Player* opponent = &player2;

    // Ensure the input buffer is cleared after reading player names
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (gameRunning) {
        clearScreen();
        displayLegend();

        // Display both boards
        cout << currentPlayer->getName() << "'s view:\n";
        cout << "Your board:\n";
        currentPlayer->displayBoard(true); // Display player's own board with ships
        cout << "\nOpponent's board:\n";
        opponent->displayBoard(false); // Display opponent's board without showing ships

        // Take the shot
        int x, y;
        cout << "Enter attack coordinates (x y): ";
        cin >> x >> y;

        // Clear the input buffer after reading coordinates
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool hit = currentPlayer->attack(*opponent, x, y);

        // Feedback for the shot
        if (hit) {
            cout << "You hit an enemy ship!\n";
            if (opponent->board.isShipSunk(x, y)) { // Check if the ship was sunk
                cout << "You sunk an enemy ship!\n";
            }
        } else {
            cout << "You missed.\n";
        }

        // Wait for player to press Enter
        waitForNextTurn();

        // Check win condition
        if (!opponent->hasShipsLeft()) {
            endGame(currentPlayer->getName()); // Display endgame screen
            gameRunning = false;
        } else {
            swap(currentPlayer, opponent);
        }
    }

    return 0;
}
