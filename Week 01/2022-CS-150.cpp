#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>


using namespace std;
template <typename T>

// ##############  auto grow list code ##################################

class AutoGrowingArray
{
private:
    int size = 0;
    int capacity = 1;
    int *DA;

public:
    AutoGrowingArray()
    {
        DA = new T[capacity];
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << DA[i] << endl;
        }
    }
    friend ostream &operator<<(ostream &out, AutoGrowingArray<T> &a)
    {
        for (int i = 0; i < a.size; i++)
        {
            out << a[i] << endl;
        }
        return out;
    }

    T &operator[](int index)

    {
        return DA[index];
    }
    T operator()(int index)
        const
    {
        return DA[index];
    }

    void pushBack(T value)
    {
        if (size == capacity)
        {
            capacity++;
            int *HA = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                HA[i] = DA[i];
            }
            delete[] DA;
            DA = HA;
        }
        DA[size] = value;
        size++;
    }
};

// ######################## code end   ###############################################
template <typename T>

// #####################  Vector code  ###############################################
class Vector
{
private:
    int size = 0;
    int capacity = 1;
    int *DA;

public:
    Vector()
    {
        DA = new T[capacity];
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << DA[i] << endl;
        }
    }
    friend ostream &operator<<(ostream &out, Vector<T> &a)
    {
        for (int i = 0; i < a.size; i++)
        {
            out << a[i] << endl;
        }
        return out;
    }

    T &operator[](int index)

    {
        return DA[index];
    }
    T operator()(int index)
        const
    {
        return DA[index];
    }

    void pushBack(T value)
    {
        if (size == capacity)
        {
            capacity = capacity * 2;
            int *HA = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                HA[i] = DA[i];
            }
            delete[] DA;
            DA = HA;
        }
        DA[size] = value;
        size++;
    }
    ~Vector()
    {

        if (DA != nullptr)
        {
            delete[] DA;
        }
    }
};

// ######################## code end   ###############################################

template <typename T>

//   #######################  ArrayList Code ###########################################
class ArrayList
{
private:
    int size = 0;
    int capacity = 2;
    int *DA;

public:
    ArrayList()
    {
        DA = new T[capacity];
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << DA[i] << endl;
        }
    }
    friend ostream &operator<<(ostream &out, ArrayList<T> &a)
    {
        for (int i = 0; i < a.size; i++)
        {
            out << a[i] << endl;
        }
        return out;
    }

    T &operator[](int index)

    {
        return DA[index];
    }
    T operator()(int index)
        const
    {
        return DA[index];
    }

    void pushBack(T value)
    {
        if (size == capacity)
        {
            capacity = capacity * 1.5;
            int *HA = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                HA[i] = DA[i];
            }
            delete[] DA;
            DA = HA;
        }
        DA[size] = value;
        size++;
    }
    ~ArrayList()
    {
        if (DA != nullptr)
        {
            delete[] DA;
        }
    }
};

// ######################## code end   ###############################################

//  write file code

void CreateRandomFile(string fn, int size, int Rn = 100)
{
    srand(time(0));
    ofstream Writer(fn);
    for (int i = 0; i < size * 1024 * 1024; i++)
    {
        Writer << rand() % Rn << " ";
    }
}
template <typename T>
void loadData(string fn, AutoGrowingArray<T> a)
{
    int value;
    ifstream Reader(fn);

    while (Reader >> value)
    {

        Reader >> value;

        a.pushBack(value);
    }
}
template <typename T>
void loadData(string fn, Vector<T> a)
{
    int value;
    ifstream Reader(fn);

    while (Reader >> value)
    {

        Reader >> value;

        a.pushBack(value);
    }
}
template <typename T>
void loadData(string fn, ArrayList<T> a)
{
    int value;
    ifstream Reader(fn);

    while (Reader >> value)
    {

        Reader >> value;

        a.pushBack(value);
    }
}
main()
{

    Vector<int> b;
    AutoGrowingArray<int> c;

    ArrayList<int> a;

    cout << "List Loading" << endl
         << endl;
    cout << "before loading : ";
    CreateRandomFile("dsa.txt", 1, 100);
    cout << time(0) << endl;

    cout << "After Loading : ";
    loadData("dsa.txt", a);
    cout << time(0);

    // cout << "Vector Loading" << endl
    //      << endl;
    // cout << "before loading : ";
    // CreateRandomFile("dsa.txt", 1, 100);
    // cout << time(0) << endl;

    // cout << "After Loading : ";
    // loadData("dsa.txt", a);
    // cout << time(0);

    // cout << "simple Loading" << endl
    //      << endl;
    // cout << "before loading : ";
    // CreateRandomFile("dsa.txt", 1, 100);
    // cout << time(0) << endl;

    // cout << "After Loading : ";
    // loadData("dsa.txt", a);
    // cout << time(0);
}
