#include <string>
#include <vector>
#include <iostream>
#include <stack>



using namespace std;

typedef struct cor{
    int y;
    int x;
}cor;

typedef struct node{
    int data;
    cor c;
}node;

node  init_node (int data, cor c){
    node n ;
    n.data= data;
    n.c = c;
    return n;
}

vector<cor> d = {{0,-1}, {-1,0}, {0,1}, {1,0}}; // direction in (y,x) , left, above, right, below

int solution(int M, int N , vector<vector<int>> H) 
{   
    int ans = 0;
    stack<node> tree;
    cor cor_end = {M-1,N-1};
    node top = init_node(H[0][0],{0,0});
    tree.push(top);
    while(!tree.empty())
    {
        node cur = tree.top();
        tree.pop();
        for(int i = 0 ; i < 4 ; i ++)
        {
            if(cur.c.y + d[i].y >= 0 && cur.c.y + d[i].y < M &&\ 
                cur.c.x + d[i].x >= 0 && cur.c.x + d[i].x < N )
                {
                    node can = init_node(H[cur.c.y + d[i].y][cur.c.x + d[i].x], {cur.c.y + d[i].y,cur.c.x + d[i].x});
                    if(can.c.x == cor_end.x && can.c.y == cor_end.y )
                        {
                            ans++;
                            continue;
                        }
                    
                    if(can.data < cur.data)
                        tree.push(can);
                }
        }
    }
    return ans;
}

int main()
{
    int M, N, c;

    scanf("%d %d", &M,&N); 
    vector<vector<int>> H (M,vector<int>(N,0));
    for(int i = 0 ; i < M ; i ++ )
    {
        for(int j = 0 ; j < N ; j ++)
        {
            scanf("%d", &c );
            H[i][j] = c;
        }   
    }

    cout<<solution(M,N,H);    
    return 0;      
}