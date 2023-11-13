#include<iostream>
#include<stack> 
#include<algorithm>
#include<string>
#include<math.h>
#include<cmath>
#include<cctype>
using namespace std;
string infixToPostfix(string s);
int precedence(char s);
string infixToPrefix(string s);
int evaluatePrefix(string s);


int evaluatePostfix(string s);

//prescedence function
int precedence(char s)
{
    if(s=='+'|| s=='-')
    {
        return 1;
    }
    else if(s=='*'|| s=='/')
    {
        return 2;
    }
    else if(s=='^')
    {
        return 3;
    }
    else
    {
        return 0;
    }

}
//infix to prefix
string infixToPrefix(string s)
{
    reverse(s.begin(),s.end());
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(')
        {
            s[i]=')';
        }
        else if(s[i]==')')
        {
            s[i]='(';
        }
    }


    
    string result=infixToPostfix(s);
    reverse(result.begin(),result.end());
    return result;
}
// infix to postfix
string infixToPostfix(string s)
{
    string result="";
    stack<char> temp;
    for(int i=0;i<s.size();i++)
    {
        if(isdigit(s[i]))
        {
            result.push_back(s[i]);
        }
        else if(s[i]==' ')
        {
            continue;
        }
        else if(s[i]=='(')
        {
            temp.push(s[i]);
        }
        else if(s[i]==')')
        {
            while(temp.top()!='(')
            {
                result.push_back(temp.top());
                temp.pop();
            }
            temp.pop();
        }
        else
        {
            while(!temp.empty() && precedence(temp.top())>=precedence(s[i]))
            {
                result.push_back(temp.top());
                temp.pop();
            }
            temp.push(s[i]);    
        }


    }
    while(!temp.empty())
    {
        result.push_back(temp.top());
        temp.pop();
    }

    return result;


}

//evaluate prefix
int evaluatePrefix(string s)
{   
   stack<int> temp;
   int result=0;
    for(int i=s.size()-1;i>=0;i--)
    {
         if(isdigit(s[i]))
         {
              temp.push(s[i]-'0');
         }
         else
         {
              int a=temp.top();
              temp.pop();
              int b=temp.top();
              temp.pop();
              if(s[i]=='+')
              {
                temp.push(a+b);
              }
              else if(s[i]=='-')
              {
                temp.push(a-b);
              }
              else if(s[i]=='*')
              {
                temp.push(a*b);
              }
              else if(s[i]=='/')
              {
                temp.push(a/b);
              }
              else if(s[i]=='^')
              {
                temp.push(pow(a,b));
              }
         }



    }

    if(temp.size()==1)
    {
        return temp.top();
    }
    else
    {
        return -1;
    }


}
//evaluate postfix
int evaluatePostfix(string s)
{
    int result=0;
    stack<int> temp;
    for(int i=0;i<s.size();i++)
    {
        if(isdigit(s[i]))
        {
            temp.push(s[i]-'0');
        }
        else if(s[i]==' ')
        {
            continue;
        }

        else
        {
            int b=temp.top();
            temp.pop();
            int a=temp.top();
            temp.pop();
            if(s[i]=='+')
            {
                result=a+b;
            }
            else if(s[i]=='-')
            {
                result=a-b;
            }
            else if(s[i]=='*')
            {
                result=a*b;
            }
            else if(s[i]=='/')
            {
                result=a/b;
            }
            else if(s[i]=='^')
            {
                result=pow(a,b);
            }
            temp.push(result);
        }
        
    }

    if(temp.size()==1)
    {
        return temp.top();
    }
    else
    {
        return -1;
    }
}



//main function

main()
{
string s="3+5*8";
string result=infixToPrefix(s);
string result1=infixToPostfix(s);
cout<<"Infix to prefix: "<<result<<endl;
cout<<"Infix to postfix: "<<result1<<endl;
int result2=evaluatePrefix(result);
int result3=evaluatePostfix(result1);
cout<<"Evaluate prefix: "<<result2<<endl;
cout<<"Evaluate postfix: "<<result3<<endl;
reverse(result.begin(),result.end());
cout<<" : "<<result<<endl;
int value=evaluatePostfix(result1);
cout<<"Evaluate postfix: "<<value<<endl;




}