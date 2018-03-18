poj1741 Tree
题意：求树上距离小于等于K的点对有多少个。
思路：对于一棵有根树， 树中满足要求的一个数对所对应的一条路径，必然是以下两种情况之一：
1、经过根节点
2、不经过根节点，也就是说在根节点的一棵子树中
对于情况2，可以递归求解然后就变成了情况1，下面主要来考虑情况1:
从u到v的路径必然经过了顶点s，只要先求出每个顶点到s的距离再做统计即可。（注意在第一种情况中减去第二种重复计算的部分）
当树退化成链的形式时，递归的深度则退化为O(n)，所以选择每次都找到树的重心作为分隔顶点。重心就是删掉此结点后得到的最大子树的顶点数最少的顶点，删除重心后得到的所有子树顶点数必然不超过n/2。
查找重心的时候，假设根为v，先在v的子树中找到一个顶点，使删除该顶点后的最大子树的顶点数最少，然后考虑删除v的情况，获得最大子树的顶点数。
两者选择最小的一个，此时选中的顶点即为重心。
递归的每一层都做了排序O(nlogn)，递归深度O(logn)，总体时间复杂度O(nlog2n)。
struct Edge{
    int to, next, w;
}edge[N<<1];
int head[N], tol;
void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w){
    edge[tol].to = v; edge[tol].next = head[u]; edge[tol].w = w; head[u] = tol++;
}
//f[i]i的子节点中sz[v]最大的值   sz[i]i的size（算上本身子树的节点数） d[i]深度 nsize子树大小
int n, K, root, ans, nsize, sz[N], f[N], d[N];
vector<int>dis; //某个子树的所有距离
bool done[N];//节点i之前作为根用过了

void getroot(int u, int fa){ //获取重心
    f[u] = 0; sz[u] = 1;
    for(int i=head[u]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(v == fa || done[v])continue;
        getroot(v, u);
        sz[u] += sz[v];
        f[u] = max(f[u], sz[v]);
    }
    f[u] = max(f[u], nsize-sz[u]);
    if(f[u] < f[root])root = u;
}

void getdis(int u, int fa){//获取子树所有节点与根的距离
    dis.pb(d[u]);
    sz[u] = 1;
    for(int i=head[u]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(v == fa || done[v])continue;
        d[v] = d[u]+edge[i].w;
        getdis(v, u);
        sz[u] += sz[v];
    }
}

int calc(int x, int w){//计算当前以重心x的子树下，所有情况的答案 d[x]初始深度为w
    dis.clear(); d[x] = w;
    getdis(x, 0);
    sort(dis.begin(), dis.end());
    int ret = 0;
    for(int l=0, r=dis.size()-1; l<r; )
        if(dis[l]+dis[r] <= K)ret += r-l++;
        else r--;
    return ret;
}

void solve(int x){//以x为重心进行计算
    ans += calc(x, 0);
    done[x] = 1;
    for(int i=head[x]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(done[v])continue;
        ans -= calc(v, edge[i].w);
        f[0] = nsize = sz[v];
        getroot(v, root=0);
        solve(root);
    }
}

int  main(){
    while(~scanf("%d%d", &n, &K)){
        if(!n && !K)break;
        init();
        memset(done, 0, sizeof(done));
        for(int i=1; i<n; i++){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        f[0] = nsize = n;
        getroot(1, root = 0);
        ans = 0;
        solve(root);
        printf("%d\n", ans);
    }
    return 0;
}
