#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;
set<int> si;
bool is_prime(int x)
{
  if (x < 2) return false;
  if (x==2) return true;
  for(int i=2; i<= ceil(sqrt(x)); i++) {
    if ((x%i) == 0) return false;
  }
  return true;
}


int sub_soll(string numbers)
{
    int l = numbers.size();
    vector<int> ind ;
    int count = 0;
    for(int i = 0 ; i < l ; i ++) ind.push_back(i);
    do{
        string cur ;
        for(int i = 0 ; i < l ; i ++)
            cur.push_back(numbers[ind[i]]);
        int c = stoi(cur);
        if(si.find(c) == si.end())
            {
            si.insert(c);
            if(is_prime(c))
                {
                    count +=1;
                    cout<<c<<endl;
                }
        }
    }
    while(next_permutation(ind.begin(),ind.end()));
    return count;
}


int sub_sol(string numbers, int s)
{
    int l = numbers.size();
    int count = 0 ;
    vector<int> ind;
    for(int i = 0 ; i < l ; i ++)
        ind.push_back(i>=l-s?1:0);

    do{
        string cur ;
        for(int i = 0 ; i < l ; i ++)
            if(ind[i]) cur.push_back(numbers[i]);
        int c = stoi(cur);
        count += sub_soll(cur);

    }
    while(next_permutation(ind.begin(),ind.end()));

    return count;
}   


int solution(string numbers) {
    int l = numbers.size();
    int count = 0 ;
    for(int s = 1; s <= l ; s ++)
    {
        count += sub_sol(numbers, s);
    }
    return count;
}


int main()
{
    cout<<solution("1234")<<endl;;
}