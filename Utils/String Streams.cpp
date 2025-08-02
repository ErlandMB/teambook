// For some complex reading of input
// st is the same as a cin, but you pass the string
string line;
getline(cin, line);
stringstream st(line);
vl in;
ll x;
while (st >> x) {
    in.pb(x);
}
