#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define RED 12
#define GREEN 13
#define BLUE 14

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
                    if (colour == "red" && amount > RED)
                    {
                        possible = false;
                    }
                    else if (colour == "green" && amount > GREEN)
                    {
                        possible = false;
                    }
                    else if (colour == "blue" && amount > BLUE)
                    {
                        possible = false;
                    }
                }
            }
            if (possible)
            {
                sum += game;
            }
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}