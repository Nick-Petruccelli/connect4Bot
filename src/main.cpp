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
    while (true) {
      std::cin >> col;
      if (col < 0 || col >= BOARDWIDTH) {
        std::cout << "You did not enter a valid column try again." << std::endl;
      } else if (board.getColHeight(col) < 0) {
        std::cout << "The column you entered is full try again." << std::endl;
      } else if (!std::cin) {
        std::cout << "You did not enter a number try again." << std::endl;
      } else {
        break;
      }
    }
    std::cout << board.getColHeight(col) << std::endl;
    board.placeToken(col, playerOne);
    playerOne = false;
    board.printBoard();

    std::cout << "Player 2 enter your row. (0-6)" << std::endl;
    while (true) {
      std::cin >> col;
      if (col < 0 || col >= BOARDWIDTH) {
        std::cout << "You did not enter a valid column try again." << std::endl;
      } else if (board.getColHeight(col) < 0) {
        std::cout << "The column you entered is full try again." << std::endl;
      } else if (!std::cin) {
        std::cout << "You did not enter a number try again." << std::endl;
      } else {
        break;
      }
    }
    board.placeToken(col, playerOne);
    playerOne = true;
  }
}
