#include "pch.h"
#include "tree.h"
#include <iostream>
#include <fstream>
#include "node.h"
using namespace std;


tree::tree()
{	
	root = NULL;
}

tree::tree(const tree & B)
{	
	cout << "copiez\n";
	root = copy(B.root);
}

node * tree::getRoot()const
{
	return root;
}

void tree::setRoot(node * r)
{
	root = r;
}



void tree::addAllNodes(istream &in, node  * n)
{
	//citire perechi de muchii
	int from=0, to=-1;

	//flag
	int stop = 1;
	//conditie de oprire: unul din noduri egal cu -1(s-au terminat toate muchiile de citi) sau al doilea nod este =0(flag =1)
	while (stop==1)
	{
		cin >> from >> to;
		//ma opresc cand am terminat de citit muchiile
		if (to == -1) stop = 0;
		else
		{
			if (root== NULL)
			{	
				root = new node(0,NULL,NULL);
				root->setValue(from);
				n = root;
				//cout << "Am setat radacina pe "<<root->getValue();
			}
			bool hs = n->hasSon();
			if (hs == false)
			{
				node *son = new node(0, NULL, NULL);
				son->setValue(to);
				n->setSon(son);
				if(to!=0)
				    addAllNodes(in, son);
				else stop = 0;
			}
			else
			{
				node *p;
				p = n->getSon();
				while (p->hasBrother())
					p = p->getBrother();
				node *aux;
				aux = new node(0, NULL, NULL);
				aux->setValue(to);
				p->setBrother(aux);
				if(to!=0)
				   addAllNodes(in, aux);
				else stop = 0;

			}

		}
	}
}

void tree::ShowAllNodes(ostream &out, node * r)
{
	if (r->getNode() != NULL)
	{
		if(r->getValue()!=0)

		    cout << r->getValue() << " ";
		//else cout << "E 0, ";
		if (r->hasSon() == true)
			ShowAllNodes(out, r->getSon());
		if (r->hasBrother() == true)
			ShowAllNodes(out, r->getBrother());
	}
}



void tree::FindLeaves(node * r)
{
	node *b, *s;
	if (r == NULL)
	{
		cout << "Ba vezi ca e NULL";
		exit(0);
	}
	b = r->getBrother();
	s = r->getSon();
	if (b == NULL)
	{	
		//acesta este cazul radacinii, care nu are frati 
		if(s->getValue()!=0)
		     FindLeaves(s);
	}
	else
	{
		//cazul oricarui alt nod
		//daca nu are fiu
		if (s->getValue() == 0)
			cout << r->getValue() << " ";

		//daca are fiu nenul
		if (s->getValue() != 0)
			FindLeaves(s);

		//daca are frate nenul
		if (b->getValue() != 0)
			FindLeaves(b);

	}
}

void tree::ShowLeaves()
{
	cout << "Acestea sunt frunzele arborelui:\n";
	FindLeaves(root);
}

void tree::BFS(node * r)
{
	//mimez o coada si adaug in ea radacina si unicul fiu
	node *vec[15];
	vec[0] = root;
	vec[1] = root->getSon();

	//contoare
	int start, end;
	start = 1;
	end = 2;
	cout << vec[0]->getValue() << "\n";
	//parcurg coada
	while (start < end)
	{
		cout << vec[start]->getValue() << " ";
		//pentru primul nod din coada parcurg fratii nenuli si ii afisez
		node *parcurgere = vec[start]->getBrother();
		while (parcurgere != NULL && parcurgere->getValue() != 0)
		{
			cout << parcurgere->getValue() << " ";
			if (parcurgere->hasSon())
			{
				vec[end] = parcurgere->getSon();
				end++;
			}
			parcurgere = parcurgere->getBrother();
		}
		cout << "\n";
		start++;
	}

	/*if (r == root)
		//afisez radacina
	{
		cout << root->getValue() << "\n";

	}
	node *s = r->getSon();
		if (s->getValue() != 0)
		{
			node *p = s;
			while (p->getValue() != 0)
			{
				cout << p->getValue() << " ";
				p = p->getBrother();
			}
			cout << "\n";
			p = s;
			while (p->getValue() != 0)
			{
				BFS(p);
				p = p->getBrother();
			}
		}*/


}

void tree::DFS(node *r)
{
	if (r->getNode() != NULL)
	{
		if (r->getValue() != 0)

			cout << r->getValue() << " ";
		//else cout << "E 0, ";
		if (r->hasSon() == true)
			DFS(r->getSon());
		if (r->hasBrother() == true)
			DFS(r->getBrother());
	}
}

