#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


unordered_map<int, vector<pair<int, int>>> graph;

void addEdge(pair<int, int> edge)
{
    int u = edge.first, v = edge.second;
    graph[u].push_back({v, 0}); 
    graph[v].push_back({u, 0}); 
}

void delEdge(pair<int, int> edge)
{
    int u = edge.first, v = edge.second;
    for (auto it = graph[u].begin(); it != graph[u].end(); ++it)
    {
        if (it->first == v)
        {
            graph[u].erase(it);
            break;
        }
    }
    for (auto it = graph[v].begin(); it != graph[v].end(); ++it)
    {
        if (it->first == u)
        {
            graph[v].erase(it);
            break;
        }
    }
}

bool isCycle(pair<int, int> edge)
{
    int u = edge.first, v = edge.second;
    unordered_set<int> visited;
    queue<pair<int, int>> q;
    q.push({u, -1});
    visited.insert(u);

    while (!q.empty())
    {
        int current = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (auto neighbor : graph[current])
        {
            if (!visited.count(neighbor.first))
            {
                visited.insert(neighbor.first);
                q.push({neighbor.first, current});
            }
            else if (neighbor.first != parent)
            {
                // If the neighbor has been visited and it's not the parent, then cycle exists
                return true;
            }
        }
    }
    return false;
}

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight)
{
    int ans = 0;
    priority_queue<pair<pair<int, int>, pair<int, int>>> edges;

    for (int i = 0; i < g_from.size(); ++i)
    {
        int criterion = g_from[i] + g_to[i] + g_weight[i];
        edges.push({{-g_weight[i], -criterion}, {g_from[i], g_to[i]}});
    }

    while (!edges.empty())
    {
        auto currentEdge = edges.top();
        edges.pop();
        addEdge({currentEdge.second.first, currentEdge.second.second});
        if (!isCycle({currentEdge.second.first, currentEdge.second.second}))
        {
            ans -= currentEdge.first.first;
        }
        else
        {
            delEdge({currentEdge.second.first, currentEdge.second.second});
        }
    }
    return ans;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++)
    {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    fout << res << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
