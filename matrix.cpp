#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Union-Find functions
vector<int> parent;
vector<int> range;
vector<int> has_machine;

void initialize_union_find(int n)
{
    parent.resize(n);
    range.resize(n, 0);
    has_machine.resize(n, 0);
    iota(parent.begin(), parent.end(), 0);
}

int find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY)
    {
        if (range[rootX] > range[rootY])
        {
            parent[rootY] = rootX;
            has_machine[rootX] |= has_machine[rootY];
        }
        else if (range[rootX] < range[rootY])
        {
            parent[rootX] = rootY;
            has_machine[rootY] |= has_machine[rootX];
        }
        else
        {
            parent[rootY] = rootX;
            has_machine[rootX] |= has_machine[rootY];
            range[rootX]++;
        }
    }
}

int minTime(vector<vector<int>> roads, vector<int> machines)
{
    int n = roads.size() + 1;

    // Sort roads by destruction time in descending order
    sort(roads.begin(), roads.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[2] > b[2]; });

    initialize_union_find(n);
    for (int machine : machines)
    {
        has_machine[machine] = 1;
    }

    int total_time = 0;
    for (const auto &road : roads)
    {
        int city1 = road[0], city2 = road[1], time = road[2];
        int root1 = find(city1), root2 = find(city2);

        if (has_machine[root1] && has_machine[root2])
        {
            // If both components have machines, destroy this road
            total_time += time;
        }
        else
        {
            // Otherwise, unite the components
            union_sets(root1, root2);
        }
    }

    return total_time;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);
    int k = stoi(first_multiple_input[1]);

    vector<vector<int>> roads(n - 1);

    for (int i = 0; i < n - 1; i++)
    {
        roads[i].resize(3);

        string roads_row_temp_temp;
        getline(cin, roads_row_temp_temp);

        vector<string> roads_row_temp = split(rtrim(roads_row_temp_temp));

        for (int j = 0; j < 3; j++)
        {
            int roads_row_item = stoi(roads_row_temp[j]);
            roads[i][j] = roads_row_item;
        }
    }

    vector<int> machines(k);

    for (int i = 0; i < k; i++)
    {
        string machines_item_temp;
        getline(cin, machines_item_temp);

        int machines_item = stoi(ltrim(rtrim(machines_item_temp)));
        machines[i] = machines_item;
    }

    int result = minTime(roads, machines);

    fout << result << "\n";

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
