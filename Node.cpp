#include <iostream>
#include "Node.h"

using namespace std;

Node :: Node(int newvalue){
  value = newvalue;
  color = 0;
  left = NULL;
  right = NULL;
  parent = NULL;
}
//getters

int Node :: getValue(){
  return value;
}

int Node :: getColor(){
  return color;
}

Node* Node :: getLeft(){
  return left;
}

Node* Node :: getRight(){
  return right;
}

Node* Node :: getParent(){
  return parent;
}

void Node :: setValue(int newvalue){
  value = newvalue;
}

void Node :: setColor(int newcolor){
  color = newcolor;
}

void Node :: setLeft(Node* newleft){
  left = newleft;
}

void Node :: setRight(Node* newright){
  right = newright;
}

void Node :: setParent(Node* newparent){
  parent = newparent;
}

Node :: ~Node(){
}
