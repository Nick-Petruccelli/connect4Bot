#pragma once

#include "abSearch.hpp"
#include "board.hpp"

class Game {
public:
  Game();
  Game(bool multiplayer);
  void startGame();

private:
  bool mMultiplayer = false;
  Board mBoard;
  int getAIMove(ABSearch ai, int player);
  int takeInput(int player);
  void display();
};
