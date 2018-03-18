const int maxn=100010;//点数的最大值
const int maxm=400010;//边数的最大值,至少两倍
const int inf = 0x3f3f3f3f;
int head[maxn], tol;
int cur[maxn], dis[maxn];
bool vis[maxn];
struct edge{
    int to, next, cap, flow;
}e[maxm];//注意是maxm

void init() { //初始化
    tol = 0;
    memset(head, -1, sizeof(head));
}

//加边，单向图三个参数，双向图四个参数
inline void addedge(int u, int v, int w, int rw = 0){
    e[tol].to=v; e[tol].cap=w;  e[tol].next=head[u]; e[tol].flow=0; head[u]=tol++;
    e[tol].to=u; e[tol].cap=rw; e[tol].next=head[v]; e[tol].flow=0; head[v]=tol++;
}

bool bfs(int s, int t){
    memset(vis, 0, sizeof(vis));
    dis[s] = 0; vis[s] = 1;
    queue<int>q;
    q.push(s);
    while (!q.empty()){
        int x = q.front();
        q.pop();
        for (int i=head[x]; ~i; i=e[i].next){
            if (!vis[e[i].to] && e[i].cap > e[i].flow){
                q.push(e[i].to);
                dis[e[i].to] = dis[x]+1;
                vis[e[i].to] = 1;
            }
        }
    }
    return vis[t];
}

int dfs(int x, int a, int t){
    if (x == t || a == 0) return a;
    int flow = 0, f;
    for (int& i=cur[x]; ~i; i=e[i].next){ //引用不能少
        if (dis[x]+1 == dis[e[i].to] && ( (f = dfs(e[i].to, min(a, e[i].cap-e[i].flow), t)) > 0) ){
            flow += f;
            e[i].flow += f;
            e[i^1].flow -= f;
            a -= f;
            if(a == 0)break;
        }
    }
    return flow;
}
//源点,汇点,点的总数N,点的下标从0~N-1
int dinic(int s, int t, int N){
    int flow = 0;
    while(bfs(s, t)){
        memcpy(cur, head, sizeof(head));
        flow += dfs(s, inf, t);
    }
    return flow;
}
