#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int TC;
    cin>>TC;
    for(int tc =1 ; tc<=TC; tc++)
    {
        int a,b;
        cin>>a>>b;
        if(a>=10 || b>=10)
            printf("#%d -1\n",tc);
        else
            printf("#%d %d\n",tc,a*b);
    }    
}