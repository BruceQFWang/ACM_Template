1������ŵ������=��ͼ�����������������
����ԭͼ��һ����ͼ��Ȼ��Է�ͼ��һ������ŵ���⣬����ű�֤���Ƿ�ͼ�е������ȫ�Ӽ����κ�����Ԫ��֮�䶼�б���������Ӧ��ԭͼ��������������֮�䲻���ڱߣ�Ҳ�������������ڣ�
2��ͼ��Ⱦɫ�����У�������Ҫ����ɫ������=����ŵ������
��ͨ���������ž��������ȫ��ͼ��

1.����ģ�� ����һ����n=100����
struct node{
    static const int N = 60; //���޸�

    bool G[N][N]; //��ʼ��
    int n, Max[N], Alt[N][N], ans;  // ���Ŵ�0��ʼ

    bool dfs(int cur, int tol){
        if(cur == 0){
            if(tol>ans){  // ��һ������ļ��������ԭ�еļ�����
                ans = tol;
                return 1;
            }
            return 0;
        }
        for(int i=0; i<cur; i++){
            if(cur-i+tol <= ans)return 0;
            int u = Alt[tol][i];
            if(Max[u]+tol <= ans)return 0;
            int nxt = 0;
            for(int j=i+1; j<cur; j++)
                if(G[u][Alt[tol][j]])Alt[tol+1][nxt++] = Alt[tol][j];
            if(dfs(nxt, tol+1)) return 1;
        }
        return 0;
    }

    int max_clique(){
        ans = 0;
        mst(Max, 0);
        for(int i=n-1; i>=0; i--){ // ����һ����,�����������ĵ�ӽ�������Щ����ܹ�������ţ�Ȼ��dfs�жϳ�һ����ʱ������
            int cur = 0;
            for(int j=i+1; j<n; j++)if(G[i][j])Alt[1][cur++] = j;
            dfs(cur, 1);
            Max[i] = ans;
        }
        return ans;
    }

};


2.��������̰��ģ��   ����һ��n=500
//loj 526
const int N = 505;

int n,g[N][N],a[N],del[N],ans,fin[N];
void go(){
    int i, j, k;
    for(i=0;i<n;i++)del[i]=0;
    for(k=i=0;i<n;i++)if(!del[i])for(k++,j=i+1;j<n;j++)if(!g[a[i]][a[j]])del[j]=1;
    if(k>ans)for(ans=k,i=j=0;i<n;i++)if(!del[i])fin[j++]=a[i];
}

ll val[N];
int  main(){
    scanf("%d", &n);  ans = 0;
    for(int i=0; i<n; i++)a[i] = i; //��ʼ��
    for(int i=0; i<n; i++)scanf("%lld", &val[i]);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j)continue;
            if(gcd(val[i], val[j]) != 1 || gcd(val[i]+1, val[j]+1) != 1)g[i][j] = 1; //����
        }
    }
    for(int turn=100; turn--; go())for(int i=0; i<n; i++)swap(a[i], a[rand()%n]);  //�������
    int i;
    for(printf("%d\n",ans),i=0; i<ans; i++)printf("%d ",fin[i]+1); //��������������һ���
    return 0;
}
