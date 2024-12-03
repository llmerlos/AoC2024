#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

bool is_safe(vector<int> values) {
    int old_value = values[0];
    int old_jump = 0;

    bool safe = true;

    for (int i=1; i < values.size(); i++) {
        int value = values[i];
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

    return safe;
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

    int safe_count = 0;

    while (getline(f, s)) {
        std::stringstream ss;
        ss.str(s);

        vector<int> values;

        bool safe = false;
        int value;
        while (ss >> value)
            values.push_back(value);


            for (int i=0; i < values.size(); i++) {
                vector<int> values_minus_1(values);

                values_minus_1.erase(values_minus_1.begin() + i);
                
                if (is_safe(values_minus_1)) {
                    safe_count++;
                    break;
                }
            }
    }

    cout << safe_count << endl;

    // Close the file
    f.close();
    return 0;
}