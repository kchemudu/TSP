#include<iostream>
#include <vector>
using namespace std;

int calcDist(int** Graph, vector<int> route)
{
	if (route.size() > 0)
	{
		int dist = 0;
		for (int i = 0; i < route.size() - 1; i++)
		{
			dist = Graph[route[i]][route[i + 1]];
		}
		return dist;
	}
	else return INT_MAX;

}
vector<int>  swapIToK(int i, int k, vector<int> route)
{
	vector<int> newRoute;
	for (int l = 0; l < i; l++)
	{
		newRoute.push_back(route[l]);
	}
	for (int l = k - 1; l >= i; l--)
	{
		newRoute.push_back(route[l]);
	}
	for (int l = k; l < route.size(); l++)
	{
		newRoute.push_back(route[l]);
	}
	return newRoute;
}
void twoOptSwap(int** graph, int size)
{
	vector<int> newRoute;
	for (int i = 0; i < size; i++)
	{
		newRoute.push_back(i);
	}
	int i = 0, k = newRoute.size();	
	int min_Dist = 0;
	int counter = 0;
	while ((calcDist(graph, swapIToK(i, k, newRoute)) > min_Dist) && counter<1000)
	{
		i++;
		k--;
		if (k <= i)
		{
			i = 0;
			k = newRoute.size();
		}
		newRoute = swapIToK(k, i, newRoute);		
		counter++;
	}
	cout << "The minimum distance is:" << calcDist(graph, newRoute);
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

	twoOptSwap(adjMatrix, size);
}