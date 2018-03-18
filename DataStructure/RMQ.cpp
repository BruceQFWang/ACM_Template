Tarjan的Sparse-Table算法(ST表)，预处理复杂度O(nlogn),查询复杂度O(1),常数很小。好写，不容易出错，不支持修改。
//求最大值，数组下标从 1 开始。
const int N=1e6+10;
int a[N];
int dp[N][31], lg[N];  //dp[i][j]从i开始，长度为2^j的一段元素中的最小值
//初始化RMQ,  b数组下标从1开始，从0开始简单修改
void rmq_init(){
    for(int i=2; i<=n; i++) if(i & (i-1)) lg[i] = lg[i-1]; else lg[i] = lg[i-1]+1;
    for(int i=1; i<=n; i++)dp[i][0]=a[i];
    for(int j=1; (1<<j)<=n; j++)
        for(int i=1; i+(1<<j)-1<=n; i++)
            dp[i][j]=max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
}
//查询最大值 ,中间部分是交叉的
int rmq(int l,int r){
    int k=lg[r-l+1];
    return max(dp[l][k], dp[r-(1<<k)+1][k]);
}
