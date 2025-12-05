#pragma once

#include <iostream>
#include <utils.h>
#include <array>

using namespace std;

// ========== PART 1 ============================

void solve1() {
    auto lines = read_string_lines("data.txt");
    vector<pair<long long, long long>> intervals;
    vector<long long> numbers;

    bool read_interval = true;
    for (const auto& line : lines) {
        if (line == "") {
            read_interval = false;
            continue;
        }
        if (read_interval) {
            auto tab = split(line, '-');
            intervals.emplace_back(stoll(tab[0]), stoll(tab[1]));
        } else {
            numbers.push_back(stoll(line));
        }
    }

    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    });

    int count = 0;

    for (auto num : numbers) {
        for (auto& [start, end] : intervals) {
            if (num < start) break;
            if (start <= num && num <= end) {
                ++count;
                break;
            }
        }
    }

    cout << count << endl;
}

// ========== PART 2 ============================

void solve2() {
    auto lines = read_string_lines("data.txt");
    vector<pair<long long, long long>> intervals;

    for (const auto& line : lines) {
        if (line == "") {
            break;;
        }
        auto tab = split(line, '-');
        intervals.emplace_back(stoll(tab[0]), stoll(tab[1]));
    }

    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    });

    long long count = 0;

    long long it = intervals.front().first;

    for (auto& [start, end] : intervals) {
        if (it > end) continue;;
        it = max(it, start);
        count += end - it + 1;
        it = end + 1;
    }


    cout << count << endl;
}