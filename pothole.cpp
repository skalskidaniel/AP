#include <cmath>
#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define V 10000

using namespace std;

vector<pair<int, int> > lastEdges;
int levels[V];
vector<vector<pair<int, int> > > graph; // vertex, current flow

bool visited[V];

void dfs(int x, int end)
{
    for (auto neighbour : graph[x])
    {
        if (levels[neighbour.first] > levels[x] && neighbour.second < 1)
        {
            ++neighbour.second;
            if (neighbour.first == end)
                return;
            
            dfs(neighbour.first, end);
        }
        --neighbour.second;
    }
}

bool bfs(int start, int end)
{
    memset(visited, false, sizeof(visited));
    fill(levels, levels + V, 0);
    bool reachedEnd = false;

    deque<int> q;
    visited[start] = true;
    q.push_back(start);

    while (!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i)
        {
            int current = q.front();
            q.pop_front();

            if (current == end)
            {
                reachedEnd = true;
            }

            for (auto neighbour : graph[current])
            {
                if (!visited[neighbour.first])
                {
                    visited[neighbour.first] = true;
                    levels[neighbour.first] = levelSize;
                    q.push_back(neighbour.first);
                }
            }
        }
    }
    if (reachedEnd)
    {
        return true;
    } else {
        return false;
    }
}

int maxFlow(int end)
{
    int ans = 0;
    while(bfs(1, end))
    {
        fill_n(visited, V, false);
        dfs(1, end);
    }

    for (auto edge : lastEdges)
    {
        ans += graph[edge.first][edge.second].second;
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int chumbers;
        cin >> chumbers;

        graph.resize(chumbers + 1);
        for (int i = 1; i <= chumbers; ++i)
        {
            int neighbours;
            cin >> neighbours;
            graph[i].resize(neighbours);
            for (int j = 0; j < neighbours; ++j)
            {
                int v;
                cin >> v;
                graph[i][j] = make_pair(v, 0);
                if (v == chumbers)
                {
                    lastEdges.push_back(make_pair(i, j));
                }
            }
        }
        cout << maxFlow(chumbers) << "\n";

    }

}

/* 
chumbers numbered from 1
between each test case blank line
*/