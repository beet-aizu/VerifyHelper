#include<bits/stdc++.h>
using namespace std;

#include "../mint.cpp"

//problemId=DPL_5_E
signed main(){
  int n,k;
  scanf("%d %d",&n,&k);
  printf("%d\n",Mint<int>::C(k,n).v);
  return 0;
}
