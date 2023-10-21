#include <bits/stdc++.h>

template<typename T> struct PersistentSegmentTree{
	struct PersistentSegmentTreeNode {
		T val;
		int ls, rs, cnt;

		PersistentSegmentTreeNode(T val = 0, int ls = 0, int rs = 0, int cnt = 0) 
											: val(val), ls(ls), rs(rs), cnt(cnt) {}
	};

	vector<PersistentSegmentTreeNode> nd;
	int n, len;
	vector<int> c, a;
	vector<int> rt;

	int build(int l, int r) {
		int o = nd.size();
		nd.emplace_back();
		if (l == r) 
			return o;
		int mid = (l + r) >> 1;
		nd[o].ls = build(l, mid);
		nd[o].rs = build(mid + 1, r);
		return o;
	}

	// update the k-th number with v, create new nodes
	int update(int k, T v, int l, int r, int rt) {
		int o = nd.size();
		nd.emplace_back(nd[rt]);
		++nd[o].cnt;
		nd[o].val += v;
		if (l == r)
			return o;
		int mid = (l + r) >> 1;
		if (k <= mid)
			nd[o].ls = update(k, v, l, mid, nd[rt].ls);
		else
			nd[o].rs = update(k, v, mid + 1, r, nd[rt].rs);
		return o;
	}

	// query the k-th number in (L, R]
	int query(int L, int R, int l, int r, int k) {
		int mid = (l + r) >> 1;
		int x = nd[nd[R].ls].cnt - nd[nd[L].ls].cnt;
		if (l == r)
			return l;
		if (k <= x)
			return query(nd[L].ls, nd[R].ls, l, mid, k);
		else 
			return query(nd[L].rs, nd[R].rs, mid + 1, r, k - x);
	}

	// query the sum of [L, R] in version rt
	PersistentSegmentTree(int n, vector<T> a) {
		this->a = a;
		rt = vector<int>(n + 1);
		c = a;
		sort(c.begin(), c.end());
		c.erase(unique(c.begin(), c.end()), c.end());
		len = c.size() - 1;
		rt[0] = build(1, len);
		for (int i = 1; i <= n; ++i) {
			int x = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
			rt[i] = update(x, a[i], 1, len, rt[i - 1]);
		}
	}

	int query(int l, int r, int k) {
		return c[query(rt[l - 1], rt[r], 1, len, k)];
	}
};