用法：
1.第k大
2.不同数只算一次然后求第k大
3.求区间中一个数出现多少次

主席树小结：在对静态序列（或者树之类的）进行预处理后支持区间k大元素询问以及区间特定元素的名次询问，需要用到可持久化线段树
可持久化线段树也叫函数式线段树(又叫主席树）

1. POJ2104
 详解参考：http://www.cnblogs.com/oyking/p/3230296.html
题目：给你n个数，m次询问每次询问[L,R]这个区间第k的数
复杂度与空间O(nlogn)

const int N = 1e5+5;
int n, m, cnt, root[N], a[N]; //初始化cnt root[]

struct node{ int l, r, sum; }T[N*20];  //这里l,r的值不一定是1-n
vector<int>vt;

int getid(int x){ return lower_bound(vt.begin(), vt.end(), x)-vt.begin()+1; }

void update(int pos, int val, int l, int r, int &x, int y){//在第y棵树的基础上在pos点加上(val=1)变成第x 棵树
    T[++cnt] = T[y], T[cnt].sum += val, x = cnt;
    if(l == r)return ;
    int mid = (l+r)>>1; //T[x].l通过引用被修改
    if(mid >= pos)update(pos, val, l, mid, T[x].l, T[y].l); //在左边
    else update(pos, val, mid+1, r, T[x].r, T[y].r);//右边
}

int query(int a, int b, int k, int l, int r){//第y棵树减去第x棵树得到[a+1,b]的一课权值线段树，从而查询
    if(l == r)return l;
    int mid = (l+r)>>1;
    int sum = T[T[b].l].sum-T[T[a].l].sum;
    if(sum >= k)return query(T[a].l, T[b].l, k, l, mid);
    else return query(T[a].r, T[b].r, k-sum, mid+1, r);
}

int  main(){
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++)scanf("%d", &a[i]), vt.pb(a[i]);
    sort(vt.begin(), vt.end());
    vt.erase(unique(vt.begin(), vt.end()), vt.end()); //去重
    for(int i=1; i<=n; i++)update(getid(a[i]), 1, 1, n, root[i], root[i-1]);
    for(int i=1; i<=m; i++){     //root[i]第i个线段树标号
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        printf("%d\n", vt[query(root[x-1], root[y], k, 1, n)-1]);
    }
    return 0;
}


2. cf 786C
题意：给你n个数，问最少能把这n个数分成连续的几段，且每段中不同的个数小于等于k个，输出k从1到n的答案。

分析：我们知道i~(i,,,n)的不同数的个数肯定是递增的，所以对于每个i，我们可以通过二分得出一个最大的j使[i,j]中不同的数个数<=k。那么问题的关键在于，如何知道[i,j]这样一个区间中，不同的数的个数。
我们可以利用主席树，以root[i]为顶点的线段树存的是，[i,n]中不同的数个数，对于每颗树，将每个第一次出现的数的位置 置为1，其他重复出现的位置 置为0。
那么，对于每个k，刚开始我们位于root[1],二分找出值为k+1的位置r，ans[k]++,并将当前位置置成root[r],这样，我们面对的就是[r,n]这段数，直到r>n停止。 (所以update是1,n)
代码中:ed[i]表示最先出现i的位置,nxt[i]表示在i位置的数下一次出现在哪个位置。
复杂度O(nlognlogn)   空间(3*nlogn) 1e5的良心数据没卡时间 但是空间得开大一点
空间分析: log(1e5)约等于20，update了三次所以至少要三倍

const int N = 1e5+5;

int n, cnt, root[N], a[N];
int ed[N], nxt[N];// ed[i]表示最先出现i的位置,nxtt[i]表示在i位置的数下一次出现在哪个位置。

struct node{
    int l, r, sum; //这里l,r的值不一定是1-n
}T[60*N];

void update(int pos, int val, int l, int r, int &x, int y){//在第y棵树的基础上在pos点加上(val=1)变成第x棵树
    T[++cnt] = T[y], T[cnt].sum += val, x = cnt;
    if(l == r)return ;
    int mid = (l+r)>>1; //T[x].l通过引用被修改
    if(mid >= pos)update(pos, val, l, mid, T[x].l, T[y].l); //在左边
    else update(pos, val, mid+1, r, T[x].r, T[y].r);//右边
}

int query(int x, int pos, int l, int r){
    if(l == r)return l;
    int mid = (l+r)>>1;
    if(T[T[x].l].sum >= pos)return query(T[x].l, pos, l, mid);
    else return query(T[x].r, pos-T[T[x].l].sum, mid+1, r);
}

