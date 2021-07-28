#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;



int N;
char map[50][50];

void input()
{
	cin>>N;
	for(int r= 0 ; r< N ; r++)
	{
		string line;
		cin>>line;
		for(int c = 0 ; c < N ; c++)
			map[r][c] = line[c];
	}
}

int len;
bool visited_row[50];
void dfs_row(int r, int c, char target)
{
	if(visited_row[c])
		return;
	visited_row[c] = true;
	len++;
	if(c-1>=0 && map[r][c-1]==target)
		dfs_row(r,c-1,target);
	if(c+1<N && map[r][c+1]==target)
		dfs_row(r,c+1,target);
	return;
}

bool visited_col[50];
void dfs_col(int r, int c, char target)
{
	if(visited_col[r])
		return;
	visited_col[r] = true;
	len++;
	if(r-1>=0 && map[r-1][c]==target)
		dfs_col(r-1,c,target);
	if(r+1<N && map[r+1][c]==target)
		dfs_col(r+1,c,target);
	return;
}

int dy[2] = {0,1};
int dx[2] = {1,0};
void solve()
{
	int ans = 0;
	//check orig
	int max_row = 0;
	for(int r = 0 ; r < N ; r++)
	{	
		char prev_color = '.';
		int prev_pos = 0;
		for(int c= 0 ; c < N ; c++)
		{
			char cur_color = map[r][c];
			if(prev_color!=cur_color)
			{
				max_row = max(max_row, c - prev_pos);
				prev_color = cur_color;
				prev_pos = c;
			}
		}
		max_row = max(max_row, N - prev_pos);
	}
	ans = max(ans, max_row);

	int max_col = 0;
	for(int c = 0 ; c < N ; c++)
		{	
			char prev_color = '.';
			int prev_pos = 0;
			for(int r= 0 ; r < N ; r++)
			{
				char cur_color = map[r][c];
				if(prev_color!=cur_color)
				{
					max_col = max(max_col, r - prev_pos);
					prev_color = cur_color;
					prev_pos = r;
				}
			}
			max_col = max(max_col, N - prev_pos);
		}
		
	ans = max(ans, max_col);
	for(int r= 0 ; r < N ; r++)
		for(int c= 0 ;c < N ; c++)
			for(int d= 0 ; d < 2; d ++)
			{
				int ty = r+dy[d];
				int tx = c+dx[d];
				if(ty<N && tx<N && map[r][c]!=map[ty][tx])
				{
					swap(map[r][c], map[ty][tx]);
					dfs_row(r,c,map[r][c]);
					ans = max(ans, len);
					len = 0 ; memset(visited_row,0,sizeof(visited_row));
					dfs_col(r,c,map[r][c]);
					ans = max(ans, len);
					len = 0 ; memset(visited_col,0,sizeof(visited_col));
					dfs_row(ty,tx,map[ty][tx]);
					ans = max(ans, len);
					len = 0 ; memset(visited_row,0,sizeof(visited_row));
					dfs_col(ty,tx,map[ty][tx]);
					ans = max(ans, len);
					len = 0 ; memset(visited_col,0,sizeof(visited_col));
					swap(map[r][c], map[ty][tx]);
				}
			}
	cout<<ans;
}

int main()
{
	input();
	solve();
}