һ�࿪�����⣬�� 2 ȡģ�� 01 ������
POJ 1681 ��Ҫö�����ɱ�Ԫ���ҽ��� 1 �������ٵ�

//��2ȡģ��01������
const int maxn = 300;
//��equ�����̣�var����Ԫ�������������Ϊequ,����Ϊvar+1,�ֱ�Ϊ0��var
int equ,var;
int a[maxn][maxn]; //�������
int x[maxn]; //�⼯
int free_x[maxn];//�����洢���ɱ�Ԫ�����ö�����ɱ�Ԫ����ʹ�ã�
int free_num;//���ɱ�Ԫ�ĸ���

//����ֵΪ-1��ʾ�޽⣬Ϊ0��Ψһ�⣬���򷵻����ɱ�Ԫ����
int Gauss(){
  int max_r,col,k;
  free_num = 0;
  for(k = 0, col = 0 ; k < equ && col < var ; k++, col++){
    max_r = k;
    for(int i = k+1;i < equ;i++){
      if(abs(a[i][col]) > abs(a[max_r][col]))
        max_r = i;
    }
    if(a[max_r][col] == 0){
      k--;
      free_x[free_num++] = col;//��������ɱ�Ԫ
      continue;
    }
    if(max_r != k){
      for(int j = col; j < var+1; j++)
        swap(a[k][j],a[max_r][j]);
    }
    for(int i = k+1;i < equ;i++){
      if(a[i][col] != 0){
        for(int j = col;j < var+1;j++)
          a[i][j] ^= a[k][j];
      }
    }
  }
  for(int i = k;i < equ;i++)
    if(a[i][col] != 0)
      return -1;//�޽�
  if(k < var) return var-k;//���ɱ�Ԫ����
  //Ψһ�⣬�ش�
  for(int i = var-1; i >= 0;i--){
    x[i] = a[i][var];
    for(int j = i+1;j < var;j++)
      x[i] ^= (a[i][j] && x[j]);
  }
  return 0;
}

int n;
void init(){
  memset(a,0,sizeof(a));
  memset(x,0,sizeof(x));
  equ = n*n;
  var = n*n;
  for(int i = 0;i < n;i++)
    for(int j = 0;j < n;j++){
      int t = i*n+j;
      a[t][t] = 1;
      if(i > 0)a[(i-1)*n+j][t] = 1;
      if(i < n-1)a[(i+1)*n+j][t] = 1;
      if(j > 0)a[i*n+j-1][t] = 1;
      if(j < n-1)a[i*n+j+1][t] = 1;
    }
}

void solve(){
  int t = Gauss();
  if(t == -1){
    printf("inf\n");
    return;
  }
  else if(t == 0){
    int ans = 0;
    for(int i = 0;i < n*n;i++)
      ans += x[i];
    printf("%d\n",ans);
    return;
  }
  else{
    //ö�����ɱ�Ԫ
    int ans = 0x3f3f3f3f;
    int tot = (1<<t);
    for(int i = 0;i < tot;i++){
      int cnt = 0;
      for(int j = 0;j < t;j++){
        if(i&(1<<j)){
          x[free_x[j]] = 1;
          cnt++;
        }
        else x[free_x[j]] = 0;
      }
      for(int j = var-t-1;j >= 0;j--){
        int idx;
        for(idx = j;idx < var;idx++)
          if(a[j][idx])
            break;
        x[idx] = a[j][var];
        for(int l = idx+1;l < var;l++)
          if(a[j][l])
            x[idx] ^= x[l];
            cnt += x[idx];
      }
      ans = min(ans,cnt);
    }
    printf("%d\n",ans);
  }
}

char str[30][30];
int main(){
  //freopen("in.txt","r",stdin);
  //freopen("out.txt","w",stdout);
  int T;
  scanf("%d",&T);
  while(T--){
    scanf("%d",&n);
    init();
    for(int i = 0;i < n;i++){
      scanf("%s",str[i]);
      for(int j = 0;j < n;j++){
        if(str[i][j] == 'y')
          a[i*n+j][n*n] = 0;
        else a[i*n+j][n*n] = 1;
      }
    }
    solve();
  }
  return 0;
}
