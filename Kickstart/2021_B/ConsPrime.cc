#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(uint64_t j) {
    if (j == 2 || j == 3) {
        return true;
    }
    if (j%6 != 1 && j%6 !=5) {
        return false;
    }
    for (uint64_t i = 2; i <= sqrt(j); i++)
    {
        if (j%i == 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int no_of_TC;
    cin >> no_of_TC;
    for (int j = 1; j <= no_of_TC; j++)
    {
        uint64_t L;
        cin >> L;

        uint64_t c = sqrt(L);
        
        uint64_t first = 0, second = 0;
        for (uint64_t i = c+1; i < L; i++)
        {
            if (isPrime(i)) {
                first = i;
                break;
            }
        }
        for (uint64_t i = c; i > 1; i--)
        {
            if (isPrime(i)) {
                second = i;
                break;
            }
        }
        
        uint64_t res = first * second;
        if (res > L) {
            for (uint64_t i = second-1; i > 1; i--)
            {
                if (isPrime(i)) {
                    res = i * second;
                    break;
                }   
            }
        }
        cout << "Case #" << j << ": " << res << endl;
    }
    
}