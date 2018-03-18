//这个算法比匈牙利算法的时间复杂度要小，大数据可以采用这个算法

/* *********************************************
二分图匹配（Hopcroft-Carp的算法）。
初始化：g[][]邻接矩阵
调用：res=MaxMatch();  Nx,Ny要初始化！！！
时间复杂大为 O(sqrt(V)*E)

适用于数据较大的二分匹配
需要queue头文件
********************************************** */
const int maxn=3000;
const int inf=1<<28;
int g[maxn][maxn],Mx[maxn],My[maxn],Nx,Ny;
int dx[maxn],dy[maxn],dis;
bool vis[maxn];

bool searchP(){
    queue<int>Q;
    dis=inf;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=0;i<Nx;i++)//这个顶点编号从0开始，若要从1开始需要修改
        if(Mx[i]==-1){
            Q.push(i);
            dx[i]=0;
        }
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        if(dx[u]>dis)  break;
        for(int v=0;v<Ny;v++)
            if(g[u][v]&&dy[v]==-1){
                dy[v]=dx[u]+1;
                if(My[v]==-1)  dis=dy[v];
                else
                {
                    dx[My[v]]=dy[v]+1;
                    Q.push(My[v]);
                }
            }
    }
    return dis!=inf;
}

bool dfs(int u){
    for(int v=0;v<Ny;v++)
       if(!vis[v]&&g[u][v]&&dy[v]==dx[u]+1)
       {
           vis[v]=1;
           if(My[v]!=-1&&dy[v]==dis) continue;
           if(My[v]==-1||dfs(My[v]))
           {
               My[v]=u;
               Mx[u]=v;
               return 1;
           }
       }
    return 0;
}

int MaxMatch(){
    int res=0;
    memset(Mx,-1,sizeof(Mx));
    memset(My,-1,sizeof(My));
    while(searchP())
    {
        memset(vis,0,sizeof(vis));
        for(int i=0;i<Nx;i++)
          if(Mx[i]==-1 && dfs(i))  res++;
    }
    return res;
}
