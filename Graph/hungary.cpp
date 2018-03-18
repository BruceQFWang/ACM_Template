/* **************************************************************************
//二分图匹配（匈牙利算法的DFS实现）
//初始化：g[][]两边顶点的划分情况
//建立g[i][j]表示i->j的有向边就可以了，是左边向右边的匹配
//g没有边相连则初始化为0
//uN是匹配左边的顶点数，vN是匹配右边的顶点数，要记得初始化
//调用：res=hungary();输出最大匹配数
//优点：适用于稠密图，DFS找增广路，实现简洁易于理解
//时间复杂度:O(VE)
//***************************************************************************/
//顶点编号从0开始的
const int maxn=510;//这个值要超过两边点个数的较大者，因为有link
int uN,vN;//u,v数目
int g[maxn][maxn];
int link[maxn];
bool used[maxn];
bool dfs(int u){//从左边开始找增广路径
    int v;
    for(v=0;v<vN;v++)//这个顶点编号从0开始，若要从1开始需要修改
      if(g[u][v]&&!used[v])
      {
          used[v]=true;
          if(link[v]==-1||dfs(link[v]))
          {//找增广路，反向
              link[v]=u;
              return true;
          }
      }
    return false;
}

int hungary(){
    int res=0;
    int u;
    memset(link,-1,sizeof(link));
    for(u=0;u<uN;u++)  //这个顶点编号从0开始，若要从1开始需要修改
    {
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
