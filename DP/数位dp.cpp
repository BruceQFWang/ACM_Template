/*
 *hdu 3652 ��С�ڵ���n�ĺ���13����13�ı��������ֵĸ�����
 */

int n;
int dp[15][10][2][15]; //λ�� ��һλ �Ƿ����13 ģ13���
ll bit[15]; // 10����

//����Ԥ��������dp
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

//Ȼ��ͳ������[0,n]
//digit[i] ���� n ���ҵ����iλ�Ƕ���,len��n�м�λ��
//�� n = 58 digit[1] = 8 digit[2] = 5
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
    for(int i=len; i>=1; i--){//ö����һλ<n�Ķ�Ӧλ
        for(int j=0; j<dig[i]; j++){//ö����һλ��ȡֵ
            ans+=dp[i][j][1][(13-((s/x)*x)%13)%13];//�տ�ʼs/x����0
            if(bg||(dig[i+1]==1&&j==3)) ans+=dp[i][j][0][(13-((s/x)*x)%13)%13];  //�ж���λ�ǲ���13
        }
        if(dig[i]==3&&dig[i+1]==1) bg=1;  //�ж��Ƿ���ǰ���ѳ���13
        //����5327,����˳�����0000~4999��5000~5299,5300~5319,5320~5326����һ��λ����13��bg=1
        x/=10;
    }
    if(cg&&bg) ans++; //����m�������������
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
���⣺
��[a,b]�����е�������0~9ÿ�����ֳ����˼���
˼·��
��dp[i][j][k]��ʾ����Ϊi����ͷΪj������k�ĸ���
�ֿ�ͳ�ƴ𰸣�����λ��С�ڵ�ǰ����ֱ��ȫ�����ϣ�ʣ��Ĳ��ͳ��
���룺
typedef long long ll;
const int maxn=20;

ll a,b;
ll dp[maxn][maxn][maxn];//����Ϊi����ͷΪj������k�ĸ���
ll bin[maxn];//iλ��������λΪi�����ĸ���
ll res[maxn];//��¼0~9����
int d[maxn];

void init(){//���Ƽ����ÿ������
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

void solve(ll x,int flag){ //����1~x����������
  int dnum=0;//��¼��ǰ����λ��
  ll tmpn=x;
  memset(d, 0, sizeof(d));
  while(x){ d[++dnum]=x%10; x/=10;}
  for(int i=1; i<=dnum-1; i++)//λ��С�ڵ�ǰ����λ��
    for(int j=1; j<=9; j++)
      for(int k=0; k<=9; k++)
        res[k]+=(dp[i][j][k]*flag);
  int tmp=dnum;
  while(tmp){//λ�����ڵ�ǰ����λ�������ͳ��������Ծ�һ��120��������ϸ˼��һ�¹���
    for(int i=0; i<d[tmp]; i++){
      if(!i && tmp==dnum)continue;//�����ظ�����
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
