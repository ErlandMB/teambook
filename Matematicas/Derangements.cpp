//Derangements

// https://judge.yosupo.jp/problem/montmort_number_mod

/*The number of derangements of n numbers, expressed as 
!n, is the number of permutations such that no element appears in its original position. 
Informally, it is the number of ways 
n hats can be returned to n people such that no person receives their own hat.
*/


void solve(){
    ll a, b;cin>>a>>b;
    mint c=1;
    MOD=b;
    for(ll i=1; i<=a; i++){
        c=(c*i)+(i&1?-1:1);
        cout<<c.v<<' ';
    }
}
