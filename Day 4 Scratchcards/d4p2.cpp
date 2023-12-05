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
        int sum = 0;
        string line;
        vector<int> points;
        while (getline(newfile, line))
        {
            int num = 0;
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
            for (auto n : my_numbers)
            {
                if (count(winning_numbers.begin(), winning_numbers.end(), n))
                {
                    num++;
                }
            }
            points.push_back(num);
        }
        // process points
        int num_cards = points.size();
        vector<int> cards;
        for (int i = 0; i < num_cards; ++i)
        {
            cards.push_back(1);
        }
        for (int i = 0; i < num_cards; ++i)
        {
            for (int x = 0; x < cards[i]; ++x)
            {
                for (int j = 1; j <= points[i]; ++j)
                {
                    cards[i + j]++;
                }
            }
        }
        // add up cards
        for (auto i : cards)
        {
            sum += i;
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}