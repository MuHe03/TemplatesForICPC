#include <vector>
#include <climits>

struct GetD {
public:
	int n, rt, len, rt2;

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
		len = 0, rt = rt2 = -1;
	}

private:
	void dfs(int u, int fa) {
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
	void solve() {
		dfs(1, 0);
		dfs2(1, 0);
		int maxd = INT_MAX;
		for (int i = 1; i <= n; ++i)
			if (std::max(upd[i], md[i]) < maxd)
				maxd = std::max(upd[i], md[i]), rt = i;
			else if (std::max(upd[i], md[i]) == maxd)
				rt2 = i;
		if (std::max(upd[rt], md[rt]) != std::max(upd[rt2], md[rt2]))
			rt2 = -1;
	}
};