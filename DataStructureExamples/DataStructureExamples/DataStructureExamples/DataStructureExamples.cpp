
#include<stdlib.h>
#include<stdio.h>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
	int data;
	Node* next;
};

//Node*	head;
//
//void Reverse(Node* cur)
//{
//	if (cur == NULL)
//		return;
//
//	if (cur->next == NULL)
//	{
//		head = cur;
//		return;
//	}
//
//	Reverse(cur->next);
//
//	cur->next->next = cur;
//	cur->next = NULL;
//	
//}

void Reverse(char *C, int n)
{
	stack<char> S;

	for (int i = 0; i < n; i++)
		S.push(C[i]);

	for (int i = 0; i < n; i++)
	{
		C[i] = S.top();
		S.pop();
	}

}

bool CheckBalancedParenthesis(char *c)
{
	int n = strlen(c);

	stack<char> parenStack;

	for (int i = 0; i < n; i++)
	{
		if ((c[i] == '(') || (c[i] == '{') || (c[i] == '['))
			parenStack.push(c[i]);

		if (c[i] == ')')
		{
			if (parenStack.empty() || parenStack.top() != '(' )
			{
				return false;
			}
			else
				parenStack.pop();
		}

		if (c[i] == '}')
		{
			if (parenStack.empty() || parenStack.top() != '{')
			{
				return false;
			}
			else
				parenStack.pop();
		}

		if (c[i] == ']')
		{
			if (parenStack.empty() || parenStack.top() != '[')
			{
				return false;
			}
			else
				parenStack.pop();
		}

	}

	return parenStack.empty();

}


//int main()
//{
//	char C[51];
//
//
//	while (1)
//	{
//		printf("Enter a string:  ");
//		gets(C);
//
//		bool checkBalanced = CheckBalancedParenthesis(C);
//
//		printf("Exp:  %s\n", C);
//		printf("Balanced? %d\n", checkBalanced);
//
//		getchar();
//	}
//}



struct bstNode
{
	int data;
	bstNode *left;
	bstNode *right;
};



class BinSearchTree
{
private:

	bstNode* root;
	
	static bstNode* newBSTNode(int value);
	static void deleteBST(bstNode * root);
	static bool checkBST(bstNode *root, int minVal, int maxVal);

public:

	BinSearchTree();
	~BinSearchTree();

	void Insert(int value);
	void Remove(int value);

	bool Search(int value);
	int FindMin();
	int FindHeight();

	void printLevelOrder();
	bool isBST();
	bool isBalanced();

};


BinSearchTree::BinSearchTree()
{
	root = NULL;
}

BinSearchTree::~BinSearchTree()
{
	BinSearchTree::deleteBST(this->root);
}


void BinSearchTree::deleteBST(bstNode *curNode)
{
	if (curNode != NULL)
	{
		deleteBST(curNode->left);
		deleteBST(curNode->right);

		delete curNode;
	}

	return;
}

bstNode* BinSearchTree::newBSTNode(int value)
{
	bstNode* pNode = new bstNode();

	pNode->data = value;
	pNode->left = NULL;
	pNode->right = NULL;

	return pNode;
}

void BinSearchTree::Insert(int value)
{
	bstNode *newNode = BinSearchTree::newBSTNode(value);

	if (this->root == NULL)
		this->root = newNode;
	else
	{
		bstNode *curNode = this->root;

		while (1)
		{
			if (value <= curNode->data)
			{
				if (curNode->left == NULL)
				{
					curNode->left = newNode;
					break;
				}
				else
					curNode = curNode->left;
			}
			else
			{
				if (curNode->right == NULL)
				{
					curNode->right = newNode;
					break;
				}
				else
					curNode = curNode->right;
			}
		}

	}
}


bool BinSearchTree::Search(int value)
{

	if (this->root != NULL)
	{
		bstNode *curNode = this->root;

		while (curNode != NULL)
		{
			if (curNode->data == value)
				return true;
			
			if (value <= curNode->data)
				curNode = curNode->left;
			else
				curNode = curNode->right;
		}
	}

	return false;

}


