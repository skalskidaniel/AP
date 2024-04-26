#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define N 50001

using namespace std;

typedef unsigned long long ull;

bool visited[N];
ull finalLength = 0LL;
ull maxLength = 0LL;

void dfs(int x, vector<pair<int, int>> graph[], ull &currentLength)
{
    visited[x] = true;
    for (auto neighbour : graph[x])
    {
        if (!visited[neighbour.first])
        {
            currentLength += neighbour.second;
            dfs(neighbour.first, graph, currentLength);
            currentLength -= neighbour.second;
        }
    }
    if (currentLength > maxLength)
    {
        maxLength = currentLength;
    }
}

int main()
{
    int t, numberOfPlacesInTown;
    cin >> t;
    while (t--)
    {
        cin >> numberOfPlacesInTown;
        vector<pair<int, int>> connections[numberOfPlacesInTown];
        maxLength = 0LL;
        for (int i = 1; i < numberOfPlacesInTown; ++i)
        {
            int placeA, placeB, streetLength;
            cin >> placeA >> placeB >> streetLength;
            connections[placeA - 1].push_back(make_pair(placeB - 1, streetLength));
            connections[placeB - 1].push_back(make_pair(placeA - 1, streetLength));
        }

        for (int i = 0; i < numberOfPlacesInTown; ++i)
        {
            finalLength = 0LL;
            dfs(i, connections, finalLength);
            if (finalLength > maxLength)
            {
                maxLength = finalLength;
            }
            fill(visited, visited + numberOfPlacesInTown, false);
        }
        cout << maxLength << endl;
        
    }
}

/*
The first line of input contains the number of testcases t.
The first line of each testcase contains the number of
places (2 <= n <= 50000) in the town.
Each street is given at one line by two
places (1 <= a, b <= n) and the length of
the street (0 <= l < 20000).

For each testcase output one line which contains
the maximum length of the longest street in the city.

TEST CASE
2
6
1 2 3
2 3 4
2 6 2
6 4 6
6 5 5
7
1 2 7
2 3 1
2 6 6
6 4 1
6 5 2
3 7 1

OUTPUT
12
15
*/