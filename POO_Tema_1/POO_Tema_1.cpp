// POO_Tema_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "node.h"
#include "tree.h"
using namespace std;
int main()
{
	//node *p;
	tree A,B;
	cout << "Citesc pentru A\n";
	cout << "Introduceti perechile de muchii:\n";
    cin >> A;
	cout << "Nodurile arborelui sunt:\n";
	cout << A;

	//afisez frunzele
	A.ShowLeaves();

	//nodurile prin bfs:
	cout << "\n Noduri prin BFS:\n";
	A.BFS(A.getRoot());
	//noduri prin dfs
	cout << "\nNoduri prin DFS\n";
	A.DFS(A.getRoot());
	cout << "\n Inaltimea arborelui (radacina se afla pe nivelul 0 si nu va fi numarata):\n";
	cout << A.inaltime(A.getRoot(), 0);

	cout << "Citesc pentru B\n";
	cout << "Introduceti perechile de muchii:\n";
	cin >> B;
	
	//cout << "\nEureka!";
	//B = A;
	tree C = A + B;
	//A.setback();
	cout << "\nEureka!";
	cout << C;
	cout << A;
	//cout <<" "<<p->hasSon();
	

}


