//模板一：未加预处理
//复杂度mlogp，当p比较大的时候可以单个处理
const ll p=1e9+7; //根据题目要求改变
ll pow_mod(ll x, ll n){
  ll res=1;
  while(n>0){
      if(n&1)res=res*x%p;
      x=x*x%p;
      n>>=1;
  }
  return res;
}

ll C(ll n,ll m,ll mod){
    if(m>n) return 0;
    ll i,ans=1,a,b;
    for(i=0; i<m; i++){
        a=(n-i)%mod;
        b=(m-i)%mod;
        ans=ans*( a*pow_mod(b,mod-2)%mod )%mod;
    }
    return ans;
}

ll lucas(ll n,ll m,ll p){
    if(m==0) return 1;
    return ( C(n%p, m%p, p)*lucas(n/p, m/p, p) )%p;
}

//例题BZOJ4403
//模板二：加了对确定p的预处理
//预处理O(p),每次计算O(logpN)
const int mod=1e6+3;//根据题目要求改变
ll fac[mod],inv[mod];
void Pretreatment(){//预处理，需要在主函数中声明
    int i;
    for(fac[0]=1,i=1;i<mod;i++)
        fac[i]=fac[i-1]*i%mod;
    for(inv[1]=1,i=2;i<mod;i++)
        inv[i]=(mod-mod/i)*inv[mod%i]%mod; //逆元打表公式
    for(inv[0]=1,i=1;i<mod;i++) //用到的逆元很多，最好先打表
        (inv[i]*=inv[i-1])%=mod; //前缀逆元积
}

ll C(int n,int m){
    if(n<m) return 0;
    if(n<mod && m<mod)
        return fac[n] * inv[m] % mod * inv[n-m] % mod ;
    return C(n/mod,m/mod) * C(n%mod,m%mod) % mod ;
}

//例题HDU3944
//模板三：加了对p及以下所有素数取模的预处理（全用的int型）
//设P以下素数的个数为k，复杂度为O(kP)
int P;//输入的模P
const int N = 10005;//P的最大值
bool prime[N];
int p[N],f[N][N],inv[N][N],cnt,pth[N];

void isprime(){//先声明
  cnt=0;
  memset(prime,1,sizeof(prime));
  for(int i=2;i<N;i++){//埃式筛法
    if(prime[i]){
      p[++cnt]=i;//记录素数
      pth[i]=cnt;//第几个素数
      for(int j=i+i;j<N;j+=i)
        prime[j]=0;
      }
  }
}

int pow_mod(int a,int b,int m){
  int ans=1;
  a%=m;
  while(b){
    if(b&1){
      ans=ans*a%m;
      b--;
    }
    b>>=1;
    a=a*a%m;
  }
  return ans;
}

void init(){//预处理阶乘与逆元,先声明
  for(int i=1;i<=cnt;i++){
    f[i][0]=inv[i][0]=1;
    for(int j=1;j<p[i];j++){
      f[i][j]=(f[i][j-1]*j)%p[i]; //模第i个素数的所有阶乘
      inv[i][j]=pow_mod(f[i][j],p[i]-2,p[i]); //模第i个素数的所有逆元
    }
  }
}

int C(int n,int m,int p){
  if(m>n) return 0;
  if(m==n) return 1;
  int t=pth[p];
  return f[t][n]*(inv[t][n-m]*inv[t][m]%p)%p;
}

int lucas(int n,int m,int p){
  if(m==0) return 1;
  return C(n%p,m%p,p)*lucas(n/p,m/p,p)%p;
}
