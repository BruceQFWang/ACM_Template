/*莫队一般是离线的，条件是只有询问操作，没有修改操作，而且可以轻易的从[L,R]区间拓展4个区间
 *模板见cf 617 E题
 *题意：n个序列，m次询问，每次询问区间[l, r]之间有多少个区间，在这些区间里面的序列xor起来值为k
 */
const int N = 1e5+5;
const int blocks = 316; // sqrt(1e5) 分块的大小
//这里一定要用const,不然排序会RE
struct node{
    int l, r, id;
    bool operator < (const node& rhs)const {
        return l/blocks == rhs.l/blocks ? r<rhs.r : l/blocks<rhs.l/blocks;
//return l / blocks < rhs.l / blocks || (l / blocks == rhs.l / blocks && r < rhs.r);
    }
}q[N];

int n, m, k;
ll ans[N], now;
int a[N], cnt[1<<20];

void add(int x){
    now += cnt[x^k];
    cnt[x]++;
}

void del(int x){
    cnt[x]--;
    now -= cnt[x^k];
}

int  main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i=1; i<=n; i++)scanf("%d", &a[i]), a[i] ^= a[i-1];
    for(int i=1; i<=m; i++){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q+1, q+1+m);
    int l = 1, r = 0; // pre[l-1]^pre[r]
    for(int i=1; i<=m; i++){  //r和l判断顺序不固定，参见hdu4638
        while(q[i].r > r)add(a[++r]);
        while(q[i].r < r)del(a[r--]);
        while(q[i].l-1 > l)del(a[l++]);// pre[l-1]^pre[r]
        while(q[i].l-1 < l)add(a[--l]);
        ans[q[i].id] = now;
    }
    for(int i=1; i<=m; i++)printf("%I64d\n", ans[i]);
    return 0;
}

