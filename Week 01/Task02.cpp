#include<iostream>
using namespace std;
template<typename T>
class Vector
{
    private:
    int size=0;
    int capacity=1;
    int* DA;
    public:
    Vector()
    {
        DA=new T[capacity];
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout<<DA[i]<<endl;
        }
        
    }
    friend ostream& operator<<(ostream& out,Vector<T>& a )
    {
        for (int i = 0; i <a.size; i++)
        {
            out<<a[i]<<endl;
        }
        return out;
        
    }

    T& operator[](int index)
    
    {
        return DA[index];
    }
    T operator()(int index)
    const
    {
        return DA[index];
    }
    


        void pushBack( T value)
    {
        if(size==capacity)
        {
            capacity=capacity*2;
            int* HA=new T[capacity];
            for(int i=0;i<size;i++)
            {
                HA[i]=DA[i];
            }
            delete[] DA;
            DA=HA;
        }
        DA[size]=value;
        size++;
    }
    ~Vector()
    {
     
        
  
  if (DA != nullptr) {
    delete[] DA;
  }




    }
};



main()
{

Vector<int> v;
v.pushBack(3);
v.pushBack(6);
v.pushBack(23);
cout<<v;
}



