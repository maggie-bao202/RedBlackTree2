#include "Node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void charToIntegerArray(char*, int* &, int &);
int pow(int, int);

Node* insert(Node* &, Node*);
void add(Node*, Node*);
void rearrange(Node*, Node* &);

void print(Node*, int);

void rotateLeft(Node* &, Node*);
void rotateRight(Node* &, Node*);

void blackUncle(Node*, Node* &);

//Part 2:
bool search(Node*, int);

Node* leftMostNode(Node*);

void doubleBlack(Node* &, Node*);

Node* getNode(Node*, int);
void remove(Node* &, Node* &);

/*4/17/2020 Maggie Bao 
Red Black Tree: A type of balanced search tree. Root and NULL nodes are black. If a node is red, children are black. All paths from a node to NULL descendents contain same number of black nodes. Shortest path has all black nodes. Longest alternates between red and black. Insert and remove requires rotation.*/

int main(){
  bool loop = true;
  char* name = new char[20];
  char* input = new char[2000];
  Node* root = NULL;
  int value = 0;
  while (loop = true){
    cout << "Type in a keyword (\"ADD\", \"READ\", \"REMOVE\", \"SEARCH\", \"PRINT\" or \"QUIT\"):"<<endl;
    cin >> name; //put input into char array keyword
    cin.ignore();
    if (strcmp(name, "ADD") == 0){//if the input is ADD
      cout << "Enter the number you want to add: ";
      cin >> value;
      root = insert(root, new Node(value));//add to tree and adjust accordingly
      //cout << root->getValue();
      cout << endl;
    }
    else if (strcmp(name, "READ") == 0){
      while(loop == true){//will keep prompting for file name until valid
       cout << "Enter the name of the file: " << endl;
       cin.getline(name, 20, '\n');
       ifstream fileStream (name);
       if (fileStream.is_open()){//open file with name from input
	 fileStream.getline(input, 200);
	 loop = false;
       }
       else{
	 cout << "Invalid file name." << endl;
       }
       fileStream.close();
      }
      loop = true;//reuse bool loop
      int* numberInput = new int[101];
      int size = 0;
      charToIntegerArray(input, numberInput, size);//convert char* to int * array
      for (int i = 0; i < (size); i++){//insert integers into tree, one by one
	root = insert(root, new Node(numberInput[i]));
      }
    }
    else if (strcmp(name, "REMOVE") == 0){//For RedBlackTree Part 2
      cout << "Enter the number you want to remove: ";
      cin >> value;
      if(search(root, value) == true){//first checks if deleting value is within the tree
	Node* temp = getNode(root, value); //traverses to deleted node in "temp"
	cout << temp->getValue() << endl;
        remove(root, temp); //removes the node from tree
      }
      else {
	cout << "Not a valid number.";
      }
      cout << endl;
    }
    else if (strcmp(name, "PRINT") == 0){
      print(root,0);//prints visual of tree
    }
    else if (strcmp(name, "SEARCH") == 0){
      cout << "Enter the number you want to search: ";
      cin >> value;
      if (search(root, value) == true){//search is a bool function. Traverses down the tree to see if input matches with a node value
	cout << "The number " << value << " exists within the tree.";
      }
      else {
	cout << "The number " << value << " does not exist within the tree.";
      }	
      cout << endl;
    }
    else if (strcmp(name, "QUIT") == 0){//if quit, boolean is false so program will stop
      cout << "Have a nice day!" << endl;
      loop = false;
      return 0;
    }
    else{//if not a valid keyword
      cout << "Make sure the keyword is capitalized." << endl;
    }
  }
  cout << endl;
  return 0;
}

//pow and charToIntegerArray function taken straight from my Heap assignment

int pow(int a, int b){//pow(10, 4) = 10^4, power function
  int x = 1;
  for (int i = 1; i <= b; i++){
    x *= a;//multiply a by itself as b many times
  }
  return x;
}

