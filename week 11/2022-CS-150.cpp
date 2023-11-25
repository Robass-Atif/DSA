#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <fstream>



using namespace std;
class compare
{
public:
    bool operator()(int &a, int &b)
    {
        return a >= b;
    }
};

void RandomArray(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i]=rand() % 100;
    }
}
void print(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl<<endl<<endl;
}

// heap sort
void heapSort(vector<int> &V)
{

    priority_queue<int, vector<int>, compare> PQ;
    for (int i = 0; i < V.size(); i++)
    {
        PQ.push(V[i]);
    }
    V.clear();
    while (!PQ.empty())
    {
        V.push_back(PQ.top());
        PQ.pop();
    }
}

// buble sort
template <typename T=int>
void bubbleSort(vector<T> &V)
{
    for (int i = 0; i < V.size(); i++)
    {
        for (int j = 0; j < V.size() - i - 1; j++)
        {
            if (V[j] > V[j + 1])
            {
                swap(V[j], V[j + 1]);
            }
        }
    }
}
// selection sort
template <typename T=int>
void selectionSort(vector<T> &V)
{
    for (int i = 0; i < V.size(); i++)
    {
        int minIndex = i;
        minIndex = min_element(V.begin() + i, V.end()) - V.begin();
        swap(V[i], V[minIndex]);
    }
}
// Quick Sort
template <typename T=int>
int partition(vector<T> &V, int start, int end)
{
    int pivot = V[end];
    int partitionIndex = start;
    for (int i = start; i < end; i++)
    {
        if (V[i] <= pivot)
        {
            swap(V[i], V[partitionIndex]);
            partitionIndex++;
        }
    }
    swap(V[partitionIndex], V[end]);
    return partitionIndex;
}
template <typename T=int>
void quickSort(vector<T> &V, int start, int end)
{
    if (start < end)
    {
        int partitionIndex = partition(V, start, end);
        quickSort(V, start, partitionIndex - 1);
        quickSort(V, partitionIndex + 1, end);
    }
}

void CreateRandomFile(string fn, int size, int Rn = 100)
{
    srand(time(0));
    ofstream Writer(fn);
    for (int i = 0; i < size * 1024 ; i++)
    {
        Writer << rand() % Rn << " ";
    }
}
template <typename T>
void loadData(string fn, vector<T> a)
{
    int value;
    ifstream Reader(fn);

    while (Reader >> value)
    {

        Reader >> value;

        a.push_back(value);
    }
}

int main()
{
    // vector<int> arr(10);
    // RandomArray(arr);
    // cout << "Before Sorting: " << endl;
    // print(arr);
    // heapSort(arr);
    // cout << "After Sorting: " << endl;
    // print(arr);
    // return 0;



    cout<< "Creating Random File"<<endl;
    //one GB
    CreateRandomFile("1GB.txt", 1024*500);
    // heap sort
    cout << "Heap Sort" << endl;
    vector<int> arr;
    loadData("1GB.txt", arr);
    clock_t start = clock();
    heapSort(arr);
    clock_t end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    arr.clear();
    // quick sort
    cout << "Quick Sort" << endl;
    loadData("1GB.txt", arr);
    start = clock();
    quickSort(arr, 0, arr.size() - 1);
    end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    // for n^2 algorithms file of two mb is created
    cout << "Creating Random File" << endl;
    CreateRandomFile("2MB.txt", 200);
    
    arr.clear();
    // bubble sort
    cout << "Bubble Sort" << endl;
    loadData("2MB.txt", arr);
    start = clock();
    bubbleSort(arr);
    end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    // selection sort
    arr.clear();
    cout << "Selection Sort" << endl;
    loadData("2MB.txt", arr);
    start = clock();
    selectionSort(arr);
    end = clock();
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    return 0;


}


// int main()
// {
//     priority_queue<int, vector<int>, compare> pq;
//     pq.push(10);
//     pq.push(20);
//     pq.push(30);
//     pq.push(40);
//     pq.push(50);
//     while (!pq.empty())
//     {
//         cout << pq.top() << " ";
//         pq.pop();
//     }

//     return 0;
// }