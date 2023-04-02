#include <vector>
#include <functional>

template<typename T> struct BinaryIndexTree {
private:
	std::vector<T> a;
	T nullValue;
	std::function<T(T, T)> aggreFunc;
	std::function<T(T)> negFunc;
    int n;

public:
	BinaryIndexTree(int __n, std::function<T(T, T)> __aggreFunc, std::function<T(T)> __negFunc, T __nullValue) : n(__n), nullValue(__nullValue, aggreFunc(__aggreFunc), negFunc(__negFunc)) {
		a.resize(n + 1);
	}

    void add(int x, T v) {
        for (; x <= n; x += x & -x)
            a[x] = aggreFunc(a[x], v);
    }

    T query(int x) {
        T res = nullValue;
        for (; x; x -= x & -x)
            res = aggreFunc(res, a[x]);
        return res;
    }

    T query(int l, int r) {
        return aggreFunc(query(r), negFunc(query(l - 1)));
    }
};
