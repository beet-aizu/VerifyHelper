#include<bits/stdc++.h>
using namespace std;

#include "../mint.cpp"

//problemId=DPL_5_D
signed main(){
  int n,k;
  scanf("%d %d",&n,&k);
  printf("%d\n",Mint<int>::H(n,k).v);
  return 0;
}
