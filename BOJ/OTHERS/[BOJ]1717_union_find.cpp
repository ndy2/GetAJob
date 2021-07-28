#include <iostream>
#include <algorithm>

using namespace std;

int N,M;
int parents[1000001];
int set_size[1000001];

int find_(int a)
{
    if(a == parents[a])
        return a;
    else return parents[a] = find_(parents[a]);
}

void union_(int a, int b)
{
   if(set_size[a] < set_size[b])
        swap(a,b);
    set_size[a] +=set_size[b];
    set_size[b] = 0;
    parents[b] = a;
}

void init_()
{
    for(int i = 1 ; i <=N; i++)
    {
        parents[i] = i;
        set_size[i] = 1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    cin>>N>>M;
    int op,a,b;
    init_();
    for(int i = 0 ; i < M ; i++)
    {
        cin>>op>>a>>b;
        int s1 = find_(a);
        int s2 = find_(b);
        if(op==0)
            union_(s1,s2);
        else{
            string s = find_(s1) == find_(s2)?"YES\n":"NO\n";
            cout<<s;
        }
    }
}