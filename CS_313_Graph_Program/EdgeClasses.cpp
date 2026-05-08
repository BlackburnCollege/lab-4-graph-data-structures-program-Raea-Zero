#include "EdgeClasses.h"
#include "VertexClasses.h"
#include <iostream>


//edge tree functions
EdgeTree::EdgeTree()
{
	left = NULL;
	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.0;
	y2 = 0.0;
	right = NULL;
	parent = NULL;
}
EdgeTree::EdgeTree(double newX1, double newY1, double newX2, double newY2)
{
	left = NULL;
	x1 = newX1;
	y1 = newY1;
	x2 = newX2;
	y2 = newY2;
	right = NULL;
	parent = NULL;
}

void EdgeTree::setLeft(EdgeTree* newLeft)
{
	left = newLeft;
}
void EdgeTree::setRight(EdgeTree* newRight)
{
	right = newRight;
}
EdgeTree* EdgeTree::getLeft()
{
	return left;
}
EdgeTree* EdgeTree::getRight()
{
	return right;
}
double EdgeTree::getX1()
{
	return x1;
}
double EdgeTree::getY1()
{
	return y1;
}
void EdgeTree::setX1(double newX)
{
	x1 = newX;
}
void EdgeTree::setY1(double newY)
{
	y1 = newY;
}

double EdgeTree::getX2()
{
	return x2;
}
double EdgeTree::getY2()
{
	return y2;
}
void EdgeTree::setX2(double newX)
{
	x2 = newX;
}
void EdgeTree::setY2(double newY)
{
	y2 = newY;
}

void EdgeTree::setParent(EdgeTree* newParent)
{
	parent = newParent;
}
EdgeTree* EdgeTree::getParent()
{
	return parent;
}

double EdgeTree::getSlope()
{
	return (y2 - y1) / (x2 - x1);
}
double EdgeTree::getIntercept()
{
	double tempSlope = getSlope();
	return y1 - tempSlope * x1;
}