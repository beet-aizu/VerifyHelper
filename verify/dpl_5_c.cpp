#include<bits/stdc++.h>
using namespace std;

#include "../mint.cpp"

//problemId=DPL_5_C
signed main(){
  int n,k;
  scanf("%d %d",&n,&k);
  Mint<int>::init(k);
  printf("%d\n",(Mint<int>::S(n,k)*Mint<int>::fact[k]).v);
  return 0;
}
