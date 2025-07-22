#include <iostream>

using namespace std;

int a(int m, int n) {
  if (m == 0)
    return n + 1;
  if (n == 0)
    return a(m - 1, 1);
  return a(m - 1, a(m, n - 1));
}

int main() {
  int m, n;

  cout << "input m n" << endl;
  cin >> m >> n;
  cout << m << "," << n << "," << a(m, n) << endl;

  system("pause");
  return 0;
}
