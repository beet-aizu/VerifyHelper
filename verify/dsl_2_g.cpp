#include<bits/stdc++.h>
using namespace std;

#include "../chien.cpp"
#include "../mint.cpp"

//problemId=DSL_2_G
signed main(){
  int n,q;
  scanf("%d %d",&n,&q);
  
  using Int = long long;
  using P = pair<Int, Int>;
  auto f=[](P a,P b){return P(a.first+b.first,a.second+b.second);};
  auto g=[](P a,Int b){return P(a.first+b*a.second,a.second);};
  auto h=[](Int a,Int b){return a+b;};
  
  SegmentTree<P, Int> ch(n,f,g,h,P(0,0),0);  
  ch.build(n,vector<P>(n,P(0,1)));
  
  for(int i=0;i<q;i++){
    int c,s,t,x;
    scanf("%d",&c);
    if(c){
      scanf("%d %d",&s,&t);
      printf("%lld\n",ch.query(s-1,t).first);
    }else{
      scanf("%d %d %d",&s,&t,&x);
      ch.update(s-1,t,x);
    }
  }
  return 0;
}
