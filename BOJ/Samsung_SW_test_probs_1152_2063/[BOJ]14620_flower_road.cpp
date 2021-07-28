#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;



int N;
int board[10][10];
int cost_map[10][10];
int cost(int r, int c)
{
	return board[r-1][c] + board[r][c-1]+board[r][c] + board[r][c+1] + board[r+1][c];
}

vector<int> idx2cor(int a)
{
	vector<int> cor = {1,1};
	cor[0] += a/(N-2);
	cor[1] += a%(N-2);
	return cor;
}

int dist(vector<int> a, vector<int> b)
{
	return abs(a[0]-b[0])+abs(a[1]-b[1]);
}

bool is_conflict(vector<int> cor_a, vector<int> cor_b, vector<int> cor_c)
{
	return (dist(cor_a,cor_b) <=2 || dist(cor_b,cor_c) <=2 || dist(cor_c,cor_a) <=2);
}

int main()
{
	cin>>N;
	for(int r = 0 ; r < N ; r++)
		for(int c = 0 ; c < N  ;c++)
			cin>>board[r][c];
	
	for(int r= 1 ; r < N-1 ; r++)
		for(int c= 1 ; c < N-1 ; c++)
			cost_map[r][c] = cost(r,c);
	
	int pos = (N-2) *(N-2);
	vector<int> ind(pos,0);
	fill_n(ind.end()-3,3,1);
	int ans = 1e9;
	do{
		vector<int> idx;
		for(int i = 0 ; i <pos; i++)
			if(ind[i]) idx.push_back(i);
		vector<int> cor_a = idx2cor(idx[0]);
		vector<int> cor_b = idx2cor(idx[1]);
		vector<int> cor_c = idx2cor(idx[2]);

		if(is_conflict(cor_a, cor_b, cor_c))
			continue;
		ans = min(ans, cost_map[cor_a[0]][cor_a[1]] + cost_map[cor_b[0]][cor_b[1]] + cost_map[cor_c[0]][cor_c[1]]);
		
	}while(next_permutation(ind.begin(), ind.end()));
	cout<<ans;
}