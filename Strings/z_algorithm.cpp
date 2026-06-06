//El vector z[i]=cuantos caracteres coinciden entre s[0...] y s[i...]
//es decir cuanto se parece cada posicion al inicio de la cadena
vector<ll> z_function(const string &s){
  	vector<ll> z(s.size());
  	z[0]=s.size();
  	ll l=0;
  	ll r=0;
  	for(int i=1; i<s.size(); i++){
  		z[i]=max(0LL, min(z[i-l], r-i+1));
  		while(i+z[i]<s.size()&&s[z[i]]==s[i+z[i]]){
  			l=i;
  			r=i+z[i];
  			z[i]++;
  		}
  	}
    return z;
}
