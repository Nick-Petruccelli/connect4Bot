#include <iostream>

const int BOARDWIDTH = 7;
const int BOARDHIGHT = 6;

void printBoard(int *board) {
  for (int r = 0; r < BOARDHIGHT; r++) {
    for (int c = 0; c < BOARDWIDTH; c++) {
      std::cout << "| " << board[(r * BOARDWIDTH) + c] << " ";
    }
    std::cout << "|" << std::endl;
    for (int i = 0; i < BOARDWIDTH * 4 + 1; i++) {
      std::cout << "-";
    }
    std::cout << std::endl;
  }
}

int main() {
  const int boardSide = BOARDWIDTH * BOARDHIGHT;
  int board[boardSide] = {0};
  printBoard(board);
}