void charToIntegerArray(char* carray, int* &iarray, int &size){//converts a char* array to an int* array
  int counter = 0;
  int place = 0;//place holds the exponent that will be multiplied by 10
  for (int i = 0; i < strlen(carray); i++){//going through each element of char array
    if (carray[i] >= '0' && carray[i] <= '9'){//if it is a number
      if (place != 2){//if the element is either in 1s or 10s place
	counter = (counter * pow(10, place)) + (carray[i] - '0');//add to runningTotal counter
	place++;
      }
      else{//if it is 100s place, (debugged)
	counter = (counter * pow(10, place-1)) + (carray[i] - '0');
      }
      if (i == strlen(carray)-1){//add last element to int array (debugged)
	iarray[size++] = counter;
      }
    }
    else if (carray[i] == ' '){//whenever there is a space, add to int array and reset
      iarray[size++] = counter;
      counter = 0;
      place = 0;
    }
  }
}

/*
Sources for Red Black Tree Part 2:

https://www.youtube.com/watch?v=aA-nLw28eUw

Right-most of left, left-most of right like in BST
Copy, not swap.

Case 1-- Node to be deleted is red:
delete the node. If node has a child, replace it with child

Case 2-- Node is black, with red child:
replace the node with child, make child black

Case 3-- Node is black, with black child:
Replace node with child, child is called a DOUBLE BLACK NODE. Transformed into normal black node through 6 cases

Deletion focuses on sibling instead of uncle

Double Black Node:

1) Node is a black root. Terminal
Turn it into a black node

2) Node is black, has black parent, red sibling
Left child, rotate left. Rotate away from root. To be deleted node is still double black. recolor parent to red, sibling to black

3) Node is black, black parent, black sibling with two black children.
Push the double black node up, sibling to red

4) Node is black, red parent. Terminal
Turn it into a black node, Parent black, sibling red

5) Node is black, black parent, and black sibling with one inner red child
rotate red child away from root, recolor

6) Node is black, black sibling, 1 outer red child. others dont care (Terminal)
rotate away from root. 

*/

bool search(Node* current, int value){//Searches for a node with matching value as user input.
  while (current != NULL){
    if (value == current->getValue()){//if value matches up, return true
      return true;
    }
    if (value < current->getValue()){//traverse down the tree
      return search(current->getLeft(), value);
    }
    if (value > current->getValue()){
      return search(current->getRight(), value);
    }
  }
  return false;//if not found when reach the end of tree, return false
}

Node* getNode(Node* current, int value){//Returns the node in which the value matches up to. Used for delete function
  if (current == NULL){//not really necessary but it is here
    return current;
  }
  if (value == current->getValue()){//if value is found, stop searching and return the node
    return current;
  }
  if (value < current->getValue()){//if value is smaller, go to left child and look
    return getNode(current->getLeft(), value);
  }
  if (value > current->getValue()){//if value is larger, go to right child and look
    return getNode(current->getRight(), value);
  }
}

Node* leftMostNode(Node* current){//find the left most node in tree for the inorder successor using recursion
  if (current->getLeft() == NULL){//if its the last node before NULL, return that node
    return current;
  }
  else{
    return leftMostNode(current->getLeft());//traverse to left child
  }
}

Node* replace(Node* node){
  if (node->getLeft() != NULL && node->getRight() != NULL){
    return leftMostNode(node->getRight());
  }
  if (node->getLeft() == NULL && node->getRight() == NULL){
    return NULL;
  }
  if (node->getLeft() == NULL){
    return node->getLeft();
  }
  else{
    return node->getRight();
  }
}

void remove(Node* &root, Node* &current){
  //cout << current->getValue() << " "<< current->getColor() << endl;
  //cout << root->getValue() << " " << root->getColor() << endl;
  Node* temp = replace(current);
  Node* parent = current->getParent();
  if (temp == NULL){
    if (current == root){
      root = NULL;
    }
    else{
      if ((temp == NULL || temp->getColor() == 1) && (current->getColor() == 1)){
	doubleBlack(root, current);
      }
      else{
	if (current->getSibling() != NULL){
	  current->getSibling()->setColor(2);
	}
      }
      if (parent->getRight() == current){
	parent->setRight(NULL);
      }
      else{
	parent->setLeft(NULL);
      }
    }
    delete current;
    return;
  }
  if (current->getLeft() == NULL || current->getRight() == NULL){
    if (current == root){
      current->setValue(temp->getValue());
      current->setLeft(NULL);
      current->setRight(NULL);
      delete temp;
    }
    else{
      if (parent->getLeft() == current){
	parent->setLeft(temp);
      }
      else{
	parent->setRight(temp);
      }
      delete current;
      temp->setParent(parent);
      if ((temp == NULL || temp->getColor() == 1) && (current->getColor() == 1)){
	doubleBlack(root, temp);
      }
      else{
	temp->setColor(1);
      }
    }
    return;
  }
  int temp2 = temp->getValue();
  temp->setValue(current->getValue());
  current->setValue(temp2);
  remove(root, temp);
}
  /*Case 1-- Node to be deleted is red:
delete the node. If node has a child, replace it with child

Case 2-- Node is black, with red child:
replace the node with child, make child black

Case 3-- Node is black, with black child:
Replace node with child, child is called a DOUBLE BLACK NODE. Transformed into norm\
al black node through 6 cases
*/

