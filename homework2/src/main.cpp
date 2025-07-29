#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_TERMS = 100;

struct Term {
    int coeff;
    int exp;
};

class Polynomial {
private:
    Term terms[MAX_TERMS];
    int size;

public:
    Polynomial() {
        size = 0;
    }

    friend istream& operator>>(istream& in, Polynomial& poly) {
        cout << "輸入項數: ";
        in >> poly.size;
        for (int i = 0; i < poly.size; ++i) {
            cout << "第 " << i + 1 << " 項的coeff exp : ";
            in >> poly.terms[i].coeff >> poly.terms[i].exp;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        for (int i = 0; i < poly.size; ++i) {
            const Term& t = poly.terms[i];
            if (i > 0 && t.coeff >= 0) out << "+";
            out << t.coeff;
            if (t.exp != 0) out << "x^" << t.exp << " ";
        }
        return out;
    }
};

int main() {
    Polynomial p;
    cin >> p;
    cout << "多項式：\n" << p << endl;
    return 0;
}
