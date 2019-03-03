
#include<stdlib.h>
#include<stdio.h>
#include <list>
#include <forward_list>
#include<unordered_map>
#include <stack>
#include <algorithm>

using namespace std;


#define LENGTH 32

void removeDuplicates(list<int>& inList)
{
	unordered_map<int, bool> numberExists;

	list<int>::iterator itList = inList.begin();

	while (itList != inList.end())
	{
		int num = *itList;

		if (numberExists[num] == true)
		{
			printf("Removing %d\n", num);

			itList = inList.erase(itList);
		}
		else
		{
			numberExists[num] = true;
			itList++;
		}
	}

}

template <typename T> void printList(list<T> inList)
{
	list<T>::iterator itList = inList.begin();

	T num;

	while (1)
	{
		num = *itList++;

		if (itList == inList.end())
			break;

		printf("%c, ", num);
	}

	printf("%c\n", num);

}

template <typename T> void printList(forward_list<T> inList)
{
	forward_list<T>::iterator itList = inList.begin();

	T num;

	while (1)
	{
		num = *itList++;

		if (itList == inList.end())
			break;

		printf("%c, ", num);
	}

	printf("%c\n", num);

}


int findKthtoLastElementR(forward_list<int>::iterator endList, forward_list<int>::iterator itList, int k, int& kthValue)
{
	if (itList == endList)
	{
		return 0;
	}

	itList++;

	int count = findKthtoLastElementR(endList, itList, k, kthValue);

	if (count == k)
		kthValue = *itList;

	return ++count;
}


int findKthtoLastElement(forward_list<int> inList, int k)
{
	int kthValue = -1;

	findKthtoLastElementR(inList.end(), inList.begin(), k, kthValue);

	return kthValue;

}

void sortAroundX(list<int>& inputList, int x)
{
	list<int>::iterator itList = inputList.begin();

	itList++;

	while (itList != inputList.end())
	{
		int num = *itList;

		if (num < x)
		{
			inputList.push_front(num);

			itList = inputList.erase(itList);
		}
		else
			itList++;

	}

}

void addNumsAsList(list<char>& sumList,  list<char> num1, list<char> num2)
{
	list<char>::iterator it1 = num1.begin();
	list<char>::iterator it2 = num2.begin();

	bool carry = false;

	while (it1 != num1.end() && it2 != num2.end())
	{
		char value = *it1++ + *it2++ + (char)carry;

		sumList.push_front(value % 10);

		carry = (value > 9);
	}

	while (it1 != num1.end())
	{
		char value = *it1++ + (char)carry;

		sumList.push_front(value % 10);

		carry = (value > 9);
	}

	while (it2 != num2.end())
	{
		char value = *it2++ + (char)carry;

		sumList.push_front(value % 10);

		carry = (value > 9);
	}

	if (carry)
		sumList.push_front(1);

}

bool checkPalindrome(list<char> stringList)
{
	list<char>::iterator itBack = stringList.end();
	list<char>::iterator itFront = stringList.begin();
	
	itBack--;

	for (int i = 0; i < stringList.size() / 2; i++)
	{
		if (*itFront++ != *itBack--)
			return false;
	}

	return true;
}


bool checkPalindromeFwdList(forward_list<char> stringList)
{
	forward_list<char>::iterator itSlow = stringList.begin();
	forward_list<char>::iterator itFast = stringList.begin();

	stack<char> halfStack;

	while (itFast != stringList.end())
	{
		char letter = *itSlow++;

		if (++itFast == stringList.end())
			break;

		halfStack.push(letter);

		itFast++;
	}

	while (itSlow != stringList.end())
	{
		if (*itSlow++ != halfStack.top())
			return false;

		halfStack.pop();
	}

	return true;
}

enum species { Dog, Cat};

typedef tuple<species, int> animal;

class animalShelter
{
private:

	forward_list<animal> listAnimals;

public:

	void enqueue(animal newAnimal)
	{
		listAnimals.push_front(newAnimal);
	}

	animal dequeueAny()
	{
		animal adoptedAnimal;

		forward_list<animal>::iterator itLastAnimal = listAnimals.begin();
		forward_list<animal>::iterator itNextToLastAnimal = listAnimals.begin();

		for (forward_list<animal>::iterator itAnimalList = listAnimals.begin(); itAnimalList != listAnimals.end(); itAnimalList++)
		{
			itNextToLastAnimal = itLastAnimal;
			itLastAnimal = itAnimalList;
		}

		adoptedAnimal = *itLastAnimal;

		listAnimals.erase_after(itNextToLastAnimal);
		
		return adoptedAnimal;
	}

	animal dequeueDog()
	{
		int oldest = 0;
		forward_list<animal>::iterator itOldest;

		for (forward_list<animal>::iterator itAnimalList = listAnimals.begin(); itAnimalList != listAnimals.end(); itAnimalList++)
		{
			if (get<0>(*itAnimalList) == Dog)
			{
				if (get<1>(*itAnimalList) > oldest)
				{
					oldest = get<1>(*itAnimalList);
					itOldest = itAnimalList;
				}
			}
		}

		animal oldestDog = *itOldest;

		listAnimals.erase_after(itOldest);

		return oldestDog;

	}

};



int main()
{
	//animalShelter shelterSPCA;

	//shelterSPCA.enqueue(make_tuple(Dog, 3));
	//shelterSPCA.enqueue(make_tuple(Dog, 7));
	//shelterSPCA.enqueue(make_tuple(Dog, 3));
	//shelterSPCA.enqueue(make_tuple(Cat, 4));
	//shelterSPCA.enqueue(make_tuple(Dog, 1));
	//shelterSPCA.enqueue(make_tuple(Cat, 9));

	//animal adoptee = shelterSPCA.dequeueAny();

	//animal adopteeDog = shelterSPCA.dequeueDog();


	//forward_list<char> someChars;

	//someChars.push_front('a');
	//someChars.push_front('m');
	//someChars.push_front('a');
	//someChars.push_front('n');
	//someChars.push_front('a');
	//someChars.push_front('p');
	//someChars.push_front('l');
	//someChars.push_front('a');
	//someChars.push_front('n');
	//someChars.push_front('a');
	//someChars.push_front('c');
	//someChars.push_front('a');
	//someChars.push_front('n');
	//someChars.push_front('a');
	//someChars.push_front('l');
	//someChars.push_front('p');
	//someChars.push_front('a');
	//someChars.push_front('n');
	//someChars.push_front('a');
	//someChars.push_front('m');
	//someChars.push_front('a');

	//printList(someChars);

	//printf("Is Palindrome?  %d\n", checkPalindromeFwdList(someChars));

	forward_list<int> someNumbers;

	srand(1);

	for (int i = 0; i < LENGTH; i++)
	{
		int num = LENGTH * rand() / RAND_MAX;

		someNumbers.push_front(num);
	}

	//list<char> num1, num2, sumList;

	//num1.push_front(6);
	//num1.push_front(1);
	//num1.push_front(7);

	//num2.push_front(1);
	//num2.push_front(3);
	//num2.push_front(9);
	//num2.push_front(5);

	//addNumsAsList(sumList, num1, num2);

	//printList(num1);
	//printList(num2);
	//printList(sumList);

	//printList(someNumbers);

	//sortAroundX(someNumbers, 17);

	//printList(someNumbers);

	printf("Kth to last element = %d\n", findKthtoLastElement(someNumbers, 5));
//	removeDuplicates(someNumbers);


}