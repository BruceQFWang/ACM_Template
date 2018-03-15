
//构造失败指针：设当前节点上的字母为C，沿着他父亲的失败指针走，直到走到一个节点，他的儿子中也有字母为C的。然后把当前节点的失败指针指向那个字母也为C的儿子。如果一直走到了root都没找到，那就把失败指针指向root。
//匹配(1)当前字符匹配，只需沿该路径走向下一个节点继续匹配即可；(2)当前字符不匹配，则去当前节点失败指针所指向的字符继续匹配.重复这2个过程中的一个，直到模式串走完。
//======================
// HDU 2222
// 求目标串中出现了几个模式串
//====================
#include<bits/stdc++.h>
using namespace std;

const int maxn=500010;

struct Trie{
  int next[maxn][26],fail[maxn],end[maxn];//字母的字典序编号 失败指针 以此结点为末尾的单词个数
  int root,L;//根结点 总的结点数

  int newnode(){
    for(int i = 0;i < 26;i++)
      next[L][i] = -1;
    end[L++] = 0;
    return L-1;
  }

  void init(){
    L = 0;
    root = newnode();
  }

  void insert(char buf[]){//建立trie树
    int len = strlen(buf);
    int now = root;
    for(int i = 0;i < len;i++){
      if(next[now][buf[i]-'a'] == -1)
        next[now][buf[i]-'a'] = newnode();
      now = next[now][buf[i]-'a'];
    }
    end[now]++;
  }

  void build(){//初始化fail指针，BFS
    queue<int>Q;
    fail[root] = root;
    for(int i = 0;i < 26;i++)//处理初始的元素
      if(next[root][i] == -1)
        next[root][i] = root;
      else{
        fail[next[root][i]] = root;//第一个元素fail必指向根
        Q.push(next[root][i]);
      }
    while( !Q.empty() ){
      int now = Q.front();
      Q.pop();
      for(int i = 0;i < 26;i++)
        if(next[now][i] == -1)
          next[now][i] = next[fail[now]][i];
        else{
          fail[next[now][i]]=next[fail[now]][i];
          Q.push(next[now][i]);
        }
    }
  }

  int query(char buf[]){//扫描文本串
    int len = strlen(buf);
    int now = root;
    int res = 0;
    for(int i = 0;i < len;i++){
      if(buf[i]>='a' && buf[i]<='z')now = next[now][buf[i]-'a'];//结合具体题目修改
      else if(buf[i]>='A' && buf[i]<='Z')now = next[now][buf[i]-'A'];
      else continue;
      int temp = now;
      while( temp != root ){
        res += end[temp];
        end[temp] = 0;
        temp = fail[temp];
      }
    }
    return res;
  }

  void debug(){//调试
    for(int i = 0;i < L;i++){
      printf("id = %3d,fail = %3d,end = %3d,chi = [",i,fail[i],end[i]);
      for(int j = 0;j < 26;j++)
        printf("%2d",next[i][j]);
        printf("]\n");
    }
  }
};
char buf[1000010];
Trie ac;

int main(){
  int T;
  int n;
  scanf("%d",&T);
  while( T-- ){
    scanf("%d",&n);
    ac.init();////////
    for(int i = 0;i < n;i++){
      scanf("%s",buf);
      ac.insert(buf);////////
    }
    ac.build();
    scanf("%s",buf);//gets scanf 得看情况
    printf("%d\n",ac.query(buf));////////
  }
  return 0;
}
