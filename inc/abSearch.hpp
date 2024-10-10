#pragma once

#include "board.hpp"
#include <array>
#include <memory>

class Node {
public:
  std::unique_ptr<Node> getParent();
  std::array<Node *, 7> getChildren();
  void generateChildren();
  int setUtility(int utility);
  int setAlpha(int a);
  int setBeta(int b);
  int getUtility();
  int getAlpha();
  int getBeta();

private:
  Node *parent;
  std::array<Node *, 7> children;
  int utility;
  int alpha;
  int beta;
};

class ABSearch {
public:
  ABSearch();
  ~ABSearch();
  void applyMove(int col);
  int getNextMove();
  void generateTree();

private:
  Node *mTree;
  Board mBoard;
  Node *minMaxAB(Node *n);
  int findMaxAB(Node *n, int a, int b);
  int findMinAB(Node *n, int a, int b);
};
