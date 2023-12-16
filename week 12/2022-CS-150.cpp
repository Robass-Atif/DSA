<<<<<<< HEAD
#include <iostream>

using namespace std;

class AVLTree
{

public:
    class node
    {
    public:
        int data;
        node *left;
        node *right;

        node(int d)
        {
            data = d;
            left = NULL;
            right = NULL;
        }
    };
    node *root = NULL;

    // height
    int height(node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return height(root->left) + height(root->right) + 1;
    }

    // height difference
    int heightDifferece(node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        int x = height(temp->left);
        int y = height(temp->right);
        return x - y;
    }
    // height check
    bool isBalance(node *temp)
    {
        if (temp == NULL)
        {
            return true;
        }
        int x = height(temp->left);
        int y = height(temp->right);
        if (abs(x - y) <= 1)
        {
            return true;
        }
        return false;
    }
    

    // rr rotation
    node* rrRotation(node *temp)
    {
        node *p = temp->right;
        node *t = p->left;
        p->left = temp;
        temp->right = t;
        return p;
        
    }
    // lr rotation
    node* lrRotation(node *temp)
    {
        node *p = temp->left;
        node *t = p->right;
        p->right = temp;
        temp->left = t;
        return p;
    }
    // rl rotation
    node* rlRotation(node *temp)
    {
        node *p = temp->right;
        node *t = p->left;
        p->left = temp;
        temp->right = t;
        return p;
    }
    // ll rotation
    node* llRotation(node *temp)
    {
        node *p = temp->left;
        node *t = p->right;
        p->right = temp;
        temp->left = t;
        return p;
    }
    // insert function
    void insert(int d)
    {
        node *temp = root;
        root= insert(temp, d);
    }
    node* insert(node* temp,int d)
    {
        if (temp == NULL)
        {
            temp = new node(d);
            
            return temp;
        }
        if (d < temp->data)
        {
            temp->left = insert(temp->left, d);
        }
        else if (d > temp->data)
        {
            temp->right = insert(temp->right, d);
        }
        else    // if data is already present
        {
            return temp;
        }
        if (!isBalance(temp))
        {
            if (heightDifferece(temp) > 1)
            {
                if (heightDifferece(temp->left) > 0)
                {

                    // ll rotation
                    temp = llRotation(temp);

                }
                else
                {
                    // lr rotation
                    temp = lrRotation(temp);
                }
            }
            else
            {
                if (heightDifferece(temp->right) > 0)
                {
                    // rl rotation
                    temp = rlRotation(temp);
                }
                else
                {
                    // rr rotation
                    temp = rrRotation(temp);
                }
            }
        }
        return temp;
    }
    
    // delete from avl
    void deleteNode(int d)
    {
        node *temp = root;
       root= deleteNode(temp, d);
    }
    node* deleteNode(node* temp,int d)
    {
        if (temp == NULL)
        {
            return temp;
        }
        if (d < temp->data)
        {
            temp->left = deleteNode(temp->left, d);
        }
        else if (d > temp->data)
        {
            temp->right = deleteNode(temp->right, d);
        }
        else
        {
            if (temp->left == NULL)
            {
                node *t = temp->right;
                delete temp;
                return t;
            }
            else if (temp->right == NULL)
            {
                node *t = temp->left;
                delete temp;
                return t;
            }
            else
            {
                node *t = temp->right;
                while (t->left != NULL)
                {
                    t = t->left;
                }
                temp->data = t->data;
                temp->right = deleteNode(temp->right, t->data);
            }
        }
        if (!isBalance(temp))
        {
            if (heightDifferece(temp) > 1)
            {
                if (heightDifferece(temp->left) > 0)
                {

                    // ll rotation
                    temp = llRotation(temp);

                }
                else
                {
                    // lr rotation
                    temp = lrRotation(temp);
                }
            }
            else
            {
                if (heightDifferece(temp->right) > 0)
                {
                    // rl rotation
                    temp = rlRotation(temp);
                }
                else
                {
                    // rr rotation
                    temp = rrRotation(temp);
                }
            }
        }
        return temp;
    }
        // print avl
    void print()
    {
        node *temp = root;
        print(temp);
    }
    void print(node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        print(temp->left);
        cout << temp->data << " ";
        print(temp->right);
    }

};
int main()
{
    
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    avl.insert(5);
    avl.insert(15);

    
    avl.print(); 
    cout<<endl;
    cout<<"After deleting 30"<<endl;
    avl.deleteNode(30);
    avl.print();
    cout<<endl;


    return 0;
}
// problem 1
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// class Solution {
// public:
//     bool isBalanced(TreeNode* root) {
//         if(!root) return true;
//         int x=height(root->left);
//         int y=height(root->right);
//         int bal=x-y;
//         if(bal>1 || bal<-1)
//         {
//            return false;
//         }
//         if(!isBalanced(root->left) || !isBalanced(root->right))
//         {
//             return false;
//         }
//         return true;
        
