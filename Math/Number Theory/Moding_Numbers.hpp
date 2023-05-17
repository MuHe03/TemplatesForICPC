struct Int {
private:
    int v, inn;
    const static int mod = 998244353;

public:
    Int() : v(0), inn(0) {}
    Int(long long __v) : v(__v % mod), inn(0) {}

    int get() { return v; }

    inline long long inv() {
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