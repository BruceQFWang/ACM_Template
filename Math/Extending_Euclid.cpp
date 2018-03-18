void extgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b){ d=a; x=1; y=0;}
    else{ extgcd(b,a%b,d,y,x); y-=x*(a/b); }
}

通解为:
x = x1 + b / gcd(a, b) * t;
y = y1 -  a / gcd(a, b) * t;
所以
// 求二元一次方程最小解
ll solve(ll a, ll b, ll c) {
    if(!a && !b) return c ? -1 : 0;  //a,b,c正负未定要分类
    if(!a) return c % b ? -1 : 0;
    if(!b) return c % a == 0 && c / a >= 0 ? c / a : -1;
    if(b < 0) a = -a, b = -b, c = -c;
    ll x, y, g;
    extgcd(a, b, g, x, y);
    if(c % g) return -1;
    x *= c / g;
    x = (x % b + b) % (b / g);
    return x;
}
