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

vector<pair<long long, long long>> split_range(vector<pair<long long, long long>> prev_range, vector<vector<long long>> mapping)
{
    vector<pair<long long, long long>> retval;
    for (auto range : prev_range)
    {
        // let range go through mapping to produce new small ranges
        vector<pair<long long, long long>> seed_ranges;
        seed_ranges.push_back(range);
        for (auto map_range : mapping)
        {
            long long map_start = map_range[1];
            long long map_end = map_range[1] + map_range[2] - 1;
            vector<pair<long long, long long>> new_seed_ranges;

            for (auto seed_range : seed_ranges)
            {
                long long seed_start = seed_range.first;
                long long seed_end = seed_range.second;

                // Check if there is an intersection
                if (map_start <= seed_end && map_end >= seed_start)
                {
                    // Split the ranges as necessary
                    if (seed_start < map_start)
                    {
                        new_seed_ranges.push_back({seed_start, map_start - 1});
                    }
                    if (map_start <= seed_end && map_end >= seed_start)
                    {
                        new_seed_ranges.push_back({max(seed_start, map_start), min(seed_end, map_end)});
                    }
                    if (map_end < seed_end)
                    {
                        new_seed_ranges.push_back({map_end + 1, seed_end});
                    }
                }
                else
                {
                    // No intersection, keep the range as is
                    new_seed_ranges.push_back(seed_range);
                }
            }
            seed_ranges = new_seed_ranges;
        }
        for (auto r : seed_ranges)
        {
            if (r.first <= r.second)
            { // Ensure valid range
                retval.push_back(r);
            }
        }
    }
    return retval;
}

vector<pair<long long, long long>> map_new_range(vector<pair<long long, long long>> source, vector<vector<long long>> dest)
{
    vector<pair<long long, long long>> retval;
    for (auto range : source)
    {
        long long source_start = range.first;
        long long source_end = range.second;
        long long new_start = -1;
        long long new_end = -1;
        // map source_start and source_end through mapping
        for (auto dest_range : dest)
        {
            if (source_start >= dest_range[1] && source_start < dest_range[1] + dest_range[2])
            {
                new_start = dest_range[0] + source_start - dest_range[1];
                new_end = new_start + (source_end - source_start);
                retval.emplace_back(make_pair(new_start, new_end));
                break;
            }
        }
        if (new_start == -1)
        {
            retval.emplace_back(make_pair(source_start, source_end));
        }
    }
    return retval;
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

        int num_seeds = seeds.size();
        long long min_location = LONG_MAX;

        for (int i = 0; i < num_seeds; i += 2)
        {
            // for each pair of seeds, split range and only check about the start of each splitted range
            long long seed_start = seeds[i];
            long long seed_end = seed_start + seeds[i + 1] - 1;

            vector<pair<long long, long long>> range;
            range.push_back(make_pair(seed_start, seed_end));

            // process range
            range = split_range(range, seed_to_soil);
            range = map_new_range(range, seed_to_soil);
            // cout << range.size() << endl;

            range = split_range(range, soil_to_fertilizer);
            range = map_new_range(range, soil_to_fertilizer);
            // cout << range.size() << endl;

            range = split_range(range, fertilizer_to_water);
            range = map_new_range(range, fertilizer_to_water);
            // cout << range.size() << endl;

            range = split_range(range, water_to_light);
            range = map_new_range(range, water_to_light);
            // cout << range.size() << endl;

            range = split_range(range, light_to_temperature);
            range = map_new_range(range, light_to_temperature);
            // cout << range.size() << endl;

            range = split_range(range, temperature_to_humidity);
            range = map_new_range(range, temperature_to_humidity);
            // cout << range.size() << endl;

            range = split_range(range, humidity_to_location);
            range = map_new_range(range, humidity_to_location);
            // cout << range.size() << endl;

            for (auto location_range : range)
            {
                if (location_range.first < min_location)
                {
                    min_location = location_range.first;
                }
            }
        }

        cout << min_location << endl;
    }
    newfile.close();
    return 0;
}
// 313045984
// 20283860