#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void countingSort(vector<int> &arr)
{
    int max = *max_element(arr.begin(), arr.end());
    //  int min = *min_element(arr.begin(), arr.end());
    vector<int> count(max + 1, 0);
    vector<int> output(arr.size(), 0);
    for (int i = 0; i < arr.size(); i++)
    {
        count[arr[i]]++;
    }
    for (int i = 1; i < count.size(); i++)
    {
        count[i] = count[i - 1] + count[i];
    }
    for (int i = arr.size()-1; i >= 0; i--)
    {
        output[--count[arr[i]]] = arr[i];
    }
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = output[i];
    }
}
main()
{
    vector<int> v = {1, 3, 2, 8, 5, 1, 2, 7};
    countingSort(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}