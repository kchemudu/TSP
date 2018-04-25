#include <iostream>
#include <vector>
using namespace std;

bool isItVisited(vector<vector<int>> route, int routeNum, int vertex)
{
	bool found = false;
	for (int i = 0; i < route[routeNum].size() && !found; i++)
	{
		if (route[routeNum][i] == vertex)
		{
			found = true;
		}
	}
	return found;
}

int heldKarp(int ** graph, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (graph[i][j] == 0)	graph[i][j] = 10000;
		}
	}
	vector<vector<int>> route;
	route.resize(size);
	vector<vector<int>> distances;
	distances.resize(size);
	for (int i = 0; i < size; i++)
	{
		route[i].push_back(i);
		distances[i].push_back(0);
	}
	

	//to do the inner forloops multiple times
	for (int k = 0; k < size-1; k++)
	{
		//outer for loop to go through all beginnings
		for (int i = 0; i < size; i++)
		{
			int nearestVertex = 0;
			int shortestDist = INT_MAX;
			// inner for loop to go through all unvisited and add the least.
			for (int j = 0; j < size; j++)
			{
				if (!isItVisited(route, i, j))
				{
					int tempDist = distances[i][k] + graph[route[i][k]][j];
					if (tempDist < shortestDist)
					{
						shortestDist = tempDist;
						nearestVertex = j;
					}
				}
			}
			route[i].push_back(nearestVertex);
			distances[i].push_back(shortestDist);
		}
	}
	int minDist = INT_MAX;
	int minVertex = 0;
	for (int i = 0; i < size; i++)
	{
		if (distances[i][size - 1] < minDist)
		{
			minDist = distances[i][size - 1];
			minVertex = i;
		}
	}
	for (int j = 0; j < route[minVertex].size(); j++)
	{
		cout << route[minVertex][j] << endl;
	}
	return minDist;
}

int main()
{
	int size = 8;
	int** adjMatrix = new int*[size];
	for (int i = 0; i < size; i++)
	{
		adjMatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			adjMatrix[i][j] = 0;
		}
	}
	adjMatrix[0][1] = 2;
	adjMatrix[0][2] = 1;
	adjMatrix[0][3] = 4;
	adjMatrix[1][2] = 1;
	adjMatrix[1][4] = 10;
	adjMatrix[1][5] = 2;
	adjMatrix[2][0] = 9;
	adjMatrix[2][4] = 8;
	adjMatrix[3][2] = 2;
	adjMatrix[4][3] = 7;
	adjMatrix[4][6] = 1;
	adjMatrix[5][7] = 3;
	adjMatrix[6][4] = 4;
	adjMatrix[6][5] = 2;
	adjMatrix[7][6] = 1;

	cout << "The min dist: " << heldKarp(adjMatrix, size) << endl;
}