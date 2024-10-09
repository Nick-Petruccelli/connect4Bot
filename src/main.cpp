#include "../inc/game.hpp"
#include <cstring>

int main(int argc, char *argv[]) {
  bool multiplayer = false;
  if (strcmp(argv[0], "multiplayer"))
    multiplayer = true;
  Game game(multiplayer);
  game.startGame();
}
