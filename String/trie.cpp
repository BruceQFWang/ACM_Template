/*
 *trie树入门题 hdu1251
 */
const int maxnode=1e6+5;
const int sigma_size=26;
struct Trie{
  int ch[maxnode][sigma_size];
  int sz;
  int num[maxnode];
  Trie(){
    sz=1;
    memset(ch[0],0,sizeof(ch[0]));
    memset(num,0,sizeof(num));
  }
  int  idx(char c){ return c-'a';}

  //插入字符串s，附加信息为v
  void insert(char *s, int v){
    int u=0,n=strlen(s);
    for(int i=0; i<n; i++){
      int c=idx(s[i]);
      if(!ch[u][c]){   //结点不存在
        memset(ch[sz],0,sizeof(ch[sz]));
        num[sz]=0;
        ch[u][c]=sz++;//新建结点
      }
      u=ch[u][c];//往下走
      num[u]++;
    }
  }

  int  search(char *s){
    int n=strlen(s);
    int u=0;
    for(int i=0; i<n; i++){
      int c=idx(s[i]);
      if(!ch[u][c])return 0;

      u=ch[u][c];
    }
    return num[u];
  }

};
Trie  T;
int  main(){
  char  s[15];
  int flag=0;
  while(gets(s),strcmp(s,"")){
    T.insert(s,1);
  }
  while(gets(s)!=NULL){
    printf("%d\n",T.search(s));
  }
  return 0;
}
