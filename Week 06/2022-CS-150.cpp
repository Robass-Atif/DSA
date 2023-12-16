#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class node
{
public:
    T data;
    node *next;

    node(int val)
    {
        data = val;
        next = NULL;
    }
};

template <typename T>
class Linkedlist
{
    node<T> *head;
    node<T> *tail;
    int size;

public:
    // Constructor
    Linkedlist()
    {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    // Insert At Front
    void insertAtFront(T val)
    {
        node<T> *new_node = new node<T>(val);
        new_node->next = head;
        head = new_node;
        size++;
    }
    // insert At End
    void insertAtEnd(T val)
    {
        node<T> *new_node = new node<T>(val);
        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
            size++;
        }
        else
        {
            size++;
            tail->next = new_node;
            tail = new_node;
        }
    }
    // Insert at middle
    void insertAtMiddle(T val)
    {
        node<T> *new_node = new node<T>(val);
        int count = size / 2;
        node<T> *temp = head;
        while (count != 0)
        {
            temp = temp->next;
            count--;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    // insert Before
    void insertBefore(T val, T key)
    {
        node<T> *new_node = new node<T>(key);
        node<T> *temp = head;
        while (temp->data == val)
        {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    // insert After at specific value
    void insertAfter(T val, T key)
    {
        node<T> *new_node = new node<T>(key);
        node<T> *temp = head;
        while (temp->data == val)
        {
            temp = temp->next;
        }
        temp = temp->next;
        new_node->next = temp->next;
        temp->next = new_node;
    }
    // to check the linkedlist is empty
    bool isEmpty()
    {
        return head == NULL;
    }
    // to display all linkedlist
    void Display()
    {
        node<T> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
    // Recursive Display
    void RecursiveDisplay()
    {
        if (head != NULL)
        {
            cout << head->data << endl;
            head = head->next;
            RecursiveDisplay();
        }
    }

    // reverse linkedlist through recursion
    void reverse(node<T> *current)
    {
        if (current != NULL)
        {

            reverse(current->next);
            cout << current->data << endl;
        }
    }
    void reverseRecursionDislay()
    {
        if (head == NULL)
        {
            cout << "list is empty" << endl;
        }
        reverse(head);
    }

    // get front of linkedlist
    T getFront()
    {
        if (head != NULL)
        {
            return head->data;
        }
        else
        {
            throw std::runtime_error("List is empty");
        }
    }
    // get tail of linkedlist
    T getTail()
    {
        if (head != NULL)
        {
            return tail->data;
        }
        else
        {
            throw std::runtime_error("List is empty");
        }
    }

    // Search node
    node<T> *search(T val)
    {
        node<T> *temp = head;
        while (temp != NULL)
        {
            if (temp->data == val)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    // remove At Front
    void removeFront()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            node<T> *temp = head;

            head = head->next;

            if (head == NULL)
            {
                tail = NULL;
            }
            delete temp;
        }
    }
    // Remove At Tail
    void removeTail()
    {
        if (head == NULL)
        {
            cout << "Nothing in list";
        }
        else
        {
            node<T> *temp = head;
            node<T> *prev = NULL;
            while (temp->next != NULL)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = NULL;
            tail = prev->next;

            delete temp;
        }
    }
    // Remove At Middle
    void removeMiddle()
    {
        int count = size / 2;
        if (count == 0)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {

            node<T> *temp = head;
            node<T> *prev = NULL;

            while (count != 0)
            {
                prev = temp;

                temp = temp->next;
                count--;
            }
            prev->next = temp->next;
            delete temp;
        }
    }

    // check whether linkedlist is circular or not

    bool isCircular()
    {   
        if(isEmpty())
        {
            return false;
        }
        node<T>* temp=head;
        while (temp!=NULL)
        {
            temp=temp->next;
            if(temp==head)
            {
                return true;
            }
        }

        return false;
    }
    // reversing the linkedlist
    void reverseLinkedlist()
    {
        node<T>* pre=NULL;
        node<T>* curr=head;
        node<T>* up;
        while(curr!=NULL)
        {
            up=curr->next;
            curr->next=pre;
            pre=curr;
            curr=up;


        }
        head=pre;


       
    }

    void recursiveLinkedlistReverse()
    {
        
       head= recursiveProcess(head); 
    }
    node<T>* recursiveProcess(node<T>* val )
    {
        if(val->next==NULL )
        {
            return val;
        }
       node<T>* temp=  recursiveProcess(val->next);
        val->next->next=val;
        val->next=NULL;
        
        return temp;

    }
};

// Implementation of Stack through Linkedlist
template <typename T>
class Stack
{
    Linkedlist<T> S;

public:
    void push(T val)
    {
        S.insertAtEnd(val);
    }
    bool isEmpty()
    {
        return S.isEmpty();
    }
    T pop()
    {
        T temp = S.getTail();
        S.removeTail();
        return temp;
    }
    void display()
    {
        S.Display();
    }
};

// Queue iplementation
template <typename T>
class Queue
{
    Linkedlist<T> Q;

public:
    bool isEmpty()
    {
        return Q.isEmpty();
    }
    void enQueue(T val)
    {
        Q.insertAtEnd(val);
    }
    T deQueue()
    {
        T temp = Q.getFront();
        Q.removeFront();
        return temp;
    }
    void display()
    {
        Q.Display();
    }
};

main()
{

    Linkedlist<int> l;
    l.insertAtEnd(1);
    l.insertAtEnd(2);
    l.insertAtEnd(3);
    l.recursiveLinkedlistReverse();
    l.Display();
   
}
