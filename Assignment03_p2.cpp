// Assignment03_p2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <vector>
using namespace std;
void printRoute(vector<int> route)
{
	for (int i = 0; i < route.size(); i++)
	{
		cout << route[i] << "-> ";
	}
	cout << endl;
}
int calcDist(int** Graph, vector<int> route)
{
	if (route.size() > 0)
	{
		int dist = 0;
		for (int i = 0; i < route.size() - 1; i++)
		{
			if (Graph[route[i]][route[i + 1]] != INT_MAX && dist!=INT_MAX)
			{
				dist += Graph[route[i]][route[i + 1]];
			}
			else dist = INT_MAX;
		}
		return dist;
	}
	else return INT_MAX;

}
vector<int> swapIToK(int i, int k, vector<int> route)
{
	int m = 0;
	int n = 0;
	if (k < i)
	{
		n = i;m = k;
	}
	else
	{
		m = i; n = k;
	}
	vector<int> newRoute;
	for (int l = 0; l < m; l++)
	{
		newRoute.push_back(route[l]);
	}
	for (int l = n ; l >= m; l--)
	{
		newRoute.push_back(route[l]);
	}
	for (int l = n+1; l < route.size(); l++)
	{
		newRoute.push_back(route[l]);
	}
	return newRoute;
}

void twoOptSwap(int** graph, int size)
{
	//i can use increasing node num as the initial order.
	//then use random generation to generate random indices for i and k 
	// stopping criteria is if for n new routes there is no overall improvement, then end. 
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (graph[i][j] == 0)	graph[i][j] = INT_MAX;
		}
	}
	vector<int> route; 
	for (int i = 0; i < size; i++)
	{
		route.push_back(i);
	}
	int counter = 0;
	int minDist = INT_MAX;
	while (counter < size)
	{
		int tempDist = calcDist(graph, route);
		if (tempDist < minDist)
		{
			minDist = tempDist;
			counter = 0;
		}
		else counter++;
		int j = 0;
		int i = rand() % size;
		do { j = rand() % size; } while (i == j);
		route = swapIToK(i, j, route);
		cout << "i: " << i << " and j: " << j << endl;
		printRoute(route);
	}

	cout << "The shortest distance is: " << calcDist(graph, route) << endl;
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
			if (i != j)
			{
				adjMatrix[i][j] = i + j;
			}
			else adjMatrix[i][j] = 0;
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