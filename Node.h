#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node {
 public:
  Node(int newvalue);
  int getValue();
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  void setValue(int newvalue);
  void setLeft(Node* newleft);
  void setRight(Node* newright);
  void setParent(Node* newparent);
  ~Node();
 private:
  int value;
  Node* left;
  Node* right;
  Node* parent;
};


#endif
