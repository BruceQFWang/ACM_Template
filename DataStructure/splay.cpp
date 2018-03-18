splay tree常常用来解决以下的问题:
问题一:维护一些数
1.添加一个数
2.删除一个数
3.询问一个数在这些数里的排名
4.询问当前排名为k的数是多少
5.查询一个数的前驱后继(比他大的最小的数/比他小的最大的数)
bzoj 1588
题意：每读入一个数，在前面输入的数中找到一个与该数相差最小的一个。把所有的差值加起来。
思路：三种操作：插入，求前驱，后驱。
const int N = 1e5+5;

int pre[N], key[N], ch[N][2], root, tol1;
//分别表示父结点，键值，左右孩子（0左1右），根结点，结点数量
int n;

//新建一个结点
void NewNode(int& r, int fa, int k){
    r = ++tol1;
    pre[r] = fa;
    key[r] = k;
    ch[r][0] = ch[r][1] = 0;//左右孩子为空
}

//旋转，kind为1是右旋，为0是左旋
void Rotate(int x, int kind){
    int y = pre[x];
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
      ch[pre[y]][ch[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
}

//Splay调整，将结点r调整到goal下面
void Splay(int r, int goal){
    while(pre[r] != goal){
        if(pre[pre[r]] == goal)Rotate(r, ch[pre[r]][0] == r);
        else{
            int y = pre[r];
            int kind = ch[pre[y]][0] == y;
            if(ch[y][kind] == r){
                Rotate(r, !kind);
                Rotate(r, kind);
            }
            else{
                Rotate(y, kind);
                Rotate(r, kind);
            }
        }
    }
    //更新根结点
    if(goal==0)root = r;
}

int Insert(int k){
    int r = root;
    while(ch[r][key[r]<k]){
        //不重复插入 相同的值当天波动肯定为0
        if(key[r] == k){
            Splay(r, 0);
            return 0;
        }
        r = ch[r][key[r]<k];
    }
    NewNode(ch[r][key[r]<k], r, k);
    Splay(ch[r][key[r]<k], 0);
    return 1;
}

//找前驱
int get_pre(int x){
    int tmp = ch[x][0];
    if(tmp == 0)return inf;
    while(ch[tmp][1])tmp = ch[tmp][1];
    return key[x]-key[tmp];
}

//找后继
int get_next(int x){
    int tmp = ch[x][1];
    if(tmp == 0)return inf;
    while(ch[tmp][0])tmp = ch[tmp][0];
    return key[tmp]-key[x];
}

int  main(){
    while(~scanf("%d", &n)){
        root = tol1 = 0;
        int ans = 0;
        for(int i=1; i<=n; i++){
            int num;
            if(scanf("%d", &num) == EOF)num = 0;
            if(i == 1){
                ans += num;
                NewNode(root, 0, num);
                continue;
            }
            if(Insert(num) == 0)continue;
            int a = get_pre(root);
            int b = get_next(root);
            ans += min(a, b);
        }
        printf("%d\n", ans);
    }


问题二:维护一个序列
1.给某个区间的所有数加上一个值
2.询问某个区间的最大/最小值
3.查询某个区间的和
4.翻转某个区间
5.平移一个区间
6.删除/添加一个区间
而对于区间的操作,splay的做法比较统一.
比如我们要对[L,R]区间进行操作,我们则先将L-1这个点转到根,然后将R+1这个点转到L-1的下面(即根的下面),然后根据splay的平衡性我们就能发现,R+1这个点的左子树就是我们要的[L,R]区间,然后我们要查询或者修改区间值,就直接对这个子树操作就行了.

hdu 3487
/*
 * 初始序列是1,2,3,...,n
 * 进行两种操作，区间切割和区间反转
 * CUT a b c :把[a,b]切割下来，然后放在第c个元素后面
 * FLIP a b :反转区间[a,b]
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define key_value ch[ch[root][1]][0]
const int N = 300010;
int pre[N], ch[N][2], key[N], sz[N];
//分别表示父结点，键值，左右孩子（0左1右），根结点，结点数量
int rev[N];
int root, tot1;
int n, q;

//debug部分**********************************
void Treavel(int x){
    if(x){
        Treavel(ch[x][0]);
        printf("结点 %2d:左儿子 %2d 右儿子 %2d  父结点 %2d key=%2d,sz=%2d,rev=%2d\n",x,ch[x][0],ch[x][1],pre[x],key[x],sz[x],rev[x]);
        Treavel(ch[x][1]);
    }
}
void debug(){
    printf("root:%d\n", root);
    Treavel(root);
}
//以上是debug部分****************************

void NewNode(int &r, int fa, int k){
    r = ++tot1;
    ch[r][0] = ch[r][1] = 0;
    sz[r] = 1;
    key[r] = k;
    rev[r] = 0;
    pre[r] = fa;
}
//反转的更新
void update_rev(int r){
    if(!r)return;
    swap(ch[r][0], ch[r][1]);
    rev[r] ^= 1;
}

void PushUp(int r){
    sz[r] = sz[ch[r][0]]+sz[ch[r][1]]+1;
}

void PushDown(int r){
    if(rev[r]){
        update_rev(ch[r][0]);
        update_rev(ch[r][1]);
        rev[r] = 0;
    }
}

void build(int &x, int l, int r, int fa){
    if(l>r)return;
    int mid = (l+r)/2;
    NewNode(x, fa, mid);
    build(ch[x][0], l, mid-1, x);
    build(ch[x][1], mid+1, r, x);
    PushUp(x);
}

void init(){
    root = tot1 = 0;
    ch[root][0] = ch[root][1] = sz[root] = key[root] = pre[root] = rev[root] = 0;
    NewNode(root, 0, -1);
    NewNode(ch[root][1], root, -1);
    build(key_value, 1, n, ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
//旋转，0为左旋，1为右旋
void Rotate(int x, int kind){
    int y = pre[x];
    PushDown(y);//先把y的标记下传，在把x的标记下传
    PushDown(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    PushUp(y);
}
//Splay调整，将r结点调整到goal下面
void Splay(int r,int goal){
    PushDown(r);
    while(pre[r] != goal){
        if(pre[pre[r]] == goal){//有反转操作，需要先push_down,再判断左右孩子
            PushDown(pre[r]);
            PushDown(r);
            Rotate(r, ch[pre[r]][0] == r);
        }
        else{//有反转操作，需要先push_down
            PushDown(pre[pre[r]]);
            PushDown(pre[r]);
            PushDown(r);
            int y=pre[r];
            int kind = ch[pre[y]][0] == y;
            if(ch[y][kind] == r){
                Rotate(r, !kind);
                Rotate(r, kind);
            }
            else{
                Rotate(y, kind);
                Rotate(r, kind);
            }
        }
    }
    PushUp(r);
    if(goal == 0)root = r;   //更新根结点
}
//得到第k个结点(需要push_down)
int get_kth(int r, int k){
    PushDown(r);
    int t = sz[ch[r][0]]+1;
    if(t == k)return r;
    if(t > k)return get_kth(ch[r][0], k);
    else return get_kth(ch[r][1], k-t);
}


//将[l,r]段剪切下来，放在剩下段的第c个后面
void CUT(int l, int r, int c){
    Splay(get_kth(root, l), 0);
    Splay(get_kth(root, r+2), root);
    int tmp = key_value;  //key_value为左儿子的右儿子
    key_value = 0;
    PushUp(ch[root][1]);
    PushUp(root);
    Splay(get_kth(root, c+1), 0);
    Splay(get_kth(root, c+2), root);
    key_value = tmp;
    pre[key_value] = ch[root][1];
    PushUp(ch[root][1]);
    PushUp(root);
}
//    对于"操作1. CUT l r c" ，只需要将 l-1 旋转到根，r+1旋转成 l-1 的子树，
//    那么 [l, r] 之间的树变成了 r+1 的左子树，将整个子树从原树中删去，并把 r+1 旋转到根。
//    之后把 c 旋转到根，c+1 旋转成 c 的子树，再把刚才删掉的子树添加到 c+1 的左子树上
//    （没添加之前，c+1 的左子树必然为空）   先序遍历排列   因为有节点0,所以代码里面都要+1

//将[l,r]段反转
void Reverse(int l, int r){
    Splay(get_kth(root, l), 0);
    Splay(get_kth(root, r+2), root);
    update_rev(key_value);
    PushUp(ch[root][1]);
    PushUp(root);
}
//    对于“操作2. FLIP a b”，只需要给树中每个节点一个 rev 标记表示
//    是否需要翻转以该节点为根的子树中序遍历所得的数列，和线段树差不多的使用懒操作就行了

//按顺序输出
int cnt;
void Inorder(int r){
    if(!r)return;
    PushDown(r);
    Inorder(ch[r][0]);
    if(cnt>=1&&cnt<=n){
        printf("%d",key[r]);
        if(cnt<n)printf(" ");
        else printf("\n");
    }
    cnt++;
    Inorder(ch[r][1]);
}

int main(){
    char op[20];
    int x, y, z;
    while(~scanf("%d%d",&n,&q)){
        if(n < 0 && q < 0)break;
        init();
        while(q--){
            scanf("%s", op);
            if(op[0] == 'C'){
                scanf("%d%d%d",&x, &y, &z);
                CUT(x, y, z);
            }
            else{
                scanf("%d%d", &x, &y);
                Reverse(x, y);
            }
        }
        cnt = 0;
        Inorder(root);
    }
    return 0;
}

hdu 1890
题意： 给了N个数的一个序列，现在要把这n个数变成完全从小到大排列的N个数，那么如何变呢？每次在当前位置找后面所有的最小的数的位置，然后把当前位置和找到的这个位置的这个区间的数反转过来。最后要输出每个数在第i次操作之前的第i个数的位置。
#define key_value ch[ch[root][1]][0]
const int N = 100010;
int pre[N], ch[N][2], sz[N];
//分别表示父结点，键值，左右孩子（0左1右），根结点，结点数量
int rev[N];
int root, tot1;
int n;

//debug部分**********************************
void Treavel(int x){
    if(x){
        Treavel(ch[x][0]);
        printf("结点 %2d:左儿子 %2d 右儿子 %2d  父结点 %2d sz=%2d,rev=%2d\n",x,ch[x][0],ch[x][1],pre[x],sz[x],rev[x]);
        Treavel(ch[x][1]);
    }
}
void debug(){
    printf("root:%d\n", root);
    Treavel(root);
}
//以上是debug部分****************************

void NewNode(int &r, int fa, int k){
    r = k; //每个结点序号就是最开始的位置
    ch[r][0] = ch[r][1] = 0;
    sz[r] = 1;
    rev[r] = 0;
    pre[r] = fa;
}
//反转的更新
void update_rev(int r){
    if(!r)return;
    swap(ch[r][0], ch[r][1]);
    rev[r] ^= 1;
}

void PushUp(int r){
    sz[r] = sz[ch[r][0]]+sz[ch[r][1]]+1;
}

void PushDown(int r){
    if(rev[r]){
        update_rev(ch[r][0]);
        update_rev(ch[r][1]);
        rev[r] = 0;
    }
}

void build(int &x, int l, int r, int fa){
    if(l>r)return;
    int mid = (l+r)/2;
    NewNode(x, fa, mid);
    build(ch[x][0], l, mid-1, x);
    build(ch[x][1], mid+1, r, x);
    PushUp(x);
}

void init(){
    root = tot1 = 0;
    ch[root][0] = ch[root][1] = sz[root] = pre[root] = rev[root] = 0;
    NewNode(root, 0, n+1); //根 父亲 命名
    NewNode(ch[root][1], root, n+2);
    build(key_value, 1, n, ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
//旋转，0为左旋，1为右旋
void Rotate(int x, int kind){
    int y = pre[x];
    PushDown(y);//先把y的标记下传，在把x的标记下传
    PushDown(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    PushUp(y);
}
//Splay调整，将r结点调整到goal下面
void Splay(int r,int goal){
    PushDown(r);
    while(pre[r] != goal){
        if(pre[pre[r]] == goal){//有反转操作，需要先push_down,再判断左右孩子
            PushDown(pre[r]);
            PushDown(r);
            Rotate(r, ch[pre[r]][0] == r);
        }
        else{//有反转操作，需要先push_down
            PushDown(pre[pre[r]]);
            PushDown(pre[r]);
            PushDown(r);
            int y=pre[r];
            int kind = ch[pre[y]][0] == y;
            if(ch[y][kind] == r){
                Rotate(r, !kind);
                Rotate(r, kind);
            }
            else{
                Rotate(y, kind);
                Rotate(r, kind);
            }
        }
    }
    PushUp(r);
    if(goal == 0)root = r;   //更新根结点
}
//得到第k个结点(需要push_down)
int get_kth(int r, int k){
    PushDown(r);
    int t = sz[ch[r][0]]+1;
    if(t == k)return r;
    if(t > k)return get_kth(ch[r][0], k);
    else return get_kth(ch[r][1], k-t);
}

//找前驱(需要PushDown)
int get_pre(int r){
    PushDown(r);
    r = ch[r][0];
    if(r == 0)return -1;
    while(ch[r][1]){
        r = ch[r][1];
        PushDown(r);
    }
    return r;
}

//找后继(需要PushDown)
int get_next(int r){
    PushDown(r);
    r = ch[r][1];
    if(r == 0)return -1;
    while(ch[r][0]){
        r = ch[r][0];
        PushDown(r);
    }
    return r;
}

struct node{
    int val, id;
    bool operator < (const node& rhs)const{
        return val == rhs.val ? id<rhs.id : val<rhs.val;
    }
}a[N];

int  main(){
    while(~scanf("%d", &n)){
        if(!n)break;
        for(int i=1; i<=n; i++){
            scanf("%d", &a[i].val);
            a[i].id = i;
        }
        sort(a+1, a+1+n); //按照价值大小对a进行排序
        init();//本题的话每个结点序号就是最开始的位置。sp树中第i个结点的序号就是第i个数的初始位置。
        //所以对每个数排序，记录初始位置，就可以在树中直接找到要操作的结点。
        for(int i=1; i<=n; i++){
            Splay(a[i].id, 0);// 把第i个结点旋出来
            printf("%d%c", sz[ch[root][0]], i==n?'\n':' ');//左子树的大小就是新的位置
            Splay(get_kth(root, i), 0);
            Splay(get_next(a[i].id), root); //得出a[i].id的后继位置并进行区间翻转
            update_rev(key_value);
        }
    }
    return 0;
}
