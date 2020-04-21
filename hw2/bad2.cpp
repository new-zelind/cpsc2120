// Zach Lindler
// CPSC 2120
// Dr. Dean
// HW2, bad2.cpp

#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]){
   
   //command line argument verification
   if(argc != 2){
	  cout << "Usage: bad2 <input size>\n" << endl;
	  return 1;
   }

   //store the size provided on the command line
   int size = atoi(argv[1]);

   //check to see if the size provided isn't negative
   if(size <= 0){
	  cout << "Invalid input size" << endl;
	  return 1;
   }

   //print the size to the file
   cout << size << endl;

   //since the hash function in prog2 hashes by 10,000,
   //we'll fill an array with multiples of 10,000. This
   //means that every value will hash to the same value,
   //and will force the program's find function to read
   //through the entire array every time something is
   //inserted
   for(int i=1; i<=size; i++){
	  cout << i * 10000 << endl;
   }

   return 0;
}
