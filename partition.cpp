#include<iostream>
using namespace std;

int S(int n, int k)
{

	if (n == 0 && k == 0)
		return 1;
	if (n == 0 && k != 0)
		return 0;

	if (n != 0 && k == 0)
		return 0;

	return (k*S(n - 1, k) + S(n - 1, k - 1));
}

int P(int n)
{
	int num = 0;
	for (int k = 1; k <= n; k++)
		num = num + S(n, k);
	return num;
}

int main()
{
	int n;
	cout << "Enter n: ";
	cin >> n;
	int num = P(n);
	cout << "Partition number : " << num << '\n';

	system("pause");
	return 0;
}
