#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

string valid_digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;
        int sum = 0;
        while (getline(newfile, line))
        {
            int len = line.length();
            int tmp_index = 0;
            int tmp_first = 0;
            int tmp_last = 0;
            // number
            for (int i = 0; i < len; ++i)
            {
                if (isdigit(line[i]))
                {
                    tmp_first = line[i] - '0';
                    tmp_index = i;
                    break;
                }
            }
            // english word
            for (int i = 0; i < 9; ++i)
            {
                if (line.find(valid_digits[i]) != string::npos)
                {
                    if (line.find(valid_digits[i]) < tmp_index)
                    {
                        tmp_index = line.find(valid_digits[i]);
                        tmp_first = i + 1;
                    }
                }
            }
            sum += tmp_first * 10;
            // number
            for (int i = len - 1; i >= 0; --i)
            {
                if (isdigit(line[i]))
                {
                    tmp_last = line[i] - '0';
                    tmp_index = i;
                    break;
                }
            }
            // english word
            for (int i = 0; i < 9; ++i)
            {
                if (line.rfind(valid_digits[i]) != string::npos)
                {
                    if (line.rfind(valid_digits[i]) > tmp_index)
                    {
                        tmp_index = line.rfind(valid_digits[i]);
                        tmp_last = i + 1;
                    }
                }
            }
            sum += tmp_last;
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}