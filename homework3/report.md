# 51115119

作業三 - Polynomial 類別設計與運算實作

## 解題說明

本題要求設計一個 Polynomial 類別，使用具有表頭節點的循環鏈結串列來表示多項式，並實作基本運算功能，包括輸入、輸出、加法、減法、乘法與評估。

### 解題策略

- 使用循環鏈結串列，透過表頭節點與循環結構，簡化插入與遍歷邏輯，避免空指標問題。
- 自動合併同指數項，插入新項時，若指數相同則合併係數，若係數為 0 則移除該項。
- 運算操作封裝，加減乘等操作透過運算子多載實作，讓使用者能以自然語法操作多項式。
- 保留使用者輸入
讓使用者輸入 m 與 n，方便測試不同組合並觀察結果。


## 程式實作

以下為主要程式碼：

```cpp
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
```

## 效能分析

1. 時間複雜度 - 插入：O(n)，需遍歷串列找插入點，加減乘：O(n + m)、O(n × m)，依據項數而定
2. 空間複雜度 - 空間與項數成正比

## 測試與驗證

### 測試案例

| 測試案例 | 輸入 p1       | 輸入 p2       | 運算 | 預期輸出         |
|----------|---------------|---------------|------|------------------|
| 測試一   | 2x² + 3       | x² + 1         | 加法 | 3x² + 4          |
| 測試二   | 5x³ - x       | 2x³ + x        | 減法 | 3x³ - 2x         |
| 測試三   | x + 1         | x + 1          | 乘法 | x² + 2x + 1      |
| 測試四   | 2x² + 3x + 1  | x = 2          | 評估 | 2×4 + 3×2 + 1 = 15 |

### 編譯與執行指令

```shell
$ g++ -std=c++11 -o polynomial polynomial.cpp
$ ./polynomial

```

### 結論

本作業成功設計並實作了 Polynomial 類別，使用循環鏈結串列來儲存與操作多項式。透過運算子多載與遞減排序插入邏輯，程式能有效處理多項式的加減乘與評估，並支援格式化輸入輸出。此設計具備良好的擴充性與記憶體管理效率，適合進一步應用於符號運算或數學系統中。


## 申論及開發報告

循環串列的優勢：避免空指標判斷，簡化插入與遍歷邏輯，尤其在多項式運算中頻繁操作節點時更顯效率。

表頭節點設計：統一入口節點，讓串列操作更具一致性，減少特殊情況處理。

自動合併項功能：在插入時即處理同指數項合併，避免重複項，提升資料結構整潔性。

運算子多載：讓使用者能以自然語法進行加減乘等操作，提升程式可讀性與易用性。
