01背包打印字典序最小的解
//n<=100 背包容量<=1000
const int N = 1e3+5;

bool path[105][N];
int f[N], cost[N], score[N];
vector<int>ans;
int main(){
    int T;
    scanf("%d", &T);
    int cas = 1;
    for(int kase=1; kase<=T; kase++){
        int B, n;
        scanf("%d%d", &B, &n);
        ans.clear();
        for(int i = 1; i <= n; i++)scanf("%d%d", &score[i], &cost[i]);
        mst(f, 0);
        mst(path, 0);
        for(int i=1; i<=n; i++){
            for(int j=B; j>=cost[i]; j--) {
                if(f[j-cost[i]]+score[i] > f[j]) {
                    path[i][j] = 1;
                    f[j] = f[j-cost[i]]+score[i];
                }
            }
        }
        int sum = 0, j = B;
        for(int i=n; i>=1; i--){
            if(path[i][j]){
                ans.push_back(i);
                j -= cost[i];
                sum += cost[i];
            }
        }
        printf("Case #%d:\n%d %d\n", kase, f[B], sum);
        reverse(ans.begin(), ans.end());
        int sz = ans.size();
        for(int i=0; i<sz; i++) {
            printf("%d%c", ans[i], i == sz-1 ? '\n':' ');
        }
    }
    return 0;
}


求01背包最多容纳的物品数和最多容纳物品数对应的方案数
类似于求背包第k大的方案数
法一：
用dp[j][k]表示总量为j时物品数为k的方案数，复杂度O(n^2*W)
代码：
const int N=50;
int n, m, w[N], dp[505][N];

int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)scanf("%d",&w[i]);
        sort(w+1, w+n+1);
        int kk=-1, sum=0;
        for(int i=1;i<=n;i++){  //最多容纳物品数上限
            sum+=w[i];
            if(sum>m){
                kk=i-1; break;
            }
        }
        if(kk==0){
            printf("Sorry, you can't buy anything.\n");
            continue;
        }
        kk = kk==-1?n:kk;
        dp[0][0]=1;
        for( int i=1; i<=n; i++)
            for( int j=m; j>=w[i]; j--)
                for( int k=kk; k>=1; k--)
                    dp[j][k]+=dp[j-w[i]][k-1];
        sum=0;
        for( int i=0;i<=m;i++)sum+=dp[i][kk];
        printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",sum,kk);
    }
    return 0;
}

法二：
用了一个数组dp[v][2] ，dp[v][0] 储存原本要记录的 容纳物品数 ，而 dp[v][1] 则记录方案数目。记住需要初始化，把所有 dp[i][1] 都设置成1。  复杂度O(n*W)
const int N = 1e5+5;
int dp[505][2], n, m, w[35];

int  main(){
    int t; scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        for(int i=1; i<=n; i++)scanf("%d", &w[i]);
        mst(dp, 0);
        for(int i=0; i<=m; i++)dp[i][1] = 1;
        for(int i=1; i<=n; i++){
            for(int j=m; j>=w[i]; j--){
                if(dp[j][0] == dp[j-w[i]][0]+1){
                    dp[j][1] = dp[j][1]+dp[j-w[i]][1];
                }
                else if(dp[j][0] < dp[j-w[i]][0]+1){
                    dp[j][0] = dp[j-w[i]][0]+1;
                    dp[j][1] = dp[j-w[i]][1];
                }
            }
        }
        if(dp[m][0]){
            printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n", dp[m][1], dp[m][0]);;
        }
        else puts("Sorry, you can't buy anything.");
    }
    return 0;
}
