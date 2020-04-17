#include <iostream>
#include "Node.h"

using namespace std;

Node :: Node(int newvalue){
  value = newvalue;
  color = 1;
  left = NULL;
  right = NULL;
  parent = NULL;
}

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

Node* Node :: getGrandparent(){
  return parent->getParent();
}

Node* Node :: getSibling(){
  if (parent == NULL){
    return NULL;
  }
  if (this == parent->getRight()){
    return parent->getLeft();
  }
  else if (this == parent->getLeft()){
    return parent->getRight();
  }
}

Node* Node :: getUncle(){
  if (parent == NULL){
    return NULL;
  }
  else{
    return parent->getSibling();
  }
  /*if (getGrandparent()->getValue() < parent->getValue()){
    return getGrandparent()->getLeft();
  }
  return getGrandparent()->getRight();*/
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
