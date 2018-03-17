/*һ��dfs��ö��ÿһ������Ϊת�۵�t�������tΪ���ڵ�������еġ��·���Լ�
 *�롮�·�����غϵġ��γ�·������������·�ĳ���֮��ȥ���´�
 */
const int N = 1e5+5;

int n;
vector<int>E[N];

int dfs(int u, int fa, int& mx){
    int tmax = 0, tsec = 0;
    for(int i=0; i<E[u].size(); i++){
        int v = E[u][i];
        if(v == fa)continue;
        int nowd = dfs(v, u, mx)+1;
        if(nowd > tmax)tsec = tmax, tmax = nowd;
        else if(nowd > tsec)tsec = nowd;
    }
    mx = max(mx, tmax+tsec);
    return tmax;
}

int  main(){
    scanf("%d", &n);
    for(int i=1; i<n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        E[u].pb(v);
        E[v].pb(u);
    }
    int sum = 0;
    dfs(1, -1, sum);
    printf("%d\n", sum);
    return 0;
}


//���￪��ȫ��dis����
//�����ο� cf 734E  ������ֱ�� �������ڽڵ�����������1 ����
const int N=2e5+10;

std::vector<int> E[N];
int col[N], n, dis[N];

void dfs(int u, int fa){
    for(auto v : E[u]){
        if(v==fa)continue;
        dis[v]+=dis[u]+(col[u]^col[v]);
        dfs(v, u);
    }
}

int  main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d", &col[i]);
    for(int i=1; i<n; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1, -1);
    int u=1;
    for(int i=1; i<=n; i++)
        if(dis[i]>dis[u])u=i;
    mst(dis, 0);
    dfs(u, -1);
    u=1;
    for(int i=1; i<=n; i++)
        if(dis[i]>dis[u])u=i;
    printf("%d\n", (dis[u]+1)/2);
    return 0;
}
