//���Ӷ�O(sqrt(n))
int euler_phi(int n)
{
    int m=(int)sqrt(n+0.5);//n��������Χ��[1,sqrt(n)]֮��
    int ret=n;//��ʼ������ֵ
    for(int i=2;i<=m;++i)if(!(n%i))//���i��n������(���Ա�֤��������)
    {
        ret=ret/i*(i-1);//������
        while(!(n%i))n/=i;//��i��Ϊ���Ӱ�n��������
    }
    if(n>1)ret=ret/n*(n-1);//n����Ҳ������
    return ret;
}

//���Ӷ�O(nloglogn)
//���Ҫ��1~n��������ŷ������ֵ������Ҫ�õ�������ɸ������˼���ˣ������룺
const int maxn=100+10;
int phi[maxn];//������
void phi_table(int n)
{
    memset(phi,0,sizeof(phi));
    phi[1]=1;//����Ϊ1
    for(int i=2;i<=n;++i)if(!phi[i])//i�ض�Ϊ����������ɸ��������
    for(int j=i;j<=n;j+=i)//����ö��i�ı���
    {
        if(!phi[j])phi[j]=j;//���û������ͳ�ʼ��Ϊj
        phi[j]=phi[j]/i*(i-1);//���м���
    }
}
