#include<iostream>
#include <vector>

using namespace std;

void print(char* msg, int A[], int S)
{
	cout << msg;
	for (int i = 0; i < S; i++)
		cout << A[i] << " ";
	cout << "\n\n";
}
void print(char* msg, vector<int> v)
{
	cout << msg;
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "\n\n";
}

void multiply(vector<int>X, vector<int>Y)
{
	vector<int>XL(X.begin(), X.begin()+ X.size()/2);
	vector<int>XR(X.begin() + X.size() / 2, X.end());
	vector<int>YL(Y.begin(), Y.begin() + Y.size() / 2);
	vector<int>YR(Y.begin() + Y.size() / 2, Y.end());

	print("XL : ", XL);
	print("XR : ", XR);
	print("YL : ", YL);
	print("YR : ", YR);
}

void copy(vector<int> &A, vector<int> &B)
{
	int i = A.size() - 1;
	int j = B.size() - 1;
	for (; j >= 0; j--,i--)
	{
		A[i] = B[j];
	}
}
// 1 2 3
//0 0 0 0 0 0
//0 1 2 3 4 5
void mul(vector<int> A,vector<int> B)
{
	vector<int> v1(A.size()+B.size());
	vector<int> v2(A.size() + B.size());

	//copy(v1, A);
	//copy(v2, B);

	print("v1 : ", A);
	print("v2 : ", B);
	multiply(A, B);
}

int main()
{
	vector<int> A({ 1, 2, 3, 4 });
	vector<int> B({ 5, 6, 7, 8 });

	print("A : ", A);
	print("B : ", B);

	mul(A, B);


	system("pause");
	return 0;
}
