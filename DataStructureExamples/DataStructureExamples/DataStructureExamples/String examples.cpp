#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <queue>
#include <iostream>
#include <Windows.h>

using namespace std;

bool uniqueChars(char *inputString)
{

	bool asciiChart[256];

	memset(asciiChart, 0, 256);

	int i = 0;

	while (inputString[i] != NULL)
	{
		unsigned char index = (unsigned char)(inputString[i]);

		if (asciiChart[index] != false)
			return false;

		asciiChart[index] = true;

		i++;

	}

	return true;

}

void reverseString(char *in)
{
	int l = strlen(in);

	for (int i = 0; i < (l / 2); i++)
	{
		char temp = in[i];
		in[i] = in[l - i - 1];
		in[l - i - 1] = temp;
	}

}

bool isPermutation(char *aStr, char *bStr)
{
	int aLen = strlen(aStr);
	int bLen = strlen(bStr);

	if (aLen != bLen)
		return false;

	char *bCopy = new char[bLen + 1];
	memcpy(bCopy, bStr, bLen + 1);

	bool isPermutation = true;

	for (int i = 0; i < aLen; i++)
	{ 
		char c = aStr[i];

		bool found = false;

		for (int j = 0; j < bLen; j++)
		{
			if (bCopy[j] == c)
			{
				found = true;
				bCopy[j] = 255;

				break;
			}
		}

		if (!found)
		{
			isPermutation = false;
			break;
		}

	}

	delete bCopy;

	return isPermutation;

}


void pushChar(std::queue<char>& charQ, char *in, int& readIndex, bool& foundNull)
{
	if ((in[readIndex] != NULL) && (!foundNull))
		charQ.push(in[readIndex++]);
	else
		foundNull = true;
}

void replaceSpaces(char *in)
{
	std::queue<char> charQ;

	int readIndex = 0;
	int writeIndex = 0;

	bool foundNull = false;

	charQ.push(in[readIndex++]);

	while (!charQ.empty())
	{
		char c = charQ.front();
		charQ.pop();

		if (c == ' ')
		{
			pushChar(charQ, in, readIndex, foundNull);
			pushChar(charQ, in, readIndex, foundNull);
			pushChar(charQ, in, readIndex, foundNull);

			in[writeIndex++] = '%';
			in[writeIndex++] = '2';
			in[writeIndex++] = '0';
		}
		else
		{
			pushChar(charQ, in, readIndex, foundNull);

			in[writeIndex++] = c;
		}

	}

	in[writeIndex] = NULL;

}

void compressString(char *in)
{
	unsigned int l = strlen(in);

	char *compString = new char[l*2];		// worst case, no characters are repeated, i.e r1e1p1e1a1t1e1d1

	unsigned int origIndex = 0;
	unsigned int newIndex = 0;

	char currentChar = in[origIndex++];
	unsigned int currentCount = 1;

	while (in[origIndex] != NULL)
	{
		char c = in[origIndex++];

		if (c == currentChar)
			currentCount++;
		else
		{
			compString[newIndex++] = currentChar;
			compString[newIndex++] = '0' + currentCount;

			currentChar = c;
			currentCount = 1;
		}
	}

	compString[newIndex++] = currentChar;
	compString[newIndex++] = '0' + currentCount;
	compString[newIndex] = NULL;

	printf("New string:  %s\n", compString);
	printf("Old length = %d, new length = %d\n", l, newIndex);

	if (newIndex < l)
	{
		printf("Copying compressed string\n");
		memcpy(in, compString, newIndex + 1);
	}

	delete compString;

}

void set2Zero(char *bmArray, int h, int w)
{
	queue<int> zeroRows;
	queue<int> zeroColumns;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j+=3)
		{
			if (bmArray[i*w + j] == 78)
			{
				zeroColumns.push(j);
				zeroRows.push(i);
			}
		}
	}

	while (!zeroRows.empty())
	{
		int r = zeroRows.front();
		zeroRows.pop();

		memset((void*)&bmArray[w*r], 0, w);
	}

	while (!zeroColumns.empty())
	{
		int c = zeroColumns.front();
		zeroColumns.pop();

		for (int i = 0; i < h; i++)
			bmArray[i*w + c] = 0;
	}

}


