#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <set>


using namespace std;

int N,M,D;
vector<vector<int>> castle;
vector<vector<int>> castle_save;

void input()
{
   cin>>N>>M>>D;
   vector<vector<int>> castle_copy(N, (vector<int>(M,0)));
   for(int r = 0 ; r < N ; r++)
      for(int c = 0 ; c < M ; c++)
         cin>> castle_copy[r][c];
   castle_save = castle_copy;
}

//this game does not require search throungh below
int dy[3] = {0,0,-1};
int dx[3] = {-1,1,0};

bool mysort(vector<int> a, vector<int> b)
{
   return a[1]<b[1];
}

vector<int> bfs(int p)
{
   vector<vector<int>> visited (N,vector<int>(M,0));
   vector<vector<int>> targets;
   queue<vector<int>> q;
   bool found = false;
   int min_dist;
   q.push({N-1,p,1});
   while(!q.empty())
   {
      vector<int> pos = q.front();
      q.pop();
      if(visited[pos[0]][pos[1]])
         continue;
      else
      {
         visited[pos[0]][pos[1]] = 1;
         if(found)
            if(castle[pos[0]][pos[1]] == 1 && pos[2] == min_dist)
            {
               targets.push_back({pos[0], pos[1]});
               continue;
            }
            else
               continue;
         if(castle[pos[0]][pos[1]] == 1 && pos[2] <=D)
            {
               targets.push_back({pos[0],pos[1]});
               found = true;
               min_dist = pos[2];
            }
         
               
         for(int d = 0 ; d <3 ; d++)
         {
            int ty = pos[0] + dy[d];
            int tx = pos[1] + dx[d];
            if(ty>=0 && ty<N && tx >=0 && tx <M && !visited[ty][tx] &&!found)
               q.push({ty,tx, pos[2]+1});
         }
      }

   }

   sort(targets.begin(), targets.end(),mysort);
   if(targets.size()>=1) return targets[0];
   else return {-1,-1};
}

int is_triv()
{
   int trivial_amount = 0;

   int upper_idx = N-D<0?0:N-D;
   for(int r = upper_idx ; r <N; r++)
      for(int c = 0 ; c < M ; c++)
         if(castle[r][c] ==1)
            return 0;
   for(int r = 0 ; r < N-D ; r++)
      for(int c = 0 ; c < M ; c++)
         if(castle[r][c] == 1)
            return 1;
   return 2;
}

void enemy_2_below()
{
   vector<int> dummy(M,0);
   castle.pop_back();
   castle.insert(castle.begin(),dummy);
}

int turn(vector<int> pos)
{
   int trivail_amount = is_triv();
   if(trivail_amount == 1)
   {
      enemy_2_below();
      return 0;
   }
   if(trivail_amount ==2)
      return -1;

   //each archor set their target
   //note that it is enought to search its target from Nth row
   set<vector<int>> target_pos;
   for(auto p : pos)
      {
         vector<int> target = bfs(p);
         if(target[0]!=-1)
         target_pos.insert(target);
      }

   //kill target   
   for(auto p : target_pos)
      castle[p[0]][p[1]] = 0;

   //enemy move to below
   enemy_2_below();
   return target_pos.size();

}

void solve()
{
   vector<int> idx(M,0);
   fill_n(idx.end()-3, 3, 1);
   int glb_ans = 0;
   do{
      int ans = 0;
      vector<int> archors;
      for(int i = 0 ; i < M  ; i++)
         if(idx[i]==1)
            archors.push_back(i);
      int kill_cnt = 0;
      castle = castle_save;
      for(int row = 0 ; row <N ; row++)
      {
         kill_cnt = turn(archors);
         if(kill_cnt == -1)
            break;
         else
            ans+=kill_cnt;
      }
         
      glb_ans = max(glb_ans , ans);
   }while(next_permutation(idx.begin(), idx.end()));

   cout<<glb_ans;
}

int main()
{
   input();
   solve();
}