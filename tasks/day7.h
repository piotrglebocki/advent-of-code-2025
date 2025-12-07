#pragma once

#include <iostream>
#include <utils.h>
#include <array>

using namespace std;

// ========== PART 1 ============================

void solve1() {
    auto grid = read_char_lines("data.txt");
    const auto ROWS = grid.size();
    const auto COLS = grid.front().size();

    vector<vector<char>> field(ROWS, vector<char>(COLS, '.'));
    for (int c = 0; c < COLS; ++c) {
        if (grid[0][c] == 'S') {
            field[0][c] = '|';
            break;
        }
    }

    int count = 0;

    for (int r = 1; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            const auto sign = grid[r][c];
            if (field[r - 1][c] == '|') {
                if (sign == '^') {
                    if (c == 0) {
                        field[r][c + 1] = '|';
                    } else if (c == COLS - 1) {
                        field[r][c - 1] = '|';
                    } else {
                        field[r][c - 1] = '|';
                        field[r][c + 1] = '|';
                    }
                    ++count;
                } else {
                    field[r][c] = '|';
                }
            }
        }
    }

    cout << count << endl;
}

// ========== PART 2 ============================

void solve2() {
    auto grid = read_char_lines("data.txt");
    const auto ROWS = grid.size();
    const auto COLS = grid.front().size();

    vector<vector<long long>> field(ROWS, vector<long long>(COLS, 0L));
    for (int c = 0; c < COLS; ++c) {
        if (grid[0][c] == 'S') {
            field[0][c] = 1L;
            break;
        }
    }

    for (int r = 1; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            const auto sign = grid[r][c];
            const auto prev = field[r - 1][c];
            if (prev > 0) {
                if (sign == '^') {
                    if (c == 0) {
                        field[r][c + 1] += prev;
                    } else if (c == COLS - 1) {
                        field[r][c - 1] += prev;
                    } else {
                        field[r][c - 1] += prev;
                        field[r][c + 1] += prev;
                    }
                } else {
                    field[r][c] += prev;
                }
            }
        }
    }

    long long count = 0;
    for (auto it : field.back()) count += it;
    cout << count << endl;
}