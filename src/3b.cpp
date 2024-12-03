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

    std::regex mulExp(R"(mul\((\d+),(\d+)\))");
    std::regex doExp(R"((?:do\(\))(.*?)(?:don't\(\)))");

    std::string full_input = "do()";
    while (getline(f, s)) {
        full_input += s;
    }

    full_input += "don't()";

    std::smatch doMatch;
    std::string::const_iterator doSearchStart(full_input.cbegin());
    while(std::regex_search(doSearchStart, full_input.cend(), doMatch, doExp)) {
        std::smatch mulMatch;

        std::string mulStr = doMatch[1].str();

        std::string::const_iterator mulSearchStart(mulStr.cbegin());
        while(std::regex_search(mulSearchStart, mulStr.cend(), mulMatch, mulExp)) {
            int num1 = std::stoi(mulMatch[1]);
            int num2 = std::stoi(mulMatch[2]);
        
            result += num1 * num2;
            
            mulSearchStart = mulMatch.suffix().first;
        }

        doSearchStart = doMatch.suffix().first;
    }

    std::cout << result << endl;

    // Close the file
    f.close();
    return 0;
}