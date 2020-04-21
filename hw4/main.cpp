// Zach Lindler
// CPSC 2120
// Dr. Dean
// Homework 4, main.cpp

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <cmath>
#include "graphics.h"
using namespace std;

// Each point represents (x, y, z=elevation above sea level)
// units are in feet; x and y increase to the east and north, respectively
struct Point {
  double x, y, z;
};

// node struct
struct Node{
   double data[2];
   double z;
   int index;
   Node* left;
   Node* right;
   Node(double x, double y, double _z, int i){
	  data[0] = x;
	  data[1] = y;
	  z = _z;
	  index = i;
	  left = right = NULL;
   }
};

// KD Tree declaration
Node* T = NULL;

// KD Tree insert function
Node* kdInsert(Node* T, double x, double y, double z, int dim, int i){
   if(T == NULL) return new Node(x, y, z, i);
   if(dim == 0){
	  if(T->data[0] > x) T->left = kdInsert(T->left, x, y, z, (dim+1)%2, i);
	  else T->right = kdInsert(T->right, x, y, z, (dim+1)%2, i);
   }
   else{
	  if(T->data[1] > y) T->left = kdInsert(T->left, x, y, z, (dim+1)%2, i);
	  else T->right = kdInsert(T->right, x, y, z, (dim+1)%2, i);
   }
   return T;
}

//Nearest neighbors Priority Queue
priority_queue <pair<double, int>> q;

