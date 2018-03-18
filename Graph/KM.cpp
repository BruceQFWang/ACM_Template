1.通俗地说，完全匹配只要一边的点都在匹配中就行。而完美匹配则是相当于要“双向的完全匹配”。
2.KM算法求的是完美匹配中权最大的一个，在本来图就达不到完美匹配，而只有若干完备匹配的情况下，KM不能求出完备匹配中权最大的一个。
3.如果本来图就达不到完美匹配，但仍要求出最大权匹配，那么该怎么办？
(1)只要把所有没有的边设成0就行了,然后跑KM算法
(2)用费用流来跑，这种情况用费用来跑相对来说代码少点，但是效率比KM稍慢

/* KM算法
* 复杂度O(nx*nx*ny)
* 求最大权匹配
* 若求最小权匹配，可将权值取相反数，结果取相反数
* 点的编号从1开始
*/
const int N=310;
const int inf=0x3f3f3f3f;
int nx,ny;//两边的点数
int g[N][N];//二分图描述 只需要存有向边就好了，匹配的时候从左边开始
int link[N],lx[N],ly[N];//y中各点匹配状态，x,y中的顶点标号
int slack[N];
bool visx[N],visy[N];

bool dfs(int x){
    visx[x]=true;
    for(int y=1; y<=ny; y++){
        if(visy[y])continue;
        int tmp=lx[x]+ly[y]-g[x][y];
        if(tmp==0){
            visy[y]=true;
            if(link[y]==-1 || dfs(link[y])){
                link[y]=x;
                return true;
            }
        }
        else if(slack[y]>tmp) slack[y]=tmp;
    }
    return false;
}

int KM(){
    memset(link, -1, sizeof(link));
    memset(ly, 0, sizeof(ly));
    for(int i=1; i<=nx; i++){
        lx[i]=-inf;
        for(int j=1; j<=ny; j++)
            if(g[i][j]>lx[i])
                lx[i]=g[i][j];
    }
    for(int x=1; x<=nx; x++){
        for(int i=1; i<=ny; i++) slack[i]=inf;
        while(true){
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(dfs(x))break;
            int d=inf;
            for(int i=1; i<=ny; i++)
                if(!visy[i] && d>slack[i])
                    d=slack[i];
            for(int i=1; i<=nx; i++)
                if(visx[i])
                    lx[i]-=d;
            for(int i=1; i<=ny; i++){
                if(visy[i])ly[i]+=d;
                else slack[i]-=d;
            }
        }
    }
    int res=0;
    for(int i=1; i<=ny; i++)
        if(link[i]!=-1)
            res+=g[link[i]][i];
    return res;
}

//HDU 2255
int main(){
  int n;
  while(~scanf("%d",&n)){
    for(int i=1; i<=n; i++)
      for(int j=1; j<=n; j++)
        scanf("%d",&g[i][j]);
    nx=ny=n;
    printf("%d\n",KM());
  }
  return 0;
}