void doubleBlack(Node* &root, Node* node){
  cout << "DOUBLE BLACK" << endl;
  if (node == root){
    return;
  }
  Node* parent = node->getParent();
  Node* sibling = node->getSibling();
  if (sibling == NULL){
    doubleBlack(root, parent);
  }
  else{
    if (sibling->getColor() == 2){
      parent->setColor(2);
      sibling->setColor(1);
      if (parent->getLeft() == sibling){
	rotateRight(root, parent);
	
      }
      else{
	rotateLeft(root, parent);
      }
      doubleBlack(root, node);
    }
    else{
      if ((sibling->getLeft() != NULL && sibling->getLeft()->getColor() == 2) || (sibling->getRight() != NULL && sibling->getRight()->getColor() == 2)){
	if ((sibling->getLeft() != NULL) && (sibling->getLeft()->getColor() == 2)){
	  if (parent->getLeft() == sibling){
	    sibling->getLeft()->setColor(sibling->getColor());
	    sibling->setColor(parent->getColor());
	    rotateRight(root, parent);
	  }
	  else{
	    sibling->getLeft()->setColor(parent->getColor());
	    rotateRight(root, sibling);
	    rotateLeft(root, parent);
	  }
	}
	else{
	  if(parent->getLeft() == sibling){
	    sibling->getRight()->setColor(parent->getColor());
	    rotateLeft(root, sibling);
	    rotateRight(root, parent);
	  }
	  else{
	    sibling->getRight()->setColor(sibling->getColor());
	    sibling->setColor(parent->getColor());
	    rotateLeft(root, parent);
	  }
	}
	parent->setColor(1);
      }
      else{
	sibling->setColor(2);
	if (parent->getColor() == 1){
	  doubleBlack(root, parent);
	}
	else{
	  parent->setColor(1);
	}
      }
    }
  }
}
 
/*
Sources for Red Black Tree Part 1:

Found these series of youtube videos very helpful:

Basics:
https://www.youtube.com/watch?v=qvZGUFHWChY

Rotations:
https://www.youtube.com/watch?v=95s3ndZRGbk

Insertions:
https://www.youtube.com/watch?v=5IBxA-bZZH8

Examples:
https://www.youtube.com/watch?v=A3JZinzkMpk

Video explains wikipedia code and:

https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-introduction-to-algorithms-sma-5503-fall-2005/video-lectures/lecture-10-red-black-trees-rotations-insertions-deletions/lec10.pdf

https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
*/

/*

Rotations: rearranges subtrees to decrease the height of the tree. Does not affec\
t the order of elements.

left rotate on blue:

blue            yellow
/   \            /  \  
   yellow -->  blue
    /  \       /  \
  red             red

*/

void rotateLeft(Node* &root, Node* blue){//node is blue
  if (blue->getRight() == NULL){//if yellow does not exist
    return;
  }

  Node* yellow = blue->getRight();//create yellow pointer
  Node* parent = blue->getParent();//parent of blue
  if (blue == root){
    root = yellow;
  }
  blue->setRight(yellow->getLeft());//set blue's right as red
  yellow->setLeft(blue);//set yellow's left as blue
  blue->setParent(yellow);//make yellow blue's parent

  if (blue->getRight() != NULL){//if red exists
    blue->getRight()->setParent(blue);//set blue as red's parent
  }
  if (parent != NULL){//if blue is not the root
    if (blue == parent->getLeft()){//if blue is the left child of parent
      parent->setLeft(yellow);//connect
    }
    else if (blue == parent->getRight()){//if blue is the right child of parent
      parent->setRight(yellow);
    }
  }
  yellow->setParent(parent);
}

