/*
  * Kruskal算法求MST
  *复杂度 O（E LOG2（V））
  * 例题POJ1258-Agri-Net
  *只要加一次边就行了
  */
const int maxn = 2e4+10; //最大点数
int p[maxn];    //并查集的使用

struct edge{
    int u,v,cost;
    bool operator < (const edge& rhs)const {
        return cost < rhs.cost;
    }
}e[55555];

void init(){ /*初始化i的父亲节点为i */
    for(int i=0 ; i<maxn ; i++){
        p[i]=i;
    }
}

int Find(int x){//查找x的父亲节点，递归调用
    return  p[x]==x?x:p[x]=Find(p[x]);
}

int kruskal(int n,int m){  //返回最小生成树的权值
    int ans = 0;
    sort(e, e+m);
    for(int i=0 ; i<m ; i++){
        int u = e[i].u, v = e[i].v;
        int fu = Find(u), fv = Find(v);
        if(fu != fv){   //如果不在一个集合中，合并
            ans += e[i].cost;
            p[fv] = fu;
        }
    }
    return ans;
}

