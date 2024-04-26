#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <climits>
#include <queue>

using namespace std;

int dijkstra(int start, int target, vector<pair<int, int>> connections[])
{
    vector<int> dist(101, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (u == target)
            return d;

        if (d > dist[u])
            continue;

        for (auto &edge : connections[u])
        {
            int v = edge.second;
            int weight = edge.first;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[target] == INT_MAX)
    {
        return -1;
    }

    return dist[target];
}

bool set_id(string x, map<string, int> locations_map)
{
    if (locations_map.count(x))
        return true;
    else
        return false;
}

void add_road(string street, int A, int B, vector<pair<int, int>> connections[])
{
    int len = stoi(street.substr(2, street.size() - 4));
    if (street[0] == '<')
    {
        connections[B].push_back({len, A});
    }
    if (street[street.size() - 1] == '>')
    {
        connections[A].push_back({len, B});
    }
}

int main()
{

    int test_number = 0, locations, broken_cars, n_of_roads;

    while (cin >> locations >> broken_cars >> n_of_roads && locations)
    {
        ++test_number;

        map<string, int> locations_map;
        vector<int> broken_cars_ids;
        vector<pair<int, int>> connections[locations + 1];
        string company_name;
        cin >> company_name;

        int i = 0;
        locations_map[company_name] = i++;

        while (broken_cars--)
        {
            string car_location;
            cin >> car_location;
            if (!set_id(car_location, locations_map))
                locations_map[car_location] = i++;
            broken_cars_ids.push_back(locations_map[car_location]);
        }

        while (n_of_roads--)
        {
            string A, street, B;
            cin >> A >> street >> B;
            if (!set_id(A, locations_map))
                locations_map[A] = i++;
            if (!set_id(B, locations_map))
                locations_map[B] = i++;
            add_road(street, locations_map[A], locations_map[B], connections);
        }

        int ans = 0;

        for (int car : broken_cars_ids)
        {
            ans += dijkstra(0, car, connections) + dijkstra(car, 0, connections);
        }

        cout << test_number << ". " << ans << endl;
    }
    return 0;
}

/*
Your program will be tested on one or more test cases. The first line of each test case specifies three numbers (N , C , and R ) separated by one or more spaces. The city has N locations with distinct names, including the company's garage. C is the number of broken cars. R is the number of roads in the city.
Note that 0 < N < 100 , 0 <= C < 1000 , and R < 10000 . The second line is made of C + 1 words,
the first being the location of the company's garage, and the rest being the locations of the broken cars.
A location is a word made of 10 letters or less. Letter case is significant. After the second line, there will be exactly R lines, each describing a road. A road is described using one of these three formats:

A --v-> B A <-v-- B A <-v-> B

A and B are names of two different locations, while v is a positive integer (not exceeding 1000) denoting the length of the road. The first format specifies a one-way street from location A to B , the second specifies a one-way street from B to A , while the last specifies a two-way street between them. A , "the arrow", and B are separated by one or more spaces. The end of the test cases is specified with a line having three zeros (for N , C , and R .)
*/