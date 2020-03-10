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
  void setValue(int newvalue);
  void setLeft(Node* newleft);
  void setRight(Node* newright);
  ~Node();
 private:
  int value;
  Node* left;
  Node* right;
};


#endif
