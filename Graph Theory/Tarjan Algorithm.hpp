#include <stack>
#include <vector>
#include <algorithm>

struct Tarjan_Graph {
    public: 
        int n, scccnt;
        std::vector<int> *g;
        std::vector<std::vector<int>> scc;
        std::vector<int> sccn;
    private:
        int t;
        bool MultipleEdgeAllowed;

    private: 
        void tarjan_dfs(int u, std::vector<int> &low, std::vector<int> &dis, std::stack<int> &st, std::vector<bool> &inst) {
            dis[u] = low[u] = ++t, st.push(u), inst[u] = true;
            for (int v : g[u]) 
                if (!dis[v])
                    tarjan_dfs(v, low, dis, st, inst), low[u] = std::min(low[u], low[v]);
                else if (inst[v])   
                    low[u] = std::min(low[u], dis[v]);
            if (low[u] == dis[u]) {
                scc.emplace_back();
                while (st.top() != u)
                    scc[scccnt].push_back(st.top()), sccn[st.top()] = scccnt + 1, inst[st.top()] = false, st.pop();
                scc[scccnt].push_back(st.top()), sccn[st.top()] = scccnt + 1, inst[st.top()] = false, st.pop();
                ++scccnt;
            }
        }
    public:
        Tarjan_Graph(int n) {
            this->n = n;
            g = new std::vector<int>[n + 1];
            MultipleEdgeAllowed = true, scccnt = 0;
        }
        inline void adde(int u, int v) {
            g[u].push_back(v);
        }
        void SCC() {
            std::vector<int> low(n + 1, 0);
            std::vector<int> dis(n + 1, 0);
            std::stack<int> st;
            std::vector<bool> inst(n + 1, false);
            sccn.resize(n + 1, 0);
            for (int i = 1; i <= n; ++i)
                if (!dis[i])
                    t = 0, tarjan_dfs(i, low, dis, st, inst);

        }
        void Shrink() {
            std::vector<int> *newg = new std::vector<int>[scccnt + 1];
            for (int u = 1; u <= n; ++u)
                for (int v : g[u])
                    if (sccn[u] != sccn[v])
                        newg[sccn[u]].push_back(sccn[v]);
            n = scccnt, g = newg;

            if (!MultipleEdgeAllowed) {
                for (int u = 1; u <= n; ++u) {
                    sort(g[u].begin(), g[u].end());
                    auto __tmp = unique(g[u].begin(), g[u].end());
                    g[u].erase(__tmp, g[u].end());
                }
            }

        }
        inline void MultipleEdgeNotAllowed() {
            MultipleEdgeAllowed = false;
        }

};