#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
// prototype
void printHeader();
using namespace std;
// color on text
void colorontext(int num)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, num);
}

template <typename T>
// mini excel class
class MiniExcel
{

public:
    // function 1: Constructor
    MiniExcel()
    {
        intialize5_5();
    }
    // Cell Class
    class cell
    {
    public:
        T value;
        cell *next;
        cell *prev;
        cell *up;
        cell *down;

        int row;
        int col;
        // Cell Construtor
        cell(T val, int row, int col)
        {
            this->row = row;
            this->col = col;
            value = val;
            next = NULL;
            prev = NULL;
            up = NULL;
            down = NULL;
        }
    };
    // iterator classs
    class iterator
    {
    public:
        cell *ptr;

        // iterator constructor
        iterator(cell *p)
        {
            ptr = p;
        }
        // operator overoading
        iterator operator++()
        {
            ptr = ptr->next;
            return *ptr;
        }
        iterator operator--()
        {
            ptr = ptr->prev;
            return *ptr;
        }
        iterator operator++(int)
        {

            ptr = ptr->down;
            return *ptr;
        }
        iterator operator--(int)
        {

            ptr = ptr->up;
            return *ptr;
        }
    };
    // attributes
    cell *active;
    cell *head;
    vector<T> copyVector;
    bool isRow = true;

    // intialize 5 by 5 cells by default and data is ""
    void intialize5_5()
    {

        cell *new_node = new cell("1", 0, 0);
        active = new_node;
        head = new_node;
        cell *temp = head;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cell *new_node2 = new cell("1", j + 1, i);
                temp->down = new_node2;
                new_node2->up = temp;
                temp = temp->down;
            }

