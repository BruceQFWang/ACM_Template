//   实际上是BFS
const int inf=1e9;
const int maxn=555;
vector<pair<int,int> >E[maxn];//邻接表
int n,m;
int cnt[maxn];
int d[maxn],inq[maxn];

void  init(){
    for(int i=0; i<maxn; i++)E[i].clear();
    for(int i=0; i<maxn; i++)inq[i] = 0, d[i] = inf, cnt[i] = 0;
}

bool spfa(int s){
    queue<int>q;
    q.push(s),d[s]=0,inq[s]=1;
   while(!q.empty()){
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i=0; i<E[u].size(); i++){
            int v = E[u][i].first, w = E[u][i].second;
            if(d[v] > d[u]+w){
                d[v] = d[u]+w;
                if(inq[v])continue;
                inq[v] = 1;
                q.push(v);
                if(++cnt[v]>n)return true;
            }
        }
    }
    return false;
}


int  main(){
    while(cin>>n>>m){
        init();
        for(int i=0; i<m; i++){
            int x,y,z;scanf("%d %d %d",&x,&y,&z);
            E[x].push_back(make_pair(y,z)); //边x,y,边权z
            E[y].push_back(make_pair(x,z));
        }
        int  s,t;
        scanf("%d %d",&s,&t);

        spfa(s,t);
    }
    return  0;
}
