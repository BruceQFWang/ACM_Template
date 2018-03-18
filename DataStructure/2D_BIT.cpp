
poj2155
���⣺��һ������ÿ�β��������Ǳ༭ĳ������������������0��Ϊ1��1��Ϊ0��ÿ�β�ѯֻ��ѯĳһ�����ֵ��0����1��
˼·��
����ʹ�ö�ά��״���顣
��ά��д�����ܷ��㣬����ѭ����
�����Ҫ�޸�(x1,y1)  -  (x2,y2)�ľ�������
��ô������(x1,y1) ����1����(x2+1,y1)����1����(x1,y2+1)����1����(x2+1,y2+1)����1 ����
����ͼ��֪���ˣ���ѯ���������͡�
�ο��� http://blog.csdn.net/zxy_snow/article/details/6264135
���Ӷȣ�O(4*m*log^2n)
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
    void update(int x, int y, ll val){  //�ڶ����������
        for(int i=x; i<=n; i+=i&-i)
            for(int j=y; j<=n; j+=j&-j)
                c[i][j] += val;
    }
    ll query(int x, int y){ //�����ѯ
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
