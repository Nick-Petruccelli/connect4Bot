#pragma once

#include "board.hpp"
#include <array>
#include <memory>
#include <vector>

class Node {
public:
  std::vector<Node *> *getChildren();
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
  std::vector<Node *> mChildren;
  int mNumChildren = 0;
  int mUtility;
  int mAlpha;
  int mBeta;
};

class ABSearch {
public:
  ABSearch(int boardWidth, int boardHeight);
  ~ABSearch();
  void applyMove(int col);
  int getNextMove();
  Node *getTree();
  void generateTree();
  void printTree();

protected:
  Board mBoard;

private:
  Node *mTree = NULL;
  void minMaxAB(Node *n);
  int findMaxAB(Node *n, int a, int b);
  int findMinAB(Node *n, int a, int b);
  void dfsPrint(Node *n, int depth);

  friend class Node;
};
