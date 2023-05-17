#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>

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

struct SuffixArray {
private:
    std::vector<int> sa, rk, ht;
    SparseTable<int> st;
public:
    SuffixArray(std::string s) {
        using namespace std;
        int n = s.size(), m = 256;
        sa = rk = ht = vector<int>(n);
        vector<int> k1(n + 1), cnt(n + 1), id(n + 1);
        for (int i = 1; i <= n; ++i)
            ++cnt[rk[i] = s[i]];
        for (int i = 1; i <= n; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i)
            sa[--cnt[rk[i]]] = i;
        m = n;
        for (int w = 1; w < n; w <<= 1) {
            int cc = 0;
            for (int i = n - w + 1; i <= n; ++i)
                id[++cc] = i;
            for (int i = 1; i <= n; ++i)
                if (sa[i] > w)
                    id[++cc] = sa[i] - w;
            fill(cnt.begin(), cnt.begin() + m + 1, 0);
            for (int i = 1; i <= n; ++i)
                ++cnt[k1[i] = rk[id[i]]];
            for (int i = 1; i <= m; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i)
                sa[--cnt[k1[i]]] = id[i];
            vector<int> tmp = rk;
            tmp.resize(n << 1 | 1, 0);
            cc = 0;
            for (int i = 1; i <= n; ++i)
                rk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + w] == tmp[sa[i - 1] + w]) ? cc : ++cc;
            if ((m = cc) == n) {
                for (int i = 1; i <= n; ++i)
                    sa[rk[i]] = i;
                break;
            }
        }
        for (int i = 1, j = 0; i <= n; ++i) {
            if (rk[i] == 1)
                continue;
            if (j)
                --j;
            while (i + j <= n && sa[rk[i] - 1] + j <= n && s[i + j] == s[sa[rk[i] - 1] + j])
                ++j;
            ht[rk[i]] = j;
        }
    }
    void buildST() {
        st = SparseTable<int>(ht);
    }
    /*
    ask the lcp of suffix sa[l] and sa[r]
    */
    int askBySA(int l, int r) {
        if (l > r)
            std::swap(l, r);
        if (l == r)
            return sa[l];
        return sa[st.ask(l + 1, r)];
    }
    /*
    ask the lcp of suffix l and r
    */
    int askByPos(int l, int r) {
        return askBySA(rk[l], rk[r]);
    }
    std::vector<int>& getSA() {
        return sa;
    }
    std::vector<int>& getRK() {
        return rk;
    }
    std::vector<int>& getHT() {
        return ht;
    }
};
