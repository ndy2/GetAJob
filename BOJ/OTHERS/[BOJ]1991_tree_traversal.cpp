#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int N;
typedef struct node{
    char root;
    char l;
    char r;
}node;

vector<node> tree;

void input()
{
    cin>>N;
    vector<node> tree_copy(N,{'a','a','a'});
    for(int i = 0 ; i < N ; i++)
        cin>>tree_copy[i].root>>tree_copy[i].l>>tree_copy[i].r;
    tree = tree_copy;
}

void dfs(node root, int type, bool init)
{
    if(type == 1) cout<<root.root;
    if(root.l!='.')
        dfs(tree[root.l-'A'],type,false);
    if(type == 2) cout<<root.root;
    if(root.r!='.')
        dfs(tree[root.r-'A'],type,false);
    if(type == 3) cout<<root.root;
    if(init) cout<<"\n";
}

bool mysort(node a, node b)
{
    return a.root<b.root;
}

void solve()
{
    int root = 0;
    int left,right;
    sort(tree.begin(), tree.end(), mysort);
    dfs(tree[0],1,true);
    dfs(tree[0],2,true);
    dfs(tree[0],3,true);
}

int main()
{
    input();
    solve();
}