//UESTC 1324��ѧ���빫��
//�������� ������ֵ

int n;
int num, blocks, belong[N], l[N], r[N];
//num�ֿ�ĸ���
//belong[i]��ʾi������һ��
//blocks��ʾ��Ĵ�С
//l[i]��ʾi��������˵�λ��
//r[i]��ʾ�Ҷ˵��λ��

ll a[N], Max[N];

//1~blocks,blocks+1~2*blocks,...
void build(){
    blocks = sqrt(n);
    num = n/blocks; if(n%blocks)num++;
    for(int i=1; i<=num; i++)
        l[i] = (i-1)*blocks+1, r[i] = i*blocks;
    r[num] = n;
    for(int i=1; i<=n; i++)
        belong[i] = (i-1)/blocks+1;

    for(int i=1; i<=num; i++)
        for(int j=l[i]; j<=r[i]; j++)
            Max[i] = max(Max[i], a[j]);
}

void update(int x, int y){
    a[x] += y;
    Max[belong[x]] = max(Max[belong[x]], a[x]);

}

ll query(int x, int y){
    ll ans = 0;
    if(belong[x] == belong[y]){ //����ͬһ���������⴦��
        for(int i=x; i<=y; i++)
            ans = max(ans, a[i]);
        return ans;
    }
    for(int i=x; i<=r[belong[x]]; i++)ans = max(ans, a[i]);
    for(int i=l[belong[y]]; i<=y; i++)ans = max(ans, a[i]);
    for(int i=belong[x]+1; i<belong[y]; i++)ans = max(ans, Max[i]);
    return ans;
}

int  main(){
    int q;
    scanf("%d%d", &n,&q);
    build();
    while(q--){
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if(op == 1)update(x, y);
        else printf("%lld\n", query(x, y));
    }
    return 0;
}
