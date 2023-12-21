#include <iostream>
using namespace std;
// binary search tree class
template <class T = int>
class BST
{
public:
    class node
    {

    public:
        T data;
        node *left;
        node *right;
        node(T value)
        {
            data = value;
            left = NULL;
            right = NULL;
        }
    };
    node *root;
    BST()
    {
        root = NULL;
    }
    // insert function
    void insertBST(T v1)
    {
        if (root == NULL)
        {
            root = new node(v1);
            return;
        }
        node *temp = root;
        while (temp != NULL)
        {
            if (v1 < temp->data)
            {
                if (temp->left == NULL)
                {
                    temp->left = new node(v1);
                    return;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = new node(v1);
                    return;
                }
                temp = temp->right;
            }
        }
    }
    // search function
    bool search(T v1)
    {
        node *temp = root;
        return search(temp, v1);
    }
    bool search(node *temp, T v1)
    {
        if (temp == NULL)
        {
            return false;
        }
        if (temp->data == v1)
        {
            return true;
        }
        else if (v1 < temp->data)
        {
            return search(temp->left, v1);
        }
        else
        {
            return search(temp->right, v1);
        }
    }
    // height function
    int height()
    {
        node *temp = root;
        return height(temp);
    }
    int height(node *temp)
    {
        if (temp == NULL)
        {
            return -1;
        }
        int left = height(temp->left);
        int right = height(temp->right);
        if (left > right)
        {
            return left + 1;
        }
        else
        {
            return right + 1;
        }
    }
    // count function
    int count()
    {
        node *temp = root;
        return count(temp);
    }
    int count(node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        int left = count(temp->left);
        int right = count(temp->right);
        return left + right + 1;
    }
    // start function
    node *start()
    {
        return root;
    }
    // end function
    node *end()
    {
        node *temp = root;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }

    // recursive print function
    // inorder function
    void inorder()
    {
        node *temp = root;
        inorder(temp);
    }
    void inorder(node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }
    // preorder function
    void preorder()
    {
        node *temp = root;
        preorder(temp);
    }
    void preorder(node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        cout << temp->data << " ";
        preorder(temp->left);
        preorder(temp->right);
    }
    // postorder function
    void postorder()
    {
        node *temp = root;
        postorder(temp);
    }
    void postorder(node *temp)
    {
        if (temp == NULL)
        {
            return;
        }
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << " ";
    }

    // internal node count function
    int internalNodeCount()
    {
        node *temp = root;
        return internalNodeCount(temp);
    }
    int internalNodeCount(node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        int x = internalNodeCount(temp->left);
        int y = internalNodeCount(temp->right);
        if (temp->left != NULL ^ temp->right != NULL)
        {
            return x + y + 1;
        }
        else
        {
            return x + y;
        }
    }
    // leaves node
    int leavesNode()
    {
        node *temp = root;
        return leavesNode(temp);
    }
    int leavesNode(node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        int x = leavesNode(temp->left);
        int y = leavesNode(temp->right);
        if (temp->left == NULL && temp->right == NULL)
        {
            return x + y + 1;
        }
        else
        {
            return x + y;
        }
    }
    // even count function in tree
    int evenCount()
    {
        node *temp = root;
        return evenCount(temp);
    }
    int evenCount(node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        int x = evenCount(temp->left);
        int y = evenCount(temp->right);
        if (temp->data % 2 == 0)
        {
            return x + y + 1;
        }
        else
        {
            return x + y;
        }
    }
    // idential trees function and their values

