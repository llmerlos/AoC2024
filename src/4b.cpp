#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <regex>
using namespace std;

int check_word(int x, int y, vector<vector<char>> &data) {
    int count = 0;

    const int rows = data.size();
    const int cols = data[0].size();

    

    if ((data[y][x] != 'A') || (x == 0) || (x == cols-1) || (y == 0) || (y == rows-1))
        return 0;

    // M M
    // S S
    if ((data[y-1][x-1] == 'M') && (data[y-1][x+1] == 'M') && (data[y+1][x+1] == 'S') && (data[y+1][x-1] == 'S'))
        count++;

    // S M
    // S M
    if ((data[y-1][x-1] == 'S') && (data[y-1][x+1] == 'M') && (data[y+1][x+1] == 'M') && (data[y+1][x-1] == 'S'))
        count++;

    // S S
    // M M
    if ((data[y-1][x-1] == 'S') && (data[y-1][x+1] == 'S') && (data[y+1][x+1] == 'M') && (data[y+1][x-1] == 'M'))
        count++;

    // M S
    // M S
    if ((data[y-1][x-1] == 'M') && (data[y-1][x+1] == 'S') && (data[y+1][x+1] == 'S') && (data[y+1][x-1] == 'M'))
        count++;

    return count;
}

int main (int argc, char *argv[]) {
    // Check if the input path has been provided
    if (argc < 2) {
        cerr << "Missing Input Path" << endl;
        return 1;
    }

    // Open the text file
    ifstream f(argv[1]);
    string s;

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    //
    //----------Logic----------  
    //
    int result = 0;

    vector<vector<char>> text = vector<vector<char>>();
    int current_ln = 0;
    while (getline(f, s)) {
        vector<char> line(s.begin(), s.end());
        text.push_back(line);
    }

    for (int y = 0; y < text.size(); y++) {
        for (int x = 0; x < text[y].size(); x++) {
            result += check_word(x, y, text);
        }
    }

    std::cout << result << endl;

    // Close the file
    f.close();
    return 0;
}