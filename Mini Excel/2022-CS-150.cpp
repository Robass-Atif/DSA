#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>

using namespace std;
void colorontext(int num)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, num);
}

template <typename T>
class MiniExcel
{

public:
    MiniExcel()
    {
        intialize5_5();
    }
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
    class iterator
    {
    public:
        cell *ptr;

        iterator(cell *p)
        {
            ptr = p;
        }
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
    cell *active;
    cell *head;
    vector<T> copyVector;
    bool isRow=true;

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

    // print whole excel sheet
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
    // insert row above
    void insertRowAbove()
    {

        cell *temp = rowStarter(active->row);
        cell *dummy = temp;

        if (temp->up != NULL)
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
        else
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
    // insert row below
    void insertRowBelow()
    {
        cell *temp = rowStarter(active->row);
        cell *dummy = temp->down;
        if (temp->down != NULL)
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
        else
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
    // insert coloumn right
    void insertColoumnRight()
    {
        cell *temp = colStarter(active->col);
        cell *dummy = temp->next;
        if (temp->next != NULL)
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
        else
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
    // insert coloumn at left
    void insertColoumnLeft()
    {

        cell *temp = colStarter(active->col);
        cell *dummy = temp;
        if (temp->prev != NULL)
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
        else
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
    // insert cell by right sift
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
    // insert cell by down shift
    void insertCellByDownShift()
    {
        cell *temp = head;
        while (temp->down != NULL)
        {
            temp = temp->down;
        }

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
    // delete coloumn
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
    // delete row
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
    void clearRow()
    {
        cell *temp = active;
        while (temp->prev != NULL)
        {
            temp = temp->prev;
        }
        while (temp != NULL)
        {
            temp->value = "_";
            temp = temp->next;
        }
    }
    void clearColoumn()
    {
        cell *temp = active;
        while (temp->up != NULL)
        {
            temp = temp->up;
        }
        while (temp != NULL)
        {
            temp->value = "_";
            temp = temp->down;
        }
    }
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

    // store excel into file
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
    // load back into program
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
    // get range end

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
                temp->value = sum;
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
            temp->value = sum;
        }
    }

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

    void copy(cell *RangeStart, cell *RangeEnd)
    {
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
                isRow=false;
                copyVector.push_Back(temp->value);
            }
        }
        else
        {

            copyVector.push_Back(temp->value);
        }
    }

    void cut(cell *RangeStart, cell *RangeEnd)
    {
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
                isRow=false;

                copyVector.push_Back(temp->value);
                temp->value = "";
            }
        }
        else
        {
            copyVector.push_Back(temp->value);
            temp->value = "";
        }
    }
    void changeData()
    {
        cout << " enter the data of current cell" << endl;
        string data1 = "";
        while (_kbhit())
        {
            _getch();
        }

        cin >> data1;
        active->value = data1;
    }
    void setColor(int fore, int back)
    {
        cout << "\033[" << fore << ";48;5;" << back << "m";
    }
    void resetColor()
    {
        cout << "\033[0m";
    }
};

int main()
{
    MiniExcel<string> m;
    m.loadData();
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

            m.printSheet();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            system("cls");
            if (m.active->next != NULL)
            {
                m.active = m.active->next;
            }
            m.printSheet();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            system("cls");
            if (m.active->up != NULL)
            {
                m.active = m.active->up;
            }
            m.printSheet();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            system("cls");
            if (m.active->down != NULL)
            {
                m.active = m.active->down;
            }
            m.printSheet();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        if (GetAsyncKeyState('R')) // insert coloumn right
        {
            system("cls");
            m.insertColoumnRight();
            m.printSheet();
        }
        if (GetAsyncKeyState('A')) // insert row above
        {
            system("cls");
            m.insertRowAbove();
            m.printSheet();
        }
        if (GetAsyncKeyState('B')) // insert row below
        {
            system("cls");
            m.insertRowBelow();
            m.printSheet();
        }
        if (GetAsyncKeyState('L')) // insert coloumn left
        {
            system("cls");
            m.insertColoumnLeft();
            m.printSheet();
        }
        if (GetAsyncKeyState('C')) // clear row
        {
            system("cls");
            m.clearRow();
            m.printSheet();
        }
        if (GetAsyncKeyState('V'))
        {
            system("cls");
            m.clearColoumn();
            m.printSheet();
        }
        if (GetAsyncKeyState(VK_DELETE))
        {
            system("cls");
            m.deleteRow();
            m.printSheet();
        }
        if (GetAsyncKeyState('E'))
        {
            system("cls");
            m.deleteColoumn();
            m.printSheet();
        }
        if (GetAsyncKeyState('T'))
        {
            m.changeData();
            system("cls");
            m.printSheet();
        }

        Sleep(80);
    }
    m.storeData();
    return 0;
}