void rotateBitmap(char *filename)
{
	FILE *fileHandle = NULL;

	if ((fileHandle = fopen(filename, "rb")) == NULL)
	{
		printf("File not found!\n");
		return;
	}

	BITMAPFILEHEADER bmHeader;
	BITMAPINFO bmInfo;

	fread((char *)&bmHeader, sizeof(BITMAPFILEHEADER), 1, fileHandle);

	fread((char *)&bmInfo, sizeof(BITMAPINFO), 1, fileHandle);

	fseek(fileHandle, bmHeader.bfOffBits, SEEK_SET); // set the pointer to start reading the bmp data  

	unsigned int bmHeight, bmWidth, bmDepth, bmSize;

	bmHeight = bmInfo.bmiHeader.biHeight;
	bmWidth = bmInfo.bmiHeader.biWidth;
	bmDepth = bmInfo.bmiHeader.biBitCount / 8;
	bmSize = bmInfo.bmiHeader.biSizeImage;

	if ((bmDepth != 3) || (bmHeight != bmWidth))
	{
		printf("We're fucked\n");
		return;
	}

	char *bmArray = new char[bmSize];

	size_t result = fread(bmArray, 1, bmSize, fileHandle);
	fclose(fileHandle);

	set2Zero(bmArray, bmHeight, 3*bmWidth);

	/*
	char valRight0, valBottom0, valLeft0, valRight1, valBottom1, valLeft1, valRight2, valBottom2, valLeft2;
	unsigned int left, right;

	left = 0;
	right = bmWidth;
	
	while (left < right)
	{
		for (int i = left; i < (right - 1); i++)
		{
			valRight0 = bmArray[3 * (i * bmWidth + right - 1)];
			valRight1 = bmArray[3 * (i * bmWidth + right - 1) + 1];
			valRight2 = bmArray[3 * (i * bmWidth + right - 1) + 2];

			bmArray[3 * (i * bmWidth + right - 1)] = bmArray[3 * (left * bmWidth + i)];
			bmArray[3 * (i * bmWidth + right - 1) + 1] = bmArray[3 * (left * bmWidth + i) + 1];
			bmArray[3 * (i * bmWidth + right - 1) + 2] = bmArray[3 * (left * bmWidth + i) + 2];

			valBottom0 = bmArray[3 * (right * bmWidth - i - 1)];
			valBottom1 = bmArray[3 * (right * bmWidth - i - 1) + 1];
			valBottom2 = bmArray[3 * (right * bmWidth - i - 1) + 2];

			bmArray[3 * (right * bmWidth - i - 1)] = valRight0;
			bmArray[3 * (right * bmWidth - i - 1) + 1] = valRight1;
			bmArray[3 * (right * bmWidth - i - 1) + 2] = valRight2;

			valLeft0 = bmArray[3 * ((bmWidth - 1 - i) * bmWidth + left)];
			valLeft1 = bmArray[3 * ((bmWidth - 1 - i) * bmWidth + left) + 1];
			valLeft2 = bmArray[3 * ((bmWidth - 1 - i) * bmWidth + left) + 2];

			bmArray[3 * ((bmWidth - 1 - i) * bmWidth + left)] = valBottom0;
			bmArray[3 * ((bmWidth - 1 - i) * bmWidth + left) + 1] = valBottom1;
			bmArray[3 * ((bmWidth - 1 - i) * bmWidth + left) + 2] = valBottom2;

			bmArray[3 * (left * bmWidth + i)] = valLeft0;
			bmArray[3 * (left * bmWidth + i) + 1] = valLeft1;
			bmArray[3 * (left * bmWidth + i) + 2] = valLeft2;
		}

		left++;
		right--;
	}

	*/

//	FILE *fileOut = fopen("InWrotated.bmp", "wb");
	FILE *fileOut = fopen("InWzeroed.bmp", "wb");

	fwrite((char *)&bmHeader, sizeof(BITMAPFILEHEADER), 1, fileOut);
	fwrite((char *)&bmInfo, sizeof(BITMAPINFO), 1, fileOut);

	fseek(fileOut, bmHeader.bfOffBits, SEEK_SET); // set the pointer to start writing the bmp data  
	fwrite(bmArray, bmSize, 1, fileOut);
	fclose(fileOut);

}

int main()
{

	char file[80] = "InW.bmp";

	rotateBitmap(file);

//	char s[80], s2[80];
//
//	while (1)
//	{
//		printf("Input a string:  ");
//		gets(s);
//
//		compressString(s);
//
////		replaceSpaces(s);
//
//		printf("New string: %s\n", s);
//
//		//printf("Input another string:  ");
//		//scanf("%s", s2);
//
//		//printf("Is Permutation?  %d\n", isPermutation(s, s2));
//
//		//reverseString(s);
//		//printf("Reverse is:  %s\n", s);
//
//		//if (uniqueChars(s))
//		//	printf("String has unique characters\n");
//		//else
//		//	printf("String has repeated characters\n");
//
//	}

	return 0;
}
