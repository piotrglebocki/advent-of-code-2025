#pragma once

#include <iostream>
#include <utils.h>
#include <array>
#include "math.h"

using namespace std;

// ========== PART 1 ============================

void solve1() {
    auto lines = read_string_lines("data.txt");
    vector<pair<long, long>> numbers;
    numbers.reserve(lines.size());

    for (const auto& line : lines) {
        auto vec = split(line, ',');
        numbers.emplace_back(stol(vec[0]), stol(vec[1]));
    }

    long long max_area = 0;
    for (size_t i = 0; i < numbers.size() - 1; ++i) {
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            long long area = (abs(numbers[i].first - numbers[j].first) + 1) * (abs(numbers[i].second - numbers[j].second) + 1);
            max_area = max(max_area, area);
        }
    }
    cout << max_area << endl;
}

// ========== PART 2 ============================

struct Cell {
    long r, c;
};

struct BBox {
    long left, right, top, bottom;
};

void draw_border(vector<vector<char>>& grid, const vector<Cell>& numbers) {
    cout << "draw_border: start" << endl;

    for (size_t i = 0; i < numbers.size(); ++i) {
        const auto pt1 = numbers[i];
        const auto pt2 = numbers[(i+1) % numbers.size()];
        grid[pt1.r][pt1.c] = '#';
        grid[pt2.r][pt2.c] = '#';

        if (pt1.r == pt2.r) { // in the same row
            auto from = min(pt1.c, pt2.c);
            auto to = max(pt1.c, pt2.c);
            for (int c = from + 1; c < to; ++c) grid[pt1.r][c] = 'X';
        } else { // in the same column
            auto from = min(pt1.r, pt2.r);
            auto to = max(pt1.r, pt2.r);
            for (int r = from + 1; r < to; ++r) grid[r][pt1.c] = 'X';
        }
    }

    cout << "draw_border: end" << endl;
}

void colour_polygon(vector<vector<char>>& grid) {
    cout << "colour_polygon: start" << endl;

    const auto ROWS = grid.size();
    const auto COLS = grid.front().size();

    queue<Cell> q;
    q.push({0, 0});

    vector<pair<int, int>> DIRS = {
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}
    };

    while (!q.empty()) {
        cout << q.size() << endl;
        auto current = q.front(); q.pop();
        grid[current.r][current.c] = ' ';

        for (auto& [dr, dc] : DIRS) {
            auto nr = current.r + dr;
            auto nc = current.c + dc;

            if (0 <= nr && nr < ROWS && 0 <= nc && nc < COLS && grid[nr][nc] == '.') {
                grid[nr][nc] = ' ';
                q.push({nr, nc});
            }
        }
    }

    for (size_t r = 0; r < ROWS; ++r) 
    for (size_t c = 0; c < COLS; ++c)
        if (grid[r][c] == ' ') grid[r][c] = '.';
        else if (grid[r][c] == '.') grid[r][c] = 'X';

    cout << "colour_polygon: end" << endl;
}

bool is_inside(const vector<vector<char>>& grid, const BBox& bbox, long r, long c) {
    if (r <= bbox.top || r >= bbox.bottom || c <= bbox.left || c >= bbox.right) {
        return false;
    }
    
    if (grid[r][c] != '.') {
        return false;
    }

    int i = c + 1;
    int cross_count = 0;
    while (i < grid.front().size()) {
        if (grid[r][i] != '.') {
            while (grid[r][i+1] != '.') ++i;
            ++cross_count;
        }
        ++i;
    }

    return cross_count % 2 == 1;
}

// void colour_polygon_2(vector<vector<char>>& grid, const BBox& bbox) {
//     const auto ROWS = grid.size();
//     const auto COLS = grid.front().size();

//     for (size_t r = 1; r < ROWS; ++r) 
//     for (size_t c = 0; c < COLS; ++c)
//         if (is_inside(grid, bbox, r, c)) grid[r][c] = 'X';
// }

void solve2() {
    auto lines = read_string_lines("data.txt");
    vector<Cell> numbers;
    numbers.reserve(lines.size());
    long max_r = 0, max_c = 0, min_r = LONG_MAX, min_c = LONG_MAX;

    for (const auto& line : lines) {
        auto vec = split(line, ',');
        long c = stol(vec[0]);
        long r = stol(vec[1]);
        numbers.push_back({r, c});
        max_r = max(r, max_r);
        max_c = max(c, max_c);
        min_r = min(r, min_r);
        min_c = min(c, min_c);
    }

    BBox bbox {min_c, max_c, min_r, max_r};

    const size_t ROWS = max_r + 2;
    const size_t COLS = max_c + 2;
    vector<vector<char>> grid(ROWS, vector<char>(COLS, '.'));

    draw_border(grid, numbers);
    // colour_polygon(grid);
    // colour_polygon_2(grid, bbox);
    // print_grid(grid);

    long long max_area = 0;
    for (size_t i = 0; i < numbers.size() - 1; ++i) {
        for (size_t j = i + 1; j < numbers.size(); ++j) {
            long left = min(numbers[i].c, numbers[j].c);
            long right = max(numbers[i].c, numbers[j].c);
            long top = min(numbers[i].r, numbers[j].r);
            long bottom = max(numbers[i].r, numbers[j].r);

            long center_c = (left + right) / 2;
            long center_r = (top + bottom) / 2;

            if (is_inside(grid, bbox, left + 1, top + 1)) {
                long long area = ((right - left) + 1) * ((bottom - top) + 1);
                max_area = max(max_area, area);
            }
            
        }
    }
    cout << max_area << endl;
}