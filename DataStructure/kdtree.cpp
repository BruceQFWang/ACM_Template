通俗理解：
每次二分区间内点的横坐标或者纵坐标，然后以mid为界，两边分别处理。
每个结点维护四个方向上的控制范围内的最值，画个图yy一下，所以保存四个值：
控制范围内纵坐标的最大最小值，横坐标的最大最小值。再存一下这个点本身的横纵坐标。
mid可以理解成这个区间的首领。
为了维护上述操作，我们需要用到nth_element这个STL，作用的话可以百度一下。
接着递归往下建就可以了，注意存一下每个结点控制区间下的子区间的控制节点
（可以理解成子区间内的两个首领）。

复杂度：
kd-tree的构树时间复杂度是O(nlogn)，空间复杂度和线段树一样，单个添加操作的时间复杂度是O(logn)，单个询问的时间复杂度是O(n^(1-1/k)) (k是维度)

具体步骤
1.按照维度依次选取中位数，建树，代码过程大概和线段树类似
2.选取估价函数作为查询的条件

估价函数：
欧几里得距离下界：
sqr(max(max(X−x.Max[0],x.Min[0]−X),0))+sqr(max(max(Y−x.Max[1],x.Min[1]−Y),0))
或者sqr(X−x.Max[0])+sqr(x.Min[0]−X)+sqr(Y−x.Max[1])+sqr(x.Min[1]−Y)
曼哈顿距离下界：
max(x.Min[0]−X,0)+max(X−x.Max[0],0)+max(x.Min[1]−Y,0)+max(Y−x.Max[1],0)
欧几里得距离上界：
max(sqr(X−x.Min[0]),sqr(X−x.Max[0]))+max(sqr(Y−x.Min[1]),sqr(Y−x.Max[1])
曼哈顿距离上界：
max(abs(X−x.Max[0]),abs(x.Min[0]−X))+max(abs(Y−x.Max[1]),abs(x.Min[1]−Y))
(其中#define sqr(a) (a)*(a)   )

例题： hdu2966  bzoj1941  bzoj2648

1. bzoj1941
题意：给定n个点，从中找一个点，使得其他所有点到它距离的最大值与最小值之差最小。
思路：利用KD-Tree暴力求出每个点的答案（找离它最近的点以及最远的点（当然只关心距离））
　　	   这两个过程分开写
　　    注意一下最近的点的距离不能是0
const int N = 5e5+5;

int n, m, cur, ans, root;
struct node{
    int mn[2], mx[2], d[2], lch, rch;
    int& operator[](int x){ return d[x];}
}p[N], t[N], T; //p[]存的是初始的点,t[]存的是建树过程中的点,T存二维查询的点
int aaa;//query查询返回值

bool cmp (const node &a, const node &b) {
    for (int i=0; i<2; i++) if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
}
int dis(node x, node y){ return abs(x[0]-y[0])+abs(x[1]-y[1]); }

void up(int k){ //类似于pushup的操作
    int l = t[k].lch, r = t[k].rch;
    for(int i=0; i<2; i++){
        t[k].mn[i] = t[k].mx[i] = t[k][i];
        if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
        if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
        if (l) t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
        if (r) t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
    }
}

int build(int l, int r, int now){ //建树 对区间[l,r] 维度为now
    cur = now;
    int mid = (l+r)>>1;
    t[mid].lch = t[mid].rch = 0;
    nth_element(t+l+1, t+mid+1, t+r+1, cmp); //找中位数
    for(int i=0; i<2; i++)t[mid].mx[i] = t[mid].mn[i] = t[mid][i];
    if(l < mid)t[mid].lch = build(l, mid-1, now^1);
    if(r > mid)t[mid].rch = build(mid+1, r, now^1);
    up(mid);
    return mid;
}

int getmx(node x){ //曼哈顿距离上界估价函数
    int ret = 0;
    for (int i=0; i<2; i++)ret += max(abs(T[i]-x.mn[i]), abs(T[i]-x.mx[i]));
    return ret;
}

int getmn(node x){ //曼哈顿距离下界估价函数
    int ret = 0;
    for(int i=0; i<2; i++){
        ret += max(T[i]-x.mx[i], 0);
        ret += max(x.mn[i]-T[i], 0);
    }
    return ret;
}

void querymx(int k){ //查询最远
    aaa = max(aaa, dis(t[k], T));
    int l = t[k].lch, r = t[k].rch, dl = -inf, dr = -inf;
    if(l)dl = getmx(t[l]);
    if(r)dr = getmx(t[r]);
        if(dl > dr){
        if(dl > aaa)querymx(l);
        if(dr > aaa)querymx(r);
    }
    else{
        if(dr > aaa)querymx(r);
        if(dl > aaa)querymx(l);
    }
}

void querymn(int k){ //查询最近
    if(dis(t[k], T))aaa = min(aaa, dis(t[k], T)); //注意一下最近的点的距离不能是0
    int l=t[k].lch, r=t[k].rch, dl=inf, dr=inf;
    if (l)dl=getmn(t[l]);
    if (r)dr=getmn(t[r]);
    if (dl < dr){
        if(dl < aaa)querymn(l);
        if(dr < aaa)querymn(r);
    }
    else{
        if(dr < aaa)querymn(r);
        if(dl < aaa)querymn(l);
    }
}

int query(int f, int x, int y){ //查询最远距离或最近距离 f是控制mx还是mn,查询坐标(x, y)
    T[0] = x; T[1] = y;
    if(f == 0)aaa = -inf, querymx(root);
    else aaa = inf, querymn(root);
    return aaa;
}

int  main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++)scanf("%d%d", &t[i][0], &t[i][1]), p[i] = t[i];

    root = build(1, n, 0); ans = inf;
    for(int i=1; i<=n; i++){
        int mx = query(0, p[i][0], p[i][1]), mn = query(1, p[i][0], p[i][1]);
        ans = min(ans, mx-mn);
    }
    printf("%d\n", ans);
    return 0;
}

