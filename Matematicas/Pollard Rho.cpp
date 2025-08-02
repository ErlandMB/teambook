
using u64 = uint64_t;
using u128 = __uint128_t;
using ll = long long;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool MillerRabin(u64 n) { // returns true if n is prime, else false
    if (n < 2)
        return false;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

ll gcd(ll a, ll b) {
    while (b) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

ll mul(ll a, ll b, ll mod) {
    return (u128)a * b % mod;
}

ll rho(ll n, ll x0 = 2, ll c = 1) {
    ll x = x0, y = x0, d = 1;
    while (d == 1) {
        x = (mul(x, x, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        d = gcd(abs(x - y), n);
    }
    return d;
}

ll pollard(ll n) {
    if (n % 2 == 0) return 2;
    if (MillerRabin(n)) return n;
    while (true) {
        ll x = rand() % (n - 2) + 2;
        ll c = rand() % (n - 1) + 1;
        ll d = rho(n, x, c);
        if (d != n && d != 1) return d;
    }
}

void factorize(ll n, map<ll, int> &factors) {
    if (n == 1) return;
    if (MillerRabin(n)) {
        factors[n]++;
        return;
    }
    ll d = pollard(n);
    factorize(d, factors);
    factorize(n / d, factors);
}
//suma de divisores
ll SumDiv(ll n) {
    map<ll, int> pf;
    factorize(n, pf);
    ll total = 1;
    for (auto &[p, e] : pf) {
        ll term = 1, power = 1;
        for (int i = 0; i < e; i++) {
            power *= p;
            term += power;
        }
        total *= term;
    }
    return total;
}
//numero de divisores
ll NumDiv(ll n) {
    map<ll, int> pf;
    factorize(n, pf);
    ll total = 1;
    for (auto &[_, e] : pf) {
        total *= (e + 1);
    }
    return total;
}
