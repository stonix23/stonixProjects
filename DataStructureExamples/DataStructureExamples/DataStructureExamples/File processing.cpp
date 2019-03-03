#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

bool isPrime(int c)
{
	for (int i = 2; i <= (c / 2); i++)
	{
		if ((c % i) == 0)
			return false;
	}

	return true;

}

void makeMagicChart(char *chart)
{
	char primeChart[256];

	for (int c = 0; c < 256; c++)
	{
		if (isPrime(c))
		{
			primeChart[c] = c;
		}
		else
			primeChart[c] = 0;

	}

	chart[0] = 0;

	for (int c = 1; c < 256; c++)
	{
		if (primeChart[c] != 0)
			chart[c] = c;
		else
		{
			int offset = 0;

			while (++offset)
			{
				if (primeChart[c - offset] != 0)
				{
					chart[c] = primeChart[c - offset];
					break;
				}

				if (primeChart[c + offset] != 0)
				{
					chart[c] = primeChart[c + offset];
					break;
				}
			}
		}

	}

}


void magicWords(vector<string> inWords, char *chart)
{
	for (vector<string>::iterator itWords = inWords.begin(); itWords != inWords.end(); itWords++)
	{
		string magicString(*itWords);

		int i = 0;

		while (magicString[i])
		{
			magicString[i] = chart[magicString[i]];
			i++;
		}

		cout << *itWords << " : " << magicString << endl;
	}


}


int main()
{
	ifstream myfile("c:\\Projects\\ImagesWords.txt");

	if (!myfile)
	{
		cout << "File not found" << endl;
		return 0;
	}

	vector<string> words;

	while (!myfile.eof())
	{
		string newLine;
		getline(myfile, newLine);

		istringstream issLine(newLine);

		string stringWord;

		while (issLine >> stringWord)
		{
			bool isWord = true;

			for (int i = 0; i < stringWord.length(); i++)
			{
				char c = tolower(stringWord[i]);
				if (c < 'a' || c > 'z')
				{
					isWord = false;
					break;
				}
			}

			if (isWord)
				words.push_back(stringWord);

		}
	}

	words.push_back(string("KINGKONG"));

	char magicChart[256];

	makeMagicChart(magicChart);

	magicWords(words, magicChart);

}