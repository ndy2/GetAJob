//https://programmers.co.kr/learn/courses/30/lessons/60059?language=cpp
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//key 시계방향 90도 회전
vector<vector<int>> rotate_cw90(vector<vector<int>> key , int k)
{
    vector<vector<int>> key_90 = vector<vector<int>>(k,vector<int>(k,0));
    for(int j = 0 ; j <k; j ++)
    {
        for(int i = 0 ; i<k ; i++)
        {
            key_90[i][j] = key[j][k-i-1];
        }
    }
    return key_90;
}

//lock의 상하좌우에 pad만큼 7 (dummy)을 덧댐
vector<vector<int>> pad (vector<vector<int>> lock, int l, int pad)
{
    vector<vector<int>> padded_lock;
    int f = l+2*pad;
    for(int i = 0 ; i < f ; i++)
    {
        if(i<pad || i>=l+pad)
            padded_lock.emplace_back(vector<int> (f,7));
        else
        {
            //vector concatinate하는 방식 검색해봄
            vector<int> l (pad, 7);
            vector<int> r (pad, 7);
            l.insert(l.end(), lock[i-pad].begin(), lock[i-pad].end());
            l.insert(l.end(), r.begin(), r.end());
            padded_lock.emplace_back(l);
        }
    }
    return padded_lock;
}

//pl (padded lock) 에 0 혹은 2가 있는지 확인
// 0 : lock의 0가 채워지지 않음
// 2 : lock의 1인공간에 key의 1이 얹어짐
bool is_valid ( vector<vector<int>> pl)
{
    for(auto r : pl)
        for(auto c : r)
            if(c == 0 || c == 2)
                return false;
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    int k = key.size();
    int l = lock.size();
    // pl : padded lock - pad = k-1을 적용
    vector<vector<int>> pl = pad(lock, l, k-1);
    vector<vector<int>> pl_save = pl;
    // s : key가 padded lock의 한 Dimmension에 덮어지는 횟수 
    int s = k + l - 1;
    // 가능한 모든 경우에대한 loop
    for(int rotate = 0 ; rotate < 360 ; rotate +=90)
    {
            for(int i = 0 ; i < s ; i ++)
                {
                    for (int j = 0 ; j < s ; j++)
                    {
                        for (int p = 0 ; p < k ; p++)
                            {
                                for( int q= 0 ; q < k ; q++)
                                {
                                    pl[p+i][q+j] += key[p][q];
                                }
                                
                            }
                        if(is_valid(pl))
                            return true;
                        pl = pl_save;
                    }
                }
        key = rotate_cw90(key,k);
    }
    return false;
}

int main()
{
    vector<vector<int>> key     = {{0,0,0},{1,0,0},{0,1,1}};
    vector<vector<int>> lock    = {{1,1,1},{1,1,0},{1,0,1}};
    
    string ans = solution(key, lock)?"true":"false";
    cout<<ans<<endl;
}

