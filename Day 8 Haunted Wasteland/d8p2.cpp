#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0)
    {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long lcm(unsigned long long a, unsigned long long b)
{
    return (a / gcd(a, b)) * b;
}

unsigned long long lcm_of_vector(const std::vector<int> &numbers)
{
    unsigned long long result = 1;
    for (int number : numbers)
    {
        result = lcm(result, static_cast<unsigned long long>(number));
        // Check for overflow (optional)
        if (result == 0)
        {
            throw std::overflow_error("LCM overflow occurred");
        }
    }
    return result;
}

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string step;
        getline(newfile, step);

        string empty;
        getline(newfile, empty);

        string line;

        unordered_map<string, pair<string, string>> map;

        vector<string> current_position;

        vector<int> distance;

        while (getline(newfile, line))
        {
            string start = line.substr(0, 3);
            string left = line.substr(7, 3);
            string right = line.substr(12, 3);
            map[start] = make_pair(left, right);

            if (start[2] == 'A')
            {
                current_position.push_back(start);
            }
        }

        for (auto pos : current_position)
        {
            int result = 0;
            while (pos[2] != 'Z')
            {
                for (char direction : step)
                {
                    if (direction == 'L')
                    {
                        pos = map[pos].first;
                        result++;
                    }
                    else if (direction == 'R')
                    {
                        pos = map[pos].second;
                        result++;
                    }
                }
            }
            distance.push_back(result);
        }
        cout << lcm_of_vector(distance) << endl;
    }
    newfile.close();
    return 0;
}