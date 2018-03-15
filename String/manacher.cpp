const int N=110005;

char str[N];//原始字符串,从s[0]开始输入
char s[N<<1];//经过Manacher处理后的字符串
int p[N<<1];//保存回文串半径，减1回文长度

void manacher(char str[], int len){//原字符串及其长度
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
