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
#include <functional> 
#include <ctime> 
#include <atomic> 


using namespace std;
typedef unsigned int uint32;


void printLastKLines(ifstream &inFile, int k)
{

	queue<string> lineQ;

	while (inFile.eof() == false)
	{
		string newLine;
		getline(inFile, newLine);

		lineQ.push(newLine);

		if (lineQ.size() > k)
			lineQ.pop();

	}

	while (lineQ.empty() == false)
	{
		cout << lineQ.front() << endl;
		lineQ.pop();
	}

}


struct Node
{
	Node *pLeft;
	Node *pRight;
};


Node* deepNodeCopy(Node *pNode)
{
	if (pNode == NULL)
		return NULL;

	Node *newNode = new Node;

	newNode->pLeft = deepNodeCopy(pNode->pLeft);
	newNode->pRight = deepNodeCopy(pNode->pRight);

	return newNode;

}


template<typename T> class RPointer
{
private:
	T *ptr;
	atomic<int> *refCount;

public:

	RPointer()
	{
		this->ptr = new T;

		this->refCount = new atomic<int>;
		*(this->refCount) = 1;
	}

	RPointer(T* pRef)
	{
		this->ptr = pRef;

		this->refCount = new atomic<int>;
		*(this->refCount) = 1;
	}


	T* getRef()
	{
		(*(this->refCount))++;
		return this->ptr;
	}

	void releaseRef()
	{
		// get lock

		(*(this->refCount))--;

		if (*refCount == 0)
		{
			delete this->ptr;
			delete this;
		}
	}

};


uint32 addNums(uint32 a, uint32 b)
{
	uint32 mask = 1;
	uint32 result = 0;
	uint32 bit = 0;

	uint32 carry = 0;

	while (mask)
	{
		bit = ((a & mask) ^ (b & mask) ^ carry);
		result |= bit;

		carry = ((a & mask) & (b & mask)) | ((a & mask) & carry) | ((b & mask) & carry);

		carry <<= 1;
		mask <<= 1;		
	}

	return result;

}


uint32 addNumsEasy(uint32 a, uint32 b)
{
	if (b == 0)
		return a;

	uint32 sum = a ^ b;

	uint32 carry = (a & b) << 1;

	return addNumsEasy(sum, carry);

}



int main()
{
	uint32 size = sizeof(size_t);

	uint32 result = addNumsEasy(3, 6);

	ifstream textFile("c:\\Projects\\ImagesWords.txt");

	if (!textFile)
	{
		cout << "File not found" << endl;
		return 0;
	}


	printLastKLines(textFile, 10);

	return 0;

}



// Two axis-aligned rectangles, determine if they overlap
// rectangle defined as upper left point and lower right point

struct newRectangle
{
	int lowerLeftX;
	int lowerLeftY;

	int upperRightX;
	int upperRightY;
};

bool checkOverlap(newRectangle r1, newRectangle r2)
{
	if ((r2.lowerLeftY > r1.upperRightY) || (r2.upperRightY < r1.lowerLeftY) || (r2.lowerLeftX > r1.upperRightX) || (r2.upperRightX < r1.lowerLeftX))
		return false;

	return true;
}

typedef unsigned int uint32;

void memcopy(void* dst, const void* src, size_t size)
{

	char *srcByte = (char*)src;
	char *dstByte = (char*)dst;

	for (unsigned __int64 i = 0; i < size; i++)
		dstByte[i] = srcByte[i];

}
