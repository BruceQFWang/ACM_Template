//一个比较简单常用的：
ull p[300000];
p[0] = 1;
for(int i=1; i<300000; i++)p[i] = p[i-1]*233;

调用的时候,看哪个用起来方便
第一种：对a-z进行hash   //很容易冲突
ull h;
for(int j=i; j<=n; j++) h += p[s[j]-'a'];
第二种： 对位置进行hash
ull h;
for(int j=i; j<=n; j++) h += p[j]*(s[j]-'a'+1);
