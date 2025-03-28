// Manacher's Algorithm
// Source: https://snuke.hatenablog.com/entry/2014/12/02/235837
//  * Time: O(N)
//  * Description: length of largest palindrome centered at each character of string
//  	* and between every consecutive pair
//  * Verification: http://www.spoj.com/problems/MSUBSTR/

// add '$' for even palindromes
string S; S.pb('$');
for (auto &x : s) {
    S += x + string("$");
}

// Manacher algorithm
vector<int> manacher(const string &S) {
    int n = S.size(), i = 0, j = 0;
    std::vector<int> R(n);
    while (i < n) {
        while (i - j >= 0 && i + j < n && S[i - j] == S[i + j]) ++j;
        R[i] = j;
        int k = 1;
        while (i - k >= 0 && k + R[i - k] < j) R[i + k] = R[i - k], ++k;
        i += k; j -= k;
    }
    return R;
}
 