    bool identicalBTree(node *temp1, node *temp2)
    {

        if (temp1 != NULL && temp2 != NULL)
        {
            return false;
        }

        if (temp1->data != temp2->data)
        {
            return false;
        }
        bool x = identicalBTree(temp1->left, temp2->left);
        bool y = identicalBTree(temp1->right, temp2->right);
        if (x == true && y == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
// binary tree class of random
template <class T = int>
class RBinary
{
public:
    class node
    {

    public:
        T data;
        node *left;
        node *right;
        node(T value)
        {
            data = value;
            left = NULL;
            right = NULL;
        }
    };
    node *root;
    BST()
    {
        root = NULL;
    }
    // randomly insert by using random function
    void insertRandom(T v1)
    {
        node *temp = root;
       insertRandom(temp, v1);
    }
    void insertRandom(node* temp,T v1)
    {
        if(node==NULL)
        {
            node*temp=new node(v1);
            return;
        }
        int x=rand()%2;
        if(x==0)
        {
            insertRandom(temp->left,v1);
        }
        else
        {
            insertRandom(temp->right,v1);
        }
    }
// output tree function
void outputTree(node* root, int level)
{
    if (root == NULL)
        return;

    outputTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        cout << "   ";

    cout << root->data << endl;

    outputTree(root->left, level + 1);
}
    
};
// binary search tree sort function using insertion
void BSTSort(int arr[], int n)
{
    BST<> b;
    for (int i = 0; i < n; i++)
    {
        b.insertBST(arr[i]);
    }
    b.inorder();
}




// main function
int main()
{
    BST<> b;
    b.insertBST(10);
    b.insertBST(5);
    b.insertBST(15);
    b.insertBST(3);
    b.insertBST(7);
    b.insertBST(12);
    b.insertBST(17);
    return 0;
}
// leetcode problem
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
//     TreeNode* insertIntoBST(TreeNode* root, int val) {
//        if(root==NULL)
//         {
//             root = new TreeNode(val);
//             return root;
//         }
//         TreeNode *temp = root;
//         while(temp!=NULL)
//         {
//             if(val<temp->val)
//             {
//                 if(temp->left==NULL)
//                 {
//                     temp->left = new TreeNode(val);
//                     break;
//                 }
//                 temp = temp->left;
//             }
//             else
//             {
//                 if(temp->right==NULL)
//                 {
//                     temp->right = new TreeNode(val);
//                     break;
//                 }
//                 temp = temp->right;
//             }
//         }
//         return root;

//     }
// };

// problem 2
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
//     vector<int> inorderTraversal(TreeNode* root) {

//         vector<int> result;
//          inorder(root,result);
//         return result;
//     }
//     void inorder(TreeNode* root,vector<int> &result)
//     {
//         if(root!=NULL)
//         {
//             inorder(root->left,result);
//             result.push_back(root->val);
//             inorder(root->right,result);

//         }
//     }
// };

//  problem 3
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
//     vector<int> postorderTraversal(TreeNode* root) {
//         vector<int> result;
//         Post(root,result);
//         return result;

//     }

//     void Post(TreeNode* root,vector<int> &result )
//     {
//         if(root==NULL)
//         {
//             return;
//         }
//         Post(root->left,result);
//         Post(root->right,result);
//         result.push_back(root->val);
//     }
// };

// problem 3
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
//     vector<int> preorderTraversal(TreeNode* root) {

//         vector<int> result;
//         pre(root,result);
//         return result;

//     }
//     void pre(TreeNode* root,vector<int> &result)
//     {
//         if(!root)
//         {
//             return;
//         }
//      result.push_back(root->val);

//         pre(root->left,result);

//         pre(root->right,result);

//     }
// };
//
// problem 4
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
//     vector<vector<int>> levelOrder(TreeNode* root) {
//         vector<vector<int>> result;
//         traversal(result, root, 1);
//         return result;
//     }
//     void traversal(vector<vector<int>>& result, TreeNode* root, int level) {
//         if (!root) {
//             return;
//         }
//         if (result.size() < level) {
//             result.push_back(vector<int>());
//         }
//         result[level - 1].push_back(root->val);
//         traversal(result, root->left, level + 1);
//         traversal(result, root->right, level + 1);
//     }
// };
