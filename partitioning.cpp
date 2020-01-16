#include<iostream>
#include<vector>
using namespace std;



int S(int n,int k)
{
	if (n == 0 && k == 0)
		return 1;
	if (n != 0 && k == 0)
		return 0;
	if (n == 0 && k != 0)
		return 0;

	return k*S(n - 1, k) + S(n - 1, k - 1);
}

int Partition_Recursive(int n)
{
	int ans = 0;
	for (int k = 0; k <=n ; k++)
	{
		ans += S(n,k);
	}
	return ans;
}



int S2(int n, int k, vector<vector<int>> &V)
{
	if (V[n][k] != -1)
		return V[n][k];

	return V[n][k] = k*S2(n - 1, k, V) + S2(n - 1, k - 1, V);
}

int partition_Memo(int n)
{

	vector<vector<int>>V;
	V.resize(n + 1);
	for (int i = 0; i <= n; i++)
	{
		V[i].resize(n + 1, {-1});
	}

	V[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		V[i][0] = 0;
		V[0][i] = 0;
	}

	int ans = 0;
	for (int k = 0; k <= n; k++)
	{
		ans += S2(n, k,V);
	}
	return ans;
}



int partition_BU(int n)
{
	vector<vector<int>>V;
	V.resize(n + 1);
	for (int i = 0; i <= n; i++)
	{
		V[i].resize(n + 1);
	}

	V[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		V[i][0] = 0;
		V[0][i] = 0;
	}

	for (int i = 1; i <= n; i++)
	{
		for (int k = 1; k <= n; k++)
		{
			V[i][k] = k*V[i - 1][k] + V[i - 1][k - 1];
		}
	}

	int ans = 0;
	for (int i = 0; i <= n; i++)
	{
		ans += V[n][i];
	}

	return ans;
}


int main()
{
	int n;
	cout << "Enter n: ";
	cin >> n;

	cout << "Partition number (recursive) : " << Partition_Recursive(n) << '\n';
	cout << "Partition number (Bottom-Up) : " << partition_BU(n) << '\n';
	cout << "Partition number (Memoized) : " << partition_Memo(n) << '\n';


	system("pause");
	return 0;
}
