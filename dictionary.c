/****************************************
Kathryn Hoskins
cs 211
assignment 2

dictionary.c
****************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

#include "dictionary.h"


bool Dictionary::failure = false;
bool Dictionary::success = true;

//-----------------Dictionary------------------
//default constructor, sets variables to appropriate values
//sets all the values in the array numOfWordsInFile to 0
//
//---------------------------------------------
Dictionary::Dictionary(): maxWordsInDict(10000), maxWordsPerFile(100) 
{
  totalWordsInDict = 0;
  
  for(int i = 0; i < 26; i++)
      numOfWordsInFile[i] = 0;
}

//-----------------Dictionary------------------
//constructor, , sets variables to appropriate val
//sets all the values in the array numOfWordsInFile to 0 
//---------------------------------------------
Dictionary::Dictionary(int dictMaxWords, int fileMaxWords): maxWordsInDict(dictMaxWords), maxWordsPerFile(fileMaxWords)
{
  totalWordsInDict = 0;
  
  for(int i = 0; i < 26; i++)
      numOfWordsInFile[i] = 0;
}

//------------------addAWord-------------------                                           
//looks through the approptiate .txt file to make sure the 
//word is not all ready there, then adds it to the end of the
//file
//
//parameters:
// string -word to add                                 
//---------------------------------------------               
bool Dictionary::addAWord(string word)
{
  char firstChar = toupper(word[0]);
  int firstCharIndex = (int)firstChar - 65;
  string fileName;
  fileName.insert(fileName.begin(), 1, firstChar);
 
  fileName += ".txt";

  ofstream myOutFile;
  myOutFile.open(fileName.data(), ios::app);
  
  //if you can find it in the file already
  if(!searchForWord(word))
    {
      ++totalWordsInDict;
      ++numOfWordsInFile[firstCharIndex];
      
      int howManyWordsInFile = numOfWordsInFile[firstCharIndex];
      
      if(totalWordsInDict < maxWordsInDict && howManyWordsInFile < maxWordsPerFile)
	{
      	  myOutFile << word << " ";
      	  myOutFile.close();
	  return (Dictionary::success);
	}
      else
	{
	  myOutFile.close();
	  cout << "the dictionary is full" << endl;
	  return (Dictionary::failure);
	}
    }
  else
    {
      myOutFile.close();
      return (Dictionary::failure);
    }
  myOutFile.close();
  return (Dictionary::failure);

}

//-----------------deleteAWord-----------------                                           
//looks through the .txt to make sure the word is in the 
//file, then puts the words into an array, deletes the word
//from the array and then puts the remaning words back into
//the .txt file
//
//parameters:
// string -word to be deleted                                 
//---------------------------------------------               
bool Dictionary::deleteAWord(string word)
{
  vector <string> theFileWords;
  char firstChar = toupper(word[0]);
  int firstCharIndex = (int)firstChar - 65;
  string fileName;
  fileName.insert(fileName.begin(), 1, firstChar);

  fileName += ".txt";
  
  ifstream myInFile;
  ofstream myOutFile;
  myInFile.open(fileName.data());

  string temp;
  if (searchForWord(word))
    {
      //filling the vector
      while (myInFile >> temp)
	{
	  theFileWords.push_back(temp);
	}

      myInFile.close();

      myOutFile.open(fileName.data());
      for (int i = 0; i < theFileWords.size(); i++)
	{
	  //looking through the vector for the word to delete
	  if(theFileWords[i] == word)
	    {
     	      --totalWordsInDict;
	      --numOfWordsInFile[firstChar];
     	    }
	  else
	    addAWord(theFileWords[i]);
	}
      
      printAFileInDict(fileName);
      myOutFile.close();
      return (Dictionary::success);
    }
  else
    {
      myOutFile.close();
      cout << "could not find " << word << " in " << fileName << endl;
      return (Dictionary::failure);
    }
  
  return (Dictionary::failure);
}

//---------------searchForWord-----------------   
//searches the .txt file to see if the word is there
//
//parameters:
// string -word          
//---------------------------------------------
bool Dictionary::searchForWord(string word)
{
  char firstChar = toupper(word[0]);
  int firstCharIndex = (int)firstChar - 65;
  string fileName;
  fileName.insert(fileName.begin(), 1, firstChar);

  fileName += ".txt";

  ifstream myInFile;
  myInFile.open(fileName.data());

  string temp;
  while (myInFile >> temp)
    {
      if(temp == word)
	{
    	  myInFile.close();
	  return (Dictionary::success);
	}
    }
  myInFile.close();
  return (Dictionary::failure);
}

//--------------printAFileInDict---------------                    
//prints the .txt file
//
//parameters:
// string -the name of the file to be printed
//---------------------------------------------
bool Dictionary::printAFileInDict(string fileName)
{
  ifstream myInFile;
  myInFile.open(fileName.data());
  int lineCount = 0;
  string temp;

  cout << "Printing " << fileName << endl;
  cout << "******************************" << endl;

  while (myInFile >> temp)
    {
      cout << temp << " ";
      lineCount ++;

      if (lineCount >  4)
	{
	  cout << endl;
	  lineCount = 0;
	}

    }
  cout << endl;
  cout << "******************************" << endl;
  myInFile.close();
  return (Dictionary::success);
}

//----------------spellChecking----------------                                        
//checks the file to see if the words in the file are 
//in the dictionary .txt files
//
//parameters:                                                                              
// string -the name of the file to be searched                                                
//--------------------------------------------- 
bool Dictionary::spellChecking(string fileName)
{
  ifstream myInFile;
  myInFile.open(fileName.data());
  string temp;
  
  if(!myInFile)
    {
      myInFile.close();
      return (Dictionary::failure);
    }

  while(myInFile >> temp)
    {
      if(!searchForWord(temp))
	cout << temp << " is not in the Dictionary" << endl;
    }
  myInFile.close();
  return (Dictionary::success);
}

//------------insertWordsIntoDict--------------                                        
//looks through a file and inserts all of the words into                  
//the appropriate .txt files                                              
//                                                                                       
//parameters:                                                   
// string -the name of the file to be inserted                                                
//--------------------------------------------- 
bool Dictionary::insertWordsIntoDict(string fileName)
{
  ifstream myInFile;
  myInFile.open(fileName.data());
  string temp;

  if(!myInFile)
    {
      myInFile.close();
      return (Dictionary::failure);
    }
  while(myInFile >> temp)
    {
      addAWord(temp);
    }
  myInFile.close();
  return (Dictionary::success);
}

//----------processTransactionFile------------                                        
//reads a file with a command and a word to be processed
//                   
//parameters:                                                                            
// none                                                
//--------------------------------------------- 
void Dictionary::processTransactionFile()
{
  string theFileName;
  cout << "Please enter the name of your Tansaction file: " ;
  cin >> theFileName;

  theFileName = theFileName + ".txt";
  ifstream myInFile;
  myInFile.open(theFileName.data());
  string command, wordToUse;

  if(!myInFile)
      cout << "Could not find file/file does not exist" << endl;

  while(myInFile >> command)
    {
      myInFile >> wordToUse;

      if(command == "AddW")
	{
	  cout << "***********Adding " << wordToUse << "************"  << endl;
	  if (addAWord(wordToUse))
	    cout << wordToUse << " was added" << endl;
	  else 
	    cout << wordToUse << " was NOT added" << endl;
	  cout << "***************************************************" << endl;
	  cout << endl;
	  cout << endl;
	}
      else if(command == "DeleteW")
	{
	  cout << "***********Deleting " << wordToUse << "************"  << endl;
	  if (deleteAWord(wordToUse))
	    cout << wordToUse << " was deleted" << endl;
	  else
	    cout << wordToUse << " was NOT deleted" << endl;
	  cout << "***************************************************" << endl;
	  cout << endl;
          cout << endl;
	}
      else if(command == "PrintF")
	{
	  cout << "***********Printing " << wordToUse << "************"  << endl;
	  printAFileInDict(wordToUse);
	  cout << "****************************************************" << endl;
          cout << endl;
          cout << endl;
	}
      else if(command == "SpellCheck")
	{
	  cout << "***********Spell Checking " << wordToUse << "************"  << endl;
	  spellChecking(wordToUse);
	  cout << "*****************************************************" << endl;
          cout << endl;
          cout << endl;
	}
      else if(command == "InsertF")
	{
	  cout << "***********Inserting " << wordToUse << "************"  << endl;
	  if (insertWordsIntoDict(wordToUse))
	    cout << wordToUse << " was inserted" << endl;
	  cout << "*****************************************************" << endl;
          cout << endl;
          cout << endl;
	}
      else if(command == "SearchW")
	{
	  cout << "***********Searching For " << wordToUse << "************"  << endl;
	  if (searchForWord(wordToUse))
	    cout << wordToUse << " was found in the dictionary" << endl;
	  else
	    cout << wordToUse << " was NOT found in the dictionary" << endl;
	  cout << "*****************************************************" << endl;
          cout << endl;
          cout << endl;
	}
	else
	cout << "Command " << command << " was not found" << endl;
     
      cout << endl;
    }
  myInFile.close();
}
