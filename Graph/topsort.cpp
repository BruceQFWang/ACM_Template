HDU 3342
���⣺
�ж�����ͼ���Ƿ���DAG���޻���
˼·��
BFS��һ���������ж�һ��

const int N=110;

std::vector<int> g[N];
int deg[N];//���
int n, m;

bool topo(){
    queue<int> q;
    rep(i, 0, n-1){
        if(deg[i] == 0)q.push(i);
    }

    int tol = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        tol ++;
        for(auto v : g[u]){
            deg[v] --;
            if(!deg[v])q.push(v);
        }
    }
    if(tol != n)return false;
    return true;
}

int  main(){
    while(cin>>n>>m){
        if(!n)break;
        mst(deg, 0);
        rep(i, 0, n-1)g[i].clear(); //��������
        rep(i, 1, m){
            int u,v;
            cin>>u>>v;
            g[u].push_back(v);
            deg[v]++;
        }
        if(topo())puts("YES");
        else puts("NO");
    }
  return 0;
}
