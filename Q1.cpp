#include<iostream>
using namespace std;

class MinHeap
{
	int A[200];
	int size;
	int count;
public:
	MinHeap()
	{
		size = 0;
		count = 1;
	}

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
	void HeapifyDown(int A[], int i)
	{
		// base case missing
		int m;
		int L = Left(i);
		int R = Right(i);

		if (L < count && A[L] < A[R])
			m = L;
		else if (R < count && A[R] < A[L])
			m = R;

		if (A[i]>A[m])
		{
			swap(A[i], A[m]);
			HeapifyDown(A, m);
		}
	}

	/*void insert(int A[],int V,int &count)
	{
		A[count++] = V;
		HeapifyUp(A, count - 1);
	}*/

	void insert(int V)
	{
		A[count++] = V;
		HeapifyUp(A, count - 1);
	}

	/*void BuildArray(int Arr[], int s)
	{
		int HS = 1;
		for (int i = 1; i < s; i++)
		{
			insert(Arr,Arr[i], HS);
		}
	}*/

	void printTree()
	{
		cout << "MIN Heap : \n\n";
		int n = 1;
		for (int i = 1; i < count; i++)
		{
			if (i == n)
			{
				cout << "\n";
				n *= 2;
			}
			cout << A[i] << " ";
			
		}
		cout << endl << endl;
	}

	void print()
	{
		cout << "MIN Heap : \n\n";
		for (int i = 1; i < count; i++)
		{
			cout << A[i] << " ";
		}
		cout << endl << endl;
	}

	void heapSort(int Arr, int s)
	{
		for (int i = 1; i < s; i++)
		{
			int T = 1, HS;
		}
	}
};

void print(int A[], int s)
{
	cout << "Arr : ";
	for (int i = 0; i < s; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl << endl;
}

int main()
{
	MinHeap heap;

	//int A[] = { 5, 3, 4, 8, 2, 1, 4, 9, 7, 3, 8, 51, 58 };
	int A[] = { 5, 3, 4, 8, 2 ,1,6};
	int size = sizeof(A) / sizeof(A[0]);

	//heap.BuildArray(A, size);
	
	for (int i = 0; i < size; i++)
	{
		heap.insert(A[i]);
	}

	heap.print();

	//print(A, size);


	system("pause");
}
