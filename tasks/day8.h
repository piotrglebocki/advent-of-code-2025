#pragma once

#include <iostream>
#include <utils.h>
#include <array>
#include "math.h"

using namespace std;

// ========== PART 1 ============================

struct Point {
    int x, y, z;

    float dist(const Point& other) {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
    }

    string to_str() const {
        return "(" + to_string(x) + "," +to_string(y) + "," + to_string(z) + ")";
    }
};

struct Connection {
    float distance; 
    int point_index_1;
    int point_index_2;
};

class UnionFind {
public:
    UnionFind(int sz) : root(sz) {
        for (int i = 0; i < sz; i++) {
            root[i] = i;
        }
    }

    int find(int x) {
        return root[x];
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            for (int i = 0; i < root.size(); i++) {
                if (root[i] == rootY) {
                    root[i] = rootX;
                }
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    bool are_all_connected() {
        int x = root[0];
        for (size_t i = 1; i < root.size(); ++i) {
            if (x != root[i]) return false;
        }
        return true;
    }

    vector<int> get_connected_groups_count() {
        unordered_map<int, int> counts;
        for (size_t i = 0; i < root.size(); ++i) {
            ++counts[root[i]];
        }
        vector<int> list;
        for (auto& it : counts) {
            list.push_back(it.second);
        }
        sort(list.begin(), list.end());
        return list;
    }

private:
    vector<int> root;
};

void solve1() {
    const auto lines = read_string_lines("data.txt");
    vector<Point> points;
    points.reserve(lines.size());

    for (const auto& line : lines) {
        auto tab = split(line, ',');
        points.push_back({stoi(tab[0]), stoi(tab[1]), stoi(tab[2])});
    }

    vector<Connection> connections;
    for (int i = 0; i < points.size() - 1; ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            float dist = points[i].dist(points[j]);
            connections.push_back(Connection{dist, i, j});
        }
    }

    sort(connections.begin(), connections.end(), [](const Connection& a, const Connection& b) {
        return a.distance < b.distance;
    });

    UnionFind uf(points.size());

    const int CONNECTIONS = 1000;
    for (int i = 0; i < CONNECTIONS; ++i) {
        const auto& conn = connections[i];
        const auto i1 = conn.point_index_1;
        const auto i2 = conn.point_index_2;

        if (!uf.connected(i1, i2)) {
            uf.unionSet(i1, i2);
        }
    }

    long long res = 1;
    vector<int> groups = uf.get_connected_groups_count();
    const int GROUPS = 3;
    for (size_t i = 0; i < GROUPS; ++i) {
        res *= groups[groups.size() - i - 1];
    }
    cout << res << endl;
}

// ========== PART 2 ============================

void solve2() {
    const auto lines = read_string_lines("data.txt");
    vector<Point> points;
    points.reserve(lines.size());

    for (const auto& line : lines) {
        auto tab = split(line, ',');
        points.push_back({stoi(tab[0]), stoi(tab[1]), stoi(tab[2])});
    }

    vector<Connection> connections;
    for (int i = 0; i < points.size() - 1; ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            float dist = points[i].dist(points[j]);
            connections.push_back(Connection{dist, i, j});
        }
    }

    sort(connections.begin(), connections.end(), [](const Connection& a, const Connection& b) {
        return a.distance < b.distance;
    });

    UnionFind uf(points.size());

    for (int i = 0; i < connections.size(); ++i) {
        const auto& conn = connections[i];
        const auto i1 = conn.point_index_1;
        const auto i2 = conn.point_index_2;

        if (!uf.connected(i1, i2)) {
            uf.unionSet(i1, i2);
            if (uf.are_all_connected()) {
                cout << points[i1].to_str() << ":" << points[i2].to_str() << endl;
                cout << (long long) points[i1].x * points[i2].x << endl;
                return;
            }
        }
    }
}