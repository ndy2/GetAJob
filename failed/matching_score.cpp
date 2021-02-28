#include <string>
#include <vector>
#include <iostream>
#include <map>
#define MAX(A,B) (A)>(B)?(A):(B)
using namespace std;

typedef struct link{
    string link_url;
}link;

typedef struct page{
    string contents;
    string body;
    int base_score;
    float link_score;
    vector<link> links;
}page;

bool is_alpha(char c)
{
    return (c>='a'&&c<='z') || (c>'A' && c<='Z');
}

int get_score(string body, string word)
{
    vector<string> body_words_vec;
    int len = body.size();
    int alpha_start_idx;
    int combo = 0;
    bool first_alpha = true;
    bool first_non_alpha = true;
    for(int i = 0 ; i < len ; i++)
    {
        if( is_alpha(body[i]))
        {
            first_non_alpha = true;
            if(first_alpha)
                {alpha_start_idx = i;
                first_alpha = false;
                }
        }
        else
        {
            first_alpha = true;
            if(first_non_alpha)
            {
                body_words_vec.push_back(body.substr(alpha_start_idx,i - alpha_start_idx ));
                first_non_alpha = false;
            }
            
        }
    }

    if(first_non_alpha)
        body_words_vec.push_back(body.substr( alpha_start_idx, len - alpha_start_idx));

    int word_len = word.length();
    int count = 0;
    int comboo = 0 ;
    for(auto w : body_words_vec)
    {
        if(w.length() == word_len)
        {
            int i;
            for(i = 0 ; i <word_len; i++)
            {
                if( (w[i]!=word[i]) && (abs(w[i]-word[i]) != abs('a'-'A')))
                {
                    break;
                }
            }
            if(i==word_len)
                count ++;
        }

    }

    return count;

}

    
int solution(string word, vector<string> pages) {
    map<string,struct page> my_pages;
    for(auto page : pages)
    {
        string content = page.substr(page.find(" content=") +10,page.find("</head>")-page.find(" content=")-14);
        vector<link> links;

        int pos = 0;
        vector<int> body_idx;
        body_idx.push_back(page.find("<body>")+7);

        

        while(page.find("<a href=",pos) != string::npos)
        {
            link cur_link;
            int link_front_idx = page.find("<a href=",pos);
            int link_end_idx = page.find_first_of('\"',link_front_idx +10);
            int a_frame_end_idx = page.find("</a>",link_front_idx +10);
            cur_link.link_url = page.substr(link_front_idx +9, link_end_idx - link_front_idx-9);
            pos = link_front_idx+9;
            links.push_back(cur_link);

            body_idx.push_back(link_front_idx-1);
            body_idx.push_back(a_frame_end_idx+4);
        }
        body_idx.push_back(page.find("</body")-1);

        int body_number = body_idx.size()/2;
            string body;
            for(int i = 0 ; i <body_number ; i++)
            {
                body += page.substr(body_idx[2*i], body_idx[2*i+1] - body_idx[2*i]);
                // cout<<"body "<<i<<" : "<< page.substr(body_idx[2*i], body_idx[2*i+1] - body_idx[2*i])<<endl;
            }

        struct page this_page;
        this_page.body = body;
        this_page.contents = content;
        this_page.links = links;
        this_page.base_score = get_score(body,word);

        my_pages[content]=this_page;
        cout<<endl;
    }

    for(auto m : my_pages)
    {
        float give = (float)m.second.base_score/ (m.second.links.size());
        for(auto l : m.second.links)
        {
            if(my_pages.find(l.link_url)!= my_pages.end())
                my_pages[l.link_url].link_score +=give;
        }
    }

    float answer;
    int i = 0;
    for(auto m : my_pages)
        {
            answer = MAX(answer , m.second.base_score + m.second.link_score);
        }

    for(auto m : my_pages)
    {
        if (answer == m.second.base_score + m.second.link_score)
            return i;
        i++;
    }
    return -1;
}

int main()
{
    
    string word = "blind";
    vector<string> pages = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", 
    "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", \
    "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"};

    string word2 = "Muzi";
    vector<string> pages2 = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", 
    "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"};
    
    string word3 = "Muzi";
    vector<string> pages3 = {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", 
    "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2\n\n\t^\n</body>\n</html>"};

    vector<string> pages5 =
    {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"};

    pages = 
    {"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"};

    cout<<solution(word,pages)<<endl;
    cout<<"===================="<<endl;
    cout<<solution(word2,pages5)<<endl;

   


}   