//�ַ�����0��ʼ���룬next��1��ʼ��ȫ��������Կ���nxt
void  getNext(const char P[],int next[]){
  int  m=strlen(P);
  int i=0,j;
  j=next[0]=-1;
  while(i<m){
    while(-1!=j && P[i]!=P[j])j=next[j];
    next[++i]=++j;
  }
}


void  kmp(const char T[],const char P[],int next[]){
  int n=strlen(T),m=strlen(P);
  int i,j;
  getNext(P,next);
  i=j=0;
  while(i<n){
    while(-1!=j && T[i]!=P[j])j=next[j];
    i++;j++;
    if(j==m)printf("%d\n",i-m+1);//�ҵ���
  }
}
