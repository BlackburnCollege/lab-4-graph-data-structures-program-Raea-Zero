#pragma once
//originally I had more edge classes, but I realized I was overcomplicating. This stores the entire graph in a binary search-able format.

class EdgeTree
{
private:
	EdgeTree* left;
	double x1;
	double y1;
	double x2;
	double y2;
	EdgeTree* right;
	EdgeTree* parent;
public:
	EdgeTree();
	EdgeTree(double newX1, double newY1, double newX2, double newY2);
	void setLeft(EdgeTree* newLeft);
	void setRight(EdgeTree* newRight);
	EdgeTree* getLeft();
	EdgeTree* getRight();
	double getX1();
	double getY1();
	void setX1(double newX);
	void setY1(double newY);
	double getX2();
	double getY2();
	void setX2(double newX);
	void setY2(double newY);
	
	void setParent(EdgeTree* newParent);
	EdgeTree* getParent();

	double getSlope();
	double getIntercept();
};

