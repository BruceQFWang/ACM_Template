(1)边双连通分量
若一个无向图中的去掉任意一条边都不会改变此图的连通性，即不存在桥，则称作边双连通图。一个无向图中的每一个极大边双连通子图称作此无向图的边双连通分量。
连接两个边双连通分量的边即是桥。

(2)点双连通分量
若一个无向图中的去掉任意一个节点都不会改变此图的连通性，即不存在割点，则称作点双连通图。一个无向图中的每一个极大点双连通子图称作此无向图的点双连通分量。
注意一个割点属于多个点双连通分量。

图的连通度分为点连通度和边连通度：

(3)点连通度：只许删点，求至少要删掉几个点（当然，s和t不能删去，这里保证原图中至少有三个点）；
(4)边连通度：只许删边，求至少要删掉几条边。
并且，有向图和无向图的连通度求法不同，因此还要分开考虑（对于混合图，只需将其中所有的无向边按照无向图的办法处理、有向边按照有向图的办法处理即可）。

【1】有向图的边连通度：
这个其实就是最小割问题。以s为源点，t为汇点建立网络，原图中的每条边在网络中仍存在，容量为1，求该网络的最小割（也就是最大流）的值即为原图的边连通度。
【2】有向图的点连通度：
需要拆点。建立一个网络，原图中的每个点i在网络中拆成i'与i''，有一条边<i', i''>，容量为1 （<s', s''>和<t', t''>例外，容量为正无穷）。原图中的每条边<i, j>在网络中为边<i'', j'>，
容量为正无穷。以s'为源点、t''为汇点求最大流，最大流的值即为原图的点连通度。
说明：最大流对应的是最小割。显然，容量为正无穷的边不可能通过最小割，也就是原图中的边和s、t两个点不能删去；若边<i, i''>通过最小割，则表示将原图中的点i删去。
【3】无向图的边连通度：
将图中的每条边(i, j)拆成<i, j>和<j, i>两条边，再按照有向图的办法（【1】）处理；
【4】无向图的点连通度：
将图中的每条边(i, j)拆成<i, j>和<j, i>两条边，再按照有向图的办法（【2】）处理。
例题poj1966   代码：
while(~scanf("%d%d", &n, &m)){
        init();
        for(int i=1; i<=n; i++)addedge(i, i+n, 1);
        for(int i=1; i<=m; i++){
            int u, v;
            scanf(" (%d,%d)", &u, &v);
            addedge(u+n, v, inf);
            addedge(v+n, u, inf);
        }
        int ans = n;
        for(int i=1; i<n; i++){
            for(int j=0; j<tol; j++)e[j].flow = 0;
            ans = min(ans, dinic(n, i, 2*n+1));
        }
        printf("%d\n", ans);
    }

(5)构造双连通图
每次找到两个叶子他们的最近公共祖先最远，然后给这两个叶子连一条边，然后依次找出这样的点，所以是(leaf+1)/2
