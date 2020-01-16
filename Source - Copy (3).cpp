#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<stack>

using namespace std;


class node
{
public:
	int id;
	int distance;
	bool visited;
	node* parent;
	list<node*> Ns;
	char Ver;

	node(int i, char a)
	{
		id = i;
		visited = false;
		Ver = a;
		distance = 0;
		parent = NULL;
	}
};

class GraphAL
{

public:
	vector<node> G;
	int count = 0;
	int NoOfEdges;

	GraphAL()
	{
	}

	GraphAL(int N)
	{
		NoOfEdges = N;

		for (int i = 0; i < N; i++)
		{
			node n(i, char(i + 65));
			G.push_back(n);
		}
	}

	void print()
	{
		cout << "Adjacency List : \n\n";
		for (int i = 0; i < G.size(); i++)
		{
			cout << G[i].Ver << " (" << G[i].distance << ")" << " : ";
			for (auto j = G[i].Ns.begin(); j != G[i].Ns.end(); j++)
			{
				cout << (*j)->Ver << " ";
			}

			cout << endl;
		}
		cout << endl;
	}

	void addNeighbour(int r, int id)
	{
		G[r].Ns.push_back(&G[id]);
	}

	void addNeighbour(char row, char id)
	{
		int r = row - 65;
		int i = id - 65;

		G[r].Ns.push_back(&G[i]);
	}

	void DisplayAll()
	{
		for (int i = 0; i < G.size(); i++)
		{
			cout << G[i].Ver << " ";
			cout << "distance = " << G[i].distance << " ";
			if (G[i].parent != NULL)
				cout << "parent = " << G[i].parent->Ver << " \n";
			else
				cout << "parent = NULL" << "\n";
		}
	}

	void BFSVisit(char source)
	{
		int r = source - 65;
		queue<node*> Q;
		Q.push(&G[r]);

		while (Q.empty() == false)
		{
			node* u = Q.front();
			Q.pop();
			for (auto v = u->Ns.begin(); v != u->Ns.end(); v++)
			{
				//	cout << (*v)->Ver << " ";
				if ((*v)->visited == false)
				{
					(*v)->visited = true;

					(*v)->distance = u->distance + 1;
					(*v)->parent = u;
					Q.push(*v);
				}
			}
			u->visited = true;
		}
	}

	void DisplayPath(int id)
	{
		stack<node*> s;
		node*n = &G[id];

		s.push(n);
		while (1)
		{
			if (n->parent == NULL)
				break;
			else
			{
				s.push(n->parent);
				n = n->parent;
			}
		}

		cout << "\t\tPath : ";
		//cout << G[id].Ver << " ";
		while (!s.empty())
		{
			node *n = s.top();
			s.pop();

			cout << n->Ver << " ";
		}

		cout << "\n\n";
	}



	void DisplayPathRec(node* n,int s)
	{
		if (n->parent == NULL || n->id==s)
		{
			cout << n->Ver << " ";
			return;
		}

		DisplayPathRec(n->parent,s);
		cout << n->Ver << " ";

	}

	void SourceToDestinationPATH(int s,int d)
	{
		DisplayPathRec(&G[d],s);
	}

};


void CopyEdges(GraphAL &G, GraphAL* &T)
{
	for (int i = 0; i < G.G.size(); i++)
	{
		for (auto j = G.G[i].Ns.begin(); j != G.G[i].Ns.end(); j++)
		{
			T->addNeighbour(G.G[i].id, (*j)->id);
		}
	}
}

int FindMinimum(int id, vector<GraphAL*> &GG)
{
	int minindex = 0;
	int min = GG[0]->G[id].distance;
	for (int i = 1; i < GG.size(); i++)
	{
		if (GG[i]->G[id].distance < min)
		{
			min = GG[i]->G[id].distance;
			minindex = i;
		}
	}
	return minindex;
}

void BFSALL(GraphAL &G, vector<char> SS)
{

	vector<GraphAL*> GG;

	for (int i = 0; i < SS.size(); i++)
	{
		int size = G.G.size();
		GraphAL* g = new GraphAL(size);

		CopyEdges(G, g);

		GG.push_back(g);
	}

	for (int i = 0; i < SS.size(); i++)
	{
		GG[i]->BFSVisit(SS[i]);
	}

	/*for (int i = 0; i < SS.size(); i++)
	{
	GG[i]->DisplayAll();
	cout << "\n\n\n";
	}*/

	cout << "\nClosest vertexex from the sources \n\n";
	for (int i = 0; i < G.G.size(); i++)	// which vertex is closest to which vertex
	{

		int id = FindMinimum(G.G[i].id, GG);
		//cout << id<<"   ";
		if (char(i + 65) != SS[id])
			cout << char(i + 65) << " is close to " << SS[id] << endl;
	}

	cout << "\n\nPaths\n\n";

	for (int i = 0; i < G.G.size(); i++)	// which vertex is closest to which vertex
	{

		int id = FindMinimum(G.G[i].id, GG);
		if (char(i + 65) != SS[id])
		{
			cout << "Path from " << SS[id] << " to " << char(i + 65) << " ";
			GG[id]->DisplayPath(i);
		}
	}
}



int main()
{
	GraphAL G(8);

	G.addNeighbour('A', 'B');
	G.addNeighbour('A', 'E');

	G.addNeighbour('B', 'A');
	G.addNeighbour('B', 'F');


	G.addNeighbour('C', 'D');
	G.addNeighbour('C', 'F');
	G.addNeighbour('C', 'G');

	G.addNeighbour('D', 'C');
	G.addNeighbour('D', 'G');
	G.addNeighbour('D', 'H');

	G.addNeighbour('F', 'B');
	G.addNeighbour('F', 'C');
	G.addNeighbour('F', 'G');


	G.addNeighbour('G', 'C');
	G.addNeighbour('G', 'D');
	G.addNeighbour('G', 'F');
	G.addNeighbour('G', 'H');

	G.addNeighbour('H', 'D');
	G.addNeighbour('H', 'G');

	G.print();

	/*vector<char> SS({ 'B', 'H' });
	BFSALL(G, SS);*/


	//G.DisplayAll();

	G.BFSVisit('B');
	G.DisplayPath(7);
	G.SourceToDestinationPATH(5,7);

	system("pause");
	return 0;
}