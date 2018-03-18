//例题POJ1006
//满足模数两两互质，两两合并
const int N=10010;
int a[N],m[N];//输入余数 模数

void extgcd(int a, int b, int &x, int &y)  {
  if(b == 0){
  	x = 1; y = 0;
    return;
  }
  extgcd(b, a % b, x, y);
  int tmp = x;
  x = y;
  y = tmp - (a / b) * y;
}

int crt(int a[],int m[],int n){//x ≡ a[i] (mod m[i])
  int M = 1;
  int ans = 0;
  for(int i=1; i<=n; i++)
    M *= m[i];
  for(int i=1; i<=n; i++){
    int x, y;
    int Mi = M / m[i];
    extgcd(Mi, m[i], x, y); //Mi模mi的逆元
    ans = (ans + Mi * x * a[i]) % M;
  }
  if(ans < 0) ans += M;
  return ans;
}

//例题POJ2891
//不满足模数两两互质（条件弱化），采取两两合并   注意一组方程的话要特判
const int maxn = 1e5 + 5;
int n;
ll m[maxn], r[maxn];//输入模数 余数

void extgcd(ll a, ll b, ll &d, ll &x, ll &y){
  if (!b) {d = a, x = 1, y = 0;}
  else{
    extgcd(b, a % b, d, y, x);
    y -= x * (a / b);
  }
}

ll extcrt(ll *m, ll *r, int n){
  ll M = m[1], R = r[1], x, y, d;
  for (int i = 2; i <= n; ++i){
    extgcd(M, m[i], d, x, y);
    if ((r[i] - R) % d) return -1;//方程无解，返回-1
    x = (r[i] - R) / d * x % (m[i] / d);
    R += x * M;
    M = M / d * m[i];
    R %= M;
  }
  return R > 0 ? R : R + M;//返回最小解
}
int main(){
  while (~scanf("%d",&n)){
    for (int i = 1; i <= n; ++i)
      scanf("%I64d%I64d", &m[i], &r[i]);
    printf("%I64d\n",extcrt(m,r,n));
  }
    return 0;
}
