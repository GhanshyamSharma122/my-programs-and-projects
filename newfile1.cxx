#include <iostream.h>
using namespace std;
int main()
{
	int n, a[100];
	cout << "enter the number if numbers you want you compare in ascending order" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (a[i] > a[j])
			{
				int temp = a[i];
				a[i] = a[j] ;
				 a[j] = temp;
			}
		}
	}
	cout<< "sorted number\n";
	for (int i = 1; i <= n; i++)
	{
		cout << a[i] << endl;
	}
	return 0;
}