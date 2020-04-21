//Zach Lindler
//CPSC 2120
//Dr. Dean
//HW1, engine.h

#ifndef ENGINE_H
#define ENGINE_H

#include <fstream>
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;

struct Node{
   
   string word;
   Node * next;

   Node(){word = ""; next = NULL;}
   Node(string _word){
	  word = _word;
	  next = NULL;
   }
};

struct Webpage{
   
   string URL;
   double weight;
   double newWeight;
   int pageLinks;
   int pageWords;
   Node * Words;
   Node * Links;
   Webpage * next;
   
   Webpage(){
	  URL = "";
	  weight = -1;
	  newWeight = -1;
	  pageLinks = 0;
	  pageWords = 0;
	  Words = NULL;
	  Links = NULL;
	  next = NULL;
   }

   Webpage(string _URL, Webpage * _next){
	  URL = _URL;
	  weight = -1;
	  newWeight = -1;
	  pageLinks = 0;
	  pageWords = 0;
	  Words = NULL;
	  Links = NULL;
	  next = _next;
   }
};

class Engine{
   private:
	  Webpage** table;
	  int size;
	  int hash(string s, int tableSize);

   public:
	  int numPages;
	  int numLinks;
	  int numWords;

	  Engine();
	  void insertURL(string URL);
	  void insertLink(string link, string URL);
	  void insertWord(string word, string URL);
	  bool find(string key);
	  void pageRank();
	  ~Engine();

};

#endif
