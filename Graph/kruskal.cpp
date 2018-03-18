/*
  * Kruskal�㷨��MST
  *���Ӷ� O��E LOG2��V����
  * ����POJ1258-Agri-Net
  *ֻҪ��һ�α߾�����
  */
const int maxn = 2e4+10; //������
int p[maxn];    //���鼯��ʹ��

struct edge{
    int u,v,cost;
    bool operator < (const edge& rhs)const {
        return cost < rhs.cost;
    }
}e[55555];

void init(){ /*��ʼ��i�ĸ��׽ڵ�Ϊi */
    for(int i=0 ; i<maxn ; i++){
        p[i]=i;
    }
}

int Find(int x){//����x�ĸ��׽ڵ㣬�ݹ����
    return  p[x]==x?x:p[x]=Find(p[x]);
}

int kruskal(int n,int m){  //������С��������Ȩֵ
    int ans = 0;
    sort(e, e+m);
    for(int i=0 ; i<m ; i++){
        int u = e[i].u, v = e[i].v;
        int fu = Find(u), fv = Find(v);
        if(fu != fv){   //�������һ�������У��ϲ�
            ans += e[i].cost;
            p[fv] = fu;
        }
    }
    return ans;
}

