#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <stack>
#include <functional>

using namespace std;
// Dos Shell
class DOSshell
{

public:
    // file class
    class File
    {
    public:
        string name;
        string extension;
        string content;
        int size;
        string path;

        File(string name, string extension, string content, string path = "")
        {
            this->name = name;
            this->extension = extension;
            this->content = content;
            this->size = content.length();
        }
    };
    // class directory
    class Directory
    {
    public:
        string name;
        list<File *> files;
        list<Directory *> directories;
        Directory *parent;
        string path;

        Directory(string name, Directory *parent = NULL, string path = "")
        {
            this->name = name;
            this->path = path;
            this->parent = parent;
        }
        // path cancadenation
        string getPath()
        {
            return path;
        }
        
    };

    Directory *root;
    Directory *currentDirectory;
    DOSshell()
    {
        root = new Directory("root", NULL, "root/");
        currentDirectory = root;
        cout << "Robass Atif 2022-CS-150 and Mohammad Tayyab 2022-CS-133  Data Structure Algorithm" << endl;
    }

    // ATTRIB Displays file (name provided as input) attributes.
    void attrib(string name, string extension)
    {

        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                cout << file->name << "." << file->extension << endl;
                cout << "Size of File :" << file->size << endl;
                cout << "Content of File :" << file->content << endl;
                break;
            }
        }
    }
    // implement cd command
    void cd(string name)
    {
        
        for (auto dir : currentDirectory->directories)
        {
            if (dir->name == name)
            {
                currentDirectory = dir;

                break;
            }
        }
        // }
    }
    // CD. Prints working directory (i.e. your current directory in your tree structure)
    void cdDot()
    {

        cout << "Your are in  " << currentDirectory->name << "  Directory" << endl;
    }
    // implement cd.. command
    void cdDotDot()
    {

        if (currentDirectory != root)
        {

            currentDirectory = currentDirectory->parent;
        }
    }
    // implement cd\ command
    void cdBackslash()
    {
        currentDirectory = root;
    }
    // implement convert command which Asks two types and converts extension of all files of one type to another type.
    void convert(string type1, string type2)
    {
        for (auto file : currentDirectory->files)
        {
            if (file->extension == type1)
            {
                file->extension = type2;
            }
            
        }
    }
    // implement copy command which copies a file from one directory to another directory.
    void copy(string name, string extension, string directoryName)
    {
        File *fileToCopy = nullptr;
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                fileToCopy = file;
                break;
            }
        }
        if (fileToCopy != nullptr)
        {
            for (auto dir : currentDirectory->directories)
            {
                if (dir->name == directoryName)
                {
                    dir->files.push_back(fileToCopy);
                    break;
                }
            }
        }
    }
    // implement create command which Creates a file with the name provided and allows the user to enter contents of the file.
    void create(string name, string extension, string content)
    {    
    
        File *file = new File(name, extension, content, currentDirectory->getPath() + name + "." + extension+"/" );
        currentDirectory->files.push_back(file);
    }

    // implement delete command which Deletes a file with the name provided.
    void deleteFile(string name, string extension)
    {
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                currentDirectory->files.remove(file);
                break;
            }
        }
    }
    // implement dir command which Lists all files and directories in the current directory.
    void dir()
    {
        for (auto file : currentDirectory->files)
        {
            cout << file->name << "." << file->extension << endl;
        }
        for (auto dir : currentDirectory->directories)
        {
            cout << dir->name << endl;
        }
    }
    // implement edit command which Edits a file with the name provided and allows the user to enter new contents of the file.
    void edit(string name, string extension, string content)
    {
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                file->content = content;
                break;
            }
        }
    }
    // implement exit command which Exits the shell.
    void exitShell()
    {
        exit(0);
    }
    // FIND Searches for a file in your current virtual directory whose name is provided as input.
    void find(string name)
    {

        for (auto file : currentDirectory->files)
        {
            if (file->name == name)
            {
                cout << "File is Found" << endl;
                cout << file->name << "." << file->extension << endl;
                break;
            }
        }
    }
    // implement findf command which Searches for a text string in the currently open file or the file whose name is provided as input
    void findf(string name, string extension, string text)
    {
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                if (file->content.find(text) != string::npos)
                {
                    cout << "Text found" << endl;
                }
                else
                {
                    cout << "Text not found" << endl;
                }
                break;
            }
        }
    }
    // implement findSTR command which Searches for strings in all files of your current virtual directory, prints names of files with the string found.
    void findSTR(string text)
    {
        bool flag = false;
        for (auto file : currentDirectory->files)
        {
            if (file->content.find(text) != string::npos)
            {
                cout << "String found in That File: ";
                cout << file->name << "." << file->extension << endl;
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            cout << "Text not found" << endl;
        }
    }
    // implement format command which Formats the current virtual directory i.e. empties the current directory and all subdirectories.
    void format()
    {
        currentDirectory->files.clear();
        currentDirectory->directories.clear();
    }
    // implement help command which Displays all commands and their syntax.
    void help()
    {
        cout<<"attrib <filename>.<extension>"<<endl;
        cout<<"cd <directory>"<<endl;
        cout<<"cd."<<endl;
        cout<<"cd.."<<endl;
        cout<<"cd\\"<<endl;
        cout<<"convert <type1> <type2>"<<endl;
        cout<<"copy <filename>.<extension> <directory>"<<endl;
        cout<<"create <filename>.<extension> <content>"<<endl;
        cout<<"del <filename>.<extension>"<<endl;
        cout<<"dir"<<endl;
        cout<<"edit <filename>.<extension> <content>"<<endl;
        cout<<"exit"<<endl;
        cout<<"find <filename>"<<endl;
        cout<<"findf <filename>.<extension> <text>"<<endl;
        cout<<"findSTR <text>"<<endl;
        cout<<"format"<<endl;
        cout<<"help"<<endl;
        cout<<"loadTree"<<endl;
        cout<<"mkdir <directory>"<<endl;
        cout<<"move <filename>.<extension> <directory>"<<endl;
        cout<<"PPPrint "<<endl;
        cout<<"prompt"<<endl;
        cout<<"print <filename>.<extension>"<<endl;
        cout<<"PQUEUE"<<endl;
        cout<<"PWD"<<endl;
        cout<<"QUEUE"<<endl;
        cout<<"rename <filename>.<extension> <newfilename>.<newextension>"<<endl;
        cout<<"RMDIR <directory>"<<endl;
        cout<<"SAVE"<<endl;
        cout<<"TREE"<<endl;
        cout<<"VER"<<endl;



    }
    // loadTree command which Loads the tree structure of the current virtual directory from a file.
    void loadTree()
    {

    }
    // implement mkdir functionalty
    void mkdir(string name)
    {
        string path2 = currentDirectory->getPath();
        path2 = path2 + name+"/" ;
        Directory *dir = new Directory(name, currentDirectory, path2);
        currentDirectory->directories.push_back(dir);
    }
    // implement move command which Moves a file from one directory to another directory.
    void move(string name, string extension, string directoryName)
    {
        File *fileToMove = nullptr;
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                fileToMove = file;
                break;
            }
        }
        if (fileToMove != nullptr)
        {
            for (auto dir : currentDirectory->directories)
            {
                if (dir->name == directoryName)
                {
                    dir->files.push_back(fileToMove);
                    currentDirectory->files.remove(fileToMove);
                    break;
                }
            }
        }
    }
    // implement PPPrint command Adds a text file to the priority based print queue, and displays the current priority queue.
