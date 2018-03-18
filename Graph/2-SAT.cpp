//不矛盾连一起,即必选的连一起  最后判断A与A'是否在同一个强连通分量内
模型一：两者（A，B）不能同时取
那么选择了A就只能选择B’，选择了B就只能选择A’
连边A→B’，B→A’

模型二：两者（A，B）不能同时不取,即至少取一个
　　那么选择了A’就只能选择B，选择了B’就只能选择A
　　连边A’→B，B’→A

模型三：两者（A，B）要么都取，要么都不取
　　那么选择了A，就只能选择B，选择了B就只能选择A，选择了A’就只能选择B’，选择了B’就只能选择A’
　　连边A→B，B→A，A’→B’，B’→A’

模型四：两者（A，A’）必取A
　　那么，那么，该怎么说呢？先说连边吧。
　　连边A’→A

例题：
poj2723
题意：m个门，每个门上有两把锁，打开一个就可以通过
           2n个钥匙，每两个绑在一起，只能选用一个 ，选了一个，另一个就被废弃。
           问最多可以通过几扇门？
思路：2-sat问题关键在建图，2-sat对每个事物都有两个选项 ,选和不选.
可以这么建：
每把钥匙有两个状态(用或不用)，把这作为2-sat的两个选项
然后是加条件，a、b绑在一起，则选a就不选b，选b就不选a，建边a->!b,b->!a
c、d在同一个门上，则不开c就开d，不开d就开c，建边!c->d,!d->c
然后二分最多的开门数就可以了

部分代码：
const int maxn = 10010; //点数
int k[maxn][2], lock[maxn][2];

bool check(int num){
    init();
    for(int i=1; i<=n; i++){
        addedge(k[i][0], k[i][1]+2*n);
        addedge(k[i][1], k[i][0]+2*n);
    }
    for(int i=1; i<=num; i++){
        addedge(lock[i][0]+2*n, lock[i][1]);
        addedge(lock[i][1]+2*n, lock[i][0]);
    }
    for(int i=1; i<=4*n; i++)if(!dfn[i])Tarjan(i);
    for(int i=1; i<=2*n; i++)if(belong[i] == belong[i+2*n])return 0;
    return 1;
}

int  main(){
    while(~scanf("%d%d", &n, &m)){
        if(!n && !m)break;
        for(int i=1; i<=n; i++)scanf("%d%d", &k[i][0], &k[i][1]), k[i][0]++, k[i][1]++;
        for(int i=1; i<=m; i++)scanf("%d%d", &lock[i][0], &lock[i][1]), lock[i][0]++, lock[i][1]++;

        int ans = 0, l = 0, r = m;
        while(l <= r){
            int mid = (l+r)>>1;
            if(check(mid))l = mid+1, ans = mid;
            else r = mid-1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
