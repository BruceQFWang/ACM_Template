��չ��
1.���Ҫ�ĳɸ߾������е�cost��d��Ҫ�ĳ�double��ͬʱע��Ƚ�Ҫ��eps
2.��Ҫ��������룬��Ҫ��������������ȶԷ���ȡ����Ȼ��ֱ�������㲿���ж��ǲ�����Ȩ����·���У�Ҳ����˵spfa֮��d[t] >= 0 ��ʱ��ֱ��break(��Ϊ���÷Ǹ��ͻ�ʹ��ȡ����ޚ�������)

//��С�������������������ֻ��Ҫȡ�෴��������ɡ�
//�������Ϊ N����ı�� 0~N-1
const int maxn=10000;
const int maxm=100000;//���������Ҫ������ߵ���������Ϊ�к����
const int inf=0x3f3f3f3f;

struct Edge{
  int to,next,cap,flow,cost;
}es[maxm];
int head[maxn],tol;
int p[maxn];//��¼����·���� �����i�ıߵı��
int d[maxn];//��λ�ܷ���
bool vis[maxn];
int N;//�ڵ��ܸ���

void init(int n){
    N=n;
    tol=0;
    memset(head, -1, sizeof(head));
}

void addedge(int u,int v,int cap,int cost){
    es[tol].to=v;es[tol].cap=cap;es[tol].cost=cost;es[tol].flow=0;es[tol].next=head[u];head[u]=tol++;
    es[tol].to=u;es[tol].cap=0;es[tol].cost=-cost;es[tol].flow=0;es[tol].next=head[v];head[v]=tol++;
}

bool spfa(int s,int t){//Ѱ�һ������ٵ�·��
    //��һ��SPFA ��s����t�����ٻ���·�� �Ҹ�·����ÿһ���߲�������
    //������ ˵�����Լ������㣬��֮����
    queue<int>q;
    for(int i=0; i<N; i++){
        d[i]=inf;
        vis[i]=false;
        p[i]=-1;
    }
    d[s]=0;
    vis[s]=true;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u]; i!=-1; i=es[i].next){ //����ö����uΪ���ı�
            int v=es[i].to;
            if(es[i].cap>es[i].flow && d[v]>d[u]+es[i].cost){//�����ɳ� �� û������ ��һ���߾���Ҫ��eps
                d[v]=d[u]+es[i].cost;
                p[v]=i;   //��¼ǰ���� �ı��
                if(!vis[v]){ vis[v]=true; q.push(v);}
            }
        }
    }
    return p[t]!=-1;//�ɴﷵ��true
}

//���ص����������cost�������С����
int MCMF(int s,int t,int &cost){
    int flow = 0;cost = 0;
    while(spfa(s,t)){//ÿ��Ѱ�һ�����С��·��
        int Min=inf;
        //ͨ������ ��Դ�㵽�������ٻ���·�� ����С������
        for(int i=p[t]; i!=-1; i=p[es[i^1].to]){
            if(Min>es[i].cap-es[i].flow)
                Min=es[i].cap-es[i].flow;
        }
    	//����
        for(int i=p[t]; i!=-1; i=p[es[i^1].to]){
            es[i].flow+=Min;
            es[i^1].flow-=Min;
            cost+=es[i].cost*Min;//�������Ļ���
        }
        flow+=Min;//�������ۼ�
    }
    return flow;
}
