//复杂度O(sqrt(n))
int euler_phi(int n)
{
    int m=(int)sqrt(n+0.5);//n的素数范围在[1,sqrt(n)]之间
    int ret=n;//初始化返回值
    for(int i=2;i<=m;++i)if(!(n%i))//如果i是n的因子(可以保证是素因子)
    {
        ret=ret/i*(i-1);//计算结果
        while(!(n%i))n/=i;//将i作为因子把n“除尽”
    }
    if(n>1)ret=ret/n*(n-1);//n可能也是质数
    return ret;
}

//复杂度O(nloglogn)
//如果要求1~n所有数的欧拉函数值，就需要用到类似于筛素数的思想了，给代码：
const int maxn=100+10;
int phi[maxn];//储存结果
void phi_table(int n)
{
    memset(phi,0,sizeof(phi));
    phi[1]=1;//首项为1
    for(int i=2;i<=n;++i)if(!phi[i])//i必定为素数（类似筛素数法）
    for(int j=i;j<=n;j+=i)//不断枚举i的倍数
    {
        if(!phi[j])phi[j]=j;//如果没有算过就初始化为j
        phi[j]=phi[j]/i*(i-1);//进行计算
    }
}
