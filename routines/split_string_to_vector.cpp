#include <string>
#include <vector>

vector<string> split_string_to_vector(string s){
  vector<string> ret;
  string temp;
  for(char c:s){
    if(c==' '){
      ret.push_back(temp);
      temp="";
    }
    else temp+=c;
  }
  ret.push_back(temp);
  return ret;
}
