//Knuth-Morris-Pratt

vector<ll> pi(const string &s) {
	  ll n=sz(s);
    vl pi_s(n);
    for(int i=1, j=0; i<n; i++){
        while(j>0&&s[i]!=s[j])j=pi_s[j-1];
        if(s[i]==s[j])j++;
        pi_s[i]=j;
    }
    return pi_s;
}
