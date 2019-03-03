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

using namespace std;


size_t	climbStairs(int stairs)
{
	if (stairs == 0)
		return 1;

	if (stairs < 0)
		return 0;

	return climbStairs(stairs - 1) + climbStairs(stairs - 2) + climbStairs(stairs - 3);

}


#define XDIM	2
#define YDIM	2

size_t robotPaths(int xPos, int yPos)
{
	if ((xPos == XDIM) && (yPos == YDIM))
		return 1;

	if ((xPos > XDIM) || (yPos > YDIM))
		return 0;

	return robotPaths(xPos + 1, yPos) + robotPaths(xPos, yPos + 1);

}

bool findPath2XY(int xPos, int yPos, bool safeSpace[][XDIM+1], vector<pair<size_t, size_t>>& path2XY)
{
	if ((xPos == XDIM) && (yPos == YDIM))
	{
		path2XY.push_back(make_pair(xPos, yPos));
		return true;
	}

	if ((xPos > XDIM) || (yPos > YDIM))
		return false;

	if (safeSpace[yPos][xPos] == false)
		return false;

	path2XY.push_back(make_pair(xPos, yPos));

	bool foundPath = findPath2XY(xPos + 1, yPos, safeSpace, path2XY) || findPath2XY(xPos, yPos + 1, safeSpace, path2XY);

	if (!foundPath)
		path2XY.pop_back();

	return foundPath;

}

int magicIndex(int *in, int start, int end)
{
	if (end < start)
		return -1;

	int h = start + (end - start) / 2;

	if (in[h] == h)
		return h;

	if (start == end)
		return -1;

	if (in[h] > h)
		return magicIndex(in, start, h - 1);
	else
		return magicIndex(in, h + 1, end);


}

int magicIndexR(int *in, size_t n)
{
	n--;

	if (in[n] == n)
		return n;

	if (in[n] < n)
		return -1;

	return magicIndexR(in, n);
}

void makeOrderedSubsets(vector<set<int>>& subsets, set<int> inputSet)
{
	size_t setLength = inputSet.size();

	for (int i = 1; i <= setLength; i++)
	{
		set<int>::iterator itSet = inputSet.begin();

		while (distance(itSet, inputSet.end()) >= i)
		{
			subsets.push_back(set<int>());

			set<int>::iterator itSet2 = itSet;

			for (int j = 0; j < i; j++)
				subsets[subsets.size() - 1].insert(*itSet2++);

			itSet++;
		}
	}
}

void makeSubsets(vector<set<int>>& subsets, set<int>::iterator& itInputSet, int setLength)
{
	if (setLength == 0)
	{
		subsets.push_back(set<int>());
		return;
	}

	makeSubsets(subsets, itInputSet, setLength - 1);

	int vecLength = subsets.size();

	for (int i = 0; i < vecLength; i++)
	{
		set<int> newSet(subsets[i]);

		newSet.insert(*itInputSet);

		subsets.push_back(newSet);
	}

	itInputSet++;
}

vector<string>* generateStringPermutations(char *inString)
{
	size_t strSize = strlen(inString);

	vector<string> *permuteNchars = new vector<string>();

	(*permuteNchars).push_back(string(inString, 1));

	for (int i = 1; i < strSize; i++)
	{
		int numPermutes = (*permuteNchars).size();

		vector<string> *permuteNplusOne = new vector<string>();

		for (int p = 0; p < numPermutes; p++)
		{
			string curString = (*permuteNchars)[p];

			for (int j = 0; j <= curString.length(); j++)
			{
				string newString(curString, 0, j);
				newString.append(1, inString[i]);
				newString.append(curString, j, curString.length() - j);

				(*permuteNplusOne).push_back(newString);
			}

		}

		delete permuteNchars;

		permuteNchars = permuteNplusOne;

	}

	return permuteNchars;
}

enum PixelColor	{ black, white, red, blue, green, yellow, orange, magenta };

#define SCREENW	16
#define SCREENH	8


void paintFunction(PixelColor *screen, PixelColor originalColor, PixelColor fillColor, int xPos, int yPos)
{
	if ((yPos < 0) || (xPos < 0) || (yPos > SCREENH) || (xPos > SCREENW))
		return;

	if (screen[yPos*SCREENW + xPos] != originalColor)
		return;

	screen[yPos*SCREENW + xPos] = fillColor;

	paintFunction(screen, originalColor, fillColor, xPos, yPos - 1);
	paintFunction(screen, originalColor, fillColor, xPos + 1, yPos);
	paintFunction(screen, originalColor, fillColor, xPos, yPos + 1);
	paintFunction(screen, originalColor, fillColor, xPos - 1, yPos);

}

void showScreen(PixelColor *screen)
{
	for (int h = 0; h < SCREENH; h++)
	{
		for (int w = 0; w < SCREENW; w++)
		{
			printf("%d ", screen[h*SCREENW + w]);
		}

		printf("\n");
	}

}

bool checkSpace(char board[][8], size_t rank, size_t file)
{
	//for (int f = 0; f < 8; f++)
	//{
	//	if (board[rank][f] != NULL)
	//		return false;
	//}

	for (int r = 0; r < 8; r++)
	{
		if (board[r][file] == 'Q')
			return false;
	}

	int r = rank + 1;
	int f = file + 1;

	while ((r < 8) && (f < 8))
	{
		if (board[r++][f++] == 'Q')
			return false;
	}

	r = rank - 1;
	f = file - 1;

	while ((r >= 0) && (f >= 0))
	{
		if (board[r--][f--] == 'Q')
			return false;
	}


	r = rank - 1;
	f = file + 1;

	while ((r >= 0) && (f < 8))
	{
		if (board[r--][f++] == 'Q')
			return false;
	}

	r = rank + 1;
	f = file - 1;

	while ((r < 8) && (f >= 0))
	{
		if (board[r++][f--] == 'Q')
			return false;
	}

	return true;

}

