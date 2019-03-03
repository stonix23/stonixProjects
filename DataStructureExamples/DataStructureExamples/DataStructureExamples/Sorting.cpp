#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <functional> 
#include <ctime> 


using namespace std;
typedef unsigned int uint32;

int generateSeed()
{
	time_t t = time(NULL);
	uint32 seed = (t & 0xFFFFFFFF) ^ (t >> 32);
	seed = ((seed & 0xFFFF) ^ (seed >> 16));
	seed = ((seed & 0xFF) ^ (seed >> 8));

	seed = seed | (seed << 8);

	return seed;
}

int getSortIndex(int maxValue)
{
	int rNum = rand();
	int num = ((double)rNum / (double)RAND_MAX) * maxValue;

	if (num == maxValue)
		num--;

	return num;
}

void quickSort(vector<int>& inV, int start, int end)
{
	cout << start << "," << end << endl;

	if ((end - start) <= 1)
		return;

	int sortIndex = getSortIndex(end - start);
	int sortValue = inV[sortIndex + start];

	int index = start;

	for (int i = index; i < end; i++)
	{
		if (inV[i] <= sortValue)
		{
			int temp = inV[i];
			inV[i] = inV[index];
			inV[index] = temp;
			index++;
		}
	}

	quickSort(inV, start, index);
	quickSort(inV, index, end);

}


void quickSort(int *inV, int vSize)
{
	static int n = 0;

	queue<pair<int, int>> sortQ;

	sortQ.push(make_pair(0, vSize - 1));

	while (!sortQ.empty())
	{
		int start = get<0>(sortQ.front());
		int end = get<1>(sortQ.front());

		int sortValue = inV[end];

//		cout << start << "," << end << " - " << sortValue << "  Sort q = " << sortQ.size() << endl;

		sortQ.pop();

		int index = start;

		for (int i = index; i <= end; i++)
		{
			if (inV[i] <= sortValue)
			{
				if (index != i)
				{
					int temp = inV[i];
					inV[i] = inV[index];
					inV[index] = temp;
				}

				index++;
			}
			n++;
		}

		index--;

		if ((index - start) > 1)
			sortQ.push(make_pair(start, index - 1));

		if ((end - index) > 1)
			sortQ.push(make_pair(index + 1, end));

	}

	cout << " n = " << n << endl;
}


void mergeBintoA(int *aVec, int *bVec, int bSize)
{
	int sortedIndex = bSize * 2 - 1;

	int aIndex = bSize - 1;
	int bIndex = bSize - 1;

	while ((bIndex >= 0) && (aIndex >= 0))
	{
		if (aVec[aIndex] >= bVec[bIndex])
		{
			aVec[sortedIndex] = aVec[aIndex--];
		}
		else
		{
			aVec[sortedIndex] = bVec[bIndex--];
		}

		sortedIndex--;
	}

	while (bIndex >= 0)
		aVec[sortedIndex--] = bVec[bIndex--];

}



#define VECLENGTH 64

int main()
{

	int aVec[VECLENGTH * 2], bVec[VECLENGTH];

	int randSeed = generateSeed();
	srand(randSeed);
	
	for (int i = 0; i < VECLENGTH; i++)
	{
		aVec[i] = rand();
		bVec[i] = rand();
	}

	quickSort(aVec, VECLENGTH);
	quickSort(bVec, VECLENGTH);

	mergeBintoA(aVec, bVec, VECLENGTH);

	int lastNum = 0;
	bool sorted = true;

	for (int i = 0; i < VECLENGTH*2; i++)
	{
		if (aVec[i] < lastNum)
			sorted = false;
	
		cout << aVec[i] << endl;

		lastNum = aVec[i]; 
	}

	cout << "Is sorted? " << sorted << endl;


//	vector<int> sortableInts;
//
//	int randSeed = generateSeed();
//	srand(randSeed);
//
//	for (int i = 0; i < VECLENGTH; i++)
//		sortableInts.push_back(rand());
//
////	quickSort(sortableInts, 0, sortableInts.size());
//	quickSort(sortableInts);
//
//	int lastNum = 0;
//	bool sorted = true;
//
//	for (int i = 0; i < VECLENGTH; i++)
//	{
//		if (sortableInts[i] < lastNum)
//			sorted = false;
//
//		lastNum = sortableInts[i]; 
//	}
//
//	cout << randSeed << ":  Is sorted? " << sorted << endl;

	return 0;
}