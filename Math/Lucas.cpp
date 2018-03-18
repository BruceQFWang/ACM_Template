//ģ��һ��δ��Ԥ����
//���Ӷ�mlogp����p�Ƚϴ��ʱ����Ե�������
const ll p=1e9+7; //������ĿҪ��ı�
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

//����BZOJ4403
//ģ��������˶�ȷ��p��Ԥ����
//Ԥ����O(p),ÿ�μ���O(logpN)
const int mod=1e6+3;//������ĿҪ��ı�
ll fac[mod],inv[mod];
void Pretreatment(){//Ԥ������Ҫ��������������
    int i;
    for(fac[0]=1,i=1;i<mod;i++)
        fac[i]=fac[i-1]*i%mod;
    for(inv[1]=1,i=2;i<mod;i++)
        inv[i]=(mod-mod/i)*inv[mod%i]%mod; //��Ԫ���ʽ
    for(inv[0]=1,i=1;i<mod;i++) //�õ�����Ԫ�ܶ࣬����ȴ��
        (inv[i]*=inv[i-1])%=mod; //ǰ׺��Ԫ��
}

ll C(int n,int m){
    if(n<m) return 0;
    if(n<mod && m<mod)
        return fac[n] * inv[m] % mod * inv[n-m] % mod ;
    return C(n/mod,m/mod) * C(n%mod,m%mod) % mod ;
}

//����HDU3944
//ģ���������˶�p��������������ȡģ��Ԥ����ȫ�õ�int�ͣ�
//��P���������ĸ���Ϊk�����Ӷ�ΪO(kP)
int P;//�����ģP
const int N = 10005;//P�����ֵ
bool prime[N];
int p[N],f[N][N],inv[N][N],cnt,pth[N];

void isprime(){//������
  cnt=0;
  memset(prime,1,sizeof(prime));
  for(int i=2;i<N;i++){//��ʽɸ��
    if(prime[i]){
      p[++cnt]=i;//��¼����
      pth[i]=cnt;//�ڼ�������
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

void init(){//Ԥ����׳�����Ԫ,������
  for(int i=1;i<=cnt;i++){
    f[i][0]=inv[i][0]=1;
    for(int j=1;j<p[i];j++){
      f[i][j]=(f[i][j-1]*j)%p[i]; //ģ��i�����������н׳�
      inv[i][j]=pow_mod(f[i][j],p[i]-2,p[i]); //ģ��i��������������Ԫ
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
