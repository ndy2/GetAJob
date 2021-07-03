#include <string>
#include <vector>
#include <iostream>

using namespace std;

string step1(string new_id){
    int l = new_id.size();
    for(int i = 0 ; i < l ; i ++)
        if('A'<=new_id[i] && new_id[i]<='Z')
            new_id[i] = new_id[i]- ('A'-'a');
    return new_id;
}

string step2(string new_id){
    string n;

    int l = new_id.size();
    for(int i = 0 ; i < l ; i ++)
        if( (('a'<=new_id[i] && new_id[i]<='z') || ('0'<=new_id[i] && new_id[i]<='9') || new_id[i] == '-' ||new_id[i] == '_' || new_id[i] == '.' ))
            n.push_back(new_id[i]);
    return n;
}

string step3(string new_id){
    string n;
    int combo = 0 ;
    vector<int> track; 
    int l = new_id.size();
    for(int i = 0 ; i < l ; i ++)
        if( new_id[i] == '.' )
            {
                if(combo == 0)
                    track.emplace_back(i);
                combo ++;
            }
        else
        {
            combo = 0;
            track.emplace_back(i);
        }

    for(auto c : track)
        n.push_back(new_id[c]);
    return n;
}


string step4(string new_id){
    string n;
    int l = new_id.size();
    if(new_id[0] == '.')
    {
        if(new_id[l-1] =='.')
            n = new_id.substr(1,l-2);
        else
            n = new_id.substr(1,l-1);
    }
    else if(new_id[l-1] =='.')
    {
            n = new_id.substr(0,l-1);
    }
    else
            n = new_id;
    return n;
}

string step5(string new_id){
    if(new_id.empty())
        return "a";
    return new_id;
}

string step6(string new_id){
    if(new_id.size()>=16)
        if(new_id[14] != '.')
            return new_id.substr(0,15);
        else
            return new_id.substr(0,14);
    return new_id;
}

string step7(string new_id){
    int l = new_id.size();
    if(l==1)
        {
           new_id.push_back(new_id[l-1]);
           new_id.push_back(new_id[l-1]); 
        }
    else if(l==2)
        new_id.push_back(new_id[l-1]);
    return new_id;
}



string solution(string new_id ) {
    bool debug = 1;
    string answer ;
    answer = step1(new_id);
    if(debug) cout<<"step1   "<<answer<<endl;

    answer = step2(answer);
    if(debug) cout<<"step2   "<<answer<<endl;

    answer = step3(answer);
    if(debug) cout<<"step3   "<<answer<<endl;

    answer = step4(answer);
    if(debug) cout<<"step4   "<<answer<<endl;

    answer = step5(answer);
    if(debug) cout<<"step5   "<<answer<<endl;

    answer = step6(answer);
    if(debug) cout<<"step6   "<<answer<<endl;

    answer = step7(answer);
    if(debug) cout<<"step7   "<<answer<<endl;

    return answer;
}

int main()
{
    string new_id1= "...!@BaT#*..y.abcdefghijklm";
    string new_id2= "z-+.^.";
    string new_id3= "=.=";
    string new_id4= "123_.def";
    string new_id5= "abcdefghijklmn.p";
    cout<<solution(new_id4)<<endl;

    cout<<solution(new_id5)<<endl;
}