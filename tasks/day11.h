#pragma once

#include <iostream>
#include <utils.h>
#include <array>
#include <queue>
#include <unordered_set>
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
    unordered_map<string, vector<string>>& adj_list,
    unordered_map<string, long long>& memo
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

// ========== PART 2 ============================

static inline int add_mask_for(const string& node) {
    int m = 0;
    if (node == "dac") m |= 1;
    if (node == "fft") m |= 2;
    return m;
}

long long dsf2(
    const string& node,
    int mask,
    unordered_map<string, vector<string>>& adj_list,
    unordered_map<string, array<long long, 4>>& memo,
    unordered_map<string, array<char, 4>>& seen
) {
    mask |= add_mask_for(node);

    if (node == "out") {
        return (mask == 3) ? 1LL : 0LL;
    }

    if (seen[node][mask]) {
        return memo[node][mask];
    }
    seen[node][mask] = 1;

    long long sum = 0;
    for (const auto& next : adj_list[node]) {
        sum += dsf2(next, mask, adj_list, memo, seen);
    }

    memo[node][mask] = sum;
    return sum;
}

void solve2() {
    auto lines = read_string_lines("data.txt");
    unordered_map<string, vector<string>> adj_list;

    for (const auto& line : lines) {
        auto words = parse_line(line);
        auto& key = words[0];
        for (size_t i = 1; i < words.size(); ++i) {
            adj_list[key].emplace_back(words[i]);
        }
    }

    unordered_map<string, array<long long, 4>> memo;
    unordered_map<string, array<char, 4>> seen;
    cout << dsf2("svr", 0, adj_list, memo, seen) << "\n";
}