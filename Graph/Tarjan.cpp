���壺
��������ͼ�ϵ�2����a,b��������һ����a��b��·����Ҳ����һ����b��a��·������ô��a,b��ǿ��ͨ�ġ�
��������ͼ�ϵ�һ����ͼ������ͼ��������(a,b)������ǿ��ͨ����Ƹ���ͼΪǿ��ͨ��ͼ��
��ǿ��ͨͼ����ͼ�ļ���ǿ��ͨ��ͼ����Ϊǿ��ͨ������
�����ĵ�Ҳ������ǿ��ͨ����

// ÿ�����㶼��������һ�Σ���ֻ������һ�ζ�ջ��ÿ����Ҳֻ��������һ��,���Ӷ�O(n+m)
const int maxn = 20010; //����
const int maxm = 100010; //����
struct Edge{
    int to, next;
}edge[maxm];
int head[maxn], tol;
int dfn[maxn];//DFN(u)Ϊ�ڵ�u�����Ĵ�����(ʱ���)
int low[maxn];//ͨ��������ܵ������Сdfn
int stk[maxn], belong[maxn];//belong�����ֵ��1~scc
int idx, top;
int scc;//ǿ��ͨ�����ĸ���  Strongly connected component
bool instk[maxn];
int num[maxn];//����ǿ��ͨ����������ĸ�����������1~scc
//num���鲻һ����Ҫ�����ʵ�����

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn)); //DFSʱ����ţ����!=0˵���Ѿ������ʹ���
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
    low[u] = dfn[u] = ++idx;//��ʼ��dfn��low
    stk[top++] = u;  //���ڵ�uѹ��ջ��
    instk[u] = 1;
    for(int i=head[u]; i!=-1; i=edge[i].next){ //ö��ÿһ����
        v = edge[i].to;
        if(!dfn[v]){  //�ڵ�vδ������
            Tarjan(v); //����������
            low[u] = min(low[u], low[v]);
        }
        else if(instk[v]) //�ڵ�v�ѷ��ʣ���(u,v)Ϊ�ر�
            low[u] = min(low[u], dfn[v]);
    }

    if(low[u] == dfn[u]){ //����ڵ�u��ǿ��ͨ�����ĸ�
        scc++;
        do{
            v = stk[--top]; //��v��ջֱ��Ϊ��ǿ��ͨ�����ĸ�
            instk[v] = 0;
            belong[v] = scc;
            num[scc]++;
        }
        while(v != u);
    }
}

//��Ϊ��Щ�������1���ﲻ�˵ģ�����Tarjan(1)�Ͳ��ܵõ����е�ǿ��ͨ������������Ҫforѭ������ÿһ����
/*1.���ã�
for(int i=1; i<=n; i++)
            if(!dfn[i])Tarjan(i);
*/

2.���½�ͼ
//����hihocoder 1185  ������ͼ�ӵ�1��ʼ�ߵõ�������Ȩ��
//���Ӷ�O(n+m)
const int maxn = 10010; //����
const int maxm = 100010; //����
struct Edge{
    int to, next;
}edge[maxm], redge[maxm];
int head[maxn], tol;
int dfn[maxn];//DFN(u)Ϊ�ڵ�u�����Ĵ�����(ʱ���)
int low[maxn];//Low(u)Ϊu��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int stk[maxn], belong[maxn];//belong�����ֵ��1~scc
int idx, top;
int scc;//ǿ��ͨ�����ĸ���  Strongly connected component
bool instk[maxn];
int num[maxn];//����ǿ��ͨ����������ĸ�����������1~scc
//num���鲻һ����Ҫ�����ʵ�����

int rhead[maxn], rtol;//���½�ͼ

void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn)); //DFSʱ����ţ����!=0˵���Ѿ������ʹ���
    memset(low, 0, sizeof(low));
    memset(num, 0, sizeof(num));
    memset(instk, 0, sizeof(instk));
    memset(belong, 0, sizeof(belong));
    idx = scc = top = 0;
    rtol = 0;//���½�ͼ
    memset(rhead, -1, sizeof(rhead));
}

void addedge(int u,int v){
    edge[tol].to = v; edge[tol].next = head[u]; head[u] = tol++;
}

void addredge(int u,int v){//���½�ͼ
    redge[rtol].to = v; redge[rtol].next = rhead[u]; rhead[u] = rtol++;
}

void Tarjan(int u){
    int v;
    low[u] = dfn[u] = ++idx;//��ʼ��dfn��low
    stk[top++] = u;  //���ڵ�uѹ��ջ��
    instk[u] = 1;
    for(int i=head[u]; i!=-1; i=edge[i].next){ //ö��ÿһ����
        v = edge[i].to;
        if(!dfn[v]){  //�ڵ�vδ������
            Tarjan(v); //����������
            low[u] = min(low[u], low[v]);
        }
        else if(instk[v]) //�ڵ�v�ѷ��ʣ���(u,v)Ϊ�ر�
            low[u] = min(low[u], dfn[v]);
    }

    if(low[u] == dfn[u]){ //����ڵ�u��ǿ��ͨ�����ĸ�
        scc++;
        do{
            v = stk[--top]; //��v��ջֱ��Ϊ��ǿ��ͨ�����ĸ�
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

        for(int i=1; i<=n; i++){//���½�ͼ
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
