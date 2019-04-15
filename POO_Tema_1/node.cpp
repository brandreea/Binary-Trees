#include "pch.h"
#include "node.h"
#include <iostream>
#include <fstream>
using namespace std;

//constructor
node::node(int val=0, node *b=NULL, node *s=NULL)
{	
	value = val;
	brother = NULL;
	son = NULL;
}

//constructor de copiere
node::node(const node &aux)
{	
	if (&aux != NULL)
	{
		value = (&aux)->value;
		//this->value = aux->value;
		brother = new node;
		brother = (&aux)->brother;
		//this->brother = aux->brother;
		son = new node;
		son = (&aux)->son;
		//this->son = aux->son;
	}
	else 
	{
		value = 0;
		brother = NULL;
		son = NULL;
	}
}

node * node::getNode()
{
	return this;
}


int node:: getValue() const
{
	return this->value;
}
void node:: setValue(int x)
{
	this->value = x;
}

//pentru frate
 bool node::hasBrother()
{
	if (brother != NULL) return 1;
	return 0;
}
node *node::getBrother()
{	
	if (brother == NULL)
		return NULL;
	return brother;
}
 void node::setBrother(node *newBro)
{	
	if (newBro == NULL)
	 brother = NULL;
	else 
		brother = newBro;
}

//pentru fiu
bool node::hasSon()
{
	if (son!= NULL)
		return 1;
	return 0;
}
node * node::getSon()
{
	return son;
}
void node:: setSon(node *newSon)
{	
	if (newSon == NULL)
		this->son = NULL;
	else 
		this->son = newSon;
}
node node::operator =(const node *nod)
{	

	this->value = nod->value;
	this->brother = nod->brother;
	this->son = nod->son;
	return *this;
}

node::~node()
{
	//delete son;
	//delete brother;
	son = NULL;
	brother = NULL;
}

istream & operator>> (istream & in, node * obj)
{
	int x;
	in >> x;
	obj->setValue(x);
	return in;
}
