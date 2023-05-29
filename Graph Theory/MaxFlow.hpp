#include <vector>
#include <queue>

struct MaxFlow {
private:
	struct edge {
        int v, r;
        long long f;
    };
    vector<vector<edge>> g;
    vector<int> d, cur;
    int n, s, t;

	bool bfs() {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto e : g[u]) {
                if (e.f && d[e.v] == -1) {
                    d[e.v] = d[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return d[t] != -1;
    }

    ll dfs(int u, ll fl) {
		if (u == t) return fl;
		for (int &i = cur[u]; i < g[u].size(); ++i) {
			auto &e = g[u][i];
			if (e.f && d[e.v] == d[u] + 1) {
				ll w = dfs(e.v, min(fl, e.f));
				if (w) {
					e.f -= w;
					g[e.v][e.r].f += w;
					return w;
				}
			}
		}
		return 0;
    }

public:
	MaxFlow(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
		g.assign(n, vector<edge>());
	}

    void addedge(int u, int v, long long f) {
		g[u].push_back({v, (int)g[v].size(), f});
		g[v].push_back({u, (int)g[u].size() - 1, 0});
    }

    ll dinic() {
        ll ans = 0;
        while (bfs()) {
            cur.assign(n, 0);
            while (ll w = dfs(s, 1e18)) ans += w;
        }
        return ans;
    }
};