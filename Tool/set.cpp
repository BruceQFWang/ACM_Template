set 和 multiset 用法一样，就是 multiset 允许重复元素。
 元素放入容器时，会按照一定的排序法则自动排序，默认是按照 less<>排序规则来排序。不 能修改容器里面的元素值，只能插入和删除。
自定义 int 排序函数：（默认的是从小到大的，下面这个从大到小）
struct cmp {
  bool operator() (const int& a, const int& b) const {
    return a>b;
  }
};//这里有个逗号的，注意
multiset<int,cmp>s;     // class as Compare
上面这样就定义成了从大到小排列了。
结构体自定义排序函数：
 （定义 set 或者 multiset 的时候定义了排序函数，定义迭代器时一样带上排序函数）
struct node{
  int x,y;
};
struct cmp{//先按照 x 从小到大排序，x相同则按照y从大到小排序
  bool operator()(const node &a,const node &b)const {
    if(a.x != b.x)return a.x<b.x;
    else return a.y>b.y;
  }
}; //注意这里有个逗号
multiset<node,cmp>ms;
multiset<node,cmp>::iterator it;

主要函数：
begin() 返回指向第一个元素的迭代器
clear() 清除所有元素
count() 返回某个值元素的个数
empty() 如果集合为空，返回 true
end() 返回指向最后一个元素的迭代器
erase() 删除集合中的元素   (参数是一个元素值，或者迭代器)
find() 返回一个指向被查找到元素的迭代器 ，没找到返回的s.end()
insert() 在集合中插入元素
size() 集合中元素的数目
lower_bound() 返回指向大于（或等于）某值的第一个元素的迭代器
upper_bound() 返回大于某个值元素的迭代器
equal_range() 返回集合中与给定值相等的上下限的两个迭代器
(注意对于 multiset 删除操作之间删除值会把所以这个值的都删掉，删除一个要用迭代器)
