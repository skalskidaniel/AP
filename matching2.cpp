#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <climits>
#define NIL 0
#define INF INT_MAX

using namespace std;

bool bfs(vector<list<int>> &adj, vector<int> &pairU, vector<int> &pairV, vector<int> &dist);
bool dfs(int u, vector<list<int>> &adj, vector<int> &pairU, vector<int> &pairV, vector<int> &dist);

int maximumMatch(vector<list<int>> &adj, int m, int n)
{
    vector<int> pairU(m + 1, NIL);
    vector<int> pairV(n + 1, NIL);
    vector<int> dist(m + 1);
    int result = 0;

    while (bfs(adj, pairU, pairV, dist))
    {
        for (int u = 1; u <= m; u++)
            if (pairU[u] == NIL && dfs(u, adj, pairU, pairV, dist))
                result++;
    }
    return result;
}

bool bfs(vector<list<int>> &adj, vector<int> &pairU, vector<int> &pairV, vector<int> &dist)
{
    queue<int> Q;

    for (size_t u = 1; u < pairU.size(); u++)
    {
        if (pairU[u] == NIL)
        {
            dist[u] = 0;
            Q.push(u);
        }
        else
        {
            dist[u] = INF;
        }
    }

    dist[NIL] = INF;

    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();

        if (dist[u] < dist[NIL])
        {
            for (auto v : adj[u])
            {
                if (dist[pairV[v]] == INF)
                {
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }

    return (dist[NIL] != INF);
}

bool dfs(int u, vector<list<int>> &adj, vector<int> &pairU, vector<int> &pairV, vector<int> &dist)
{
    if (u != NIL)
    {
        for (auto v : adj[u])
        {
            if (dist[pairV[v]] == dist[u] + 1)
            {
                if (dfs(pairV[v], adj, pairU, pairV, dist))
                {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int main()
{
    int cows, bulls, potentialMatches;
    cin >> cows >> bulls >> potentialMatches;

    vector<list<int>> adj(cows + 1);
    for (int i = 0; i < potentialMatches; ++i)
    {
        int c, b;
        cin >> c >> b;
        adj[c].push_back(b);
    }

    cout << maximumMatch(adj, cows, bulls) << endl;

    return 0;
}
