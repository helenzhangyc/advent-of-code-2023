#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string step;
        getline(newfile, step);
        cout << step << endl;

        string empty;
        getline(newfile, empty);
        cout << empty << endl;

        string line;

        unordered_map<string, pair<string, string>> map;

        while (getline(newfile, line))
        {
            string start = line.substr(0, 3);
            string left = line.substr(7, 3);
            string right = line.substr(12, 3);
            map[start] = make_pair(left, right);
        }
        int result = 0;
        string current_position = "AAA";
        while (current_position != "ZZZ")
        {
            for (char direction : step)
            {
                if (direction == 'L')
                {
                    current_position = map[current_position].first;
                    result++;
                }
                else if (direction == 'R')
                {
                    current_position = map[current_position].second;
                    result++;
                }
                if (current_position == "ZZZ")
                {
                    cout << result << endl;
                }
            }
        }
    }
    newfile.close();
    return 0;
}