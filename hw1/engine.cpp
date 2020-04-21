// Zach Lindler
// CPSC 2120
// HW1, engine.cpp

#include "engine.h"
using namespace std;

int Engine::hash(string s, int arrSize){
   unsigned int i, h = 0;
   for(i=0; i<s.length(); i++){
	  h = (h * 2917 + (unsigned int)s[i]) % arrSize;
   }
   return h;
}

Engine::Engine(){
   size = 4;
   table = new Webpage* [size];
   for(int i=0; i<size; i++){
	  table[i] = NULL;
   }
   numWords=0;
   numPages=0;
}

Engine::~Engine(){
   
}

void Engine::insertURL(string URL){
   int h;
   int newH;
   int oldSize;
   numPages++;
   if(numPages == size){
	  oldSize = size;
	  size *= 2;
	  Webpage ** newTable = new Webpage* [size];
	  for(int i=0; i<size; i++){
		 newTable[i] = NULL;
	  }

	  for(int j=0; j<oldSize; j++){
		 Webpage * oldCurr = table[j];
		 Webpage * oldTemp = NULL;

		 while(oldCurr != NULL){
			newH = hash(oldCurr->URL, size);
			newTable[newH] = new Webpage(oldCurr->URL, newTable[newH]);
			oldTemp = oldCurr;
			oldCurr = oldCurr->next;
			delete oldTemp;
		 }
	  }

	  delete[] table;
	  table = newTable;
   }
   h=hash(URL, size);
   table[h] = new Webpage(URL, table[h]);
}

void Engine::insertLink(string link, string URL){
   cout<<"starting link insert"<<endl;
   numLinks++;
   if(find(URL)){
	  for(int i=0; i<size; i++){
		 if(table[i]->URL == URL){
			Node * curr = table[i]->Links;
			while(1==1){
			   if(curr != NULL){curr = curr->next;}
			   else{
				  cout<<"link loop"<<endl;
				  Node * newNode = new Node(link);
				  curr->next = newNode;
				  delete curr;
				  return;
			   }
			}
		 }
	  }
   }
}

void Engine::insertWord(string word, string URL){
   cout<<"starting word insert"<<endl;
   numWords++;
   if(find(URL)){
	  cout<<"here"<<endl;
	  for(int i=0; i<size; i++){
		 cout<<"here"<<endl;
		 Webpage * curr = table[i];
		 if(curr->URL == URL){
			cout<<"here 1"<<endl;
			Node * currWord = curr->Words;
			while(true){
			   cout<<"here 2"<<endl;
				if(currWord!=NULL){currWord = currWord->next;}
				else{
				  cout<<"word loop"<<endl;
				  Node * newNode = new Node(word);
				  currWord->next = newNode;
				  delete curr;
				  return;
				}
			}
		 }
	  }
   }
}

bool Engine::find(string key){
   int h = hash(key, size);
   Webpage* n = table[h];
   while(n != NULL){
	  if(n->URL == key){
		 return true;
	  }
	  n = n->next;
   }
   return false;
}

void Engine::pageRank(){
   cout<<"Starting pagerank algorithm."<<endl;
   for(int i = 0; i<size; i++){
	  Webpage * tempPage = table[i];
	  while(tempPage != NULL){
		 tempPage->weight = (double)1/(double)numPages;
		 Node * tempLink = tempPage->Links;
		 while(tempLink != NULL){
			tempPage->pageLinks++;
			tempLink = tempLink->next;
		 }
		 tempPage = tempPage->next;
	  }
   }

   cout<<"Starting pass 2"<<endl;
   for(int j=0; j<50; j++){
	  for(int k=0; k<size; k++){	
		 Webpage* tempPage = table[k];
		 while(tempPage != NULL){
			tempPage->newWeight = 0.1/double(numPages);
			tempPage = tempPage->next;
		 }
	  }
	  for(int L=0; L<size; L++){
		 Webpage * tempPage = table[L];
		 int count = 0;
		 for(tempPage = table[L]; tempPage != NULL; tempPage = tempPage->next){
			count++;
		 }
		 cout<<count<<endl;
		 tempPage = table[L];
		 while(tempPage != NULL){
			cout<<L<<endl;
			cout<<count<<endl;
			Node * tempLink = tempPage->Links;
			while(tempLink != NULL){
			   tempPage->newWeight += 0.9*(tempPage->weight/(double)tempPage->pageLinks);
			   tempLink = tempLink->next;
			   cout<<tempPage->newWeight<<endl;
			}
		 tempPage = tempPage->next;
		 }
	  }

	  for(int m=0; m<size; m++){
		 Webpage* tempPage = table[m];
		 while(tempPage != NULL){
			tempPage->weight = tempPage->newWeight;
			tempPage = tempPage->next;
		 }
	  }
   }
   cout<<"Finishing up..."<<endl;
}
