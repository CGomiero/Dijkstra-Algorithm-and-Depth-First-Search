//---------------------------------------------------------------------------
// GRAPL_H_
// Author: Clement Gomiero
//---------------------------------------------------------------------------
// GraphL class: is a class used to perform depth-first search and it is used
// to display all the nodes and its adjacent one
// The class: 
// -- allows to use pointers and have no memory leaks
// -- allows to read the size, data, and connected nodes from a file
// -- allows to create an array of linkedlist
// -- allows to determine which node was visited
// -- allows to display a source node with edges
// -- allows to insert a node 
// 
// Implementation and Assumption: 
// -- When reading from the file, the amount of data is equal to the size
// -- The file will always have a from node, to node and nothing more
// -- The maximun amount of nodes will never go over 100
// -- All the pointers/array will be deleted and set to null at the end
// -- There will not be any duplicates in the input
//---------------------------------------------------------------------------

#ifndef GRAPHL_H_
#define GRAPHL_H_
#include<string>
#include <iostream>
#include <list>
#include <stack>
#include "nodedata.h"
#define MAXNODES 100
using namespace std;

class GraphL
{
public:
	//---------------------------------------------------------------------------
	// Constructor: 
  // Preconditions: None
  // Postconditions: all variables are initialized
	GraphL();	

	//---------------------------------------------------------------------------
	// Destructor: 
  // Preconditions: None
  // PostConditions: delete all allocated memory so there is no memory leaks
	~GraphL();                                

	//---------------------------------------------------------------------------
	// buildGraph: 
  // Preconditions: an input stream was created and the file can be read
  // Postconditions: size, graphNodeList, and data are initialized
	void buildGraph(istream& file);

	//---------------------------------------------------------------------------
	// displayGraph: 
  // Preconditions: All the variables have received a value from the buildGraph
  // Postconditions: display all the source nodes and its adjacent node, and data
	void displayGraph();

	//---------------------------------------------------------------------------
	// depthFirstSearch: 
  // Preconditions: list<int> adj was initialized from the build graph method
  // Postconditions: perform the depth first search algorithm which output
	// in a line all the node 
	void depthFirstSearch() const;

	//---------------------------------------------------------------------------
	// makeEmpty: 
  // Preconditions: none
  // Postconditions: delete all of the pointers and set them to nullptr
	void makeEmpty();

	//---------------------------------------------------------------------------
	// insert: 
  // Preconditions: graphNodeList was initialized
  // Postconditions: add an object in the linkedlist
	void insert(int from, int to);

private:

	// Every source will be connected to an adjNode with is a linkedlist of nodes
	struct AdjNode {				// create a linkedlist of all the adjacent nodes
		int adjacent = 0;			
		AdjNode* next = nullptr;	
	};
	struct GraphNode {
		NodeData data;	// data of one linkedlist
		bool visited = false;       // used to know if the node was visited
		AdjNode* head = nullptr;	// head node for the adjacent linkedlist
		list<int> adjList;
	};
	GraphNode** graphNodeList = nullptr;		// 2d pointer array that will hold the data and adj node
	int size;					// number of data in this Graph
	
	//---------------------------------------------------------------------------
	// helper methods that is mostly used to go over the linkedlist
	void insertHelper(AdjNode*& insert, int to);
	void displayHelper(AdjNode* current, int source);
	void DFSHelper(int source) const;
	void MakeEmptyHelper(AdjNode* current);
};
#endif