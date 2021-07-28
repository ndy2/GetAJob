#include <iostream>
#include <string.h>
using namespace std;

int N,M;
bool map[102][102];
bool visited[102][102];

void input()
{
	cin>>N>>M;
	int in;
	for(int r= 1 ;r <= N ; r++)
		for(int c= 1 ;c <= M ;c++)
		{
			cin>>in;
			map[r][c] = in==1;
		}
}

int cheese_cnt()
{
	int cnt = 0 ;
	for(int r= 1 ;r <= N ; r++)
		for(int c= 1 ; c<=M ; c++)
			if(map[r][c])
				cnt++;
	return cnt;
}

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

void dfs(int r, int c)
{
	if(visited[r][c])
		return;
	visited[r][c] = true;
	if(map[r][c])
		return;
	for(int d= 0 ;d <4; d++)
	{
		int ty = r+dy[d];
		int tx = c+dx[d];
		if(ty<0 || ty>N+1 || tx<0 || tx>M+1)
			continue;
		if(!visited[ty][tx])
			dfs(ty,tx);
	}
}

void remove()
{
	for(int r= 1; r <=N ; r++)
		for(int c= 1 ; c<= M ; c++)
			if(visited[r][c] && map[r][c])
				map[r][c] = false;
}

void solve()
{
	int time = 0;
	int prev_cnt = cheese_cnt();
	int cnt;
	if(prev_cnt ==0){
		cout<<"0\n0";
		return;
		}
	while(1)
	{
		memset(visited,0,sizeof(visited));
		time++;
		dfs(0,0);
		remove();
		cnt = cheese_cnt();
		if(cnt == 0)
			{
				printf("%d\n%d", time, prev_cnt);
				return;
			}
		prev_cnt = cnt;
	}
}

int main()
{
	input();
	solve();
}