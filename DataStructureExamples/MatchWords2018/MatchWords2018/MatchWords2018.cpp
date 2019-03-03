#include<stdlib.h>
#include<stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <queue>


using namespace std;

void matchWords(char *matchKey, vector<string>& wordList, vector<string>& outputList)
{
	string matchString(matchKey);

	size_t keyLength = matchString.length();

	if (keyLength < 3)
	{
		printf("Invalid matching key!\n");
		return;
	}

	char firstChar = tolower(matchKey[0]);
	char lastChar = tolower(matchKey[keyLength - 1]);

	string matchKeyNumber(matchKey, 1, keyLength - 2);

	int matchLength = atoi(matchKeyNumber.data());

	if (matchLength <= 0)
	{
		printf("Invalid matching length!\n");
		return;
	}

	for (vector<string>::iterator iterWords = wordList.begin(); iterWords != wordList.end(); iterWords++)
	{
		string currentWord = *iterWords;
		int currentWordLength = currentWord.length();

		if ((currentWord[0] == firstChar) && (currentWord[currentWordLength - 1] == lastChar) && (currentWordLength == matchLength))
		{
			outputList.push_back(currentWord);
		}

	}


}


void makeWordList(char* inputString, vector<string>& wordList)
{
	string currentWord;

	while (*inputString != NULL)
	{
		char currentChar = tolower(*inputString++);

		if (currentChar >= 'a' && currentChar <= 'z')
		{
			currentWord.append(1, currentChar);
		}
		else
		{
			if (currentWord.length() != 0)
			{
				wordList.push_back(currentWord);
				currentWord.clear();
			}

		}

	}

	// remove repeats

	for (int i = 0; i < wordList.size(); i++)
	{
		for (int j = i + 1; j < wordList.size(); j++)
		{
			if (!strcmp(wordList[i].data(), wordList[j].data()))
			{
				wordList[j] = wordList[wordList.size() - 1];
				wordList.pop_back();
				j--;  // re-check this position if the word we just swapped in is also a match
			}
		}
	}

}


// A comparator function used by qsort 
int qSortCompare(const void * a, const void * b)
{
	return (int)(*(char*)a - *(char*)b);
}

void groupAnagrams(vector<string>& inWords)
{
	vector<string> sortedLetters;

	for (vector<string>::iterator itWords = inWords.begin(); itWords != inWords.end(); itWords++)
	{
		string sortedWord(itWords->data());
		int wordLength = itWords->size();

		qsort((void*)sortedWord.data(), wordLength, sizeof(char), qSortCompare);

		sortedLetters.push_back(sortedWord);

	}

	int numWords = inWords.size();

	for (int i = 0; i < numWords; i++)
	{
		const char *pWord = sortedLetters[i].data();

		int index = i + 1;

		for (int j = i + 1; j < numWords; j++)
		{
			if (!strcmp(pWord, sortedLetters[j].data()))
			{
				string swapWord(inWords[index]);
				inWords[index] = inWords[j];
				inWords[j] = swapWord;

				cout << inWords[index - 1] << ", " << inWords[index] << endl;

				swapWord = sortedLetters[index];
				sortedLetters[index] = sortedLetters[j];
				sortedLetters[j] = swapWord;

				index++;
				i++;
			}
		}

	}

}

void groupAnagramsHash(vector<string> &wordList)
{
	unordered_map<string, list<string>> anagramTable;

	for (int i = 0; i < wordList.size(); i++)
	{
		string iWord(wordList[i]);

		qsort((void*)iWord.data(), iWord.size(), 1, qSortCompare);

		if (anagramTable.find(iWord) == anagramTable.end())
		{
			anagramTable[iWord] = list<string>();
		}
		
		anagramTable[iWord].push_back(wordList[i]);
	}

	wordList.clear();

	for (unordered_map<string, list<string>>::iterator itTable = anagramTable.begin(); itTable != anagramTable.end(); itTable++)
	{
		if (itTable->second.size() > 1)
		{
			for (list<string>::iterator itList = itTable->second.begin(); itList != itTable->second.end(); itList++)
				wordList.push_back(itList.operator*());
		}
	}

}

void printLastKLines(FILE * fileHandle, int k)
{
	queue<string> lineQ;

	char lineBuffer[1024];

	int i = 0;

	while (1)
	{
		char c = fgetc(fileHandle);
		if (c == EOF)
			break;

		if (c == '\n')
		{
			lineBuffer[i] = NULL;

			lineQ.push(string(lineBuffer));

			if (lineQ.size() > k)
				lineQ.pop();

			i = 0;
			continue;
		}

		lineBuffer[i++] = c;
	}

	while (!lineQ.empty())
	{
		cout << lineQ.front() << endl;
		lineQ.pop();
	}

}


int main()
{
	FILE *fileHandle;

	if ((fileHandle = fopen("ImagesWords.txt", "r")) == NULL)
	{
		printf("File not found!\n");
		return 0;
	}

	printLastKLines(fileHandle, 100);

	fseek(fileHandle, 0, SEEK_END);
	size_t fileLength = ftell(fileHandle);

	char *words = new char[fileLength + 1];

	rewind(fileHandle);
	fread(words, fileLength, 1, fileHandle);
	words[fileLength] = NULL;

	vector<string> wordList;
	makeWordList(words, wordList);

	delete words;

	groupAnagramsHash(wordList);

	while (1)
	{
		printf("Enter keyword to match:");

		char matchKey[32];
		scanf("%s", matchKey);

		vector<string> matchedWords;
		matchWords(matchKey, wordList, matchedWords);

		printf("Matched words:\n\n");

		for (vector<string>::iterator iterWords = matchedWords.begin(); iterWords != matchedWords.end(); iterWords++)
			printf("%s\n", (*iterWords).data());

	}


	fclose(fileHandle);

	return 0;
}