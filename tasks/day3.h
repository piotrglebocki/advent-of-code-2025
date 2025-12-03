#pragma once

#include <iostream>
#include <utils.h>
#include <array>

using namespace std;

// ========== PART 1 ============================

int biggest_joltable(const string& line) {
    const auto len = line.size();
    int first_max = 0;
    int first_index = 0;
    for (int i = 0; i < len - 1; ++i) {
        int digit = line[i] - '0';
        if (digit > first_max) {
            first_max = digit;
            first_index = i;
            if (digit == 9) break;
        }
    }

    int second_max = 0;
    for (int i = first_index + 1; i < len; ++i) {
        int digit = line[i] - '0';
        if (digit > second_max) {
            second_max = digit;
        }
    }

    int res = first_max * 10 + second_max;
    cout << res << endl;
    return res;
}

void solve1() {
    auto lines = read_string_lines("data.txt");
    long count = 0;
    for (const auto& line : lines) {
        count += biggest_joltable(line);
    }
    cout << count << endl;
}

// ========== PART 2 ===============================


template<size_t N>
struct Buffer {
    array<int, N> digits_;

    Buffer(array<int, N> digits) : digits_(digits) {}

    long long to_number() {
        long long num = 0;
        for (int i = 0; i < N; ++i) {
            num += digits_[N - i - 1] * pow(10, i);
        }
        return num;
    }

    void offer(int digit) {
        for (int i = 0; i < N; ++i) {
            if (digit >= digits_[i]) {
                swap(digit, digits_[i]);
            } else {
                break;
            }
        }
    }
};

array<int, 12> take_last_12(const string& line) {
    array<int, 12> result;
    for (int i = 0; i < 12; ++i) {
        result[i] = line[line.size() - 12 + i] - '0';
    }
    return result;
}

long long biggest_joltable_for_12(const string& line) {
    auto buffer = Buffer<12>(take_last_12(line));
    int it = line.size() - 12 - 1;
    while (it >= 0) {
        int digit = line[it] - '0';
        buffer.offer(digit);
        --it;
    }
    return buffer.to_number();
}


void solve2() {
    auto lines = read_string_lines("data.txt");
    long long count = 0;
    for (const auto& line : lines) {
        count += biggest_joltable_for_12(line);
    }
    cout << count << endl;
}