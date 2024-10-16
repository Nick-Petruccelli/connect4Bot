#include "../inc/abSearch.hpp"
#include "../inc/board.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

unsigned int nodesVisited = 0;
unsigned int pruned = 0;

ABSearch::ABSearch(int boardWidth, int boardHeight)
    : mBoard(boardWidth, boardHeight) {}
ABSearch::~ABSearch() {
  /*
  if (mTree != NULL)
    free(mTree);
  */
}

Node *ABSearch::getTree() { return mTree; }

void ABSearch::generateTree() {
  if (mTree != NULL) {
    free(mTree);
    mTree = NULL;
  }
  mTree = new Node;
  minMaxAB(mTree);
}

void ABSearch::minMaxAB(Node *root) {
  root->setUtility(findMaxAB(root, std::numeric_limits<int>::min(),
                             std::numeric_limits<int>::max(), 0));
  std::cout << "done" << std::endl;
}

int ABSearch::findMaxAB(Node *node, int a, int b, int depth) {
  /*
  nodesVisited++;
  std::cout << "nodesVisited: " << nodesVisited << std::endl;
  std::cout << "Depth: " << depth << std::endl;
  */
  if (isLeaf(node)) {
    return node->getUtility();
  }

  int best = std::numeric_limits<int>::min();
  node->setAlpha(a);
  node->setBeta(b);
  std::vector<Node *> *children = node->getChildren();
  depth++;
  for (int i = 0; i < children->size(); i++) {
    if (children->at(i) == nullptr) {
      continue;
    }
    Node *child = children->at(i);
    mBoard.placeToken(i, 1);
    child->setUtility(
        findMinAB(child, node->getAlpha(), node->getBeta(), depth));
    mBoard.removeToken(i);
    best = std::max(best, child->getUtility());
    /*
    std::cout << "Best: " << best << std::endl;
    std::cout << "Beta: " << node->getBeta() << std::endl;
    */
    if (best >= node->getBeta()) {
      /*
      pruned++;
      std::cout << "Pruned: " << pruned << std::endl;
      */
      return best;
    }
    node->setAlpha(std::max(node->getAlpha(), best));
  }
  return best;
}

int ABSearch::findMinAB(Node *node, int a, int b, int depth) {
  /*
  nodesVisited++;
  std::cout << "nodesVisited: " << nodesVisited << std::endl;
  std::cout << "Depth: " << depth << std::endl;
  */

  if (isLeaf(node)) {
    return node->getUtility();
  }

  int best = std::numeric_limits<int>::max();
  node->setAlpha(a);
  node->setBeta(b);
  std::vector<Node *> *children = node->getChildren();
  depth++;
  for (int i = 0; i < children->size(); i++) {
    if (children->at(i) == nullptr)
      continue;
    Node *child = children->at(i);
    mBoard.placeToken(i, 2);
    child->setUtility(
        findMaxAB(child, node->getAlpha(), node->getBeta(), depth));
    mBoard.removeToken(i);
    best = std::min(child->getUtility(), best);
    /*
    std::cout << "Best: " << best << std::endl;
    std::cout << "Alpha: " << node->getAlpha() << std::endl;
    */
    if (best <= node->getAlpha()) {
      /*
      pruned++;
      std::cout << "Pruned: " << pruned << std::endl;
      */
      return best;
    }
    node->setBeta(std::min(node->getBeta(), best));
  }
  return best;
}

bool ABSearch::isLeaf(Node *node) {
  int winner = mBoard.checkWin();
  if (winner == 2)
    winner = -1;
  if (winner != 0) {
    node->setUtility(winner);
    return true;
  }
  node->generateChildren(&mBoard);
  std::vector<Node *> *children = node->getChildren();
  int numChildren = node->getNumChildren();
  if (numChildren == 0) {
    node->setUtility(winner);
    return true;
  }
  return false;
}

void ABSearch::dfsPrint(Node *node, int depth) {
  std::cout << "Util : " << node->getUtility() << "Depth: " << depth
            << std::endl;
  depth++;
  for (int i = 0; i < mBoard.getBoardWidth(); i++) {
    if (node->getChildren()->at(i) == nullptr)
      continue;
    dfsPrint(node->getChildren()->at(i), depth);
  }
}

void ABSearch::printTree() { dfsPrint(mTree, 0); }

int ABSearch::getNextMove() {
  std::vector<Node *> *children = mTree->getChildren();
  int best = std::numeric_limits<int>::max();
  int col;
  for (int i = 0; i < mBoard.getBoardWidth(); i++) {
    if (children->at(i)->getUtility() < best) {
      col = i;
      best = children->at(i)->getUtility();
    }
  }
  return col;
}

void ABSearch::applyMove(int col) {
  std::vector<Node *> *children = mTree->getChildren();
  if (children->at(col) == nullptr) {
    std::cout << "hit" << std::endl;
    minMaxAB(mTree);
  }
  mTree = children->at(col);
}

void Node::generateChildren(Board *curBoard) {
  mChildren.resize(curBoard->getBoardWidth());
  mChildren.clear();
  mNumChildren = 0;
  bool *moves = curBoard->getValidMoves();
  for (int i = 0; i < curBoard->getBoardWidth(); i++) {
    if (moves[i]) {
      mChildren.insert(mChildren.begin() + i, new Node);
      mNumChildren++;
    } else {
      mChildren.insert(mChildren.begin() + i, nullptr);
    }
  }
  free(moves);
}

void Node::setUtility(int util) { mUtility = util; }
void Node::setAlpha(int alpha) { mAlpha = alpha; }
void Node::setBeta(int beta) { mBeta = beta; }

std::vector<Node *> *Node::getChildren() { return &mChildren; }
int Node::getNumChildren() { return mNumChildren; }
int Node::getUtility() { return mUtility; }
int Node::getAlpha() { return mAlpha; }
int Node::getBeta() { return mBeta; }
