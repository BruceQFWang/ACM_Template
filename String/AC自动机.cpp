
//����ʧ��ָ�룺�赱ǰ�ڵ��ϵ���ĸΪC�����������׵�ʧ��ָ���ߣ�ֱ���ߵ�һ���ڵ㣬���Ķ�����Ҳ����ĸΪC�ġ�Ȼ��ѵ�ǰ�ڵ��ʧ��ָ��ָ���Ǹ���ĸҲΪC�Ķ��ӡ����һֱ�ߵ���root��û�ҵ����ǾͰ�ʧ��ָ��ָ��root��
//ƥ��(1)��ǰ�ַ�ƥ�䣬ֻ���ظ�·��������һ���ڵ����ƥ�伴�ɣ�(2)��ǰ�ַ���ƥ�䣬��ȥ��ǰ�ڵ�ʧ��ָ����ָ����ַ�����ƥ��.�ظ���2�������е�һ����ֱ��ģʽ�����ꡣ
//======================
// HDU 2222
// ��Ŀ�괮�г����˼���ģʽ��
//====================
#include<bits/stdc++.h>
using namespace std;

const int maxn=500010;

struct Trie{
  int next[maxn][26],fail[maxn],end[maxn];//��ĸ���ֵ����� ʧ��ָ�� �Դ˽��Ϊĩβ�ĵ��ʸ���
  int root,L;//����� �ܵĽ����

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

  void insert(char buf[]){//����trie��
    int len = strlen(buf);
    int now = root;
    for(int i = 0;i < len;i++){
      if(next[now][buf[i]-'a'] == -1)
        next[now][buf[i]-'a'] = newnode();
      now = next[now][buf[i]-'a'];
    }
    end[now]++;
  }

  void build(){//��ʼ��failָ�룬BFS
    queue<int>Q;
    fail[root] = root;
    for(int i = 0;i < 26;i++)//�����ʼ��Ԫ��
      if(next[root][i] == -1)
        next[root][i] = root;
      else{
        fail[next[root][i]] = root;//��һ��Ԫ��fail��ָ���
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

  int query(char buf[]){//ɨ���ı���
    int len = strlen(buf);
    int now = root;
    int res = 0;
    for(int i = 0;i < len;i++){
      if(buf[i]>='a' && buf[i]<='z')now = next[now][buf[i]-'a'];//��Ͼ�����Ŀ�޸�
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

  void debug(){//����
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
    scanf("%s",buf);//gets scanf �ÿ����
    printf("%d\n",ac.query(buf));////////
  }
  return 0;
}
