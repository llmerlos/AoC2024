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
    string full_input;

    std::regex rulesExp(R"(^(\d+)\|(\d+)$)");
    std::regex recordExp(R"((\d+))");

    std::map<int, vector<int>> rulesMap;

    bool doing_rules = true;
    while (getline(f, s)) {
        if (doing_rules) {
            std::smatch rulesMatch;
            
            if (std::regex_match(s, rulesMatch, rulesExp)) {

                int base_page = std::stoi(rulesMatch[1].str());
                int next_page = std::stoi(rulesMatch[2].str());
                rulesMap[base_page].push_back(next_page);
            } else {
                doing_rules = false;
            }

        } else {
            vector<int> records;

            std::smatch recordMatch;
            std::string::const_iterator recordSearchStart(s.cbegin());
            while(std::regex_search(recordSearchStart, s.cend(), recordMatch, recordExp)) {
                int num = std::stoi(recordMatch[1]);
                records.push_back(num);

                recordSearchStart = recordMatch.suffix().first;
            }

            bool valid = true;
            for (int i = 0; i < records.size(); i++) {
                int page = records[i];

                for (int j = 0; j < i; j++) {
                    int to_find = records[j];
                    if ((std::find(rulesMap[page].begin(), rulesMap[page].end(), to_find)) != rulesMap[page].end()) {
                        valid = false;
                    }
                }
            }

            if (!valid) {
                for (int i = 0; i < records.size(); i++) {
                    int page = records[i];

                    for (int j = 0; j < i; j++) {
                        int to_find = records[j];
                        if ((std::find(rulesMap[page].begin(), rulesMap[page].end(), to_find)) != rulesMap[page].end()) {
                            records[i] = to_find;
                            records[j] = page;

                            i=0;
                            break;
                        }
                    }
                }
                result += records[records.size()/2];
            }

            
        }
    }

    std::cout << result << endl;

    // Close the file
    f.close();
    return 0;
}