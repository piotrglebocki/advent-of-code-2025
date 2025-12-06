#pragma once

#include <iostream>
#include <utils.h>
#include <array>

using namespace std;

// ========== PART 1 ============================

vector<long long> parse_numbers_line(const string& line) {
    vector<long long> result;
    string current = "";
    for (auto c : line) {
        if (c == ' ') {
            if (!current.empty()) {
                result.push_back(stoll(current));
                current = "";
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        result.push_back(stoll(current));
    }
    return result;
}

vector<char> parse_signs_line(const string& line) {
    vector<char> result;
    for (auto c : line) {
        if (c != ' ') {
            result.push_back(c);
        }
    }
    return result;
}

void solve1() {
    auto lines = read_string_lines("data.txt");
    auto signs = parse_signs_line(lines.back());

    auto results = parse_numbers_line(lines.front());

    for (size_t i = 1; i < lines.size() - 1; ++i) {
        auto numbers = parse_numbers_line(lines[i]);
        for (int j = 0; j < numbers.size(); ++j) {
            if (signs[j] == '*') {
                results[j] *= numbers[j];
            } else {
                results[j] += numbers[j];
            }
        }
        cout << endl;
    }

    long long sum = 0;
    for (auto it : results) sum += it;

    cout << sum << endl;
}

// ========== PART 2 ============================


void solve2() {
    auto grid = read_char_lines("data.txt");
    const size_t ROWS = grid.size();
    const size_t COLS = grid.front().size();
    vector<long long> numbers(COLS, 0L);

    for (size_t r = 0; r < ROWS - 1; ++r)
    for (size_t c = 0; c < COLS; ++c)
        if (grid[r][c] != ' ') 
            numbers[c] = numbers[c] * 10L + (long long)(grid[r][c] - '0');

    vector<pair<size_t, size_t>> operations;
    size_t index = 0;
    size_t count = 1;

    for (size_t i = 1; i < COLS; ++i) {
        const char operation = grid[ROWS - 1][i];
        if (operation != ' ') {
            operations.emplace_back(index, count - 1);
            index = i;
            count = 1;
        } else if (i == COLS - 1) {
            operations.emplace_back(index, count + 1);
        } else {
            ++count;
        }
    }

    // for (auto [i, c] : operations) {
    //     cout << i<< ":" << c << endl;
    // }

    long long sum = 0;
    for (auto& [index, count]: operations) {
        const char operation = grid[ROWS - 1][index];
        long long x = numbers[index];
        for (int i = 1; i < count; ++i) {
            if (operation == '*') x *= numbers[index + i];
            else x += numbers[index + i];
        }

        sum += x;
    }

    cout << sum << endl;
}