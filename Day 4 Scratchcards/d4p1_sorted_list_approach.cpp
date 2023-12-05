#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<string> split_str(string s, char delimiter)
{
    stringstream ss(s);
    vector<string> result;

    while (ss.good())
    {
        string substr;
        getline(ss, substr, delimiter);
        result.push_back(substr);
    }
    return result;
}

int main()
{
    auto start = high_resolution_clock::now();
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        int sum = 0;
        string line;
        while (getline(newfile, line))
        {
            int point = 0;
            line = line.substr(line.find(":") + 2);
            vector<string> tmp = split_str(line, '|');
            string winning = tmp[0];
            string mine = tmp[1];
            vector<int> winning_numbers;
            vector<int> my_numbers;
            vector<string> winning_tmp = split_str(winning, ' ');
            vector<string> mine_tmp = split_str(mine, ' ');
            for (auto i : winning_tmp)
            {
                if (i != "")
                {
                    winning_numbers.push_back(stoi(i));
                }
            }
            for (auto i : mine_tmp)
            {
                if (i != "")
                {
                    my_numbers.push_back(stoi(i));
                }
            }
            // count number of match
            // sort both vectors
            sort(winning_numbers.begin(), winning_numbers.end());
            sort(my_numbers.begin(), my_numbers.end());
            int win_i = 0;
            int my_i = 0;
            int win_size = winning_numbers.size();
            int my_size = my_numbers.size();
            while (win_i < win_size && my_i < my_size)
            {
                if (winning_numbers[win_i] < my_numbers[my_i])
                {
                    win_i++;
                }
                else if (my_numbers[my_i] < winning_numbers[win_i])
                {
                    my_i++;
                }
                else
                {
                    // number match
                    if (point == 0)
                    {
                        point = 1;
                    }
                    else
                    {
                        point *= 2;
                    }
                    win_i++;
                    my_i++;
                }
            }
            sum += point;
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}