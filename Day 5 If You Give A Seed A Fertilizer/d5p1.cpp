#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
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
        vector<long long> seeds;
        vector<vector<long long>> seed_to_soil;
        vector<vector<long long>> soil_to_fertilizer;
        vector<vector<long long>> fertilizer_to_water;
        vector<vector<long long>> water_to_light;
        vector<vector<long long>> light_to_temperature;
        vector<vector<long long>> temperature_to_humidity;
        vector<vector<long long>> humidity_to_location;
        while (getline(newfile, line))
        {
            if (line.find("seeds:") != string::npos)
            {
                line = line.substr(7);
                vector<string> tmp = split_str(line, ' ');
                for (auto i : tmp)
                {
                    seeds.push_back(stoull(i));
                }
            }
            else if (line.find("seed-to-soil map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    seed_to_soil.push_back(tmp_vector);
                    getline(newfile, line);
                }
            }
            else if (line.find("soil-to-fertilizer map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    soil_to_fertilizer.push_back(tmp_vector);
                    getline(newfile, line);
                }
            }
            else if (line.find("fertilizer-to-water map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    fertilizer_to_water.push_back(tmp_vector);
                    getline(newfile, line);
                }
            }
            else if (line.find("water-to-light map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    water_to_light.push_back(tmp_vector);
                    getline(newfile, line);
                }
            }
            else if (line.find("light-to-temperature map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    light_to_temperature.push_back(tmp_vector);
                    getline(newfile, line);
                }
            }
            else if (line.find("temperature-to-humidity map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    temperature_to_humidity.push_back(tmp_vector);
                    getline(newfile, line);
                }
            }
            else if (line.find("humidity-to-location map:") != string::npos)
            {
                getline(newfile, line);
                while (line != "")
                {
                    vector<string> tmp = split_str(line, ' ');
                    vector<long long> tmp_vector;
                    for (int i = 0; i < 3; ++i)
                    {
                        tmp_vector.push_back(stoull(tmp[i]));
                    }
                    humidity_to_location.push_back(tmp_vector);
                    if (!getline(newfile, line))
                    {
                        break;
                    }
                }
            }
        }
        // find final location for each seed
        long long min_location = LONG_MAX;
        long long soil = -1;
        long long fertilizer = -1;
        long long water = -1;
        long long light = -1;
        long long temperature = -1;
        long long humidity = -1;
        long long location = -1;
        for (auto seed_id : seeds)
        {
            // get soil
            for (auto seed : seed_to_soil)
            {
                if (seed_id >= seed[1] && seed_id < seed[1] + seed[2])
                {
                    soil = seed[0] + seed_id - seed[1];
                    break;
                }
            }
            if (soil == -1)
            {
                soil = seed_id;
            }
            // get fertilizer
            for (auto item : soil_to_fertilizer)
            {
                if (soil >= item[1] && soil < item[1] + item[2])
                {
                    fertilizer = item[0] + soil - item[1];
                    break;
                }
            }
            if (fertilizer == -1)
            {
                fertilizer = soil;
            }
            // get water
            for (auto item : fertilizer_to_water)
            {
                if (fertilizer >= item[1] && fertilizer < item[1] + item[2])
                {
                    water = item[0] + fertilizer - item[1];
                    break;
                }
            }
            if (water == -1)
            {
                water = fertilizer;
            }
            // get light
            for (auto item : water_to_light)
            {
                if (water >= item[1] && water < item[1] + item[2])
                {
                    light = item[0] + water - item[1];
                    break;
                }
            }
            if (light == -1)
            {
                light = water;
            }
            // get temperature
            for (auto item : light_to_temperature)
            {
                if (light >= item[1] && light < item[1] + item[2])
                {
                    temperature = item[0] + light - item[1];
                    break;
                }
            }
            if (temperature == -1)
            {
                temperature = light;
            }
            // get humidity
            for (auto item : temperature_to_humidity)
            {
                if (temperature >= item[1] && temperature < item[1] + item[2])
                {
                    humidity = item[0] + temperature - item[1];
                    break;
                }
            }
            if (humidity == -1)
            {
                humidity = temperature;
            }
            // get location
            for (auto item : humidity_to_location)
            {
                if (humidity >= item[1] && humidity < item[1] + item[2])
                {
                    location = item[0] + humidity - item[1];
                    break;
                }
            }
            if (location == -1)
            {
                location = humidity;
            }
            if (location < min_location)
            {
                min_location = location;
            }
            // change everything to -1 again
            soil = -1;
            fertilizer = -1;
            water = -1;
            light = -1;
            temperature = -1;
            humidity = -1;
            location = -1;
        }
        cout << min_location << endl;
    }
    newfile.close();
    return 0;
}