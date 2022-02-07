#include "graphm.h"

//-----------------------------------------------------------------------------
// default constructor: initialize C and T (most of T is initialize when the 
// array is created. Set T and C to 0 when i == j because source to source 
// must output 0
GraphM::GraphM(){
	for (int i = 0; i < MAXNODES; i++){
		for (int j = 0; j < MAXNODES; j++){
			if (i == j){ 
				C[i][j] = 0;      
				T[i][j].dist = 0; 
			}
			else {
				C[i][j] = INT_MAX;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// buildGraph: add the data from a file to the data, T and C array
// first: read the size and increment by one because index 0 is never used
// second: create a for loop to read all the data 
// third: read the from, to node with its weigth
// stop when the file reaches 0
void GraphM::buildGraph(istream& file){
	// from, to and it's weight of each edge
	int from, to, weight;

	file >> size;         // read size is int
	size++;
	if (file.eof()) {
		return;
	}
	change = true;

	string s;
	getline(file, s);

	
	for (int i = 1; i < size; i++) { // store data from file
		data[i].setData(file);
	}
		
	file >> from >> to >> weight;
	
	while (from > 0){ //stops when it reaches 0
		if (from < 0 || to <= 0 || from == to || from > size || to > size || (weight <= 0 && from != to)) {
			file >> from >> to;
		}
		else if (from != 0 || to != 0) {
			C[from][to] = weight;
		}
		file >> from >> to >> weight;
	}
}

//-----------------------------------------------------------------------------
// insertEdge: add an edge in the array by taking the input from, to and weight
// update the value change to true as changes were made
// return true if an item was added
bool GraphM::insertEdge(int from, int to, int weight){
	if (weight <= 0 || from <= 0 || from > size || to <= 0 || to > size 
		|| from == to) {
		return false;
	}
	else{
		C[from][to] = weight;
		change = true;
		return true;
	}
}

//-----------------------------------------------------------------------------
// removeEdge: change C[from][to] to zero
// update change to true
// return true if an item was deleted
bool GraphM::removeEdge(int from, int to){
	//return false if parameter is invalidtry or try remove inexist edge
	if (from <= 0 || from > size || to <= 0 || to > size || from == to
		|| C[from][to] == INT_MAX) {
		return false;
	}
	else{
		//set the weight of that edge to infinity, which means no edge
		C[from][to] = INT_MAX;
		//since remove an edge in graph, set change to true
		change = true;
		return true;
	}
}

//-----------------------------------------------------------------------------
// findShortestPath: call oneSourceShortestPath which will find the shortest 
// with a given source node. Use a for loop to do all sources
// update change to false
void GraphM::findShortestPath(){
	for (int i = 1; i < size; i++){
		dijkstra(i);
	}
	change = false;
}

//-----------------------------------------------------------------------------
// dijkstra: use dijkstra algorithm to find the shortest path
// everytime a node is search, set it to true
void GraphM::dijkstra(int source){
	for (int i = 1; i < size - 1;i++){
		int v = minDistance(source);	// find the shortest adjacent node
		if (v == -1) { // if the shortest distance was not found then break the loop
			break;       
		}

		T[source][v].visited = true;	
		// find the shortest distance from source to all other nodes
		for (int w = 1; w < size; w++){
			if (C[v][w] < INT_MAX && !T[source][w].visited)
				if (T[source][v].dist + C[v][w] < T[source][w].dist){
					T[source][w].dist = T[source][v].dist + C[v][w];
					T[source][w].path = (v == source ? 0 : v);
				}
		}
	}
}

//-----------------------------------------------------------------------------
// minDistance: return the index/node with the smallest distance between
// the source and the node
// if it is not found then return -1
int GraphM::minDistance(int from){
	int minNode = -1;
	int minValue = INT_MAX; //initial minValue to infinity
	for (int i = 1; i < size; i++){
		//find the shorter distance node and not visited yet  
		if (!T[from][i].visited && T[from][i].dist < minValue){
			minNode = i;
			minValue = T[from][i].dist;
		}
	}
	return minNode;
}

//-----------------------------------------------------------------------------
// displayAll: display all path from source to size with its path 
// Format -- Description  From node  To node  Dijkstra's  Path
// also display the data from data[]
// don't output the path when the source == end node
void GraphM::displayAll()const{
	cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
		<< setw(13) << "Dijkstra's" << setw(10) << "Path" << endl;

	for (int i = 1; i < size; i++){
		cout << data[i] << endl; //display data
		for (int j = 1; j < size; j++){
			if (i != j){
				cout << setw(20) << "";
				stack<int> path; // use a stack to output in correct order
				displayPath(i, j, path);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// display: output one path between the source and end node
// output the data of each visited node
void GraphM::display(int from, int to)const{
	
	if (from <= 0 || from > size || to <= 0 || to > size) {
		return;
	}
	else{
		stack<int> path;
		displayPath(from, to, path);
		
		while (!path.empty()){
			cout << data[path.top()] << endl;
			path.pop();
		};
		cout << endl;
	}
}

//-----------------------------------------------------------------------------
// displayPath: output the from,	to,   distance,     path
// Example:					1       4      50          1 3 2 4 
// use an helper method and a stack to store and output the path in the correct
// order
void GraphM::displayPath(int from, int to, stack<int>& path)const
{
	cout << setw(5) << from;
	cout << setw(10) << to;
	if (T[from][to].dist == INT_MAX) {
		cout << setw(10) << "---";
	}
	else {
		cout << setw(10) << T[from][to].dist;
	}
	
	if (T[from][to].dist != INT_MAX) {
		cout << setw(16) << from << " ";
		path.push(to);
		displayPathHelper(from, to, path);
		cout << to << " ";
		path.push(from);
	}
	cout << endl;
}

//-----------------------------------------------------------------------------
// displayPathHelper: find recursively the path 
// and output it in the correct order
void GraphM::displayPathHelper(int from, int to, stack<int>& path)const
{
	if (T[from][to].path != 0)
	{
		path.push(T[from][to].path);
		displayPathHelper(from, T[from][to].path, path);
		cout << T[from][to].path << " ";
	}
}

