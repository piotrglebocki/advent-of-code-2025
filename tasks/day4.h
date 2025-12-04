#pragma once

#include <iostream>
#include <utils.h>
#include <array>

using namespace std;

// ========== PART 1 ============================

vector<pair<int, int>> DIRS = {
    {-1, -1}, 
    {0, -1},
    {1, -1},
    {-1, 0}, 
    {1, 0},
    {-1, 1}, 
    {0, 1},
    {1, 1}
};

int count_neighbour_rolls(const vector<vector<char>>& grid, int r, int c) {
    const auto rows = grid.size();
    const auto cols = grid.front().size();
    int res = 0;

    for (auto& [dr, dc] : DIRS) {
        int nr = r + dr;
        int nc = c + dc;
        if (0 <= nr && nr < rows && 0 <= c && c < cols) {
            if (grid[nr][nc] == '@') {
                ++res;
            }
        }
    }

    return res;
}

void solve1() {
    auto grid = read_char_lines("data.txt");
    int count = 0;

    // print_grid(grid);
    
    for (int r = 0; r < grid.size(); ++r)
    for (int c = 0; c < grid.front().size(); ++c) {
        if (grid[r][c] == '@' && count_neighbour_rolls(grid, r, c) < 4) {
            ++count;
        }
    }

    cout << count << endl;
}

// ========== PART 2 ============================

// vector<pair<int, int>> get_neighbour_rolls(const vector<vector<char>>& grid, int r, int c) {
//     const auto rows = grid.size();
//     const auto cols = grid.front().size();
//     vector<pair<int, int>> res;

//     for (auto& [dr, dc] : DIRS) {
//         int nr = r + dr;
//         int nc = c + dc;
//         if (0 <= nr && nr < rows && 0 <= c && c < cols) {
//             if (grid[nr][nc] == '@') {
//                 res.emplace_back(nr, nc);
//             }
//         }
//     }

//     return res;
// }

void solve2() {
    auto grid = read_char_lines("data.txt");
    int count = 0;

    while (true) {
        int removed = 0;
        vector<pair<int, int>> to_be_removed;

        for (int r = 0; r < grid.size(); ++r)
        for (int c = 0; c < grid.front().size(); ++c) {
            if (grid[r][c] == '@' && count_neighbour_rolls(grid, r, c) < 4) {
                to_be_removed.emplace_back(r, c);
            }
        }
        
        if (to_be_removed.empty()) {
            break;
        }

        for (auto& [r, c] : to_be_removed) {
            grid[r][c] = '.';
        }
        count += to_be_removed.size();
    }

    cout << count << endl;
}