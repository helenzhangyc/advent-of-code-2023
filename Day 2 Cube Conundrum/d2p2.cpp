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
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;
        int sum = 0;
        int game = 0;
        while (getline(newfile, line))
        {
            game++;
            bool possible = true;
            line = line.substr(line.find(":") + 2);
            vector<string> splitted = split_str(line, ';');
            int max_red = 0;
            int max_blue = 0;
            int max_green = 0;
            for (auto set : splitted)
            {
                vector<string> cubes = split_str(set, ',');
                for (auto word : cubes)
                {
                    if (word[0] == ' ')
                    {
                        word = word.substr(1, word.length() - 1);
                    }
                    vector<string> cube = split_str(word, ' ');
                    int amount = stoi(cube[0]);
                    string colour = cube[1];
                    if (colour == "red")
                    {
                        if (amount > max_red)
                        {
                            max_red = amount;
                        }
                    }
                    else if (colour == "green")
                    {
                        if (amount > max_green)
                        {
                            max_green = amount;
                        }
                    }
                    else if (colour == "blue")
                    {
                        if (amount > max_blue)
                        {
                            max_blue = amount;
                        }
                    }
                }
            }
            sum += max_red * max_green * max_blue;
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}