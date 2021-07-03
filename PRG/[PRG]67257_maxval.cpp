#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

vector<long long> figs_orig;
vector<char> ops_orig;

vector<long long> figs;
vector<char> ops;

void op(long long idx)
{
    long long fig1 = figs[idx];
    long long fig2 = figs[idx+1];
    
    long long res;
    
    switch (ops[idx]){
        case '*' : {
            res = fig1 * fig2;
            break;
        }
        case '-' :{
            res = fig1 - fig2;
            break;
        }
        case '+' :{
            res = fig1 + fig2;
            break;
        }
            
    }
    figs.erase(figs.begin() + idx);
    figs.erase(figs.begin() + idx);
    figs.insert(figs.begin()+idx, res);
    
    ops.erase(ops.begin()+idx);
}

long long solution(string expression) {
    long long answer = 0;
    figs_orig.clear();
    ops_orig.clear();
    vector<long long> res;
    string fig;
    for(auto c : expression)
    {
        if(c>='0' && c<='9')
            fig+=c;
        else
        {
            figs_orig.push_back(stoi(fig));
            fig.clear();
            ops_orig.push_back(c);
        }
    }
    figs_orig.push_back(stoi(fig));
    char ops_comp[3] = {'*','+','-'};
    do{
        figs = figs_orig;
        ops = ops_orig;
        for(long long op_idx = 0 ; op_idx < 3; op_idx ++)
            {
                for(long long idx = 0 ; idx < ops.size(); idx++)
                {
                    if(ops[idx] == ops_comp[op_idx])
                    {
                        op(idx);
                        idx--;
                    }
                }            
        }
        res.push_back(abs(figs[0]));
    }while(next_permutation(ops_comp,ops_comp+3));
    
    answer = *max_element(res.begin(), res.end());
    return answer;
}

int main()
{
    string expression ="100-200*300-500+20";
    cout<<solution(expression)<<endl;
    string expression2 ="50*6-3*2";
    cout<<solution(expression2)<<endl;

    expression ="50-6*3*2+100";
    cout<<solution(expression)<<endl;

    expression ="200-300-500-600*40+500+500";
    cout<<solution(expression)<<endl;

    expression ="2-990-5+2";
    cout<<solution(expression)<<endl;

    return 0;
}