#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool is_bipartite(const vector<vector<int>> &graph, int num_bugs)
{
    vector<int> color(num_bugs + 1, -1); // -1 means uncolored

    for (int start = 1; start <= num_bugs; ++start)
    {
        if (color[start] == -1)
        { // Not colored yet
            queue<int> q;
            q.push(start);
            color[start] = 0; // Start coloring with 0

            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                int current_color = color[node];

                for (int neighbor : graph[node])
                {
                    if (color[neighbor] == -1)
                    {
                        // Assign opposite color to neighbor
                        color[neighbor] = 1 - current_color;
                        q.push(neighbor);
                    }
                    else if (color[neighbor] == current_color)
                    {
                        // Found same color neighbor
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void check_scenarios(int num_scenarios)
{
    for (int i = 1; i <= num_scenarios; ++i)
    {
        int num_bugs, num_interactions;
        cin >> num_bugs >> num_interactions;

        vector<vector<int>> graph(num_bugs + 1);
        for (int j = 0; j < num_interactions; ++j)
        {
            int bug1, bug2;
            cin >> bug1 >> bug2;
            graph[bug1].push_back(bug2);
            graph[bug2].push_back(bug1);
        }

        if (is_bipartite(graph, num_bugs))
        {
            cout << "Scenario #" << i << ":\nNo suspicious bugs found!\n";
        }
        else
        {
            cout << "Scenario #" << i << ":\nSuspicious bugs found!\n";
        }
    }
}

int main()
{
    int num_scenarios;
    cin >> num_scenarios;
    check_scenarios(num_scenarios);
    return 0;
}