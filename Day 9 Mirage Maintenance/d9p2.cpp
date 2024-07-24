#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<int> splitStr(string &str)
{
    istringstream iss(str);
    vector<int> result;
    int number;

    while (iss >> number)
    {
        result.push_back(number);
    }

    return result;
}

// check if a vector is all zero
bool allZero(vector<int> v)
{
    for (auto i : v)
    {
        if (i != 0)
        {
            return false;
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
        unsigned long long result = 0;
        while (getline(newfile, line))
        {
            bool negate = true;
            vector<int> values = splitStr(line);
            // add up values[-1] with all the last terms in each row of series
            vector<int> series;
            int length = values.size();
            int first_term = values[0];
            while (true)
            {
                length = values.size();
                for (int i = 0; i < length - 1; ++i)
                {
                    int curr_term = values[i + 1] - values[i];
                    series.push_back(curr_term);
                }
                if (allZero(series))
                {
                    break;
                }
                if (negate)
                {
                    first_term -= series[0];
                }
                else
                {
                    first_term += series[0];
                }

                values = series;
                series.clear();
                negate = !negate;
            }
            result += (unsigned long long)first_term;
        }
        cout << result << endl;
    }
    newfile.close();
    return 0;
}