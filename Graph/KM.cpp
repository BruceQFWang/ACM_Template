1.ͨ�׵�˵����ȫƥ��ֻҪһ�ߵĵ㶼��ƥ���о��С�������ƥ�������൱��Ҫ��˫�����ȫƥ�䡱��
2.KM�㷨���������ƥ����Ȩ����һ�����ڱ���ͼ�ʹﲻ������ƥ�䣬��ֻ�������걸ƥ�������£�KM��������걸ƥ����Ȩ����һ����
3.�������ͼ�ʹﲻ������ƥ�䣬����Ҫ������Ȩƥ�䣬��ô����ô�죿
(1)ֻҪ������û�еı����0������,Ȼ����KM�㷨
(2)�÷��������ܣ���������÷������������˵�����ٵ㣬����Ч�ʱ�KM����

/* KM�㷨
* ���Ӷ�O(nx*nx*ny)
* �����Ȩƥ��
* ������СȨƥ�䣬�ɽ�Ȩֵȡ�෴�������ȡ�෴��
* ��ı�Ŵ�1��ʼ
*/
const int N=310;
const int inf=0x3f3f3f3f;
int nx,ny;//���ߵĵ���
int g[N][N];//����ͼ���� ֻ��Ҫ������߾ͺ��ˣ�ƥ���ʱ�����߿�ʼ
int link[N],lx[N],ly[N];//y�и���ƥ��״̬��x,y�еĶ�����
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
