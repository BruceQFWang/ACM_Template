![image](https://github.com/Cyberstk/ACM_Template/blob/master/Tool/bitset.jpg)

题意：给一个DAG，每次可以删点或者加点，问总存在路径的点对的个数
思路：

可以用矩阵维护u,v之间的路径条数，实现起来很麻烦。
这里可以用bitset优化直接搞过去
bitset优化floyd 复杂度为O(T*q*n^3/64)
const int N = 305;

int n, m, q;
bitset<N>path[N];
bool g[N][N];
int col[N];

void floyd(){
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++){
        if(path[j][i])path[j] |= path[i];
    }
}

int  main(){
    while(~scanf("%d%d%d", &n, &m, &q)){
        mst(col, 0);  mst(g, 0);
        for(int i=1; i<=m; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            g[u][v] = 1;
        }
        while(q--){
            int u; scanf("%d", &u);
            for(int i=1; i<=n; i++)path[i].reset();
            col[u] = 1-col[u];
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++){
                    if(g[i][j] && !col[i] && !col[j])
                        path[i].set(j);
                }
            floyd();
            int ans = 0;
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    if(path[i].test(j))ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}
