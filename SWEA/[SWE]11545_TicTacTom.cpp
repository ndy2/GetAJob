#include<string>
#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;



int main()
{
    int N;
    cin>>N;
    int x4 = 4*'X';
    int x3t1 = 3*'X'+'T';
    int o4 = 4*'O';
    int o3t1 = 3*'O'+'T';
    
    int target[4] = {x4,x3t1, o4, o3t1};

    for(int i = 1 ; i <= N ; i++)
    {
        vector<string> b = vector<string>(4,"");
        for(int r = 0 ; r < 4 ; r++)
            cin>>b[r];

        //pos diagonal, neg diagonal, col 1234, row 1234
        vector<int> sum (10,0);
        for(int k = 0 ; k <4 ; k ++)
        {
            sum[0] +=b[k][k];
            sum[1] +=b[k][3-k];

            sum[2] +=b[k][0];
            sum[3] +=b[k][1];
            sum[4] +=b[k][2];
            sum[5] +=b[k][3];

            sum[6] +=b[0][k];
            sum[7] +=b[1][k];
            sum[8] +=b[2][k];
            sum[9] +=b[3][k];
        }

        int k;
        int j;
        for(k=0; k<10;k++)
        {
            for(j = 0 ; j < 4 ;j ++)
            {
                if(sum[k] == target[j])
                    {
                        char winner = j<2?'X':'O';
                        cout<<"#"<<i<<" "<<winner<<" won"<<endl;
                        k = 20;
                    }
            }
        }
        if(k==10)
        {
            for(k= 0 ; k < 4 ; k ++)
            {
                for(int j = 0 ; j < 4 ; j ++)
                {
                    if(b[k][j] == '.')
                    {
                        cout<<"#"<<i<<" Game has not completed"<<endl;
                        j=10; k =10;
                    }
                }
            }
            if(j==4 &&k==4)
                        cout<<"#"<<i<<" Draw"<<endl;
            }
        

    }

}