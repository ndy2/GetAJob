#include <iostream>

using namespace std;

int main()
{
	int TC;
	cin>>TC;
	for(int tc=1 ; tc<=TC; tc++)
	{
		int N,M;
		cin>>N>>M;
		int a,b;
		for(int i = 0 ; i <M ; i++)
			cin>>a>>b;
		cout<<N-1<<endl;
	}
}