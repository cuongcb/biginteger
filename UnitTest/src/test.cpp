#include <vector>
#include <iostream>

using namespace std;

void printVector(const vector<int> &v)
{
	for (auto iter : v)
	{
		cout << iter << " ";
	}
	cout << endl;
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	vector<int> v1(arr, arr + 6);
	vector<int> v2(v1.begin(), v1.begin());

	printVector(v1);
	printVector(v2);

	system("pause");
	return 0;
}