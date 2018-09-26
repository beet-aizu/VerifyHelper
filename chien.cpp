#include<bits/stdc++.h>
using namespace std;
//BEGIN CUT HERE
template <typename T,typename E>
struct SegmentTree{
  using F = function<T(T,T)>;
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;
  int n,height;
  F f;
  G g;
  H h;
  T ti;
  E ei;
  vector<T> dat;
  vector<E> laz;
  SegmentTree(int n_,F f,G g,H h,T ti,E ei):
    f(f),g(g),h(h),ti(ti),ei(ei){init(n_);}
  void init(int n_){
    n=1;height=0;
    while(n<n_) n<<=1,height++;
    dat.assign(2*n,ti);
    laz.assign(2*n,ei);
  }
  void build(int n_, vector<T> v){
    for(int i=0;i<n_;i++) dat[n+i]=v[i];
    for(int i=n-1;i;i--)
      dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
  }
  T reflect(int k){
    return g(dat[k],laz[k]);
  }
  inline void eval(int k){
    if(laz[k]==ei) return;
    laz[(k<<1)|0]=h(laz[(k<<1)|0],laz[k]);
    laz[(k<<1)|1]=h(laz[(k<<1)|1],laz[k]);
    dat[k]=reflect(k);
    laz[k]=ei;
  }
  void update(int a,int b,E x){
    a+=n;b+=n-1;
    for(int i=height;i;i--) eval(a>>i);
    for(int i=height;i;i--) eval(b>>i);
    for(int l=a,r=b+1;l<r;l>>=1,r>>=1){
      if(l&1) laz[l]=h(laz[l],x),l++;
      if(r&1) --r,laz[r]=h(laz[r],x);
    }
    while(a>>=1)
      dat[a]=f(reflect((a<<1)|0),reflect((a<<1)|1));
    while(b>>=1)
      dat[b]=f(reflect((b<<1)|0),reflect((b<<1)|1));
  }
  T query(int a,int b){
    a+=n;b+=n-1;
    for(int i=height;i;i--) eval(a>>i);
    for(int i=height;i;i--) eval(b>>i);
    T vl=ti,vr=ti;
    for(int l=a,r=b+1;l<r;l>>=1,r>>=1) {
      if(l&1) vl=f(vl,reflect(l++));
      if(r&1) vr=f(reflect(--r),vr);
    }
    return f(vl,vr);
  }
};
//END CUT HERE

/* 
   BEGIN VERIFY
   dsl_2_g.cpp,
   END VERIFY
*/ 