int  main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++)scanf("%d", &a[i]), ed[i] = n+1;
    for(int i=n; i>=1; i--){
        nxt[i] = ed[a[i]];
        ed[a[i]] = i;
    }
    // 存储区间[1-n]的数，重复的数记录一次
    for(int i=1; i<=n; i++)update(ed[i], 1, 1, n+1, root[1], root[1]);
    for(int i=2; i<=n; i++){ //因为ed以n+1结尾所以是1,n+1
        update(i-1, -1, 1, n+1, root[i], root[i-1]); //以root[i]为顶点的线段树存的是[i,n]中不同的数个数就要删去i-1
        update(nxt[i-1], 1, 1, n+1, root[i], root[i]); //如果后面还可能出现a[i-1]就要加进去
    }
    for(int i=1; i<=n; i++){
        int now = 1, ans = 0;
        while(now <= n){
            now = query(root[now], i+1, 1, n+1);
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}


 2016CCPC长春：Sequence II（主席树）
const int N = 2e5+5;

int n, m, cnt, root[N], a[N];
struct node{ int l, r, sum;}T[40*N];

void update(int pos, int v, int l, int r, int& x, int y){
    T[++cnt] = T[y], T[cnt].sum += v, x = cnt;
    if(l == r)return ;
    int mid = (l+r)>>1;
    if(mid >= pos)update(pos, v, l, mid, T[x].l, T[y].l);
    else update(pos, v, mid+1, r, T[x].r, T[y].r);
}

int query(int rt, int k, int l, int r){
    if(l == r)return l;
    int mid = (l+r)>>1;
    int sum = T[T[rt].l].sum;
    if(sum >= k)return query(T[rt].l, k, l, mid);
    else return query(T[rt].r, k-sum, mid+1, r);
}

int query_blk(int a, int b, int l, int r, int rt){
    if(a <= l && r <= b)return T[rt].sum;
    int mid = (l+r)>>1;
    int ret = 0;
    if(a <= mid)ret += query_blk(a, b, l, mid, T[rt].l);
    if(b > mid)ret += query_blk(a, b, mid+1, r, T[rt].r);
    return ret;
}

int pre[N], ans[N];
int  main(){
    int t;
    scanf("%d", &t);
    for(int kase=1; kase<=t; kase++){
        mst(pre, 0);
        mst(root, 0);
        cnt = 0;
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)scanf("%d", &a[i]);
        for(int i=n; i>=1; i--){
            update(i, 1, 1, n, root[i], root[i+1]);
            if(pre[a[i]])update(pre[a[i]], -1, 1, n, root[i], root[i]);
            pre[a[i]] = i;
        }
        ans[0] = 0;
        for(int i=1; i<=m; i++){
            int l, r;
            scanf("%d%d", &l, &r);
            l = (l+ans[i-1])%n+1, r = (r+ans[i-1])%n+1;
            if(l > r)swap(l, r);
            int num = query_blk(l, r, 1, n, root[l]);
            num = (num+1)/2;
            ans[i] = query(root[l], num, 1, n);
        }
        printf("Case #%d:", kase);
        for(int i=1; i<=m; i++)printf(" %d", ans[i]); puts("");
    }
    return 0;
}

3. cf 840D
题意：q次询问，每次询问区间[l,r]中出现次数大于⌊(r−l+1)/k⌋的数的最小值。
思路：发现k≤5只要查询区间第⌊(r−l+1)∗i/k⌋(1≤i≤k)大的数，并判一下是否出现了这么多次即可。
主席树作用：查询区间第k大，查询区间一个数出现的次数
const int N = 3e5+5;

struct node{
    int l, r, sz;
}T[N*20];
int n, q, cnt, root[N], a[N];

void update(int pos, int l, int r, int &x, int y){//在第y棵树的基础上在pos点加上(val=1)变成第x 棵树
    T[++cnt] = T[y], T[cnt].sz = T[x].sz+1, x = cnt;
    if(l == r)return ;
    int mid = (l+r)>>1; //T[x].l通过引用被修改
    if(mid >= pos)update(pos, l, mid, T[x].l, T[y].l); //在左边
    else update(pos, mid+1, r, T[x].r, T[y].r);//右边
}

inline int Kth(int x, int y, int k) {
    x = root[x]; y = root[y];
    int l = 1, r = n, mid;
    while (l != r) {
        mid = (l + r) >> 1;
        if (T[T[y].l].sz - T[T[x].l].sz >= k) {
            x = T[x].l; y = T[y].l;
            r = mid;
        } else {
            k -= T[T[y].l].sz - T[T[x].l].sz;
            x = T[x].r; y = T[y].r;
            l = mid + 1;
        }
    }
    return l;
}
inline int Query(int x, int y, int p) {
    x = root[x]; y = root[y];
    int l = 1, r = n, mid;
    while (l != r) {
        mid = (l + r) >> 1;
        if (p <= mid) {
            x = T[x].l; y = T[y].l;
            r = mid;
        } else {
            x = T[x].r; y = T[y].r;
            l = mid + 1;
        }
    }
    return T[y].sz - T[x].sz;
}

int  main(){
    scanf("%d%d", &n, &q);
    for(int i=1; i<=n; i++){
        scanf("%d", &a[i]);
        update(a[i], 1, n, root[i], root[i-1]);
    }
    while(q--){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int ans = inf;
        for (int i=1; i<=k; i++) {
            int p = (r-l+1)*i/k, num;
            if (Query(l-1, r, num = Kth(l-1, r, p)) > (r-l+1)/k)
                ans = min(ans, num);
        }
        if(ans == inf)ans = -1;
        printf("%d\n", ans);
    }
    return 0;
}
