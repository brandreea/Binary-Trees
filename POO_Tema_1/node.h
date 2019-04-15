#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class node
{
private:
	int value;
	node *brother, *son;
	friend class tree;

public:

	node(int val, node *, node *);
	node(const node & aux);
	node *getNode();
	//pentru valoare
	int getValue() const;
	void setValue(int x);

	//pentru frate
	bool hasBrother();
	node *getBrother();
	void setBrother(node *newBro);
	
	//pentru fiu
	bool hasSon();
	node *getSon();
	void setSon(node *newSon);

	//operator de atribuire "="
	node operator =(const node *nod);

	//citire si afisare

	friend istream &operator >> (istream &in, node *obj);

	~node();
};

