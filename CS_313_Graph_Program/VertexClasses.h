#pragma once
//originally I had more vertex related classes, but I realized I was overcomplicating. This only exists to streamline printing the graph.

class VertexList
{
private:

	double xCoord;
	double yCoord;
	VertexList* next;
public:
	VertexList();
	VertexList(double newX, double newY);

	void setNext(VertexList* newNext);

	VertexList* getNext();
	double getX();
	double getY();
	void setX(double newX);
	void setY(double newY);
	bool hasVertex(double x, double y);
};