void rotateRight(Node* &root, Node* yellow){//similar to left-rotate. Rotate yellow (see example in video)
  if (yellow->getLeft() == NULL){
    return;
  }
  
  Node* blue = yellow->getLeft(); //blue is left child of yellow 
  Node* parent = yellow->getParent();//parent of yellow
  if (yellow == root){
    root = blue;
  }
  yellow->setLeft(blue->getRight());//set yellow's left as red
  blue->setRight(yellow); //set blue's right as yellow
  yellow->setParent(blue); //set yellow's parent as blue

  if (yellow->getLeft() != NULL){//if red exists
    yellow->getLeft()->setParent(yellow);//set yellow as red's parent
  }
  if (parent != NULL){//if yellow is not the root
    if (yellow == parent->getLeft()){//if yellow is left child of parent
      parent->setLeft(blue);
    }
    else if (yellow == parent->getRight()){//if yellow is right child of parent
      parent->setRight(blue);
    }
  }
  blue->setParent(parent);//set original parent of yellow as blue's parent
}


Node* insert(Node* &root, Node* node){//add and rearrange tree
  add(root, node);
  rearrange(node, root);
  root = node;//would want to return the root
  while(root->getParent() != NULL){
    root = root->getParent();//keep on getting parent until parent is null (so we get the root)
  }
  return root;
}
 
void add(Node* current, Node* node){//adds the new node with integer value as a leaf (BST)
  if (current == NULL){//if nothing in tree, make the node the root
    current = node;
    return; 
  }
  if (node->getValue() < current->getValue()){//value is smaller than current node, go to left child
    if (current->getLeft() != NULL){//if its not a leaf, keep going to left child
      add(current->getLeft(), node);
      return;
    }
    else{//then, assign the node as left child of the current
      current->setLeft(node);
    }
  }
  else{//value is larger (or equal to) go right
    if (current->getRight() != NULL){
      add(current->getRight(), node);
      return;
    }
    else{//assign node as right child of current
      current->setRight(node);
    }
    
  }
  node->setParent(current);//assign current as parent of new node
}

void rearrange(Node* current, Node* &root){
  if (current->getParent() == NULL){//current is the root
    current->setColor(1);//color black
  }
  else if (current->getParent()->getColor() == 1){//current parent is black, n is red.
    //nothing
  }
  else if (current->getUncle() != NULL && current->getUncle()->getColor() == 2){//if uncle is red
    current->getParent()->setColor(1);//parent and uncle to black
    current->getUncle()->setColor(1);
    current->getGrandparent()->setColor(2);//grandparent to red
    rearrange(current->getGrandparent(), root);
  }
  else{//if uncle is black, there are two cases: triangle and line
    blackUncle(current, root);
  }
}

void blackUncle(Node* current, Node* &root){//if uncle is black 
  Node* parent = current->getParent();
  Node* grandparent = current->getGrandparent();
  if (current == parent->getRight() && parent == grandparent->getLeft()){//if triange
    rotateLeft(root, parent);//rotate parent opposite direction of grandparent
    current = current->getLeft();//original parent becomes current
  }
  else if (current == parent->getLeft() && parent == grandparent->getRight()){//if triangle
    rotateRight(root, parent);
    current = current->getRight();
  }

  parent = current->getParent();
  grandparent = current->getGrandparent();
  if (current == parent->getLeft()){//if grandparent, parent, current form a line on left
    rotateRight(root, grandparent);//rotate grandparent
  }
  else{//line on right
    rotateLeft(root, grandparent);
  }
  if (root == grandparent){//reassign the root if changed (debugging)
    root = parent;
  }
  parent->setColor(1);//adjust colors for parent and grandparent
  grandparent->setColor(2);
}

void print(Node* current, int depth){//modified my BST tree visualizer
  if (current == NULL){
    return;
  }
  print(current->getRight(), depth+1);//incrementing tabs to bottom most right
  for(int i = 0; i < depth; i++){//print the amount of tabs, then print value
    cout << "\t";
  }
  if (current->getColor() == 1){//print the color before the value
    cout << "B ";
  }
  if (current->getColor() == 2){
    cout << "R ";
  }
  cout << current->getValue() << endl;
  print(current->getLeft(), depth+1);//end at bottom most left node
}
