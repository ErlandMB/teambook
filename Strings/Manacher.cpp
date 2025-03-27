// Manacher's Algorithm - Finding all sub-palindromes in O(n)
string S;
S.pb('#');
forn (i, sz(s)) {
    S.pb(s[i]);
    S.pb('#');
}

// Manacher algorithm
ll i = 0, j = 0;
vll R(sz(S));
while (i < S.size()) {
    while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
    R[i] = j;
    int k = 1;
    while (i-k >= 0 && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
    i += k; j -= k;
}
