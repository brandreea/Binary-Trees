#pragma once
#include <iostream>
#include <fstream>
#include "node.h"
using namespace std;
class tree
{
private:
	friend class node;
	node *root;

public:
	tree();
	tree(const tree &B);
	//constructor de copiere

	//pentru radacina
	node *getRoot() const;
	void setRoot(node *r);

	//alocare nod

	//functii recursive apelate in cadrul operatorilor de citire si afisare
	void addAllNodes(istream &in, node *n);
	void ShowAllNodes(ostream &out, node *r);

	//functii recursive pentru afisarea frunzelor (ShowLeaves apeleaza FindLeaves)
	void FindLeaves(node *r);
	void ShowLeaves();

	//parcurgerea pe niveluri
	void BFS(node *r);

	//parcurgerea in adancime
	void DFS(node *r);
	
	//inaltimea arborelui
	int inaltime(node *r, int max);
	friend istream &operator>>(istream &in, tree &A);
	friend ostream &operator<<(ostream &out, tree &A);

	//copiez arborele in alta zona de memorie
	const tree & operator =( const tree &B);
	node *copy(node *);
	
	void copyrest( node *r, node *decopiat);
	const tree & operator +(const tree &B);
	void setback();

	//stergere
	void DeleteALL(node *r);
	~tree();
};

