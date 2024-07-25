#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;

unordered_map<char, vector<pair<int, int>>> pipe_connections = {
    {'|', {{-1, 0}, {1, 0}}},
    {'-', {{0, -1}, {0, 1}}},
    {'L', {{-1, 0}, {0, 1}}},
    {'J', {{-1, 0}, {0, -1}}},
    {'7', {{1, 0}, {0, -1}}},
    {'F', {{1, 0}, {0, 1}}},
    {'S', {{-1, 0}, {1, 0}}}};

vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool canGo(char from, char to, int dx, int dy)
{
    auto it_from = pipe_connections.find(from);
    auto it_to = pipe_connections.find(to);

    for (auto connection : it_from->second)
    {
        if (connection.first == dx && connection.second == dy)
        {
            for (auto backwards_connection : it_to->second)
            {
                if (backwards_connection.first == -dx && backwards_connection.second == -dy)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool dfs(int x, int y, int px, int py, vector<vector<char>> &grid, vector<vector<bool>> &visited, unordered_map<int, pair<int, int>> &parent, pair<int, int> &cycle_start, pair<int, int> &cycle_end)
{
    visited[x][y] = true;
    int row = grid.size();
    int col = grid.size();
    char current_pipe = grid[x][y];

    for (auto dir : pipe_connections[current_pipe])
    {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (nx < 0 || ny < 0 || nx >= row || ny >= col || grid[nx][ny] == '.')
        {
            continue;
        }

        if (canGo(current_pipe, grid[nx][ny], dir.first, dir.second))
        {
            if (!visited[nx][ny])
            {
                parent[nx * row + ny] = {x, y};
                if (dfs(nx, ny, x, y, grid, visited, parent, cycle_start, cycle_end))
                {
                    return true;
                }
            }
            else if (!(nx == px && ny == py))
            {
                cycle_start = {x, y};
                cycle_end = {nx, ny};
                return true;
            }
        }
    }
    return false;
}

int findCycleLength(vector<vector<char>> &grid, pair<int, int> start, vector<vector<bool>> &visited, vector<pair<int, int>> &cycle_nodes)
{
    int row = grid.size();
    int col = grid[0].size();

    unordered_map<int, pair<int, int>> parent;
    pair<int, int> cycle_start = {-1, -1};
    pair<int, int> cycle_end = {-1, -1};

    // keep track of the cycle
    parent[start.first * row + start.second] = {-1, -1};
    dfs(start.first, start.second, -1, -1, grid, visited, parent, cycle_start, cycle_end);

    int cycle_length = 1;
    pair<int, int> current = cycle_start;
    while (current != cycle_end)
    {
        cycle_length++;
        cycle_nodes.push_back(current);
        current = parent[current.first * row + current.second];
    }
    cycle_length++;
    cycle_nodes.push_back(cycle_end);
    return cycle_length;
}

double shoelace(vector<pair<int, int>> &points)
{
    double area = 0;
    int n = points.size();
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        area += points[i].first * points[j].second;
        area -= points[i].second * points[j].first;
    }
    return abs(area) / 2.0;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int countBoundaryPoints(vector<pair<int, int>> &points)
{
    int boundary_points = 0;
    int n = points.size();
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        int dx = abs(points[j].first - points[i].first);
        int dy = abs(points[j].second - points[i].second);
        boundary_points += gcd(dx, dy);
    }
    return boundary_points;
}

int countEnclosedTiles(vector<pair<int, int>> &cycle_nodes)
{
    double area = shoelace(cycle_nodes);
    int boundary_points = countBoundaryPoints(cycle_nodes);
    int interior_points = static_cast<int>(area - boundary_points / 2.0 + 1);
    return interior_points;
}

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;
        vector<vector<char>> graph;
        while (getline(newfile, line))
        {
            vector<char> tmp;
            for (char c : line)
            {
                tmp.push_back(c);
            }
            graph.push_back(tmp);
        }

        int row = graph.size();
        int col = graph[0].size();
        pair<int, int> start;
        for (int r = 0; r < row; ++r)
        {
            for (int c = 0; c < col; ++c)
            {
                if (graph[r][c] == 'S')
                {
                    start = {r, c};
                }
            }
        }
        vector<vector<bool>> visited(graph.size(), vector<bool>(graph[0].size(), false));
        vector<pair<int, int>> cycle_nodes;
        int cycle_length = findCycleLength(graph, start, visited, cycle_nodes);

        int enclosed_tiles = countEnclosedTiles(cycle_nodes);
        cout << enclosed_tiles << endl;
    }
    newfile.close();
    return 0;
}