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
                            if (grid[rr][cc] != '.' && !isdigit(grid[rr][cc]))
                            {
                                sum += curr_number;
                                break;
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