/*
 *hdu 3652 求小于等于n的含有13且是13的倍数的数字的个数。
 */

int n;
int dp[15][10][2][15]; //位数 第一位 是否包含13 模13结果
ll bit[15]; // 10的幂

//首先预处理数组dp
void init() {
    int s=1;
    dp[0][0][0][0]=1;
    for(int i=1; i<=10; i++){
        for(int j=0; j<=9; j++){
            for(int k=0; k<=9; k++){
                for(int l=0; l<13; l++){
                    if(k==3&&j==1)
                        dp[i][j][1][(l+(j*s)%13)%13]+=dp[i-1][k][0][l];
                    else dp[i][j][0][(l+(j*s)%13)%13]+=dp[i-1][k][0][l];
                    dp[i][j][1][(l+(j*s)%13)%13]+=dp[i-1][k][1][l];
                }
            }
        }
        s*=10;
    }
}

//然后统计区间[0,n]
//digit[i] 代表 n 从右到左第i位是多少,len是n有几位。
//如 n = 58 digit[1] = 8 digit[2] = 5
int solve(int m){
    int len=0,dig[20]= {0},x=1,s=m;
    bool bg = 0, cg = 0;
    if(m%13==0) cg=1;
    while(m){
        dig[++len]=m%10;
        m/=10;
        x*=10;
    }
    int ans=0;
    for(int i=len; i>=1; i--){//枚举哪一位<n的对应位
        for(int j=0; j<dig[i]; j++){//枚举这一位的取值
            ans+=dp[i][j][1][(13-((s/x)*x)%13)%13];//刚开始s/x等于0
            if(bg||(dig[i+1]==1&&j==3)) ans+=dp[i][j][0][(13-((s/x)*x)%13)%13];  //判断这位是不是13
        }
        if(dig[i]==3&&dig[i+1]==1) bg=1;  //判断是否在前面已出现13
        //例如5327,计算顺序就是0000~4999，5000~5299,5300~5319,5320~5326，万一高位出现13，bg=1
        x/=10;
    }
    if(cg&&bg) ans++; //等于m的情况单独处理
    return ans;
}

int  main(){
    init();
    while(~scanf("%d", &n)){
        printf("%d\n", solve(n));
    }
    return 0;
}

bzoj1833
题意：
求[a,b]间所有的整数中0~9每个数字出现了几次
思路：
设dp[i][j][k]表示长度为i，开头为j的数中k的个数
分开统计答案，对于位数小于当前数的直接全部加上，剩余的拆分统计
代码：
typedef long long ll;
const int maxn=20;

ll a,b;
ll dp[maxn][maxn][maxn];//长度为i，开头为j的数中k的个数
ll bin[maxn];//i位中所有首位为i的数的个数
ll res[maxn];//记录0~9个数
int d[maxn];

void init(){//递推计算出每个整数
  bin[1]=1;
  for(int i=2; i<=13; i++)bin[i]=bin[i-1]*10;
  for(int i=0; i<=9; i++)dp[1][i][i]=1;
  for(int i=2; i<=13; i++)
    for(int j=0; j<=9; j++)
      for(int z=0; z<=9; z++){
        for(int k=0; k<=9; k++)
           dp[i][j][z]+=dp[i-1][k][z];
        dp[i][z][z]+=bin[i-1];
      }
}

void solve(ll x,int flag){ //计算1~x的所有整数
  int dnum=0;//记录当前数的位数
  ll tmpn=x;
  memset(d, 0, sizeof(d));
  while(x){ d[++dnum]=x%10; x/=10;}
  for(int i=1; i<=dnum-1; i++)//位数小于当前数的位数
    for(int j=1; j<=9; j++)
      for(int k=0; k<=9; k++)
        res[k]+=(dp[i][j][k]*flag);
  int tmp=dnum;
  while(tmp){//位数等于当前数的位数，拆分统计这里可以举一个120的例子仔细思考一下过程
    for(int i=0; i<d[tmp]; i++){
      if(!i && tmp==dnum)continue;//不能重复计算
      for(int j=0; j<=9; j++)
        res[j]+=(dp[tmp][i][j]*flag);
    }
    res[d[tmp]]+=(tmpn%bin[tmp]+1)*flag;
    tmp--;
  }
}

int  main(){
  init();
  scanf("%lld%lld",&a,&b);
  solve(b, 1);solve(a-1, -1);
  for(int i=0; i<=9; i++)
    printf("%lld%c",res[i],i==9?'\n':' ');
  return 0;
}
