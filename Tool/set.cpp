set �� multiset �÷�һ�������� multiset �����ظ�Ԫ�ء�
 Ԫ�ط�������ʱ���ᰴ��һ�����������Զ�����Ĭ���ǰ��� less<>������������򡣲� ���޸����������Ԫ��ֵ��ֻ�ܲ����ɾ����
�Զ��� int ����������Ĭ�ϵ��Ǵ�С����ģ���������Ӵ�С��
struct cmp {
  bool operator() (const int& a, const int& b) const {
    return a>b;
  }
};//�����и����ŵģ�ע��
multiset<int,cmp>s;     // class as Compare
���������Ͷ�����˴Ӵ�С�����ˡ�
�ṹ���Զ�����������
 ������ set ���� multiset ��ʱ�����������������������ʱһ��������������
struct node{
  int x,y;
};
struct cmp{//�Ȱ��� x ��С��������x��ͬ����y�Ӵ�С����
  bool operator()(const node &a,const node &b)const {
    if(a.x != b.x)return a.x<b.x;
    else return a.y>b.y;
  }
}; //ע�������и�����
multiset<node,cmp>ms;
multiset<node,cmp>::iterator it;

��Ҫ������
begin() ����ָ���һ��Ԫ�صĵ�����
clear() �������Ԫ��
count() ����ĳ��ֵԪ�صĸ���
empty() �������Ϊ�գ����� true
end() ����ָ�����һ��Ԫ�صĵ�����
erase() ɾ�������е�Ԫ��   (������һ��Ԫ��ֵ�����ߵ�����)
find() ����һ��ָ�򱻲��ҵ�Ԫ�صĵ����� ��û�ҵ����ص�s.end()
insert() �ڼ����в���Ԫ��
size() ������Ԫ�ص���Ŀ
lower_bound() ����ָ����ڣ�����ڣ�ĳֵ�ĵ�һ��Ԫ�صĵ�����
upper_bound() ���ش���ĳ��ֵԪ�صĵ�����
equal_range() ���ؼ����������ֵ��ȵ������޵�����������
(ע����� multiset ɾ������֮��ɾ��ֵ����������ֵ�Ķ�ɾ����ɾ��һ��Ҫ�õ�����)
