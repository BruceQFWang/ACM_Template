//����㷨���������㷨��ʱ�临�Ӷ�ҪС�������ݿ��Բ�������㷨

/* *********************************************
����ͼƥ�䣨Hopcroft-Carp���㷨����
��ʼ����g[][]�ڽӾ���
���ã�res=MaxMatch();  Nx,NyҪ��ʼ��������
ʱ�临�Ӵ�Ϊ O(sqrt(V)*E)

���������ݽϴ�Ķ���ƥ��
��Ҫqueueͷ�ļ�
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
    for(int i=0;i<Nx;i++)//��������Ŵ�0��ʼ����Ҫ��1��ʼ��Ҫ�޸�
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
