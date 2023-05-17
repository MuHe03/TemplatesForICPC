#include <vector>
#include <cmath>
#include <algorithm>

template<typename T>
struct SparseTable {
private:
    std::vector<std::vector<T>> val;
    T (*cmp)(T, T);
public:
    SparseTable() {}
    /*
    @param a: the array to build sparse table on
    @param cmp: the function to compare two elements, default is std::min
    */
    SparseTable(std::vector<T> &a, T (*cmp)(T, T) = std::min<T>) {
        this->cmp = cmp;
        int n = a.size();
        val = std::vector<std::vector<T>>(n + 1, std::vector<T>(1 + (int)log2(n)));
        for (int i = 0; i < n; ++i)
            val[i][0] = a[i];
        for (int j = 1; j < (int)val[0].size(); ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                val[i][j] = cmp(val[i][j - 1], val[i + (1 << (j - 1))][j - 1]);
    }
    T ask(int l, int r) {
        int k = log2(r - l + 1);
        return cmp(val[l][k], val[r - (1 << k) + 1][k]);
    }
};