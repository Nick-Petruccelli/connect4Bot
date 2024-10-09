#pragma once

#include "board.hpp"

class Game {
public:
  Game();
  Game(bool multiplayer);
  void startGame();

private:
  bool mMultiplayer = false;
  Board mBoard;
  void takeInput(int player);
  void display();
};
