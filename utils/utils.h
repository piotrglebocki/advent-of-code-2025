#pragma once 

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

template<typename T> 
void print_grid(const vector<vector<T>>& grid) {
    for (const auto& row : grid) {
        for (auto it : row) {
            cout << it;
        }
        cout << endl;
    }
}

vector<vector<char>> read_char_lines(const string &filename) {
    vector<vector<char>> matrix;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open file " << filename << endl;
    }
    string line;
    while (getline(inputFile, line)) {
        vector<char> row(line.begin(), line.end());
        matrix.emplace_back(row);
    }
    inputFile.close();
    return matrix;
}

vector<string> read_string_lines(const string &filename) {
    vector<string> lines;
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open file " << filename << endl;
    }
    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    return lines;
}

vector<string> split(const string& word, char separator) {
    vector<string> result;
    string current;

    for (char c : word) {
        if (c == separator) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    result.push_back(current);
    return result;
}