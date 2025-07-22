# 51115119

作業一 - Powerset 子集合列舉

## 解題說明

本題要求實作一個遞迴函式，列舉集合 {A, B, C} 的所有子集合（powerset）。powerset 是指一個集合的所有可能子集合，包括空集合與集合本身。

### 解題策略

1. 使用遞迴函式將問題拆解為更小的子問題：
每個元素都有兩種選擇：包含或不包含，形成二元樹狀結構。
2. 當遞迴深度達到集合大小（i == MAX）時，表示已處理完所有元素，輸出目前的子集合。
3. 主程式呼叫遞迴函式，並輸出所有子集合。


## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cstring>
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

```

## 效能分析

1. 時間複雜度：每個元素有兩種選擇，共 2^n 種組合，時間複雜度為 O(2ⁿ)。
2. 空間複雜度：遞迴深度為 n，每層最多儲存一個元素，空間複雜度為 O(n)。

## 測試與驗證

### 測試案例

| 預期輸出 |
|----------|
|Powerset of {A, B, C}:|
|{ }|
|{ C }|
|{ B }|
|{ B C }|
|{ A }|
|{ A C }|
|{ A B }|
|{ A B C }|

### 編譯與執行指令

```shell
$ g++ -std=c++17 -Wall -O2 -o powerset powerset.cpp
$ ./powerset
```

### 結論

1. 本作業成功實作了列舉集合 {A, B, C} 所有子集合的遞迴演算法。
2. 程式完整產生了 2^3 = 8 個子集合，展現了遞迴在組合問題上的強大表達力。
3. 遞迴結構清楚，適合初學者理解遞迴流程

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **具備可擴充性與通用性**  
   此遞迴架構可輕易擴展至任意大小的集合，只需調整 MAX 值與輸入集合即可，具有良好的通用性。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
      void powerset(char set[], char bset[], int i, int len) {
    if (i == MAX) {
        cout << "{ ";
        for (int i = 0; i < len; ++i)
            cout << bset[i] << " ";
        cout << "}" << endl;
        return;
    }
   ```