int tree::inaltime(node * r, int max)
{
	node *s, *b;
	b = r->getBrother();
	s = r->getSon();
	//cazul radacinii
	if (r==root)
		return inaltime(r->getSon(), max + 1);
	else
	{
		//cazul in care nu are nici fiu, nici frate
		if (s->getValue() == 0 && b->getValue() == 0)
			return max;
		int m = max;
		int maux;
		if (s->getValue() != 0)
		{
			maux = inaltime(r->getSon(), max + 1);
			if (maux > m)
				m = maux;
		}
		
		while (b->getValue() != 0)
		{
			//cout << "In while nodul"<<b->getValue()<<" \n";
			if (b->hasSon())
			{	
				node *son;
				son = b->getSon();
				if (son->getValue() != 0)
				{	
					
					maux = inaltime(b->getSon(), max + 1);
					if (maux > m)
						m = maux;
				}
			}
			b = b->getBrother();
		}
		return m;
	}
}

const tree & tree::operator+(const tree &B)
{	
	tree C=(*this);
	//cout << C;
	node *r2=NULL, *rc;
	//r2 = cb.getRoot();

	rc = C.getRoot();

	node *lastbro=rc->getSon();
	node *aux=lastbro->getBrother();
	int auxval = aux->getValue();

	while (auxval != 0)
	{
		lastbro = lastbro->getBrother();
		aux = lastbro->getBrother();
		auxval = aux->getValue();
	}
	B.getRoot()->setBrother(aux);

	//C.copy(B.getRoot(), r2);
	//r2->setBrother(aux);
	lastbro->setBrother(B.getRoot());
	cout << "Am facut adunarea";
	//cout << C;
	//exit(0);
	return C;

}

void tree::setback()
{	
	node *b = root->getSon();
	node *lastb = b->getBrother();
	lastb = lastb->getBrother();
	while (lastb->getValue() != 0)
	{
		lastb = lastb->getBrother();
		b = b->getBrother();
	}
	b->setBrother(lastb);
}

void tree::copyrest(node * r,node *decopiat)
{
	r->setValue(decopiat->getValue());
	cout << "Am setat valoare"<< decopiat->getValue()<<"\n";
	if (decopiat->hasBrother())
	{
		cout << "If frate\n";
		node *auxB = r->getBrother();
		node *b = decopiat->getBrother();
		int val = b->getValue();
		node *fratenou = new node(val, NULL, NULL);
        r->setBrother(fratenou);
		delete auxB;
		copyrest(r->getBrother(), decopiat->getBrother());

	}
	cout << "Am setat frate\n";
	if(decopiat->hasBrother())
		copyrest(r->getBrother(), decopiat->getBrother());

	node *auxS = r->getSon();
	if (decopiat->hasSon())
	{	
		node *ns = decopiat->getSon();
		r->setSon(new node(ns->getValue(), NULL, NULL));
		delete auxS;
		cout << "Am setat fiu\n";
		copyrest(r->getSon(), decopiat->getSon());
	}

}
tree::~tree()
{	
	DeleteALL(root);
	//delete root;
}

void tree::DeleteALL(node * r)
{
	if (r != NULL)
	{
		if (r->hasSon())
			DeleteALL(r->getSon());
		if (r->hasBrother())
			DeleteALL(r->getBrother());
		 r=NULL;
	}
}




istream & operator>>(istream & in, tree &A)
{
	int from = 0, to = 0;
	node *r=new node(0, NULL, NULL);
	//A.setRoot(r);
	A.addAllNodes(in, r);
	//A.setRoot(r);
	
	return in;
}

ostream & operator<<(ostream & out, tree & A)
{
	node *r = A.getRoot();
	A.ShowAllNodes(out, r);
	cout << endl;
	return out;
}
const tree & tree:: operator =(const tree &B)
{
	if (this != &B)
	{
		if (B.root != NULL)
			cout << "Nu e null\n";
		else
		{
			cout << "E null\n";
			exit(0);
		}
		cout << "in egal\n";
		if (root == NULL)
			root = new node(B.root->getValue(), NULL, NULL);
		else root->setValue(B.root->getValue());
		cout << "Am setat radacina pe " << root->getValue() << "\n";

		root->setBrother(NULL);
		cout << "Am setat frate\n";
		if (B.root->hasSon())
		{
			node *auxS = root->getSon();
			root->setSon(new node(B.root->getSon()->getValue(), NULL, NULL));
			delete auxS;
			cout << "Am setat fiu" << root->getSon()->getValue() << "\n";
		}
		copyrest(root->getSon(), B.root->getSon());
	}

	return *this;
}
node * tree::copy(node *r1)
{
	if (r1->getNode() != NULL)
	{
		//setez valoarea pentru nodul curent
		node *copie = new node(r1->getValue(),NULL,NULL);
		cout << "Am facut\n";
		//setez fiu
		if (r1->hasSon() == true)
		{
			cout << "Are fiu\n";
			copie->setSon(copy(r1->getSon()));
		}
		//setez frate
		if (r1->hasBrother() == true)
		{
			cout << "Are frate\n";
			copie->setBrother(copy(r1->getBrother()));
		}
		return copie;
	}
	else
		return NULL;
}