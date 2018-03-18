(�����㷨��Tarjan�㷨�����Ӷ�O(n+q)ûѧ)
hdu2586  �ο�����:http://blog.csdn.net/liangzhaoyang1/article/details/52549822
���⣺��ѯ�����������
�����㷨 DFS + ST��  ���Ӷ�O(nlogn+q) Ԥ����nlogn ��ѯO(1)    ����Ȩ
const int N = 4e4+5;
const int M = 25;

int dp[N<<1][M], lg[N];  //�������ǵÿ���2*N����Ϊ���������г���Ϊ2*n-1

struct Edge{
    int to, next, w;
}edge[N<<2];  //��Ҫ�����
int tol, head[N];

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int w){
    edge[tol].to = v; edge[tol].w = w; edge[tol].next = head[u]; head[u] = tol++;
}

int ver[N<<1], R[N<<1], first[N], dis[N], cnt;
//ver:�ڵ��� R����� first������λ�� dis������ cnt:���������г���
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

//��ѯ��Сֵ,�м䲿���ǽ����
int rmq(int l,int r){
    int k=lg[r-l+1];
    int a = dp[l][k], b = dp[r-(1<<k)+1][k]; //��������ver�����е��±�
    return R[a]<R[b]?a:b;
}

int LCA(int u, int v){
    int x = first[u], y = first[v];
    if(x > y)swap(x, y);
    int ret = rmq(x, y);
    return ver[ret];//ά��һ��dp���鱣�������������С���±꣬���ҵ�ʱ�򷵻ؾͿ����ˡ�
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
            addedge(u, v, w); //u , v֮���ȨΪw
            addedge(v, u, w);
            in[v]++;
        }
        int root;
        for(int i=1; i<=n; i++)if(!in[i])root = i;
        dis[root] = 0; cnt = 0;
        dfs(root, -1, 0);
        rmq_init(2*n-1);  //�������Ļ�Ҫע�����������  ������rmq�±겻��Ҫ����
        while(q--){
            int u, v;
            scanf("%d%d", &u, &v);
            int lca = LCA(u, v);
            printf("%d\n", dis[u]+dis[v]-2*dis[lca]);
        }
    }
    return 0;
}

�����ʷ�������������� ���Ӷ�Ԥ����O(nlogn) ��ѯO(logn)
3379ģ����https://www.luogu.org/problem/show?pid=3379#sub
���⣺ֱ����LCA
�ο����ͣ�http://www.cnblogs.com/qilinart2/articles/5931595.html
http://www.cnblogs.com/fuyun-boy/p/6045709.html

const int N = 5e5+5;
int n, m, q;
struct Edge{
    int to, next;
}edge[N<<1];

int head[N], tol;
int top[N];//top[v]��ʾv���ڵ������Ķ��˽ڵ�
int fa[N];//���׽ڵ�
int dep[N];//���
int sz[N];//sz[v]��ʾ��vΪ���������Ľڵ���
int son[N];//�ض���

int a[N];

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(son, -1, sizeof(son));
}

void addedge(int u, int  v){
    edge[tol].to = v;edge[tol].next = head[u]; head[u] = tol++;
}

void dfs1(int u, int pre, int d){//��һ��dfs���fa,deep,sz,son
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

void getpos(int u, int sp){ //�ڶ���dfs���top��p
    top[u] = sp;
    if(son[u] != -1)getpos(son[u], sp);
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v); //�����
    }
}

int LCA(int x, int y){
    //�����������������ȣ����ǾͰ�������һ��
    //���Ǹ����������ȴ�ı��Ǹ���
    for( ; top[x]!=top[y] ; dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
    return dep[x]<dep[y]?x:y; //����ʱҪ������ȱȽ�С����
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
