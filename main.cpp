#include "Node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int a, int b);
bool search(Node* current, int value);
Node* addToTree(Node* current, int value);
Node* removeFromTree(Node* &current);
void printOutput(Node* current);
Node* find(Node* current, int value);
Node* successorRight(Node* current);
Node* successorLeft(Node* current);
//Node* getParent(Node* current, int value);
void printTree(Node* current, int depth);

int main(){
  bool loop = true;
  char* name = new char[20];
  char* input = new char[2000];
  Node* root = NULL;
  while (loop == true){
    cout << "Enter the name of the file: " << endl;
    cin.getline(name, 20, '\n');
    ifstream fileStream (name);
    if (fileStream.is_open()){
      fileStream.getline(input, 200);
      loop = false;
    }
    else{
      cout << "Invalid file name." << endl;
    }
    fileStream.close();
  }
  int* numberInput = new int[101];
  int size = 0;
  charToIntegerArray(input, numberInput, size);
  cout << "Integer Array:" << endl;
  for (int i = 0; i < (size); i++){
    cout << numberInput[i] << ",";
  }
  for (int i = 0; i < (size); i++){
    root = addToTree(root, numberInput[i]);
  }
  loop = true;
  cout << endl;
  int value = 0;
  while (loop = true){
    cout << "Type in a keyword (\"ADD\", \"SEARCH\",\"REMOVE\", \"OUTPUT\", \"TREE\" or \"QUIT\"):"<<endl;
    cin >> name; //put input into char array keyword
    cin.ignore();
    if (strcmp(name, "ADD") == 0){//if the input is ADD
      cout << "Enter the number you want to add: ";
      cin >> value;
      addToTree(root, value);
      cout << endl;
    }
    else if (strcmp(name, "SEARCH") == 0){//Similar to above
      cout << "Enter the number you want to search: ";
      cin >> value;
      if (search(root, value) == true){
	cout << "The number " << value << " exists within the tree.";
      }
      else {
	cout << "The number " << value << " does not exist within the tree.";
      }	
      cout << endl;
    }
    else if (strcmp(name, "REMOVE") == 0){
      cout << "Enter the number you want to remove: ";
      cin >> value;
      if(search(root, value) == true){
	Node* temp = find(root, value);
	root = removeFromTree(temp);
      }
      else {
	cout << "Not a valid number.";
      }
      cout << endl;
    }
    else if (strcmp(name, "OUTPUT") == 0){
      printOutput(root);
      cout << endl;
    }
    else if (strcmp(name, "TREE") == 0){
      cout << endl;
      printTree(root,0);
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

Node* addToTree(Node* current, int value){ 
  if (current == NULL){
    Node* temp = new Node(value);
    return temp; 
  }
  if (value < current->getValue()){
    current->setLeft(addToTree(current->getLeft(), value));
  }
  else{
    current->setRight(addToTree(current->getRight(), value));
  } 
} 

//Professor Fant's slides
void printOutput(Node* current){
  if (current != NULL){
    printOutput(current->getLeft());
    cout << current->getValue() << ",";
    printOutput(current->getRight());
  } 
}


bool search(Node* current, int value){
  while (current != NULL){
    if (value == current->getValue()){
      return true;
    }
    if (value < current->getValue()){
      return search(current->getLeft(), value);
    }
    if (value > current->getValue()){
      return search(current->getRight(), value);
    }
  }
  return false;
}

Node* find(Node* current, int value){
  if (current == NULL){
    return current;
  }
  if (value == current->getValue()){
    return current;
  }
  if (value < current->getValue()){
    return find(current->getLeft(), value);
  }
  if (value > current->getValue()){
    return find(current->getRight(), value);
  }
}

Node* successorRight(Node* current){
  if (current->getLeft() == NULL){
    return current;
  }
  else{
    return successorRight(current->getLeft());
  }
}

Node* successorLeft(Node* current){
  if (current->getRight() == NULL){
    return current;
  }
  else{
    return successorLeft(current->getRight());
  }
}

Node* removeFromTree(Node* &current){
  if (current == NULL){
    return current;
  }
  else if (current->getLeft() == NULL){
    Node* right = current->getRight();
    delete current;
    return right;
  }
  else if(current->getRight() == NULL){
    Node* left = current->getLeft();
    delete current;
    return left;
  }
  else{
  }
  
}

void printTree(Node* current, int depth){
  if (current == NULL){
    return;
  }
  printTree(current->getRight(), depth+1);
  for(int i = 0; i < depth; i++){
    cout << "\t";
  }
  cout << current->getValue() << endl;
  printTree(current->getLeft(), depth+1);
}


  
/*void removeFromTree(Node* &root, Node* current, int value){
  if (value < current->getLeft()->getValue()){
    removeFromTree(root, current->getLeft(), value);
  }
  if (value > current->getRight()->getValue()){
    removeFromTree(root, current->getRight(), value);
  }
  if (current->getLeft() == NULL && current->getRight() == NULL){//a leaf
    if (getParent(root, current->getValue()) == NULL){
      current->setValue(0);
      return;
    }
    if (current->getValue() <= getParent(root, current->getValue())->getValue()){
      getParent(root, current->getValue())->setLeft(NULL);
    }
    else{
      getParent(root, current->getValue())->setRight(NULL);
    }
    delete current;
    current = NULL;
  }
  else if (current->getLeft() == NULL){//only right leaf
    Node* temp = current->getRight();
    if (getParent(root, current->getValue()) == NULL){
      current->setValue(temp->getValue());
      current->setRight(temp->getRight());
      current->setLeft(temp->getLeft());
      getParent(root, temp->getLeft()->getValue()) = current;
      if (temp->getLeft() != NULL){
	getParent(root, temp->getLeft()->getValue()) = current;
      }
      if (temp->getRight() != NULL){
	getParent(root, temp->getRight()->getValue()) = current;
      }
      delete temp;
    }
    else{
      Node* parent = getParent(root, current->getValue());
      delete current;
      current = NULL;
      if (temp->getValue() <= parent->getValue()){
	parent->setLeft(temp);
      }
      else{
	parent->setRight(temp);
      }
      getParent(root, temp->getValue()) = parent;
    }
  }
  else if (current->getRight() == NULL){//only left leaf
    Node* temp = current->getLeft();
    if (getParent(root, current->getValue()) == NULL){
      current->setValue(temp->getValue());
      current->setRight(temp->getRight());
      current->setLeft(temp->getLeft());
      getParent(root, temp->getLeft()->getValue()) = current;
      if (temp->getLeft() != NULL){
        getParent(root, temp->getLeft()->getValue()) = current;
      }
      if (temp->getRight() != NULL){
        getParent(root, temp->getRight()->getValue()) = current;
      }
      delete temp;
    }
    else{
      Node* parent = getParent(root, current->getValue());
      delete current;
      current = NULL;
      if (temp->getValue() <= parent->getValue()){
        parent->setLeft(temp);
      }
      else{
        parent->setRight(temp);
      }
      getParent(root, temp->getValue()) = parent;
    }
  }
  else{//has both left and right child
    return;
  }
  }/*
  
/*
Node* getParent(Node* current, int value){
  if (current == NULL || (current->getLeft() == NULL && current->getRight() == NULL)){
    return NULL;
  }
  else if (current->getLeft() != NULL && current->getLeft()->getValue() == value){
    return current;
  }
  else if (current->getRight() != NULL && current->getRight()->getValue() == value){
    return current;
  }
  if (value < current->getValue()){
    return getParent(current->getLeft(), value);
  }
  if (value > current->getValue()){
    return getParent(current->getRight(), value);
  }
}
*/
