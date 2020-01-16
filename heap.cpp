#include<iostream>
using namespace std;

class Heap
{
	int A[200];
	int size;
	int count;
public:
	Heap()
	{
		size = 0;
		count = 0;
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


	void HeapifyUp(int A[],int i)
	{
		if (i == 0)
			return;


		int p = A[Parent(i)];
		if (A[i] < A[Parent(i)])
		{
			swap(A[i] , A[Parent(i)]);
			HeapifyUp(A, Parent(i));
		}
	}
	void HeapifyDown(int A[], int i)
	{
		// base case missing

		int m;
		int L = Left(i);
		int R = Right(i);
		
		if (A[L] < A[R])
			m = L;
		else
			m = R;

		if (A[i]>A[m])
		{
			swap(A[i], A[m]);
			HeapifyDown(A,m);
		}
		
	}
	void insert(int V)
	{
		A[count++] = V;
		HeapifyUp(A,count-1);
	}

	void BuildArray(int Arr[],int s)
	{
		for (int  i = 1; i < s; i++)
		{
			insert(Arr[i]);
		}
	}


	void print()
	{
		cout << "Heap : ";
		for (int i = 0; i < count; i++)
		{
			cout << A[i] << " ";
		}
		cout << endl << endl;
	}

	void heapSort(int Arr,int s)
	{

		for (int i = 0; i < s; i++)
		{
			int T = 1, HS;
		}
	}

};

void print(int A[],int s)
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
	Heap heap;

	
	int A[] = { 5, 3, 4, 8, 2, 1, 4, 9, 7, 3, 8, 51, 58 };
	int size = sizeof(A) / sizeof(A[0]);

	heap.BuildArray(A, size);

	//heap.print();

	print(A,size);


	system("pause");
}
