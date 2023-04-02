#include <vector>
#include <climits>

struct GetD {
public:
	int n, mid1, len, mid2, rt, center;
	std::vector<int> siz, dep;

private:
	std::vector<std::vector<int>> e;
	std::vector<int> md, sed, mdf, sedf, upd;

public: 
	GetD(int __n, std::vector<std::vector<int>> __e) : n(__n), e(__e) {
		md.resize(n + 1);
		sed.resize(n + 1);
		mdf.resize(n + 1);
		sedf.resize(n + 1);
		upd.resize(n + 1);
		siz.resize(n + 1);
		dep.resize(n + 1);
		len = 0, mid1 = mid2 = -1, rt = 1;
	}

private:
	void dfs(int u, int fa) {
		siz[u] = 1;
		int maxs = 0;
		for (int v : e[u]) {
			if (v == fa) continue;
			dep[v] = dep[u] + 1;
			dfs(v, u);
			siz[u] += siz[v];
			maxs = std::max(maxs, siz[v]);
		}
		if (std::max(maxs, n - siz[u]) <= n / 2)
			rt = u;
	}
	void dfs1(int u, int fa) {
		md[u] = sed[u] = 0;
		for (int v : e[u]) {
			if (v == fa) continue;
			dfs(v, u);
			if (md[v] + 1 > md[u]) {
				sed[u] = md[u];
				sedf[u] = mdf[u];
				md[u] = md[v] + 1;
				mdf[u] = v;
			} else if (md[v] + 1 > sed[u]) {
				sed[u] = md[v] + 1;
				sedf[u] = v;
			}
		}
		len = std::max(len, md[u] + sed[u]);
	}

	void dfs2(int u, int fa) {
		for (int v : e[u]) {
			if (v == fa)
				continue;
			if (mdf[u] != v)
				upd[v] = std::max(md[u], upd[u]) + 1;
			else 
				upd[v] = std::max(sed[u], upd[u]) + 1;
			dfs2(v, u);
		}
		if (upd[u] >= md[u])
			len = std::max(len, md[u] + upd[u]);
	}

public:
	void getLenAndMidpoint() {
		dfs(rt, rt);
		dfs2(rt, rt);
		int maxd = INT_MAX;
		for (int i = 1; i <= n; ++i)
			if (std::max(upd[i], md[i]) < maxd)
				maxd = std::max(upd[i], md[i]), mid1 = i;
			else if (std::max(upd[i], md[i]) == maxd)
				mid2 = i;
		if (std::max(upd[mid1], md[mid1]) != std::max(upd[mid2], md[mid2]))
			mid2 = -1;
		rt = mid1;
	}
	void getCenter() {
		dfs1(rt, rt);
		center = rt;
	}
};