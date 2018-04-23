//Krishna Sai Chemudupati
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <limits>
using namespace std;

int** copySubMatrix(int ** graph, int vertices, int removedVertex)
{
	int** subMatrix = new int *[vertices - 1];
	for (int i = 0; i < vertices - 1; i++)
	{
		subMatrix[i] = new int[vertices - 1];
	}
	int i = 0;
	for (int i1 = 0; i1 < vertices; i1++)
	{
		int j = 0;
		for (int j1 = 0; j1 < vertices; j1++)
		{
			if (i1 != removedVertex && j1 != removedVertex)
			{
				subMatrix[i][j]= graph[i1][j1];
				j++;
			}
		}  
		if (j != 0)i++;
	}
}
unordered_map<string, int> distances;
int heldKarpMinDist(int ** Map, int vertices, int startVertices)
{
	//change all 0 distances to max_int in the graph
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			if (Map[i][j] == 0)	Map[i][j] = INT_MAX;
		}
	}
	if (vertices == 2)
	{
		return Map[0][1];
	}
	else
	{
		//unordered_map<string, int> distances;
		int tempStart = startVertices;
		int * visitStatus = new int[vertices];
		for (int i = 0; i < vertices; i++)
		{
			visitStatus[i] = 0;
		}

		return 0;
	}
}

int main()
{
}