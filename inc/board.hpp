#pragma once

class Board {
public:
  Board(int width, int height);
  ~Board();
  void placeToken(int col, int player);
  void removeToken(int col);
  int getColHeight(int col);
  bool *getValidMoves();
  int getBoardWidth();
  int getBoardHeight();
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
