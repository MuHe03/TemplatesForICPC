#include <climits>
#include <algorithm>

template<typename T>
struct ValueSegmentTreeNode {
private: 
    T v, tag, Max, Min;
    int siz, l, r;
    ValueSegmentTreeNode *ls, *rs;
    ValueSegmentTreeNode(T __v, int __l, int __r): v(__v), l(__l), r(__r) {
        tag = Max = Min = v;
        siz = 1;
    }
    ValueSegmentTreeNode(int __l, int __r): l(__l), r(__r) {
        tag = Max = Min = siz = 0;
    }
};

template<typename T>
struct ValueSegmentTree {
    friend ValueSegmentTreeNode<T>;
private:
    ValueSegmentTreeNode<T> *root;
    int n;
    const T INF = __INT_MAX__; // should set INF to the maximum value of T

public:
    ValueSegmentTree(int __n): n(__n){
        root = new ValueSegmentTreeNode<T>(0);
    }

private: 
    inline void pushup(ValueSegmentTreeNode<T> *o, int l, int r) { // modify this function to change the pushup strategy
        o->sum = aggreFunc(o->ls->sum, o->rs->sum);
        o->Max = std::max(o->ls->Max, o->rs->Max);
        o->Min = std::min(o->ls->Min, o->rs->Min);
        o->siz = o->ls->siz + o->rs->siz;
    }
    inline void pushdown(ValueSegmentTreeNode<T> *o, int l, int r) { // modify this function to change the pushdown strategy
        if (o == nullptr)
            o = new ValueSegmentTreeNode<T>(l, r);
        if (o->tag) {
            o->ls->tag += o->tag;
            o->rs->tag += o->tag;
            o->ls->sum += o->tag * o->ls->siz;
            o->rs->sum += o->tag * o->rs->siz;
            o->ls->Max += o->tag;
            o->rs->Max += o->tag;
            o->ls->Min += o->tag;
            o->rs->Min += o->tag;
            o->tag = 0;
        }
    }
    void __insert(ValueSegmentTreeNode<T> *o, int l, int r, int pos, T v) {
        if (l == r) {
            o->sum = o->Max = o->Min = v;
            o->siz = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) __insert(o->ls, l, mid, pos, v);
        else __insert(o->rs, mid + 1, r, pos, v);
        pushup(o, l, r);
    }
    T __queryMax(ValueSegmentTreeNode<T> *o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return o->Max;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        int ret = -INF;
        if (ql <= mid) ret = std::max(ret, __queryMax(o->ls, l, mid, ql, qr));
        if (qr > mid) ret = std::max(ret, __queryMax(o->rs, mid + 1, r, ql, qr));
        return ret;
    }
    T __queryMin(ValueSegmentTreeNode<T> *o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return o->Min;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        int ret = INF;
        if (ql <= mid) ret = std::min(ret, __queryMin(o->ls, l, mid, ql, qr));
        if (qr > mid) ret = std::min(ret, __queryMin(o->rs, mid + 1, r, ql, qr));
        return ret;
    }
    int __querySiz(ValueSegmentTreeNode<T> *o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return o->siz;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        int ret = 0;
        if (ql <= mid) ret += __querySize(o->ls, l, mid, ql, qr);
        if (qr > mid) ret += __querySize(o->rs, mid + 1, r, ql, qr);
        return ret;
    }
    int __queryRank(ValueSegmentTreeNode<T> *o, int l, int r, int pos) {
        if (l == r) {
            return 1;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (pos <= mid) return __queryRank(o->ls, l, mid, pos);
        else return __queryRank(o->rs, mid + 1, r, pos) + o->ls->siz;
    }
public:
    void insert(int pos, T v) {
        __insert(root, 1, n, pos, v);
    }
    T queryMax(int l, int r) {
        return __queryMax(root, 1, n, l, r);
    }
    T queryMin(int l, int r) {
        return __queryMin(root, 1, n, l, r);
    }
    int querySiz(int l, int r) {
        return __querySiz(root, 1, n, l, r);
    }
    int queryRank(int pos) {
        return __queryRank(root, 1, n, pos);
    }
};
