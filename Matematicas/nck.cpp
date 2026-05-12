long long nck(long long n, long long k) {
    if (k > n) return 0;
    k = min(k, n - k);

    long long res = 1;
    for (long long i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}
