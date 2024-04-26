#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <queue>
#include <map>
using namespace std;

bool visited[20][20];
vector<pair<int, int>> graph[20][20];

int bfs(pair<int, int> start, pair<int, int> end)
{
    memset(visited, false, sizeof(visited));
    bool reachedEnd = false;
    int moveLength = 0;

    deque<pair<int, int>> q;
    visited[start.first][start.second] = true;
    q.push_back(start);

    while (!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i)
        {
            pair<int, int> current = q.front();
            q.pop_front();

            if (current == end)
            {
                reachedEnd = true;
                break; // exit for loop
            }

            for (auto neighbour : graph[current.first][current.second])
            {
                if (!visited[neighbour.first][neighbour.second])
                {
                    visited[neighbour.first][neighbour.second] = true;
                    q.push_back(neighbour);
                }
            }
        }
        if (reachedEnd)
        {
            break; // exit while loop
        }
        ++moveLength;
    }
    if (reachedEnd)
    {
        return moveLength;
    }
    return INT_MAX;
}

int main()
{
    while (true)
    {
        // reseting values
        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                graph[i][j].clear();
            }
        }

        // inputting
        int width, height;
        cin >> width >> height;
        if (width == 0 && height == 0)
        {
            break;
        }

        

        char tiles[height][width];
        pair<int, int> startingPoint;
        vector<pair<int, int>> dirtyTilesPositions;

        // reading symbols
        for (int x = 0; x < height; ++x)
        {
            for (int y = 0; y < width; ++y)
            {
                char symbol;
                cin >> symbol;
                tiles[x][y] = symbol;
                if (symbol == 'o')
                {
                    startingPoint = make_pair(x, y);
                }
                else if (symbol == '*')
                {
                    dirtyTilesPositions.push_back(make_pair(x, y));
                }
            }
        }

        for (int x = 0; x < height; ++x)
        {
            for (int y = 0; y < width; ++y)
            {
                char symbol = tiles[x][y];
                if (symbol != 'x')
                {
                    if (x - 1 >= 0 && tiles[x - 1][y] != 'x')
                    {
                        graph[x][y].push_back(make_pair(x - 1, y));
                    }
                    if (x + 1 < height && tiles[x + 1][y] != 'x')
                    {
                        graph[x][y].push_back(make_pair(x + 1, y));
                    }
                    if (y - 1 >= 0 && tiles[x][y - 1] != 'x')
                    {
                        graph[x][y].push_back(make_pair(x, y - 1));
                    }
                    if (y + 1 < width && tiles[x][y + 1] != 'x')
                    {
                        graph[x][y].push_back(make_pair(x, y + 1));
                    }
                }
            }
        }

        // calculating distances
        vector<vector<map<pair<int, int>, int>>> distances(height, vector<map<pair<int, int>, int>>(width));
        for (auto dirt : dirtyTilesPositions)
        {
            distances[startingPoint.first][startingPoint.second][dirt] = bfs(startingPoint, dirt);
        }
        
        for (auto dirtStart : dirtyTilesPositions)
        {
            for (auto dirtEnd : dirtyTilesPositions)
            {
                if (dirtEnd == dirtStart)
                {
                    continue;
                }
                else
                {
                    distances[dirtStart.first][dirtStart.second][dirtEnd] = bfs(dirtStart, dirtEnd);
                }
            }
        }

        // executing algorithm
        int minLength = INT_MAX;
        do
        {
            int currentLength = distances[startingPoint.first][startingPoint.second][dirtyTilesPositions[0]];

            for (int i = 0; i < dirtyTilesPositions.size() - 1; ++i)
            {
                pair<int, int> cur = dirtyTilesPositions[i], next = dirtyTilesPositions[i + 1];
                currentLength += distances[cur.first][cur.second][next];
            }

            if (currentLength < minLength)
            {
                minLength = currentLength;
            }
        } while (next_permutation(dirtyTilesPositions.begin(), dirtyTilesPositions.end()));
        if (minLength != INT_MAX && minLength > 0)
        {
            cout << minLength << endl;
        } else {
            cout << -1 << endl;
        }
        
    }

}
