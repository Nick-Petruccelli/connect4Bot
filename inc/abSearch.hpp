#pragma once

#include "board.hpp"
#include <array>
#include <memory>

class Node {
public:
  Node();
  ~Node();
  std::array<Node *, 7> *getChildren();
  void generateChildren(Board *curBoard);
  void setUtility(int utility);
  void setAlpha(int a);
  void setBeta(int b);
  void setParent(Node *parent);
  int getNumChildren();
  int getUtility();
  int getAlpha();
  int getBeta();

private:
  std::array<Node *, 7> mChildren;
  int mNumChildren = 0;
  int mUtility;
  int mAlpha;
  int mBeta;
};

class ABSearch {
public:
  ABSearch();
  ~ABSearch();
  void applyMove(int col);
  int getNextMove();
  void generateTree();

protected:
  Board mBoard;

private:
  Node *mTree = NULL;
  Node *minMaxAB(Node *n);
  int findMaxAB(Node *n, int a, int b);
  int findMinAB(Node *n, int a, int b);

  friend class Node;
};
