#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

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
  int color;
  Node* left;
  Node* right;
  Node* parent;
};


#endif
