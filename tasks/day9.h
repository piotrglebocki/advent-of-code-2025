#pragma once

#include <iostream>
#include <utils.h>
#include <array>
#include "math.h"
#include <boost/geometry.hpp>

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

void solve2() {
    namespace bg = boost::geometry;
    using point   = bg::model::d2::point_xy<long>;
    using polygon = bg::model::polygon<point>;
    using box     = bg::model::box<point>;

    auto lines = read_string_lines("data.txt");

    vector<pair<long, long>> red;
    red.reserve(lines.size());
    for (const auto& line : lines) {
        auto vec = split(line, ',');
        long c = stol(vec[0]);
        long r = stol(vec[1]);
        red.emplace_back(r, c);
    }

    polygon poly;
    auto& ring = poly.outer();

    for (size_t i = 0; i < red.size(); ++i) {
        auto [r1, c1] = red[i];
        auto [r2, c2] = red[(i + 1) % red.size()];
        ring.emplace_back(c1, r1);
        if (r1 != r2 && c1 != c2) {
            ring.emplace_back(c2, r1);
        }
    }
    bg::correct(poly);

    long long max_area = 0;

    for (size_t i = 0; i < red.size(); ++i) {
        for (size_t j = i + 1; j < red.size(); ++j) {

            long r1 = red[i].first;
            long c1 = red[i].second;
            long r2 = red[j].first;
            long c2 = red[j].second;

            long top    = min(r1, r2);
            long bottom = max(r1, r2);
            long left   = min(c1, c2);
            long right  = max(c1, c2);

            box rect(point(left, top), point(right, bottom));

            if (bg::covered_by(rect, poly)) {
                long long area = (abs(r1 - r2) + 1) * (abs(c1 - c2) + 1);
                max_area = max(max_area, area);
            }
        }
    }

    cout << max_area << endl;
}