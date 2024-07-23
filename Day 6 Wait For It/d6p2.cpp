#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

long long extractAndConcatenateNumbers(const std::string &str)
{
    std::ostringstream concatenatedNumbers;
    std::istringstream iss(str);
    std::string temp;
    while (iss >> temp)
    {
        try
        {
            int num = std::stoi(temp);
            concatenatedNumbers << num;
        }
        catch (const std::invalid_argument &e)
        {
            // If conversion fails, skip the current word
        }
    }
    return std::stoll(concatenatedNumbers.str());
}

int main()
{
    cout << "main";
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line1;
        string line2;
        getline(newfile, line1);
        getline(newfile, line2);

        long long time = extractAndConcatenateNumbers(line1);
        long long distance = extractAndConcatenateNumbers(line2);

        int ways = 1;

        int win_count = 0;
        long long curr_distance = 0;
        for (long long t = 0; t <= time; ++t)
        {
            curr_distance = t * (time - t);
            if (curr_distance > distance)
            {
                win_count++;
            }
        }
        ways *= win_count;

        cout << ways << endl;
    }
    newfile.close();
    return 0;
}