#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    printf("%d",min(a+d,b+c));
}