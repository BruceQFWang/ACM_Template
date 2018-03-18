
poj2155
题意：有一个矩阵，每次操作可以是编辑某个矩形区域，这个区域的0改为1，1改为0，每次查询只查询某一个点的值是0还是1。
思路：
可以使用二维树状数组。
二维的写起来很方便，两重循环。
如果是要修改(x1,y1)  -  (x2,y2)的矩形区域。
那么可以在(x1,y1) 出加1，在(x2+1,y1)处加1，在(x1,y2+1)处加1，在(x2+1,y2+1)处加1 。。
画个图就知道了，查询单点就是求和。
复杂度：O(4*m*log^2n)
const int N = 1e3+5;

struct BIT{
    int n;
    ll c[N][N];
    void init(int _n){
        n=_n;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                c[i][j] = 0;
    }
    void update(int x, int y, ll val){  //第二种区间更新
        for(int i=x; i<=n; i+=i&-i)
            for(int j=y; j<=n; j+=j&-j)
                c[i][j] += val;
    }
    ll query(int x, int y){ //单点查询
        ll ret = 0;
        for(int i=x; i>0; i-=i&-i)
            for(int j=y; j>0; j-=j&-j)
                ret += c[i][j];
        return ret;
    }
}bit;

int  main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m; scanf("%d%d", &n, &m);
        bit.init(n);
        while(m--){
            char op[5]; scanf("%s", op);
            if(op[0] == 'C'){
                int x1, y1, x2, y2;
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                bit.update(x1, y1, 1);
                bit.update(x2+1, y1, 1);
                bit.update(x1, y2+1, 1);
                bit.update(x2+1, y2+1, 1);
            }
            else{
                int x, y; scanf("%d%d", &x, &y);
                printf("%d\n", bit.query(x, y)%2);
            }
        }
        puts("");
    }
    return 0;
}
