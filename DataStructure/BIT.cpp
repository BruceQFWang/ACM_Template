//经典例题poj2299
/*
 *好题 http://codeforces.com/contest/777/submission/25005987
 *单点替换，区间最值
 */

//单点修改， 区间查询(不仅可以区间求和还可以异或、最值等操作)
struct BIT{
    int n;
    ll c[N];
    void init(int _n){
        n=_n;
        for(int i=1;i<=n;i++)c[i] = 0;
    }
    void update(int p, ll x){  //单点更新 往叶子还是根更新看情况
        for(int i=p; i<=n; i+=i&-i)c[i] += x;
    }
    ll query(int p){ //区间查询
        ll ret = 0;
        for(int i=p; i>0; i-=i&-i)ret += c[i];
        return ret;
    }
}bit;

//区间修改， 单点查询
一开始接触树状数组时，只知道“单点更新，区间求和”的功能，没想到还有“区间更新，单点查询”的作用。

法一：
树状数组有两种用途（以一维树状数组举例）：
　　1.单点更新，区间查询（即求和）
　　　　单点更新时，是往树根（即c[n]）拓展
　　　　而区间查询时，是往叶子节点（即c[1]）拓展
　　2.区间更新，单点查询
　　　　区间更新时，是往叶子节点（即c[1]）拓展
　　　　单点查询时，往树根（即c[n]）拓展

(具体操作参考http://www.cnblogs.com/chenxiwenruo/p/3430920.html)
这两个操作只不过是在update()和query()方法中的+和-替换一下而已。
修改[a, b]，使得区间+1:
update(b,1);
update(a-1,-1);
查询点p
query(p)

法二：
其实也可以正向填表，和一般的查询和操作差不多，不过注意如何更新节点。
（具体操作参考http://blog.csdn.net/kenden23/article/details/29854527）
update和query不变
修改[a, b]，使得区间+1:
update(a,1);
update(b+1,-1);
查询点p
query(p)
