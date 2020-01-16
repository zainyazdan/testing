#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<stack>

using namespace std;

class GraphAL
{
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

	vector<node> G;
	int count = 0;
	int NoOfEdges;

public:

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

	bool IS_ApproximateNEIGHBOUR(char V,int T)
	{
		BFSVisit(V);

		for (int i = 0; i < G.size(); i++)
		{
			if (G[i].distance > T)
				return false;
		}
		return true;
	}



};



int main()
{
	GraphAL G(7);

	G.addNeighbour('A', 'B');
	G.addNeighbour('A', 'D');

	G.addNeighbour('B', 'A');
	G.addNeighbour('B', 'C');

	G.addNeighbour('C', 'B');
	G.addNeighbour('C', 'D');
	G.addNeighbour('C', 'E');
	G.addNeighbour('C', 'F');

	G.addNeighbour('D', 'A');
	G.addNeighbour('D', 'C');

	G.addNeighbour('E', 'C');

	G.addNeighbour('F', 'C');
	G.addNeighbour('F', 'G');

	G.addNeighbour('F', 'C');
	G.addNeighbour('F', 'G');

	G.addNeighbour('G', 'F');

	G.print();

	cout<<"is : "<<G.IS_ApproximateNEIGHBOUR('G', 2);

	//G.DisplayAll();


	system("pause");
	return 0;
}