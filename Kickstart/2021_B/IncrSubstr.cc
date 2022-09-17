#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int no_of_TC;
    cin >> no_of_TC;
    for (int i = 1; i <= no_of_TC; i++)
    {
        int L;
        cin >> L;

        string str;
        cin >> str;

        vector<int> res;
        res.push_back(1);
        char ch=str[0];
        int len = 1;
        for (int j = 1; j < L; j++)
        {
            char this_ch = str[j];
            
            //This char is also in strictly increasing order
            if ((int)this_ch > (int)ch) {
                len = len+1;
            } else {
                len = 1;
            }
            res.push_back(len);
            ch = this_ch;
        }
        
        cout << "Case #" << i << ": " ;

        for (int j = 0; j < L; j++)
        {
            cout << res[j] << " ";
        }
        cout << endl;
    }
    
}