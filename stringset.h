/*******************
  Gary Allen
  grallen
  HW 1
  Lab Section: CPSC 2120-003
  Completed On: 9/28/19
*******************/
#ifndef STRINGSET_H /* Prevent multiple inclusion... */
#define STRINGSET_H

#include <string>
using namespace std;

class Stringset {

 private:


 private:

   struct urlStruct {
     string url;
     urlStruct *next;
     int index;
     urlStruct(string u, urlStruct *n, int i) {url = u; next = n; index = i; }
     urlStruct () {url = ""; next = NULL; index = 0;}
   };
   struct wordStruct {
     string word;
     wordStruct *next;
     wordStruct(string w, wordStruct *n) {word = w; next = n;}
     wordStruct() {word = ""; next = NULL;}

   };

  struct Node {
    string key;
    Node *next;
    urlStruct *head;
    wordStruct *wHead;
    int urlcount;
    int wordcount;
    double iweight;
    double nweight;
    Node(string k, Node *n, urlStruct *u, wordStruct *w, double iw, double nw, int uC, int wC) { key = k; next = n; head = u; wHead = w; iweight = iw; nweight = nw; urlcount = uC; wordcount = wC;}
    Node(string k, Node *n) {key = k; next = n; head = NULL; wHead = NULL; iweight = 0; nweight = 0; urlcount = 0; wordcount = 0;}
    Node() { key = ""; next = NULL; head = NULL; wHead = NULL; iweight = 0; nweight = 0; urlcount = 0; wordcount = 0;}
  };




  Node **table;  // main hash table array of new page head pointers
  Node **reversetable; //reverse hash table of words with their links to webpages
  int size;      // size of table, as currently allocated
  int rsize;
  int rnum_elems;
  int num_elems; // number of elements stored in the table

 public:
  Stringset();
  ~Stringset();
  bool find(string key);
  bool rfind(string key);
  void insert(string key);
  void rinsert(string key);
  void initializeWeight(int count);
  void insertURL(string url, string newPage);
  void rinsertURL(string word, string url);
  void insertWord(string word, string newPage);
  void print(void);
  void rprintURLS(string key, int count);
};

#endif
