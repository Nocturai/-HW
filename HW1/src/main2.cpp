
#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 3;

void powerset(char set[], char subset[], int index, int subset_len) {
    if (index == MAX) {
        cout << "{ ";
        for (int i = 0; i < subset_len; ++i)
            cout << subset[i] << " ";
        cout << "}" << endl;
        return;
    }

    powerset(set, subset, index + 1, subset_len);

    subset[subset_len] = set[index];
    powerset(set, subset, index + 1, subset_len + 1);
}

int main() {
    char set[MAX] = {'A', 'B', 'C'};
    char subset[MAX];
    cout << "Powerset of {A, B, C}:" << endl;
    powerset(set, subset, 0, 0);
    return 0;
}
