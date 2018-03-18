1.单点更新
hdu1166 敌兵布阵
线段树功能:update:单点增减 query:区间求和
#include<bits/stdc++.h>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;

const int N=55555;
int sum[N<<2];//四倍

void PushUp(int rt){
  sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void build(int l,int r,int rt){
  if(l==r){
    scanf("%d",&sum[rt]);
    return ;
  }
  int m=(l+r)>>1;
  build(lson);
  build(rson);
  PushUp(rt);
}

void update(int p,int add,int l,int r,int rt){
  if(l==r){
    sum[rt]+=add;
    return ;
  }
  int m=(l+r)>>1;
  if(p<=m)update(p, add, lson);
  else update(p, add, rson);
  PushUp(rt);
}

int query(int L,int R,int l,int r,int rt){
  if(L<=l && r<=R){
    return sum[rt];
  }
  int m=(l+r)>>1;
  int ret=0;
  if(L<=m)ret+=query(L, R, lson);
  if(R>m)ret+=query(L, R, rson);
  return ret;
}

int main(){
  int T,n;
  scanf("%d",&T);
  for(int cas=1; cas<=T; cas++){
    printf("Case %d:\n",cas);
    scanf("%d",&n);
    build(1, n, 1);
    char op[10];
    while(scanf("%s",op)){
      if(op[0]=='E')break;
      int a,b;
      scanf("%d%d",&a,&b);
      if(op[0]=='Q')printf("%d\n",query(a, b, 1, n, 1));
      else if(op[0]=='S')update(a, -b, 1, n , 1);
      else update(a, b, 1, n, 1);
    }
  }
  return 0;
}

hdu1754 I Hate It
线段树功能:update:单点替换 query:区间最值
#include<bits/stdc++.h>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;

const int N=222222;
int Max[N<<2];

void PushUp(int rt){
  Max[rt]=max(Max[rt<<1],Max[rt<<1|1]);
}

void build(int l,int r,int rt){
  if(l==r){
    scanf("%d",&Max[rt]);
    return ;
  }
  int m=(l+r)>>1;
  build(lson);
  build(rson);
  PushUp(rt);
}

void update(int p,int re,int l,int r,int rt){
  if(l==r){
    Max[rt]=re;
    return ;
  }
  int m=(l+r)>>1;
  if(p<=m)update(p, re, lson);
  else update(p, re, rson);
  PushUp(rt);
}

int query(int L,int R,int l,int r,int rt){
  if(L<=l && r<=R){
    return Max[rt];
  }
  int m=(l+r)>>1;
  int ret=0;
  if(L<=m)ret=max(ret, query(L, R, lson));
  if(R>m)ret=max(ret,query(L, R, rson));
  return ret;
}

int main(){
  int n,m;
  while(~scanf("%d%d",&n,&m)){
    build(1, n, 1);
    int a,b;
    char op[2];
    while(m--){
      scanf("%s%d%d",op,&a,&b);
      if(op[0]=='Q')printf("%d\n",query(a, b, 1, n, 1));
      else update(a, b, 1, n, 1);
    }
  }
  return 0;
}

2.区间更新
用延迟标记使得更新延迟到下次需要 更新or询问到的时候
hdu1698 Just a Hook
题意：对一个初始值都是1的区间[1,n]进行一些区间更新操作，每次将一个区间[a,b]的值更新为c，问更新后的区间和
线段树功能:update:成段替换 (由于只query一次总区间,所以可以直接输出1结点的信息)
#include<bits/stdc++.h>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
using namespace std;

const int N=111111;
int sum[N<<2];
int col[N<<2];

void PushUp(int rt){
  sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void PushDown(int rt,int m){
  if(col[rt]){
    col[rt<<1]=col[rt<<1|1]=col[rt];
    sum[rt<<1]=(m- (m>>1)) * col[rt];
    sum[rt<<1|1]=(m>>1) * col[rt];
    col[rt]=0;
  }
}

void build(int l,int r,int rt){
  col[rt]=0;
  sum[rt]=1;
  if(l==r)return ;
  int m=(l+r)>>1;
  build(lson);
  build(rson);
  PushUp(rt);
}

void update(int L,int R,int c,int l,int r,int rt){
  if(L<=l && r<=R){
    col[rt]=c;
    sum[rt]=c*(r-l+1);
    return ;
  }
  PushDown(rt, r-l+1);
  int m=(l+r)>>1;
  if(L<=m)update(L, R, c, lson);
  if(R>m) update(L, R, c, rson);
  PushUp(rt);
}

int main(){
  int T,n,m;
  scanf("%d",&T);
  for(int cas=1; cas<=T; cas++){
    scanf("%d%d",&n,&m);
    build(1, n, 1);
    while(m--){
      int a,b,c;
      scanf("%d%d%d",&a,&b,&c);
      update(a, b, c, 1, n, 1);
    }
    printf("Case %d: The total value of the hook is %d.\n",cas,sum[1]);
  }
  return 0;
}

poj3468 A Simple Problem with Integers
题意：C的时候在区间[a,b]之间，每个元素增加一个c。Q的时候求出[a,b]区间元素的和。
线段树功能:update:成段增减 query:区间求和
//G++2594ms C++1735ms
#include <cstdio>
#include <algorithm>
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define ll long long
using namespace std;

const int N=111111;
ll sum[N<<2];
ll add[N<<2];

void PushUp(int rt){
  sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void PushDown(int rt,int m){
  if(add[rt]){
    add[rt<<1]+=add[rt];
    add[rt<<1|1]+=add[rt];
    sum[rt<<1]+=(m- (m>>1)) * add[rt];
    sum[rt<<1|1]+=(m>>1) * add[rt];
    add[rt]=0;
  }
}

void build(int l,int r,int rt){
  add[rt]=0;
  if(l==r){
    scanf("%lld",&sum[rt]);
    return ;
  }
  int m=(l+r)>>1;
  build(lson);
  build(rson);
  PushUp(rt);
}

void update(int L,int R,int c,int l,int r,int rt){
  if(L<=l && r<=R){
    add[rt]+=c;
    sum[rt]+=(ll) c*(r-l+1);
    return ;
  }
  PushDown(rt, r-l+1);
  int m=(l+r)>>1;
  if(L<=m)update(L, R, c, lson);
  if(R>m) update(L, R, c, rson);
  PushUp(rt);
}

ll query(int L,int R,int l,int r,int rt){
  if(L<=l && r<=R){
    return sum[rt];
  }
  PushDown(rt, r-l+1);
  int m=(l+r)>>1;
  ll ret=0;
  if(L<=m)ret+=query(L, R, lson);
  if(R>m)ret+=query(L, R, rson);
  return ret;
}

int main(){
  int N,Q;
  scanf("%d%d",&N,&Q);
  build(1, N, 1);
  while(Q--){
    char op[2];
    int a,b,c;
    scanf("%s",op);
    if(op[0]=='Q'){
      scanf("%d%d",&a,&b);
      printf("%lld\n",query(a, b, 1, N, 1));
    }else{
      scanf("%d%d%d",&a,&b,&c);
      update(a, b, c, 1, N, 1);
    }
  }
  return 0;
}

bzoj 1798
有如下三种操作形式： (1)把数列中的一段数全部乘一个值; (2)把数列中的一段数全部加一个值; (3)询问数列中的一段数的和，由于答案可能很大，你只需输出这个数模P的值。
双lazy线段树

这类题目主要在于要维护双lazy的关系
1. 建树时维护区间和，把乘的lazy初始为1.
2. 对于一个节点d乘上一个数c,则把该区间的累加和，乘的lazy，加的lazy都乘上c。
3. 对于一个节点d加上一个数c，则把该区间的区间和加上区间的数的个数乘上c,加的lazy加上c。
4. 上诉所有操作都在模P意义下进行。
代码：
const int N = 1e5+5;

ll p;
ll sum[N<<2], add[N<<2], mul[N<<2];
int n, m;

void PushUp(int rt){
    sum[rt] = (sum[rt<<1]+sum[rt<<1|1])%p;
}

void PushDown(int rt, int m){
    if(mul[rt] == 1 && add[rt] == 0)return ;
    mul[rt<<1] = (mul[rt<<1]*mul[rt])%p;
    mul[rt<<1|1] = (mul[rt<<1|1]*mul[rt])%p;
    add[rt<<1] = (add[rt<<1]*mul[rt]+add[rt])%p;
    add[rt<<1|1] = (add[rt<<1|1]*mul[rt]+add[rt])%p;
    sum[rt<<1] = (sum[rt<<1]*mul[rt]+(m-(m>>1))*add[rt])%p;
    sum[rt<<1|1] = (sum[rt<<1|1]*mul[rt]+1LL*(m>>1)*add[rt])%p;
    mul[rt] = 1;
    add[rt] = 0;
}

void build(int l, int r, int rt){
    mul[rt] = 1;
    add[rt] = 0;
    sum[rt] = 0;
    if(l == r){
        scanf("%lld", &sum[rt]);
        sum[rt] %= p;
        return ;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    PushUp(rt);
}

void update(int L, int R, int l, int r, int rt, ll mulval, ll addval){
    if(L <= l && r <= R){
        mul[rt] = (mul[rt]*mulval)%p;
        add[rt] = (add[rt]*mulval+addval)%p;
        sum[rt] = (sum[rt]*mulval+(r-l+1)*addval)%p;
        return ;
    }
    PushDown(rt, r-l+1);
    int m = (l+r)>>1;
    if(L <= m)update(L, R, lson, mulval, addval);
    if(R > m)update(L, R, rson, mulval, addval);
    PushUp(rt);
}

ll query(int L, int R, int l, int r, int rt){
    if(L <= l && r <= R)return sum[rt]%p;
    PushDown(rt, r-l+1);
    int m = (l+r)>>1;
    ll ret = 0;
    if(L <= m)ret += query(L, R, lson), ret %= p;
    if(R > m)ret += query(L, R, rson), ret %= p;
    return ret%p;
}

int  main(){
    scanf("%d%lld", &n, &p);
    build(1, n, 1);
    scanf("%d", &m);
    while(m--){
        int op, a, b;
        ll c;
        scanf("%d%d%d", &op, &a, &b);
        if(op == 1){
            scanf("%lld", &c);
            update(a, b, 1, n, 1, c%p, 0);
        }
        else if(op == 2){
            scanf("%lld", &c);
            update(a, b, 1, n, 1, 1, c%p);
        }
        else{
            printf("%lld\n", query(a, b, 1, n, 1));
        }
    }
    return 0;
}

3.区间合并
题意:1 a:询问是不是有连续长度为a的空房间,有的话住进最左边
2 a b:将[a,a+b-1]的房间清空
思路:记录区间中最长的空房间
线段树操作:update:区间替换 query:询问满足条件的最左断点
//lsum表示从最左边开始数(最长前缀)，rsum表示从最右边开始数(最长后缀)
//msum表示区间内最长子串  PushUp的时候扩展区间
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1

const int maxn = 55555;
int lsum[maxn<<2] , rsum[maxn<<2] , msum[maxn<<2];
int cover[maxn<<2];

void PushDown(int rt,int m) {
    if (cover[rt] != -1) {
        cover[rt<<1] = cover[rt<<1|1] = cover[rt];
        msum[rt<<1] = lsum[rt<<1] = rsum[rt<<1] = cover[rt] ? 0 : m - (m >> 1);
        msum[rt<<1|1] = lsum[rt<<1|1] = rsum[rt<<1|1] = cover[rt] ? 0 : (m >> 1);
        cover[rt] = -1;
    }
}

void PushUp(int rt,int m) {
    lsum[rt] = lsum[rt<<1];
    rsum[rt] = rsum[rt<<1|1];
    if (lsum[rt] == m - (m >> 1)) lsum[rt] += lsum[rt<<1|1];
    if (rsum[rt] == (m >> 1)) rsum[rt] += rsum[rt<<1];
    msum[rt] = max(lsum[rt<<1|1] + rsum[rt<<1] , max(msum[rt<<1] , msum[rt<<1|1]));
}

void build(int l,int r,int rt) {
    msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
    cover[rt] = -1;
    if (l == r) return ;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}

void update(int L,int R,int c,int l,int r,int rt) {
    if (L <= l && r <= R) {
        msum[rt] = lsum[rt] = rsum[rt] = c ? 0 : r - l + 1;
        cover[rt] = c;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt , r - l + 1);
}

int query(int w,int l,int r,int rt) { //没有区间[L, R]的问题
    if (l == r) return l;
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (msum[rt<<1] >= w) return query(w , lson);
    else if (rsum[rt<<1] + lsum[rt<<1|1] >= w) return m - rsum[rt<<1] + 1;
    return query(w , rson);
}

int main() {
    int n , m;
    scanf("%d%d",&n,&m);
    build(1 , n , 1);
    while (m --) {
        int op , a , b;
        scanf("%d",&op);
        if (op == 1) {
            scanf("%d",&a);
            if (msum[1] < a) puts("0");
            else {
                int p = query(a , 1 , n , 1);
                printf("%d\n",p);
                update(p , p + a - 1 , 1 , 1 , n , 1);
            }
        } else {
            scanf("%d%d",&a,&b);
            update(a , a + b - 1 , 0 , 1 , n , 1);
        }
    }
    return 0;
}

有n个村庄，每个操作：
D x 表示摧毁x
Q x 询问与x相连接的有多少个
R 恢复之前摧毁的一个城市
询问区间内最长连通城市的长度
线段树操作:update:单点修改 query:询问满足条件的最长区间
#include <bits/stdc++.h>
using  namespace  std;

#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
typedef pair <int, int> pii;
const int inf = 0x3f3f3f3f;
const int N = 5e4+5;
int lsum[N<<2], rsum[N<<2], msum[N<<2];
int n, m;
int stk[N], cnt;

void PushUp(int rt,int m) {
    lsum[rt] = lsum[rt<<1];
    rsum[rt] = rsum[rt<<1|1];  //m - (m >> 1)  (m >> 1) 对应上面的PushDown,一般要修改
    if (lsum[rt] == m-(m>>1)) lsum[rt] += lsum[rt<<1|1];//左边往右扩展
    if (rsum[rt] == (m>>1)) rsum[rt] += rsum[rt<<1];//右边往左扩展
    msum[rt] = max(lsum[rt<<1|1] + rsum[rt<<1] , max(msum[rt<<1] , msum[rt<<1|1]));
}

void build(int l, int r, int rt){
    msum[rt] = lsum[rt] = rsum[rt] = r-l+1;
    if (l == r) return ;
    int m = (l+r)>>1;
    build(lson);
    build(rson);
}

void update(int p, int c, int l, int r, int rt) {
    if(l == r){
        msum[rt] = lsum[rt] = rsum[rt] = c;
        return ;
    }
    int m = (l+r)>>1;
    if (p <= m) update(p, c, lson);
    else update(p, c, rson);
    PushUp(rt, r-l+1);
}

int query(int p, int l, int r, int rt) {
    if(l == r || msum[rt] == 0 || msum[rt] == r-l+1)//改了会TLE
        return msum[rt];
    int m = (l+r)>>1;
    if(p <= m){
        if(p >= m-rsum[rt<<1]+1)
            return query(p, lson)+query(m+1, rson);//特别注意这里的m+1，不能取m
        else
            return query(p, lson);
    }
    else{
        if(p <= m+lsum[rt<<1|1]){   //不减1 rt<<1|1本身就少1
            return query(p, rson)+query(m, lson); //特别注意这里的m，要取等号
        }
        else query(p, rson);
    }
}

int  main(){
    while(~scanf("%d%d", &n, &m)){
        build(1, n, 1);
        cnt = 0;
        while(m--){
            char op[10];
            int x;
            scanf("%s", op);
            if(op[0] == 'D'){
                scanf("%d", &x);
                stk[cnt++] = x;
                update(x, 0, 1, n, 1);
            }
            else if(op[0] == 'R'){
                x = stk[--cnt];
                update(x, 1, 1, n, 1);
            }
            else{
                scanf("%d", &x);
                printf("%d\n", query(x, 1, n, 1));
            }
        }
    }
    return 0;
}


将结构lsum,rsum,msum封装成结构体
电科17数据结构G http://mozhu.today/#/contest/show/155
求区间最大子段和，支持单点修改
这题结构体非常好写
#define max3(a, b, c) max(a, max(b, c))
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1

struct node{
    int ls, rs, ms, sum;
}tree[N<<2];
int n, m;

void PushUp(int rt){
    tree[rt].sum = tree[rt<<1].sum+tree[rt<<1|1].sum;
    tree[rt].ls = max(tree[rt<<1].ls, tree[rt<<1].sum+tree[rt<<1|1].ls);
    tree[rt].rs = max(tree[rt<<1|1].rs, tree[rt<<1|1].sum+tree[rt<<1].rs);
    tree[rt].ms = max3(tree[rt<<1|1].ls+tree[rt<<1].rs, tree[rt<<1].ms, tree[rt<<1|1].ms);
}

void build(int l, int r, int rt){
    if(l == r){
        int tmp;
        scanf("%d", &tmp);
        tree[rt].ls = tree[rt].rs = tree[rt].ms = tree[rt].sum = tmp;
        return ;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    PushUp(rt);
}

void update(int p, int c, int l, int r, int rt){
    if(l == r){
        tree[rt].ls = tree[rt].rs = tree[rt].ms = tree[rt].sum = c;
        return ;
    }
    int m = (l+r)>>1;
    if(p <= m)update(p, c, lson);
    else update(p, c, rson);
    PushUp(rt);
}

node query(int L, int R, int l, int r, int rt){
    if(L <= l && r <= R)
        return tree[rt];
    int m = (l+r)>>1;
    if(L <=m && m < R){
        node tmp1 = query(L, R, lson), tmp2 = query(L, R, rson), ret;
        ret.sum = tmp1.sum+tmp2.sum;
        ret.ls = max(tmp1.ls, tmp1.sum+tmp2.ls);
        ret.rs = max(tmp2.rs, tmp2.sum+tmp1.rs);
        ret.ms = max3(tmp2.ls+tmp1.rs, tmp1.ms, tmp2.ms);
        return ret;
    }
    else if(L <= m)return query(L, R, lson);
    else return query(L, R, rson);
}

int  main(){
    scanf("%d%d", &n, &m);
    build(1, n, 1);
    while(m--){
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);
        if(op == 1)printf("%d\n", query(a, b, 1, n, 1).ms);
        else update(a, b, 1, n, 1);
    }
    return 0;
}


4.扫描线
矩形面积并： 参考http://blog.csdn.net/u013480600/article/details/22548393
//hdu1542   输入对角的两点，坐标是浮点数
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 2222;

int cnt[maxn << 2];
double sum[maxn << 2];
double X[maxn];
struct Seg {
    double h , l , r;//扫描线的左右端点x坐标,扫描线的高度
    int s; //为1或-1,标记扫描线是矩形的上位还是下位边.
    Seg(){}
    Seg(double a,double b,double c,int d) : l(a) , r(b) , h(c) , s(d) {}
    bool operator < (const Seg& rhs) const {
        return h < rhs.h;
    }
}ss[maxn];

void PushUp(int rt,int l,int r) {
    if (cnt[rt]) sum[rt] = X[r+1] - X[l];
    else if (l == r) sum[rt] = 0;
    else sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void update(int L,int R,int c,int l,int r,int rt) { //区间增减
    if (L <= l && r <= R) {
        cnt[rt] += c;
        PushUp(rt , l , r);
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt , l , r);
}

int main() {
    int n , cas = 1;
    while (~scanf("%d",&n) && n) {
        int m = 0;
        while (n --) {
            double a , b , c , d;
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            X[m] = a;
            ss[m++] = Seg(a , c , b , 1);
            X[m] = c;
            ss[m++] = Seg(a , c , d , -1);
        }
        sort(X , X + m); //X按从小到大排序
        sort(ss , ss + m);//按h值从小到大排序
        int k = 1; //对X去重,并且用k表示一共有多少个X
        for (int i = 1 ; i < m ; i ++) {
            if (X[i] != X[i-1]) X[k++] = X[i];
        }//当我们需要找到第i个区域的两端点坐标时,只需要X[i]和X[i+1]
        memset(cnt , 0 , sizeof(cnt));//cnt: >=0时表示本节点控制的区域内下位边个数-上位边个数的结果.
        //如果==-1时,表示本节点左右子树的上下位边数不一致.
        memset(sum , 0 , sizeof(sum)); //sum: 本节点控制的区域内cnt值不为0的区域总长度.
        double ret = 0;
        for (int i = 0 ; i < m - 1 ; i ++) {
            int l = lower_bound(X, X+k, ss[i].l)-X;
            int r = lower_bound(X, X+k, ss[i].r)-X-1;
            if (l <= r) update(l , r , ss[i].s , 0 , k - 1, 1);//线段树从0~k-1,也就是X的下标
            ret += sum[1] * (ss[i+1].h - ss[i].h);
        }
        printf("Test case #%d\n", cas++);
        printf("Total explored area: %.2f\n\n", ret);
    }
    return 0;
}

矩阵周长：参考http://blog.csdn.net/u013480600/article/details/22581063
//poj1177 或者 hdu 1828  坐标的范围的[-10000,10000]的整数
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 22222;

struct Seg{
    int l , r , h , s;
    Seg() {}
    Seg(int a,int b,int c,int d):l(a) , r(b) , h(c) , s(d) {}
    bool operator < (const Seg &cmp) const {
        return h < cmp.h;
    }
}ss[maxn];
bool lbd[maxn<<2] , rbd[maxn<<2];
int numseg[maxn<<2];
int cnt[maxn<<2];
int len[maxn<<2];

void PushUP(int rt,int l,int r) {
    if (cnt[rt]) {
        lbd[rt] = rbd[rt] = 1;
        len[rt] = r - l + 1;
        numseg[rt] = 2;
    } else if (l == r) {
        len[rt] = numseg[rt] = lbd[rt] = rbd[rt] = 0;
    } else {
        lbd[rt] = lbd[rt<<1];
        rbd[rt] = rbd[rt<<1|1];
        len[rt] = len[rt<<1] + len[rt<<1|1];
        numseg[rt] = numseg[rt<<1] + numseg[rt<<1|1];
        if (lbd[rt<<1|1] && rbd[rt<<1]) numseg[rt] -= 2;//两条线重合
    }
}

void update(int L,int R,int c,int l,int r,int rt) {
    if (L <= l && r <= R) {
        cnt[rt] += c;
        PushUP(rt , l , r);
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUP(rt , l , r);
}

int main() {
    int n;
    while (~scanf("%d",&n)) {
        int m = 0;
        int lbd = 10000, rbd = -10000;
        for (int i = 0 ; i < n ; i ++) {
            int a , b , c , d;
            scanf("%d%d%d%d",&a,&b,&c,&d);
            lbd = min(lbd , a);
            rbd = max(rbd , c);
            ss[m++] = Seg(a , c , b , 1);
            ss[m++] = Seg(a , c , d , -1);
        }
        sort(ss , ss + m);
        int ret = 0 , last = 0;
        for (int i = 0 ; i < m ; i ++) {
            if (ss[i].l < ss[i].r) update(ss[i].l , ss[i].r - 1 , ss[i].s , lbd , rbd - 1 , 1);
            ret += numseg[1] * (ss[i+1].h - ss[i].h);
            ret += abs(len[1] - last);
            last = len[1];
        }
        printf("%d\n",ret);
    }
    return 0;
}

5.均摊线段树
其实就是在需要均摊的更新里面多加个check

例题1：
uoj 228

//区间加，区间最值，区间开根号操作
/*首先开根号很快就能变成1
 *对于一次区间开根：
 *设最大值为mx，最小值为mn，如果mx-mn=sqrt(mx)-sqrt(mn)，就可以看成区间减法
 *因为减小的值是一样的
 */
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
const int N = 1e5+5;
int n, m;
ll sum[N<<2], add[N<<2], Max[N<<2], Min[N<<2];

void PushUp(int rt){
    sum[rt] = sum[rt<<1]+sum[rt<<1|1];
    Max[rt] = max(Max[rt<<1], Max[rt<<1|1]);
    Min[rt] = min(Min[rt<<1], Min[rt<<1|1]);
}

void PushDown(int rt,int m){
    if(add[rt]){
        add[rt<<1] += add[rt], add[rt<<1|1] += add[rt];
        sum[rt<<1] += (m- (m>>1)) * add[rt], sum[rt<<1|1] += (m>>1) * add[rt];
        Max[rt<<1] += add[rt], Max[rt<<1|1] += add[rt];
        Min[rt<<1] += add[rt], Min[rt<<1|1] += add[rt];
        add[rt] = 0;
    }
}

void build(int l,int r,int rt){
    add[rt] = 0;
    if(l == r){
        scanf("%lld", &sum[rt]);
        Max[rt] = Min[rt] = sum[rt];
        return ;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    PushUp(rt);
}

void update(int L,int R,int c,int l,int r,int rt){
    if(L <= l && r <= R){
        add[rt] += c;
        sum[rt] += 1LL*c*(r-l+1);
        Min[rt] += c;
        Max[rt] += c;
        return ;
    }
    PushDown(rt, r-l+1);
    int m = (l+r)>>1;
    if(L <= m)update(L, R, c, lson);
    if(R > m) update(L, R, c, rson);
    PushUp(rt);
}

ll query(int L,int R,int l,int r,int rt){
    if(L <= l && r <= R){
        return sum[rt];
    }
    PushDown(rt, r-l+1);
    int m = (l+r)>>1;
    ll ret = 0;
    if(L <= m)ret += query(L, R, lson);
    if(R > m)ret += query(L, R, rson);
    return ret;
}

void Sqrt(int L, int R, int l, int r, int rt){
    if(L <= l && r <= R){
        ll mx = Max[rt], mn = Min[rt];
        if(((ll)sqrt(mx)-(ll)sqrt(mn)) == (mx-mn)){ //先把sqrt转化成ll
            ll v = (ll)sqrt(mx)-mx;
            add[rt] += v;
            sum[rt] += v*(r-l+1);
            Min[rt] += v;
            Max[rt] += v;
            return ;
        }
    }
    PushDown(rt, r-l+1);
    int m = (l+r)>>1;
    if(L <= m)Sqrt(L, R, lson);
    if(R > m)Sqrt(L, R, rson);
    PushUp(rt);
}

int  main(){
    scanf("%d%d", &n, &m);
    build(1, n, 1);
    while(m--){
        int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1){
            scanf("%d", &x);
            update(l, r, x, 1, n, 1);
        }
        else if(op == 2){
            Sqrt(l, r, 1, n, 1);
        }
        else{
            printf("%lld\n", query(l, r, 1, n, 1));
        }
    }
    return 0;
}

