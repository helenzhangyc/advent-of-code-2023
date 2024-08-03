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

        unordered_map<int, bool> emptyRow;
        unordered_map<int, bool> emptyCol;

        // row
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
                emptyRow[i] = true;
            }
            else
            {
                emptyRow[i] = false;
            }
        }

        // col
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
                emptyCol[j] = true;
            }
            else
            {
                emptyCol[j] = false;
            }
        }

        // find shortest path between each pair of galaxy and add them up
        unsigned long long result = 0;
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
                int g1r = galaxy_location[i].first;
                int g1c = galaxy_location[i].second;
                int g2r = galaxy_location[j].first;
                int g2c = galaxy_location[j].second;
                for (int k = min(g1r, g2r); k < max(g1r, g2r); ++k)
                {
                    if (emptyRow[k])
                    {
                        result += 999999;
                    }
                }
                for (int k = min(g1c, g2c); k < max(g1c, g2c); ++k)
                {
                    if (emptyCol[k])
                    {
                        result += 999999;
                    }
                }
            }
        }
        cout << result << endl;
        newfile.close();
        return 0;
    }
}