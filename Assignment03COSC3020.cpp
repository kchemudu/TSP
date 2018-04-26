#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include<algorithm>
#include <unordered_map>
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
void printVec(vector<int> cities, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << cities[i] << " ";
	}
	cout << endl;
}
int returnPrevCalc(vector<int> cities, int size, int start, unordered_map<string, int> distances)
{
	int sigma = 0;
	for (int i = 0; i < size; i++)
	{
		int a = 1 << cities[i];
		sigma = sigma + a ;
	}
	string a = to_string(sigma);
	string b = to_string(start);
	string key = a + "|" + b;
	if (distances.count(key) > 0)
	{
		return distances.at(key);
	}
	else return -1;

}
void setToDistances(vector<int> cities, int size, int start, unordered_map<string, int>& distances, int distance)
{
	int sigma = 0;
	for (int i = 0; i < size; i++)
	{
		int x = 1 << cities[i];
		sigma = sigma + x;
	}
	string a = to_string(sigma);
	string b = to_string(start);
	string key = a + "|" + b;
	distances.insert({ key, distance });
}
int heldKarpDP(vector<int> cities, int size, int ** graph, int start, unordered_map<string, int>& distances)
{
	std::remove(cities.begin(), cities.end(), start);
	int minDist = INT_MAX;
	int prevCalcMinDist = returnPrevCalc(cities, size-1, start, distances);
	if (prevCalcMinDist < 0) {
		if (size == 2)
		{
			minDist = graph[start][cities[0]];
		}
		else {
			int size1 = size - 1;
			for (int i = 0; i < size1; i++)
			{
				int tempDist = heldKarpDP(cities, size1, graph, cities[i], distances) + graph[start][cities[i]];
				if (tempDist < minDist)
				{
					minDist = tempDist;
				}
			}
		}
		setToDistances(cities, size-1, start, distances, minDist);
	}else minDist = prevCalcMinDist;
	return minDist;	
}
int heldKarp(int ** graph, int size)
{
	vector<int> cities;
	for (int i = 0; i < size; i++)
	{
		cities.push_back(i);
	}
	unordered_map<string, int> distances;
	int minDist = INT_MAX;
	for (int i = 0; i < size; i++)
	{
		int tempDist = heldKarpDP(cities, size, graph, i, distances);
		if (tempDist < minDist)
		{
			minDist = tempDist;
		}
	}

	return minDist;
}

int main()
{
	int size = 10;
	int** adjMatrix = new int*[size];
	for (int i = 0; i < size; i++)
	{
		adjMatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			adjMatrix[i][j] = i+j;
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
	cout << "The min dist: " << heldKarp(adjMatrix, size) << endl;
	time = clock() - time;
	cout << "The time taken to run the algorithm is:" << (double)time / CLOCKS_PER_SEC << " seconds" << endl;
}