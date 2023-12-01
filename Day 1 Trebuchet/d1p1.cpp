#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    fstream newfile;
    newfile.open("input.txt", ios::in);
    if (newfile.is_open())
    {
        string line;
        int first = 0;
        int last = 0;
        int sum = 0;
        while (getline(newfile, line))
        {
            int len = line.length();
            for (int i = 0; i < len; ++i)
            {
                if (isdigit(line[i]))
                {
                    first = line[i] - '0';
                    break;
                }
            }
            for (int i = len - 1; i >= 0; --i)
            {
                if (isdigit(line[i]))
                {
                    last = line[i] - '0';
                    break;
                }
            }
            sum += first * 10 + last;
        }
        cout << sum << endl;
    }
    newfile.close();
    return 0;
}