#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

int N;
string exp_;
vector<int> num_;
vector<char> ops_;

typedef struct expression{
   vector<int> num;
   vector<char> ops;
   int bar;
}expression;

void input()
{
   cin>>N;
   cin>>exp_;
}

void init_num_ops()
{
   bool is_num = true;
   for(auto i : exp_)
   {
      if(is_num) num_.push_back(i - '0');
      else ops_.push_back(i);
      is_num = !is_num;
   }
}

int calc(vector<int> n, vector<char> o)
{
   int size = o.size();
   for(int l = 0 ; l < size ; l++)
   {
      switch (o[l]){
      case '+':{
         n[l+1] = n[l] + n[l+1];
         break;
      }
      case '-':{
         n[l+1] = n[l] - n[l+1];
         break;
      }
      case '*':{
         n[l+1] = n[l] * n[l+1];
         break;
      }
      }
   }
   return n[size];
}

int calc_one(int a, int b, char op)
{
      int ret;
      switch (op){
      case '+':{
         ret = a + b;
         break;
      }
      case '-':{
         ret = a - b;
         break;
      }
      case '*':{
         ret = a * b;
         break;
      }
      }
   return ret;

}
vector<expression> children(expression e)
{
   vector<int> n = e.num;
   vector<char> o = e.ops;
   int b = e.bar;

   vector<expression> ve;

   //add bracket
   vector<int> ab_n = n;
   vector<char> ab_o = o;
   ab_n[e.bar] = calc_one(n[e.bar], n[e.bar+1], o[e.bar]);
   ab_n.erase(ab_n.begin() + e.bar+1);
   ab_o.erase(ab_o.begin() + e.bar);
   int ab_b = e.bar+1;

   if(ab_b <= ab_o.size()+1)
      ve.push_back({ab_n, ab_o, ab_b});

   //no braket
   vector<int> nb_n = n;
   vector<char> nb_o = o;
   int nb_b = e.bar+1;

   if(nb_b <= nb_o.size())
      ve.push_back({nb_n, nb_o, nb_b});

   return ve;
}


void solve()
{
   init_num_ops();

   //bfs
   queue<expression> q;
   q.push({num_, ops_, 0});
   vector<expression> le;
   while(!q.empty())
   {
      expression e = q.front();
      q.pop();
      if(e.bar >= e.ops.size())
      {
         le.push_back(e);
         continue;
      }
         
      vector<expression> ve = children(e);
      for(auto e : ve)
         q.push(e);
   }

   int ans = 0x80000000;
   for(auto e : le)
         ans = max(calc(e.num, e.ops), ans);
   
   cout<<ans;
}

int main()
{
   input();
   solve();
}