#include<iostream>
#include<algorithm>
#include <vector>
#include <map> 
#include <queue> 
#include <list>
#include <time.h> 

using namespace std;

// Q1 (Heap)

int Left(int i)
{
	return i * 2;
}

int Right(int i)
{
	return (i * 2) + 1;
}

int Parent(int i)
{
	return (i / 2);
}

void HeapifyUp(int A[], int i)
{
	if (i == 1)
		return;

	int p = Parent(i);
	if (A[i] <  A[p])
	{
		swap(A[i], A[p]);
		HeapifyUp(A, p);
	}
}
void HeapifyDown(int A[], int i, int s)
{
	int m = -1;
	int L = Left(i);
	int R = Right(i);

	if (L <= s && R <= s && A[L] < A[R])
		m = L;
	else if (L <= s && R <= s && A[R] < A[L])
		m = R;
	else if (L <= s && R >= s)
		m = L;

	if (m != -1 && A[m]<A[i])
	{
		swap(A[i], A[m]);
		HeapifyDown(A, m, s);
	}
}

void insert(int A[], int V, int &count)
{
	A[count++] = V;
	HeapifyUp(A, count - 1);
}

void BuildArray(int Arr[], int s)
{
	int HS = 2;
	for (int i = 2; HS != s; i++)
	{
		insert(Arr, Arr[i], HS);
	}
}

//Q1  Heap Sort

int ExtractMin(int A[], int &S)
{
	int t = A[1];
	int p = A[S - 1];

	swap(A[1], A[S - 1]);
	S--;
	HeapifyDown(A, 1, S - 1);
	return t;
}



void heapSort(int A[], int s)
{
	int HS = s;
	for (int i = 1; i < s; i++)
	{
		int m = ExtractMin(A, HS);
		//cout << m << " ";
		A[s - i] = m;
	}
}

//Q1 Tree implimentation


class node1{
public:
	int val;
	node1* parent;
	node1* left;
	node1* right;
	node1(int n)
	{
		val = n;
		parent, left, right = NULL;
	}
};

class MinHeap
{
public:
	node1* Root;
	int count;
	queue <node1*> Q;

	MinHeap()
	{
		Root = NULL;
		count = 0;
	}

	void HeapifyUp(node1* n)
	{
		if (n->parent == NULL)
			return;

		if (n->parent->val > n->val)
		{
			swap(n->parent->val, n->val);
			HeapifyUp(n->parent);
		}

	}

	void insert(int v)
	{
		node1 *n = new node1(v);

		if (Root == NULL)
		{
			Root = n;
			Q.push(n);
			count++;
		}
		else
		{
			node1 *c = Q.front();

			if (c->left == NULL && c->right == NULL)
			{
				n->parent = c;
				count++;
				c->left = n;
				Q.push(n);

				HeapifyUp(n);

			}
			else if (c->left != NULL && c->right == NULL)
			{
				n->parent = c;
				c->right = n;

				count++;
				Q.pop();
				Q.push(n);
				HeapifyUp(n);
			}
		}
	}

	void print()
	{
		cout << "\n\nTREE (LNR) : ";
		printLNR(Root);
	}

	void printLNR(node1 * n)
	{
		if (n == NULL)
			return;

		printLNR(n->left);

		cout << n->val << " ";

		printLNR(n->right);
	}

	void print2()
	{
		cout << "\n\nHeap (array order) : ";

		queue <node1*> q;
		q.push(Root);

		while (q.size() != 0)
		{
			node1* c = q.front();
			cout << c->val << " ";

			if (c->left != NULL && c->right != NULL)
			{
				q.push(c->left);
				q.push(c->right);
				q.pop();
			}
			else if (c->left != NULL && c->right == NULL)
			{
				q.push(c->left);
			}
			else
				q.pop();
		}
	}
};

//Question 2 (Adjacency list implimentation)


class node
{
public:
	int id;
	int cn;
	int scc;
	bool visited;
	list<node*> Ns;

	node(int i)
	{
		cn = 0;
		id = i;
		visited = false;
	}
};

class GraphAL
{
public:
	vector<node> G;
	int count = 0;
	int NoOfVertex;

