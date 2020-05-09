#include <iostream>
#include "Node.h"

using namespace std;

Node :: Node(int newvalue){//pass through value
  value = newvalue;
  color = 2;//all nodes are created as red
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

Node* Node :: getGrandparent(){//parent's parent is grandparent
  return parent->getParent();
}

Node* Node :: getSibling(){//if node is not the root, get the other child
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

Node* Node :: getUncle(){//uncle is just parent's sibling
  if (parent == NULL){
    return NULL;
  }
  else{
    return parent->getSibling();
  }
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
