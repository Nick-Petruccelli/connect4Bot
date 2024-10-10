#include "../inc/abSearch.hpp"
#include "../inc/board.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>

ABSearch::ABSearch() : mBoard(7, 6) {}
ABSearch::~ABSearch() {
  if (mTree != NULL)
    free(mTree);
}

void ABSearch::generateTree() {
  if (mTree != NULL) {
    free(mTree);
    mTree = NULL;
  }
  static Node root;
  root.generateChildren(&mBoard);
  mTree = minMaxAB(&root);
}

Node *ABSearch::minMaxAB(Node *root) {
  root->setUtility(findMaxAB(root, std::numeric_limits<int>::min(),
                             std::numeric_limits<int>::max()));
  return root;
}

int ABSearch::findMaxAB(Node *node, int a, int b) {
  node->generateChildren(&mBoard);
  std::array<Node *, 7> *children = node->getChildren();
  int numChildren = node->getNumChildren();
  if (numChildren == 0)
    return mBoard.checkWin();
  int best = std::numeric_limits<int>::min();
  node->setAlpha(a);
  node->setBeta(b);
  for (int i = 0; i < children->size(); i++) {
    if (children->at(i) == nullptr)
      continue;
    Node *child = children->at(i);
    mBoard.placeToken(i, 1);
    child->setUtility(findMinAB(child, node->getAlpha(), node->getBeta()));
    mBoard.removeToken(i);
    best = best >= child->getUtility() ? best : child->getUtility();
    if (best >= node->getBeta())
      return best;
    if (node->getAlpha() < best)
      node->setAlpha(best);
  }
  return best;
}

int ABSearch::findMinAB(Node *node, int a, int b) {
  node->generateChildren(&mBoard);
  std::array<Node *, 7> *children = node->getChildren();
  int numChildren = node->getNumChildren();
  if (numChildren == 0)
    return mBoard.checkWin();
  if (mBoard.checkWin() != 0)
    return mBoard.checkWin() == 1 ? 1 : -1;
  int best = std::numeric_limits<int>::max();
  node->setAlpha(a);
  node->setBeta(b);
  for (int i = 0; i < children->size(); i++) {
    if (children->at(i) == nullptr)
      continue;
    Node *child = children->at(i);
    mBoard.placeToken(i, 2);
    child->setUtility(findMaxAB(child, node->getAlpha(), node->getBeta()));
    mBoard.removeToken(i);
    best = best <= child->getUtility() ? best : child->getUtility();
    if (best <= node->getAlpha())
      return best;
    if (node->getBeta() > best)
      node->setBeta(best);
  }
  return best;
}

int ABSearch::getNextMove() {
  std::array<Node *, 7> *children = mTree->getChildren();
  int best = std::numeric_limits<int>::max();
  int col;
  for (int i = 0; i < 7; i++) {
    if (children->at(i)->getUtility() < best) {
      col = i;
      best = children->at(i)->getUtility();
    }
  }
  return col;
}

Node::Node() {}
Node::~Node() {}

void Node::generateChildren(Board *curBoard) {
  bool *moves = curBoard->getValidMoves();
  for (int i = 0; i < 7; i++) {
    if (moves[i]) {
      static Node child;
      mChildren[i] = &child;
      mNumChildren++;
    } else {
      mChildren[i] = nullptr;
    }
  }
}

void Node::setUtility(int util) { mUtility = util; }
void Node::setAlpha(int alpha) { mAlpha = alpha; }
void Node::setBeta(int beta) { mBeta = beta; }

std::array<Node *, 7> *Node::getChildren() { return &mChildren; }
int Node::getNumChildren() { return mNumChildren; }
int Node::getUtility() { return mUtility; }
int Node::getAlpha() { return mAlpha; }
int Node::getBeta() { return mBeta; }
