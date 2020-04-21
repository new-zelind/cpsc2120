#include <string>
#include <fstream>
#include <iostream>
#include "stringset.h"

using namespace std;

void spellcheck(void)
{
   Stringset S;
   string word;

   ifstream wordfile("words.txt");
   while (wordfile >> word)
	  S.insert(word);
   wordfile.close();

   cout << "Dictionary loaded.  Please enter words to spell check.\n";

   while (cin >> word) {
	  cout << "Possible alternatives for word '" << word << "':\n";
	  
	  //Create a copy of the provided word to use as reference
	  string copy = word;

	  //Iterate through each character of the word
	  for(unsigned int i=0; i<word.length(); i++){

		 //reset the original word after each list of changes
		 word = copy;
		 for(char j='a'; j<='z'; j++){

			//Each character in the initial word change to a all 25 other
			//alphabetical letters. If the changed word and copy don't
			//match, then check to see if the word exists in the dictionary.
			//If so, print out the word. Otherwise, don't do anything.
			word[i]=j;
			if(word != copy){
			   if(S.find(word)==true){
				  cout<<word<<endl;
			   }
			}
		 }
	  }
   }
}

void test(void)
{
  Stringset S;
  string key, command;

  while(cin >> command) {
    
    if (command == "insert") {
      
      cin >> key;
      if (S.find(key))
	cout << "Error!  Key " << key << " already in structure!\n";
      else
	S.insert(key);

    } else if (command == "remove") {
      
      cin >> key;
      if (!S.find(key)) 
	cout << "Error!  Key " << key << " not in structure!\n";
      else
	S.remove(key);

    } else if (command == "find") {

      cin >> key;
      if (S.find(key))
	cout << "Key " << key << " present.\n";
      else
	cout << "Key " << key << " absent.\n";

    } else if (command == "print") {

      cout << "Contents of structure:\n";
      S.print();

    } else if (command == "quit") {

      break;

    } else {

      cout << "Error!  Unknown command '" << command << "'!\n";

    }
  }
}

int main(void)
{
  //test();
  spellcheck();
  return 0;
}
