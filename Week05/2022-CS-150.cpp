#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <stack>
using namespace std;

// first
int sum(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n + sum(n - 1);
}
// second
int sumofOdd(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n + sumofOdd(n - 2);
}
// third
int sumofGM(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return pow(2, n) + sumofGM(n - 1);
}
// fourth
int sumofGM3(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return pow(3, n) + sumofGM3(n - 1);
}
// fiveth
int sumofGP(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n + sumofGP(n / 3);
}
// sixth
int sumofGP2(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n + sumofGP(n / 2);
}
// Q:2 (1)
string decimalTOBinary(int n)
{
    if (n == 0)
    {
        return "";
    }
    return decimalTOBinary(n / 2) + (n % 2 == 0 ? "0" : "1");
}
// Q:2 (2)
string itoa(int n)
{
    if (n == 0)
    {
        return "";
    }
    return itoa(n / 10) + to_string(n % 10);
}
// Q:2 (3)
int gcd(int a, int b)
{
    if (a % b == 0)
    {
        return b;
    }
    return gcd(b, a % b);
}
// Q:3(1)
int searchFirstEntry(int arr[], int start, int end, int target)
{
    int mid = start + (end - start) / 2;
    if (target == arr[mid])
    {
        if (mid == 0)
            return mid;
    }
    else if (arr[mid] > target)
    {
        searchFirstEntry(arr, start, mid - 1, target);
    }
    else
    {
        searchFirstEntry(arr, mid + 1, end, target);
    }
    return -1;
}

// Q:3(2)

int searchLastEntry(int arr[], int start, int end, int target)
{
    int mid = start + (end - start) / 2;
    if (target == arr[mid])
    {
        // if (mid == sizeof(arr) / sizeof(arr[0]) - 1)
        return mid;
    }
    else if (arr[mid] > target)
    {
        searchLastEntry(arr, start, mid - 1, target);
    }
    else
    {
        searchLastEntry(arr, mid + 1, end, target);
    }
    return -1;
}

// Q:3 (3)
int binarysearch(int arr[], int start, int end, int target)
{
    int mid = start + (end - start) / 2;
    if (target == arr[mid])
    {
        return mid;
    }
    else if (arr[mid] > target)
    {
        binarysearch(arr, start, mid - 1, target);
    }
    else
    {
        binarysearch(arr, mid + 1, end, target);
    }
    return -1;
}
// Q3 :(1)
int powerMod2(int x, int y, int m)
{
    if (y == 0)
    {

        return 1;
    }

    int result = (x * powerMod2(x, y - 1, m)) % m;

    return result;
}
// Q:3 :(2)
int powerMod(int x, int y, int m)
{
    if (y == 0)
    {
        return 1;
    }
    else if (y % 2 == 0)
    {
        return powerMod((x * x), y / 2, m);
    }
    else
    {
        return (x * powerMod(x, y - 1, m)) % m;
    }
}
// probelm 1
int divideBY(int a, int b)
{
    if (a - b <= 0)
    {
        return 1;
    }
    return (divideBY(a - b, b) + 1);
}
// time O(log(n))^2
int divideBY2(int a, int b)
{
    if (a - b <= 0)
    {
        return 0;
    }
    int temp = b;
    int count = 1;
    while (a >= (temp * 2))
    {
        temp = temp * 2;
        count = count * 2;
    }

    return count + divideBY2(a - temp, b);
}
// problem 2
int reminder(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return reminder(a - b, b);
}

// time O(log(n))^2
int reminder2(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    int temp = b;
    while (a >= (temp * 2))
    {
        temp = temp * 2;
    }
    return reminder2(a - temp, b);
}

// fib
int iterativeFibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }

    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++)
    {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
// recursive
int recursiveFibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
    }
}
// Memorizaion

int fib(int n, int arr[])
{
    if (arr[n] != -1)
    {
        return arr[n];
    }
    else
    {
        arr[n] = fib(n - 2, arr) + fib(n - 1, arr);
        return arr[n];
    }
}
int fibFast(int n)
{
    int arr[n + 1] ;

    for(int i=0;i<n+1;i++)
    {
        arr[i]=-1;
    }
    arr[0] = 0;
    arr[1] = 1;
    arr[2]=1;
    return fib(n, arr);
}

// bottom up approach
int fibonacci_bottom_up(int n)
{

    int arr[n + 1];

    arr[0] = 0;
    arr[1] = 1;
    arr[2]=1;

    for (int i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    return arr[n];
}

// tri sum bottom up approach

int fibonacciTriSum(int n)
{

    int arr[n + 1];

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    for (int i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2] + arr[i - 3];
    }

    return arr[n];
}

// Memorizaion tri sum

int fib3(int n, int arr[])
{
    if (arr[n] != -1)
    {
        return arr[n];
    }
    else
    {
        arr[n] = fib3(n - 2, arr) + fib3(n - 1, arr) + fib3(n - 3, arr);
        return arr[n];
    }
}

int fibTri(int n)
{
    int size= n+1;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = -1;
    }
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    return fib3(n, arr);
}
// chalenge 1
void generateSubarrays(vector<int> &arr, int start, int end)
{
    if (start > end)
    {
        return;
    }

    for (int i = start; i <= end; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    generateSubarrays(arr, start, end - 1);
    generateSubarrays(arr, start + 1, end);
}

// Challenge 2
void insertSorted(stack<int> &s, int element)
{
    if (s.empty() || element > s.top())
    {
        s.push(element);
    }
    else
    {
        int topElement = s.top();
        s.pop();
        insertSorted(s, element);
        s.push(topElement);
    }
}
void sortStack(stack<int> &s)
{
    if (!s.empty())
    {
        int topElement = s.top();
        s.pop();
        sortStack(s);
        insertSorted(s, topElement);
    }
}
// Q:5 (2)
int add(int x, int y)
{
    return x + y;
}
int Mul(int x, int y)
{

    if (y == 0)
    {
        return 0;
    }
    return add(x, Mul(x, y - 1));
}

// Q : 5(2)
int Mul2(int x, int y)
{
    if (y == 0)
    {
        return 0;
    }
    if (y % 2 == 0)
    {
        return Mul2(x, y / 2) + Mul2(x, y / 2);
    }
    else
    {
        return x + Mul2(x, y / 2) + Mul2(x, y / 2);
    }
}

// Memorization
vector<int> memo(  1, -1);

int Mul3(int x, int y) {
    if (y == 0) {
        return 0;
    }

    // Check if the result is already memoized
    if (memo[y] != -1) {
        return memo[y];
    }

    int result = x + Mul3(x, y - 1);

    // Memoize the result
    memo[y] = result;

    return result;
}


int main(int argc, char const *argv[])
{
    cout<<sum(5)<<endl;
    cout<<sumofOdd(5)<<endl;
    cout<<sumofGM(5)<<endl;
    cout<<sumofGM3(5)<<endl;
    cout<<sumofGP(5)<<endl;
    
    cout<<decimalTOBinary(5)<<endl;
    cout<<itoa(5)<<endl;
    cout<<gcd(5,5)<<endl;
    cout<<Mul(5,5)<<endl;
    cout<<Mul2(5,5)<<endl;
    cout<<fibonacci_bottom_up(15)<<endl;
    cout<<fibFast(15)<<endl;
    cout<<fibTri(15)<<endl;
    cout<<iterativeFibonacci(15)<<endl;
    cout<<recursiveFibonacci(15)<<endl;
    
    
    return 0;
}
