ll expmod(ll x, ll n) {if (n == 0) return 1 % MOD; ll u = expmod(x, n / 2); u = (u * u) % MOD; if (n & 1) u = (u * x) % MOD; return u; }

ll invmod(ll a){ return expmod(a, MOD - 2); }

const int max_n = int(2e5 + 1);

vll fac(max_n), fac_inv(max_n);
int nck(int n, int k) {
    return k < 0 ? 0 : n < 0 ? 0 : k > n ? 0 : fac[n] * fac_inv[k] % MOD * fac_inv[n - k] % MOD;
};
void precalbino() {
    fac[0] = 1;
    fore(i, 1, max_n)
        fac[i] = fac[i - 1] * i % MOD;
    fac_inv[max_n - 1] = invmod(fac[max_n - 1]);
    for(int i = max_n - 2; i >= 0; i--)
        fac_inv[i] = fac_inv[i + 1] * (i + 1) % MOD;
}
