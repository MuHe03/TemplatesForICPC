#include <vector>
#include <algorithm>

template<typename T>
struct SegmentTree {
private: 
    std::vector<T> sum, Max, Min, tag; // change attribute for different problems
    std::vector<int> siz;
    int n;

#define ls (o << 1)
#define rs (o << 1 | 1)

private: 
    inline void pushup(int o) { // modify this function to change the pushup strategy
        sum[o] = sum[ls] + sum[rs];
        Max[o] = std::max(Max[ls], Max[rs]);
        Min[o] = std::min(Min[ls], Min[rs]);
        siz[o] = siz[ls] + siz[rs];
    }
    inline void pushdown(int o) { // modify this function to change the pushdown strategy
        if (tag[o]) {
            tag[ls] += tag[o];
            tag[rs] += tag[o];
            sum[ls] += tag[o] * siz[ls];
            sum[rs] += tag[o] * siz[rs];
            Max[ls] += tag[o];
            Max[rs] += tag[o];
            Min[ls] += tag[o];
            Min[rs] += tag[o];
            tag[o] = 0;
        }
    }
    void build(int o, int l, int r, const vector<int> &a) {
        siz[o] = r - l + 1;
        if (l == r) {
            sum[o] = Max[o] = Min[o] = a[l], tag[o] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(o);
    }
public:
    SegmentTree(int n, const vector<int> &a){
        t.resize(n << 2);
        siz.resize(n << 2);
        build(1, 1, n, a);
    }
    void add(int o, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            tag[o] += v;
            sum[o] += v * siz[o];
            Max[o] += v;
            Min[o] += v;
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(ls, l, mid, ql, qr, v);
        if (qr > mid) update(rs, mid + 1, r, ql, qr, v);
        pushup(o);
    }
    void add(int o, int l, int r, int p, int v) {
        if (l == r) {
            sum[o] = Max[o] = Min[o] = v;
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (p <= mid) update(ls, l, mid, p, v);
        else update(rs, mid + 1, r, p, v);
        pushup(o);
    }
    int querySum(int o, int l, int r, int ql, int qr) { // modify this function to change the query strategy
        if (ql <= l && r <= qr) return sum[o];
        pushdown(o);
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid) res += querySum(ls, l, mid, ql, qr);
        if (qr > mid) res += querySum(rs, mid + 1, r, ql, qr);
        return res;
    }
    int queryMax(int o, int l, int r, int ql, int qr) { // modify this function to change the query strategy
        if (ql <= l && r <= qr) return Max[o];
        pushdown(o);
        int mid = (l + r) >> 1;
        int res = -INF;
        if (ql <= mid) res = std::max(res, queryMax(ls, l, mid, ql, qr));
        if (qr > mid) res = std::max(res, queryMax(rs, mid + 1, r, ql, qr));
        return res;
    }
    int queryMin(int o, int l, int r, int ql, int qr) { // modify this function to change the query strategy
        if (ql <= l && r <= qr) return Min[o];
        pushdown(o);
        int mid = (l + r) >> 1;
        int res = INF;
        if (ql <= mid) res = std::min(res, queryMin(ls, l, mid, ql, qr));
        if (qr > mid) res = std::min(res, queryMin(rs, mid + 1, r, ql, qr));
        return res;
    }

#undef ls
#undef rs
};
