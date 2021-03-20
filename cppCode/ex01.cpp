#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main ()  {
  ifstream file("cep.txt");
  string str;
  string delimiter = "\t";

  regex regexp("\t"); 

  while (getline(file, str)) {
  
    size_t pos = 0;
    vector<std::string> userInfo {};

    while ((pos = str.find(delimiter)) != string::npos) {
      string token;
      token = str.substr(0, pos);
      str.erase(0, pos + delimiter.length());
      cout << token << "\n";
      userInfo.push_back(token);
    }

     for (int i = userInfo.size() -1 ; i >= 0 ; i--)
        std::cout << userInfo[i] << "|";



    cout << regex_replace(str,regexp , "|") << "\n";
     
  }
}