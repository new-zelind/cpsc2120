//Zach Lindler
//CPSC 2120
//Dr. Dean
//HW1, driver.cpp

#include "engine.h"

int main(void){
   Engine E;
   fstream infile;
   infile.open("webpages.txt");
   
   string URL, data, temp;
   while(infile >> URL){
	  if(URL == "NEWPAGE"){
		 infile >> URL;
		 E.insertURL(URL);
	  }
   }

   cout<<E.numPages<<" pages."<<endl;

   infile.clear();
   infile.seekg(0);

   while(infile >> data){
	  if(data == "NEWPAGE"){
		 infile >> temp;
	  }
	  if(data[0]=='h' && data[1]=='t' && data[2]=='t' && data[3]=='p' && data[4]==':'){
		 if(E.find(data)){
			E.insertLink(data, URL);
		 }
	  }
	  else{
		 E.insertWord(data, URL);
	  }
   }

   cout<<E.numLinks<<" links, "<<E.numWords<<" words."<<endl;

   infile.close();

   E.pageRank();

   return 0;
}
