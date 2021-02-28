#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct p{
    string cjp;
    string bf;
    string js;
    string cp;
    int score;
}p;

vector<p> info_to_ps(vector<string> info)
{
    vector<p> ps;
    int idx1, idx2, idx3, idx4, idx5, idx6;
    for(auto i : info)
    {
        p pe ;
        idx1 = 0;
        idx2 = i.find(' ',idx1+1)+1;
        idx3 = i.find(' ',idx2+1)+1;
        idx4 = i.find(' ',idx3+1)+1;
        idx5 = i.find(' ',idx4+1)+1;
        idx6 = i.length(); 
    
        pe.cjp = i.substr(idx1, idx2-idx1-1);
        pe.bf = i.substr(idx2, idx3-idx2-1);
        pe.js = i.substr(idx3, idx4-idx3-1);
        pe.cp = i.substr(idx4, idx5-idx4-1);
        pe.score = stoi(i.substr(idx5, idx6-idx5));

        ps.emplace_back(pe);
        
    }
    return ps;
}

vector<int> query_process(vector<p> ps, vector<string> query)
{
    vector<int> answer;
    
    for(auto q: query)
    {

    int idx1, idx2, idx3, idx4, idx5, idx6, idx7;
    int ans= 0;
    idx1 = 0;
    idx2 = q.find("and ",idx1+1)+4;
    idx3 = q.find("and ",idx2+1)+4;
    idx4 = q.find("and ",idx3+1);
    idx5 = q.find(" ",idx4+1)+1;
    idx6 = q.find(" ",idx5+1)+1;
    idx7 = q.length(); 

    string cjp = q.substr(idx1, idx2-idx1-5);
    string bf = q.substr(idx2, idx3-idx2-5);
    string js = q.substr(idx3, idx4-idx3-1);
    string cp = q.substr(idx5, idx6-idx5-1); 
    string ss = q.substr(idx6, idx7-idx6);
    if(ss =="-") ss = "0";
    int s = stoi(q.substr(idx6, idx7-idx6));

    int l = ps.size();
    vector<int> search_idx ;
    vector<int> search_idx_new1 ;
    vector<int> search_idx_new2 ;
    vector<int> search_idx_new3 ;
    vector<int> search_idx_new4 ;
    vector<int> search_idx_new5 ;

    for(int i = 0 ; i < l ; i ++)
        search_idx.emplace_back(i);
    
    for(auto idx : search_idx)
    {   if(cjp != "-" )
           {if(cjp == ps[idx].cjp)
                search_idx_new1.emplace_back(idx);
                } 
        else 
            search_idx_new1 = search_idx;
    }
    for(auto idx : search_idx_new1)
    {   if(bf != "-" )
             {if(bf == ps[idx].bf)
                search_idx_new2.emplace_back(idx);} 
        else
          search_idx_new2 = search_idx_new1;

    }
    for(auto idx : search_idx_new2)
    {   if(js != "-" )
               {  if(js == ps[idx].js)
            search_idx_new3.emplace_back(idx);} 
        else
          search_idx_new3 = search_idx_new2;
    }
    for(auto idx : search_idx_new3)
    {   if(cp != "-" )
                { if(cp == ps[idx].cp)
            search_idx_new4.emplace_back(idx);} 
        else
          search_idx_new4 = search_idx_new3;
    }
    for(auto idx : search_idx_new4)
    {   if(ss != "-" )
            { if( ps[idx].score >= s)
            search_idx_new5.emplace_back(idx);} 
        else
          search_idx_new5 = search_idx_new4;
    }

    answer.emplace_back(search_idx_new5.size());
}
    return answer;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    vector<p> ps = info_to_ps(info);
    return query_process(ps,query);
}

int main()
{
    vector<string> info = {"java backend junior pizza 150",
                            "python frontend senior chicken 210",
                            "python frontend senior chicken 150",
                            "cpp backend senior pizza 260",
                            "java backend junior chicken 80",
                            "python backend senior chicken 50"};
    vector<string> query = {"java and backend and junior and pizza 100",
                            "python and frontend and senior and chicken 200",
                            "cpp and - and senior and pizza 250",
                            "- and backend and senior and - 150",
                            "- and - and - and chicken 100",
                            "- and - and - and - 150"};
    
    vector<int> answer = solution(info, query);

    for(auto a : answer)
        cout<<a<<" ";
}