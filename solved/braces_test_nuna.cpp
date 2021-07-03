#include <string>
#include <vector>

using namespace std;

//올바른 괄호 문자열 확인
bool check(string p) {
    int cnt = 0;
    for (int i = 0; i < p.length(); i++) {
        if (p.substr(i, 1).compare("(")) {
            cnt--;
        }
        else {
            cnt++;
        }
        if (cnt < 0) {
            return false;
        }
    }
    if (cnt == 0) {
        return true;
    }
    return false;
}

string process(string p) {
    if (p.length()==0) {
        return p;
    }
    int cnt = 0;
    string u = "", v = "";
    for (int i = 0; i < p.length(); i++) {
        u.append(p.substr(i, 1));
        if (p.substr(i, 1).compare(")")) {
            cnt++;
        }
        else {
            cnt--;
        }
        if (cnt == 0) {
            v = p.substr(i + 1, p.length() - i);
            break;
        }
    }
    if (check(u) == true) {
        return u.append(process(v));
    }
    else {
        string n_s = "(";
        n_s.append(process(v));
        n_s.append(")");
        for (int i = 1; i < u.length()-1; i++) {
            string n_o = u.substr(i, 1);
            if (n_o == ")") {
                n_o = "(";
            }
            else {
                n_o = ")";
            }
            n_s.append(n_o);
        }
        return n_s;
    }
}

string solution(string p) {
    if (check(p) == true) {
        return p;
    }

    return  process(p);
}