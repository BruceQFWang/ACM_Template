hdu 5647
题意：一个连通集的大小定义为它包含的结点个数，DZY想知道所有连通集的大小之和是多少。
In the second sample, the 4 edges are (1,2),(2,3),(2,4),(3,5). All the connected sets are {1},{2},{3},{4},{5},{1,2},{2,3},{2,4},{3,5},{1,2,3},{1,2,4},{2,3,4},{2,3,5},{1,2,3,4},{1,2,3,5},{2,3,4,5},{1,2,3,4,5}.
一共有13个连通集，大小之和为42个
思路：
其他的就不说了，主要说说如果采用 dfs 方法的话，这个关键的递推式是什么意思。
ans[u] = ans[u] * (sum[v] + 1) + ans[v] * sum[u]
（其中 u 是当前结点，v 是子结点。）
ans[u] 表示 u 在 u 结点处产生的所有集合里的元素个数。
sum[u] 表示以 u 为根节点的集合个数。
所以答案是sigma(ans[i])


ans[u] 由两部分构成。
1.u 结点处新产生的元素的贡献
2.v 结点原来的元素的贡献
先说ans[u] * (sum[v] + 1)。这里得出的就是第一部分的值。
其实这里应该写为ans[u]*sum[v] + ans[u]
因为每个元素都能在子结点的集合里出现一次，所以 ans[u]*sum[v]就得出了增加了结点 v 之后又新增的贡献，还要加上原来的。

ans[v]*sum[u]计算的是后一部分的贡献。
每个子结点的元素都能在 u 的集合里出现一次。
void dfs(int u, int fa) {
    for (int v : G[u]) if (v != fa) {
        dfs(v, u);
        dp[u][1] = (dp[u][1] * (dp[v][0] + 1)) % MOD + dp[u][0]*dp[v][1]%MOD;
        dp[u][1] %= MOD;
        dp[u][0] = dp[u][0] * (dp[v][0] + 1) % MOD;
    }
}

for (int i = 1; i <= n; ++i) {
        G[i].clear();
        dp[i][0] = dp[i][1] = 1;
}
dfs(1, -1);
LL ans = 0;
for (int i = 1; i <= n; ++i) {
        ans += dp[i][1];
        if (ans > MOD) ans -= MOD;
 }
