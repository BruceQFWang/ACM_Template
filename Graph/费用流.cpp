拓展：
1.如果要改成高精度所有的cost和d都要改成double，同时注意比较要加eps
2.当要求最大收入，不要求最大流，可以先对费用取反，然后直接在增广部分判断是不是正权增广路就行，也就是说spfa之后d[t] >= 0 的时候直接break(因为费用非负就会使得取反后逇收入减少)

//最小费用最大流，求最大费用只需要取相反数结果即可。
//点的总数为 N，点的编号 0~N-1
const int maxn=10000;
const int maxm=100000;//看情况，还要是有向边的两倍，因为有后悔流
const int inf=0x3f3f3f3f;

struct Edge{
  int to,next,cap,flow,cost;
}es[maxm];
int head[maxn],tol;
int p[maxn];//记录增广路径上 到达点i的边的编号
int d[maxn];//单位总费用
bool vis[maxn];
int N;//节点总个数

void init(int n){
    N=n;
    tol=0;
    memset(head, -1, sizeof(head));
}

void addedge(int u,int v,int cap,int cost){
    es[tol].to=v;es[tol].cap=cap;es[tol].cost=cost;es[tol].flow=0;es[tol].next=head[u];head[u]=tol++;
    es[tol].to=u;es[tol].cap=0;es[tol].cost=-cost;es[tol].flow=0;es[tol].next=head[v];head[v]=tol++;
}

bool spfa(int s,int t){//寻找花销最少的路径
    //跑一遍SPFA 找s——t的最少花销路径 且该路径上每一条边不能满流
    //若存在 说明可以继续增广，反之不能
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
        for(int i=head[u]; i!=-1; i=es[i].next){ //逆向枚举以u为起点的边
            int v=es[i].to;
            if(es[i].cap>es[i].flow && d[v]>d[u]+es[i].cost){//可以松弛 且 没有满流 后一个高精度要加eps
                d[v]=d[u]+es[i].cost;
                p[v]=i;   //记录前驱边 的编号
                if(!vis[v]){ vis[v]=true; q.push(v);}
            }
        }
    }
    return p[t]!=-1;//可达返回true
}

//返回的是最大流，cost存的是最小费用
int MCMF(int s,int t,int &cost){
    int flow = 0;cost = 0;
    while(spfa(s,t)){//每次寻找花销最小的路径
        int Min=inf;
        //通过反向弧 在源点到汇点的最少花费路径 找最小增广流
        for(int i=p[t]; i!=-1; i=p[es[i^1].to]){
            if(Min>es[i].cap-es[i].flow)
                Min=es[i].cap-es[i].flow;
        }
    	//增广
        for(int i=p[t]; i!=-1; i=p[es[i^1].to]){
            es[i].flow+=Min;
            es[i^1].flow-=Min;
            cost+=es[i].cost*Min;//增广流的花销
        }
        flow+=Min;//总流量累加
    }
    return flow;
}
