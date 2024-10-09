#include "../inc/board.hpp"
#include <cstdlib>
#include <iostream>

Board::Board(int width, int height) {
  mBoardWidth = width;
  mBoardHeight = height;
  mBoard = (int *)malloc(width * height * sizeof(int));
}

Board::~Board() { free(mBoard); }

int Board::getColHeight(int col) {
  for (int height = 0; height < mBoardHeight; height++) {
    if (mBoard[(height * mBoardWidth) + col] == 0) {
      return height;
    }
  }
  return -1;
}

void Board::placeToken(int col, bool player) {
  int height = getColHeight(col);
  mBoard[(height * mBoardWidth) + col] = player ? 1 : -1;
}

void Board::printBoard() {
  for (int r = mBoardHeight - 1; r >= 0; r--) {
    for (int c = 0; c < mBoardWidth; c++) {
      std::cout << "| " << mBoard[(r * mBoardWidth) + c] << " ";
    }
    std::cout << "|" << std::endl;
    for (int i = 0; i < mBoardWidth * 4 + 1; i++) {
      std::cout << "-";
    }
    std::cout << std::endl;
  }
}
