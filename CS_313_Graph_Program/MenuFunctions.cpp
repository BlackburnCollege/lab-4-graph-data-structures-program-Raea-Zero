#include "MenuFunctions.h"
#include "EdgeClasses.h"
#include "VertexClasses.h"
#include <iostream>
//option 1: load graph file (graph.txt default)
/*
* how to do option 1:
* each node should hold the x and y coordinates as data members
* need some sort of data member to track edges that varies in size, since one point could have multiple edges; perhaps a linked list with a different format to handle edges?
* here is what I'm thinking: a vertex object that holds coordinates and a list of edges. An edge object that points to its two vertices. And at the top, a list that holds vertices. Probably use trees to allow binary sort.
* the input file mentions the points through edges, so for each pair: create the points if they don't exist, then create the edge between them
* 
* should also store the number of vertices and edges, since they are given in the first line
* perhaps the root stores the numbers of each, and has a pointer to the first one. the tree is sorted based on x values
* 
* remember to use new keyword for classes
*/
void insertEdgeTree(EdgeTree*& root, EdgeTree x, EdgeTree *parent)
{
	EdgeTree* temp = NULL;

	if (root == NULL)
	{
		temp = new EdgeTree;
		temp->setX1(x.getX1());
		temp->setY1(x.getY1());
		temp->setX2(x.getX2());
		temp->setY2(x.getY2());
		temp->setParent(parent);
		root = temp;
		return;
	}
	else
	{
		if (x.getX1() < root->getX1())
		{
			//these temporary pointers to the left and right scattered around are because the compiler complains if I try to send it root->getLeft() directly as a parameter to a recursive function
			EdgeTree* left = NULL;
			left = root->getLeft();
			insertEdgeTree(left, x, root);
		}
		else
		{
			EdgeTree* right = NULL;
			right = root->getRight();
			insertEdgeTree(right, x, root);
		}
		return;
	}
}

void fillGraph(EdgeTree* &root, std::ifstream& inFile)
{
	std::string lineHolder;
	double coord;
	EdgeTree edgeHolder;
	
	//I do not need to store the number of vertices and edges, so I am skipping over this line.
	std::getline(inFile, lineHolder);

	//fill a temporary edge with the current line, insert it into the tree
	while (!inFile.eof())
	{
		std::getline(inFile, lineHolder, ',');
		//double checking if eof() missed the end, I've done this since that happened in CS 211
		if (lineHolder == "")
		{
			break;
		}
		coord = std::stod(lineHolder);
		edgeHolder.setX1(coord);

		std::getline(inFile, lineHolder, ',');
		coord = std::stod(lineHolder);
		edgeHolder.setY1(coord);

		std::getline(inFile, lineHolder, ',');
		coord = std::stod(lineHolder);
		edgeHolder.setX2(coord);

		std::getline(inFile, lineHolder);
		coord = std::stod(lineHolder);
		edgeHolder.setY2(coord);

		insertEdgeTree(root, edgeHolder, NULL);
	}
}


//option 2: search for edge (ask for an edge and report if it exists)
//how to: simply binary search the vertex tree for the first of the two points, then check that point's edge tree for an edge with the other point

bool edgeExists(EdgeTree*& root, EdgeTree targetEdge)
{
	//if the end of the tree has been reached, the edge doesn't exist.
	if (root == NULL)
	{
		return false;
	}
	//if it's not the end, either this is the target point or it could be left or right.
	if (root->getX1() == targetEdge.getX1())
	{
		if (root->getY1() == targetEdge.getY1() && root->getX2() == targetEdge.getX2() && root->getY2() == targetEdge.getY2())
		{
			return true;
		}
		else
		{
			//if the X1 value matches but the rest don't, then it might be a different point with the same X1 value. In that case, insertEdgeTree would have inserted it to the right.
			EdgeTree* right = NULL;
			right = root->getRight();
			edgeExists(right, targetEdge);
		}
	}
	else if (root->getX1() > targetEdge.getX1())
	{
		EdgeTree* left = NULL;
		left = root->getLeft();
		edgeExists(left, targetEdge);
	}
	else
	{
		EdgeTree* right = NULL;
		right = root->getRight();
		edgeExists(right, targetEdge);
	}
}

//option 3: print graph in this format:
/*
Number of Vertices: 4 Number of Edges: 3
Vertices: (1,3), (1,5), (3,5), (3,3)
Edge 1: (1,3) - (1,5)
Edge 2: (1,5) - (3,5)
Edge 3: (3,5) - (3,3)
*/

//how to: printing vertices is easy, edges less so. I'm considering just putting them in a temporary vector
void fillVertexList(EdgeTree* root, VertexList*& head, int &edgeCounter, int &vertexCounter)
{
	VertexList* tail = NULL;
	VertexList* temp = NULL;
	if (root != NULL)
	{
		fillVertexList(root->getLeft(), head, edgeCounter, vertexCounter);
		tail = head;
		while (tail != NULL)
		{
			tail = tail->getNext();
		}
		if (!head->hasVertex(root->getX1(),root->getY1()))
		{
			//add first vertex
			temp = new VertexList;
			temp->setX(root->getX1());
			temp->setY(root->getY1());
			tail->setNext(temp);
			tail = temp;
			vertexCounter++;
		}
		if (!head->hasVertex(root->getX2(), root->getY2()))
		{
			//add second vertex
			temp = new VertexList;
			temp->setX(root->getX2());
			temp->setY(root->getY2());
			tail->setNext(temp);
			tail = temp;
			vertexCounter++;
		}
		edgeCounter++;
		fillVertexList(root->getRight(), head, edgeCounter, vertexCounter);
	}
	return;
}

