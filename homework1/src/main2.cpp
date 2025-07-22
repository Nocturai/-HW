#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 3;

void powerset(char set[], char bset[], int i, int len) {
  if (i == MAX) {
    cout << "{ ";
    for (int i = 0; i < len; ++i)
      cout << bset[i] << " ";
    cout << "}" << endl;
    return;
  }

  powerset(set, bset, i + 1, len);

  bset[len] = set[i];
  powerset(set, bset, i + 1, len + 1);
}

int main() {
  char set[MAX] = {'A', 'B', 'C'};
  char bset[MAX];
  cout << "Powerset of {A, B, C}:" << endl;
  powerset(set, bset, 0, 0);
  return 0;
}
