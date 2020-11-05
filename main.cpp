/*******************
  Gary Allen
  grallen117
*******************/
#include <string>
#include <fstream>
#include <iostream>
#include "stringset.h"

using namespace std;

void readtext(void)
{
  Stringset set;
  ifstream fin;
  string s;
  int count = 0;
  fin.open("webpages.txt");
  while (fin >> s) {
    if (s == "NEWPAGE") {
      count++;
      fin>>s;
      set.insert(s);
    }
  }
  fin.close();
  fin.open("webpages.txt");
  string newpage;
  while (fin >> s) {
    if (s == "NEWPAGE") {
      fin >> newpage;
      fin >> s;
    }
    if (s.substr(0, 4) == "http" && set.find(s)) {
        set.insertURL(s, newpage);
    }
    else {
      set.insertWord(s, newpage);
      if (set.rfind(s)) {
        set.rinsertURL(s, newpage);
      }
      else {
        set.rinsert(s);
        set.rinsertURL(s, newpage);
      }
    }
  }
  fin.close();
  set.initializeWeight(count);
  string answer = "";
  cout << "Google Pagerank Algorithm, please enter a word: " << "\n";
   while (cin >> answer) {
     set.rprintURLS(answer, count);
   }
}
int main(void)
{
  readtext();
  return 0;
}