//     }
//     int height(TreeNode* root)
//     {
//         if(!root)
//         {
//             return 0;
//         }
//         return 1+max(height(root->left),height(root->right));
//     }
// };


//problem 2

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// class Solution {
//     void inorderArray(TreeNode* &root,vector<int> &inorder){
//         if(root==NULL)
//         {
//              return ;
//         }
//         inorderArray(root->left,inorder);
//         inorder.push_back(root->val);
//         inorderArray(root->right,inorder);
//     }
//     TreeNode* constructTree(vector<int>& inorder,int start,int end){
//     if(start>end)
//     {
//         return NULL;
//     }
//     int mid=start+(end-start)/2;
//     int ele=inorder[mid];
//     TreeNode* root=new TreeNode(ele);
//     root->left=constructTree(inorder,start,mid-1);
//     root->right=constructTree(inorder,mid+1,end);
//         return root;
//     }
    
// public:
//     TreeNode* balanceBST(TreeNode* root) {
//         vector<int> inorder;
//         inorderArray(root,inorder);
//         return constructTree(inorder,0,inorder.size()-1);
//     }
// };

=======
#include <iostream>

using namespace std;

class AVLTree
{

public:
    class node
    {
    public:
        int data;
        node *left;
        node *right;

        node(int d)
        {
            data = d;
            left = NULL;
            right = NULL;
        }
    };
    node *root = NULL;

    // height
    int height(node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        return height(root->left) + height(root->right) + 1;
    }

    // height difference
    int heightDifferece(node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        int x = height(temp->left);
        int y = height(temp->right);
        return x - y;
    }
    // height check
    bool isBalance(node *temp)
    {
        if (temp == NULL)
        {
            return true;
        }
        int x = height(temp->left);
        int y = height(temp->right);
        if (abs(x - y) <= 1)
        {
            return true;
        }
        return false;
    }
    

    // rr rotation
    node* rrRotation(node *temp)
    {
        node *p = temp->right;
        node *t = p->left;
        p->left = temp;
        temp->right = t;
        return p;
        
    }
    // lr rotation
    node* lrRotation(node *temp)
    {
        node *p = temp->left;
        node *t = p->right;
        p->right = temp;
        temp->left = t;
        return p;
    }
    // rl rotation
    node* rlRotation(node *temp)
    {
        node *p = temp->right;
        node *t = p->left;
        p->left = temp;
        temp->right = t;
        return p;
    }
    // ll rotation
    node* llRotation(node *temp)
    {
        node *p = temp->left;
        node *t = p->right;
        p->right = temp;
        temp->left = t;
        return p;
    }
    // insert function
    void insert(int d)
    {
        node *temp = root;
        root= insert(temp, d);
    }
    node* insert(node* temp,int d)
    {
        if (temp == NULL)
        {
            temp = new node(d);
            
            return temp;
        }
        if (d < temp->data)
        {
            temp->left = insert(temp->left, d);
        }
        else if (d > temp->data)
        {
            temp->right = insert(temp->right, d);
        }
        else    // if data is already present
        {
            return temp;
        }
        if (!isBalance(temp))
        {
            if (heightDifferece(temp) > 1)
            {
                if (heightDifferece(temp->left) > 0)
                {

                    // ll rotation
                    temp = llRotation(temp);

                }
                else
                {
                    // lr rotation
                    temp = lrRotation(temp);
                }
            }
            else
            {
                if (heightDifferece(temp->right) > 0)
                {
                    // rl rotation
                    temp = rlRotation(temp);
                }
                else
                {
                    // rr rotation
                    temp = rrRotation(temp);
                }
            }
        }
        return temp;
    }
    
