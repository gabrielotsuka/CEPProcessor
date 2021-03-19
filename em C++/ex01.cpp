#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main ()  {
  ifstream file("cep.txt");
  string str;
  regex regexp("\t"); 
  while (getline(file, str)) {
    cout << regex_replace(str,regexp , "|") << "\n";
     
  }
}