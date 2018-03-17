���⣺��n����Ʒ��ÿ����Ʒ���м۸�ci���Ż�ȯdi,���˵�һ����Ʒ����������Ʒ���Ż�ȯ������֮ǰ��ĳ����Ʒ������bԪ��������Ʒ��
˼·��������������DP�����Ը����Ż�ȯ��Լ����ϵ�����һ����,��������DP

���壺dp[������] [ѡ����Ʒ��] [�ò����Ż�ȯ] ����С����
ת�Ʒ��̣�
dp[u][j][1]=min(dp[u][j-k][1],min(dp[v][k][1],dp[v][k][0]))
dp[u][j][0]=min(dp[u][j-k][0],dp[v][k][0]))

��Ȼ,ֱ��DP��ҪO(n3)
�����Ż�,ά��size[u]=��ǰuΪ���������Ѿ����ֵĽڵ����
���ȶ�����u,size[u]=1,�������v��,���������һ��,Ȼ��size[u]+=size[v],��������������ӡ�
�������Ӷ���ʵֻ��O(n2),��Ϊ����u������2�����,ֻͬʱ����һ��
ע�����size[u]+=size[v],�ٶ�u,v�󱳰�,���ӶȾͱ�ΪO(n3)��,��Ϊ����vҲ����������һ�α���
���룺
const int N = 5e3+5;

int n, b, c[N], d[N], sz[N];
ll dp[N][N][2];
vector<int>E[N];

void dfs(int u){
    sz[u] = 1;
    dp[u][0][0] = 0;  //��ѡ����Ǯ
    dp[u][1][0] = c[u];  //���þ��Լ�
    dp[u][1][1] = c[u]-d[u];  //���˾ͼ�ȥ
    for(int i=0; i<E[u].size(); i++){
        int v = E[u][i];
        dfs(v);
        for(int j=sz[u]; j>=0; j--)
            for(int k=sz[v]; k>=0; k--){
                dp[u][j+k][0] = min(dp[u][j+k][0], dp[u][j][0]+dp[v][k][0]);
                dp[u][j+k][1] = min3(dp[u][j+k][1], dp[u][j][1]+dp[v][k][1], dp[u][j][1]+dp[v][k][0]);
            }
        sz[u] += sz[v];
    }
}


int  main(){
    mst(dp, inf);
    scanf("%d %d", &n, &b);
    for(int i=1; i<=n; i++){
        int pre;
        scanf("%d %d", &c[i], &d[i]);
        if(i >= 2){
            scanf("%d", &pre);
            E[pre].pb(i);
        }
    }
    dfs(1);
    for(int i=n; i>=0; i--){
        if(dp[1][i][0] <= 1LL*b || dp[1][i][1] <= 1LL*b){
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
