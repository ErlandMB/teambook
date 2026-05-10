ll expmod(ll x, ll n) {if (n == 0) return 1 % MOD; ll u = expmod(x, n / 2); u = (u * u) % MOD; if (n & 1) u = (u * x) % MOD; return u; }
ll invmod(ll a){ return expmod(a, MOD - 2); }
