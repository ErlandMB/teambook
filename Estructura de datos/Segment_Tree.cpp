struct SegTree {
    int n;
    vector<long long> st;

    SegTree(int _n) {
        n = 1;
        while (n < _n) n <<= 1;
        st.assign(2 * n, 0);
    }
    void build(vector<int>& a) {
        for (int i = 0; i < (int)a.size(); i++)
            st[n + i] = a[i];

        for (int i = n - 1; i >= 1; i--)
            st[i] = st[i << 1] + st[i << 1 | 1];
    }
    // point update: a[pos] = val
    void update(int pos, long long val) {
        pos += n;
        st[pos] = val;

        for (pos >>= 1; pos; pos >>= 1)
            st[pos] = st[pos << 1] + st[pos << 1 | 1];
    }
    // query sum on [l, r]
    long long query(int l, int r) {
        long long res = 0;
        l += n;
        r += n;
        while (l <= r) {
            if (l & 1) res += st[l++];
            if (!(r & 1)) res += st[r--];

            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};
