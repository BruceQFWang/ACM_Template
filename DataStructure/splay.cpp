splay tree��������������µ�����:
����һ:ά��һЩ��
1.���һ����
2.ɾ��һ����
3.ѯ��һ��������Щ���������
4.ѯ�ʵ�ǰ����Ϊk�����Ƕ���
5.��ѯһ������ǰ�����(���������С����/����С��������)
bzoj 1588
���⣺ÿ����һ��������ǰ������������ҵ�һ������������С��һ���������еĲ�ֵ��������
˼·�����ֲ��������룬��ǰ����������
const int N = 1e5+5;

int pre[N], key[N], ch[N][2], root, tol1;
//�ֱ��ʾ����㣬��ֵ�����Һ��ӣ�0��1�ң�������㣬�������
int n;

//�½�һ�����
void NewNode(int& r, int fa, int k){
    r = ++tol1;
    pre[r] = fa;
    key[r] = k;
    ch[r][0] = ch[r][1] = 0;//���Һ���Ϊ��
}

//��ת��kindΪ1��������Ϊ0������
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

//Splay�����������r������goal����
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
    //���¸����
    if(goal==0)root = r;
}

int Insert(int k){
    int r = root;
    while(ch[r][key[r]<k]){
        //���ظ����� ��ͬ��ֵ���첨���϶�Ϊ0
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

//��ǰ��
int get_pre(int x){
    int tmp = ch[x][0];
    if(tmp == 0)return inf;
    while(ch[tmp][1])tmp = ch[tmp][1];
    return key[x]-key[tmp];
}

//�Һ��
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


�����:ά��һ������
1.��ĳ�����������������һ��ֵ
2.ѯ��ĳ����������/��Сֵ
3.��ѯĳ������ĺ�
4.��תĳ������
5.ƽ��һ������
6.ɾ��/���һ������
����������Ĳ���,splay�������Ƚ�ͳһ.
��������Ҫ��[L,R]������в���,�������Ƚ�L-1�����ת����,Ȼ��R+1�����ת��L-1������(����������),Ȼ�����splay��ƽ�������Ǿ��ܷ���,R+1��������������������Ҫ��[L,R]����,Ȼ������Ҫ��ѯ�����޸�����ֵ,��ֱ�Ӷ������������������.

hdu 3487
/*
 * ��ʼ������1,2,3,...,n
 * �������ֲ����������и�����䷴ת
 * CUT a b c :��[a,b]�и�������Ȼ����ڵ�c��Ԫ�غ���
 * FLIP a b :��ת����[a,b]
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define key_value ch[ch[root][1]][0]
const int N = 300010;
int pre[N], ch[N][2], key[N], sz[N];
//�ֱ��ʾ����㣬��ֵ�����Һ��ӣ�0��1�ң�������㣬�������
int rev[N];
int root, tot1;
int n, q;

//debug����**********************************
void Treavel(int x){
    if(x){
        Treavel(ch[x][0]);
        printf("��� %2d:����� %2d �Ҷ��� %2d  ����� %2d key=%2d,sz=%2d,rev=%2d\n",x,ch[x][0],ch[x][1],pre[x],key[x],sz[x],rev[x]);
        Treavel(ch[x][1]);
    }
}
void debug(){
    printf("root:%d\n", root);
    Treavel(root);
}
//������debug����****************************

void NewNode(int &r, int fa, int k){
    r = ++tot1;
    ch[r][0] = ch[r][1] = 0;
    sz[r] = 1;
    key[r] = k;
    rev[r] = 0;
    pre[r] = fa;
}
//��ת�ĸ���
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
//��ת��0Ϊ������1Ϊ����
void Rotate(int x, int kind){
    int y = pre[x];
    PushDown(y);//�Ȱ�y�ı���´����ڰ�x�ı���´�
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
//Splay��������r��������goal����
void Splay(int r,int goal){
    PushDown(r);
    while(pre[r] != goal){
        if(pre[pre[r]] == goal){//�з�ת��������Ҫ��push_down,���ж����Һ���
            PushDown(pre[r]);
            PushDown(r);
            Rotate(r, ch[pre[r]][0] == r);
        }
        else{//�з�ת��������Ҫ��push_down
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
    if(goal == 0)root = r;   //���¸����
}
//�õ���k�����(��Ҫpush_down)
int get_kth(int r, int k){
    PushDown(r);
    int t = sz[ch[r][0]]+1;
    if(t == k)return r;
    if(t > k)return get_kth(ch[r][0], k);
    else return get_kth(ch[r][1], k-t);
}


//��[l,r]�μ�������������ʣ�¶εĵ�c������
void CUT(int l, int r, int c){
    Splay(get_kth(root, l), 0);
    Splay(get_kth(root, r+2), root);
    int tmp = key_value;  //key_valueΪ����ӵ��Ҷ���
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
//    ����"����1. CUT l r c" ��ֻ��Ҫ�� l-1 ��ת������r+1��ת�� l-1 ��������
//    ��ô [l, r] ֮���������� r+1 ����������������������ԭ����ɾȥ������ r+1 ��ת������
//    ֮��� c ��ת������c+1 ��ת�� c ���������ٰѸղ�ɾ����������ӵ� c+1 ����������
//    ��û���֮ǰ��c+1 ����������ȻΪ�գ�   �����������   ��Ϊ�нڵ�0,���Դ������涼Ҫ+1

//��[l,r]�η�ת
void Reverse(int l, int r){
    Splay(get_kth(root, l), 0);
    Splay(get_kth(root, r+2), root);
    update_rev(key_value);
    PushUp(ch[root][1]);
    PushUp(root);
}
//    ���ڡ�����2. FLIP a b����ֻ��Ҫ������ÿ���ڵ�һ�� rev ��Ǳ�ʾ
//    �Ƿ���Ҫ��ת�Ըýڵ�Ϊ������������������õ����У����߶�������ʹ��������������

//��˳�����
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
���⣺ ����N������һ�����У�����Ҫ����n���������ȫ��С�������е�N��������ô��α��أ�ÿ���ڵ�ǰλ���Һ������е���С������λ�ã�Ȼ��ѵ�ǰλ�ú��ҵ������λ�õ�������������ת���������Ҫ���ÿ�����ڵ�i�β���֮ǰ�ĵ�i������λ�á�
#define key_value ch[ch[root][1]][0]
const int N = 100010;
int pre[N], ch[N][2], sz[N];
//�ֱ��ʾ����㣬��ֵ�����Һ��ӣ�0��1�ң�������㣬�������
int rev[N];
int root, tot1;
int n;

//debug����**********************************
void Treavel(int x){
    if(x){
        Treavel(ch[x][0]);
        printf("��� %2d:����� %2d �Ҷ��� %2d  ����� %2d sz=%2d,rev=%2d\n",x,ch[x][0],ch[x][1],pre[x],sz[x],rev[x]);
        Treavel(ch[x][1]);
    }
}
void debug(){
    printf("root:%d\n", root);
    Treavel(root);
}
//������debug����****************************

void NewNode(int &r, int fa, int k){
    r = k; //ÿ�������ž����ʼ��λ��
    ch[r][0] = ch[r][1] = 0;
    sz[r] = 1;
    rev[r] = 0;
    pre[r] = fa;
}
//��ת�ĸ���
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
    NewNode(root, 0, n+1); //�� ���� ����
    NewNode(ch[root][1], root, n+2);
    build(key_value, 1, n, ch[root][1]);
    PushUp(ch[root][1]);
    PushUp(root);
}
//��ת��0Ϊ������1Ϊ����
void Rotate(int x, int kind){
    int y = pre[x];
    PushDown(y);//�Ȱ�y�ı���´����ڰ�x�ı���´�
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
//Splay��������r��������goal����
void Splay(int r,int goal){
    PushDown(r);
    while(pre[r] != goal){
        if(pre[pre[r]] == goal){//�з�ת��������Ҫ��push_down,���ж����Һ���
            PushDown(pre[r]);
            PushDown(r);
            Rotate(r, ch[pre[r]][0] == r);
        }
        else{//�з�ת��������Ҫ��push_down
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
    if(goal == 0)root = r;   //���¸����
}
//�õ���k�����(��Ҫpush_down)
int get_kth(int r, int k){
    PushDown(r);
    int t = sz[ch[r][0]]+1;
    if(t == k)return r;
    if(t > k)return get_kth(ch[r][0], k);
    else return get_kth(ch[r][1], k-t);
}

//��ǰ��(��ҪPushDown)
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

//�Һ��(��ҪPushDown)
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
        sort(a+1, a+1+n); //���ռ�ֵ��С��a��������
        init();//����Ļ�ÿ�������ž����ʼ��λ�á�sp���е�i��������ž��ǵ�i�����ĳ�ʼλ�á�
        //���Զ�ÿ�������򣬼�¼��ʼλ�ã��Ϳ���������ֱ���ҵ�Ҫ�����Ľ�㡣
        for(int i=1; i<=n; i++){
            Splay(a[i].id, 0);// �ѵ�i�����������
            printf("%d%c", sz[ch[root][0]], i==n?'\n':' ');//�������Ĵ�С�����µ�λ��
            Splay(get_kth(root, i), 0);
            Splay(get_next(a[i].id), root); //�ó�a[i].id�ĺ��λ�ò��������䷭ת
            update_rev(key_value);
        }
    }
    return 0;
}
