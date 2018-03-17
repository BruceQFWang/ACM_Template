题意：有n个商品，每个商品都有价格ci，优惠券di,除了第一个商品，其他的商品用优惠券必须买之前的某个商品，求用b元买到最大的商品数
思路：很明显是树上DP，可以根据优惠券的约束关系构造成一颗树,考虑树形DP

定义：dp[子树根] [选的物品数] [用不用优惠券] 的最小代价
转移方程：
dp[u][j][1]=min(dp[u][j-k][1],min(dp[v][k][1],dp[v][k][0]))
dp[u][j][0]=min(dp[u][j-k][0],dp[v][k][0]))

显然,直接DP需要O(n3)
考虑优化,维护size[u]=当前u为根的子树已经发现的节点个数
首先对任意u,size[u]=1,求出儿子v后,背包问题搞一下,然后size[u]+=size[v],继续求解其他儿子…
这样复杂度其实只有O(n2),因为子树u内任意2个点对,只同时求了一次
注意如果size[u]+=size[v],再对u,v求背包,复杂度就变为O(n3)了,因为子树v也与自身求了一次背包
代码：
const int N = 5e3+5;

int n, b, c[N], d[N], sz[N];
ll dp[N][N][2];
vector<int>E[N];

void dfs(int u){
    sz[u] = 1;
    dp[u][0][0] = 0;  //不选不花钱
    dp[u][1][0] = c[u];  //不用就自己
    dp[u][1][1] = c[u]-d[u];  //用了就减去
    for(int i=0; i<E[u].size(); i++){
        int v = E[u][i];
        dfs(v);
        for(int j=sz[u]; j>=0; j--)
            for(int k=sz[v]; k>=0; k--){
                dp[u][j+k][0] = min(dp[u][j+k][0], dp[u][j][0]+dp[v][k][0]);
                dp[u][j+k][1] = min3(dp[u][j+k][1], dp[u][j][1]+dp[v][k][1], dp[u][j][1]+dp[v][k][0]);
            }
        sz[u] += sz[v];
    }
}


int  main(){
    mst(dp, inf);
    scanf("%d %d", &n, &b);
    for(int i=1; i<=n; i++){
        int pre;
        scanf("%d %d", &c[i], &d[i]);
        if(i >= 2){
            scanf("%d", &pre);
            E[pre].pb(i);
        }
    }
    dfs(1);
    for(int i=n; i>=0; i--){
        if(dp[1][i][0] <= 1LL*b || dp[1][i][1] <= 1LL*b){
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
