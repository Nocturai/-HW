#include <iostream>
#include <cmath>
#include <string>
using namespace std;

struct Term {
    float coef;
    int exp;
    Term* next;

    Term(float c = 0, int e = 0, Term* n = NULL) : coef(c), exp(e), next(n) {}
};

class Polynomial {
private:
    Term* head;

    void Clear() {
        Term* p = head->next;
        while (p != head) {
            Term* temp = p;
            p = p->next;
            delete temp;
        }
        head->next = head;
    }

    void CopyFrom(const Polynomial& other) {
        Term* p = other.head->next;
        while (p != other.head) {
            InsertTerm(p->coef, p->exp);
            p = p->next;
        }
    }

    void InsertTerm(float coef, int exp) {
        if (fabs(coef) < 1e-6) return;
        Term* prev = head;
        Term* curr = head->next;
        while (curr != head && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }
        if (curr != head && curr->exp == exp) {
            curr->coef += coef;
            if (fabs(curr->coef) < 1e-6) {
                prev->next = curr->next;
                delete curr;
            }
        } else {
            Term* newTerm = new Term(coef, exp, curr);
            prev->next = newTerm;
        }
    }

public:
    Polynomial() {
        head = new Term();
        head->next = head;
    }

    Polynomial(const Polynomial& other) : Polynomial() {
        CopyFrom(other);
    }

    ~Polynomial() {
        Clear();
        delete head;
    }

    const Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Term* a = head->next;
        Term* bptr = b.head->next;
        while (a != head || bptr != b.head) {
            if (a != head && (bptr == b.head || a->exp > bptr->exp)) {
                result.InsertTerm(a->coef, a->exp);
                a = a->next;
            } else if (bptr != b.head && (a == head || bptr->exp > a->exp)) {
                result.InsertTerm(bptr->coef, bptr->exp);
                bptr = bptr->next;
            } else {
                result.InsertTerm(a->coef + bptr->coef, a->exp);
                a = a->next;
                bptr = bptr->next;
            }
        }
        return result;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Term* a = head->next;
        Term* bptr = b.head->next;
        while (a != head || bptr != b.head) {
            if (a != head && (bptr == b.head || a->exp > bptr->exp)) {
                result.InsertTerm(a->coef, a->exp);
                a = a->next;
            } else if (bptr != b.head && (a == head || bptr->exp > a->exp)) {
                result.InsertTerm(-bptr->coef, bptr->exp);
                bptr = bptr->next;
            } else {
                result.InsertTerm(a->coef - bptr->coef, a->exp);
                a = a->next;
                bptr = bptr->next;
            }
        }
        return result;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (Term* a = head->next; a != head; a = a->next) {
            for (Term* bptr = b.head->next; bptr != b.head; bptr = bptr->next) {
                result.InsertTerm(a->coef * bptr->coef, a->exp + bptr->exp);
            }
        }
        return result;
    }

    float Evaluate(float x) const {
        float sum = 0;
        for (Term* p = head->next; p != head; p = p->next) {
            sum += p->coef * pow(x, p->exp);
        }
        return sum;
    }

    friend istream& operator>>(istream& is, Polynomial& poly) {
        int n;
        is >> n;
        for (int i = 0; i < n; ++i) {
            float coef;
            int exp;
            is >> coef >> exp;
            poly.InsertTerm(coef, exp);
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        Term* p = poly.head->next;
        bool first = true;
        while (p != poly.head) {
            if (!first && p->coef > 0) os << "+";
            os << p->coef;
            if (p->exp != 0) os << "x^" << p->exp;
            first = false;
            p = p->next;
        }
        if (first) os << "0";
        return os;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "第一個多項式:\n";
    cin >> p1;
    cout << "第二個多項式:\n";
    cin >> p2;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "p1 + p2 = " << sum << endl;
    cout << "p1 - p2 = " << diff << endl;
    cout << "p1 * p2 = " << prod << endl;

    float x;
    cout << " x ?:";
    cin >> x;
    cout << "p1(x) = " << p1.Evaluate(x) << endl;
}
