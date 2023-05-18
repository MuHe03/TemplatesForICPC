#include <vector>

struct Int {
private:
    int v, inn;
    const static int mod = 998244353;
    static int n = 1e6;
    static std::vector<int> fac, inv, invfac;

public:
    Int() : v(0), inn(0) {}
    Int(long long __v) : v(__v % mod), inn(0) {}

    int get() { return v; }

    inline static void init(const int n = this.n) {
        this.n = n;
        fac.resize(n + 1);
        inv.resize(n + 1);
        invfac.resize(n + 1);
        fac[0] = inv[0] = invfac[0] = 1;
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
        for (int i = 1; i <= n; ++i) {
            fac[i] = (long long)fac[i - 1] * i % mod;
            invfac[i] = (long long)invfac[i - 1] * inv[i] % mod;
        }
    }

    static inline long long fac(int x) { return fac[x]; }
    static inline long long inv(int x) { return inv[x]; }
    static inline long long invfac(int x) { return invfac[x]; }

    static inline long long C(int m, int n) {
        return (n < 0 || m < n) ? 0 : (long long)fac[m] * invfac[n] % mod * invfac[m - n] % mod;
    }

    inline long long inv() {
        if (v <= n)
            return inv[v];
        if (inn)
            return inn;
        long long a = v, b = mod - 2;
        inn = 1;
        while (b) {
            if (b & 1)
                inn = inn * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return inn % mod;
    }
    
    Int operator + (const Int &rhs) { return ((long long)v + rhs.v) % mod; }
    Int operator - (const Int &rhs) { return (v - rhs.v + mod) % mod; }
    Int operator * (const Int &rhs) { return (long long)v * rhs.v % mod; }
    Int operator / (Int &rhs) { return (long long)v * rhs.inv() % mod; }
    Int operator - () { return mod - v; }

    Int &operator += (const Int &rhs) { return *this = *this + rhs; }
    Int &operator -= (const Int &rhs) { return *this = *this - rhs; }
    Int &operator *= (const Int &rhs) { return *this = *this * rhs; }
    Int &operator /= (Int &rhs) { return *this = *this / rhs; }

};