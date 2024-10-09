#include "../inc/game.hpp"
#include <iostream>
#include <limits>

const int BOARDWIDTH = 7;
const int BOARDHEIGHT = 6;

Game::Game(bool multiplayer) : mBoard(BOARDWIDTH, BOARDHEIGHT) {
  mMultiplayer = multiplayer;
}

void Game::startGame() {
  bool running = true;
  int player = 1;
  int winner = 0;
  mBoard.printBoard();
  while (running) {
    takeInput(player);
    player = 2;
    mBoard.printBoard();
    winner = mBoard.checkWin();
    if (winner != 0) {
      std::cout << "Player" << winner << "wins!!!" << std::endl;
      break;
    }

    takeInput(player);
    player = 1;
    winner = mBoard.checkWin();
    if (winner != 0) {
      std::cout << "Player" << winner << "wins!!!" << std::endl;
      break;
    }
    mBoard.printBoard();
  }
}

void Game::takeInput(int player) {
  int col;
  std::cout << "Player" << player << " enter your row. (1-7)" << std::endl;
  while (true) {
    std::cin >> col;
    if (!std::cin) {
      std::cout << "You did not enter a number try again." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    col--;
    if (col < 0 || col >= BOARDWIDTH) {
      std::cout << "You did not enter a valid column try again." << std::endl;
    } else if (mBoard.getColHeight(col) < 0) {
      std::cout << "The column you entered is full try again." << std::endl;
    } else {
      break;
    }
  }
  mBoard.placeToken(col, player);
}