void ppprint()
{
    // Using priority queue based on file size in descending order
    priority_queue<File*, vector<File*>, function<bool(File*, File*)>> pq(
        [](File* a, File* b) { return a->size < b->size; }
    );

    for (auto file : currentDirectory->files)
    {
        pq.push(file);
    }

    while (!pq.empty())
    {
        File* file = pq.top();
        pq.pop();
        cout << file->name << "." << file->extension << endl;
    }
}


    
    // print which Adds a text file to the print queue, and displays the current queue.
    void print(string name, string extension)
    {
        File *fileToPrint = nullptr;
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                fileToPrint = file;
                break;
            }
        }
        if (fileToPrint != nullptr)
        {
            cout << fileToPrint->name << "." << fileToPrint->extension << endl;
        }
    }
    // PQUEUE Shows current state of the priority based print queue, with time left for each element
    // base on size of file
    void PQUEUE()
    {
        priority_queue<File *> pq;
        for (auto file : currentDirectory->files)
        {
            pq.push(file);
        }
        while (!pq.empty())
        {
            File *file = pq.top();
            pq.pop();
            cout << file->name << "." << file->extension << endl;
        }
    }
    // PWD Prints working directory
    void PWD()
    {
        cout << currentDirectory->name << endl;
    }
    // QUEUE Shows current state of the print queue, with time left for each element
    // simple print queue
    void QUEUE()
    {
        for (auto file : currentDirectory->files)
        {
            cout << file->name << "." << file->extension << endl;
        }
    }
    // implement rename command which Renames a file with the name provided.
    void rename(string name, string extension, string newName, string newExtension)
    {
        for (auto file : currentDirectory->files)
        {
            if (file->name == name && file->extension == extension)
            {
                file->name = newName;
                file->extension = newExtension;
                break;
            }
        }
    }
    // RMDIR Removes a directory along with its contents. Consider setting the respective sibling links
    void RMDIR(string name)
    {
        for (auto dir : currentDirectory->directories)
        {
            if (dir->name == name)
            {
                currentDirectory->directories.remove(dir);
                break;
            }
        }
    }
    // SAVE Saves the currently open file to disk.
    void SAVE()
    {
    // store directories on separate file and files on separeate files and this function is recursive function
     ofstream myfile;
     ofstream myfile2;
        myfile2.open ("files.txt");
        myfile.open ("directories.txt");
        for (auto dir : currentDirectory->directories)
        {
            myfile << dir->name << endl;
            myfile << dir->path << endl;
            SAVE();
        }
        for (auto file : currentDirectory->files)
        {
            myfile2 << file->name << endl;
            myfile2 << file->extension << endl;
            myfile2 << file->content << endl;
            myfile2 << file->size << endl;
            myfile2 << file->path << endl;
        }
        myfile.close();
        myfile2.close();
        
        



     
    }
    // TREE Displays the complete directory structure. recursive function
    void TREE()
    {
        // format foldername
        //            |__SUbfoldername
        //            |__SUbfoldername

        cout << currentDirectory->name << endl;
        for (auto dir : currentDirectory->directories)
        {
            cout << "|__";
            cd(dir->name);
            TREE();
            cdDotDot();
        }
    }
    
    // VER Displays the version of your program.
    void VER()
    {
        cout << "Version 1.0" << endl;
    }
    // user input
    void userInput()
    {
        string input;
        bool isPrompt=false;

        while (true)
        {
            if(!isPrompt)
            {
            cout << currentDirectory->path << ">:";
            }
            else
            {
            // last / remove and put $ 
            string path = currentDirectory->path;
            path = path.substr(0, path.length() - 1);
            path = path.substr(0, path.find_last_of("/"));
            path = path + "$";
            cout << path << ">:";

            }
            getline(cin, input);
            string command = input.substr(0, input.find(" "));
            string args = input.substr(input.find(" ") + 1);
            if (command == "attrib")
            {
                // in that format attrib <filename>.<extension>
                string name = args.substr(0, args.find("."));
                string extension = args.substr(args.find(".") + 1);

                attrib(name, extension);
            }
            else if (command == "cd")
            {
                string name = args.substr(0, args.find(" "));
                cd(name);
            }
            else if (command == "cd.")
            {
                cdDot();
            }
            else if (command == "cd..")
            {
                cdDotDot();
            }
            else if (command == "cd\\")
            {
                cdBackslash();
            }
            else if (command == "convert")
            {
                string type1 = args.substr(0, args.find(" "));
                string type2 = args.substr(args.find(" ") + 1);
                convert(type1, type2);
            }
            else if (command == "copy")
            {
                // format copy <filename>.<extension> <directory>
                string name = args.substr(0, args.find("."));
                args = args.substr(args.find(".") + 1);
                string extension = args.substr(0, args.find(" "));
                string directoryName = args.substr(args.find(" ") + 1);

                copy(name, extension, directoryName);
            }
            else if (command == "create")
            {
                // in fromat "create <filename>.<extension> <content>" and all validation
                if(args.find(".") == string::npos || args.find(" ") == string::npos)
                {
                    cout << "Invalid Command" << endl;
                    continue;
                }
                string name = args.substr(0, args.find(".")); 
                args = args.substr(args.find(".") + 1);
                
                
                if (args.find(" ") == string::npos)
                {
                    cout << "Invalid Command" << endl;
                    continue;
                }
                // if he donot enter extension
                

                string extension = args.substr(0, args.find(" ")); 
                string content = args.substr(args.find(" ") + 1);  

                create(name, extension, content);
            }
            else if (command == "del")
            {
                // format delete <filename>.<extension>
                string name = args.substr(0, args.find("."));
                string extension = args.substr(args.find(".") + 1);
                deleteFile(name, extension);
            }
            else if (command == "dir")
            {
                dir();
            }
            else if (command == "mkdir")
            {
                mkdir(args);
            }
            else if (command == "edit")
            {
                // format edit <filename>.<extension> <content>
                string name = args.substr(0, args.find("."));
                args = args.substr(args.find(".") + 1);
                string extension = args.substr(0, args.find(" "));
                string content = args.substr(args.find(" ") + 1);
                edit(name, extension, content);
            }
            else if (command == "exit")
            {
                exitShell();
            }
            else if (command == "find")
            {
                string name = args.substr(0, args.find(" "));
                find(name);
            }
            else if (command == "findf")
            {
              // format findf <filename>.<extension> <text>
                string name = args.substr(0, args.find("."));
                args = args.substr(args.find(".") + 1);
                string extension = args.substr(0, args.find(" "));
                string text = args.substr(args.find(" ") + 1);
                findf(name, extension, text);
            }
            else if (command == "findSTR")
            {
                string text = args.substr(0, args.find(" "));
                findSTR(text);
            }
            else if (command == "format")
            {
                format();
            }
            else if (command == "help")
            {
                help();
            }
            else if (command == "move")
            {
                // format move <filename>.<extension> <directory>
                string name = args.substr(0, args.find("."));
                args = args.substr(args.find(".") + 1);
                string extension = args.substr(0, args.find(" "));
                string directoryName = args.substr(args.find(" ") + 1);
                move(name, extension, directoryName);
            }
            else if (command == "print")
            {
                string name = args.substr(0, args.find(" "));
                string extension = args.substr(args.find(" ") + 1);
                print(name, extension);
            }
            else if (command == "prompt")
            {
                isPrompt=true;
            }
            else if (command == "rename")
            {
                // format rename <filename>.<extension> <newfilename>.<newextension>
                string name = args.substr(0, args.find("."));
                args = args.substr(args.find(".") + 1);
                string extension = args.substr(0, args.find(" "));
                args = args.substr(args.find(" ") + 1);
                string newName = args.substr(0, args.find("."));
                string newExtension = args.substr(args.find(".") + 1);

                rename(name, extension, newName, newExtension);
            }
            else if (command == "rmdir")
            {
                string name = args.substr(0, args.find(" "));
                RMDIR(name);
            }
            else if (command == "save")
            {
                SAVE();
            }
            else if (command == "tree")
            {
                TREE();
            }
            else if (command == "ver")
            {
                VER();
            }
            else if (command == "pwd")
            {
                PWD();
            }
            else if (command == "queue")
            {
                QUEUE();
            }
            else if (command == "pqueue")
            {
                PQUEUE();
            }
            else if(command == "ppprint")
            {
                // format ppprint <filename>.<extension> <content>
                
                ppprint();

            }
            else
            {
                cout << "Invalid Command" << endl;
            }
        }
    }
};

int main()
{
    DOSshell shell;
    shell.userInput();

    return 0;
}