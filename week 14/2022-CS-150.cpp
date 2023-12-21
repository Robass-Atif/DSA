#include <iostream>
#include <list>

using namespace std;

// Implement the chaining method.
// In this method, you will handle collisions by making a list corresponding to every
// index of the hash table.
    list<int> hashTable[10];

// insert elements in the chained hash table
void hashingChaining(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int index = arr[i] % 10;
        hashTable[index].push_back(arr[i]);
    }
}
// search for an element in the chained hash table
bool searchChaining(int key)
{
    int index = key % 10;
    for(auto x : hashTable[index])
    {
        if(x == key)
        {
            return true;
        }
        

    }
    return false;
}
// array of linear probing hash table
    int Linear[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

// linear probing method for inserting elements in the hash table
void hashingLinearProbing(int arr[], int n)
{
    
    for(int i = 0; i < n; i++)
    {
        int index = arr[i] % 10;
        if(Linear[index] == -1)
        {
            Linear[index] = arr[i];
        }
        else
        {
            int j = 1;
            while(Linear[(index + j) % 10] != -1)
            {
                j++;
                if(j == 10)
                {
                    break;
                }
            }
            Linear[(index + j) % 10] = arr[i];
        }
    }
    
}
// search for an element in the linear probing hash table
bool searchLinearProbing(int key)
{
    int index = key % 10;
    if(Linear[index] == key)
    {
        return true;
    }
    else
    {
        int j = 1;
        while(Linear[(index + j) % 10] != key && Linear[(index + j) % 10] != -1)
        {
            j++;
            if(j == 10)
            {
                break;
            }
        }
        if(Linear[(index + j) % 10] == key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
}
// array of quardratic probing hash table
    int Quadratic[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
// quardratic probing method for inserting elements in the hash table
void hashingQuadraticProbing(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int index = arr[i] % 10;
        if(Quadratic[index] == -1)
        {
            Quadratic[index] = arr[i];
        }
        else
        {
            int j = 1;
            while(Quadratic[(index + j*j) % 10] != -1)
            {
                j++;
                if(j*j >= 10)
                {
                    break;
                }
            }
            Quadratic[(index + j*j) % 10] = arr[i];
        }
    }

}
// search for an element in the quardratic probing hash table
bool searchQuadraticProbing(int key)
{
    int index = key % 10;
    if(Quadratic[index] == key)
    {
        return true;
    }
    else
    {
        int j = 1;
        while(Quadratic[(index + j*j) % 10] != key && Quadratic[(index + j*j) % 10] != -1)
        {
            j++;
            if(j*j >= 10)
            {
                break;
            }
        }
        if(Quadratic[(index + j*j) % 10] == key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
}


int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    
   hashingQuadraticProbing(arr, 7);
    
   cout<<searchQuadraticProbing(1)<<endl;




    return 0;
}
// leetcode problem 1

// class Solution {
// public:
//     vector<string> findRepeatedDnaSequences(string s) {

//         string curr="";
//         vector<string> res;
//         unordered_map<string, int> m;
        
//         for(int i=0; i+10<=s.size(); i++)
//         {
        
//             curr=s.substr(i, 10);
            
//             if(m.find(curr)==m.end())
//                 m.insert({curr, 0});
            
//             else if(!m[curr])
//             {
                
//                 res.push_back(curr);
              
//                 m[curr]++;
//             }
//         }

//         return res;
//     }
// };
// leetcode problem 2
// class Solution {
// public:
//     vector<vector<string>> groupAnagrams(vector<string>& v) {
//         int m=v.size();
        
//         map<map<char,int>,vector<string>> bm;
        
//         for(int i=0;i<m;i++){
//             map<char,int> sm;
            
//             string s=v[i];
//             int n=s.length();
            
//             for(int i=0;i<n;i++){
//                 char ch=s[i];
//                 sm[ch]++;
//             }
            
//             vector<string> cur;
//             if(bm.find(sm)!=bm.end()) cur=bm[sm];
//             cur.push_back(s);
            
//             bm[sm]=cur;
//         }
        
//         vector<vector<string>> ans;
            
//         for(auto it=bm.begin();it!=bm.end();it++){
//             vector<string> cur=it->second;
            
//             ans.push_back(cur);
//         }
        
//         return ans;
//     }
// };