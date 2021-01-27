#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
using namespace std;

/*is_balanced
 in   	- string p: consists of '(', ')'
 out  	- boolean 1 implies p is balanced, 0 implies p is imbalanced
 check 	- loop string p */
bool is_balanced(string p)
{
    int i=0;
    //auto 문법 까먹어서 쳐봄
    for (auto a : p)
    {
        if(a == '(') i++;
        else i--;
    }
    if (i==0) return true;
    else return false;
}

/*is_balanced
 in   	- string p: consists of '(', ')'
 out  	- boolean : 1 implies p is correct, 0 implies p is incorrect
 check 	- loop string p with stack s*/
bool is_correct(string p)
{
    stack <char> s;
    if(p.front() == ')') return false;
    for (auto a : p)
    {
        if( a == '(') s.push(a);
        else s.pop();
    }
    if (s.empty()) return true;
    else return false;
}

//split info
//return : pair<int,bool>
//int - split index
//bool - true  if u is correct   : go to stage 3
//     - false if u is incorrect : go to stage 4
pair<int,bool> get_split_info(string p)
{
    string u,v;
    int len = p.length();
    for(int i = 2; i <= len ; i+=2)
    {
        //substr 문법 까먹어서 쳐봄
        u = p.substr(0,i);
        v = p.substr(i,len);
        if(is_balanced(u)&&is_balanced(v))
        {
            if(is_correct(u)) return make_pair(i,true);
            else return  make_pair(i,false);
        }
    }
}

//step 4-4 of description
string truncate_flip(string u)
{
    string s;
    //truncate
    s = u.substr(1,u.length()-2);
    //flip
    for (int i = 0 ; i <s.length(); i++)
    {
        if (s[i] =='(') s[i] = ')';
        else s[i] = '(';
    }
    return s;
}

string solution(string p) {
    //step 1 of description
    if(p.empty())
        return p;
    string answer = "";
    string u,v;
    pair <int,bool> info = get_split_info(p);
    u = p.substr(0,info.first);
    v = p.substr(info.first,p.length());
       
    if(info.second)  answer = u + solution(v);
    else  answer = "(" + solution(v) +")" + truncate_flip(u);

    return answer;
}


int main()
{
    // cout<<solution("(()())()")<<endl;
    cout<<solution(")(")<<endl;
    // cout<<solution("()))((()")<<endl;
}