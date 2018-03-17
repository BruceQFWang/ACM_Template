struct Edge{
    int to, next;
}edge[N<<2];
int head[N], tol;

void init(){
    memset(head, -1, sizeof(head));
    tol = 0;
}

void addedge(int u, int v){
    edge[tol].to = v; edge[tol].next = head[u]; head[u] = tol++;
}

int dp[N], sz[N]; //dp[i]i���ӽڵ���sz[v]����ֵ   sz[i]i��size�����ϱ��������Ľڵ�����
int n;

void dfs(int u, int fa){
    dp[u] = 0; sz[u] = 1;
    for(int i=head[u]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(v == fa)continue;
        dfs(v, u);
        sz[u] += sz[v];
        dp[u] = max(dp[u], sz[v]);
    }
    dp[u] = max(dp[u], n-sz[u]);
}

int  main(){
    int T;
    scanf("%d",  &T);
    while(T--){
        scanf("%d", &n);
        init();
        for(int i=1; i<n; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        dfs(1, -1);
        int pos = 1, mx = dp[1];
        for(int i=2; i<=n; i++){
            if(mx > dp[i]){
                mx = dp[i];
                pos = i;
            }
        }
        printf("%d %d\n", pos, mx);
//������Ϊ�������ģ�����ж��֣����С�ģ� �ٵ�������������Ĵ�С
    }
    return 0;
}
