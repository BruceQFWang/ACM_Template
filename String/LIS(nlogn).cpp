模板一： //poj3903
      fill(dp+1, dp+n+1, inf);
        for(int i=1; i<=n; i++)//a[]为原数组，如果是非递增，则将这句lower改成upper
                *lower_bound(dp+1, dp+1+n, a[i]) = a[i];
        printf("%d\n", (int)(lower_bound(dp+1, dp+1+n, inf)-dp-1)); //返回找到的第一个inf,找不到返回最后一位

模板二：
如果是求不下降子序列，for中if改成>=,lower_bound改成upper_bound
const int maxn=5000005;
int a[maxn],ans[maxn],len;
int getLS(int *a,int n,int *ans){
    int len=1;
    ans[1]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]>=ans[len]) ans[++len]=a[i];
        else{
            int pos=int(upper_bound(ans,ans+len,a[i])-ans);
            ans[pos]=a[i];
        }
    }
    return len;
}
