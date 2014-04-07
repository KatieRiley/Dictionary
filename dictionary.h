/****************************************
Kathryn Hoskins
cs 211
assignment 2

dictionary.h
****************************************/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary
{
 private:
  const int maxWordsInDict;
  const int maxWordsPerFile;
  int totalWordsInDict;
  int numOfWordsInFile[26];
  static bool failure;
  static bool success;
  
 public:
  Dictionary(); //done
  Dictionary(int dictMaxWords, int fileMaxWords); //done
  bool addAWord(string word);  //done
  bool deleteAWord(string word); //done
  bool searchForWord(string word); //done
  bool printAFileInDict(string filename); //done
  bool spellChecking(string fileName); //done
  bool insertWordsIntoDict(string fileName); //done
  void processTransactionFile();
};
#endif
