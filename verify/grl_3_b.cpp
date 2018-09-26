#include<bits/stdc++.h>
using namespace std;

#include "../lowlink.cpp"

//problemId=GRL_3_B
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
  
  auto bs=G.bs;
  for(auto &e:bs)
    if(e.first>e.second) swap(e.first, e.second);
  
  sort(bs.begin(),bs.end());
  for(auto e:bs) printf("%d %d\n",e.first, e.second);
  
  return 0;
}
