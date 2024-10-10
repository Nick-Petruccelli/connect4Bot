#include "../inc/abSearch.hpp"
#include "../inc/board.hpp"
#include <cstdlib>
#include <limits>

void ABSearch::generateTree() {
  if (mTree != NULL) {
    free(mTree);
    mTree = NULL;
  }
  static Node root;
  root.generateChildren();
  mTree = minMaxAB(&root);
}

Node *ABSearch::minMaxAB(Node *root) {
  root->setUtility(findMaxAB(root, std::numeric_limits<int>::min(),
                             std::numeric_limits<int>::max()));
  return root;
}

int ABSearch::findMaxAB(Node *node, int a, int b) {
  node->generateChildren();
  std::array<Node *, 7> children = node->getChildren();
  if (children.size() == 0)
    return mBoard.checkWin();
  int best = std::numeric_limits<int>::min();
  for (int i = 0; i < children.size(); i++) {
    Node *child = children[i];
    child->setUtility(findMinAB(child, a, b));
    best = best >= child->getUtility() ? best : child->getUtility();
    if (best >= b)
      return best;
    a = a >= best ? a : best;
  }
  return best;
}

int ABSearch::findMinAB(Node *node, int a, int b) {
  node->generateChildren();
  std::array<Node *, 7> children = node->getChildren();
  if (children.size() == 0)
    return mBoard.checkWin();
  int best = std::numeric_limits<int>::max();
  for (int i = 0; i < children.size(); i++) {
    Node *child = children[i];
    child->setUtility(findMaxAB(child, a, b));
    best = best <= child->getUtility() ? best : child->getUtility();
    if (best <= a)
      return best;
    b = b <= best ? b : best;
  }
  return best;
}
