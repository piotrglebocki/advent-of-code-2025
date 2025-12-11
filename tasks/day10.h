#pragma once

#include <iostream>
#include <utils.h>
#include <array>
#include <queue>
#include "math.h"

using namespace std;

// ========== PART 1 ============================

struct InputLineData {
    string indicator;
    vector<vector<int>> buttons;

    void print() {
        cout << "["<< indicator << "]";
        for (const auto& button : buttons) {
            cout << " (";
            for (size_t i = 0; i < button.size(); ++i) {
                cout << button[i];
                if (i < button.size() - 1) cout << ",";
            }
            cout << ")";
        }
        cout << endl;
    }
};


InputLineData parse_line(const string& line) {
    string indicator = "";
    string current = "";
    vector<vector<int>> buttons;

    for (auto c : line) {
        if (c == '[' || c == '(') {
            current.clear();
        } else if (c == ']') {
            indicator = current;
            current.clear();
        } else if (c == ')') {
            auto s_numbers = split(current, ',');
            vector<int> i_numbers;
            i_numbers.reserve(s_numbers.size());
            for (const auto& it : s_numbers) {
                i_numbers.push_back(stoi(it));
            }
            buttons.emplace_back(i_numbers);
            current.clear();
        } else {
            current += c;
        }
    }

    return {indicator, buttons};
}

string toggle(const string& indicators, const vector<int>& button) {
    string res = indicators;
    for (auto index : button) {
        if (res[index] == '.') {
            res[index] = '#';
        } else {
            res[index] = '.';
        }
    }
    return res;
}

int find_fewer_presses(const InputLineData& line_data) {
    string initial_indicators_state(line_data.indicator.size(), '.');

    if (line_data.indicator == initial_indicators_state) {
        return 0;
    }

    queue<string> q;
    q.push(initial_indicators_state);

    int presses_count = 1;
    while (!q.empty()) {
        size_t size = q.size();
        while(size--) {
            const string current_state = q.front(); 
            q.pop();

            for (auto button : line_data.buttons) {
                const string new_state = toggle(current_state, button);
                if (new_state == line_data.indicator) {
                    return presses_count;
                }
                q.push(new_state);
            }
        }
        ++presses_count;
    }
    return presses_count;
}

void solve1() {
    auto lines = read_string_lines("data.txt");
    const auto size = lines.size();

    long long sum = 0;
    int i = 0;
    for (size_t i = 0; i < size; ++i) {
        auto data = parse_line(lines[i]);
        auto count = find_fewer_presses(data);
        cout << "Line ("<<i<<"/"<<size<< ") fewer presses = " << count << endl;
        sum += count;
    }

    cout << "Sum = " << sum << endl;
}