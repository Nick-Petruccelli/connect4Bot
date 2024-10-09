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
  bool checkRight(int row, int col);
  bool checkDiLeft(int row, int col);
  bool checkUp(int row, int col);
  bool checkDiRight(int row, int col);
};
