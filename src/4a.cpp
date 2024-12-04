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

    

    if (data[y][x] != 'X') 
        return 0;


    // E
    if ((x + 3 < cols) && (data[y][x+1] == 'M') && (data[y][x+2] == 'A') && (data[y][x+3] == 'S'))
        count++;

    // W
    if ((x - 3 >= 0) && (data[y][x-1] == 'M') && (data[y][x-2] == 'A') && (data[y][x-3] == 'S'))
        count++;

    // N
    if ((y - 3 >= 0) && (data[y-1][x] == 'M') && (data[y-2][x] == 'A') && (data[y-3][x] == 'S'))
        count++;

    // S
    if ((y + 3 < rows) && (data[y+1][x] == 'M') && (data[y+2][x] == 'A') && (data[y+3][x] == 'S'))
        count++;

    // SE
    if ((x + 3 < cols) && (y + 3 < rows) && (data[y+1][x+1] == 'M') && (data[y+2][x+2] == 'A') && (data[y+3][x+3] == 'S'))
        count++;

    // NE
    if ((x + 3 < cols) && (y - 3 >= 0) && (data[y-1][x+1] == 'M') && (data[y-2][x+2] == 'A') && (data[y-3][x+3] == 'S'))
        count++;

    // NW
    if ((x - 3 >= 0) && (y - 3 >= 0) && (data[y-1][x-1] == 'M') && (data[y-2][x-2] == 'A') && (data[y-3][x-3] == 'S'))
        count++;

    // SW
    if ((x - 3 >= 0) && (y + 3 < rows) && (data[y+1][x-1] == 'M') && (data[y+2][x-2] == 'A') && (data[y+3][x-3] == 'S'))
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