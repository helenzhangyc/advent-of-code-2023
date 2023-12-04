#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;
        vector<vector<char>> grid;
        // stores the location of *
        vector<pair<int, int>> engine_location;
        // stores the number corresponding to *
        vector<int> numbers;
        int sum = 0;
        while (getline(newfile, line))
        {
            vector<char> tmp(line.begin(), line.end());
            grid.push_back(tmp);
        }
        int width = grid[0].size();
        int height = grid.size();
        for (int r = 0; r < height; ++r)
        {
            for (int c = 0; c < width; ++c)
            {
                if (isdigit(grid[r][c]))
                {
                    string curr_number_str(1, grid[r][c]);
                    c++;
                    while (c < width && isdigit(grid[r][c]))
                    {
                        curr_number_str += grid[r][c];
                        c++;
                    }
                    int curr_number = stoi(curr_number_str);
                    int length = curr_number_str.length();
                    // check if there are any symbol adjacent to the number
                    for (int rr = max(0, r - 1); rr <= min(r + 1, height - 1); ++rr)
                    {
                        for (int cc = max(0, c - length - 1); cc <= min(c, width - 1); ++cc)
                        {
                            if (grid[rr][cc] == '*')
                            {
                                // store the position of * and the number if not exist
                                // add to sum if it already exists
                                pair<int, int> curr_star_location = make_pair(rr, cc);
                                bool found = false;
                                for (int i = 0; i < engine_location.size(); ++i)
                                {
                                    if (engine_location[i] == curr_star_location)
                                    {
                                        found = true;
                                        sum += curr_number * numbers[i];
                                        break;
                                    }
                                }
                                if (!found)
                                {
                                    engine_location.push_back(curr_star_location);
                                    numbers.push_back(curr_number);
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}