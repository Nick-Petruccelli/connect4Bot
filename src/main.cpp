#include "../inc/board.hpp"
#include <iostream>

const int BOARDWIDTH = 7;
const int BOARDHIGHT = 6;

int main() {
  Board board(BOARDWIDTH, BOARDHIGHT);
  bool playing = true;
  bool playerOne = true;
  while (playing) {
    board.printBoard();

    int col;
    std::cout << "Player 1 enter your row. (0-6)" << std::endl;
    std::cin >> col;
    while (!std::cin) {
      if (col < 0 || col > BOARDWIDTH) {
        std::cout << "You did not enter a valid column try again." << std::endl;
      } else {
        std::cout << "You did not enter a number try again." << std::endl;
      }
    }
    board.placeToken(col, playerOne);
    playerOne = false;

    std::cout << "Player 2 enter your row. (0-6)" << std::endl;
    std::cin >> col;
    while (!std::cin) {
      if (col < 0 || col > BOARDWIDTH) {
        std::cout << "You did not enter a valid column try again." << std::endl;
      } else {
        std::cout << "You did not enter a number try again." << std::endl;
      }
    }
    board.placeToken(col, playerOne);
    playerOne = true;
  }
}
