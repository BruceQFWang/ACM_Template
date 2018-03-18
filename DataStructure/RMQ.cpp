Tarjan��Sparse-Table�㷨(ST��)��Ԥ�����Ӷ�O(nlogn),��ѯ���Ӷ�O(1),������С����д�������׳�����֧���޸ġ�
//�����ֵ�������±�� 1 ��ʼ��
const int N=1e6+10;
int a[N];
int dp[N][31], lg[N];  //dp[i][j]��i��ʼ������Ϊ2^j��һ��Ԫ���е���Сֵ
//��ʼ��RMQ,  b�����±��1��ʼ����0��ʼ���޸�
void rmq_init(){
    for(int i=2; i<=n; i++) if(i & (i-1)) lg[i] = lg[i-1]; else lg[i] = lg[i-1]+1;
    for(int i=1; i<=n; i++)dp[i][0]=a[i];
    for(int j=1; (1<<j)<=n; j++)
        for(int i=1; i+(1<<j)-1<=n; i++)
            dp[i][j]=max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
}
//��ѯ���ֵ ,�м䲿���ǽ����
int rmq(int l,int r){
    int k=lg[r-l+1];
    return max(dp[l][k], dp[r-(1<<k)+1][k]);
}
