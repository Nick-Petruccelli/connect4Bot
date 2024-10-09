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

int Board::checkWin() {
  bool win = false;
  for (int row = 0; row < mBoardHeight; row++) {
    for (int col = 0; col < mBoardWidth; col++) {
      win |= checkRight(row, col);
      win |= checkDiLeft(row, col);
      win |= checkUp(row, col);
      win |= checkDiRight(row, col);
      if (win)
        return mBoard[(row * mBoardWidth) + col];
    }
  }
  return 0;
}

bool Board::checkRight(int row, int col) {
  int player = mBoard[(row * mBoardWidth) + col];
  if (player == 0)
    return false;
  for (int i = 1; i < 4; i++) {
    col++;
    if (col >= mBoardWidth)
      return false;
    if (mBoard[(row * mBoardWidth) + col] != player)
      return false;
  }
  return true;
}

bool Board::checkDiLeft(int row, int col) {
  int player = mBoard[(row * mBoardWidth) + col];
  for (int i = 1; i < 4; i++) {
    row++;
    col--;
    if (row >= mBoardHeight || col < 0)
      return false;
    if (mBoard[(row * mBoardWidth) + col] != player)
      return false;
  }
  return true;
}

bool Board::checkUp(int row, int col) {
  int player = mBoard[(row * mBoardWidth) + col];
  for (int i = 1; i < 4; i++) {
    row++;
    if (row >= mBoardHeight)
      return false;
    if (mBoard[(row * mBoardWidth) + col] != player)
      return false;
  }
  return true;
}

bool Board::checkDiRight(int row, int col) {
  int player = mBoard[(row * mBoardWidth) + col];
  for (int i = 1; i < 4; i++) {
    row++;
    col++;
    if (row >= mBoardHeight || col >= mBoardWidth)
      return false;
    if (mBoard[(row * mBoardWidth) + col] != player)
      return false;
  }
  return true;
}