	GraphAL(int N)
	{
		NoOfVertex = N;

		for (int i = 0; i < N; i++)
		{
			node n(i);
			G.push_back(n);
		}
	}

	void print()
	{
		cout << "Adjacency List : \n\n";
		for (int i = 0; i < G.size(); i++)
		{
			cout << G[i].id << " : ";
			for (auto j = G[i].Ns.begin(); j != G[i].Ns.end(); j++)
			{
				cout << (*j)->id << "  ";
			}

			cout << endl;
		}
		cout << endl;
	}

	void addNeighbour(int row, int id)
	{
		G[row].Ns.push_back(&G[id]);
	}

	void printaddress(int i)	// For Dry Run
	{
		cout << &G[i];
	}

	void displayCN(int n)	// For Dry Run
	{
		cout << "[" << n << "]   ";
		for (int i = 0; i < NoOfVertex; i++)
		{
			if (G[i].cn == n)
				cout << G[i].id << " ";
		}
		cout << endl;
	}



	void Explore(node *v, int cn)
	{
		v->visited = true;
		v->cn = cn;

		for (auto j = v->Ns.begin(); j != v->Ns.end(); j++)
		{
			int id = (*j)->id;
			//cout << (*j)->id << " ";
			if ((*j)->visited == false)
				Explore(*j, cn);
		}
	}

	void DFS()
	{
		int ccn = 0;
		for (int i = 0; i < NoOfVertex; i++)
		{
			if (G[i].visited == false)
			{
				Explore(&G[i], ++ccn);
			}
		}
		cout << "Total Connected Components : " << ccn << endl << endl;
	}

	bool HasConnection(int i, int j)
	{
		if (G[i].cn == G[j].cn)
			return true;
		return false;
	}

	//Question 4 Transpose

	void FindTranspose(GraphAL &T)
	{
		for (int i = 0; i < G.size(); i++)
		{
			//cout << Graph.G[i].id << " : ";
			for (auto j = G[i].Ns.begin(); j != G[i].Ns.end(); j++)
			{
				//cout << (*j)->id << " ";
				T.addNeighbour((*j)->id, i);
			}
		}
	}

	//Question 7 strongly connected component


	void ExploreWithStack(list<node*> &Stack, node *v, int cn)
	{
		v->visited = true;
		v->cn = cn;
		int id = v->id;
		for (auto j = v->Ns.begin(); j != v->Ns.end(); j++)
		{
			int id = (*j)->id;
			//cout << (*j)->id << " ";
			if ((*j)->visited == false)
				ExploreWithStack(Stack, *j, cn);

		}
		//cout << v->id<<"  ";
		Stack.push_front(v);
	}

	void ModifiedDFS(list<node*> &Stack)
	{
		int ccn = 0;
		for (int i = 0; i < NoOfVertex; i++)
		{
			if (G[i].visited == false)
			{
				ExploreWithStack(Stack, &G[i], ++ccn);
			}
		}
		//cout << "Total Connected Components : " << ccn << endl << endl;
	}

	void ModifiedExplore2(node *v, int scc)
	{
		v->visited = true;
		v->scc = scc;

		for (auto j = v->Ns.begin(); j != v->Ns.end(); j++)
		{
			int id = (*j)->id;
			if ((*j)->visited == false)
				ModifiedExplore2(*j, scc);
		}
		//cout << v->id<<"  ";
	}


	void SCC(list<node*> Stack)
	{
		int scc = 0;
		for (auto j = Stack.begin(); j != Stack.end(); j++)
		{
			int id = (*j)->id;
			//cout << (*j)->id << " ";
			if ((*j)->visited == false)
				ModifiedExplore2(*j, ++scc);
		}
	}

	void displaySCC(int n)	// For Dry Run
	{
		cout << "SCC " << n << " :  ";
		for (int i = 0; i < NoOfVertex; i++)
		{
			if (G[i].scc == n)
				cout << G[i].id << " ";
		}
		cout << endl;
	}

