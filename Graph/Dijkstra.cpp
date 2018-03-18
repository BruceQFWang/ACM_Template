/*模板一
 *前向星邻接表  枚举边方便点
 *tol记得初始化
 */
typedef pair <int, int> pii;
const int N = 50010;
const int inf= 0x3f3f3f3f;
int n,tol;
int d[N];
int head[N];
struct edge{
    int u,v,w,next;
}e[2*N];

void  init(){
    memset(head, -1, sizeof(head));
    for(int i=0; i<N; i++)d[i]=inf;
}

void addedge(int u,int v,int w){
    e[tol].u=u; e[tol].v=v; e[tol].w=w;
    e[tol].next=head[u]; head[u]=tol++;
    u=u^v;  v=u^v;  u=u^v;//异或
    e[tol].u=u; e[tol].v=v; e[tol].w=w;
    e[tol].next=head[u]; head[u]=tol++;
}

void dij(){
    priority_queue<pii, vector<pii >, greater<pii > > q;//取最小值
    d[1] = 0;
    q.push(make_pair(d[1], 1));
    while(!q.empty()){
        int u,v,w;
        pii x = q.top();
        q.pop();
        u = x.second;
        for(int i=head[u]; i!=-1; i=e[i].next){
            v = e[i].v;
            w = e[i].w;
            if(d[u]+w < d[v]){
                d[v] = d[u]+w;
                q.push(make_pair(d[v], v));
            }
        }
    }
}

/*模板二
  vector建图
  点很多的话效率会比较低
*/
const  int  inf=1e9;
const  int  maxn=205;
vector<pair<int,int> >E[maxn];//邻接表
int n,m;
int d[maxn];

void  init(){
    for(int i=0; i<maxn; i++)E[i].clear();
    for(int i=0; i<maxn; i++)d[i] = inf;
}

void dijkstra(int s,int t){
    priority_queue<pair<int,int> >q;
    d[s] = 0;
    q.push({-d[s], s});//优队返回的是最大值，取负就返回的最小值
    while(!q.empty()){
        int u = q.top().second;
        q.pop();
        for(int i=0; i<E[u].size(); i++){
           int v = E[u][i].first, w = E[u][i].second;
            if(d[v] > d[u]+w){
                d[v] = d[u]+w;
                q.push({-d[v], v});
            }
        }
    }
    if(d[t] == inf)printf("-1\n");
    else  printf("%d\n",d[t]);
}

int  main(){
    while(cin>>n>>m){
        init();
        for(int i=0; i<m; i++){
            int x,y,z;scanf("%d %d %d",&x,&y,&z);
            E[x].push_back(make_pair(y,z));  //边x,y,边权z
            E[y].push_back(make_pair(x,z));
        }
        int  s,t;
        scanf("%d %d",&s,&t);

        dijkstra(s,t);
    }
    return  0;
}
