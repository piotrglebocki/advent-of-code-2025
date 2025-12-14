#pragma once

#include <iostream>
#include <utils.h>
#include <array>
#include <queue>
#include "math.h"

using namespace std;

// ========== PART 1 ============================

vector<string> parse_line(const string& line) {
    vector<string> words;
    string current = "";
    for (auto c : line) {
        if (c == ':') continue;
        if (c == ' ') {
            words.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    if (!current.empty()) words.push_back(current);
    return words;
}

long long dsf(
    const string& node, 
    unordered_map<string, vector<string>> adj_list,
    unordered_map<string, long long> memo
) {
    if (node == "out") {
        return 1;
    }
    if (memo.count(node)) {
        return memo[node];
    }

    long long sum = 0;
    for (const auto& next : adj_list[node]) {
        sum += dsf(next, adj_list, memo);
    }
    return memo[node] = sum;
}

void solve1() {
    auto lines = read_string_lines("data.txt");
    unordered_map<string, vector<string>> adj_list;
    unordered_map<string, long long> memo;

    for (const auto& line : lines) {
        auto words = parse_line(line);
        auto& key = words[0];
        for (size_t i = 1; i < words.size(); ++i) {
            adj_list[key].emplace_back(words[i]);
        }
    }

    cout << dsf("you", adj_list, memo) << endl;
}