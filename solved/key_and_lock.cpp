#include <string>
#include <vector>
#include <iostream>

using namespace std;

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

void print_mat(vector<vector<int>> pl)
{
    for(auto r : pl)
        {
            for(auto c : r)
            {
                cout<<c;
            }
            cout<<endl;
        }
}

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
            vector<int> l (pad, 7);
            vector<int> r (pad, 7);
            l.insert(l.end(), lock[i-pad].begin(), lock[i-pad].end());
            l.insert(l.end(), r.begin(), r.end());
            padded_lock.emplace_back(l);
        }
    }
    return padded_lock;
}

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
    int s = k + l - 1;
    bool debug = false;
    vector<vector<int>> pl = pad(lock, l, k-1);
    vector<vector<int>> pl_save = pl;
    for(int rotate = 0 ; rotate < 360 ; rotate +=90)
    {
            for(int i = 0 ; i < s ; i ++)
                {
                    for (int j = 0 ; j < s ; j++)
                    {
                        int p;
                        for (p = 0 ; p < k ; p++)
                            {
                                for( int q= 0 ; q < k ; q++)
                                {
                                    pl[p+i][q+j] += key[p][q];
                                }
                                
                            }
                        if(is_valid(pl))
                            return true;
                        if (debug)
                            {cout<<"i: "<<i<<" j: "<<j<<endl; 
                            print_mat(pl); 
                            string valid = is_valid(pl)?"valid":"non_valid";
                            cout<<valid<<endl;
                            cout<<"=============="<<endl<<endl;
                             }
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

