#include<bits/stdc++.h>
using namespace std;

#include "../mint.cpp"

//problemId=DPL_5_F
signed main(){
  int n,k;
  scanf("%d %d",&n,&k);
  printf("%d\n",Mint<int>::C(n-1,k-1).v);
  return 0;
}
