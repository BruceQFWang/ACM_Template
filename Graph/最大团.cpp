1）最大团点的数量=补图中最大独立集点的数量
（对原图建一个反图，然后对反图做一个最大团的求解，最大团保证了是反图中的最大完全子集，任何两个元素之间都有边相连，反应在原图中则是任意两两之间不存在边，也就是两两不相邻）
2）图的染色问题中，最少需要的颜色的数量=最大团点的数量
（通俗理解最大团就是最大完全子图）

1.搜索模板 数据一般是n=100左右
struct node{
    static const int N = 60; //可修改

    bool G[N][N]; //初始化
    int n, Max[N], Alt[N][N], ans;  // 点标号从0开始

    bool dfs(int cur, int tol){
        if(cur == 0){
            if(tol>ans){  // 用一个更大的极大团替代原有的极大团
                ans = tol;
                return 1;
            }
            return 0;
        }
        for(int i=0; i<cur; i++){
            if(cur-i+tol <= ans)return 0;
            int u = Alt[tol][i];
            if(Max[u]+tol <= ans)return 0;
            int nxt = 0;
            for(int j=i+1; j<cur; j++)
                if(G[u][Alt[tol][j]])Alt[tol+1][nxt++] = Alt[tol][j];
            if(dfs(nxt, tol+1)) return 1;
        }
        return 0;
    }

    int max_clique(){
        ans = 0;
        mst(Max, 0);
        for(int i=n-1; i>=0; i--){ // 先找一个点,把与它相连的点加进来，这些点可能构成最大团，然后dfs判断出一个临时极大团
            int cur = 0;
            for(int j=i+1; j<n; j++)if(G[i][j])Alt[1][cur++] = j;
            dfs(cur, 1);
            Max[i] = ans;
        }
        return ans;
    }

};


2.最大团随机贪心模板   数据一般n=500
//loj 526
const int N = 505;

int n,g[N][N],a[N],del[N],ans,fin[N];
void go(){
    int i, j, k;
    for(i=0;i<n;i++)del[i]=0;
    for(k=i=0;i<n;i++)if(!del[i])for(k++,j=i+1;j<n;j++)if(!g[a[i]][a[j]])del[j]=1;
    if(k>ans)for(ans=k,i=j=0;i<n;i++)if(!del[i])fin[j++]=a[i];
}

ll val[N];
int  main(){
    scanf("%d", &n);  ans = 0;
    for(int i=0; i<n; i++)a[i] = i; //初始化
    for(int i=0; i<n; i++)scanf("%lld", &val[i]);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j)continue;
            if(gcd(val[i], val[j]) != 1 || gcd(val[i]+1, val[j]+1) != 1)g[i][j] = 1; //建边
        }
    }
    for(int turn=100; turn--; go())for(int i=0; i<n; i++)swap(a[i], a[rand()%n]);  //随机交换
    int i;
    for(printf("%d\n",ans),i=0; i<ans; i++)printf("%d ",fin[i]+1); //输出最大团数量及一组解
    return 0;
}
