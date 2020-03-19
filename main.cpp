#include "Node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int a, int b);
bool search(Node* current, int value);
Node* addToTree(Node* current, int value);
void removeFromTree(Node* &root, Node* &current);
void printSort(Node* current);
Node* getNode(Node* current, int value);
Node* successorRight(Node* current);
void printTree(Node* current, int depth);

/*3/19/2020 Author: Maggie Bao Description: The program takes a list 
of numbers from a text file and converts it into a binary search tree. 
The user could be able to add, search, and remove nodes from the tree. 
Additionally, the user could print out a visual of the sideways tree 
and print out the sorted output.*/


int main(){
  bool loop = true;
  char* name = new char[20];
  char* input = new char[2000];
  Node* root = NULL;
  while (loop == true){//Read file input code modified from my Heap assignment
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
  int* numberInput = new int[101];
  int size = 0;
  charToIntegerArray(input, numberInput, size);//convert char* to int * array
  /*cout << "Integer Array:" << endl;
  for (int i = 0; i < (size); i++){
    cout << numberInput[i] << ",";
  }*/
  for (int i = 0; i < (size); i++){//insert integers into tree, one by one
    root = addToTree(root, numberInput[i]);//addToTree returns the root each time
  }
  loop = true;
  cout << endl;
  int value = 0;
  while (loop = true){
    cout << "Type in a keyword (\"ADD\", \"SEARCH\",\"REMOVE\", \"SORT\", \"TREE\" or \"QUIT\"):"<<endl;
    cin >> name; //put input into char array keyword
    cin.ignore();
    if (strcmp(name, "ADD") == 0){//if the input is ADD
      cout << "Enter the number you want to add: ";
      cin >> value;
      root = addToTree(root, value);//insert new value into tree
      cout << endl;
    }
    else if (strcmp(name, "SEARCH") == 0){//Similar to above
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
    else if (strcmp(name, "REMOVE") == 0){
      cout << "Enter the number you want to remove: ";
      cin >> value;
      if(search(root, value) == true){//first checks if deleting value is within the tree
	Node* temp = getNode(root, value); //traverses to deleted node in "temp"
	removeFromTree(root, temp); //removes the node from tree
      }
      else {
	cout << "Not a valid number.";
      }
      cout << endl;
    }
    else if (strcmp(name, "SORT") == 0){
      printSort(root);//prints out sorted list, smallest to largest
      cout << endl;
    }
    else if (strcmp(name, "TREE") == 0){
      cout << endl;
      printTree(root,0);//prints visual of tree
    }
    else if (strcmp(name, "QUIT") == 0){//if quit, boolean is false so program will stop
      while (root != NULL){//keep on removing root until last root is removed. I'm not sure why this sends an error
	removeFromTree(root, root);
      }
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

//pow and charToIntegerArray function copied straight from my Heap assignment

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

Node* addToTree(Node* current, int value){//adds a new node with integer value and returns the root each time (in case of NULL tree)
  if (current == NULL){//if nothing in tree
    Node* temp = new Node(value);
    return temp; 
  }
  if (value < current->getValue()){//value is smaller than current node, go to left child
    Node* child = addToTree(current->getLeft(), value);
    child->setParent(current); //after reach a leaf, set the child parent relationship
    current->setLeft(child);
    
  }
  else{//value is larger (or equal to) go right
    Node* child = addToTree(current->getRight(), value);
    child->setParent(current); //after reach a leaf, set child parent relationship
    current->setRight(child);
  }
  return current;
} 

//Professor Fant's slides 
void printSort(Node* current){//Prints out the sorted tree from least to greatest
  if (current != NULL){
    printSort(current->getLeft());
    cout << current->getValue() << ",";
    printSort(current->getRight());
  } 
}


bool search(Node* current, int value){//Searches for a node with matching value as user input. If not found, return false.
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

Node* getNode(Node* current, int value){//Returns the node in which the value matches up to. Used for delete function
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

void removeFromTree(Node* &root, Node* &current){
  if (current == NULL){
    return;
  }
  if (current->getLeft() == NULL && current->getRight() == NULL){//Case 1
    if (current->getParent() == NULL){//if root
      Node* temp = current;
      current = NULL;
      return;
    }
    if(current == current->getParent()->getLeft()){//if it is the parent's left child, set to left child to null
      current->getParent()->setLeft(NULL);
    }
    else {//same for right child
      current->getParent()->setRight(NULL);
    }
    delete current;
    current = NULL;
    return;
  }
  else if (current->getLeft() != NULL && current->getRight() != NULL){//two child
    Node* successor = successorRight(current->getRight());
    int value = successor->getValue();
    removeFromTree(root, successor);
    current->setValue(value);
  }
  else if (current->getLeft() == NULL){//right child
    if (current->getParent() == NULL){
      root = current->getRight();
      root->setParent(NULL);
      delete current;
      return;
    }
    Node* right = current->getRight();
    if(current == current->getParent()->getLeft()){
      current->getParent()->setLeft(right);
    }
    else{
      current->getParent()->setRight(right);
      right->setParent(current->getParent());
      delete current;
    }
  }
  else{//left child
    if (current->getParent() == NULL){
      root = current->getLeft();
      root->setParent(NULL);
      delete current;
      return;
    }
    Node* left = current->getLeft();
    if(current == current->getParent()->getLeft()){
      current->getParent()->setLeft(left);
    }
    else{
      current->getParent()->setRight(left);
      left->setParent(current->getParent());
      delete current;
    }
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
