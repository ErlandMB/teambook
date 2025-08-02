#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

ll mul(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

ll powmod(ll a, ll b, ll mod) {
    ll res = 1 % mod;
    while (b > 0) {
        if (b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool miller_rabin(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    ll r = 0, d = n - 1;
    while ((d & 1) == 0) d >>= 1, ++r;
    for (ll a : {2, 3, 5, 7, 11}) {
        if (a >= n) break;
        ll x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int i = 0; i < r - 1; i++) {
            x = mul(x, x, n);
            if (x == n - 1) ok = true;
        }
        if (!ok) return false;
    }
    return true;
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
    if (miller_rabin(n)) return n;
    while (true) {
        ll x = rand() % (n - 2) + 2;
        ll c = rand() % (n - 1) + 1;
        ll d = rho(n, x, c);
        if (d != n && d != 1) return d;
    }
}

void factorize(ll n, map<ll, int>& factors) {
    if (n == 1) return;
    if (miller_rabin(n)) {
        factors[n]++;
        return;
    }
    ll f = pollard(n);
    factorize(f, factors);
    factorize(n / f, factors);
}

ll SumOfDivisors(ll n) {
    map<ll, int> pf;
    factorize(n, pf);
    ll total = 1;
    for (auto [p, e] : pf) {
        ll term = 1, power = 1;
        for (int i = 0; i < e; i++) {
            power *= p;
            term += power;
        }
        total *= term;
    }
    return total;
}

ll NumberOfDivisors(ll n) {
    map<ll, int> pf;
    factorize(n, pf);
    ll total = 1;
    for (auto [_, e] : pf) {
        total *= (e + 1);
    }
    return total;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        cout << "Proper divisor sum: " << SumOfDivisors(n) - n << '\n';
        cout << "Total number of divisors: " << NumberOfDivisors(n) << '\n';
    }
    return 0;
}
