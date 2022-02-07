#include "graphl.h"

//---------------------------------------------------------------------------
// Constructor: size is set to 0
// all other variables are automatically initialize when created
// (showed in the .h file)
GraphL::GraphL()
{
	size = 0;
}

//---------------------------------------------------------------------------
// Destructor: make sure there is no memory leaks
GraphL::~GraphL()
{
	makeEmpty();
  graphNodeList = nullptr;
}

//---------------------------------------------------------------------------
// makeEmpty: delete every node and of every list
// delete the data and the 2d graphNodeList
void GraphL::makeEmpty()
{
	if (graphNodeList == nullptr) {
		return;
	}
	for (int i = 0; i < size; i++) {
		AdjNode* current = graphNodeList[i]->head;
			MakeEmptyHelper(current);
			delete graphNodeList[i];
			graphNodeList[i] = nullptr;
	}
	delete[] graphNodeList;
	graphNodeList = nullptr;
}

//---------------------------------------------------------------------------
// MakeEmptyHelper: recursively reach the end of the linkedList
// delete the last node, one by one
void GraphL::MakeEmptyHelper(AdjNode* current)
{
	if (current == nullptr) {
		return;
	}
	else {
		MakeEmptyHelper(current->next);
		delete current;
		current = nullptr;
	}
}

//---------------------------------------------------------------------------
// insert: insert a node in the array of list at the from index
// then insert at the last node the to value
// call helper method
void GraphL::insert(int from, int to)
{
	AdjNode*& insert = graphNodeList[from]->head;
	insertHelper(insert, to);
}

//---------------------------------------------------------------------------
// insertNode: insert an adjacent node in the linkedlist
// go over the linkedlist until temp is null
// insert the adjacent value with is to
void GraphL::insertHelper(AdjNode*& insert, int to)
{
	if (insert == nullptr) {
		insert = new AdjNode();
		insert->adjacent = to;
	}
	else {
		insertHelper(insert->next, to);
	}
}

//---------------------------------------------------------------------------
// buildGraph: get the size, the data, and insert any nodes
// in the linkedlist using from and to
// make sure size is not less than 0 or over MAXNODES
// stop inserting when the graph reaches 0
void GraphL::buildGraph(istream& file)
{
	makeEmpty(); // make sure the linked lists are empty
	int from, to;

	file >> size;         // read size is int
	size++;

	if (file.eof()) { 
		return;
	}

	graphNodeList = new GraphNode * [size](); // initialize the amount of columns/nodes
	for (int i = 0; i < size; i++) {
		graphNodeList[i] = new GraphNode(); // create a node for each columns/data
	}

	string s;
	getline(file, s);

	for (int i = 1; i < size; i++) { // store data from file
		graphNodeList[i]->data.setData(file);
	}
	
	file >> from >> to;

	while (from != 0) {
		if (from < 0 || to <= 0 || from == to || from > size || to > size) {
			file >> from >> to;
		}
		else if (from != 0 && to != 0) {
			insert(from, to);
			graphNodeList[from]->adjList.push_back(to);
		}
		file >> from >> to;
	}
}

//---------------------------------------------------------------------------
// displayGraph: output every source node with its data and 
// every adjacent node to the source
void GraphL::displayGraph()
{
	cout << endl << "Graph: " << endl;
	for (int i = 1; i < size; i++) {
		cout << "Node " << i << "		  " << graphNodeList[i]->data << endl;
		AdjNode* current = graphNodeList[i]->head;
		displayHelper(current, i);
	}
	cout << endl;
}

//---------------------------------------------------------------------------
// displayHelper: output the edge and its closest adjacent first
// then recursively go over the linkedlist to output the source
// adjacent that are always the closest and not visited
void GraphL::displayHelper(AdjNode* current, int source)
{
	if (current == nullptr) { // end of list
		return;
	}
	cout << "   edge " << source << " " << current->adjacent << endl;
	displayHelper(current->next, source);
}

//---------------------------------------------------------------------------
// depthFirstSearch: use a for loop to get every node
// call DFSHelper for every node
void GraphL::depthFirstSearch() const {
	cout << "Depth-First Search: ";
	for (int i = 1; i < size; i++) {
		if (!graphNodeList[i]->visited) {
			DFSHelper(i);
		}
	}
	cout << endl;
}

//---------------------------------------------------------------------------
// DFSHelper: check if the current node is visited
// if it is not then set visited to true
// output the source/fisrt element in array
// create a adjNode object to check for all the adjacent number
// call SearchLastNode for that
void GraphL::DFSHelper(int source) const {
	graphNodeList[source]->visited = true;
	cout << source << " ";
	for (list<int>::const_iterator it = graphNodeList[source]->adjList.begin(); it != graphNodeList[source]->adjList.end(); it++) {
		if (!graphNodeList[*it]->visited) {
			DFSHelper(*it);
		}
	}
}