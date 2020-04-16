#include "Node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int a, int b);
Node* add(Node* current, int value);
void print(Node* current, int depth);


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
      root = add(root, value);//insert new value into tree
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
	root = add(root, numberInput[i]);//addToTree returns the root each time
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

Node* add(Node* current, int value){//adds a new node with integer value and returns the root each time (in case of NULL tree)
  if (current == NULL){//if nothing in tree
    Node* temp = new Node(value);
    return temp; 
  }
  if (value < current->getValue()){//value is smaller than current node, go to left child
    Node* child = add(current->getLeft(), value);
    child->setParent(current); //after reach a leaf, set the child parent relationship
    current->setLeft(child);
    
  }
  else{//value is larger (or equal to) go right
    Node* child = add(current->getRight(), value);
    child->setParent(current); //after reach a leaf, set child parent relationship
    current->setRight(child);
  }
  return current;
}

void print(Node* current, int depth){
  if (current = NULL){
    return;
  }
  print(current->getRight(), depth+1);//incrementing tabs to bottom most right
  for(int i = 0; i < depth; i++){//print the amount of tabs, then print value
    cout << "  ";
  }
  cout << current->getColor() << current->getValue() << endl;
  print(current->getLeft(), depth+1);//end at bottom most left node
}
