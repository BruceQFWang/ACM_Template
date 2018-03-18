hdu2586           
题意：查询树上两点距离
在线算法 DFS + ST表  复杂度O(nlogn+q) 预处理nlogn 查询O(1)    带边权
const int N = 4e4+5;
const int M = 25;

int dp[N<<1][M], lg[N];  //这个数组记得开到2*N，因为遍历后序列长度为2*n-1

struct Edge{
    int to, next, w;
}edge[N<<2];  //边要开大点
int tol, head[N];

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int w){
    edge[tol].to = v; edge[tol].w = w; edge[tol].next = head[u]; head[u] = tol++;
}

int ver[N<<1], R[N<<1], first[N], dis[N], cnt;
//ver:节点编号 R：深度 first：点编号位置 dis：距离 cnt:遍历后序列长度
void dfs(int u, int pre, int dep){
    ver[++cnt] = u; first[u] = cnt; R[cnt] = dep;
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v == pre)continue;
        int w = edge[i].w;
        dis[v] = dis[u]+w;
        dfs(v, u, dep+1);
        ver[++cnt] = u;
        R[cnt] = dep;
    }
}

int rmq_init(int n){
    for(int i=2; i<=n; i++) if(i & (i-1)) lg[i] = lg[i-1]; else lg[i] = lg[i-1]+1;
    for(int i=1; i<=n; i++)dp[i][0] = i;
    for(int j=1; (1<<j)<=n; j++)
        for(int i=1; i+(1<<j)-1<=n; i++){
            int a = dp[i][j-1] , b = dp[i+(1<<(j-1))][j-1];
            dp[i][j] = R[a]<R[b]?a:b;
        }
}

//查询最小值,中间部分是交叉的
int rmq(int l,int r){
    int k=lg[r-l+1];
    int a = dp[l][k], b = dp[r-(1<<k)+1][k]; //返回其在ver数组中的下标
    return R[a]<R[b]?a:b;
}

int LCA(int u, int v){
    int x = first[u], y = first[v];
    if(x > y)swap(x, y);
    int ret = rmq(x, y);
    return ver[ret];//维护一个dp数组保存其区间深度最小的下标，查找的时候返回就可以了。
}

int in[N];
int  main(){
    int T;
    scanf("%d", &T);
    while(T--){
        init();
        mst(in, 0);
        int n, q;
        scanf("%d%d", &n, &q);
        for(int i=1; i<n; i++){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w); //u , v之间边权为w
            addedge(v, u, w);
            in[v]++;
        }
        int root;
        for(int i=1; i<=n; i++)if(!in[i])root = i;
        dis[root] = 0; cnt = 0;
        dfs(root, -1, 0);
        rmq_init(2*n-1);  //建立虚点的话要注意点数的增加  其他的rmq下标不需要考虑
        while(q--){
            int u, v;
            scanf("%d%d", &u, &v);
            int lca = LCA(u, v);
            printf("%d\n", dis[u]+dis[v]-2*dis[lca]);
        }
    }
    return 0;
}

树链剖分求最近公共祖先 复杂度预处理O(nlogn) 查询O(logn)
3379模板题
题意：直接求LCA

const int N = 5e5+5;
int n, m, q;
struct Edge{
    int to, next;
}edge[N<<1];

int head[N], tol;
int top[N];//top[v]表示v所在的重链的顶端节点
int fa[N];//父亲节点
int dep[N];//深度
int sz[N];//sz[v]表示以v为根的子树的节点数
int son[N];//重儿子

int a[N];

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(son, -1, sizeof(son));
}

void addedge(int u, int  v){
    edge[tol].to = v;edge[tol].next = head[u]; head[u] = tol++;
}

void dfs1(int u, int pre, int d){//第一遍dfs求出fa,deep,sz,son
    dep[u] = d;
    fa[u] = pre;
    sz[u] = 1;
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != pre){
            dfs1(v, u, d+1);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[v] > sz[son[u]])
                son[u] = v;
        }
    }
}

void getpos(int u, int sp){ //第二遍dfs求出top和p
    top[u] = sp;
    if(son[u] != -1)getpos(son[u], sp);
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v); //轻儿子
    }
}

int LCA(int x, int y){
    //如果两个的链顶不相等，我们就把他们往一起靠
    //看那个点的链顶深度大改变那个点
    for( ; top[x]!=top[y] ; dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
    return dep[x]<dep[y]?x:y; //返回时要返回深度比较小的数
}

int  main(){
    init();
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for(int i=1; i<n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(s, -1, 0);
    getpos(s, s);
    while(m--){
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", LCA(x, y));
    }
    return 0;
}
