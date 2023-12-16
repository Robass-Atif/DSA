#include<iostream>
using namespace std;

int binarySearch(int arr[],int size,int target)
{
    int left=0;
    int right=size;
    
    while(left<=right)
    {
    int mid=(right+left)/2;

        if(target==arr[mid])
        {
            return mid; 
        }
        else if(target<=arr[mid])
        {
            left=left;
            right=mid-1;

        }
        else
        {
            left=mid+1;
            right=right;
        }
    }
        return -1;
    
}
int main(int argc, char const *argv[])
{
    int arr[5]={1,2,34,5,6};
  int result=  binarySearch(arr,5,1);
  cout<<"the result is: "<<result;
      return 0;
}



