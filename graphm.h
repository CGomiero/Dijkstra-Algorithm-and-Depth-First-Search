//---------------------------------------------------------------------------
// GRAPM_H_
// Author: Clement Gomiero
//---------------------------------------------------------------------------
// GrahM class: is a class used to perform dijkstra algorithm
// The class:
// -- allows to read a file and store the data, nodes and their weight
// -- allows to insert and remove any edges
// -- allows to find the shortest path between any source node to another
// -- allows to display one source node and another or all
// 
// Implementation and Assumption: 
// -- When reading from the file, the amount of data is equal to the size
// -- The file will always have a from node, to node, and a weight
// -- The from node and source node will never be display when equal
// -- Any insert or remove or buildGraph will set change to true
// -- The maximun amount of nodes will never go over 100
// -- There will not be any duplicates in the input
//---------------------------------------------------------------------------

#ifndef GRAPH_H_
#define GRAPH_H_
#include <string>
#include<iostream>
#include"nodedata.h"
#include <iomanip>
#include <limits.h>
#include <algorithm>  
#include <stack>
using namespace std;

#define MAXNODES 100 // maximun size of nodes

class GraphM
{
public:
	//---------------------------------------------------------------------------
	// default constructor: 
  // Preconditions: None
  // PostConditions: initialize T[][] and C[][]
	GraphM();

	//---------------------------------------------------------------------------
	// buildGraph
  // Preconditions: a file input stream need to be up
  // Postconditions: C[][], data[] and size receives input from the file
	void buildGraph(istream& file);

	//---------------------------------------------------------------------------
	// insertEdge: 
  // Preconditions: the edge inserted is not already in C[][] and all values 
  // are more than 0 and less than MAXNODES
  // Postconditions: C[from][to] = weight is updated
	bool insertEdge(int from, int to, int weight);

	//---------------------------------------------------------------------------
	// removeEdge: 
  // Preconditions: from and to are bigger than 0 but less than MAXNODES
  // PostConditions: the node is set to 0
	// Example: C[from][to] = 0
	bool removeEdge(int from, int to);

	//---------------------------------------------------------------------------
	// findShortestPath: 
  // Preconditions: The arrays are not empty and some nodes are connected 
  // Postconditions: find the shortest path between all sources and other nodes
	void findShortestPath();

	//---------------------------------------------------------------------------
	// displayAll:
  // Preconditions: change is either true or false
  // Postconditions:  display all the path from the sources to all nodes
	// Format -- Description  From node  To node  Dijkstra's  Path
	void displayAll()const;

	//---------------------------------------------------------------------------
	// display:
  // Preconditions: none
  // Postconditions:  display all the path from one to another node if 
  // there is one
	// Format -- Description  From node  To node  Dijkstra's  Path
	void display(int from, int to) const;

private:

	struct TableType {
		bool visited = false;			 // whether node has been visited 
		int dist = INT_MAX;              // currently known shortest distance from source  
		int path = 0;					// previous node in path of min dist  
	};

	//---------------------------------------------------------------------------
	NodeData data[MAXNODES];              // data for graph nodes information 
	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix 
	int size = 0;                             // number of nodes in the graph 
	TableType T[MAXNODES][MAXNODES];      // stores Dijkstra information 
	bool change = false;

	//---------------------------------------------------------------------------
	// dijkstra: 
  // Preconditions: The arrays are not empty
  // PostConditions: All the shortest path are found from a source to all other 
  // nodes
	void dijkstra(int from);

	//---------------------------------------------------------------------------
	// minDistance: 
  // Preconditions: T is not empty
  // Postconditions: return the index of the shortest distance between the 
  // source and from
	int minDistance(int from);

	//---------------------------------------------------------------------------
	// Helper methods used to correctly the path of each source
	// A stack was created to output the data in the correct order
	void displayPath(int from, int to, stack<int>& path)const;
	void displayPathHelper(int from, int to, stack<int>& path)const;
};
#endif