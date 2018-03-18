const int maxn=100010;//���������ֵ
const int maxm=400010;//���������ֵ,��������
const int inf=0x3f3f3f3f;
struct Edge {
  int to,next,cap,flow;
}edge[maxm];//ע����maxm
int tol;
int head[maxn];
int cur[maxn],d[maxn];// ��ǰ���±�   ��㵽�������½�
int p[maxn],gap[maxn];//������·�ϵ���һ����   gap�Ż�  //��dinic�����������

void init() {
    tol=0;
    memset(head,-1,sizeof(head));
}

//�ӱߣ�����ͼ����������˫��ͼ�ĸ�����
void addedge(int u,int v,int w,int rw=0) {
    edge[tol].to=v; edge[tol].cap=w; edge[tol].next=head[u];edge[tol].flow=0; head[u]=tol++;
    edge[tol].to=u; edge[tol].cap=rw; edge[tol].next=head[v];edge[tol].flow=0; head[v]=tol++;
}

//�����������㡢�յ㡢�������
//��ı��û��Ӱ�죬ֻҪ������(���)����
int sap(int s,int t,int N){
    memset(gap, 0, sizeof(gap));
    memset(d, 0, sizeof(d));
    memcpy(cur, head, sizeof(head));
    int u=s;
    p[u]=-1;
    gap[0]=N;
    int ans=0;
    while(d[s]<N){
        if(u == t){
            int Min=inf;
            for(int i=p[u]; i!=-1; i=p[edge[i^1].to])//����С����ֵ
                if(Min>edge[i].cap-edge[i].flow)
                    Min=edge[i].cap-edge[i].flow;
            for(int i = p[u]; i!=-1; i=p[edge[i^1].to]){//����
                edge[i].flow+=Min;
                edge[i^1].flow-=Min;
            }
            u=s;
            ans+=Min;
            continue;
        }
        bool ok=false;
        int v;
        for(int i=cur[u]; i!=-1; i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cap-edge[i].flow && d[v]+1==d[u]){//Advanceǰ��
                ok=true;
                cur[u]=p[v]=i;
                break;
            }
        }
        if(ok){
            u=v;
            continue;
        }
        //Retreat�߲����ˣ�����
        int Min=N;
        for(int i=head[u]; i!=-1; i=edge[i].next)
            if(edge[i].cap-edge[i].flow && d[edge[i].to] < Min){
                Min=d[edge[i].to];
                cur[u]=i;
        }
        gap[d[u]]--;
        if(!gap[d[u]])return ans;
        d[u] = Min+1;
        gap[d[u]]++;
        if(u!=s) u=edge[p[u]^1].to;//��һ�����ظ��߷���
    }
    return ans;
}
