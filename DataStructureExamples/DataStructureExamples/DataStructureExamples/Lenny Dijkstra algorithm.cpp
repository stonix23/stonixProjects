#include<stdlib.h>
#include<stdio.h>
#include<set>
#include<vector>

using namespace std;

#define V 9

unsigned int FindMinDistanceVertex(unsigned int dist[], bool sptSet[])
{
	unsigned int minDist = INT_MAX;
	unsigned int minDistIndex = -1;

	for (int i = 0; i < V; i++)
	{
		if ((dist[i] < minDist) && (sptSet[i] == false))
		{
			minDist = dist[i];
			minDistIndex = i;
		}
	}

	return minDistIndex;
}

void dijkstra(int graph[][V], int srcNode)
{
	unsigned int dist[V];
	bool sptSet[V];

	for (int i = 0; i < V; i++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}
	
	dist[srcNode] = 0;

	int vtxCount = 0;

	while (vtxCount < V)
	{
		unsigned int v = FindMinDistanceVertex(dist, sptSet);

		for (int i = 0; i < V; i++)
		{
			if (graph[v][i] != 0)
			{
				if ( (dist[v] + graph[v][i]) < dist[i] )
					dist[i] = (dist[v] + graph[v][i]);
			}
		}

		sptSet[v] = true;
		vtxCount++;
	}

	printf("Minimum distances from %d\n", srcNode);

	for (int i = 0; i < V; i++)
		printf("Node %d : distance = %d\n", i, dist[i]);

}


void dijkstraELog2V(int graph[][V], int srcNode)
{
	set < pair<unsigned int, unsigned int>> sptSet;

	vector <unsigned int> dist(V, INT_MAX);

	dist[srcNode] = 0;
	sptSet.insert(make_pair(0, srcNode));

	while (!sptSet.empty())
	{
		set < pair<unsigned int, unsigned int>> :: iterator itNode = sptSet.begin();
		unsigned int vCurrent = itNode->second;
		sptSet.erase(itNode);

		for (int i = 0; i < V; i++)
		{
			if (graph[vCurrent][i] != 0)
			{
				if ((dist[vCurrent] + graph[vCurrent][i]) < dist[i])
				{
					if (dist[i] != INT_MAX)
						sptSet.erase(sptSet.find(make_pair(dist[i], i)));

					dist[i] = (dist[vCurrent] + graph[vCurrent][i]);
					sptSet.insert(make_pair(dist[i], i));
				}
			}
		}
	}


	printf("Minimum distances from %d\n", srcNode);

	for (int i = 0; i < V; i++)
		printf("Node %d : distance = %d\n", i, dist[i]);

}

bool  findPath(int graph[][V], set<int>& visitedNodes, int srcNode, int dstNode)
{
	if (graph[srcNode][dstNode])
	{
		printf("Path back from %d", dstNode);
		return true;
	}

	visitedNodes.insert(srcNode);

	for (int i = 0; i < V; i++)
	{
		if ( (graph[srcNode][i] != 0) && (visitedNodes.find(i) == visitedNodes.end()) )
		{
			if (findPath(graph, visitedNodes, i, dstNode) == true)
			{
				printf("-> %d", i);
				return true;
			}
		}
	}

	return false;
}

bool  findPath(int graph[][V], int srcNode, int dstNode)
{
	if (srcNode == dstNode)
		return true;

	set<int> visitedNodes;

	bool isPath = findPath(graph, visitedNodes, srcNode, dstNode);

	if (isPath)
		printf("-> %d\n", srcNode);
	else
		printf("No path from %d to %d\n", srcNode, dstNode);

	return isPath;
}


int main()
{
	/* Let us create the example graph discussed above */
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
	};

	printf("Find path from 0 to 8?\n");

	dijkstra(graph, 0);

//	findPath(graph, 0, 6);

//	dijkstraELog2V(graph, 0);

//	getchar();

	return 0;
}