void traverseEdgeTree(EdgeTree* root, int &counter)
{
	if (root != NULL)
	{
		traverseEdgeTree(root->getLeft(), counter);
		std::cout << "Edge" << counter << "(" << root->getX1() << ',' << root->getY1() << ") - " << "(" << root->getX2() << ',' << root->getY2() << ")\n";
		counter++;
		traverseEdgeTree(root->getRight(), counter);
	}
	return;
}

void printGraph(EdgeTree*& root)
{
	VertexList* listHead = NULL;
	VertexList* searcherVertex = NULL;
	int numEdges;
	int numVertices;
	if (root == NULL)
	{
		std::cout << "The graph is empty.";
	}
	else
	{
		//put all the unique vertices in a list, plus count the number of edges and vertices
		fillVertexList(root, listHead, numEdges, numVertices);
		//print line 1 (number of vertices and edges)
		std::cout << "Number of Vertices: " << numVertices << ", Number of Edges: " << numEdges << "\n";

		//print line 2 (all unique vertices)
		std::cout << "Vertices: ";
		searcherVertex = listHead;
		while (searcherVertex != NULL)
		{
			std::cout << "(" << searcherVertex->getX() << "," << searcherVertex->getY() << ") ";
			searcherVertex = searcherVertex->getNext();
		}
		std::cout << "\n";
		//print edges (pass 1 in as starting value of counter)
		int startCount = 1;
		traverseEdgeTree(root, startCount);

		clearVertexList(listHead);
	}
}

//option 4: load and compare 2nd graph against 1st graph
/*
* ask for a second file name; only accept if it's different from the first
* load graph
* compare graphs to determine if they intersect, report yes or no (return bool)
* discard second graph
*/

/*
how to do option 4:
formula involves getting the function for 2 lines, then see if it lies between the points of the line segment
in the initial function, calculate the slope and intercept. use these to determine if parallel or the same line and handle special cases if they are
have another function that calculates the intersection, pass it the pieces of the formula as parameters and have it return the point of intersection
check if the x of that point is within the range of the edge; if not, discard it
repeat for every edge in graph 2 ( O(m) )
repeat all of that for every edge in graph 1 ( O(n x m) )
*/
bool compareAllToEdge(EdgeTree* graph, double slope, double intercept)
{
	double thisSlope;
	double thisIntercept;
	double xOfIntercept;

	bool leftCheck;
	bool rightCheck;
	if (graph != NULL)
	{
		leftCheck = compareAllToEdge(graph->getLeft(), slope, intercept);
		if (leftCheck == true)
		{
			return true;
		}
		//process this node on the second graph
		thisSlope = graph->getSlope();
		thisIntercept = graph->getIntercept();

		//the edges are the exact same
		if (thisSlope == slope && thisIntercept == intercept)
		{
			return true;
		}
		//the edges are parallel
		else if (thisSlope == slope && thisIntercept != intercept)
		{
			return false;
		}
		//the edges are not parallel or the same, so they must have a single point of interception
		else
		{
			xOfIntercept = (thisIntercept - intercept) / (slope - thisSlope);
			//if the point of interception is within the range of this edge, return true
			//checking both ways because I don't know whether X1 is bigger or X2 is bigger
			if ((xOfIntercept >= graph->getX1() && xOfIntercept <= graph->getX2()) || (xOfIntercept >= graph->getX2() && xOfIntercept <= graph->getX1()))
			{
				return true;
			}
			//if the point of interception is outside the range of this edge, return false because it's not within the graph
			else
			{
				return false;
			}
		}

		rightCheck = compareAllToEdge(graph->getRight(), slope, intercept);
		if (rightCheck == true)
		{
			return true;
		}
	}
	return false;
}

bool compareEdges(EdgeTree* graph1, EdgeTree* graph2)
{
	double slope;
	double intercept;

	bool leftCheck;
	bool rightCheck;

	if (graph1 != NULL)
	{
		//need to catch what these return somehow
		leftCheck = compareEdges(graph1->getLeft(), graph2);
		//process for current edge in graph 1
		if (leftCheck == true)
		{
			return true;
		}

		slope = graph1->getSlope();
		intercept = graph1->getIntercept();
		//traverse graph2, and for each edge, calculate the slope, intercept, and point of intersection against this
		bool doesThisEdgeIntersect = compareAllToEdge(graph2, slope, intercept);
		if (doesThisEdgeIntersect == true)
		{
			return true;
		}
		else
		{
			return false;
		}

		rightCheck = compareEdges(graph1->getRight(), graph2);
		if (rightCheck == true)
		{
			return true;
		}
	}
	return false;
}

bool compareGraphs(EdgeTree*& root, std::ifstream& graph2File)
{
	EdgeTree* secondGraph = NULL;

	fillGraph(secondGraph, graph2File);

	//for every edge in graph 1, check every edge in graph 2
	bool result = compareEdges(root, secondGraph);

	clearEdgeTree(secondGraph);

	return result;
}

//option 5: exit (this function should free the data structures)
//remember to use delete keyword for classes

void clearEdgeTree(EdgeTree*& root)
{
	if (root != NULL)
	{
		EdgeTree* tempLeft = NULL;
		tempLeft = root->getLeft();
		clearEdgeTree(tempLeft);

		//delete
		if (root->getParent()->getLeft() == root)
		{
			root->getParent()->setLeft(NULL);
		}
		else
		{
			root->getParent()->setRight(NULL);
		}
		delete root;
		root = NULL;

		EdgeTree* tempRight = NULL;
		tempRight = root->getRight();
		clearEdgeTree(tempRight);
	}
	return;
}

void clearVertexList(VertexList*& head)
{
	VertexList* temp = NULL;
	if (head != NULL)
	{
		temp = head->getNext();
		delete head;
		head = NULL;
		clearVertexList(temp);
	}
	return;
}
