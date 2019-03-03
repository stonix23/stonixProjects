#include<stdlib.h>
#include<stdio.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>



using namespace std;

struct bstNode
{
	int data;
	bstNode *left;
	bstNode *right;

	bstNode *parent;
};


class BinSearchTree
{
private:

	bstNode* root;
	int findCommonAncestorfromNode(bstNode* curNode, int val1, int val2);

	static bstNode* newBSTNode(int value);
	static void deleteBST(bstNode * root);
	static bool checkBST(bstNode *root, int minVal, int maxVal);

public:

	BinSearchTree();
	~BinSearchTree();

	void Insert(int value);
	void Remove(int value);

	bstNode* Search(int value);
	bool Search(bstNode* curNode, int value);

	int FindMin();
	int FindHeight();

	int findNext(int value);

	void printLevelOrder();
	bool isBST();
	bool isBalanced();

	void bst2Lists(vector<list<bstNode*>>& listofBSTLevels);
	int findCommonAncestor(int val1, int val2);

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


bstNode* BinSearchTree::Search(int value)
{

	bstNode *curNode = this->root;

	while (curNode != NULL)
	{
		if (curNode->data == value)
			return curNode;

		if (value <= curNode->data)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}

	return NULL;

}


int BinSearchTree::findNext(int value)
{
	bstNode* firstNode = this->Search(value);

	if (firstNode == NULL)
		return -1;

	bstNode* nextNode = NULL;

	if (firstNode->right)
	{
		nextNode = firstNode->right;

		while (nextNode->left != NULL)
			nextNode = nextNode->left;

		return nextNode->data;
	}

	if (nextNode = NULL)
	{
		while (firstNode->parent)
		{
			if (firstNode == firstNode->parent->left)
			{
				nextNode = firstNode->parent;
				break;
			}

			firstNode = firstNode->parent;
		}
	}

	if (nextNode)
		return nextNode->data;
	else
		return -1;

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

	printf("\n");
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


#define LENGTH 8

void buildBST(BinSearchTree& bst, vector<int>::iterator start, vector<int>::iterator end)
{
	if (start == end)
		return;

	if (start == (end - 1))
	{
		bst.Insert(*start);
		return;
	}

	vector<int>::iterator middle = start;
	vector<int>::iterator fast = start;

	while (fast != end)
	{
		middle++;
		fast++;

		if (fast == end)
			break;

		fast++;

	}

	bst.Insert(*middle);

	buildBST(bst, start, middle);

	buildBST(bst, middle + 1, end);

}

//void BinSearchTree::bst2Lists(vector<list<bstNode*>>& listofBSTLevels)
//{
//	queue<tuple<bstNode*, int>> qNodes;
//
//	if (this->root)
//		qNodes.push(make_tuple(this->root, 1));
//
//	while (!qNodes.empty())
//	{
//		bstNode *currentNode = get<0>(qNodes.front());
//		int height = get<1>(qNodes.front());
//		qNodes.pop();
//
//		if (height > listofBSTLevels.size())
//		{
//			list<bstNode*> newList;
//			listofBSTLevels.push_back(newList);
//		}
//
//		listofBSTLevels.back().push_back(currentNode);
//
//		if (currentNode->left)
//			qNodes.push(make_tuple(currentNode->left, height + 1));
//
//		if (currentNode->right)
//			qNodes.push(make_tuple(currentNode->right, height + 1));
//
//	}
//
//}


void BinSearchTree::bst2Lists(vector<list<bstNode*>>& listofBSTLevels)
{
	if (this->root == NULL)
		return;

	list<bstNode*> rootList;
	listofBSTLevels.push_back(rootList);
	listofBSTLevels.back().push_back(this->root);
	int index = 0;

	while (listofBSTLevels.size() > index)
	{
		list<bstNode*> newList;
		listofBSTLevels.push_back(newList);

		list<bstNode*>::iterator itNodes;

		for (itNodes = listofBSTLevels[index].begin(); itNodes != listofBSTLevels[index].end(); itNodes++)
		{
			if ((*itNodes)->left)
				listofBSTLevels[index + 1].push_back((*itNodes)->left);

			if ((*itNodes)->right)
				listofBSTLevels[index + 1].push_back((*itNodes)->right);

		}

		if (listofBSTLevels[index + 1].size() == 0)
			listofBSTLevels.pop_back();

		index++;
	}


}


bool BinSearchTree::Search(bstNode* curNode, int value)
{

	while (curNode != NULL)
	{
		if (curNode->data == value)
			return true;

		if (value <= curNode->data)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}

	return false;

}


//  base case:  Neither left nor right contain both values, but curNode does

int BinSearchTree::findCommonAncestorfromNode(bstNode* curNode, int val1, int val2)
{
	if (this->Search(curNode, val1) == false)
		return -1;

	if (this->Search(curNode, val2) == false)
		return -1;

	// this node is ancestor to both values

	int findLeft = findCommonAncestorfromNode(curNode->left, val1, val2);

	if (findLeft != -1)
		return findLeft;

	int findRight = findCommonAncestorfromNode(curNode->right, val1, val2);

	if (findRight != -1)
		return findRight;

	return curNode->data;
}


int BinSearchTree::findCommonAncestor(int val1, int val2)
{
	return findCommonAncestorfromNode(this->root, val1, val2);
}



int main()
{
	vector<int> sortedArray;

	srand(1);

	for (int i = 0; i < LENGTH; i++)
		sortedArray.push_back(rand());

	sort(sortedArray.begin(), sortedArray.end());

	BinSearchTree balancedBST;

	buildBST(balancedBST, sortedArray.begin(), sortedArray.end());

	printf("common ancestor = %d\n", balancedBST.findCommonAncestor(19169, 41));

//	balancedBST.printLevelOrder();


//	vector<list<bstNode*>> listBSTNodes;
//	balancedBST.bst2Lists(listBSTNodes);

	return 0;

}