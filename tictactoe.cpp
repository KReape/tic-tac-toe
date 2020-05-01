// Code written by Kateri Reape on 9/13/19, updated on 3/22/20

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const size_t SPOTS = 9;
void game(); // runs the game

class Board {
public:
  // constructor
  Board() {resetBoard();}

  // accessors
  void currentBoard(); // returns the current game board
  size_t countFreeSpots(); // goes through claim and finds free spots
  size_t findFreeSpot(); // returns an optimal free spot on the board
  bool gameIsWon(); // returns true if there are 3 of any symbol in a row

  // mutators
  bool placeSymbol(char symbol, size_t spotOnBoard); // returns true if the symbol was correctly placed
  void resetBoard(); // resets the board so that another game may be played
private:
  // each element is either a number, an 'X', or an 'O'
  char place[SPOTS];
  // each element set to true if the corresponding spot on the board is claimed
  bool claim[SPOTS];
};

int main() {
  game();
  return 0;
}

void game() {
  Board tictactoe;
  bool continueGame = true;
  size_t numPlayers; // either 1 or 2
  size_t whereToPlace;
  char winningSymbol;
  char playAgain;
  while (continueGame) {
    tictactoe.resetBoard();
    cout << "1 or 2 players? (1/2)" << endl;
    cin >> numPlayers;
    if (numPlayers == 1) {
      while (tictactoe.countFreeSpots() > 0) { // true if there are free spots
        tictactoe.currentBoard();
        cout << "Please choose where to place your X." << endl;
        cin >> whereToPlace;
        tictactoe.placeSymbol('X', whereToPlace); // places an 'X' in the spot corresponding to the number
        if (tictactoe.gameIsWon() == true) { // if the game is won here, 'X' wins
          winningSymbol = 'X';
          break;
        } else if (tictactoe.countFreeSpots() == 0) { // if board is full
          break;
        }

        tictactoe.placeSymbol('O', tictactoe.findFreeSpot()); // places an 'O' in a random spot
        if (tictactoe.gameIsWon() == true) { // if the game is won here, 'O' wins
          winningSymbol = 'O';
          break;
        } else if (tictactoe.countFreeSpots() == 0) { // if board is full
          break;
        }
      }

      tictactoe.currentBoard();
      if (!tictactoe.gameIsWon()) { // true if board is full but win condition is not satisfied
        cout << "It's a tie!";
      } else {
        cout << winningSymbol << "\'s won!";
      }
      cout << " Would you like to play again? (y/n)" << endl;
      cin >> playAgain;
      if (tolower(playAgain) == 'y') { // allows the user to continue playing
        continue;
      } else { // ends the game
        break;
      }
    } else if (numPlayers == 2) {
      while (tictactoe.countFreeSpots() > 0) { // true if there are free spots
        tictactoe.currentBoard();
        cout << "Please choose where to place your X." << endl;
        cin >> whereToPlace;
        tictactoe.placeSymbol('X', whereToPlace); // places an 'X' in the spot corresponding to the number
        if (tictactoe.gameIsWon() == true) { // if the game is won here, 'X' wins
          winningSymbol = 'X';
          break;
        } else if (tictactoe.countFreeSpots() == 0) { // if board is full
          break;
        }

        tictactoe.currentBoard();
        cout << "Please choose where to place your O." << endl;
        cin >> whereToPlace;
        tictactoe.placeSymbol('O', whereToPlace); // places an 'O' in the spot corresponding to the number
        if (tictactoe.gameIsWon() == true) { // if the game is won here, 'O' wins
          winningSymbol = 'O';
          break;
        } else if (tictactoe.countFreeSpots() == 0) { // if board is full
          break;
        }
      }

      tictactoe.currentBoard();
      if (!tictactoe.gameIsWon()) { // true if board is full but win condition is not satisfied
        cout << "It's a tie!";
      } else {
        cout << winningSymbol << "\'s won!";
      }
      cout << " Would you like to play again? (y/n)" << endl;
      cin >> playAgain;
      if (tolower(playAgain) == 'y') { // allows the user to continue playing
        continue;
      } else { // ends the game
        break;
      }
    } else {
      cout << "Error: invalid input. Please try again." << endl;
      continue; // allows the user to try again if input is invalid
    }
  }
}

