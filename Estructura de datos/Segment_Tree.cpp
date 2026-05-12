
struct SegTree {
    int n;
    vector<ll> st;
    SegTree(int sz) {
        n=sz;
        st.assign(4*n, 0);
    }
    void build(int v, int l, int r, vector<ll>& a, bool op) {
        if (l==r) {
            st[v]=a[l];
            return;
        }
        int m=(l+r)/2;
        build(v*2+1, l, m, a, !op);
        build(v*2+2, m+1, r, a, !op);
        if(op)
            st[v]=st[v*2+1]|st[v*2+2];
        else
            st[v]=st[v*2+1]^st[v*2+2];
    }
    void update(int v, int l, int r, int pos, int val, bool op) {
        if (l==r) {
            st[v]=val;
            return;
        }
        int m=(l+r)/2;
        if(pos<= m)
            update(v*2+1, l, m, pos, val, !op);
        else
            update(v*2+2, m+1, r, pos, val, !op);
        if(op)
            st[v]=st[v*2+1]|st[v*2+2];
        else
            st[v]=st[v*2+1]^st[v*2+2];
    }
};
