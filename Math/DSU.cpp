int p[N];//������Ҫ������ʼ��

int Find(int x){
    return p[x]==x?x:p[x]=Find(p[x]);
}

void unite(int x,int y){
    x=Find(x);
    y=Find(y);
    if(x!=y)
        p[y]=x;
}
