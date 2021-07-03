#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>


using namespace std;

int N,M;
int map[101][101];
int visited[101][101];

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};
vector<vector<int>> edges;

int idx_some = 1;

void input()
{
   cin>>N>>M;
   for(int r = 1; r <=N ; r++)
      for(int c= 1; c <=M ; c++)
         cin>>map[r][c];
}

void bfs(int r, int c)
{  
   if(visited[r][c] || map[r][c] == 0)
      return;
   else{
      queue<vector<int>> q;
      q.push({r,c});
      while(!q.empty())
      {
         vector<int> cor = q.front();
         q.pop();
         visited[cor[0]][cor[1]] = 1;
         map[cor[0]][cor[1]] = idx_some;

         for(int d = 0 ; d<4; d++)
         {
            int ty = cor[0] + dy[d];
            int tx = cor[1] + dx[d];
            if(ty>=1 && ty <=N && tx>=1 && tx <=M && !visited[ty][tx] && map[ty][tx] == 1)
               q.push({ty,tx});
         }
      }
      idx_some ++;
   }
}

void division()
{
   for(int r = 1; r <=N ; r++)
       for(int c= 1; c <=M; c++)
           bfs(r,c);
}

void transpose()
{
   int map_transpose[101][101];
   for(int r = 1 ; r<=N ; r ++)
      for(int c= 1 ; c<=M ; c++)
         map_transpose[c][r] = map[r][c];
   copy(&map_transpose[0][0], &map_transpose[0][0] + 101*101, &map[0][0]);
   int temp = N;
   N=M;
   M=temp;
}

void set_edge_row()
{ 
   for(int row = 1 ; row <= N ; row ++)
    {
       int prev_island = -1;
       int prev_island_idx = -1;
       int cur_island = -1;
       
       for(int col = 1; col <=M ; col++)
       {
         if(map[row][col] != 0)
            cur_island = map[row][col];
         else
         {
            if(cur_island != -1)
               {
                  prev_island = cur_island;
                  cur_island = -1;
                  prev_island_idx = col-1;
               }
         } 
         if(cur_island != prev_island && prev_island !=-1 &&map[row][col] !=0)
          {
            cur_island = map[row][col];
            int bridge_len = col-prev_island_idx-1;
            if( bridge_len>=2)
            {
               edges[cur_island][prev_island] = min(bridge_len, edges[cur_island][prev_island]);
               edges[prev_island][cur_island] = min(bridge_len,edges[prev_island][cur_island]);
            }
            prev_island = cur_island;
               
          }
            
       }
    }
}

bool mysort(vector<int> a, vector<int> b)
{
   return a[2]<b[2];
}

int connection_map[7][7];
int is_visited[7];
int target;
int num;

bool connected;

int edges_cnt = 0;

void dfs(int a)
{
   if(a==target)
   {
      connected = true;
      return;
   }
   else{
      if(connected)
         return;
      if(is_visited[a])
         return;
      else
      {
         is_visited[a] = true;
         for(int c = 1 ; c <= edges.size(); c++)
            if(connection_map[a][c] == 1 && !is_visited[c])
                dfs(c);
      }
   }
}


int kruskal( )
{
   int ret = 0;
   vector<vector<int>> vec_edges;
   for(int r= 1 ; r <=edges.size()-1 ; r++)
      for(int c= 1; c <= r-1; c++)
         if(edges[r][c]!=1e9)
            vec_edges.push_back({r,c,edges[r][c]});
   
   sort(vec_edges.begin(), vec_edges.end(), mysort);
   bool is_valid = false;
   for(auto e : vec_edges)
   {
      connected = false;
      target = e[1];
      dfs(e[0]);
      memset(is_visited, 0 ,sizeof(is_visited));
      if(connected)
         continue;
      else{
         edges_cnt ++;
         ret += e[2];
         connection_map[e[0]][e[1]] = 1;
         connection_map[e[1]][e[0]] = 1;
      }
      if(edges_cnt == edges.size()-2)
      {
         is_valid = true;
         break;
      }
         
   }
   if(!is_valid) return -1;
   return ret;
}

void solve()
{
    division();

    int num_island = idx_some -1;
    vector<vector<int>> edges_copy(num_island+1, vector<int>(num_island+1,1e9));
    for(int i = 1 ; i <=num_island ; i++)
      edges_copy[i][i] =0;
   edges = edges_copy;
   set_edge_row();
   transpose();
   set_edge_row();
   
   //get answer;
   cout<<kruskal();
}

int main()
{
   input();
   solve();
}