	void StronglyConnectedComponentHelper()
	{
		GraphAL T(NoOfVertex);
		FindTranspose(T);
		//T.print();

		list<node*> Stack;
		T.ModifiedDFS(Stack);
		//T.SCC(Stack);

		for (int i = 0; i < NoOfVertex; i++)
			G[i].visited = false;

		int scc = 0;
		for (auto j = Stack.begin(); j != Stack.end(); j++)
		{
			int id = (*j)->id;

			//cout << (*j)->id << " ";

			if (G[(*j)->id].visited == false)
				ModifiedExplore2(&G[(*j)->id], ++scc);
		}

		cout << "\n\nStrongly Connected Components : \n\n";
		for (int i = 1; i <= scc; i++)
			displaySCC(i);
	}

	// Q5 inverse

	bool SearchNeighbour(int row, int id)
	{
		for (auto j = G[row].Ns.begin(); j != G[row].Ns.end(); j++)
		{
			if ((*j)->id == id)
				return true;
		}
		return false;
	}

	void FindInverse(GraphAL &I)
	{
		for (int i = 0; i < NoOfVertex; i++)
		{
			for (int j = 0; j < NoOfVertex; j++)
			{
				if (!SearchNeighbour(i, j) && i != j)
					I.addNeighbour(i, j);
			}
		}
	}
// Q7 tupological

	void TopologicalOrder()
	{
		list<node*> Stack;
		ModifiedDFS(Stack);
		cout << "Topological Order : ";
		for (auto j = Stack.begin(); j != Stack.end(); j++)
			cout << (*j)->id << " ";
		cout << endl << endl;
	}


};

// Adjacency matrix

class GraphAM
{
public:
	vector<bool> visited;
	vector<int> CN;
	vector<vector<int>> G;

	GraphAM(int N)
	{
		G.resize(N);
		visited.resize(N);
		CN.resize(N);

		for (int i = 0; i < N; i++)
		{
			G[i].resize(N);
		}
	}

	void print()
	{
		cout << "Adjacency Matrix : \n\n";
		for (int i = 0; i < G.size(); i++)
		{
			cout << i << " : ";
			for (int j = 0; j < G[i].size(); j++)
			{
				cout << G[i][j] << "  ";
			}
			cout << endl;

			cout << endl;
		}
	}

	vector<int>& operator[](int r)
	{
		return G[r];
	}

	void RandominitializeGraph()	//		For Dry Run
	{
		for (int i = 0; i < G.size(); i++)
		{
			for (int j = 0; j < G[i].size(); j++)
			{
				G[i][j] = (rand() % 2);
			}
		}
	}



	void Explore(int v, int cn)
	{
		visited[v] = true;
		CN[v] = cn;

		for (int i = 0; i < G[v].size(); i++)
		{
			if (G[v][i] == 1 && visited[i] == false)
				Explore(i, cn);
		}
	}

	void DFS()
	{
		int ccn = 0;
		for (int i = 0; i < G.size(); i++)
		{
			if (visited[i] == false)
			{
				Explore(i, ++ccn);
			}
		}
		cout << "Total Connected Components : " << ccn << endl << endl;
	}

	bool HasConnection(int i, int j)
	{
		if (CN[i] == CN[j])
			return true;
		return false;
	}


	void Transpose(GraphAM &T)
	{
		for (int i = 0; i < G.size(); i++)
		{
			for (int j = 0; j < G[i].size(); j++)
			{
				if (G[i][j] == 1)
				{
					T[j][i] = 1;
				}
			}
		}
	}
	void FindInverse(GraphAM &T)
	{
		for (int i = 0; i < G.size(); i++)
		{
			for (int j = 0; j < G[i].size(); j++)
			{
				if (G[i][j] == 1 && i != j)
					T[i][j] = 0;
				else if (G[i][j] == 0 && i != j)
					T[i][j] = 1;
			}
		}
	}



};



