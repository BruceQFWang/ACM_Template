 树链，就是树上的路径。剖分，就是把路径分类为重链和轻链。
个人认为，其实树链剖分并不是一个复杂的算法或者数据结构，只是能把一棵树拆成链来处理而已，换一种说法，树链剖分只是xxx数据结构/算法在树上的推广，或者说，树链剖分只是把树hash到了几段连续的区间上。
因为这东西本身没有功能，具体功能都是靠具体数据结构实现的，所以复杂度就是O(logn * ??)。如果套上了线段树，就是 O(log^2 n)。如果套上了树套树，那就是O(log^3 n)。如果你用树链剖分和树套树写区间第k大，那就是O(log^4 n)。
另外，树链剖分具体实现的时候是给边重新编号还是给点重新编号，这得根据不同的题目而定，实现的时候要注意顶端那个编号能不能取。
对了，这东西可以顺便求LCA。比如说基于点的剖分，就是剖分到两个点都到同一条重链的时候，比较上端的那个点。

注意点：
1.修改的是边权还是点权
2.不同的操作套不同的线段树或者树状数组

题意：给两个操作，一个是把第i条边权值修改成ti，另一个是查询a到b之间最大的边权值
//基于边权，修改单条边权，查询路径边权最大值（SPOJ QTREE   树链剖分+线段树）
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
const int inf = 0x3f3f3f3f;
const int N = 10000+5;

struct Edge{
    int to, next;
}edge[N<<1];

int head[N], tol;
int top[N];//top[v]表示v所在的重链的顶端节点
int fa[N];//父亲节点
int dep[N];//深度
int sz[N];//sz[v]表示以v为根的子树的节点数
int p[N];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[N];//和p数组相反  已知v在线段树中位置,其父亲节点是u
int son[N];//重儿子
int pos; //pos为线段树或者树状数组的大小

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
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
    p[u] = ++pos;
    fp[p[u]] = u;
    if(son[u] != -1)getpos(son[u], sp);
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v); //轻儿子
    }
}

//线段树
int Max[N<<2];
void PushUp(int rt){
    Max[rt]=max(Max[rt<<1],Max[rt<<1|1]);
}

void build(int l,int r,int rt){
    if(l==r)return ;
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    //PushUp(rt); //Max都是0不需要PushUp
}

void update(int p,int re,int l,int r,int rt){  //单点替换
    if(l==r){
        Max[rt]=re;
        return ;
    }
    int m=(l+r)>>1;
    if(p<=m)update(p, re, lson);
    else update(p, re, rson);
    PushUp(rt);
}

int query(int L,int R,int l,int r,int rt){ //区间最大
    if(L<=l && r<=R){
        return Max[rt];
    }
    int m=(l+r)>>1;
    int ret=0;
    if(L<=m)ret=max(ret, query(L, R, lson));
    if(R>m)ret=max(ret,query(L, R, rson));
    return ret;
}

int solve(int u, int v){ //查询u->v边的最大值
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2){
        if(dep[f1] < dep[f2]){  //对深度大的操作
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(p[f1], p[u], 1, pos, 1));
        u = fa[f1]; f1 = top[u];
    }//下面点权和边权处理有些不同
    if(u == v)return tmp;   //u等于v就没边了
    if(dep[u] > dep[v])swap(u, v);  //最后一次操作
    return max(tmp, query(p[son[u]], p[v], 1, pos, 1));
}

int e[N][3];
int  main(){
    int T;
    scanf("%d", &T);
    int n;
    while(T--){
        init();
        memset(Max, 0, sizeof(Max));
        scanf("%d", &n);
        for(int i=1; i<n; i++){
            for(int j=0; j<3; j++)scanf("%d", &e[i][j]);
            addedge(e[i][0], e[i][1]);
            addedge(e[i][1], e[i][0]);
        }
        dfs1(1, -1, 0);  //把fa、dep、sz、son求出来
        getpos(1, 1); // 求出top、p、pos (其中pos可以被看成线段树的大小，一般都等于n)
        build(1, pos, 1);
        for(int i=1; i<n; i++){
            if(dep[e[i][0]] > dep[e[i][1]])
                swap(e[i][0], e[i][1]);
            update(p[e[i][1]], e[i][2], 1, pos, 1); //用深度大的来更新边权，这是基于边权的方法
        }
        char op[10];
        int u, v;
        while(~scanf("%s", op)){
            if(op[0] == 'D')break;
            scanf("%d%d", &u, &v);
            if(op[0] == 'Q')printf("%d\n", solve(u, v));
            else update(p[e[u][1]], v, 1, pos, 1);
        }
    }
    return 0;
}


HDU 3966 Aragorn's Story （树链剖分+树状数组）
题意：
给一棵树，并给定各个点权的值，然后有3种操作：
I C1 C2 K: 把C1与C2的路径上的所有点权值加上K
D C1 C2 K：把C1与C2的路径上的所有点权值减去K
Q C：查询节点编号为C的权值
//基于点权，查询单点值，修改路径的上的点权
int n, m, q;
struct Edge{
    int to, next;
}edge[N<<1];

int head[N], tol;
int top[N];//top[v]表示v所在的重链的顶端节点
int fa[N];//父亲节点
int dep[N];//深度
int sz[N];//sz[v]表示以v为根的子树的节点数
int p[N];//p[v]表示v与其父亲节点的连边在线段树中的位置
int fp[N];//和p数组相反  已知v在线段树中位置,其父亲节点是u
int son[N];//重儿子
int pos;

int a[N];

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
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
    p[u] = ++pos;  //树状数组编号从1开始
    fp[p[u]] = u;
    if(son[u] != -1)getpos(son[u], sp);
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v); //轻儿子
    }
}

struct BIT{
    int n;
    int c[N];

    void init(int _n){
        n = _n;
        for(int i=1; i<=n; i++)c[i] = 0;
        mst(c, 0);
    }

    void update(int p, int x){
        for(int i=p; i<=n; i+=i&-i)c[i] += x;
    }

    int query(int p){
        int ret = 0;
        for(int i=p; i>0; i-=i&-i)ret += c[i];
        return ret;
    }

}bit;

void solve(int u, int v, int val){
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2){
        if(dep[f1] < dep[f2]){
            swap(f1, f2);
            swap(u, v);
        }
        bit.update(p[f1], val);
        bit.update(p[u]+1, -val);
        u = fa[f1];  f1 = top[u];
    }  //下面点权和边权处理有些不同
    if(u == v){
        bit.update(p[u], val);
        bit.update(p[u]+1, -val);
        return ;
    }
    if(dep[u] > dep[v])swap(u, v);
    bit.update(p[u], val);
    bit.update(p[v]+1, -val);
}

int  main(){
    while(~scanf("%d%d%d", &n, &m, &q)){
        init();
        for(int i=1; i<=n; i++)scanf("%d", &a[i]);
        for(int i=1; i<=m; i++){
            int  u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        dfs1(1, -1, 0);
        getpos(1, 1);
        bit.init(pos);
        for(int i=1; i<=n; i++){
            bit.update(p[i], a[i]);
            bit.update(p[i]+1, -a[i]);
        }
        while(q--){
            char op[10];
            scanf("%s", op);
            if(op[0] == 'Q'){
                int C;
                scanf("%d", &C);
                printf("%d\n", bit.query(p[C]));
            }
            else{
                int C1, C2, K;
                scanf("%d%d%d", &C1, &C2, &K);
                if(op[0] == 'D')K = -K;
                solve(C1, C2, K);
            }
        }
    }
    return 0;
}
