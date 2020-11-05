/*******************
  Gary Allen
  grallen
  HW 1
  Lab Section: CPSC 2120-003
  Completed On: 9/28/19
*******************/
#include <iostream>
#include <string.h>
#include <assert.h>
#include "stringset.h"

using namespace std;

/* Return a hash for the string s in the range 0..table_size-1 */
int myhash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

Stringset::Stringset()
{
  size = 4; // initial size of word table
  table = new Node *[size]; // allocate table, initialize head ptrs all to NULL
  for (int i=0; i<size; i++)
    table[i] = NULL;
  num_elems = 0;
  rsize = 4;
  reversetable = new Node *[rsize]; // allocate table, initialize head ptrs all to NULL
  for (int i=0; i<size; i++)
    reversetable[i] = NULL;
  rnum_elems = 0;
}

Stringset::~Stringset()
{
  //first get rid of word table
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Node *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;

  for (int i=0; i<rsize; i++) {
    while (reversetable[i] != NULL) {
      Node *temp = reversetable[i];
      reversetable[i] = reversetable[i]->next;
      delete temp;
    }
  }
  delete[] reversetable;
  //then get rid of URL table

}

/* Return true if key is in the set */
bool Stringset::find(string key)
{
  int h = myhash(key, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}
bool Stringset::rfind(string key)
{
  int h = myhash(key, rsize);
  Node *n = reversetable[h];
  while (n != NULL) {
    if (n->key == key) return true;
    n = n->next;
  }
  return false;
}
void Stringset::insertURL(string url, string newPage) {

  int h = myhash(newPage, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == newPage) {
        n->head = new urlStruct(url, n->head, myhash(url, size));
        n->urlcount++;
        break;
    }
    n = n->next;
  }
}

void Stringset::rinsertURL(string word, string url) {
    int h = myhash(word, rsize);
    Node *n = reversetable[h];
    while (n != NULL) {
      if (n->key == word) {
          n->head = new urlStruct(url, n->head, 0);
          n->urlcount++;
          break;
          if (word == "olympiad") {
            cout << "inserting " << url << " at word OLYMPIAD" << "\n";
          }
      }
      n = n->next;
    }
  }
void Stringset::insertWord(string word, string newPage) {
  int h = myhash(newPage, size);
  Node *n = table[h];
  while (n != NULL) {
    if (n->key == newPage) {
        n->wHead = new wordStruct(word, n->wHead);
        n->wordcount++;
        break;
    }
      n = n->next;
  }
}
void Stringset::initializeWeight(int count) {
  double weight;
  for ( int i = 0; i < size; i ++) {
    Node *temp = table[i];
    while (temp != NULL) {
      temp-> iweight = 1.0 / ((double) count);
      weight = weight + temp->iweight;
      temp = temp->next;
    }
  }
  //repeat 50 times
  for (int l = 0; l < 50; l++) {
    //for each page I
    for (int i = 0; i < size; i++) {
      //loop through hash table at each index
      Node *tempi = table[i];
      //while temp is not null
      while (tempi != NULL) {
        //do the arithmetic for that temp and move it forward
        tempi->nweight = ((0.1) / count);
        tempi = tempi->next;
      }
    }
    for (int j = 0; j < size; j++) {
      Node *tempj = table[j];
      while (tempj != NULL) {
        urlStruct * tempurl = tempj->head;
        while (tempurl != NULL) {
          Node *findpage = table[tempurl->index];
          while (findpage->key != tempurl->url) {
            findpage = findpage -> next;
          }
          findpage->nweight += (((double) (0.9) * tempj->iweight) / tempj->urlcount);
          tempurl = tempurl->next;
        }
        tempj = tempj-> next;
      }
    }
    for (int m = 0; m < size; m++) {
      Node *tempj = table[m];
      while (tempj != NULL) {
        tempj->iweight = tempj->nweight;
        tempj = tempj->next;
      }
    }
  }
  weight = 0;
  for ( int i = 0; i < size; i ++) {
    Node *temp = table[i];
    while (temp != NULL) {
      temp-> iweight = temp->nweight;
      weight = weight + temp->iweight;
      temp = temp->next;
    }
  }
}
void Stringset::insert(string key)
{
  num_elems++;
  if (num_elems == size) {
    size *= 2;
    Node **new_table = new Node*[size];
for(int i =0; i<size;i++)
{
  new_table[i] = NULL;
}
    // Transfer all elements from old_table into table
    for (int i=0; i<size/2; i++) {
      while (table[i] != NULL) {
          Node *n = table[i];
	        int h = myhash(n->key, size);
	        new_table[h] = new Node(n->key, new_table[h], n->head, n->wHead, n->iweight, n->nweight, n->urlcount, n->wordcount);
	        table[i] = table[i]->next;
	        delete n;
      }
    }
    // De-allocate old_table
    delete [] table;
    table = new_table;
  }
  int h = myhash(key, size);
  table[h] = new Node(key, table[h]);
}
void Stringset::rinsert(string key)
{
  rnum_elems++;
  if (rnum_elems == rsize) {
    rsize *= 2;
    Node **new_table = new Node*[rsize];
    for(int i =0; i<rsize;i++)
    {
      new_table[i] = NULL;
    }
    // Transfer all elements from old_table into table
    for (int i=0; i<rsize/2; i++) {
      while (reversetable[i] != NULL) {
          Node *n = reversetable[i];
	        int h = myhash(n->key, rsize);
	        new_table[h] = new Node(n->key, new_table[h], n->head, n->wHead, n->iweight, n->nweight, n->urlcount, n->wordcount);
	        reversetable[i] = reversetable[i]->next;
	        delete n;
      }
    }
    // De-allocate old_table
    delete [] reversetable;
    reversetable = new_table;
  }
  int h = myhash(key, rsize);
  reversetable[h] = new Node(key, reversetable[h]);
}
void Stringset::print(void)
{
  //initialize current to NULL
  Node * current = NULL;
  //loop for the size of the hash table
  for (int i = 0; i < size; i++) {
    //set current equal to head of position i of hash table
    current = table[i];
    //while current is not NULL, meaning it has not reached the end of hash
    //table
    while (current != NULL) {
      //print current key
      cout << current->key << "\n";
      //send current onwards down the LL until it reaches NULL, then restart
      current = current -> next;
    }
  }
}
void Stringset::rprintURLS(string key, int count)
{
  int h = myhash(key, rsize);
  Node *n = reversetable[h];
  urlStruct *temp;
  while (n != NULL) {
    if (n->key == key) break;
    n = n->next;
  }
  temp = n->head;
  for (int i = 0; i < n ->urlcount; i++) {
    int z = myhash(temp->url, size);
    Node *b = table[z];
    while (b != NULL) {
      if (b->key == temp->url) break;
      b = b->next;
    }
    cout << (int)(b->iweight * 100 * count ) << " " << temp->url << "\n";
    temp = temp->next;
  }
}
