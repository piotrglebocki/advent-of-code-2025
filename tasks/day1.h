#pragma once

#include <iostream>
#include <utils.h>

using namespace std;

void solve1() {
    auto input = read_string_lines("data.txt");
    
    int count = 0;
    int position = 50;

    for (auto& line : input) {
        const char sign = line[0];
        int shift = stoi(line.substr(1));

        if (sign == 'R') {
            position += shift;
        } else {
            position += 100 - shift;
        }
        position %= 100;
        
        if (position == 0) {
            ++count;
        }
    }

    cout<< count << endl;
}

void solve2() {
    auto input = read_string_lines("data.txt");
    
    int count = 0;
    int position = 50;

    for (auto& line : input) {
        const char sign = line[0];
        int shift = stoi(line.substr(1));

        while (shift--) {
            position += sign == 'R' ? 1 : -1;
            if (position == 100) position = 0;
            if (position == -1) position = 99;
            if (position == 0) ++count;
        }
    }

    cout<< count << endl;
}