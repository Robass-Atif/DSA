l.insertAtBefore(l.fbegin()++,4);
    for (doublyLinkedlist<int>::iterator i = l.fbegin(); i != l.fend(); i++)
    {
        cout << *i << endl;
    }