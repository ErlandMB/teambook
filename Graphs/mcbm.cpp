vi match, vis;                                   // global variables
vector<vi> AL;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : AL[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}


//dentro del main
match.assign(V, -1);
int MCBM=0;
for(int L=0; L<left; L++){
  vis.assign(VLeft, 0);
  MCBM+=Aug(L);
}
cout <<"Found "<<MCBM<<"Matchings\n";
