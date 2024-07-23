#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int getHandRank(string &hand)
{
    unordered_map<char, int> frequencyMap;
    for (char card : hand)
    {
        frequencyMap[card]++;
    }
    bool hasThree = false;
    int hasTwo = 0;
    for (auto &pair : frequencyMap)
    {
        // five of a kind
        if (pair.second == 5)
        {
            return 7;
        }
        // four of a kind
        else if (pair.second == 4)
        {
            return 6;
        }
        else if (pair.second == 3)
        {
            hasThree = true;
        }
        else if (pair.second == 2)
        {
            hasTwo++;
        }
    }
    // full house
    if (hasThree && (hasTwo == 1))
    {
        return 5;
    }
    // three of a kind
    if (hasThree && (hasTwo == 0))
    {
        return 4;
    }
    // two pair
    if (hasTwo == 2)
    {
        return 3;
    }
    // one pair
    if (hasTwo == 1)
    {
        return 2;
    }
    // high card
    return 1;
}

// custom hand comparison
bool handcmp(string &h1, string &h2)
{
    unordered_map<char, int> cardRank = {
        {'2', 0},
        {'3', 1},
        {'4', 2},
        {'5', 3},
        {'6', 4},
        {'7', 5},
        {'8', 6},
        {'9', 7},
        {'T', 8},
        {'J', 9},
        {'Q', 10},
        {'K', 11},
        {'A', 12}};
    int rank1 = getHandRank(h1);
    int rank2 = getHandRank(h2);
    if (rank1 != rank2)
    {
        return rank1 < rank2;
    }
    else
    {
        for (int i = 0; i < 5; ++i)
        {
            if (h1[i] != h2[i])
            {
                return cardRank[h1[i]] < cardRank[h2[i]];
            }
        }
    }
    return true;
}

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;

        vector<pair<string, int>> handAndBid;

        while (getline(newfile, line))
        {
            string hand = line.substr(0, 5);
            string bidstr = line.substr(6, line.size() - 6);
            int bid = stoi(bidstr);
            handAndBid.push_back(make_pair(hand, bid));
        }
        sort(handAndBid.begin(), handAndBid.end(), [](pair<string, int> a, pair<string, int> b)
             { return handcmp(a.first, b.first); });
        unsigned long long sum = 0;
        int length = handAndBid.size();
        for (int i = 0; i < length; ++i)
        {
            sum += ((unsigned long long)(i + 1)) * ((unsigned long long)handAndBid[i].second);
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}