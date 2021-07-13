#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,K;
int map[10][10];

int abc[3][20];

void input()
{
    cin>>N>>K;
    for(int r = 1 ; r <=N ; r++)
        for(int c= 1; c <=N; c++)
            cin>>map[r][c];
    for(int i = 1 ; i <=2 ; i++)
        for(int c = 0 ; c <20 ; c++)
            cin>>abc[i][c];
}

void print_abc()
{
    for(int r = 0 ; r <3 ; r++)
        {
        for(int c = 0 ; c <20 ; c++)
            cout<<abc[r][c]<<" ";
        cout<<endl;
        }
    cout<<endl;
}
void print_pan(int pan, int aa,int bb,int cc, int a, int b , int c, int a_hand, int b_hand)
{
    cout<<"at pan : "<<pan<<endl;
    cout<<"user_a : "<< aa<<" user_b : "<<bb<<" user_c :" <<cc<<endl;
    cout<<"a_hand : "<<a_hand<<" b_hand : "<<b_hand<<endl;
    cout<<"winner : "<< a<<" losser : "<<b<<" waiter :" <<c<<endl;
    cout<<endl;
}

void solve()
{
    vector<int> order;
    for(int i = 1 ; i <= N ; i++)
        order.push_back(i);
    
    int answer = 0;
    do{
        int win_cnt[3] = {0,0,0};
        int user_a,user_b,user_c;
        user_a = 0;
        user_b = 1;
        user_c = 2;
        copy(order.begin(), order.end(),&abc[0][0]);
        vector<int> played_pan(3,0);
        // print_abc();

        for(int pan = 1 ; pan <=20 ; pan++)
        {
            int winner, losser, waiter = user_c;
            //user_a vs user_b
            int a_hand = abc[user_a][played_pan[user_a]];
            int b_hand = abc[user_b][played_pan[user_b]];
            played_pan[user_a] +=1;
            played_pan[user_b] +=1;
            
            //tie
            if(map[a_hand][b_hand] == 1)
                {
                    winner = max(user_a,user_b);
                    losser = min(user_a,user_b);
                }
            //a win
            else if(map[a_hand][b_hand] ==2)
                {
                    winner = user_a;
                    losser = user_b;
                }
            
            //b win
            else
                {
                    winner = user_b;
                    losser = user_a;
                }
            win_cnt[winner] +=1;
            
            // print_pan(pan, user_a,user_b,user_c, winner,losser,waiter, a_hand, b_hand);

            user_a = winner;
            user_b = waiter;
            user_c = losser;

            if(win_cnt[0] == K)
            {
                answer = 1;
                break;
            }
            else if(win_cnt[1] == K || win_cnt[2] == K)
                break;
            if(played_pan[0] >= N)
                break;
        }
        if(answer == 1)
            break;
    }while(next_permutation(order.begin(), order.end()));

    cout<<answer;
}

int main()
{
    input();
    solve();
    return 0;
}