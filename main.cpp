#include "Node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int, int);
Node* insert(Node*, Node*);
void add(Node*, Node*);
void rearrange(Node*);
void print(Node*, int);
void rotateLeft(Node*);
void rotateRight(Node*);
void case3(Node*);
void case4(Node*);
void case4part2(Node*);
/*Red Black Tree: A type of balanced search tree. Root and NULL nodes are black. If a node is red, children are black. All paths from a node to NULL descendents contain same number of black nodes. Shortest path has all black nodes. Longest alternates between red and black. Insert and remove requires rotation.*/

int main(){
  bool loop = true;
  char* name = new char[20];
  char* input = new char[2000];
  Node* root = NULL;
  int value = 0;
  while (loop = true){
    cout << "Type in a keyword (\"ADD\", \"READ\",\"REMOVE\",\"PRINT\" or \"QUIT\"):"<<endl;
    cin >> name; //put input into char array keyword
    cin.ignore();
    if (strcmp(name, "ADD") == 0){//if the input is ADD
      cout << "Enter the number you want to add: ";
      cin >> value;
      root = insert(root, new Node(value));//insert new value into tree
      cout << endl;
    }
    else if (strcmp(name, "READ") == 0){//Similar to above
      while(loop == true){
       cout << "Enter the name of the file: " << endl;
       cin.getline(name, 20, '\n');
       ifstream fileStream (name);
       if (fileStream.is_open()){//open file with name from input
	 fileStream.getline(input, 200);
	 loop = false;
       }
       else{//loop until a valid file name is entered
	 cout << "Invalid file name." << endl;
       }
       fileStream.close();
      }
      loop = true;
      int* numberInput = new int[101];
      int size = 0;
      charToIntegerArray(input, numberInput, size);//convert char* to int * array
      for (int i = 0; i < (size); i++){//insert integers into tree, one by one
	root = insert(root, new Node(numberInput[i]));
      }
    }
    else if (strcmp(name, "REMOVE") == 0){/*
      cout << "Enter the number you want to remove: ";
      cin >> value;
      if(search(root, value) == true){//first checks if deleting value is within the tree
	Node* temp = getNode(root, value); //traverses to deleted node in "temp"
	removeFromTree(root, temp); //removes the node from tree
      }
      else {
	cout << "Not a valid number.";
      }
      cout << endl;*/
    }
    else if (strcmp(name, "PRINT") == 0){
      cout << endl;
      print(root,0);//prints visual of tree
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

//Rotations: rearranges subtrees to decrease the height of the tree. Does not affect the order of elements.
void rotateLeft(Node* blue){//node is blue
  if (blue->getRight() == NULL){
    return;
  }
  Node* yellow = blue->getRight();//create yellow pointer
  Node* parent = blue->getParent();//parent of blue
  blue->setRight(yellow->getLeft());//set blue's right as red
  yellow->setLeft(blue);//set yellow's left as blue
  blue->setParent(yellow);//make yellow blue's parent
  if (blue->getRight() != NULL){
    blue->getRight()->setParent(blue);
  }
  if (parent != NULL){
    if (blue == parent->getLeft()){
      parent->setLeft(yellow);
    }
    else if (blue == parent->getRight()){
      parent->setRight(yellow);
    }
  }
  yellow->setParent(parent);
}

void rotateRight(Node* blue){
  if (blue->getLeft() == NULL){
    return;
  }
  Node* yellow = blue->getLeft();
  Node* parent = blue->getParent();
  blue->setLeft(yellow->getRight());
  yellow->setRight(blue);
  blue->setParent(yellow);
  if (blue->getLeft() != NULL){
    blue->getLeft()->setParent(blue);
  }
  if (parent != NULL){
    if (blue == parent->getLeft()){
      parent->setLeft(yellow);
    }
    else if (blue == parent->getRight()){
      parent->setRight(yellow);
    }
  }
  yellow->setParent(parent);
}


Node* insert(Node* root, Node* node){
  add(node, root);
  rearrange(node);
  root = node;
  while(root->getParent() != NULL){
    root = root->getParent();
  }
  return root;
}
 
void add(Node* current, Node* node){//adds a new node with integer value and returns the root each time (in case of NULL tree)
  if (current == NULL){//if nothing in tree
    current = node;
    return; 
  }
  if (node->getValue() < current->getValue()){//value is smaller than current node, go to left child
    if (current->getLeft()){
      add(current->getLeft(), node);
      return;
    }
    else{
      current->setLeft(node);
    }
  }
  else{//value is larger (or equal to) go right
    if (current->getRight()){
      add(current->getRight(), node);
    }
    else{
      current->setRight(node);
    }
    
  }
  node->setParent(current);
  node->setColor(2);
}

void rearrange(Node* current){
  if (current->getParent() == NULL){
    current->setColor(1);
  }
  else if (current->getParent()->getColor() == 1){
    //nothing
  }
  else if (current->getUncle() != NULL && current->getUncle()->getColor() == 2){
    case3(current);
  }
  else{
    case4(current);
  }
}


void case3(Node* current){
  current->getParent()->setColor(1);
  current->getUncle()->setColor(1);
  current->getGrandparent()->setColor(2);
  rearrange(current->getGrandparent());
}

void case4(Node* current){
  Node* parent = current->getParent();
  Node* grandparent = current->getGrandparent();
  if (current == parent->getRight() && parent == grandparent->getLeft()){
    rotateLeft(parent);
    current = current->getLeft();
  }
  else if (current == parent->getLeft() && parent == grandparent->getRight()){
    rotateRight(parent);
    current = current->getRight();
  }
  case4part2(current);
}

void case4part2(Node* current){
  Node* parent = current->getParent();
  Node* grandparent = current->getGrandparent();
  if (current == parent->getLeft()){
    rotateRight(grandparent);
  }
  else{
    rotateLeft(grandparent);
  }
  parent->setColor(1);
  grandparent->setColor(2);
}

void print(Node* current, int depth){
  print(current->getRight(), depth+1);//incrementing tabs to bottom most right
  for(int i = 0; i < depth; i++){//print the amount of tabs, then print value
    cout << "\t";
  }
  cout << current->getColor() << current->getValue() << endl;
  print(current->getLeft(), depth+1);//end at bottom most left node
}