2. bzoj2648
题意：在一个棋盘上初始有一些黑棋子，接着要放一些黑白棋子，
若放的是白棋子则回答离它最近的（曼哈顿距离）黑棋子的距离
思路：模板题，带上一个插入操作，类似平衡树的思想。
const int N = 1e6+5;

int n, m, cur, ans, root;
struct node{
    int mn[2], mx[2], d[2], lch, rch;
    int& operator[](int x){ return d[x];}
    friend bool operator < (node x, node y){ return x[cur] < y[cur]; }
    friend int dis(node x, node y){ return abs(x[0]-y[0])+abs(x[1]-y[1]); }
}p[N];

struct kdtree{
    node t[N], T;
    int aaa;
    void up(int k){ //类似于pushup的操作
        int l = t[k].lch, r = t[k].rch;
        for(int i=0; i<2; i++){
            t[k].mn[i] = t[k].mx[i] = t[k][i];
            if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
            if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
            if (l) t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
            if (r) t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
        }
    }

    int build(int l, int r, int now){ //建树 对区间[l,r] 维度为now
        cur = now;
        int mid = (l+r)>>1;
        nth_element(p+l, p+mid, p+r+1); //找中位数
        t[mid] = p[mid];
        for(int i=0; i<2; i++)t[mid].mx[i] = t[mid].mn[i] = t[mid][i];
        if(l < mid)t[mid].lch = build(l, mid-1, now^1);
        if(r > mid)t[mid].rch = build(mid+1, r, now^1);
        up(mid);
        return mid;
    }

    int getmn(node x){  //曼哈顿距离下界估价函数
        int ret = 0;
        for(int i=0; i<2; i++){
            ret += max(T[i]-x.mx[i], 0);
            ret += max(x.mn[i]-T[i], 0);
        }
        return ret;
    }

    void querymn(int k){  //查询最近
        aaa = min(aaa, dis(t[k], T));  //同一个格子可能有多个棋子
        int l=t[k].lch, r=t[k].rch, dl=inf, dr=inf;
        if (l)dl=getmn(t[l]);
        if (r)dr=getmn(t[r]);
        if (dl < dr){
            if(dl < aaa)querymn(l);
            if(dr < aaa)querymn(r);
        }
        else{
            if(dr < aaa)querymn(r);
            if(dl < aaa)querymn(l);
        }
    }

    int query(int x, int y){   //查询最近综合函数
        T[0] = x; T[1] = y; T.lch=0;T.rch=0;
        aaa = inf, querymn(root);
        return aaa;
    }

