#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

//Modified BST Node class. Added get grandparent, sibling, uncle
class Node {
 public:
  Node(int newvalue);
  int getValue();
  int getColor();
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  Node* getGrandparent();
  Node* getSibling();
  Node* getUncle();
  void setValue(int newvalue);
  void setColor(int newcolor);
  void setLeft(Node* newleft);
  void setRight(Node* newright);
  void setParent(Node* newparent);
  ~Node();
 private:
  int value;
  int color;//1 = black. 2 = red.
  Node* left;
  Node* right;
  Node* parent;
};


#endif
