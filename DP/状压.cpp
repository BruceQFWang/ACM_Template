二进制运算：
1、将a的第k位修改为1：a |= 1<<k;
2、将a的第k位修改为0：a &= ~(1<<k);
3、取第k位：a>>k & 1;
4、for (int S0 = S; S0; S0 = S&(S0 - 1))   //  对于集合S 枚举S0为子集


例题uva 11825 - Hackers' Crackdown
题意：
有一个由编号0~n-1的n台计算机组成的网络，一共有n种服务，每台计算机上都运行着全部服务，对于每台计算机，你可以选择停止一项服务，这个行为会导致与这台计算机和与他相连的其他计算机上的这项服务都停止（原来已经停止的继续保持停止状态）。求最多能使多少个服务瘫痪（即没有任何一台计算机在运行这项服务）。
分析：
题目说白了，就是：
把n个集合p[i],0<=i<n分成尽量多组，使得每组中各个集合的并集为全集。
利用状态压缩，记录每个节点运行的服务。由于数据大小就16所以直接可以用int范围数字表示一个集合。
然后预处理下cover，处理16个节点组成的各个集合会带来的服务效果。
然后dp，如果cover[S0] == all (all全为1) 那么是S-S0 的部分也有可能终止服务 ，dp[S] = max(dp[S], dp[S^S0]+1)。

int n, dp[1<<16], mask[1<<16], cover[1<<16];

int  main(){
    int kase = 0;
    while(~scanf("%d", &n) && n){
        for(int i=0; i<n; i++){
            int m;
            scanf("%d", &m);
            mask[i] = (1<<i);
            while(m--){
                int x;
                scanf("%d", &x);
                mask[i] |= (1<<x);
            }
        }
        for(int S=0; S<(1<<n); S++){ //预处理几个集合的并
            cover[S] = 0;
            for(int i=0; i<n; i++)if((S>>i)&1)cover[S] |= mask[i];
        }
        int tol = (1<<n)-1;
        for(int S=0; S<(1<<n); S++){
            dp[S] = 0;
            for(int S0=S; S0; S0=(S0-1)&S){
                if(cover[S0] == tol)dp[S] = max(dp[S], dp[S^S0]+1);
            }
        }
        printf("Case %d: %d\n", ++kase, dp[tol]);
    }
    return 0;
}
