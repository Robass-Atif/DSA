//  First problem of leetcode
class Solution {
public:
    bool isValid(string s) {
        stack<char> a;
        
        for(int i=0;i<s.length();i++)
        {
            
            if(s[i]=='(' || s[i]=='{' ||s[i]=='[')
            {
                a.push(s[i]);
            
            }
            else
            {
                if(!a.empty())
                {
                    char b=a.top();
                    if((b=='{'&& s[i]=='}')||(b=='['&& s[i]==']')|| (b=='('&& s[i]==')'))
                    {
                        a.pop();
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                    
                }
                else
                {
                    return false;
                }    
            }
        }  
        return  a.empty();
    }
};
// code end




// code of second example
class MinStack {
public:
    vector<int> a;

    MinStack() {
      
    }
    
    void push(int val) {
    a.push_back(val);
    }
    
    void pop() {
        a.pop_back();
    }
    
    int top() {
     return a.back();   
    }
    
    int getMin() {
        int smallest = a[0];
  for (int i = 1; i < a.size(); i++) {
    if (a[i] < smallest) {
      smallest = a[i];
    }
  }
   return smallest;     
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


// code end





//problem three
class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int> left_array(n);
        vector<int> right_array(n);
        left_array[0]=height[0];
        
        int sum=0;
        right_array[n-1]=height[n-1];
        
        for(int i=1;i<n;i++)
        {
        left_array[i]=max(height[i],left_array[i-1]);
        }
        for(int i=n-2;i>=0;i--)
        {
            right_array[i]=max(height[i],right_array[i+1]);
        }
        for(int i=0;i<n;i++)
        {
            
            sum+=min(left_array[i],right_array[i])-height[i];
        }
     
        return sum;
    }
};

// code end





// probelem Four
class Solution {
public:
    string decodeString(string s) {
        
        stack<char> decode;
        string result="";
        for(int i=0;i<s.length();i++)
        {
            if(s[i]==']')
            {
                string temp;
                while(decode.top()!='[' )
                {
                    temp.push_back(decode.top());
                    decode.pop();
                }
                decode.pop();
                reverse(temp.begin(),temp.end());
                string num;
                while(!decode.empty() && (decode.top()>='0' && decode.top()<='9'))
                {
                    num.push_back(decode.top());
                    decode.pop();
                }
                 reverse(num.begin(),num.end());
                int w=stoi(num);
                                
                for(int i=0;i<w;i++)
                {
                    for(int j=0;j<temp.length();j++)
                    {
                        decode.push(temp[j]);
                    }
                }

                
            }
            else
            {
                decode.push(s[i]);
            }
            
            
        }
        while(!decode.empty())
            {
              result.push_back(decode.top());
                decode.pop();
            }
            reverse(result.begin(),result.end());
        return result;
        
        
        
    }
    
    
};
// code end





// problem five
class Solution {
public:
    int maxArea(vector<int>& height) {
        int lr=0;
        int ri=height.size()-1;
        int result=0;
        while(lr<ri)
        {
            int lh=height[lr];
            int rh=height[ri];
            int mini=min(height[lr],height[ri]);
            result=max(result,mini*(ri-lr));

            if(lh<rh)
            {
                lr++;
            }
            else
            {
                ri--;
            }
            
        }
        
        
        return result;
    }
};
// code end





// problem six
class MyStack {
public:
    queue<int> a;
    queue<int> b;

    MyStack() {
        
    }
    
    void push(int x) {
        while(!a.empty())
        {
            b.push(a.front());
            a.pop();
        }
        a.push(x);
        while(!b.empty())
        {
                a.push(b.front());
            b.pop();
        }
        
        
    }
    
    int pop() {
        int p=a.front();
        a.pop();
     return p;
        
    }
    
    int top() {
      return  a.front();
    }
    
    bool empty() {
       return a.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */




// problem seven
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        stack<int> box;
        queue<int> line;

        for(int i = 0; i < students.size(); i++)
        {
            box.push(sandwiches[sandwiches.size() - 1 - i]);
            line.push(students[i]);
        }
        int n = 0;
        while(!line.empty())
        {
            if(box.top() == line.front())
            {
                box.pop();
                line.pop();
                n = 0;
            } else 
            {
                line.push(line.front());
                line.pop();
                n++;
            }

            if(n == line.size())
            {
                break;
            }
        }
        return line.size();
    }
};
//code end


// problem eight
class FrontMiddleBackQueue {
public:
    vector<int> main;
    FrontMiddleBackQueue() {
        
    }
    
    void pushFront(int val) {
        main.insert(main.begin(),val);
    }
    
    void pushMiddle(int val) {
        main.insert(main.begin()+main.size()/2,val);
    }
    
    void pushBack(int val) {
        main.push_back(val);
    }
    
    int popFront() {
        if(main.size()==0)
        {
            return -1;
        }
        int x=main[0];
        main.erase(main.begin());
        return x;
    }
    
    int popMiddle() {
        if(main.size()==0)
        {
            return -1;
        }
        int m=(main.size()-1)/2;
        int x=main[m];
        main.erase(main.begin()+m);
        return x;
    }
    
    int popBack() {
        if(main.size()==0)
        {
            return -1;
        }
        int x=main.back();
        main.pop_back();
        return x;
    }
};
// code end




// problem nine
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int arraysum=0;
        int maxm=nums[0];
        int mini=nums[0];
        int tempmin=0;
        int tempmax=0;
        
        for(int i=0;i<nums.size();i++)
            
        {
            tempmax+=nums[i];
            arraysum+=nums[i];
            tempmin+=nums[i];
            maxm=max(maxm,tempmax);
            if(tempmax<0)
            {
                tempmax=0;
            }
            
            mini=min(tempmin,mini);
            if(tempmin>0)
            {
                tempmin=0;
            }
            
        }
        int result=0;
        if(arraysum==mini)
        {
        result=maxm;
        }
        else
        {
            result=max(arraysum-mini,maxm);
        }
        return result;
        
        
        
    }
};
// code end

// problem ten
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        
        stack<int> val;
        int n=asteroids.size();
    
        for(int i=0;i<n;i++)
        {
            if(asteroids[i]>0 ||val.empty())
            {
                val.push(asteroids[i]);
            }
            else
            {
            
                while(true)
                {
                    int top=val.top();
                    if(top<0)
                    {
                        val.push(asteroids[i]);
                        break;
                    }
                    
                   else if(top>-asteroids[i])
                    {
                        break;
                    }
                    else if(top<-asteroids[i])
                    {
                        val.pop();
                      if(val.empty())
                      {
                          val.push(asteroids[i]);
                          break;
                      }
                    
                    }
                    else if(top==-asteroids[i])
                    {
                        val.pop();
                        break;
                    }
                    
                }
                
                
            }
        }
        stack<int> temp;
        while (!val.empty()) {
            temp.push(val.top());
            val.pop();
        }
        vector<int> ans;
        while (!temp.empty()) {
            ans.push_back(temp.top());
            temp.pop();
        }
        return ans;
         
    }
};
//code end







