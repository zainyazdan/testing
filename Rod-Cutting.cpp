#include<iostream>
#include<vector>
using namespace std;


int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}


int Rod_Cutting_Rec(vector<int> p,int n)
{
	if (n == 0)
		return 0;

	int q = INT_MIN;
	for (int i = 0; i < n ; i++)
	{
		q = max(q, p[i] + Rod_Cutting_Rec(p, n - i - 1));
	}
	return q;
}

int Rod_Cutting_M(vector<int> p, vector<int> &r, int n)
{
	if (r[n] != -1)
		return r[n];

	int q = INT_MIN;
	for (int i = 0; i < n; i++)
	{
		q = max(q, p[i] + Rod_Cutting_M(p,r, n - i - 1));
	}

	return r[n] = q;
}


int Rod_Cutting_Memoized(vector<int> p, int n)
{
	vector<int> r(p.size() + 1, { -1 });
	r[0] = 0;
	return Rod_Cutting_M(p, r, n);
}


int Rod_Cutting_BottomUp(vector<int> p, int n)
{
	vector<int> r(p.size() + 1, { -1 });
	r[0] = 0;

	for (int j = 1; j <= n; j++)
	{
		int q = INT_MIN;
		for (int i = 0; i < j; i++)
		{
			q = max(q, p[i] + r[j - i - 1]);
		}
		r[j] = q;
	}
	return r[n];
}

int main()
{

	vector<int> p({ 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 });


	cout << "Rod Cutting (recursive) : " << Rod_Cutting_Rec(p, 9) << '\n';
	cout << "Rod Cutting (Bottom-Up) : " << Rod_Cutting_Memoized(p, 9) << '\n';
	cout << "Rod Cutting (Bottom-Up) : " << Rod_Cutting_BottomUp(p, 9) << '\n';

	
	system("pause");
	return 0;
}
