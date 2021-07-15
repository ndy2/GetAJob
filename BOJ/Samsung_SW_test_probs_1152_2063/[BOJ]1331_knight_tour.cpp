#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool visited[6][6];

int main()
{
    int cur_row, cur_col;
    int prev_row, prev_col;
    int first_row, first_col;
    for(int n = 1 ; n <=36 ; n++)
    {
        string cor;
        cin>>cor;
        cur_row = 5 - (cor[1]-'1') ;
        cur_col = cor[0]-'A';
        if(visited[cur_row][cur_col])
            {
                cout<<"Invalid";
                return 0;
            }
        
        bool valid = false;
        if(n==1)
        {
            first_row = cur_row;
            first_col = cur_col;
            valid = true;
        }
        else if(abs(prev_row - cur_row) * abs(prev_col - cur_col) == 2)
            valid = true;
        
        if(!valid)
        {
            cout<<"Invalid";
            return 0;
        }

        visited[cur_row][cur_col] = true;

        prev_row = cur_row;
        prev_col = cur_col;
        
    }
    if(abs(first_row - cur_row) * abs(first_col - cur_col) == 2)
        cout<<"Valid";
    else
        cout<<"Invalid";
    return 0;
}