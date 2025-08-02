//long long type hasta 18 digitos
#include <bits/stdc++.h>
using namespace std;

using ll   = long long;
using u64  = uint64_t;
using u128 = __uint128_t;

// fast modular multiplication  
inline u64 mod_mul(u64 a, u64 b, u64 m) {
    return (u128)a * b % m;
}

ll gcd(ll a, ll b) { if (b == 0) return a; return gcd(b, a % b);}

// fast modular exponentiation
u64 mod_pow(u64 a, u64 e, u64 m) {
    u64 res = 1;
    a %= m;
    while (e) {
        if (e & 1) res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        e >>= 1;
    }
    return res;
}

// deterministic Miller–Rabin for 64-bit
bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

// Pollard's Rho
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll pollard(ll n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    uniform_int_distribution<ll> distX(2, n-2);
    uniform_int_distribution<ll> distC(1, n-1);
    while (true) {
        ll x = distX(rng), y = x;
        ll c = distC(rng), d = 1;
        auto f = [&](ll v){ return (mod_mul(v,v,n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd(abs(x - y), n);
        }
        if (d > 1 && d < n) return d;
    }
}

// recursive factorization into map
void factorize(ll n, map<ll,int> &fac) {
    if (n <= 1) return;
    if (isPrime(n)) {
        fac[n]++;
    } else {
        ll d = pollard(n);
        factorize(d, fac);
        factorize(n/d, fac);
    }
}

// number of divisors
ll numOfDiv(ll n) {
    map<ll,int> fac;
    factorize(n, fac);
    ll cnt = 1;
    for (auto &pr : fac) cnt *= (pr.second + 1);
    return cnt;
}

// sum of divisors
ll sumOfDiv(ll n) {
    map<ll,int> fac;
    factorize(n, fac);
    ll total = 1;
    for (auto &pr : fac) {
        ll p = pr.first;
        int e = pr.second;
        ll term = 1, cur = 1;
        for (int i = 0; i < e; i++) {
            cur *= p;
            term += cur;
        }
        total *= term;
    }
    return total;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        // mostrar sólo sumatorio de divisores:
        cout << sumOfDiv(n) << "\n";
        // si quieres también número de divisores, usa:
        // cout << numOfDiv(n) << "\n";
    }
    return 0;
}


// hasta 20 digitos
#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;
using u128 = __uint128_t;

// High-quality RNG
static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Generate a random __int128 in [lo..hi]
i128 random_i128(i128 lo, i128 hi) {
    u128 range = (u128)(hi - lo) + 1;
    u128 r = ((u128)rng() << 64) ^ rng();
    return lo + (i128)(r % range);
}

// a * b mod m, safe via 128-bit
inline i128 mulmod(i128 a, i128 b, i128 m) {
    return (u128)a * b % m;
}

// fast exponentiation a^e mod m
i128 powmod(i128 a, i128 e, i128 m) {
    i128 res = 1;
    a %= m;
    while (e > 0) {
        if (e & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return res;
}

// deterministic Miller–Rabin for n < 2^64
bool isPrime(i128 n) {
    if (n < 2) return false;
    for (i128 p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n % p == 0) return n == p;
    }
    // write n-1 = d * 2^s
    i128 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (i128 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0) continue;
        i128 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

// Pollard's Rho to find a non-trivial factor
i128 pollards_rho(i128 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    while (true) {
        i128 c = random_i128(1, n - 1);
        i128 x = random_i128(2, n - 2);
        i128 y = x;
        i128 d = 1;
        auto f = [&](i128 v){ return (mulmod(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd((i128)(x>y ? x-y : y-x), n);
        }
        if (d > 1 && d < n) return d;
    }
}

// Recursive factorization
void factor(i128 n, map<i128,int> &fac) {
    if (n == 1) return;
    if (isPrime(n)) {
        fac[n]++;
    } else {
        i128 d = pollards_rho(n);
        factor(d, fac);
        factor(n / d, fac);
    }
}

// Compute number of divisors by factoring n directly
i128 numOfDiv(i128 n) {
    map<i128,int> fac;
    factor(n, fac);
    i128 cnt = 1;
    for (auto &pr : fac) cnt *= (pr.second + 1);
    return cnt;
}

// Compute sum of divisors by factoring n directly
i128 sumOfDiv(i128 n) {
    map<i128,int> fac;
    factor(n, fac);
    i128 total = 1;
    for (auto &pr : fac) {
        i128 p = pr.first;
        int e = pr.second;
        i128 term = 1, cur = 1;
        for (int i = 0; i < e; i++) {
            cur *= p;
            term += cur;
        }
        total *= term;
    }
    return total;
}

// Convert string to __int128
i128 str2i128(const string &s) {
    i128 x = 0;
    for (char c : s) x = x*10 + (c - '0');
    return x;
}

// Convert __int128 to string
string i1282str(i128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        s.push_back('0' + int(x % 10));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Lectura estándar
    string line;
    while (cin >> line) {
        if (line == "0") break;
        i128 n = str2i128(line);
        map<i128,int> fac;
        factor(n, fac);

        // Mostrar factorización
        bool first = true;
        for (auto &pr : fac) {
            if (!first) cout << ' ';
            cout << i1282str(pr.first) << '^' << pr.second;
            first = false;
        }
        // Mostrar número y suma de divisores
        cout << "  #divs=" << i1282str(numOfDiv(fac))
             << "  #sumDiv=" << i1282str(sumOfDiv(fac))
             << "\n";
    }

    return 0;
}

