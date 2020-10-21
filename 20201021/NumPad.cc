#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {

    std::map<char, vector<char>> keyMap;

    keyMap['1'] = {'a', 'b', 'c'};
    keyMap['2'] = {'d', 'e', 'f'};
    keyMap['3'] = {'g', 'h', 'i'};
/*keyMap['4'] = 3;
keyMap['5'] = 3;
keyMap['6'] = 3;
keyMap['7'] = 4;
keyMap['8'] = 3;
keyMap['9'] = 4;*/
    string input;
    cin >> input;

    int num_of_chars = input.length();

    vector<string> result;
    
    for (size_t i = 0; i < input.length(); i++)
    {
        char input_ch = input[i];
        vector<char> kb_chars = keyMap[input_ch];
        if(result.empty()) {
            for(auto c: kb_chars) {
                result.push_back(string(1, c));
            }
            continue;
        }

        std::vector<string> temp;
        for(auto c: kb_chars) {
            for(auto r: result) {
                string newStr = r.append(string(1, c));
                temp.push_back(newStr);
            }
        }
        result = temp;

    }

    for(auto str: result) {
        cout << str << endl;
    } 
    
    cout << result.size() << endl;
}