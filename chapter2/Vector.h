#ifndef MY_VECTOR_H
#define MY_VECTOR_H

const int DEFAULT_CAPACITY = 3;
using Rank = int;

template <typename T> //向量模板类
class Vector
{
  protected:
  //数据成员
    Rank _size;    //规模
    int _CAPACITY; //容量      规模<=容量
    T *_elem;      //数据区
  //内部接口
    void copyform(const T *A, Rank lo, Rank hi);//复制数组A的[lo,hi)
    void expand();//装填因子为50%
    void shrink();//小于_size<_capacity的25%缩小
    void permute(); //置乱器，将向量置为乱序，内部接口，对外提供unsort()

    //排序
    void bubbleSort()(Rank lo, Rank hi); //冒泡排序[lo,hi)

  public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c，规模为s，初始化为v
    {
        _elem = new T[_CAPACITY = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }
    Vector(const T *A, int n) { copyform(A, 0, n); }//以数组A的前n-1的元素生成对象
    Vector(const T *A, int lo, int hi) { copyform(A, lo, hi); }//以区间[lo,hi)的元素生成对象
    Vector(const Vector<T> &V) { copyform(V.elem(), 0, V.size()); }//生成的对象中的元素与V相同
    Vector(const Vector<T> &V, Rank lo, Rank hi) { copyform(V.elem(), lo, hi); }//以V中[lo,hi)的元素生成对象
    ~Vector() { delete[] _elem; }//析构函数，释放内存
    
    
    //只读接口
    T *elem() const { return _elem; }//返回头指针
    Rank size() const{ return _size; }//返回_size
    bool empty() const{ return !_size; }//空向量返回1，否则返回0
    Rank find(const T &e, Rank lo, Rank hi) const; //无序查找：在[lo,hi)之间找e
    Rank find(const T &e) const { return find(e, 0, _size); } //无序查找：在[0,_size)之间找e
    void show() const;//测试使用，显示向量中各个元素的值
    
    
    //可写接口
    Vector<T> &operator=(const Vector<T> &); //向量间赋值
    T &operator[](Rank r) const;//使用[]获得元素的引用
    void unsort(Rank lo, Rank hi);//将区间[lo,hi)置乱
    void unsort();//整体置乱[0,_size)
    Rank insert(Rank r, const T &e);//在r出插入e 其与之后元素后移一位,返回插入位置的秩
    Rank insert(const T &e) { return insert(_size, e); }//在最后插入一个元素,返回最后一个元素的秩
    int remove(Rank lo, Rank hi);//去除[lo,hi)间的元素，后面元素前移，返回去除元素的个数
    T remove(Rank r);//去除秩为r的元素，后面元素前移，返回去除的元素的值
    int deduplicate();//去除无序向量的重复元素，返回去除的元素个数 O(n2)
    void traverse(void (*visit)(T &)) { for (int i = 0; i != _elem;++i)
        visit(_elem[i]);
    }

    //有序向量(隐含条件，各个元素之间可以比较大小)假设T已经重载 > 和 ==
    int disordered() const;//因为有序向量可以采用特有的算法，此函数进行判别，返回逆序数
    int uniquify();        //有序向量的唯一化操作
    //查找
    Rank binSearch_A(const T &e, Rank lo, Rank hi)const;//二分查找版本A
    Rank fibSearch(const T &e, Rank lo, Rank hi)const;//fibonacci查找
    Rank binSearch_B(const T &e, Rank lo, Rank hi)const;//二分查找版本B
    Rank binSearch_C(const T &e, Rank lo, Rank hi)const;//二分查找版本C
    Rank Search(const T &e) const;//整体查找
};



#endif