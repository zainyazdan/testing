#include<iostream>
#include<vector>
using namespace std;

int longestContiguousSum(int a[], int s)
{

	int maxSoFar = INT_MIN, maxEndingHere = 0;

	for (int i = 0; i < s; i++)
	{
		maxEndingHere = maxEndingHere + a[i];
		if (maxSoFar < maxEndingHere)
			maxSoFar = maxEndingHere;

		if (maxEndingHere < 0)
			maxEndingHere = 0;
	}
	return maxSoFar;
}

int max(int valueA, int valueB)
{
	if (valueA > valueB)
		return valueA;

	return valueB;
}

int TopDownHelper(int a[], int s, vector<int> &m, int i)
{	
	if (i <= 0)
		return 0;

	m[i] = max(TopDownHelper(a, s, m, i - 1) + a[i], a[i]);

	return m[i];
}

// TopDown

int longestContiguousSumTopDown(int a[], int s)
{
	vector<int> m(s, { -1 });
	m[0] = a[0];

	TopDownHelper(a, a[0], m, s - 1);
	int max = INT_MIN;
	for (int i = 0; i < m.size(); i++)
	{
		if (max < m[i])
			max = m[i];
	}
	return max;
}

int longestContiguousSumBU(int a[], int s)
{
	vector<int> m(s, { -1 });
	m[0] = a[0];

	for (int i = 1; i < s; i++)
		m[i] = max(m[i - 1] + a[i], a[i]);

	int max = INT_MIN;
	for (int i = 1; i < s; i++)
	if (max < m[i])
		max = m[i];

	return max;
}

// Recursive

int longestContiguousSumRecursive(int a[], int s, int &maxx, int i, vector<int> &m)
{
	if (i == 0)
		return 0;

	longestContiguousSumRecursive(a, s, maxx, i - 1, m);
	m[i] = max(m[i - 1] + a[i], a[i]);
	if (maxx < m[i])
		maxx = m[i];
	return maxx;
}


void printArray(int a[], int s)
{
	for (int i = 0; i < s; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main()
{
	int a[] = { -2, -3, 4, -1, -2, 1, 5, -1 };
	int size = 8;
	int max = a[0];
	vector<int> m(size, { -1 });
	printArray(a, size);
	cout << "LONGEST CONTIGUOS SUM Recursive : " << longestContiguousSumRecursive(a, size, max, size - 1, m) << endl;
	cout << "LONGEST CONTIGUOS SUM Town Down : " << longestContiguousSumTopDown(a, size) << endl;
	cout << "LONGEST CONTIGUOS SUM Bottom Up : " << longestContiguousSumBU(a, size) << endl;

	system("pause");
	return 0;
}