    void inser(int k, int now){ //插入函数 k是结点,now是维度 类似平衡树的思想
        if(T[now] >= t[k][now]){
            if(t[k].rch)inser(t[k].rch, now^1);
            else{
                t[k].rch = ++n, t[n] = T;
                for(int i=0; i<2; i++)t[n].mx[i] = t[n].mn[i] = t[n][i];
            }
        }
        else{
            if(t[k].lch)inser(t[k].lch, now^1);
            else{
                t[k].lch = ++n, t[n] = T;
                for(int i=0; i<2; i++)t[n].mx[i] = t[n].mn[i] = t[n][i];
            }
        }
        up(k);
    }

    void ins(int x, int y){ //插入的综合函数
        T[0] = x, T[1] = y; T.lch = 0, T.rch = 0, inser(root, 0);
    }
}kd;

int  main(){
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++)scanf("%d%d", &p[i][0], &p[i][1]);

    root = kd.build(1, n, 0);
    while(m--){
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if(op ==1)kd.ins(x, y);
        else printf("%d\n", kd.query(x, y));
    }
    return 0;
}


3. hdu 5992
const ll INF = (1LL<<62)-1;
const int N = 2e5+5;

template<class T> void read(T&num) {
    char CH; bool F=false;
    for(CH=getchar();CH<'0'||CH>'9';F= CH=='-',CH=getchar());
    for(num=0;CH>='0'&&CH<='9';num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}

int n, m, cur, root;
pair<ll, int>ans;
struct node{
    ll mn[3], mx[3], d[3];
    int id, lch, rch;
    ll& operator[](int x){ return d[x];}
}p[N], t[N]; //p[]存的是初始的点,t[]存的是建树过程中的点
ll x, y, z;  //三维输入

bool cmp (const node &a, const node &b) {
    for (int i=0; i<3; i++) if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
    return a.id < b.id;
}

void up(int k){ //类似于pushup的操作
    int l = t[k].lch, r = t[k].rch;
    for(int i=0; i<3; i++){
        t[k].mn[i] = t[k].mx[i] = t[k][i];
        if (l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
        if (r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
        if (l) t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
        if (r) t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
    }
}

int build(int l, int r, int now){ //建树 对区间[l,r] 维度为now
    cur = now;
    int mid = (l+r)>>1;
    t[mid].lch = t[mid].rch = 0;
    nth_element(t+l+1, t+mid+1, t+r+1, cmp); //找中位数
    for(int i=0; i<3; i++)t[mid].mx[i] = t[mid].mn[i] = t[mid][i];
    if(l < mid)t[mid].lch = build(l, mid-1, (now+1)%3);
    if(r > mid)t[mid].rch = build(mid+1, r, (now+1)%3);
    up(mid);
    return mid;
}

ll dis(int k){//点(x,y)在cost的管辖范围内的可能最小值
    ll ret = 0;
    if (z < t[k].mn[2])return INF; //如果一个节点范围内最小第三维比询问大，那么可以直接忽略
    if (x < t[k].mn[0]) ret += sqr(t[k].mn[0]-x);
    if (x > t[k].mx[0]) ret += sqr(x-t[k].mx[0]);
    if (y < t[k].mn[1]) ret += sqr(t[k].mn[1]-y);
    if (y > t[k].mx[1]) ret += sqr(y-t[k].mx[1]);
    return ret;
}

void query (int k) {
    pair<ll, int> dl = make_pair(INF, 1), dr = make_pair(INF, 1);
    int l = t[k].lch, r = t[k].rch;
    long long d0 = INF;
    if (z >= t[k].d[2])
        d0 = sqr(t[k].d[0]-x)+sqr(t[k].d[1]-y);//初始答案
    ans = min(ans, make_pair (d0, t[k].id)); //相同需要输出标号在前的,所以用pair判断
    if (l)dl = make_pair(dis(l), t[l].id);
    if (r)dr = make_pair(dis(r), t[r].id);
    if (dl < dr) {
        if (dl < ans)query(l);
        if (dr < ans)query(r);
    }
    else {
        if (dr < ans)query(r);
        if (dl < ans)query(l);
    }
}

int  main(){
    int T; scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        for(int i=1; i<=n; i++){
            read(t[i][0]); read(t[i][1]); read(t[i][2]); t[i].id = i;
            p[i] = t[i];
        }
        root = build(1, n, 0);
        for(int i=1; i<=m; i++){
            ans = make_pair(INF, 0);
            read(x); read(y); read(z);
            query(root);
            int id = ans.ss;
            printf("%lld %lld %lld\n", p[id][0], p[id][1], p[id][2]);
        }
    }
    return 0;
}
