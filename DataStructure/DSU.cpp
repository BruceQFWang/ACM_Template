int p[N];//主函数要对它初始化

int Find(int x){
    return p[x]==x?x:p[x]=Find(p[x]);
}

void unite(int x,int y){
    x=Find(x);
    y=Find(y);
    if(x!=y)
        p[y]=x;
}
