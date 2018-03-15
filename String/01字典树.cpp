CF 706 D. Vasiliy's Multiset
˼·��һ��01�ֵ������⡣��Ҫ��������Ķ�����λ���Ž���(Ϊʲô����Ϊ���ʱ��λ�����󣬽���ž�����)������λ����ȵ͵Ľڵ��ϡ���һ�������¼���������ڵ�����ĸ���������ʱ��ÿ����һ���㣬���ڵ�����ֵ��һ��ɾ��ʱ�����һ������ʱ����ǰ�ڵ�����ֵ����0��˵����������������Ҫ���ҵ�������ĸ�λ�������1��Ҫʹ���ֵ��������ô��Ҫ��0�ĵط��ߣ���֮����1�ĵط��ߣ�ʵ��û�취�ߣ�ֻ�а�ԭ·��������������롣ע�⣺0��Զ�����С�
#include<bits/stdc++.h>
using namespace std;
#define Memset(x, a) memset(x, a, sizeof(x))
typedef long long ll;
const int maxn = 222222;//�����е����ָ���
int ch[32*maxn][2];         //�ڵ�ı���Ϣ
ll val[32*maxn];            //�ڵ�洢��ֵ   �ǵó�ʼ��
int sz,q;                     //���е�ǰ�ڵ����
ll num;

void init(){
    Memset(ch[0],0);           //�����
    sz=1;
}

void _insert(ll a){
    int u=0;
    for(int i=32;i>=0;i--){
        int c=((a>>i)&1);
        if(!ch[u][c]){
            Memset(ch[sz],0);
            ch[u][c]=sz++;
        }
        u=ch[u][c];
        ++val[u];
    }
}

void _delete(ll a){
  int u=0;
  for (int i=32; i>=0; --i){
      int c=((a>>i)&1);
      u=ch[u][c];
      --val[u];
  }
}

ll query(ll a){
    int u=0;
    ll ans=0;
    for(int i=32;i>=0;i--){
        int c=((a>>i)&1);
        if (c==1){
            if (ch[u][0] && val[ch[u][0]]){
                ans+=1<<i;
                u=ch[u][0];
            }
            else
                u=ch[u][1];
        }
        else{
            if (ch[u][1] && val[ch[u][1]]){
                ans+=1<<i;
                u=ch[u][1];
            }
            else
                u=ch[u][0];
        }
    }
    return ans;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  string op;
  init();
  cin>>q;
  _insert(0);
  while(q--){
    cin>>op>>num;
    if(op[0]=='+')_insert(num);
    else if(op[0]=='-')_delete(num);
    else cout<<query(num)<<endl;
  }
  return 0;
}
