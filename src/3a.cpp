#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <regex>
using namespace std;

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

    std::regex e(R"(mul\((\d+),(\d+)\))");
    while (getline(f, s)) {
        std::smatch m;
        std::string::const_iterator searchStart(s.cbegin());

        std::regex_search(s, m, e);

        while(std::regex_search(searchStart, s.cend(), m, e)) {
            int num1 = std::stoi(m[1]);
            int num2 = std::stoi(m[2]);
        
            result += num1 * num2;

            searchStart = m.suffix().first;
        }
    }

    std::cout << result << endl;

    // Close the file
    f.close();
    return 0;
}