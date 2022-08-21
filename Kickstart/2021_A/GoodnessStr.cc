#include <iostream>

using namespace std;

int main(void) {
    int no_of_TC;
    cin >> no_of_TC;
    for (int i = 1; i <= no_of_TC; i++)
    {
        int L, K;
        cin >> L >> K;
        int goodness = 0;
        string S;
        cin >> S;
        for (int j = L/2-1; j >= 0; j--)
        {
            if (S[j] != S[L-1-j]) {
                goodness++;
            }
        }
        
        cout << "Case #" << i << ": " << abs(K - goodness) <<  endl;
    }
    
}