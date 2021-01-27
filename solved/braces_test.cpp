#include <string>
#include <iostream>
#include <stack>
using namespace std;

/*is_balanced
 in   	- string p: consists of '(', ')'
 out  	- boolean 1 implies p is balanced, 0 implies p is imbalanced
 check 	- looping string p */
bool is_balanced(string p)
{
	int i = 0;
	if (p.empty()) return false;
	for (auto a : p)
	{
		if (a == '(') i++;
		else i--;
	}
	if (i == 0) return 1;
	return 0;
}

/*is_balanced
 in   	- string p: consists of '(', ')'
 out  	- boolean : 1 implies p is correct, 0 implies p is incorrect
 check 	- looping string p with stack s*/
bool is_correct(string p)
{
	stack <char> s;
	for (auto a : p)
	{
		//deal with extreme case : prevent pop empty stack
		if (s.empty()) 
			s.push(a);
		
		// ordinary case
		else
		{
			if (a == '(')
				s.push(a);
			else
				s.pop();
		}
	}
	if (s.empty()) return 1;
	return 0;
}

/*is_reducible
 in   	- string p: consists of '(', ')'
 out  	- boolean : 1 implies p is reducible, 0 implies p is irreducible
 check 	- loop string p */
bool is_reducible(string p)
{
	//deal with trivial cases
	if (p.empty()) return false;
	if (p.size() == 2)return false;
	
	// loop p in appropriate range
	string u, v;
	for (int i = 2; i <= p.size(); i += 2)
	{
		u = p.substr(0,i);
		v = p.substr(i, p.size() - i);
		if (is_balanced(u) && is_balanced(v))
			return true;
	}
	return false;
}

/*step 4-4 of description*/
string truncate_flip(string p)
{
	//truncate
	string q = p.substr(1, p.size() - 2);
	//flip
	for (int i = 0; i < p.size()-2; i++)
	{
		if (q[i] == '(') q[i] = ')';
		else q[i] = '(';
	}
	return q;
}

string solution(string p) {
	//step 1 of description
	if (p.empty()) return p;
	// 3. 만약 p가 이미 올바른 괄호 문자열이라면 그대로 return 하면 됩니다.
	if (is_correct(p)) return p;
	
	// string declaration
	string u, v;
	string answer = "";

	// loop p under appropriate range
	for (int i = 2; i <= p.size(); i += 2)
	{
		u = p.substr(0, i);
		v = p.substr(i, p.size() - i);
		// step 2 of description - validation of furthur steps
		if (is_balanced(u)  && !is_reducible(u))
		{
			//step 3 of description -  recurssive call under string u
			if (is_correct(u))
			{
				answer = u + solution(v);
				continue;
			}
			//step 4 of description - recurssive call under string v
			else
			{
				answer = "(" + solution(v) + ")" + truncate_flip(u);
				continue;
			}
		}
	}
	
	return answer;
}

int main()

{
    cout<<"Hello, world"<<endl;

    cout<<solution("(()())()")<<endl;
    cout<<solution(")(")<<endl;
    cout<<solution("()))((()")<<endl;

}