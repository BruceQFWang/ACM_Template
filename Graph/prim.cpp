//复杂度 O（E LOG2（V））
//51nod  1212 无向图最小生成树
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include<cstring>
using  namespace std;
const  int inf=0x3f3f3f3f;
int cost[1001][1001];//邻接矩阵
int lowc[1001];
bool  vis[1001];
int prim(int cost[][1001],int n){
    int p,minc,res=0;
    memset(vis,0,sizeof(vis));
    vis[1]=1;//从1开始访问
    for(int i=2 ; i<=n ; i++) lowc[i]=cost[1][i];
    for(int i=2;i<=n;i++){
        minc=inf; p=-1;
        for(int j=1;j<=n;j++){
            if(vis[j]==0&&lowc[j]<minc){
                minc=lowc[j]; p=j;
            }
        }
        if(inf==minc) return -1;//原图不连通
        res+=minc; vis[p]=1;
        for(int j=1;j<=n;j++){//更新lowc[]
            if(vis[j]==0&&lowc[j]>cost[p][j]){
                lowc[j]=cost[p][j];
            }
        }
    }
    return res;
}
int main()
{
    std::ios::sync_with_stdio(false);
    int n,m;
    while(cin>>n>>m){
        int x,y,w;
        memset(cost,inf,sizeof(cost));//首先记录所有边的权为inf
        for(int i=1;i<=m;i++){
            cin>>x>>y>>w;
            cost[x][y]=cost[y][x]=w;
        }
        cout<<prim(cost,n)<<endl;
    }
    return 0;
}
