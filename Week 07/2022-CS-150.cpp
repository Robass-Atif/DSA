#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class doublyLinkedlist
{
public:
    class node
    {
    public:
        T data;
        node *next;
        node *pre;

        friend doublyLinkedlist;

        node(T val)
        {
            data = val;
            next = NULL;
            pre = NULL;
        }
    };
    class iterator
    {
    public:
        node *temp;

        iterator(node *head)
        {
            temp = head;
        }
        node *operator++(T)
        {
            return temp = temp->next;
        }
        bool operator==(iterator l)
        {
            return l.temp == temp;
        }
        bool operator!=(iterator l)
        {
            return l.temp != temp;
        }
        T operator*()
        {
            return temp->data;
        }
    };
    class reverse_iterator
    {
    public:
        node *temp;

        reverse_iterator(node *head)
        {
            temp = head;
        }
        node *operator++(T)
        {
            return temp = temp->next;
        }
        bool operator==(reverse_iterator l)
        {
            return l.temp == temp;
        }
        bool operator!=(reverse_iterator l)
        {
            return l.temp != temp;
        }
        T operator*()
        {
            return temp->data;
        }
    };
    class general_iterator
    {
    public:
        node *temp;

        general_iterator(node *head)
        {
            temp = head;
        }
        node *operator++(T)
        {
            return temp = temp->next;
        }
        bool operator==(general_iterator l)
        {
            return l.temp == temp;
        }
        bool operator!=(general_iterator l)
        {
            return l.temp != temp;
        }
        T operator*()
        {
            return temp->data;
        }
    };

general_iterator rbegin()
    {
        return general_iterator(head);
    }
    general_iterator rend()
    {
        return general_iterator(NULL);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(tail);
    }
    reverse_iterator rend()
    {
        return reverse_iterator(NULL);
    }

    iterator fbegin()
    {
        return iterator(head);
    }
    iterator fend()
    {
        return iterator(NULL);
    }

    node *head;
    node *tail;
    doublyLinkedlist()
    {

        head = NULL;
        tail = NULL;
    }
    bool isEmpty()
    {
        return head == NULL;
    }
    void insertAtTail(T val)
    {
        node *temp = new node(val);
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->pre = tail;
            tail = tail->next;
        }
    }
    void insertAtFront(T val)
    {
        node *temp = new node(val);
        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            temp->next = head;
            head->pre = temp;
            head = temp;
        }
    }
    void insertAtAfter(iterator temp1, T val)
    {
        if (temp1 == NULL || temp1.temp->next == NULL)
        {
            insertAtTail(val);
        }
        else
        {
            node *new_node = new node(val);
            new_node->next = temp1.temp->next;
            new_node->pre = temp1.temp;
            temp1.temp->next->pre = new_node;
            temp1.temp->next = new_node;
        }
    }

    void insertAtBefore(iterator temp1, T val)
    {
        if (temp1 == NULL || temp1.temp->pre == NULL)
        {
            insertAtFront(val);
        }
        else
        {
            node *new_node = new node(val);
            new_node->next = temp1.temp;
            new_node->pre = temp1.temp->pre;
            temp1.temp->pre->next = new_node;
            temp1.temp->pre = new_node;
        }
    }
    void splice(iterator curr, doublyLinkedlist &other)
    {
        if (curr.temp == NULL && head == NULL)
        {
            head = other.head;
            tail = other.tail;
        }
        else if (curr.temp == NULL && head != NULL)
        {
            tail->next = other.head;
            other.head->pre = tail;
            tail = other.tail;
        }
        else if (curr.temp != NULL && head != NULL)
        {
            curr.temp->next = other.head;
            other.head->pre = curr.temp;
            other.tail->next = curr.temp->next;
        }
    }
};

main()
{
    doublyLinkedlist<int> l;
    l.insertAtTail(2);
    l.insertAtFront(0);
    l.insertAtTail(3);
    l.insertAtAfter(l.fbegin(), 1);
    l.insertAtTail(4);

    for (doublyLinkedlist<int>::iterator i = l.fbegin(); i != l.fend(); i++)
    {
        cout << *i << endl;
    }

    doublyLinkedlist<int> l1;
    l1.insertAtTail(5);
    l1.insertAtTail(6);
    l1.insertAtTail(7);
    l1.insertAtTail(8);
    l1.insertAtTail(9);
    l1.insertAtTail(10);
    l.splice(l.fend(), l1);
    cout << "After Splice" << endl;
    for (doublyLinkedlist<int>::iterator i = l.fbegin(); i != l.fend(); i++)
    {
        cout << *i << endl;
    }
}
// leetcode first problem
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// class Solution
// {
// public:
//     ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
//     {
//         if (list1 == NULL)
//         {
//             return list2;
//         }
//         if (list2 == NULL)
//         {
//             return list1;
//         }
//         if (list1->val <= list2->val)
//         {
//             list1->next = mergeTwoLists(list1->next, list2);
//             return list1;
//         }
//         else
//         {
//             list2->next = mergeTwoLists(list1, list2->next);
//             return list2;
//         }
//     }
// };
// second problem
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// class Solution
// {
// public:
//     ListNode *removeNthFromEnd(ListNode *head, int n)
//     {
//         ListNode *temp = new ListNode(100);
//         temp->next = head;
//         ListNode *left = temp;
//         ListNode *right = temp;
//         for (int i = 1; i <= n + 1; i++)
//         {
//             right = right->next;
//         }
//         if (right == NULL)
//         {
//             return head->next;
//         }
//         while (right != NULL)
//         {