    // delete from avl
    void deleteNode(int d)
    {
        node *temp = root;
       root= deleteNode(temp, d);
    }
    node* deleteNode(node* temp,int d)
    {
        if (temp == NULL)
        {
            return temp;
        }
        if (d < temp->data)
        {
            temp->left = deleteNode(temp->left, d);
        }
        else if (d > temp->data)
        {
            temp->right = deleteNode(temp->right, d);
        }
        else
        {
            if (temp->left == NULL)
            {
                node *t = temp->right;
                delete temp;
                return t;
            }
            else if (temp->right == NULL)
            {
                node *t = temp->left;
                delete temp;
                return t;
            }
            else
            {
                node *t = temp->right;
                while (t->left != NULL)
                {
                    t = t->left;
                }
                temp->data = t->data;
                temp->right = deleteNode(temp->right, t->data);
            }
        }
        if (!isBalance(temp))
        {
            if (heightDifferece(temp) > 1)
            {
                if (heightDifferece(temp->left) > 0)
                {

                    // ll rotation
                    temp = llRotation(temp);

                }
                else
                {
                    // lr rotation
                    temp = lrRotation(temp);
                }
            }
            else
            {
                if (heightDifferece(temp->right) > 0)
                {
                    // rl rotation
                    temp = rlRotation(temp);
                }
                else
                {
                    // rr rotation
                    temp = rrRotation(temp);
                }
            }
        }
        return temp;
    }
        // print avl
    void print()
    {
        node *temp = root;
        print(temp);
    }
    void print(node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        print(temp->left);
        cout << temp->data << " ";
        print(temp->right);
    }

};
int main()
{
    
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    avl.insert(5);
    avl.insert(15);

    
    avl.print(); 
    cout<<endl;
    cout<<"After deleting 30"<<endl;
    avl.deleteNode(30);
    avl.print();
    cout<<endl;


    return 0;
}
// problem 1
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// class Solution {
// public:
//     bool isBalanced(TreeNode* root) {
//         if(!root) return true;
//         int x=height(root->left);
//         int y=height(root->right);
//         int bal=x-y;
//         if(bal>1 || bal<-1)
//         {
//            return false;
//         }
//         if(!isBalanced(root->left) || !isBalanced(root->right))
//         {
//             return false;
//         }
//         return true;
        
//     }
//     int height(TreeNode* root)
//     {
//         if(!root)
//         {
//             return 0;
//         }
//         return 1+max(height(root->left),height(root->right));
//     }
// };


//problem 2

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// class Solution {
//     void inorderArray(TreeNode* &root,vector<int> &inorder){
//         if(root==NULL)
//         {
//              return ;
//         }
//         inorderArray(root->left,inorder);
//         inorder.push_back(root->val);
//         inorderArray(root->right,inorder);
//     }
//     TreeNode* constructTree(vector<int>& inorder,int start,int end){
//     if(start>end)
//     {
//         return NULL;
//     }
//     int mid=start+(end-start)/2;
//     int ele=inorder[mid];
//     TreeNode* root=new TreeNode(ele);
//     root->left=constructTree(inorder,start,mid-1);
//     root->right=constructTree(inorder,mid+1,end);
//         return root;
//     }
    
// public:
//     TreeNode* balanceBST(TreeNode* root) {
//         vector<int> inorder;
//         inorderArray(root,inorder);
//         return constructTree(inorder,0,inorder.size()-1);
//     }
// };

>>>>>>> 8aa07efba4f79221f542f6be7867d4db0792810d
