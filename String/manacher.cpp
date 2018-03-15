const int N=110005;

char str[N];//ԭʼ�ַ���,��s[0]��ʼ����
char s[N<<1];//����Manacher�������ַ���
int p[N<<1];//������Ĵ��뾶����1���ĳ���

void manacher(char str[], int len){//ԭ�ַ������䳤��
    int l=0;
    s[l++]='$';
    s[l++]='#';
    for(int i=0; i<len; i++){
        s[l++]=str[i];
        s[l++]='#';
    }
    s[l]=0;
    int mx=0, id=0;
    for(int i=0; i<l; i++){
        p[i]=(mx>i ? min(p[2*id-i], mx-i) : 1);
        while(s[i+p[i]] == s[i-p[i]])p[i]++;
        if(i+p[i]>mx) mx=i+p[i], id=i;
    }
}
