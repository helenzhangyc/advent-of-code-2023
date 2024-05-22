#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

vector<int> extractNumbers(const string &str)
{
    vector<int> numbers;
    istringstream iss(str);
    string temp;
    while (iss >> temp)
    {
        try
        {
            int num = stoi(temp);
            numbers.push_back(num);
        }
        catch (const invalid_argument &e)
        {
            // If conversion fails, skip the current word
        }
    }
    return numbers;
}

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line1;
        string line2;
        getline(newfile, line1);
        getline(newfile, line2);

        vector<int> time = extractNumbers(line1);
        vector<int> distance = extractNumbers(line2);

        int ways = 1;

        int num_matches = time.size();
        for (int i = 0; i < num_matches; ++i)
        {
            int win_count = 0;
            int curr_distance = 0;
            for (int t = 0; t <= time[i]; ++t)
            {
                curr_distance = t * (time[i] - t);
                if (curr_distance > distance[i])
                {
                    win_count++;
                }
            }
            ways *= win_count;
        }

        cout << ways << endl;
    }
    newfile.close();
    return 0;
}