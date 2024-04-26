#include <bits/stdc++.h>
#define N 100005 

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct DSU
{
    vector<int> parent;
    vector<int> rank;

    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y)
    {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y)
        {
            if (rank[root_x] < rank[root_y])
                swap(root_x, root_y);
            parent[root_y] = root_x;
            rank[root_x] += rank[root_y];
        }
    }
};

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> &cities)
{
    if (c_lib <= c_road)
        return (long)n * c_lib;

    DSU dsu(n);
    for (auto &road : cities)
        dsu.unite(road[0], road[1]);

    unordered_set<int> main_houses;
    for (int i = 1; i <= n; ++i)
        main_houses.insert(dsu.find(i));

    long total_cost = 0;
    for (int house : main_houses)
        total_cost += c_lib + (dsu.rank[house] - 1) * c_road;

    return total_cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);
        int m = stoi(first_multiple_input[1]);
        int c_lib = stoi(first_multiple_input[2]);
        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++)
        {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++)
            {
                int cities_row_item = stoi(cities_row_temp[j]);
                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

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
