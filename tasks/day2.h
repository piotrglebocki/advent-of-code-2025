#pragma once

#include <iostream>
#include <utils.h>
#include <array>

using namespace std;

vector<pair<long long, long long>> read_intervals() {
    vector<pair<long long, long long>> results;
    auto lines = read_string_lines("data.txt");
    for (auto& line : lines) {
        auto words = split(line, ',');
        for (auto word : words) {
            if (word.size() == 0) continue;
            auto s = split(word, '-');
            results.emplace_back(stoll(s[0]), stoll(s[1]));
        }
    }
    return results;
}

bool is_invalid(long long number) {
    string array = to_string(number);
    const size_t size = array.size();
    if (size % 2 == 1) {
        return false;
    }

    for (size_t i = 0; i < size / 2; ++i) {
        if (array[i] != array[i + size / 2]) {
            return false;
        }
    }

    return true;
}

bool is_invalid_2(long long number) {
    string array = to_string(number);
    const size_t size = array.size();

    for (int repeats = 2; repeats <= size; ++repeats) {
        if (size % repeats != 0) {
            continue;
        }

        int pattern_len = size / repeats;
        bool invalid = true;

        for (int i = 0; i < pattern_len; ++i) {
            for (int r = 1; r < repeats; ++r) {
                if (array[i] != array[i + r * pattern_len]) {
                    invalid = false;
                    break;
                }
            }
        }

        if (invalid) return true;
    }

    return false;
}

void solve1() {
    auto intervals = read_intervals();
    long long sum = 0;
    for (auto& [start, end]: intervals) {
        for (long long i = start; i <= end; ++i) {
            if (is_invalid(i)) sum += i;
        }
    }
    cout << sum << endl;
}

void solve2() {
    auto intervals = read_intervals();
    long long sum = 0;
    for (auto& [start, end]: intervals) {
        for (long long i = start; i <= end; ++i) {
            if (is_invalid_2(i)) sum += i;
        }
    }
    cout << sum << endl;
}