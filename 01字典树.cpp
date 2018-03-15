CF 706 D. Vasiliy's Multiset
思路：一道01字典树的题。将要插入的数的二进制位倒着建树(为什么？因为异或时高位尽量大，结果才尽量大)，即高位在深度低的节点上。用一个数组记录经过各个节点的数的个数，插入时，每经过一个点，将节点的这个值加一，删除时，则减一。查找时，当前节点的这个值大于0，说明有数经过。对于要查找的这个数的高位，如果是1，要使异或值尽量大，那么就要往0的地方走，反之，往1的地方走，实在没办法走，只有按原路径走啦。详见代码。注意：0永远在树中。
#include<bits/stdc++.h>
using namespace std;
#define Memset(x, a) memset(x, a, sizeof(x))
typedef long long ll;
const int maxn = 222222;//集合中的数字个数
int ch[32*maxn][2];         //节点的边信息
ll val[32*maxn];            //节点存储的值   记得初始化
int sz,q;                     //树中当前节点个数
ll num;

void init(){
    Memset(ch[0],0);           //树清空
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
