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

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;
        vector<vector<char>> grid;
        while (getline(newfile, line))
        {
            vector<char> tmp;
            for (char c : line)
            {
                tmp.push_back(c);
            }
            grid.push_back(tmp);
        }

        // universe expand

        // expand row
        for (int i = 0; i < grid.size(); ++i)
        {
            bool galaxy = false;
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '#')
                {
                    galaxy = true;
                }
            }
            if (!galaxy)
            {
                vector<char> tmp(grid[0].size(), '.');
                grid.insert(grid.begin() + i, tmp);
                i++;
            }
        }

        // expand col
        vector<int> col_to_append;
        for (int j = 0; j < grid[0].size(); ++j)
        {
            bool galaxy = false;
            for (int i = 0; i < grid.size(); ++i)
            {
                if (grid[i][j] == '#')
                {
                    galaxy = true;
                }
            }
            if (!galaxy)
            {
                col_to_append.push_back(j);
            }
        }
        for (int i = 0; i < grid.size(); ++i)
        {
            // process grid[i]
            int offset = 0;
            for (auto c : col_to_append)
            {
                grid[i].insert(grid[i].begin() + c + offset, '.');
                offset++;
            }
        }

        // find shortest path between each pair of galaxy and add them up
        int result = 0;
        vector<pair<int, int>> galaxy_location;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '#')
                {
                    galaxy_location.push_back(make_pair(i, j));
                }
            }
        }

        // calculate location
        int num_galaxy = galaxy_location.size();
        for (int i = 0; i < num_galaxy; ++i)
        {
            for (int j = i + 1; j < num_galaxy; ++j)
            {
                result += abs(galaxy_location[i].first - galaxy_location[j].first) + abs(galaxy_location[i].second - galaxy_location[j].second);
            }
        }
        cout << result << endl;
    }
    newfile.close();
    return 0;
}