void BinSearchTree::Remove(int value)
{

	bstNode *curNode = this->root;
	bstNode **prevNodePtr = NULL;

	// Search for the node
	while (curNode != NULL)
	{
		if (curNode->data == value)
			break;

		if (value <= curNode->data)
		{
			prevNodePtr = &(curNode->left);
			curNode = curNode->left;
		}
		else
		{
			prevNodePtr = &(curNode->right);
			curNode = curNode->right;
		}
	}

	if (curNode == NULL)
	{
		printf("Node %d not found\n", value);
		return;
	}


	// case 1:  Node has two children
	if ((curNode->left != NULL) && (curNode->right != NULL))
	{
		// Find min of right tree
		bstNode *minRightNode = curNode->right;
		bstNode *prevRightNode = curNode;

		while (minRightNode->left != NULL)
		{
			prevRightNode = minRightNode;
			minRightNode = minRightNode->left;
		}

		int minRightValue = minRightNode->data;
		 
		// Remove minimum node from right side
		this->Remove(minRightNode->data);

		// Assign minRight value in place of deleted value
		curNode->data = minRightValue;

		return;
	}

	// case 2:  Node has one child or no children

	// Check if we are deleting the root node
	if (prevNodePtr == NULL)
		prevNodePtr = &(this->root);

	if (curNode->left != NULL)
		*prevNodePtr = curNode->left;
	else
		*prevNodePtr = curNode->right;	// Node has either one right child or none

	delete curNode;

	return;

}



int BinSearchTree::FindMin()
{
	if (this->root == NULL)
		return -1;

	bstNode *curNode = this->root;

	while (curNode->left != NULL)
		curNode = curNode->left;

	return curNode->data;

}


void BinSearchTree::printLevelOrder()
{
	queue<bstNode*> nodeQ;

	if (this->root != NULL)
		nodeQ.push(this->root);


	while (nodeQ.empty() == false)
	{
		bstNode *currentNode = nodeQ.front();
		nodeQ.pop();

		printf("%d ", currentNode->data);

		if (currentNode->left != NULL)
		{
			nodeQ.push(currentNode->left);
		}

		if (currentNode->right != NULL)
		{
			nodeQ.push(currentNode->right);
		}
	}

}


bool BinSearchTree::isBST()
{
	return BinSearchTree::checkBST(this->root, INT_MIN, INT_MAX);
}


bool BinSearchTree::checkBST(bstNode *curNode, int minVal, int maxVal)
{
	if (curNode != NULL)
	{
		if ((curNode->data > minVal) && (curNode->data < maxVal))
		{
			if (checkBST(curNode->left, minVal, curNode->data) == false)
				return false;
				
			if (checkBST(curNode->right, curNode->data, maxVal) == false)
				return false;
		}
		else
			return false;
	}

	return true;

}

int findHeight(bstNode* curNode)
{
	if (curNode == NULL)
		return 0;

	int leftHeight = findHeight(curNode->left);

	if (leftHeight == -1)
		return -1;

	int rightHeight = findHeight(curNode->right);

	if (rightHeight == -1)
		return -1;

	if (!(abs(leftHeight - rightHeight) < 2))
		return -1;

	return max(leftHeight, rightHeight) + 1;

}


bool BinSearchTree::isBalanced()
{
	if (this->root == NULL)
		return true;

	return (findHeight(this->root) != -1);

}


// Find Successor
// Search for node
// if node has right child, find min along right child
// else find deepest ancestor where child lies along left edge



int main()
{
	BinSearchTree bstExample;

	bstExample.Insert(23);
	bstExample.Insert(15);
	bstExample.Insert(18);
	bstExample.Insert(21);
	bstExample.Insert(19);
	bstExample.Insert(43);
	bstExample.Insert(1);
	bstExample.Insert(7);
	bstExample.Insert(9);
	bstExample.Insert(11);
	bstExample.Insert(27);
	bstExample.Insert(41);

	printf("Is balanced? %d\n", bstExample.isBalanced());

	bstExample.Remove(41);
	bstExample.Remove(27);
	bstExample.Remove(43);
	bstExample.Remove(23);

	int searchValue = 0;

	printf(" Is this a BST? %d\n", bstExample.isBST());

	bstExample.printLevelOrder();

	while (1)
	{
		printf("search for a number:  ");
		scanf("%d", &searchValue);

		printf("Found? %d\n", bstExample.Search(searchValue));
	}

	return 0;
}