//calc distance
double dist(double x1, double y1, double x2, double y2){
   return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

//Nearest neighbor function
void findNeighbors(Node* T, const double x, const double y, int dim){
   if(T == NULL) return;

   double dst = dist(x, y, T->data[0], T->data[1]);
   
   q.push(make_pair(dst, T->index));
   if(q.size() > 10){
	  q.pop();
   }
   
   if(dim == 0){
	  if(T->data[0] < x){
	     findNeighbors(T->right, x, y, (dim+1)%2);
	  }
	  else {
		 findNeighbors(T->left, x, y, (dim+1)%2);
	  }
	  if(q.top().first > abs(T->data[0] - x)){
		 if(T->data[0] < x){
			findNeighbors(T->left, x, y, (dim+1)%2);
		 }
		 else{
			findNeighbors(T->right, x, y, (dim+1)%2);
		 }
	  }
   }
   else{
	  if(T->data[1] < y){
		 findNeighbors(T->right, x, y, (dim+1)%2);
	  }
	  else{
		 findNeighbors(T->left, x, y, (dim+1)%2);
	  }
	  if(q.top().first > abs(T->data[1] - y)){
		 if(T->data[1] < y){
			findNeighbors(T->left, x, y, (dim+1)%2);
		 }
		 else{
			findNeighbors(T->right, x, y, (dim+1)%2);
		 }
	  }
   }
}

// All the points in our LIDAR data set
vector<Point> all_points;

Point mins, maxes; // highest and lowest values in dataset
Point winmin, winmax; // corners of window being displayed on screen

// Size of our window on screen
double window_xsize = 1000, window_ysize = 800;

// Source and destination nodes for shortest path calculation
int source_node = -1;
int destination_node = -1;

//create maps and vectors, as well as vals for dijkstra's algorithm
map<int, double> dists;
vector<int> pred;
bool isPath, alreadyRendered;
double x1, x2, y_1, y2, z1, z2;

// Dijkstra's Algorithm
bool dijkstra(void){

   //init vars
   alreadyRendered = false;
   set <pair<double, int> > S;
   
   //You have been asleep for 9999999 days
   const double infinity = 9999999;
   
   //initialize all points distances to infinity
   for(unsigned int i=0; i<all_points.size(); i++) dists[i] = infinity;
   
   //set distance from the source node to 0
   dists[source_node] = 0.0;

   //insert the first make_pair value
   S.insert(make_pair(dists[source_node], source_node));
   
   //while the Stack of distances is not empty
   while(!S.empty()){
	  //find the next closest point
	  int to_visit = S.begin()->second;
	  //if this is our destination, return true - we're done
	  if(to_visit == destination_node) return true;

	  //otherwise, erase the beginning of the stack and call findNeighbors
	  S.erase(S.begin());
	  findNeighbors(T, all_points.at(to_visit).x, all_points.at(to_visit).y, 0);
	  
	  //dijkstra witchcraft
	  while(!q.empty()){
		 pair<int, int> edge = make_pair(to_visit, q.top().second);
		 
		 x1 = all_points.at(edge.first).x;
		 x2 = all_points.at(edge.second).x;
		 y_1 = all_points.at(edge.first).y;
		 y2 = all_points.at(edge.second).y;
		 z1 = all_points.at(edge.first).z;
		 z2 = all_points.at(edge.second).z;
		 
		 double tempDist = sqrt(pow(x1 - x2, 2) + pow(y_1 - y2, 2) + pow(z1 - z2, 2));
		 	 
		 if(abs((z2 - z1) / sqrt(pow(x1 - x2, 2) + pow(y_1 - y2, 2))) <= 1){	
			if(dists[to_visit] + tempDist < dists[edge.second]){
			   dists[edge.second] = dists[to_visit] + tempDist;
			   S.insert(make_pair(dists[edge.second], edge.second));
			   pred.at(edge.second) = to_visit;
			}
		 }
		 q.pop();
	  }
   }
   return false;
}

// clear the queue
void clearQueue(){
   while(!q.empty()){
	  q.pop();
   }
}

// Returns where on the screen to plot a point, offsetting it slightly based on elevation
// from its usual (x,y) location to make tall things look tall
pair<double,double> get_point_screen_location(Point &p)
{
  double x = (p.x - winmin.x) / (winmax.x - winmin.x) * window_xsize;
  double y = window_ysize - (p.y - winmin.y) / (winmax.y - winmin.y) * window_ysize;
  double offset = (p.z - 700) / 5; // how much we offset pixel to emphasize its height
  return make_pair(x-offset, y-offset);
}

// Called whenever a key is pressed
void keyhandler(int key)
{
  double x_range = winmax.x - winmin.x;
  double y_range = winmax.y - winmin.y;  
  double x_center = winmin.x + x_range/2;
  double y_center = winmin.y + y_range/2;

  if (key == KEY_LEFT) { winmin.x -= x_range/10; winmax.x -= x_range/10; }
  if (key == KEY_RIGHT) { winmin.x += x_range/10; winmax.x += x_range/10; }
  if (key == KEY_UP) { winmin.y += y_range/10; winmax.y += y_range/10; }
  if (key == KEY_DOWN) { winmin.y -= y_range/10; winmax.y -= y_range/10; }

  if (key == '=') { // Zoom in
    winmin.x = x_center - x_range / 2 * 0.8;
    winmax.x = x_center + x_range / 2 * 0.8;
    winmin.y = y_center - y_range / 2 * 0.8;
    winmax.y = y_center + y_range / 2 * 0.8;
  }
  if (key == '-') { // Zoom out
    winmin.x = x_center - x_range / 2 / 0.8;
    winmax.x = x_center + x_range / 2 / 0.8;
    winmin.y = y_center - y_range / 2 / 0.8;
    winmax.y = y_center + y_range / 2 / 0.8;
  }

  if (key == 'n') { // test nearest neighbors
	clearQueue();
	findNeighbors(T, x_center, y_center, 0);
  }
  
  if (key == 's') { // set source
	clearQueue();
    findNeighbors(T, x_center, y_center, 0);
	while(q.size() != 1) q.pop();
	source_node = q.top().second;
    cout << "Set source node = " << source_node << "\n";
  }
  if (key == 'd') { // set destination and compute shortest path	
	clearQueue();
    findNeighbors(T, x_center, y_center, 0);
	while(q.size() != 1) q.pop();
    destination_node = q.top().second;
    cout << "Set destination node = " << destination_node << "\n";
  }
  if ((key == 's' || key == 'd') && source_node != -1 && destination_node != -1) {
    cout << endl << "Computing shortest path from source to destination...\n";
	// TBD: compute shortest path from source to destination and record it so it can be
	// visualized
    // if no path (e.g., all paths would require stepping at more than a 45 degree 
	// incline, print "No path". If there is a path, print its length in feet
	  clearQueue();
	  isPath = dijkstra();
	  if(isPath == false) cout << "No path." << endl;
  }
  
  if (key == 'q') exit(0);
}

// Called whenever we need to re-render the current window
void render(void)
{
  // Feel welcome to turn off this message if you want...
  //cout << "Rendering (" << winmin.x << "," << winmin.y;
  //cout << ") - (" << winmax.x << "," << winmax.y << ")\n";

  for (Point &p : all_points) {
    pair<double, double> loc = get_point_screen_location(p);
    double x = loc.first, y = loc.second;
    if (x >= 0 && y >= 0 && x < window_xsize && y < window_ysize) {
      double color = min(1.0, max(0.0, (p.z - 700) / 80.0)); 
	  // color in range [0,1] based on height
      set_color (color, 0.8, 0.5);
      draw_pixel (x, y);
    }
  }

  // Draw small crosshairs at center of window
  set_color(1,1,1);
  draw_line(window_xsize/2-3, window_ysize/2, window_xsize/2+3, window_ysize/2);
  draw_line(window_xsize/2, window_ysize/2-3, window_xsize/2, window_ysize/2+3);
  
  // highlight points returned in response to asking for nearest neighbors
   while(!q.empty()){
	  set_color(1, 0, 0);
	  Point pt;
	  pt = all_points.at(q.top().second);
	  pair<double, double> loc = get_point_screen_location(pt);
	  draw_line(loc.first-3, loc.second, loc.first+3, loc.second);
	  draw_line(loc.first, loc.second-3, loc.first, loc.second+3);
	  q.pop();
   }
  
   // plot sequence of line segments depicting shortest path, if one has been computed
   if(isPath == true && alreadyRendered == false){
	  cout << "Source Node: " << source_node;
	  cout << ", Destination Node: " << destination_node << endl;
	  int tempNode = destination_node;
	  
	  while(source_node != tempNode){
		 set_color(1, 0, 0);
		 
		 pair<double, double> point1 = get_point_screen_location(
		   all_points.at(tempNode));
		 pair<double, double> point2 = get_point_screen_location(
		   all_points.at(pred.at(tempNode)));
		 
		 double x = point1.first;
		 double y = point1.second;
		 double x_2 = point2.first;
		 double y_2 = point2.second;
		 
		 draw_line(x, y, x_2, y_2);
		 tempNode = pred.at(tempNode);
	  }
	  cout << "Path Distance: " << dists[destination_node] << " feet" << endl;
	  alreadyRendered = true;
   }
}

int main(int argc, char *argv[])
{
  // Read in all the data
  ifstream fin ("points.txt");
  Point p;
  // int count = 0;
  while (fin >> p.x >> p.y >> p.z){
	 all_points.push_back(p);
	 pred.push_back(0);
  }
    
  // Find initial view window corner points
  mins = maxes = all_points[0];
  for (auto &p : all_points) {
    mins.x = min(mins.x, p.x);
    mins.y = min(mins.y, p.y);
    mins.z = min(mins.z, p.z);
    maxes.x = max(maxes.x, p.x);
    maxes.y = max(maxes.y, p.y);
    maxes.z = max(maxes.z, p.z);
  }
  // Re-adjust y to match aspect ratio of window
  winmin = mins; winmax = maxes;
  winmax.y = winmin.y + (winmax.x - winmin.x) * window_ysize / window_xsize;

  //build kd tree
  for(unsigned int i=0; i < all_points.size(); i++){
	 T = kdInsert(T, all_points.at(i).x, all_points.at(i).y, all_points.at(i).z, 0, i);
  }
  
  // Launch graphics; all remaining interaction is via callback to render and keyhandler function
  init_graphics(argc, argv, window_xsize, window_ysize, render, keyhandler);
  return 0;
}
