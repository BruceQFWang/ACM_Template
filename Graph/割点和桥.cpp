����1��
��㣺һ������Ϊ��㣨���߸�����ҽ���ȥ���ýڵ㼫����صı�֮�����ͼ����ͨ��
�ţ�һ���߳�Ϊ�ţ����߸�ߣ����ҽ���ȥ���ñ�֮�����ͼ����ͨ��
����2��
��㣺��һ������ͼ�У����ɾȥһ���㣬���ͼ����ͨ�������ˣ�ɾȥ�������
�ţ����ɾ��һ���ߣ����ͼ����ͨ�������ˣ�ɾ����������
�ο����ͣ�http://blog.csdn.net/fuyukai/article/details/51039788 ���������Ҳ��ע�ͣ�
const int maxn = 10005;
const int maxm = 100005;
struct Edge{
    int to, next;
    bool cut;//�Ƿ�Ϊ�ŵı��
}edge[maxm];
int head[maxn], tol;
int low[maxn], dfn[maxn], stk[maxn];
int idx, top;
bool instk[maxn];
bool cut[maxn];
int add_block[maxn];//ɾ��һ��������ӵ���ͨ��
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
            //��
            //һ�������(u,v)���ţ����ҽ���(u,v)Ϊ��֦�ߣ�������DFS(u)<Low(v)��
            if(low[v] > dfn[u]){  //�ж��ŵ�ʱ��������Ӳ��ܴ����ر�
                bridge++;
                edge[i].cut = 1;
                edge[i^1].cut = 1;
            }
            //���
            //һ������u�Ǹ�㣬���ҽ�������(1)��(2) (1) uΪ��������u�ж���һ��������
            //(2) u��Ϊ���������������(u,v)Ϊ��֦��(��Ƹ��ӱߣ�
            //��uΪv���������еĸ���)��ʹ��DFS(u)<=Low(v)
            if(u != fa && low[v] >= dfn[u]){//��������
                cut[u] = 1;
                add_block[u]++;
            }
        }
        else if(low[u] > dfn[v])low[u] = dfn[v];
    }
    //��������֧������1
    if(u == fa && son > 1)cut[u] = 1;
    if(u == fa)add_block[u] = son-1;
    instk[u] = 0;
    top--;
}

/*1.���ã�
for(int i=1; i<=n; i++)
            if(!dfn[i])Tarjan(i, -1);
addedge���˫���,һ��Ҫһ��ӣ�Ҫ��Ȼi��i^1�Ͳ���˫�����
�������رߣ�����Tarjan��������Ҫ��father
*/
/*2.���ĸ���forһ��cut�����������ˣ��ŵĸ������ǿ�bridge
*/

//�ж��ſ��Դ����رߣ���ʵpre_cnt����Ҳ���Լӵ�����Ĵ������Ϊ�в����ر߲�Ӱ�����ж�
const int maxn = 400005;
const int maxm = 4000005;
struct Edge{
    int to, next;
    bool cut;//�Ƿ�Ϊ�ŵı��
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
    int pre_cnt = 0;//�����رߣ��������Ҫ����ȥ��
    for(int i=head[u]; i!=-1; i=edge[i].next){
        v = edge[i].to;
        if(v == pre && !pre_cnt){ pre_cnt++; continue;}
        if(!dfn[v]){
            son++;
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            //��
            //һ�������(u,v)���ţ����ҽ���(u,v)Ϊ��֦�ߣ�������DFS(u)<Low(v)��
            if(low[v] > dfn[u]){
                bridge++;
                edge[i].cut = 1;
                edge[i^1].cut = 1;
            }
        }
        else if(low[u] > dfn[v])low[u] = dfn[v];
    }
    if(low[u] == dfn[u]){ //����ڵ�u��ǿ��ͨ�����ĸ�
        scc++;
        do{
            v = stk[--top]; //��v��ջֱ��Ϊ��ǿ��ͨ�����ĸ�
            instk[v] = 0;
            belong[v] = scc;
        }
        while(v != u);
    }
}
