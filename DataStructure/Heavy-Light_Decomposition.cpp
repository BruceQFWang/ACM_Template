 �������������ϵ�·�����ʷ֣����ǰ�·������Ϊ������������
������Ϊ����ʵ�����ʷֲ�����һ�����ӵ��㷨�������ݽṹ��ֻ���ܰ�һ�����������������ѣ���һ��˵���������ʷ�ֻ��xxx���ݽṹ/�㷨�����ϵ��ƹ㣬����˵�������ʷ�ֻ�ǰ���hash���˼��������������ϡ�
��Ϊ�ⶫ������û�й��ܣ����幦�ܶ��ǿ��������ݽṹʵ�ֵģ����Ը��ӶȾ���O(logn * ??)������������߶��������� O(log^2 n)��������������������Ǿ���O(log^3 n)��������������ʷֺ�������д�����k���Ǿ���O(log^4 n)��
���⣬�����ʷ־���ʵ�ֵ�ʱ���Ǹ������±�Ż��Ǹ������±�ţ���ø��ݲ�ͬ����Ŀ������ʵ�ֵ�ʱ��Ҫע�ⶥ���Ǹ�����ܲ���ȡ��
���ˣ��ⶫ������˳����LCA������˵���ڵ���ʷ֣������ʷֵ������㶼��ͬһ��������ʱ�򣬱Ƚ��϶˵��Ǹ��㡣

ע��㣺
1.�޸ĵ��Ǳ�Ȩ���ǵ�Ȩ
2.��ͬ�Ĳ����ײ�ͬ���߶���������״����

���⣺������������һ���ǰѵ�i����Ȩֵ�޸ĳ�ti����һ���ǲ�ѯa��b֮�����ı�Ȩֵ
//���ڱ�Ȩ���޸ĵ�����Ȩ����ѯ·����Ȩ���ֵ��SPOJ QTREE   �����ʷ�+�߶�����
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
const int inf = 0x3f3f3f3f;
const int N = 10000+5;

struct Edge{
    int to, next;
}edge[N<<1];

int head[N], tol;
int top[N];//top[v]��ʾv���ڵ������Ķ��˽ڵ�
int fa[N];//���׽ڵ�
int dep[N];//���
int sz[N];//sz[v]��ʾ��vΪ���������Ľڵ���
int p[N];//p[v]��ʾv���丸�׽ڵ���������߶����е�λ��
int fp[N];//��p�����෴  ��֪v���߶�����λ��,�丸�׽ڵ���u
int son[N];//�ض���
int pos; //posΪ�߶���������״����Ĵ�С

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
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
    p[u] = ++pos;
    fp[p[u]] = u;
    if(son[u] != -1)getpos(son[u], sp);
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v); //�����
    }
}

//�߶���
int Max[N<<2];
void PushUp(int rt){
    Max[rt]=max(Max[rt<<1],Max[rt<<1|1]);
}

void build(int l,int r,int rt){
    if(l==r)return ;
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    //PushUp(rt); //Max����0����ҪPushUp
}

void update(int p,int re,int l,int r,int rt){  //�����滻
    if(l==r){
        Max[rt]=re;
        return ;
    }
    int m=(l+r)>>1;
    if(p<=m)update(p, re, lson);
    else update(p, re, rson);
    PushUp(rt);
}

int query(int L,int R,int l,int r,int rt){ //�������
    if(L<=l && r<=R){
        return Max[rt];
    }
    int m=(l+r)>>1;
    int ret=0;
    if(L<=m)ret=max(ret, query(L, R, lson));
    if(R>m)ret=max(ret,query(L, R, rson));
    return ret;
}

int solve(int u, int v){ //��ѯu->v�ߵ����ֵ
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2){
        if(dep[f1] < dep[f2]){  //����ȴ�Ĳ���
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(p[f1], p[u], 1, pos, 1));
        u = fa[f1]; f1 = top[u];
    }//�����Ȩ�ͱ�Ȩ������Щ��ͬ
    if(u == v)return tmp;   //u����v��û����
    if(dep[u] > dep[v])swap(u, v);  //���һ�β���
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
        dfs1(1, -1, 0);  //��fa��dep��sz��son�����
        getpos(1, 1); // ���top��p��pos (����pos���Ա������߶����Ĵ�С��һ�㶼����n)
        build(1, pos, 1);
        for(int i=1; i<n; i++){
            if(dep[e[i][0]] > dep[e[i][1]])
                swap(e[i][0], e[i][1]);
            update(p[e[i][1]], e[i][2], 1, pos, 1); //����ȴ�������±�Ȩ�����ǻ��ڱ�Ȩ�ķ���
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


HDU 3966 Aragorn's Story �������ʷ�+��״���飩
���⣺
��һ������������������Ȩ��ֵ��Ȼ����3�ֲ�����
I C1 C2 K: ��C1��C2��·���ϵ����е�Ȩֵ����K
D C1 C2 K����C1��C2��·���ϵ����е�Ȩֵ��ȥK
Q C����ѯ�ڵ���ΪC��Ȩֵ
//���ڵ�Ȩ����ѯ����ֵ���޸�·�����ϵĵ�Ȩ
int n, m, q;
struct Edge{
    int to, next;
}edge[N<<1];

int head[N], tol;
int top[N];//top[v]��ʾv���ڵ������Ķ��˽ڵ�
int fa[N];//���׽ڵ�
int dep[N];//���
int sz[N];//sz[v]��ʾ��vΪ���������Ľڵ���
int p[N];//p[v]��ʾv���丸�׽ڵ���������߶����е�λ��
int fp[N];//��p�����෴  ��֪v���߶�����λ��,�丸�׽ڵ���u
int son[N];//�ض���
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
    p[u] = ++pos;  //��״�����Ŵ�1��ʼ
    fp[p[u]] = u;
    if(son[u] != -1)getpos(son[u], sp);
    for(int i=head[u]; i!=-1; i=edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v); //�����
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
    }  //�����Ȩ�ͱ�Ȩ������Щ��ͬ
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