void showBoard(char board[][8])
{
	cout << endl;

	for (int r = 0; r < 8; r++)
	{
		for (int f = 0; f < 8; f++)
		{
			cout << " " << board[r][f];
		}

		cout << endl;
	}

}

bool placeQueens(char board[][8], int rank)
{
	if (rank >= 8)
	{
		static size_t count = 0;

		cout << ++count;

		showBoard(board);

		return placeQueens(board, rank - 1);
	}

	int i;

	for (i = 0; i < 8; i++)
	{
		if (board[rank][i] == 'Q')	// Handle case where we are trying again
		{
			board[rank][i] = '0';

			if (i == 7)
			{
				if (rank == 0)
					return true;

				return placeQueens(board, rank - 1);
			}

			i++;
			break;
		}
	}

	if (i == 8)
		i = 0;

	for (; i < 8; i++)
	{
		if (checkSpace(board, rank, i))
		{
			board[rank][i] = 'Q';
			break;
		}
	}


	if (i < 8)
		return placeQueens(board, rank + 1);	// Go to next rank
	else
		return placeQueens(board, rank - 1);	// Retry previous rank

}

typedef unsigned int uint32;

struct Box
{
	uint32 height;
	uint32 width;
	uint32 depth;

public:
	Box(uint32 h, uint32 w, uint32 d) : height(h), width(w), depth(d) {};

};

class boxComparator
{
public:

	bool operator() (const Box *box1, const Box *box2)
	{
		return box1->height > box2->height;
	}

};


void stackBoxes(stack<Box*>& stackBoxes, vector<Box*> boxes)
{
	multiset<Box*, boxComparator> mapBoxes;

	for (uint32 i = 0; i < boxes.size(); i++)
	{
		mapBoxes.insert(boxes[i]);
	}

	multiset<Box*>::iterator itBoxes = mapBoxes.begin();

	stackBoxes.push(*itBoxes++);

	while (itBoxes != mapBoxes.end())
	{
		Box* top = stackBoxes.top();

		if (top->height == (*itBoxes)->height)
		{
			int maxTop = max(top->width, top->depth);
			int maxNext = max((*itBoxes)->width, (*itBoxes)->depth);

			if (maxNext > maxTop)
			{
				stackBoxes.pop();
				stackBoxes.push(*itBoxes);
			}
		}
		else if ((top->width > (*itBoxes)->width) && (top->depth > (*itBoxes)->depth))
		{
			stackBoxes.push(*itBoxes);
		}

		itBoxes++;
	}

}



int main()
{
	vector<Box*> vBoxes;

	vBoxes.push_back(new Box(3, 6, 4));
	vBoxes.push_back(new Box(13, 6, 4));
	vBoxes.push_back(new Box(13, 8, 5));
	vBoxes.push_back(new Box(2, 3, 9));
	vBoxes.push_back(new Box(7, 8, 9));
	vBoxes.push_back(new Box(11, 8, 19));
	vBoxes.push_back(new Box(33, 16, 14));
	vBoxes.push_back(new Box(3, 2, 3));
	vBoxes.push_back(new Box(22, 22, 22));

	stack<Box*> stackedBoxes;

	stackBoxes(stackedBoxes, vBoxes);

	//char board[8][8];

	//for (int r = 0; r < 8; r++)
	//	for (int f = 0; f < 8; f++)
	//		board[r][f] = '0';


	//placeQueens(board, 0);

	//srand(1);

	//PixelColor screen[SCREENH * SCREENW];

	//for (int i = 0; i < SCREENH * SCREENW; i++)
	//	screen[i] = (PixelColor)((unsigned char)((8 * rand()) / RAND_MAX));

	//screen[38] = black;
	//screen[39] = black;
	//screen[40] = black;
	//screen[56] = black;
	//screen[57] = black;
	//screen[58] = black;

	//showScreen(screen);
	//
	//paintFunction(screen, screen[8 + 1 * SCREENW], magenta, 8, 1);

	//cout << endl;

	//showScreen(screen);

	//vector<string> *permutations = generateStringPermutations("priestess");

	//printf("num permutes = %d\n", (*permutations).size());

	//set<int> setExample;

	//for (int i = 0; i < 5; i++)
	//	setExample.insert(rand());

	//vector<set<int>> subsets;

	//makeSubsets(subsets, setExample.begin(), setExample.size());

	//int array[9] = { -4, -2, 0, 2, 3, 4, 5, 6, 9 };

	//int magic = magicIndex(array, 0, 9);


	//bool safeSpace[YDIM+1][XDIM+1];

	//for (int y = 0; y <= YDIM; y++)
	//	for (int x = 0; x <= XDIM; x++)
	//		safeSpace[y][x] = true;

	//safeSpace[0][1] = false;
	//safeSpace[1][2] = false;

	//vector<pair<size_t, size_t>> path2XY;

	//findPath2XY(0, 0, safeSpace, path2XY);

	//size_t numPaths = robotPaths(0, 0);

	//for (int s = 1; s < 10; s++)
	//{
	//	size_t numWays = climbStairs(s);
	//	printf("Stairs = %d, # ways = %d\n", s, numWays);
	//}

}