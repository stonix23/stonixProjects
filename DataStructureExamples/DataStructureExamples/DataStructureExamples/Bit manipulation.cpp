#include<stdlib.h>
#include<stdio.h>
#include <stack>
#include <queue>

using namespace std;


size_t insertMintoN(size_t n, size_t m, size_t i, size_t j)
{
	size_t bits = 1 + j - i;

	size_t mask = ~((2 ^ bits) < i);

	size_t result = (n & mask) | (m << i);

	return result;

}

size_t binaryRep(double value)
{
	//size_t exp = (size_t)(*(unsigned __int64*)&value >> 52) & ~(1 << 11);

	//bool sign = (bool)(*(__int64*)&value >> 63);

	//unsigned __int64 mantissa = (*(unsigned __int64*)&value << 12) >> 12;
	//mantissa |= ((unsigned __int64)1 << 52);

	//size_t expOffset = 1023 - exp;

	//size_t mantissaTrailingZeros = expOffset + (53 - 32);

	//unsigned __int64 mask = (1 << mantissaTrailingZeros) - 1;

	//if (mantissa & mask)
	//	printf("ERROR\n");

	//return mantissa >> mantissaTrailingZeros;

	size_t binValue = 0;

	for (int i = 1; i <= 32; i++)
	{
		double bitValue = pow(2, -i);

		if (value >= bitValue)
		{
			binValue |= 1 << (32 - i);
			value -= bitValue;
		}

		if (value == 0.0)
			break;

	}

	if (value != 0.0)
		printf("Error!\n");

	return binValue;

}

void nextSmallestLargest(size_t value)
{
	size_t nextLargest;
	size_t trailingZeroes = 0;

	int i;

	for (i = 0; i < 31; i++)
	{
		// Find first 01 sequence
		if (value & (1 << i))
		{
			if ((value & (1 << (i + 1))) == 0)
			{
				nextLargest = value + (1 << i);
				break;
			}
		}
		else
			trailingZeroes++;
	}

	nextLargest = (nextLargest >> i) << i;

	nextLargest += ((1 << (i - trailingZeroes)) - 1);

	char buffer[33];

	itoa(value, buffer, 2);
	printf("Value = %d : 0x%x  %s\n", value, value, buffer);

	itoa(nextLargest, buffer, 2);
	printf("Next largest = %d : 0x%x  %s\n", nextLargest, nextLargest, buffer);

}

size_t numberBits(size_t val1, size_t val2)
{
	size_t bits = 0;

	size_t xorResult = val1 ^ val2;

	while (xorResult)
	{
		bits++;

		xorResult = xorResult & (xorResult - 1);
	}

	return bits;

}

void drawHorizontalLine(char * screen, int width, int x1, int x2, int y)
{
	size_t widthBytes = width / 8;

	size_t startIndex = y * widthBytes + x1 / 8;
	size_t endIndex = y * widthBytes + x2 / 8;

	size_t startOffset = x1 % 8;
	size_t endOffset = 7 - (x2 % 8);

	size_t firstByte = (0xff >> startOffset) << startOffset;

	if (endIndex == startIndex)
	{
		firstByte = (firstByte << endOffset) >> endOffset;

		screen[startIndex] |= firstByte;

		return;
	}


	screen[startIndex++] |= firstByte;

	while (startIndex < endIndex)
	{
		screen[startIndex++] = 0xff;
	}

	size_t lastByte = (0xff << endOffset) >> endOffset;

	screen[endIndex] |= lastByte;

}

size_t swapBits(size_t val)
{
	size_t evenMask = 0xaaaaaaaa;
	size_t oddMask = 0x55555555;

	size_t evenBits = val & evenMask;
	size_t oddBits = val & oddMask;

	oddBits << 1;
	evenBits >> 1;

	return oddBits | evenBits;

}

//		10110100
//		01111000
//


int main()
{
	srand(1);

	size_t numBits = numberBits(rand(), rand());

	nextSmallestLargest(rand());
	nextSmallestLargest(rand());
	nextSmallestLargest(rand());

	double values[10];

	values[0] = (double)rand() / RAND_MAX;
	values[1] = double((float)((float)rand() / RAND_MAX));
	values[2] = .625;
	values[3] = pow(2, -2) + pow(2, -3) + pow(2, -7) + pow(2, -9);

	size_t binValue = binaryRep(values[3]);

	size_t nnn = 1024;
	size_t mmm = 19;

	size_t result = insertMintoN(nnn, mmm, 2, 6);

	printf("result = %b\n", result);

	return 0;

}