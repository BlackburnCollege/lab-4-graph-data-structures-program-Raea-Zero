#pragma once
#include <fstream>
#include "VertexClasses.h"
#include "EdgeClasses.h"
#include <string>

void insertEdgeTree(EdgeTree*& root, EdgeTree x, EdgeTree* parent);
void fillGraph(EdgeTree*& root, std::ifstream &inFile);

bool edgeExists(EdgeTree*& root, EdgeTree targetEdge);

void fillVertexList(EdgeTree* root, VertexList*& head, int& edgeCounter, int& vertexCounter);
void traverseEdgeTree(EdgeTree* root, int &counter);
void printGraph(EdgeTree*& root);

bool compareAllToEdge(EdgeTree* graph, double slope, double intercept);
bool compareEdges(EdgeTree* graph1, EdgeTree* graph2);
bool compareGraphs(EdgeTree*& root, std::ifstream& graph2File);


void clearEdgeTree(EdgeTree*& root);
void clearVertexList(VertexList*& head);
