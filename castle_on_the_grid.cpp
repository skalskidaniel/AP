#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */

struct PointDistance
{
    int x, y;
    int distance;
};

const int X_MOVES[] = {0, 1, 0, -1};
const int Y_MOVES[] = {1, 0, -1, 0};

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY)
{
    int grid_size = grid.size();
    vector<vector<bool>> visited(grid_size, vector<bool>(grid_size));
    queue<PointDistance> distances_queue;

    distances_queue.push({startX, startY, 0});
    visited[startX][startY] = true;

    while (!distances_queue.empty())
    {
        PointDistance current_point_distance = distances_queue.front();
        distances_queue.pop();

        if (current_point_distance.x == goalX && current_point_distance.y == goalY)
            return current_point_distance.distance;

        int x = current_point_distance.x;
        int y = current_point_distance.y;

        for (int dir = 0; dir < 4; dir++)
        {
            int dx = X_MOVES[dir], dy = Y_MOVES[dir];

            for (int i = x + dx, j = y + dy;
                 i < grid_size && i >= 0 && j < grid_size && j >= 0 && grid[i][j] == '.';
                 i = i + dx, j = j + dy)
            {
                if (!visited[i][j])
                {
                    visited[i][j] = true;
                    distances_queue.push({i, j, current_point_distance.distance + 1});
                }
            }
        }
    }
    return -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++)
    {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

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