void print(char *msg, int A[], int s)
{
	cout << msg;
	for (int i = 1; i < s; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl << endl;
}

// Q8 part a

int Partition(int A[], int Si, int Ei, int  V)
{
	int si = Si, ei = Ei;
	do
	{
		while (A[si] < V)
			si++;
		while (A[ei] > V)
			ei--;
		if (A[si] == A[ei])
			ei--;
		else if (si < ei)
			swap(A[si], A[ei]);

	} while (si < ei);
	return si;
}


int RandomizedSelect(int A[], int si, int ei, int i)
{
	if (si == ei)
		return A[si];

	int ri = rand() % (ei - si) + 1;
	int pi = Partition(A, si, ei, A[ri]);
	int k = pi - si + 1;

	if (i == k)
		return A[pi];

	else if (i < k)
		return RandomizedSelect(A, si, pi - 1, i);
	else
		return RandomizedSelect(A, pi + 1, ei, i - k);
}

void QuickSort(int A[], int si, int ei)
{
	if (si >= ei)
		return;
	//srand(time(NULL));

	int mid = RandomizedSelect(A, si, ei, (si + ei) / 2);

	int pi = Partition(A, si, ei, mid);
	QuickSort(A, si, pi - 1);
	QuickSort(A, pi + 1, ei);
}

// Q9 counting sort


int maxValue(vector<int>A)
{
	int max = A[0];
	for (int i = 1; i < A.size(); i++)
	{
		if (A[i]>max)
			max = A[i];
	}
	return max;
}
void print(char* msg, vector<int>A)
{
	cout << msg;
	for (int i = 0; i < A.size(); i++)
	{
		cout << A[i] << " ";
	}
	cout << endl << endl;
}

void CountingSort(vector<int> &A)
{
	int max = maxValue(A) + 1;

	vector<int>C(max, 0);
	vector<int>B(A.size(), 0);

	for (int i = 0; i < A.size(); i++)
		C[A[i]]++;

	for (int i = 1; i < C.size(); i++)
		C[i] = C[i] + C[i - 1];

	//print("C : ",C);

	int a, b;
	for (int i = A.size() - 1; i >= 0; i--)
	{
		a = A[i];
		b = C[a] - 1;

		B[b] = a;
		C[a]--;
	}
	print("After Sorting : : ", B);
}

void Initialize(vector<int> &A, int range)
{
	srand(time(NULL));
	for (int i = 0; i < A.size(); i++)
	{
		A[i] = rand() % range + 1;
	}
}


int main()
{
	int choice = 0;

	while (1)
	{
		cout << "1.  Heap\n";
		cout << "2.  Grapf implimemntation\n";
		cout << "3.  Connected components\n";
		cout << "4.  transpose\n";
		cout << "5.  Inverse of The directed graph\n";
		cout << "6.	 Multiplication of two N digits numbers\n";
		cout << "7.  Strongly connected components + Topological Ordering\n";
		cout << "8.  QuickSort\n";
		cout << "9.  Counting Sort\n";
		cout << "10.  Matrix Multiplication\n";
		cout << "-1. EXIT\n\n";
		cout << "choice : ";
		cin >> choice;

		if (choice == -1)
			break;

		if (choice == 1)
		{

			int A[] = { -1, 5, 3, 4, 8, 2, 1, 9, 7, 51, 58 };
			int size = sizeof(A) / sizeof(A[0]);

			print("\nBefore Sorting : ", A, size);

			BuildArray(A, size);

			heapSort(A, size);

			print("Decending Sorting : ", A, size);
			cout << "\n_____________________________________\n";

			cout << "\nTree implimentation";
			MinHeap H;

			H.insert(5);
			H.insert(3);
			H.insert(4);
			H.insert(8);
			H.insert(2);
			H.insert(1);
			H.insert(6);

			//H.print();

			H.print2();

		}
		else if (choice == 2)
		{
			{ int size = 4;
			GraphAL G(size);

			G.addNeighbour(0, 1);
			G.addNeighbour(0, 2);

			G.addNeighbour(1, 0);

			G.addNeighbour(2, 3);

			G.addNeighbour(3, 1);

			G.print(); }
		
			int size = 4;
			GraphAM G(size);

			G[0][1] = 1;
			G[0][2] = 1;

			G[1][0] = 1;
			G[2][3] = 1;

			G[3][1] = 1;

			G.print();
		}
		else if (choice == 3)
		{
			{int size = 12;
			GraphAL G(size);

			G.addNeighbour(0, 1);
			G.addNeighbour(0, 4);

			G.addNeighbour(1, 0);

			G.addNeighbour(2, 3);
			G.addNeighbour(2, 6);
			G.addNeighbour(2, 7);

			G.addNeighbour(3, 2);
			G.addNeighbour(3, 7);

			G.addNeighbour(4, 0);
			G.addNeighbour(4, 8);

			G.addNeighbour(6, 2);
			G.addNeighbour(6, 7);
			G.addNeighbour(6, 10);

			G.addNeighbour(7, 3);
			G.addNeighbour(7, 6);
			G.addNeighbour(7, 10);
			G.addNeighbour(7, 11);

			G.addNeighbour(8, 4);
			G.addNeighbour(8, 9);

			G.addNeighbour(9, 4);
			G.addNeighbour(9, 8);

			G.addNeighbour(10, 6);
			G.addNeighbour(10, 7);

			G.addNeighbour(11, 7);

			G.print();

			G.DFS();

			//G.displayCN(1);
			//G.displayCN(2);
			//G.displayCN(3);

			int Vertex1 = 0, Vertex2 = 8;

			if (G.HasConnection(Vertex1, Vertex2))
				cout << "\nVertex " << Vertex1 << " and " << "Vertex " << Vertex2 << " has a Connection \n\n";
			else
				cout << "\nVertex " << Vertex1 << " and " << "Vertex " << Vertex2 << " donot has a Connection \n\n";}

			cout << "\n_____________________________________\n";
			int size = 12;
			GraphAM G(size);

			G[0][1] = 1;
			G[0][4] = 1;

			G[1][0] = 1;

			G[2][3] = 1;
			G[2][6] = 1;
			G[2][7] = 1;


			G[3][2] = 1;
			G[3][7] = 1;

			G[4][0] = 1;
			G[4][8] = 1;

			G[6][2] = 1;
			G[6][7] = 1;
			G[6][10] = 1;

			G[7][3] = 1;
			G[7][6] = 1;
			G[7][10] = 1;
			G[7][11] = 1;

			G[8][4] = 1;
			G[8][9] = 1;

			G[9][4] = 1;
			G[9][8] = 1;

			G[10][6] = 1;
			G[10][7] = 1;

			G[11][7] = 1;

			G.print();


			G.DFS();
			int Vertex1 = 0, Vertex2 = 8;

			if (G.HasConnection(Vertex1, Vertex2))
				cout << "\Vertex " << Vertex1 << " and " << "Vertex " << Vertex2 << " has a Connection \n\n";
			else
				cout << "\Vertex " << Vertex1 << " and " << "Vertex " << Vertex2 << " donot has a Connection \n\n";

		}
		else if (choice == 4)
		{
			int size = 12;
			GraphAL G(size);

			G.addNeighbour(0, 1);
			G.addNeighbour(0, 4);

			G.addNeighbour(1, 0);

			G.addNeighbour(2, 3);
			G.addNeighbour(2, 6);
			G.addNeighbour(2, 7);

			G.addNeighbour(3, 2);
			G.addNeighbour(3, 7);

			G.addNeighbour(4, 0);
			G.addNeighbour(4, 8);

			G.addNeighbour(6, 2);
			G.addNeighbour(6, 7);
			G.addNeighbour(6, 10);

			G.addNeighbour(7, 3);
			G.addNeighbour(7, 6);
			G.addNeighbour(7, 10);
			G.addNeighbour(7, 11);

			G.addNeighbour(8, 4);
			G.addNeighbour(8, 9);

			G.addNeighbour(9, 4);
			G.addNeighbour(9, 8);

			G.addNeighbour(10, 6);
			G.addNeighbour(10, 7);

			G.addNeighbour(11, 7);

			G.print();

			GraphAL T(size);
			G.FindTranspose(T);
			cout << "\n\n\nTranspose of ";
			T.print();
			cout << "\n_____________________________________\n";

			{int size = 12;
			GraphAM G(size);

			G[0][1] = 1;
			G[0][4] = 1;

			G[1][0] = 1;

			G[2][3] = 1;
			G[2][6] = 1;
			G[2][7] = 1;


			G[3][2] = 1;
			G[3][7] = 1;

			G[4][0] = 1;
			G[4][8] = 1;

			G[6][2] = 1;
			G[6][7] = 1;
			G[6][10] = 1;

			G[7][3] = 1;
			G[7][6] = 1;
			G[7][10] = 1;
			G[7][11] = 1;

			G[8][4] = 1;
			G[8][9] = 1;

			G[9][4] = 1;
			G[9][8] = 1;

			G[10][6] = 1;
			G[10][7] = 1;

			G[11][7] = 1;

			G.print();

			GraphAM T(size);
			G.Transpose(T);
			cout << "\n\n\nTranspose of ";
			T.print(); }
		}
		else if (choice == 5)
		{
			{ int size = 4;
			GraphAL G(size);


			G.addNeighbour(0, 1);
			G.addNeighbour(0, 2);

			G.addNeighbour(1, 2);

			G.addNeighbour(2, 3);
			G.addNeighbour(3, 1);

			G.print();

			GraphAL Inverse(size);


			G.FindInverse(Inverse);
			cout << "Inverse ";
			Inverse.print();
			}
			cout << "\n_____________________________________\n";

			int size = 4;
			GraphAM G(size);

			G[0][1] = 1;
			G[0][2] = 1;

			G[1][2] = 1;

			G[2][3] = 1;

			G[3][1] = 1;

			G.print();

			GraphAM Inverse(size);
			G.FindInverse(Inverse);
			cout << "\n\n\nInverse of ";
			Inverse.print();
		}
		else if (choice == 6)
		{

		}
		else if (choice == 7)
		{

			int size = 12;
			GraphAL G(size);
			G.addNeighbour(1, 0);	G.addNeighbour(1, 4);
			G.addNeighbour(2, 1);	G.addNeighbour(2, 5);
			G.addNeighbour(3, 1);	G.addNeighbour(4, 1);
			G.addNeighbour(5, 2);	G.addNeighbour(5, 4);
			G.addNeighbour(6, 4);	G.addNeighbour(6, 8);
			G.addNeighbour(7, 5);	G.addNeighbour(7, 6);
			G.addNeighbour(9, 6);	G.addNeighbour(8, 9);
			G.addNeighbour(9, 11);	G.addNeighbour(10, 7);
			G.addNeighbour(11, 10);

			G.print();
			G.StronglyConnectedComponentHelper();
			cout << "\n_____________________________________\n";
			{
				int size = 9;
			GraphAL G(size);

			G.addNeighbour(0, 6);
			G.addNeighbour(2, 1);
			G.addNeighbour(4, 1);
			G.addNeighbour(4, 7);

			G.addNeighbour(5, 0);
			G.addNeighbour(5, 7);
			G.addNeighbour(7, 6);
			G.addNeighbour(8, 1);
			G.addNeighbour(8, 4);

			G.print();
			G.TopologicalOrder(); }
		}
		else if (choice == 8)
		{
			int A[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 2 };
			int size = sizeof(A) / 4;

			print("Before Sorting : ", A, size);

			QuickSort(A, 0, size - 1);

			print("After Sorting : ", A, size);
		}
		else if (choice == 9)
		{
			cout << "Part (a)\n\n";
			{int N = 5, range;
			vector<int>A(N);
			range = pow(N, 2);
			Initialize(A, range);
			print("Before Sorting : ", A);
			CountingSort(A); }
			cout << "\n_____________________________________\n";
			cout << "Part (b)\n\n";
			{int N = 5, range;
			vector<int>A(N);
			range = pow(N, 3);
			Initialize(A, range);
			print("Before Sorting : ", A);
			CountingSort(A);
			}
			cout << "\n_____________________________________\n";
			cout << "Part (c)\n\n";
			{int N = 5,k=4, range;
			vector<int>A(N);
			range = pow(N, k);
			Initialize(A, range);
			print("Before Sorting : ", A);
			CountingSort(A);
			}

		}
		else if (choice == 10)
		{

		}

		cout << "\n\n";
		system("pause");
		system("CLS");
	}
	system("pause");
	return 0;
}