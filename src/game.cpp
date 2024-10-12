#include "../inc/game.hpp"
#include "../inc/abSearch.hpp"
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
  ABSearch ai(BOARDWIDTH, BOARDHEIGHT);
  ai.generateTree();
  std::cout << "Tree Ptr: " << ai.getTree() << std::endl;
  std::cout << "Tree Children Ptr: " << ai.getTree()->getChildren()->size()
            << std::endl;
  /*
  ai.printTree();
  std::cout << "--------------" << std::endl;
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      std::cout << ai.getTree()->getChildren()->at(i)->getChildren()->at(j)
                << std::endl;
    }
  }
  std::cout << "--------------" << std::endl;
  */

  int move;
  move = ai.getNextMove();
  while (running) {
    mBoard.printBoard();
    int util = ai.getTree()->getUtility();
    std::cout << util << std::endl;
    move = takeInput(player);
    if (mMultiplayer)
      ai.applyMove(move);

    player = 2;
    mBoard.printBoard();
    util = ai.getTree()->getUtility();
    std::cout << util << std::endl;
    winner = mBoard.checkWin();
    if (winner != 0) {
      mBoard.printBoard();
      std::cout << "Player" << winner << "wins!!!" << std::endl;
      break;
    }

    if (mMultiplayer) {
      takeInput(player);
    } else {
      getAIMove(ai, player);
    }
    player = 1;
    winner = mBoard.checkWin();
    if (winner != 0) {
      mBoard.printBoard();
      std::cout << "Player" << winner << "wins!!!" << std::endl;
      break;
    }
  }
}

int Game::getAIMove(ABSearch ai, int player) {
  int col = ai.getNextMove();
  mBoard.placeToken(col, player);
  ai.applyMove(col);
  return col;
}

int Game::takeInput(int player) {
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
  return col;
}