//             right = right->next;

//             left = left->next;
//         }
//         left->next = left->next->next;

//         return head;
//     }
// };

// // leetcode problem three
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
// class Solution
// {
// public:
//     ListNode *swapPairs(ListNode *head)
//     {
//         ListNode *temp = new ListNode(0);
//         temp->next = head;
//         swap(temp);
//         return temp->next;
//     }

//     void swap(ListNode *temp)
//     {
//         if (temp == NULL)
//         {
//             return;
//         }

//         ListNode *left = temp->next;
//         ListNode *right = NULL;
//         if (left != NULL)
//         {
//             right = left->next;
//         }

//         if (right != NULL)
//         {
//             ListNode *temporary = right->next;
//             right->next = left;
//             temp->next = right;
//             left->next = temporary;

//             swap(left);
//         }
//     }
// };
// // leetcode problem four
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
// class Solution
// {
// public:
//     ListNode *reverseBetween(ListNode *head, int left, int right)
//     {
//         ListNode *prev = NULL;
//         ListNode *curr = head;
//         for (int i = 1; i < left; i++)
//         {
//             prev = curr;
//             curr = curr->next;
//         }
//         ListNode *start = prev;
//         ListNode *end = curr;
//         for (int i = left; i <= right; i++)
//         {
//             ListNode *next = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = next;
//         }
//         if (start != NULL)
//         {
//             start->next = prev;
//         }
//         else
//         {
//             head = prev;
//         }
//         end->next = curr;
//         return head;
//     }
// };

// // leetcode problem five
// class node
// {
// public:
//     int val;
//     node *next;

//     node(int data)
//     {
//         this->val = data;
//         this->next = NULL;
//     }
// };

// class MyLinkedList
// {
// public:
//     node *head;
//     int size = 0;
//     MyLinkedList()
//     {
//         head = NULL;
//     }

//     int get(int index)
//     {
//         node *temp = head;
//         int i = 0;
//         while (temp != NULL && i < index)
//         {
//             temp = temp->next;
//             i++;
//         }
//         if (temp == NULL)
//             return -1;
//         return temp->val;
//     }

//     void addAtHead(int val)
//     {
//         node *newh = new node(val);
//         if (head == NULL)
//         {
//             head = newh;
//             size++;
//         }
//         else
//         {
//             newh->next = head;
//             head = newh;
//             size++;
//         }
//     }

//     void addAtTail(int val)
//     {
//         node *newt = new node(val);
//         if (head == NULL)
//         {
//             head = newt;
//             size++;
//         }
//         else
//         {
//             node *t = head;
//             while (t->next != NULL)
//             {
//                 t = t->next;
//             }
//             t->next = newt;
//         }
//     }

//     void addAtIndex(int index, int val)
//     {
//         node *newn = new node(val);
//         if (index == 0)
//         {
//             newn->next = head;
//             head = newn;
//         }
//         else
//         {
//             node *temp = head;
//             int i = 0;
//             while (temp != NULL && i < index - 1)
//             {
//                 temp = temp->next;
//                 i++;
//             }
//             if (temp == NULL)
//                 return;
//             if (temp != NULL && temp->next == NULL)
//             {
//                 temp->next = newn;
//             }
//             if (i == index - 1)
//             {
//                 node *t = temp->next;
//                 temp->next = newn;
//                 newn->next = t;
//             }
//         }
//     }

//     void deleteAtIndex(int index)
//     {
//         if (index == 0)
//         {
//             // Deleting at head
//             node *tmp = head;
//             head = head->next;
//             size--;
//             delete tmp;
//             return;
//         }

//         node *curr = head, *pre = nullptr;
//         while (curr && index > 0)
//         {
//             pre = curr;
//             curr = curr->next;
//             index--;
//         }

//         if (index == 0 && curr != nullptr)
//         {
//             node *tmp = curr;
//             pre->next = curr->next;
//             size--;
//             delete tmp;
//         }
//     }
// };

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */