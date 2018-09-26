#include<bits/stdc++.h>
using namespace std;

#include "../mint.cpp"

//problemId=DPL_5_L
signed main(){
  int n,k;
  scanf("%d %d",&n,&k);
  printf("%d\n",n>=k?Mint<int>::D(n,k)[n-k][k].v:0);
  return 0;
}
