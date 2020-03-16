#include "Node.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
void charToIntegerArray(char* carray, int* &iarray, int &size);
int pow(int a, int b);
void sort();
bool search();
void addToTree(Node* );
void removeFromTree();
void printTree();


int main(){
  bool loop = true;
  char* name = new char[20];
  char* input = new char[200];
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
  int* numberInput = new int [101];
  int size = 0;
  charToIntegerArray(input, numberInput, size);
  cout << "Integer Array:" << endl;
  for (int i = 0; i < (size); i++){
    cout << numberInput[i] << ",";
  }
  loop = true;
  while (loop = true){
    cout << "Type in a keyword (\"ADD\", \"SEARCH\",\"REMOVE\", \"PRINT\", or \"QUIT\"):"<<endl;
    cin >> name; //put input into char array keyword
    cin.ignore();
    if (strcmp(name, "ADD") == 0){//if the input is ADD
      cout << endl; //formatting
      addToTree();
      cout << endl;
    }
    else if (strcmp(name, "SEARCH") == 0){//Similar to above
      cout << endl;
      search();
      cout << endl;
    }
    else if (strcmp(name, "REMOVE") == 0){
      cout << endl;
      removeFromTree();
      cout << endl;
    }
    else if (strcmp(name, "PRINT") == 0){
      cout << endl;
      printTree();
    }
    else if (strcmp(name, "QUIT") == 0){//if quit, boolean is false so program will stop
      cout << "Have a nice day!" << endl;
      loop = false;
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