            cell *new_node1 = new cell("1", 0, i + 1);
            temp = new_node1;
            new_node->next = new_node1;
            new_node1->prev = new_node;
            new_node = new_node->next;
        }
        for (int j = 0; j < 4; j++)
        {
            cell *new_node2 = new cell("1", j + 1, 4);
            temp->down = new_node2;
            new_node2->up = temp;

            temp = temp->down;
        }
        cell *h1 = head;
        cell *h2 = head->next;
        cell *t1 = h1;
        cell *t2 = h2;
        while (h2 != NULL)
        {
            t1 = h1;
            t2 = h2;
            for (int i = 0; i < 5; i++)
            {
                t1->next = t2;
                t2->prev = t1;
                t1 = t1->down;
                t2 = t2->down;
            }
            h1 = h2;
            h2 = h2->next;
        }
    }

    // Function:17 print whole excel sheet
    void printSheet()
    {
        cell *first = head;
        while (first != NULL)
        {
            setColor(32, 0);
            cout << "----------------";
            resetColor();
            first = first->next;
        }
        cout << endl;
        cell *temp = head;
        cell *tempRow = head;

        while (tempRow != NULL)
        {
            setColor(32, 0);
            cout << "|";
            resetColor();
            temp = tempRow;
            while (temp != NULL)
            {
                if (temp == active)
                {
                    setColor(31, 51);
                    cout << " " << setw(13) << temp->value << " ";
                    resetColor();
                    setColor(32, 0);
                    cout << "|";
                    resetColor();
                }
                else
                {
                    cout << " " << setw(13) << temp->value << " ";
                    setColor(32, 0);
                    cout << "|";
                    resetColor();
                }

                temp = temp->next;
            }
            cout << endl;

            first = head;
            while (first != NULL)
            {
                setColor(31, 0);
                cout << "----------------";
                resetColor();
                first = first->next;
            }

            cout << endl;
            tempRow = tempRow->down;
        }
    }
    // Function:2 insert row above
    void insertRowAbove()
    {

        cell *temp = rowStarter(active->row);
        cell *dummy = temp;

        if (temp->up != NULL) // when up is not null
        {

            cell *previous = NULL;

            while (temp != NULL)
            {

                cell *new_node = new cell("5", temp->row, temp->col);
                new_node->down = temp;

                new_node->up = temp->up;
                temp->up->down = new_node;
                temp->up = new_node;

                if (previous != NULL)
                {
                    previous->next = new_node;
                    new_node->prev = previous;
                }
                previous = new_node;

                temp = temp->next;
            }
        }
        else // when up is not null
        {

            cell *original = dummy;
            cell *previous = NULL;
            while (temp != NULL)
            {
                cell *new_node = new cell("5", 0, temp->col);
                new_node->down = temp;
                temp->up = new_node;

                if (previous != NULL)
                {
                    previous->next = new_node;
                    new_node->prev = previous;
                }
                previous = new_node;
                temp = temp->next;
            }

            head = original->up;
        }
        //  correction of row and coloumn
        cell *dummyrow = dummy;
        while (dummyrow != NULL)
        {
            dummy = dummyrow;
            while (dummy != NULL)
            {
                dummy->row = dummy->row + 1;
                dummy = dummy->next;
            }

            dummyrow = dummyrow->down;
        }
    }
    // find row
    cell *rowStarter(int i)
    {
        cell *temp = head;

        while (i > 0)
        {
            temp = temp->down;
            i--;
        }
        return temp;
    }
    // Function:3 insert row below
    void insertRowBelow()
    {
        cell *temp = rowStarter(active->row);
        cell *dummy = temp->down;
        if (temp->down != NULL) // when down is not null
        {
            cell *previous = NULL;
            cell *help = temp->down;
            while (temp != NULL)
            {

                cell *new_node = new cell("2", temp->row + 1, temp->down->col);
                new_node->up = temp;

                new_node->down = temp->down;
                temp->down->up = new_node;
                temp->down = new_node;

                if (previous != NULL)
                {
                    previous->next = new_node;
                    new_node->prev = previous;
                }
                previous = new_node;

                temp = temp->next;
            }
        }
        else // when down is null
        {

            cell *previous = NULL;
            while (temp != NULL)
            {
                cell *new_node = new cell("9", temp->row, temp->col);
                new_node->up = temp;
                temp->down = new_node;

                if (previous != NULL)
                {
                    previous->next = new_node;
                    new_node->prev = previous;
                }
                previous = new_node;
                temp = temp->next;
            }
        }
        // updation of row and coloumn
        cell *dummyrow = dummy;
        while (dummyrow != NULL)
        {
            dummy = dummyrow;
            while (dummy != NULL)
            {
                dummy->row = dummy->row + 1;
                dummy = dummy->next;
            }

            dummyrow = dummyrow->down;
        }
    }
    // Function:4 insert coloumn right
    void insertColoumnRight()
    {
        cell *temp = colStarter(active->col);
        cell *dummy = temp->next;
        if (temp->next != NULL) // when next is not null
        {
            cell *previous = NULL;
            cell *help = temp->next;
            while (temp != NULL)
            {

                cell *new_node = new cell("4", temp->row, temp->col + 1);
                new_node->prev = temp;

                new_node->next = temp->next;
                temp->next->prev = new_node;
                temp->next = new_node;

                if (previous != NULL)
                {
                    previous->down = new_node;
                    new_node->up = previous;
                }
                previous = new_node;

                temp = temp->down;
            }
        }
        else // when next is null
        {

            cell *previous = NULL;
            while (temp != NULL)
            {
                cell *new_node = new cell("6", temp->row, temp->col + 1);
                new_node->prev = temp;
                temp->next = new_node;

                if (previous != NULL)
                {
                    previous->down = new_node;
                    new_node->up = previous;
                }
                previous = new_node;
                temp = temp->down;
            }
        }
        // updation of row and coloumn
        cell *dummyrow = dummy;
        while (dummyrow != NULL)
        {
            dummy = dummyrow;
            while (dummy != NULL)
            {
                dummy->col = dummy->col + 1;
                dummy = dummy->next;
            }

            dummyrow = dummyrow->down;
        }
    }
    // get coloumn address
    cell *colStarter(int i)
    {
        cell *temp = head;

        while (i > 0)
        {
            temp = temp->next;
            i--;
        }
        return temp;
    }
    // Function:5 insert coloumn at left
    void insertColoumnLeft()
    {

        cell *temp = colStarter(active->col);
        cell *dummy = temp;
        if (temp->prev != NULL) // when prev is not null
        {

            cell *previous = NULL;
            cell *help = temp->prev;
            while (temp != NULL)
            {

                cell *new_node = new cell("2", temp->row, temp->col);
                new_node->next = temp;

                new_node->prev = temp->prev;
                temp->prev->next = new_node;
                temp->prev = new_node;

                if (previous != NULL)
                {
                    previous->down = new_node;
                    new_node->up = previous;
                }
                previous = new_node;

                temp = temp->down;
            }
        }
        else // when prev is null
        {

            cell *previous = NULL;

            while (temp != NULL)
            {
                cell *new_node = new cell("7", temp->row, temp->col);
                new_node->next = temp;
                temp->prev = new_node;

                if (previous != NULL)
                {
                    previous->down = new_node;
                    new_node->up = previous;
                }
                previous = new_node;
                temp = temp->down;
            }
            head = dummy->prev;
        }
        // updation of row and coloumn
        cell *dummyrow = dummy;
        while (dummyrow != NULL)
        {
            dummy = dummyrow;
            while (dummy != NULL)
            {
                dummy->col = dummy->col + 1;
                dummy = dummy->next;
            }

            dummyrow = dummyrow->down;
        }
    }
    // Function:6 insert cell by right sift
    void insertCellByRightShift()
    {
        cell *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        cell *previous = NULL;
        while (temp != NULL)
        {
            cell *new_node = new cell("_", temp->row, temp->col + 1);
            new_node->prev = temp;
            temp->next = new_node;

            if (previous != NULL)
            {
                previous->down = new_node;
                new_node->up = previous;
            }
            previous = new_node;
            temp = temp->down;
        }
        // shifting of values upward
        cell *help = active;
        temp = active;
        T n = temp->next->value;
        T p = temp->value;
        temp = temp->next;
        while (temp != NULL)
        {
            n = temp->value;
            temp->value = p;
            p = n;

            temp = temp->next;
        }
        help->value = "_";
        active = help->next;
    }
    // Function:7 insert cell by down shift
    void insertCellByDownShift()
    {
        cell *temp = head;
        while (temp->down != NULL)
        {
            temp = temp->down;
        }
        // insert coloumn at bottom of the sheet
        cell *previous = NULL;
        while (temp != NULL)
        {
            cell *new_node = new cell("_", temp->row + 1, temp->col);
            new_node->up = temp;
            temp->down = new_node;

            if (previous != NULL)
            {
                previous->next = new_node;
                new_node->prev = previous;
            }
            previous = new_node;
            temp = temp->next;
        }
        // shifting of values upward
        cell *help = active;

        temp = active;
        T n = temp->down->value;
        T p = temp->value;
        temp = temp->down;

        while (temp != NULL)
        {

            n = temp->value;
            temp->value = p;
            p = n;
            temp = temp->down;
        }
        help->value = "_";

        active = active->down;
    }
    // Function:10 delete coloumn
    void deleteColoumn()
    {
        cell *temp = colStarter(active->col);
        if (temp->prev == NULL && temp->next != NULL)
        {
            active = temp->next;
            head = temp->next;
            temp = temp->next;
            while (temp != NULL)
            {
                temp->prev = NULL;
                temp = temp->down;
            }
            cell *original = active;
            cell *row = active;
            while (row != NULL)
            {
                original = row;
                while (original != NULL)
                {
                    original->col = original->col - 1;
                    original = original->next;
                }
                row = row->down;
            }
        }
        else if (temp->next == NULL && temp->prev != NULL)
        {
            active = temp->prev;
            temp = temp->prev;
            while (temp != NULL)
            {
                temp->next = NULL;
                temp = temp->down;
            }
        }
        else if (temp->next != NULL && temp->prev != NULL)
        {
            active = temp->next;
            temp = temp->next;
            while (temp != NULL)
            {
                temp->prev = temp->prev->prev;
                temp->prev->next = temp;
                temp = temp->down;
            }
            cell *original = active;
            cell *row = active;
            while (row != NULL)
            {
                original = row;
                while (original != NULL)
                {
                    original->col = original->col - 1;
                    original = original->next;
                }
                row = row->down;
            }
        }
    }
    // Function:11 delete row
    void deleteRow()
    {
        cell *temp = active;
        while (temp->prev != NULL)
        {
            temp = temp->prev;
        }
        if (temp->up == NULL && temp->down != NULL)
        {
            head = temp->down;
            active = temp->down;
            temp = temp->down;
            while (temp != NULL)
            {
                temp->up = NULL;
                temp = temp->next;
            }
            cell *original = active;
            cell *row = active;
            while (row != NULL)
            {
                original = row;
                while (original != NULL)
                {
                    original->row = original->row - 1;
                    original = original->next;
                }
                row = row->down;
            }
        }
        else if (temp->down == NULL && temp->up != NULL)
        {

            active = temp->up;
            temp = temp->up;
            while (temp != NULL)
            {
                temp->up = NULL;
                temp = temp->next;
            }
        }
        else if (temp->down != NULL && temp->up != NULL)
        {

            active = temp->down;
            temp = temp->down;
            while (temp != NULL)
            {
                temp->up = temp->up->up;
                temp->up->down = temp;
                temp = temp->next;
            }
            cell *original = active;
            cell *row = active;
            while (row != NULL)
            {
                original = row;
                while (original != NULL)
                {
                    original->row = original->row - 1;
                    original = original->next;
                }
                row = row->down;
            }
        }
    }
    // Function:13 clear row
    void clearRow()
    {
        cell *temp = active;
        // mov at the start of row
        while (temp->prev != NULL)
        {
            temp = temp->prev;
        }
        // put _ in all cells of row
        while (temp != NULL)
        {
            temp->value = "_";
            temp = temp->next;
        }
    }
    // Function:12 clear coloumn
    void clearColoumn()
    {
        cell *temp = active;
        // mov at the start of coloumn
        while (temp->up != NULL)
        {
            temp = temp->up;
        }
        // put _ in all cells of coloumn
        while (temp != NULL)
        {
            temp->value = "_";
            temp = temp->down;
        }
    }
    // Function:8 delete cell by  left shift
    void DeleteCellByLeftShift()
    {
        cell *temp = active;
        if (temp->prev == NULL && temp->next != NULL)
        {
            while (temp->next != NULL)
            {
                temp->value = temp->next->value;
                temp = temp->next;
            }
            temp->value = "_";
        }
        else if (temp->prev != NULL && temp->next != NULL)
        {
            active = active->prev;
            while (temp->next != NULL)
            {
                temp->value = temp->next->value;
                temp = temp->next;
            }
            temp->value = "_";
        }
    }
    // Function:9 delete cell by up shift
    void DeleteCellByUpShift()
    {
        cell *temp = active;
        if (temp->up == NULL && temp->down != NULL)
        {
            while (temp->down != NULL)
            {
                temp->value = temp->down->value;
                temp = temp->down;
            }
            temp->value = "_";
        }
        else if (temp->up != NULL && temp->down != NULL)
        {
            active = active->up;
            while (temp->down != NULL)
            {
                temp->value = temp->down->value;
                temp = temp->down;
            }
            temp->value = "_";
        }
        else if (temp->down == NULL && temp->up != NULL)
        {
            active = active->up;
            temp->value = "_";
        }
    }

    // Function:23 store excel into file
    void storeData()
    {
        fstream file;
        cell *temp = head;
        cell *tempRow = head;
        file.open("excel.txt", ios::out);
        while (tempRow != NULL)
        {
            temp = tempRow;
            while (temp != NULL)
            {
                file << temp->value;
                if (temp->next != NULL)
                {
                    file << ",";
                }

                temp = temp->next;
            }
            file << endl;
            tempRow = tempRow->down;
        }
        file.close();
    }
    // split function
    void splitString(const string &inputString, vector<string> &outputVector, char delimiter)
    {
        istringstream tokenStream(inputString);
        string token;

        while (getline(tokenStream, token, delimiter))
        {
            outputVector.push_back(token);
        }
    }
    //  Function:23 load back into program
    void loadData()
    {
        string line;
        fstream file;
        file.open("excel.txt", ios::in);
        int row = 0;
        int coloumn = 0;
        cell *temp = NULL;
        cell *tempRow = NULL;
        while (getline(file, line))
        {
            vector<string> values;
            splitString(line, values, ',');

            while (!values.empty())
            {
                cell *new_node = new cell(values.front(), row, coloumn);
                coloumn++;
                values.erase(values.begin());
                if (temp == NULL && tempRow == NULL)
                {
                    temp = new_node;
                    tempRow = temp;
                    active = temp;
                    head = temp;
                }
                else if (temp == NULL && tempRow != NULL)
                {
                    temp = new_node;
                    tempRow->down = new_node;
                    new_node->up = tempRow;
                    tempRow = tempRow->down;
                }
                else
                {
                    temp->next = new_node;
                    new_node->prev = temp;
                    temp = temp->next;
                }
            }
            row++;
            coloumn = 0;
            temp = NULL;
        }
        cell *h1 = head;
        cell *h2 = head->down;
        cell *t1 = h1;
        cell *t2 = h2;
        while (h2 != NULL)
        {
            t1 = h1;
            t2 = h2;
            while (t2 != NULL)
            {
                t1->down = t2;
                t2->up = t1;
                t1 = t1->next;
                t2 = t2->next;
            }
            h1 = h2;
            h2 = h2->down;
        }

        file.close();
    }
    // Function:14 get range end

    void GetRangeSum(cell *RangeStart, cell *RangeEnd)
    {
        cell *temp = RangeStart;
        int sum = 0;
        while (temp != NULL && temp != RangeEnd)
        {
            for (char c : temp->value)
            {
                if (isdigit(static_cast<unsigned char>(c)))
                {
                    sum += c - '0'; // Convert character to integer
                }
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {
            sum = 0;
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {
                for (char c : temp->value)
                {
                    if (isdigit(static_cast<unsigned char>(c)))
                    {
                        sum += c - '0'; // Convert character to integer
                    }
                }

                temp = temp->down;
            }
            if (temp == NULL)
            {
                return;
            }
            else
            {
                for (char c : temp->value)
                {
                    if (isdigit(static_cast<unsigned char>(c)))
                    {
                        sum += c - '0'; // Convert character to integer
                    }
                }
                active->value = to_string(sum);
            }
        }
        else
        {
            for (char c : temp->value)
            {
                if (isdigit(static_cast<unsigned char>(c)))
                {
                    sum += c - '0'; // Convert character to integer
                }
            }
            active->value = to_string(sum);
        }
    }
    // Function:14 get range average
    void GetRangeAverage(cell *RangeStart, cell *RangeEnd)
    {
        cell *temp = RangeStart;
        int sum = 0;
        int count = 0;
        while (temp != NULL && temp != RangeEnd)
        {
            for (char c : temp->value)
            {
                if (isdigit(static_cast<unsigned char>(c)))
                {
                    sum += c - '0'; // Convert character to integer
                }
            }
            count++;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            count = 0;
            sum = 0;
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {
                for (char c : temp->value)
                {
                    if (isdigit(static_cast<unsigned char>(c)))
                    {
                        sum += c - '0'; // Convert character to integer
                    }
                }
                count++;
                temp = temp->down;
            }
            if (temp == NULL)
            {
                return;
            }
            else
            {
                for (char c : temp->value)
                {
                    if (isdigit(static_cast<unsigned char>(c)))
                    {
                        sum += c - '0'; // Convert character to integer
                    }
                }
                temp->value = sum / count;
            }
        }
        else
        {
            for (char c : temp->value)
            {
                if (isdigit(static_cast<unsigned char>(c)))
                {
                    sum += c - '0'; // Convert character to integer
                }
            }

            temp->value = sum / count;
        }
    }
    // Function:19 copy function
    void copy(cell *RangeStart, cell *RangeEnd)
    {
        if (RangeStart == RangeEnd)
        {
            RangeStart->value = "";
            return;
        }
        if (copyVector.size() > 0)
        {
            copyVector.clear();
        }
        cell *temp = RangeStart;

        while (temp != NULL && temp != RangeEnd)
        {
            copyVector.push_back(temp->value);
            temp = temp->next;
        }
        if (temp == NULL)
        {

            copyVector.clear();
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {
                copyVector.push_back(temp->value);

                temp = temp->down;
            }
            if (temp == NULL)
            {
                copyVector.clear();
            }
            else
            {

                copyVector.push_back(temp->value);
            }
        }
        else
        {

            copyVector.push_back(temp->value);
        }
    }
    // Function:20 cut function
    void cut(cell *RangeStart, cell *RangeEnd)
    {
        if (RangeStart == RangeEnd)
        {
            RangeStart->value = "";
            return;
        }
        if (copyVector.size() > 0)
        {
            copyVector.clear();
        }
        cell *temp = RangeStart;

        while (temp != NULL && temp != RangeEnd)
        {
            copyVector.push_back(temp->value);
            temp->value = "";
            temp = temp->next;
        }
        if (temp == NULL)
        {

            copyVector.clear();
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {
                copyVector.push_back(temp->value);
                temp->value = "";

                temp = temp->down;
            }
            if (temp == NULL)
            {
                copyVector.clear();
            }
            else
            {

                copyVector.push_back(temp->value);
                temp->value = "";
            }
        }
        else
        {
            copyVector.push_back(temp->value);
            temp->value = "";
        }
    }
    // change Data of cell
    void changeData()
    {
        cout << " enter the data of current cell : ";
        string data1 = "";
        while (_kbhit())
        {
            _getch();
        }

        cin >> data1;
        active->value = data1;
    }
    // set color
    void setColor(int fore, int back)
    {
        cout << "\033[" << fore << ";48;5;" << back << "m";
    }
    // reset color
    void resetColor()
    {
        cout << "\033[0m";
    }
    cell *find(int row, int col)
    {
        cell *temp = head;
        while (row > 0 && temp)
        {
            temp = temp->down;
            row--;
        }
        while (col > 0 && temp)
        {
            temp = temp->next;
            col--;
        }
        if (row != 0 || col != 0)
        {
            return NULL;
        }
        else
        {
            return temp;
        }
    }
    void copyWorks()
    {
        int row, col, r1, c1;
        while (_kbhit())
        {
            _getch();
        }
        cout << "Enter the row of starting cell: ";
        cin >> row;
        cout << "Enter the Coloumn of staring cell: ";
        cin >> col;
        cout << "Enter the row of ending cell: ";
        cin >> r1;
        cout << "Enter the Coloumn of ending cell: ";
        cin >> c1;
        if (r1 == row)
        {
            isRow = true;
        }
        else if (c1 == col)
        {
            isRow = false;
        }
        else
        {
            return;
        }
        cell *temp1 = find(row, col);
        cell *temp2 = find(r1, c1);
        copy(temp1, temp2);
    }
    void cutWork()
    {
        int row, col, r1, c1;
        while (_kbhit())
        {
            _getch();
        }
        cout << "Enter the row of starting cell: ";
        cin >> row;
        cout << "Enter the Coloumn of staring cell: ";
        cin >> col;
        cout << "Enter the row of ending cell: ";
        cin >> r1;
        cout << "Enter the Coloumn of ending cell: ";
        cin >> c1;
        if (r1 == row)
        {
            isRow = true;
        }
        else if (c1 == col)
        {
            isRow = false;
        }
        else
        {
            return;
        }
        cell *temp1 = find(row, col);
        cell *temp2 = find(r1, c1);
        cut(temp1, temp2);
    }
    void paste()
    {
        if (isRow)
        {
            int row = active->row;
            int col = active->col;
            cell *temp = find(row, col);
            for (int i = 0; i < copyVector.size(); i++)
            {
                temp->value = copyVector[i];
                if (temp->next == NULL && i != copyVector.size() - 1)
                {
                    cell *temp1 = temp;
                    cell *previous = NULL;
                    while (temp1 != NULL)
                    {
                        cell *new_node = new cell("6", temp1->row, temp1->col + 1);
                        new_node->prev = temp1;
                        temp1->next = new_node;

                        if (previous != NULL)
                        {
                            previous->down = new_node;
                            new_node->up = previous;
                        }
                        previous = new_node;
                        temp1 = temp1->down;
                    }
                }
                temp = temp->next;
            }
            copyVector.clear();
        }
        else
        {
            int row = active->row;
            int col = active->col;
            cell *temp = find(row, col);
            for (int i = 0; i < copyVector.size(); i++)
            {
                temp->value = copyVector[i];
                if (temp->down == NULL && i != copyVector.size() - 1)
                {
                    cell *temp1 = temp;
                    cell *previous = NULL;
                    while (temp1 != NULL)
                    {
                        cell *new_node = new cell("6", temp1->row + 1, temp1->col);
                        new_node->up = temp1;
                        temp1->down = new_node;

                        if (previous != NULL)
                        {
                            previous->next = new_node;
                            new_node->prev = previous;
                        }
                        previous = new_node;
                        temp1 = temp1->next;
                    }
                }

                temp = temp->down;
            }
            copyVector.clear();
        }
    }
    void Count(cell *RangeStart, cell *RangeEnd)
    {
        cell *temp = RangeStart;
        int sum = 0;
        int count = 0;
        while (temp != NULL && temp != RangeEnd)
        {

            count++;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            count = 0;
            sum = 0;
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {

                count++;
                temp = temp->down;
            }
            if (temp == NULL)
            {
                return;
            }
            else
            {

                temp->value = count;
            }
        }
        else
        {

            temp->value = count;
        }
    }
    void Min(cell *RangeStart, cell *RangeEnd)
    {
        cell *temp = RangeStart;
        int sum = 0;
        int Min = 0;
        while (temp != NULL && temp != RangeEnd)
        {

            sum = temp->value - '0'; // Convert character to integer

            if (Min > sum)
            {
                Min = sum;
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {

            sum = 0;
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {

                sum = temp->value - '0'; // Convert character to integer
                if (Min > sum)
                {
                    Min = sum;
                }

                temp = temp->down;
            }
            if (temp == NULL)
            {
                return;
            }
            else
            {

                sum = temp->value - '0'; // Convert character to integer

                if (Min > sum)
                {
                    Min = sum;
                }
                temp->value = Min;
            }
        }
        else
        {

            sum = temp->value - '0'; // Convert character to integer
            if (Min > sum)
            {
                Min = sum;
            }

            temp->value = Min;
        }
    }
    void Max(cell *RangeStart, cell *RangeEnd)
    {
        cell *temp = RangeStart;
        int sum = 0;
        int Max = 0;
        while (temp != NULL && temp != RangeEnd)
        {

            sum = temp->value - '0'; // Convert character to integer

            if (Max < sum)
            {
                Max = sum;
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {

            sum = 0;
            temp = RangeStart;

            while (temp != NULL && temp != RangeEnd)
            {

                sum = temp->value - '0'; // Convert character to integer
                if (Max < sum)
                {
                    Max = sum;
                }

                temp = temp->down;
            }
            if (temp == NULL)
            {
                return;
            }
            else
            {

                sum = temp->value - '0'; // Convert character to integer

                if (Max > sum)
                {
                    Max = sum;
                }
                temp->value = Min;
            }
        }
        else
        {

            sum = temp->value - '0'; // Convert character to integer
            if (Max > sum)
            {
                Max = sum;
            }

            temp->value = Min;
        }
    }

    void sumWork()
    {
        int row, col, r1, c1;
        while (_kbhit())
        {
            _getch();
        }
        cout << "Enter the row of starting cell: ";
        cin >> row;
        cout << "Enter the Coloumn of staring cell: ";
        cin >> col;
        cout << "Enter the row of ending cell: ";
        cin >> r1;
        cout << "Enter the Coloumn of ending cell: ";
        cin >> c1;
        cell *temp1 = find(row, col);
        cell *temp2 = find(r1, c1);
        GetRangeSum(temp1, temp2);
    }
};
// main function
int main()
{
    MiniExcel<string> m;
    m.loadData();
    printHeader();
    m.printSheet();

    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            system("cls");
            if (m.active->prev != NULL)
            {
                m.active = m.active->prev;
            }
            printHeader();
            m.printSheet();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            system("cls");
            if (m.active->next != NULL)
            {
                m.active = m.active->next;
            }
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            system("cls");
            if (m.active->up != NULL)
            {
                m.active = m.active->up;
            }
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            system("cls");
            if (m.active->down != NULL)
            {
                m.active = m.active->down;
            }
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        if (GetAsyncKeyState('R') && GetAsyncKeyState(VK_SHIFT)) // insert coloumn right
        {
            system("cls");
            m.insertColoumnRight();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('A') && GetAsyncKeyState(VK_SHIFT)) // insert row above
        {
            system("cls");
            m.insertRowAbove();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('B') && GetAsyncKeyState(VK_SHIFT)) // insert row below
        {
            system("cls");
            m.insertRowBelow();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('L') && GetAsyncKeyState(VK_SHIFT)) // insert coloumn left
        {
            system("cls");
            m.insertColoumnLeft();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('C') && GetAsyncKeyState(VK_SHIFT)) // clear row
        {
            system("cls");
            m.clearRow();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('I') && GetAsyncKeyState(VK_SHIFT))
        {
            system("cls");
            m.clearColoumn();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_DELETE))
        {
            system("cls");
            m.DeleteCellByLeftShift();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('E') && GetAsyncKeyState(VK_SHIFT))
        {
            system("cls");
            m.deleteColoumn();
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState('T') && GetAsyncKeyState(VK_SHIFT))
        {
            m.changeData();
            system("cls");
            printHeader();

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('Q'))
        {

            m.copyWorks();
            system("cls");

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('D'))
        {

            m.cutWork();
            system("cls");

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('O'))
        {

            m.paste();
            system("cls");

            m.printSheet();
        }
        if (GetAsyncKeyState('S') && GetAsyncKeyState(VK_SHIFT))
        {

            m.sumWork();
            system("cls");

            m.printSheet();
        }

        Sleep(80);
    }
    m.storeData();
    return 0;
}

void printHeader()
{
    colorontext(3);
    cout << "   ##   ##    ####   ###  ##    ####   ### ###  ##  ##    ## ##   ### ###  ####   " << endl;
    cout << "    ## ##      ##      ## ##     ##     ##  ##  ### ##   ##   ##   ##  ##   ##    " << endl;
    cout << "   # ### #     ##     # ## #     ##     ##       ###     ##        ##       ##    " << endl;
    cout << "   ## # ##     ##     ## ##      ##     ## ##     ###    ##        ## ##    ##    " << endl;
    cout << "   ##   ##     ##     ##  ##     ##     ##         ###   ##        ##       ##     " << endl;
    cout << "   ##   ##     ##     ##  ##     ##     ##  ##  ##  ###  ##   ##   ##  ##   ##  ## " << endl;
    cout << "   ##   ##    ####   ###  ##    ####   ### ###  ##   ##   ## ##   ### ###  ### ### " << endl;
    colorontext(7);
}
