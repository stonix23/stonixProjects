#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <stack>
#include <set>
#include <vector>

using namespace std;


class stackMin : public stack<int>
{

private:

	stack<int> mins;

public:

	stackMin()
	{
		mins.push(INT_MAX);
	}

	void push(int val)
	{
		stack<int>::push(val);

		if (val <= mins.top())
			mins.push(val);
	}

	void pop()
	{
		if (this->top() == this->min())
			mins.pop();

		stack<int>::pop();
	}

	int min()
	{
		return mins.top();
	}

};


template<typename T> class SetOfStacks
{
private:

	vector<stack<T>> m_stacks;

	int maxHeight;

public:

	SetOfStacks(int maxH) : maxHeight(maxH)	{};

	void push(T val)
	{
		if (m_stacks.empty() || (m_stacks.back().size() == maxHeight))
		{
			stack<T> newStack;
			m_stacks.push_back(newStack);
		}

		m_stacks.back().push(val);

	}
	
	void pop()
	{
		m_stacks.back().pop();

		if (m_stacks.back().empty())
		{
			m_stacks.pop_back();
		}

	}


	void popAt(size_t index)
	{
		if (m_stacks.size() >= index)
			m_stacks[index].pop();

	}

	T top()
	{
		if (m_stacks.empty())
			return NULL;

		return m_stacks.back().top();

	}

	bool empty()
	{
		return m_stacks.empty();
	}

};



void showstack(stackMin s)
{
	int minVal = s.min();

	while (!s.empty())
	{
		cout << "  " << s.top();
		s.pop();
	}

	cout << endl;

	cout << "Minimum value = " << minVal << endl;
}


void showstack(SetOfStacks<int> s)
{
	while (!s.empty())
	{
		cout << "  " << s.top();
		s.pop();
	}

	cout << endl;
}


void showstack(stack<int> s)
{
	while (!s.empty())
	{
		cout << "  " << s.top();
		s.pop();
	}

	cout << endl;
}



//int main()
//{
//
//	SetOfStacks<int> stackExample(4);
//
//	stackExample.push(23);
//	stackExample.push(15);
//	stackExample.push(18);
//	stackExample.push(21);
//	stackExample.push(19);
//	stackExample.push(43);
//	stackExample.push(9);
//	stackExample.push(11);
//	stackExample.push(27);
//	stackExample.push(7);
//	stackExample.push(41);
//	stackExample.push(7);
//	stackExample.push(1);
//
//	showstack(stackExample);
//
//	stackExample.pop();
//	showstack(stackExample);
//
//	stackExample.popAt(0);
//	showstack(stackExample);
//
//	stackExample.popAt(0);
//	stackExample.popAt(0);
//	stackExample.popAt(0);
//	showstack(stackExample);
//
//
//	//stackMin stackMinExample;
//
//	//stackMinExample.push(23);
//	//stackMinExample.push(15);
//	//stackMinExample.push(18);
//	//stackMinExample.push(21);
//	//stackMinExample.push(19);
//	//stackMinExample.push(43);
//	//stackMinExample.push(9);
//	//stackMinExample.push(11);
//	//stackMinExample.push(27);
//	//stackMinExample.push(7);
//	//stackMinExample.push(41);
//	//stackMinExample.push(7);
//	//stackMinExample.push(1);
//
//
//	//// printing stack values  
//
//	//showstack(stackMinExample);
//
//	//stackMinExample.pop();
//	//showstack(stackMinExample);
//
//	//stackMinExample.pop();
//	//showstack(stackMinExample);
//
//	//stackMinExample.pop();
//	//showstack(stackMinExample);
//
//	//stackMinExample.pop();
//	//showstack(stackMinExample);
//
//	return 0;
//}





void buildTower(vector<stack<int>>& towers, int origin, int target, int buffer, int height)
{
	if (height == 0)
		return;

	buildTower(towers, origin, buffer, target, height - 1);

	towers[target].push(towers[origin].top());
	towers[origin].pop();
	
	buildTower(towers, buffer, target, origin, height - 1);

}


//#define TOWER_SIZE 5
//
//int main()
//{
//	vector<stack<int>> towers;
//
//	stack<int> tower0, tower1, tower2;
//
//	towers.push_back(tower0);
//	towers.push_back(tower1);
//	towers.push_back(tower2);
//
//	for (int i = TOWER_SIZE; i > 0; i--)
//		towers[0].push(i);
//
//	cout << "Top of tower 0 = " << towers[0].top() << endl;
//
//	buildTower(towers, 0, 2, 1, towers[0].size());
//
//	return 0;
//}


class MyQueue
{
	stack<int> front, back;

public:

	void push(int val)
	{
		while (!front.empty())
		{
			back.push(front.top());
			front.pop();
		}

		back.push(val);

	}

	void pop()
	{
		while (!back.empty())
		{
			front.push(back.top());
			back.pop();
		}

		front.pop();
	}

	int peekfront()
	{
		while (!back.empty())
		{
			front.push(back.top());
			back.pop();
		}

		return front.top();
	}

};


void sortStack(stack<int>& inputStack, stack<int>& outputStack)
{
	while (!inputStack.empty())
	{
		int tos = inputStack.top();
		inputStack.pop();

		while (!outputStack.empty() && tos < outputStack.top())
		{
			inputStack.push(outputStack.top());
			outputStack.pop();
		}

		outputStack.push(tos);
	}

}

int main()
{

	stack<int> stackExample, outputStack;
			
	stackExample.push(23);
	stackExample.push(15);
	stackExample.push(18);
	stackExample.push(21);
	stackExample.push(19);
	stackExample.push(43);
	stackExample.push(9);
	stackExample.push(11);
	stackExample.push(27);
	stackExample.push(7);
	stackExample.push(41);
	stackExample.push(7);
	stackExample.push(1);

	showstack(stackExample);

	sortStack(stackExample, outputStack);

	showstack(outputStack);
	
	return 0;
}