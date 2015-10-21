
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

extern string IWlist;
void matchWords(string &matchWord, vector<string> const &inWords, vector<char*> &outWords);


void main()
{
	vector<string> wordList;

	istringstream iss(IWlist);
	string word;
	while (iss >> word)
		wordList.push_back(word);

/*
	string line;
	ifstream inFile ("ImagesWords.txt");
	if (inFile.is_open())
	{
		while ( getline (inFile, line) )
		{

			istringstream iss(line);
			string word;
			while (iss >> word)
				wordList.push_back(word);

		}

	}

	inFile.close();
*/



	vector<char*> matchingList;
	string key;

	while (1)
	{
		cout << "Enter search key:  ";
		cin >> key;

		matchWords(key, wordList, matchingList);

		cout << endl << "Words matched:" << endl;
		for( vector<char*>::const_iterator it = matchingList.begin(); it != matchingList.end(); ++it )
			cout << *it << endl;

		cout << endl;

		matchingList.clear();
	}

//	for( vector<string>::const_iterator it = wordList.begin(); it != wordList.end(); ++it )
//        cout << *it << endl;


  }



void matchWords(string &matchWord, vector<string> const &inWords, vector<char*> &outWords)
{
	int lKey = matchWord.length();

	if (lKey >= 3)
	{
		// get encoding info
		char firstChar = matchWord[0];
		char lastChar = matchWord[lKey-1];

		int lWord = 0;
		for(int i=1; i< lKey-1; i++)
			lWord = lWord*10 + (matchWord[i] - '0');			


		// find matching words
		for( vector<string>::const_iterator it = inWords.begin(); it != inWords.end(); ++it )
		{
			string w = *it;

			if  (w.length() == lWord) 
				if ( (tolower(w[0]) == firstChar) && (w[lWord-1] == lastChar) )
					outWords.push_back((char*)(it->data()));
	
		}
	}
	else

		for( vector<string>::const_iterator it = inWords.begin(); it != inWords.end(); ++it )
		{
			string w = *it;
			
			if  (w == matchWord) 
					outWords.push_back((char*)(it->data()));

		}
}
