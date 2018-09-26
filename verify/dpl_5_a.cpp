#include<bits/stdc++.h>
using namespace std;

#include "../mint.cpp"

//problemId=DPL_5_A
signed main(){
  int n;
  Mint<int> k;
  scanf("%d %d",&n,&k.v);
  printf("%d\n",k.pow(n).v);
  return 0;
}
