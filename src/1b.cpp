#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

bool comp(int a, int b) {
    return a >= b;
};


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
    
    std::vector<int> left, right;

    while (getline(f, s)) {
        int rnum;
        int lnum;
        std::stringstream ss;
        
        ss.str(s);
        ss >> lnum;
        ss >> rnum;

        left.push_back(lnum);
        right.push_back(rnum);
    }

    std::sort(left.begin(), left.end(), comp);
    std::sort(right.begin(), right.end(), comp);
    

    int sum = 0;
    for (auto el : left) {
        sum += el * count(right.begin(), right.end(), el); 
    }

    cout << sum  << endl;

    // Close the file
    f.close();
    return 0;
}