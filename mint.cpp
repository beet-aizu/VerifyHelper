#include<bits/stdc++.h>
using namespace std;
//BEGIN CUT HERE
template<typename T,T MOD = 1000000007>
struct Mint{
  T v;
  Mint():v(0){}
  Mint(signed v):v(v){}
  Mint(long long t){v=t%MOD;if(v<0) v+=MOD;}

  Mint pow(int k){
    Mint res(1),tmp(v);
    while(k){
      if(k&1) res*=tmp;
      tmp*=tmp;
      k>>=1;
    }
    return res;
  }
  
  Mint inv(){return pow(MOD-2);}
  
  Mint& operator+=(Mint a){v+=a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator-=(Mint a){v+=MOD-a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator*=(Mint a){v=1LL*v*a.v%MOD;return *this;}
  Mint& operator/=(Mint a){return (*this)*=a.inv();}
  
  Mint operator+(Mint a){return Mint(v)+=a;};
  Mint operator-(Mint a){return Mint(v)-=a;};
  Mint operator*(Mint a){return Mint(v)*=a;};
  Mint operator/(Mint a){return Mint(v)/=a;};

  Mint operator-(){return v?MOD-v:v;}

  bool operator==(const Mint a)const{return v==a.v;}
  bool operator!=(const Mint a)const{return v!=a.v;}

  static vector<Mint> fact,finv,invs;
  
  static void init(int n){
    if(n+1<=(signed)fact.size()) return;
    fact.assign(n+1,1);
    finv.assign(n+1,1);
    invs.assign(n+1,1);
    
    for(int i=1;i<=n;i++) fact[i]=fact[i-1]*Mint(i);
    finv[n]=Mint(1)/fact[n];
    for(int i=n;i>=1;i--) finv[i-1]=finv[i]*Mint(i);
    for(int i=1;i<=n;i++) invs[i]=finv[i]*fact[i-1];
  }

  static Mint comb(long long n,int k){
    Mint res(1);
    for(int i=0;i<k;i++){
      res*=Mint(n-i);
      res/=Mint(i+1);
    }
    return res;
  }
  
  static Mint C(int n,int k){
    if(n<k||k<0) return Mint(0);
    init(n);
    return fact[n]*finv[n-k]*finv[k];
  }

  static Mint P(int n,int k){
    if(n<k||k<0) return Mint(0);
    init(n);
    return fact[n]*finv[n-k];
  }
  
  static Mint H(int n,int k){
    if(n<0||k<0) return Mint(0);
    if(!n&&!k) return Mint(1);
    init(n+k-1);
    return C(n+k-1,n);
  }

  static Mint S(int n,int k){
    Mint res;
    init(k);
    for(int i=1;i<=k;i++){
      Mint tmp=C(k,i)*Mint(i).pow(n);
      if((k-i)&1) res-=tmp;
      else res+=tmp;
    }    
    return res*=finv[k];
  }

  static vector<vector<Mint> > D(int n,int m){
    vector<vector<Mint> > dp(n+1,vector<Mint>(m+1,0));
    dp[0][0]=Mint(1);
    for(int i=0;i<=n;i++){
      for(int j=1;j<=m;j++){
	if(i-j>=0) dp[i][j]=dp[i][j-1]+dp[i-j][j];
	else dp[i][j]=dp[i][j-1];
      }
    }
    return dp;
  }

  static Mint B(int n,int k){
    Mint res;
    for(int j=1;j<=k;j++) res+=S(n,j);
    return res;
  }

  static Mint montmort(int n){
    Mint res;
    init(n);
    for(int k=2;k<=n;k++){
      if(k&1) res-=finv[k];
      else res+=finv[k];
    }
    return res*=fact[n];
  }

  static Mint LagrangePolynomial(vector<Mint> &y,Mint t){
    int n=y.size()-1;
    init(n+1);
    Mint num(1);
    for(int i=0;i<=n;i++) num*=t-Mint(i);
    Mint res;
    for(int i=0;i<=n;i++){
      Mint tmp=y[i]*num/(t-Mint(i))*finv[i]*finv[n-i];
      if((n-i)&1) res-=tmp;
      else res+=tmp;
    }
    return res;
  }
};
template<typename T,T MOD>
vector<Mint<T, MOD> > Mint<T, MOD>::fact = vector<Mint<T, MOD> >();
template<typename T,T MOD>
vector<Mint<T, MOD> > Mint<T, MOD>::finv = vector<Mint<T, MOD> >();
template<typename T,T MOD>
vector<Mint<T, MOD> > Mint<T, MOD>::invs = vector<Mint<T, MOD> >();
//END CUT HERE

/*
  BEGIN VERIFY
  dpl_5_a.cpp,
  dpl_5_b.cpp,
  dpl_5_c.cpp,
  dpl_5_d.cpp,
  dpl_5_e.cpp,
  dpl_5_f.cpp,
  dpl_5_g.cpp,
  dpl_5_h.cpp,
  dpl_5_i.cpp,
  dpl_5_j.cpp,
  dpl_5_k.cpp,
  dpl_5_l.cpp,
  END VERIFY 
*/
