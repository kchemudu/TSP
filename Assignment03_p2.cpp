// Assignment03_p2.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include <vector>
#include <time.h>
#include <limits.h>
using namespace std;
//Used for checking if the swaps were made properly
void printRoute(vector<int> route)
{
	for (int i = 0; i < route.size(); i++)
	{
		cout << route[i] << "-> ";
	}
	cout << endl;
}
// for a given route whose nodes are stored in the vector, the method calculates the distance. 
int calcDist(int** Graph, vector<int> route)
{
	if (route.size() > 1)
	{
		int dist = 0;
		for (int i = 0; i < route.size() - 1; i++)
		{
			// All the INT_MAX checks are to avoid negative values when something is added to INT_MAX. 
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
//SwapIToK swaps everything from i to k (inclusive of the elements at i and k). 
vector<int> swapIToK(int i, int k, vector<int>& route)
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
	//The initial random order i chose is according to increasing node num.
	//Then I use random generation to generate random indices for i and k .
	//Stopping criteria is if for n new routes there is no overall improvement, then end. 
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
	int j = 0;
	int i = 0;
	while (counter <= size && size > 0)
	{
		int tempDist = calcDist(graph, route);
		if (tempDist < minDist)
		{
			minDist = tempDist;
			counter = 0;
		}
		else { counter++; }
		//cout << "i: " << i << " and j: " << j << endl;
		//printRoute(route);
		/*cout << "tempDist: " << tempDist << endl;
		cout << "counter: " << counter << endl;
		cout << "minDist: " << minDist << endl;*/
		i = rand() % size;
		do { j = rand() % size; } while (i == j && size!=1);
		route = swapIToK(i, j, route);
		
	}

	cout << "The shortest distance is: " << minDist << endl;
}

int main()
{
	int size = 100;
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
	/*adjMatrix[0][1] = 2;
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
	adjMatrix[7][6] = 1;*/
	clock_t time = clock();
	twoOptSwap(adjMatrix, size);
	time = clock() - time;
	cout << "The input size is: " << size << endl;
	cout << "The time taken to run the algorithm is:" << (double)time / CLOCKS_PER_SEC << " seconds" << endl;
	
}