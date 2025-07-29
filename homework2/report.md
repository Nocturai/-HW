# 51115119  

作業二 - Polynomial 類別實作  

### 解題說明  

本題要求以 C++ 實作一個 `Polynomial`（多項式）類別，支援基本的輸入與輸出功能，並使用運算子多載簡化使用方式。

---

### 解題策略  

1. **使用結構表示多項式項（term）**  
  每一項包含「係數 coeff」與「指數 exp」，以 `Term` 結構儲存。  

2. **使用陣列儲存多項式**  
  使用固定大小的 `Term terms[MAX_TERMS]` 來保存整個多項式，並以變數 `size` 紀錄實際項數。  

3. **使用運算子多載簡化輸入與輸出**  
  分別重載 `>>` 與 `<<` 運算子來完成輸入與輸出，符合 C++ 操作習慣。  

4. **輸出格式直觀清楚**  
  對於每一項輸出係數與次方，正係數加上 `+` 號，並略過 `x^0` 的指數顯示。

---

### 程式實作  

以下為主要程式碼：

```cpp
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

    // 輸入運算子多載
    friend istream& operator>>(istream& in, Polynomial& poly) {
        cout << "輸入項數: ";
        in >> poly.size;
        for (int i = 0; i < poly.size; ++i) {
            cout << "第 " << i + 1 << " 項的coeff exp : ";
            in >> poly.terms[i].coeff >> poly.terms[i].exp;
        }
        return in;
    }

    // 輸出運算子多載
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
```
### 編譯與執行指令
```
sh
$ g++ -std=c++17 -o polynomial polynomial.cpp
$ ./polynomial
```
### 結論
本作業成功實作了一個 Polynomial 類別，支援多項式的輸入與輸出，並使用運算子多載（>> 與 <<）簡化使用流程。
程式碼設計清晰、資料結構簡單，且完全符合題目的功能需求與標頭檔限制。

透過本作業也能理解結構（struct）與類別（class）在 C++ 中的應用方式，並對多項式資料的儲存與操作方式有更深刻的掌握。

### 申論及開發報告
使用運算子多載的優勢
透過 operator>> 與 operator<< 的多載，可將物件當作基本型別一樣使用 cin 和 cout 處理，提高可讀性與可維護性，程式使用上更直覺。

多項式輸出格式設計
每一項都顯示 係數x^次方，且當係數為正數時，自動補上 + 符號。這樣的格式清楚易懂，也符合數學習慣。
