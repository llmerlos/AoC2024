#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
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

    int safe_count = 0;

    while (getline(f, s)) {
        std::stringstream ss;
        ss.str(s);

        int value = 0;
        int old_value = 0;
        int old_jump = 0;
        int directon = 0; // -1 means down, 1 means up, 0 not set yet

        ss >> old_value;

        bool safe = true;
        while (ss >> value) {
            int jump = value - old_value;
            
            if ((abs(jump) > 3) || (abs(jump) < 1)) {
                safe = false;
            }

            if ((old_jump != 0) && ((old_jump >= 0 ) != (jump >= 0))) {
                safe = false;
            }

            old_value = value;
            old_jump = jump;       
        }

        if (safe) {
            safe_count++;
        }
    }

    cout << safe_count << endl;

    // Close the file
    f.close();
    return 0;
}