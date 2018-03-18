定义：
对于有向图上的2个点a,b，若存在一条从a到b的路径，也存在一条从b到a的路径，那么称a,b是强连通的。
对于有向图上的一个子图，若子图内任意点对(a,b)都满足强连通，则称该子图为强连通子图。
非强连通图有向图的极大强连通子图，称为强连通分量。
单独的点也可以是强连通分量

// 每个顶点都被访问了一次，且只进出了一次堆栈，每条边也只被访问了一次,复杂度O(n+m)
const int maxn = 20010; //点数
const int maxm = 100010; //边数
struct Edge{
    int to, next;
}edge[maxm];
int head[maxn], tol;
int dfn[maxn];//DFN(u)为节点u搜索的次序编号(时间戳)
int low[maxn];//通过反向边能到达的最小dfn
int stk[maxn], belong[maxn];//belong数组的值是1~scc
int idx, top;
int scc;//强连通分量的个数  Strongly connected component
bool instk[maxn];
int num[maxn];//各个强连通分量包含点的个数，数组编号1~scc
//num数组不一定需要，结合实际情况

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn)); //DFS时的序号，如果!=0说明已经被访问过了
    memset(low, 0, sizeof(low));
    memset(num, 0, sizeof(num));
    memset(instk, 0, sizeof(instk));
    memset(belong, 0, sizeof(belong));
    idx = scc = top = 0;
}

void addedge(int u,int v){
    edge[tol].to = v; edge[tol].next = head[u]; head[u] = tol++;
}

void Tarjan(int u){
    int v;
    low[u] = dfn[u] = ++idx;//初始化dfn与low
    stk[top++] = u;  //将节点u压入栈中
    instk[u] = 1;
    for(int i=head[u]; i!=-1; i=edge[i].next){ //枚举每一条边
        v = edge[i].to;
        if(!dfn[v]){  //节点v未被访问
            Tarjan(v); //继续向下找
            low[u] = min(low[u], low[v]);
        }
        else if(instk[v]) //节点v已访问，则(u,v)为回边
            low[u] = min(low[u], dfn[v]);
    }

    if(low[u] == dfn[u]){ //如果节点u是强连通分量的根
        scc++;
        do{
            v = stk[--top]; //将v退栈直到为该强连通分量的根
            instk[v] = 0;
            belong[v] = scc;
            num[scc]++;
        }
        while(v != u);
    }
}

//因为有些点可能是1到达不了的，这样Tarjan(1)就不能得到所有的强连通分量，所以需要for循环尝试每一个点
/*1.调用：
for(int i=1; i<=n; i++)
            if(!dfn[i])Tarjan(i);
*/

2.重新建图
//例题hihocoder 1185  求有向图从点1开始走得到的最大点权和
//复杂度O(n+m)
const int maxn = 10010; //点数
const int maxm = 100010; //边数
struct Edge{
    int to, next;
}edge[maxm], redge[maxm];
int head[maxn], tol;
int dfn[maxn];//DFN(u)为节点u搜索的次序编号(时间戳)
int low[maxn];//Low(u)为u或u的子树能够追溯到的最早的栈中节点的次序号
int stk[maxn], belong[maxn];//belong数组的值是1~scc
int idx, top;
int scc;//强连通分量的个数  Strongly connected component
bool instk[maxn];
int num[maxn];//各个强连通分量包含点的个数，数组编号1~scc
//num数组不一定需要，结合实际情况

int rhead[maxn], rtol;//重新建图

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn)); //DFS时的序号，如果!=0说明已经被访问过了
    memset(low, 0, sizeof(low));
    memset(num, 0, sizeof(num));
    memset(instk, 0, sizeof(instk));
    memset(belong, 0, sizeof(belong));
    idx = scc = top = 0;
    rtol = 0;//重新建图
    memset(rhead, -1, sizeof(rhead));
}

void addedge(int u,int v){
    edge[tol].to = v; edge[tol].next = head[u]; head[u] = tol++;
}

void addredge(int u,int v){//重新建图
    redge[rtol].to = v; redge[rtol].next = rhead[u]; rhead[u] = rtol++;
}

void Tarjan(int u){
    int v;
    low[u] = dfn[u] = ++idx;//初始化dfn与low
    stk[top++] = u;  //将节点u压入栈中
    instk[u] = 1;
    for(int i=head[u]; i!=-1; i=edge[i].next){ //枚举每一条边
        v = edge[i].to;
        if(!dfn[v]){  //节点v未被访问
            Tarjan(v); //继续向下找
            low[u] = min(low[u], low[v]);
        }
        else if(instk[v]) //节点v已访问，则(u,v)为回边
            low[u] = min(low[u], dfn[v]);
    }

    if(low[u] == dfn[u]){ //如果节点u是强连通分量的根
        scc++;
        do{
            v = stk[--top]; //将v退栈直到为该强连通分量的根
            instk[v] = 0;
            belong[v] = scc;
            num[scc]++;
        }
        while(v != u);
    }
}

int w[N], block[N], ans;

void dfs(int u, int sum){
    sum += block[u];
    if(sum > ans)ans = sum;
    for(int i=rhead[u]; i!=-1; i=redge[i].next){
        int v = redge[i].to;
        dfs(v, sum);
    }
}

int  main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        init();
        ans = 0;
        mst(block, 0);

        for(int i=1; i<=n; i++)scanf("%d", &w[i]);
        while(m--){
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        for(int i=1; i<=n; i++)
            if(!dfn[i])Tarjan(i);

        for(int i=1; i<=n; i++)block[belong[i]] += w[i];

        for(int i=1; i<=n; i++){//重新建图
            for(int j=head[i]; j!=-1; j=edge[j].next){
                int v = edge[j].to;
                if(belong[i] != belong[v]){
                    addredge(belong[i], belong[v]);
                }
            }
        }
        dfs(belong[1], 0);
        printf("%d\n", ans);
    }
    return 0;
}
