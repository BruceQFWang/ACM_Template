HDU1023
代码:
//C++ 0ms  1616k
#include <iostream>
#include <stdio.h>
using namespace std;

int a[101][101]={0};
int main(){
  int n,i,j,len,r,temp,t;
  int b[101];
  a[1][0] = 1;
  len = 1;
  b[1] = 1;
  for(i=2;i<=100;i++){
    t = i-1;
    for(j=0;j<len;j++) //乘法
      a[i][j] = a[i-1][j]*(4*t+2);
    for(r=j=0;j<len;j++) { //处理相乘结果
      temp = a[i][j] + r;
      a[i][j] = temp % 10;
      r = temp / 10;
    }
    while(r){ //进位处理
      a[i][len++] = r % 10;
      r /= 10;
    }

    for(j=len-1,r=0;j>=0;j--){ //除法
      temp = r*10 + a[i][j];
      a[i][j] = temp/(t+2);
      r = temp%(t+2);
    }
    while(!a[i][len-1]) //高位零处理
      len --;
      b[i] = len;
    }
    while(cin>>n){
      for(j=b[n]-1;j>=0;j--)
        printf("%d",a[n][j]);
      puts("");
    }
  return 0;
}

//java 358ms 9748k
import java.io.*;
import java.util.*;
import java.math.BigInteger;


public class Main
{
    public static void main(String args[])
    {
        BigInteger[] a = new BigInteger[101];
        a[0] = BigInteger.ZERO;
        a[1] = BigInteger.valueOf(1);
        for(int i = 2; i <= 100; ++i)
            a[i] = a[i - 1].multiply(BigInteger.valueOf(4 * i - 2)).divide(BigInteger.valueOf(i+1));
            Scanner in = new Scanner(System.in);
            int n;
            while(in.hasNext())
            {
                n = in.nextInt();
                System.out.println(a[n]);
            }
    }
}
