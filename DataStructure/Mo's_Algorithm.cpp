/*Ī��һ�������ߵģ�������ֻ��ѯ�ʲ�����û���޸Ĳ��������ҿ������׵Ĵ�[L,R]������չ4������
 *ģ���cf 617 E��
 *���⣺n�����У�m��ѯ�ʣ�ÿ��ѯ������[l, r]֮���ж��ٸ����䣬����Щ�������������xor����ֵΪk
 */
const int N = 1e5+5;
const int blocks = 316; // sqrt(1e5) �ֿ�Ĵ�С
//����һ��Ҫ��const,��Ȼ�����RE
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
    for(int i=1; i<=m; i++){  //r��l�ж�˳�򲻹̶����μ�hdu4638
        while(q[i].r > r)add(a[++r]);
        while(q[i].r < r)del(a[r--]);
        while(q[i].l-1 > l)del(a[l++]);// pre[l-1]^pre[r]
        while(q[i].l-1 < l)add(a[--l]);
        ans[q[i].id] = now;
    }
    for(int i=1; i<=m; i++)printf("%I64d\n", ans[i]);
    return 0;
}

