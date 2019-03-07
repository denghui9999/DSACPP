#ifndef MY_VECTOR_H
#define MY_VECTOR_H

const int DEFAULT_CAPACITY = 3;
using Rank = int;

template <typename T> //向量模板类
class Vector
{
  protected:
    Rank _size;    //规模
    int _CAPACITY; //容量      规模<=容量
    T *_elem;      //数据区
    void copyform(T const *A, Rank lo, Rank hi);
    void expand();
    void shrink();

  public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c，规模为s，初始化为v
    {
        _elem = new T[_CAPACITY = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }
    Vector(T const *A, int n) { copyform(A, 0, n); }
    Vector(T const *A, int lo, int hi) { copyform(A, lo, hi); }
    Vector(Vector<T> const &V) { copyform(V._elem(), 0, V._size()); }
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyform(V._elem(), lo, hi); }
    ~Vector() { delete[] _elem; }
    //只读接口
    T *elem() const { return _elem; }
    Rank size() const{ return _size; }
    bool empty() const{ return !_size; }

    Vector<T> &operator=(Vector<T> const &);//
    T &operator[](Rank r) const;
    void permute();//置乱器，将向量置为乱序
};



#endif