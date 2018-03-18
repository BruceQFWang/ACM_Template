定义1：
割点：一个结点称为割点（或者割顶）当且仅当去掉该节点极其相关的边之后的子图不连通。
桥：一条边称为桥（或者割边）当且仅当去掉该边之后的子图不连通。
定义2：
割点：在一个无向图中，如果删去一个点，这个图的连通度增加了，删去的这个点
桥：如果删掉一条边，这个图的连通度增加了，删掉的这条边
参考博客：http://blog.csdn.net/fuyukai/article/details/51039788 （下面代码也有注释）
const int maxn = 10005;
const int maxm = 100005;
struct Edge{
    int to, next;
    bool cut;//是否为桥的标记
}edge[maxm];
int head[maxn], tol;
int low[maxn], dfn[maxn], stk[maxn];
int idx, top;
bool instk[maxn];
bool cut[maxn];
int add_block[maxn];//删除一个点后增加的连通块
int bridge;

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instk, 0, sizeof(instk));
    memset(cut, 0, sizeof(cut));
    memset(add_block, 0, sizeof(add_block));
    idx = top = bridge = 0;
}

void addedge(int u, int v){
    edge[tol].to = v; edge[tol].next = head[u]; edge[tol].cut = 0;
    head[u] = tol++;
}

void Tarjan(int u, int fa){
    int v;
    low[u] = dfn[u] = ++idx;
    stk[top++] = u;
    instk[u] = 1;
    int son = 0;
    for(int i=head[u]; i!=-1; i=edge[i].next){
        v = edge[i].to;
        if(v == fa)continue;
        if(!dfn[v]){
            son++;
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            //桥
            //一条无向边(u,v)是桥，当且仅当(u,v)为树枝边，且满足DFS(u)<Low(v)。
            if(low[v] > dfn[u]){  //判断桥的时候这个板子不能处理重边
                bridge++;
                edge[i].cut = 1;
                edge[i^1].cut = 1;
            }
            //割点
            //一个顶点u是割点，当且仅当满足(1)或(2) (1) u为树根，且u有多于一个子树。
            //(2) u不为树根，且满足存在(u,v)为树枝边(或称父子边，
            //即u为v在搜索树中的父亲)，使得DFS(u)<=Low(v)
            if(u != fa && low[v] >= dfn[u]){//不是树根
                cut[u] = 1;
                add_block[u]++;
            }
        }
        else if(low[u] > dfn[v])low[u] = dfn[v];
    }
    //树根，分支数大于1
    if(u == fa && son > 1)cut[u] = 1;
    if(u == fa)add_block[u] = son-1;
    instk[u] = 0;
    top--;
}

/*1.调用：
for(int i=1; i<=n; i++)
            if(!dfn[i])Tarjan(i, -1);
addedge添加双向边,一定要一起加，要不然i和i^1就不是双向边了
可能有重边，所以Tarjan函数里面要加father
*/
/*2.割点的个数for一遍cut数组就算出来了，桥的个数就是看bridge
*/

//判断桥可以处理重边，其实pre_cnt部分也可以加到上面的代码里，因为判不判重边不影响割点判断
const int maxn = 400005;
const int maxm = 4000005;
struct Edge{
    int to, next;
    bool cut;//是否为桥的标记
}edge[maxm];
int head[maxn], tol;
int low[maxn], dfn[maxn], stk[maxn];
int idx, top;
bool instk[maxn];
int belong[maxn];
int bridge, scc;

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instk, 0, sizeof(instk));
    memset(belong, 0, sizeof(belong));
    idx = top = bridge = scc = 0;
}

void addedge(int u, int v){
    edge[tol].to = v; edge[tol].next = head[u]; edge[tol].cut = 0;
    head[u] = tol++;
}

void Tarjan(int u, int pre){
    int v;
    low[u] = dfn[u] = ++idx;
    stk[top++] = u;
    instk[u] = 1;
    int son = 0;
    int pre_cnt = 0;//处理重边，如果不需要可以去掉
    for(int i=head[u]; i!=-1; i=edge[i].next){
        v = edge[i].to;
        if(v == pre && !pre_cnt){ pre_cnt++; continue;}
        if(!dfn[v]){
            son++;
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            //桥
            //一条无向边(u,v)是桥，当且仅当(u,v)为树枝边，且满足DFS(u)<Low(v)。
            if(low[v] > dfn[u]){
                bridge++;
                edge[i].cut = 1;
                edge[i^1].cut = 1;
            }
        }
        else if(low[u] > dfn[v])low[u] = dfn[v];
    }
    if(low[u] == dfn[u]){ //如果节点u是强连通分量的根
        scc++;
        do{
            v = stk[--top]; //将v退栈直到为该强连通分量的根
            instk[v] = 0;
            belong[v] = scc;
        }
        while(v != u);
    }
}
