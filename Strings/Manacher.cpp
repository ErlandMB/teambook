// Manacher's Algorithm
// Source: https://snuke.hatenablog.com/entry/2014/12/02/235837
//  * Time: O(N)
//  * Description: length of largest palindrome centered at each character of string
//  	* and between every consecutive pair
//  * Verification: http://www.spoj.com/problems/MSUBSTR/

// add '#' for even palindromes
string S; S.pb('$');
fore (i, l, r + 1) {
    S += s[i] + string("$");
}

// Manacher algorithm
vector<int> manacher(const string &s) {
    int n = s.size(), i = 0, j = 0;
    std::vector<int> R(n);
    while (i < n) {
        while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) ++j;
        R[i] = j;
        int k = 1;
        while (i - k >= 0 && k + R[i - k] < j) R[i + k] = R[i - k], ++k;
        i += k; j -= k;
    }
    return R;
}
 
