#include "VertexClasses.h"
#include <iostream>



//vertex tree functions
VertexList::VertexList()
{
	xCoord = 0.0;
	yCoord = 0.0;
	next = NULL;
}
VertexList::VertexList(double newX, double newY)
{

	xCoord = newX;
	yCoord = newY;
	next = NULL;
}

void VertexList::setNext(VertexList* newNext)
{
	next = newNext;
}

VertexList* VertexList::getNext()
{
	return next;
}
double VertexList::getX()
{
	return xCoord;
}
double VertexList::getY()
{
	return yCoord;
}
void VertexList::setX(double newX)
{
	xCoord = newX;
}
void VertexList::setY(double newY)
{
	yCoord = newY;
}

bool VertexList::hasVertex(double x, double y)
{
	if (xCoord == x && yCoord == y)
	{
		return true;
	}
	else if (next != NULL)
	{
		return next->hasVertex(x, y);
	}
	else
	{
		return false;
	}
}