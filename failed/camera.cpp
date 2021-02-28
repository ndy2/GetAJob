#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

bool sortFunc(vector<int>&p1, vector<int>&p2)
	{return p1[2] < p2[2];}

bool sortFunc2(vector<int>&p1, vector<int>&p2)
	{return p1.size() < p2.size();}

void sort_to(vector<vector<int>> routes)
{
	 sort(routes.begin(), routes.end(), sortFunc);
}

void sort_size2(vector<vector<int>> routes)
{
	 sort(routes.begin(), routes.end(), sortFunc2);
}

int solution(vector<vector<int>> routes) {
	int len = routes.size();
	vector<int> list;
	vector<vector<int>> indice;
	sort_to(routes);
	for (int i = 0; i<len ; i++)
	{
		vector<int> idx;
		for (int j = 0; j<i ; j++)
			if(routes[j][1]>routes[i][0])
				 idx.push_back(j);
		idx.push_back(i);
		for (int j = i+1; j<len ; j++)
			if(routes[j][0]<routes[i][1])
				 idx.push_back(j);
		indice.push_back(idx);
	}
	sort_size2(indice);
	int count = 0;
	set <int> s;
	while(s.size()!= len)
	{
		vector<int> popped = indice.back();
		indice.pop_back();
		for (auto i : popped)
			s.insert(i);
		count ++;
	}


    return count;
}

int main()
{
	vector<vector<int>> routes = {{2,2},{0,1},{-10,9}};
	cout<<solution(routes)<<endl;
}