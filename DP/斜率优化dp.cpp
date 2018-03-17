б���Ż�dp�����϶��ǿ��Ի��� dp[i]=min(dp[j]+cost(j+1,i)) ��������ʽ����ά�ľ���dp[i][m]=min(dp[j][m-1]+cost(j+1,i));

1.bzoj1010
���⣺��n����ߣ���߳���Ϊci����������߿���װ��ͬһ��������֮��Ҫ����1����λ�Ŀռ䡣����������Ϊ(X-L)^2������X��ʾ�������ȣ�L��ʾ����������С���á�
���룺
const int N = 5e4+5;

int c[N];
ll dp[N], sum[N];
int n, L;
int deq[N];

double cal(int j, int k){
    return (dp[k]-dp[j]+(sum[k]+L)*(sum[k]+L)-(sum[j]+L)*(sum[j]+L))/(2.0*(sum[k]-sum[j]));
}

void solve(){
    int l = 1, r = 0; deq[++r] = 0;
    for(int i=1; i<=n; i++){
        while(l < r && cal(deq[l], deq[l+1]) <= sum[i])l++;
        int tmp = deq[l];
        dp[i] = dp[tmp]+(sum[i]-sum[tmp]-L)*(sum[i]-sum[tmp]-L);
        while(l < r && cal(deq[r], i) < cal(deq[r-1], deq[r]))r--;
        deq[++r] = i;
    }
}

int  main(){
    scanf("%d%d", &n, &L);
    L++;
    for(int i=1; i<=n; i++)scanf("%d", &c[i]);
    for(int i=1; i<=n; i++)sum[i] = sum[i-1]+c[i];
    for(int i=1; i<=n; i++)sum[i] += i;
    solve();
    printf("%lld\n", dp[n]);
    return 0;
}

2.hdu3507
���⣺�������a[n]��ÿ��������ķ�����������������ֺ͵�ƽ�����ϳ���M
ps��ע������ж���Ӻͳ��ӵĵط���С�ڵ��ڶ�����С�ڣ�С�ڻ�wa��
�ѳ���ɳ�
���룺
const int N = 5e5+5;

ll dp[N], sum[N];
int n, M;
int deq[N];

ll getup(int j, int k){
    return dp[k]-dp[j]+sum[k]*sum[k]-sum[j]*sum[j];
}

ll getdown(int j, int k){
    return 2*(sum[k]-sum[j]);
}

void solve(){
    int l = 1, r = 0; deq[++r] = 0;
    for(int i=1; i<=n; i++){
        while(l < r && getup(deq[l], deq[l+1]) <= sum[i]*getdown(deq[l], deq[l+1]))l++;
        int tmp = deq[l];
        dp[i] = dp[tmp]+(sum[i]-sum[tmp])*(sum[i]-sum[tmp])+M;
        while(l < r && getup(deq[r], i)*getdown(deq[r-1], deq[r]) <= getup(deq[r-1], deq[r])*getdown(deq[r], i))r--;
        deq[++r] = i;
    }
}

int  main(){
    while(~scanf("%d%d", &n, &M)){
        mst(dp, 0);
        sum[0] = 0;
        for(int i=1; i<=n; i++)scanf("%I64d", &sum[i]), sum[i] += sum[i-1];
        solve();
        printf("%I64d\n", dp[n]);
    }
    return 0;
}
