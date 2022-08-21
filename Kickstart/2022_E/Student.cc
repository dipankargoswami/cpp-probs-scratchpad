#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int no_of_TC;
    cin >> no_of_TC;
    for (int i = 1; i <= no_of_TC; i++)
    {
        cout << "Case #" << i << ": " ;

        int L;
        cin >> L;
        
        vector<int> v1(L, 0);
        vector<int> v2(L, 0);

        for (int i = 0; i < L; i++)
        {
            int j;
            cin >> j;
            v1[i] = j;
            v2[i] = j;
        }

        sort(v2.begin(), v2.end());

        for (int i = 0; i < L; i++)
        {
            int stdn = v1[i];
            bool dup=true;
            int mentor = -1;
            for (int j = L-1; j >= 0; j--)
            {
                if (v2[j] == stdn && dup) {
                    dup = false;
                    continue;
                }
                if (v2[j] <= 2 * stdn) {
                    mentor = v2[j];
                    break;
                }
            }
            cout << mentor << " ";
        }
        
        cout << endl;
    }
    
}