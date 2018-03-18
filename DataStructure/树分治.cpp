poj1741 Tree
���⣺�����Ͼ���С�ڵ���K�ĵ���ж��ٸ���
˼·������һ���и����� ��������Ҫ���һ����������Ӧ��һ��·������Ȼ�������������֮һ��
1���������ڵ�
2�����������ڵ㣬Ҳ����˵�ڸ��ڵ��һ��������
�������2�����Եݹ����Ȼ��ͱ�������1��������Ҫ���������1:
��u��v��·����Ȼ�����˶���s��ֻҪ�����ÿ�����㵽s�ľ�������ͳ�Ƽ��ɡ���ע���ڵ�һ������м�ȥ�ڶ����ظ�����Ĳ��֣�
�����˻���������ʽʱ���ݹ��������˻�ΪO(n)������ѡ��ÿ�ζ��ҵ�����������Ϊ�ָ����㡣���ľ���ɾ���˽���õ�����������Ķ��������ٵĶ��㣬ɾ�����ĺ�õ�������������������Ȼ������n/2��
�������ĵ�ʱ�򣬼����Ϊv������v���������ҵ�һ�����㣬ʹɾ���ö�������������Ķ��������٣�Ȼ����ɾ��v������������������Ķ�������
����ѡ����С��һ������ʱѡ�еĶ��㼴Ϊ���ġ�
�ݹ��ÿһ�㶼��������O(nlogn)���ݹ����O(logn)������ʱ�临�Ӷ�O(nlog2n)��
struct Edge{
    int to, next, w;
}edge[N<<1];
int head[N], tol;
void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int w){
    edge[tol].to = v; edge[tol].next = head[u]; edge[tol].w = w; head[u] = tol++;
}
//f[i]i���ӽڵ���sz[v]����ֵ   sz[i]i��size�����ϱ��������Ľڵ����� d[i]��� nsize������С
int n, K, root, ans, nsize, sz[N], f[N], d[N];
vector<int>dis; //ĳ�����������о���
bool done[N];//�ڵ�i֮ǰ��Ϊ���ù���

void getroot(int u, int fa){ //��ȡ����
    f[u] = 0; sz[u] = 1;
    for(int i=head[u]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(v == fa || done[v])continue;
        getroot(v, u);
        sz[u] += sz[v];
        f[u] = max(f[u], sz[v]);
    }
    f[u] = max(f[u], nsize-sz[u]);
    if(f[u] < f[root])root = u;
}

void getdis(int u, int fa){//��ȡ�������нڵ�����ľ���
    dis.pb(d[u]);
    sz[u] = 1;
    for(int i=head[u]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(v == fa || done[v])continue;
        d[v] = d[u]+edge[i].w;
        getdis(v, u);
        sz[u] += sz[v];
    }
}

int calc(int x, int w){//���㵱ǰ������x�������£���������Ĵ� d[x]��ʼ���Ϊw
    dis.clear(); d[x] = w;
    getdis(x, 0);
    sort(dis.begin(), dis.end());
    int ret = 0;
    for(int l=0, r=dis.size()-1; l<r; )
        if(dis[l]+dis[r] <= K)ret += r-l++;
        else r--;
    return ret;
}

void solve(int x){//��xΪ���Ľ��м���
    ans += calc(x, 0);
    done[x] = 1;
    for(int i=head[x]; ~i; i=edge[i].next){
        int v = edge[i].to;
        if(done[v])continue;
        ans -= calc(v, edge[i].w);
        f[0] = nsize = sz[v];
        getroot(v, root=0);
        solve(root);
    }
}

int  main(){
    while(~scanf("%d%d", &n, &K)){
        if(!n && !K)break;
        init();
        memset(done, 0, sizeof(done));
        for(int i=1; i<n; i++){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        f[0] = nsize = n;
        getroot(1, root = 0);
        ans = 0;
        solve(root);
        printf("%d\n", ans);
    }
    return 0;
}
