#include "dst.h"

//Default constructor for Graph:
//Declares and initializes the 2D hash table containing linked lists of all
//the data points. Each of these buckets in the has table is initialized
//to NULL.
Graph::Graph(){
   size = 750;
   table = new Node ** [size];
   for (int i=0; i<size; i++){
	  table[i] = new Node * [size];
	  for(int j=0; j<size; j++){
		 table[i][j] = NULL;
	  }
   }
}

//Default deconstructor
//Iterates through each bucket in the hash table and deletes each linked
//list node by node. It then deletes the individual buckets in the hash
//table, and finally the table itself.
Graph::~Graph(){
   for(int i=0; i<size; i++){
	  for(int j=0; j<size; j++){
		 while(table[i][j] != NULL){
			Node * temp = table[i][j]->next;
			delete table[i][j];
			table[i][j] = temp;
		 }	  
	  }
   }

   for(int k=0; k<size; k++){
	  delete[] table[k];
   }

   delete [] table;
}

void Graph::readData(void){

   double x, y;
   
   //Declare the input file and read the data in.
   ifstream infile("points.txt");
   while(infile >> x >> y){
	  
	  //Insert a new data point.
	  insert(x, y);
   }

   //Close the file.
   infile.close();
}

void Graph::insert(double x, double y){

   //"Hash" each individual coordinate based on its location and cast
   //the resulting number as an integer.
   int xArr = (int) (x * size);
   int yArr = (int) (y * size);

   //Then, declare a new node in the hash table's location corresponding
   //to the coordinate's hash, and store it in that bucket.
   table[xArr][yArr] = new Node (x , y, table[xArr][yArr]);
}

void Graph::findDistance(void){
   double min = 1;		//Double that holds the minimum distance found.
   double dist = 1.1;	//Double that holds each distance calculation.
   
   //Iterate through each bucket in the superimposed "array" on the grid.
   for(int i=0; i<size; i++){
	  for(int j=0; j<size; j++){

		 //Declare a pointer node that points to the current array square.
		 for(Node * curr = table[i][j]; curr; curr = curr->next){

			//these two loops then ensure that each square around it is
			//compared to the current square.
			for(int a=(i-1); a<=(i+1); a++){
			   for(int b=(j-1); b<=(j+1); b++){

				  //out of bounds checking to prevent segfaults.
				  if(a>=0 && b>=0 && a<size && b<size){

					 //declares a new node pointer that points to each
					 //member of the linked list
					 for(Node * curr2 = table[a][b]; curr2; curr2 = curr2->next){
						
						//If the two nodes are pointing to the same square
						//in the array, then an issue will occur in the
						//calculations. Don't do it if they're equal.
						if(curr != curr2){

						   //The distance formula!
						   dist = sqrt(pow((curr->x - curr2->x), 2) + pow((curr->y - curr2->y), 2));

						   //Check to see if the distace calculated is less
						   //than the minimum distance so far. If it is,
						   //update the minimum distance.
						   if(dist < min){min = dist;}
						}
					 }
				  }
			   }
			}
		 }
	  }
   }

   //Print the value of the minimum distance.
   cout<<"The minimum distance between two points is "<<min<<"."<<endl;
}
