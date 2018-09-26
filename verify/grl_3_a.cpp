#include<bits/stdc++.h>
using namespace std;

#include "../lowlink.cpp"

//problemId=GRL_3_A
signed main(){
  int n,m;
  scanf("%d %d",&n,&m);
  LowLink G(n);
  for(int i=0;i<m;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    G.add_edge(u,v);
  }
  G.build();
  auto ap=G.ap;
  sort(ap.begin(),ap.end());
  for(int v:ap) printf("%d\n",v);
  return 0;
}
