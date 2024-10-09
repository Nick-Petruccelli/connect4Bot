#pragma once

class Board {
public:
  Board(int width, int height);
  ~Board();
  void placeToken(int col, bool player);
  int getColHeight(int col);
  int checkWin();
  void printBoard();

private:
  int *mBoard;
  int mBoardWidth;
  int mBoardHeight;
};