void Board::currentBoard() { // prints the current board
  cout << " ———————————" << endl;
  cout << "| " << place[0] << " | " << place[1] << " | " << place[2] << " |" << endl;
  cout << " ———————————" << endl;
  cout << "| " << place[3] << " | " << place[4] << " | " << place[5] << " |" << endl;
  cout << " ———————————" << endl;
  cout << "| " << place[6] << " | " << place[7] << " | " << place[8] << " |" << endl;
  cout << " ———————————" << endl;
}

size_t Board::countFreeSpots() { // counts the number of free spots
  size_t counter = 0;
  for (size_t i = 0; i < SPOTS; i++) {
    if (claim[i] == false) {
      counter++;
    }
  }
  return counter;
}

size_t Board::findFreeSpot() { // returns a free spot based on the state of the board
  srand(time(0));
  vector<size_t> free; // stores optimal, free spots
  free.clear();
  for (size_t i = 0; i < SPOTS; i++) {
    if (claim[i] == false) {
      switch (i) { // these are true if there are two symbols in one lane
        case 0: if ((claim[1] == true && place[1] == place[2]) ||
          (claim[3] == true && place[3] == place[6]) ||
          (claim[4] == true && place[4] == place[8])) {free.push_back(i);}
          break;
        case 1: if ((claim[0] == true && place[0] == place[2]) ||
          (claim[4] == true && place[4] == place[7])) {free.push_back(i);}
          break;
        case 2: if ((claim[0] == true && place[0] == place[1]) ||
          (claim[5] == true && place[5] == place[8]) ||
          (claim[4] == true && place[4] == place[6])) {free.push_back(i);}
          break;
        case 3: if ((claim[4] == true && place[4] == place[5]) ||
          (claim[0] == true && place[0] == place[6])) {free.push_back(i);}
          break;
        case 4: if ((claim[3] == true && place[3] == place[5]) ||
          (claim[1] == true && place[1] == place[7]) ||
          (claim[0] == true && place[0] == place[8]) ||
          (claim[2] == true && place[2] == place[6])) {free.push_back(i);}
          break;
        case 5: if ((claim[3] == true && place[3] == place[4]) ||
          (claim[2] == true && place[2] == place[8])) {free.push_back(i);}
          break;
        case 6: if ((claim[7] == true && place[7] == place[8]) ||
          (claim[0] == true && place[0] == place[3]) ||
          (claim[2] == true && place[2] == place[4])) {free.push_back(i);}
          break;
        case 7: if ((claim[6] == true && place[6] == place[8]) ||
          (claim[1] == true && place[1] == place[4])) {free.push_back(i);}
          break;
        case 8: if ((claim[6] == true && place[6] == place[7]) ||
          (claim[2] == true && place[2] == place[5]) ||
          (claim[0] == true && place[0] == place[4])) {free.push_back(i);}
          break;
      }
    }
  }
  if (free.empty()) { // if the above didn't find any critical spots, this chooses optimal spots
    if (claim[4] == false) { // tries the middle spot
      return 5;
    } else { // tries the corner spots
      for (int i = 0; i < SPOTS; i = i + 2) {
        if (claim[i] == false) {
          free.push_back(i);
        }
      }
    }
    if (free.empty()) { // tries the remaining edge spots
      for (size_t i = 1; i < SPOTS; i = i + 2) {
        if (claim[i] == false) {
          free.push_back(i);
        }
      }
    }
  }
  if (free.size() == 1) {
    return free[0] + 1; // returns the spot in free
  } else {
    size_t pick = rand() % free.size();
    return free[pick] + 1; // returns a random spot in free
  }
}

bool Board::gameIsWon() { // true if any win condition is satisfied
  if ((place[0] == place[1] && place[1] == place[2]) ||
  (place[3] == place[4] && place[4] == place[5]) ||
  (place[6] == place[7] && place[7] == place[8]) ||
  (place[0] == place[3] && place[3] == place[6]) ||
  (place[1] == place[4] && place[4] == place[7]) ||
  (place[2] == place[5] && place[5] == place[8]) ||
  (place[0] == place[4] && place[4] == place[8]) ||
  (place[2] == place[4] && place[4] == place[6])) {
    return true;
  } else {
    return false;
  }
}

bool Board::placeSymbol(char symbol, size_t spotOnBoard) { // puts an 'X' or an 'O' on the board
  if (!claim[spotOnBoard - 1]) {
    place[spotOnBoard - 1] = symbol;
    claim[spotOnBoard - 1] = true;
    return true;
  } else {
    return false;
  }
}

void Board::resetBoard() { // puts the board back in its original state
  for (size_t i = 0; i < 9; i++) {
    place[i] = i + '0' + 1;
    claim[i] = false;
  }
}
