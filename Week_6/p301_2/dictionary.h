#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
using namespace std;

const int MAXWORDS = 100;

struct WordPair {
    string eng;
    string kor;
};

class MyDic {
    WordPair words[MAXWORDS];
    int nWords = 0;
public:
    void add(string eng, string kor);
    void load(string filename);
    void store(string filename);
    void print();
    string getEng(int id);
    string getKor(int id);
};

#endif