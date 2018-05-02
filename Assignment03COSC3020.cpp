#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include<algorithm>
#include <unordered_map>
#include <limits.h> //clang doesnt recognize INT_MAX on its own. 
using namespace std;

// I use this function in HeldkarpDp to get previously calculated distance if done before. If not done before, the function returns -1. 
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
// This is used to set a key with the calculated distance in the map. 
//if from node 3 i visit nodes 0, 1 and 2, as 2^0+2^1+2^2 = 7, I put "7|3" as the key with the distance in the map. 
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
// Recurses through all possible permutations, of n-1 nodes, with other node as the start node. gets the lowest distance to travel all the nodes
// for a given start. 
// Assumptions made:
/*1. The graph is fully connected. i.e. edges exist between one node to every other node.
  2. The graph has positive weights for edges.*/
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
	//Used this vector to keep track of unvisited node, because it is easy to remove elements from a vector using std::remove().
	vector<int> cities;//stores the unvisited nodes. 
	for (int i = 0; i < size; i++)// push 0-1-2-3----n in the beginning.
	{
		cities.push_back(i);
	}
	// Used an unordered map because of O(1) memory access.
	unordered_map<string, int> distances;// Map to hold the key and the distance everytime we calculate something new.
	int minDist = INT_MAX;
	for (int i = 0; i < size; i++)// gets the least distance from all beginnings. 
	{
		int tempDist = heldKarpDP(cities, size, graph, i, distances);
		if (tempDist < minDist)
		{
			minDist = tempDist;
		}
	}
	//cout << "The size of the memoization DS: " << distances.size() << endl;
	return minDist;
}

int main()
{
	//checked for size of 0 which doesn't let the actual function heldKarpDP get executed at all, and that is why it just returns INT_MAX.
	/*int size = 0;
	int size = 1;*/
	// I have just one matrix for the test because, regardless of the weights in the graph, the algorithm will process all possible subsets. 
	// I also assume as stated above that the graph i recieve is fully connected, so didn't test for adjMatrix with all zeroes. The result if i tested with a matrix of all zeroes 
	// will result in a minDist of zero. 
	int size = 8;
	int** adjMatrix = new int*[size];
	for (int i = 0; i < size; i++)
	{
		adjMatrix[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			if (i == j) {
				adjMatrix[i][j] = 0;
			}
			else { adjMatrix[i][j] = i + j; }
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